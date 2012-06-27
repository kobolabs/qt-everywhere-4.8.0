/*
    Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies)
    Copyright (C) 2008 Holger Hans Peter Freyther

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

    This class provides all functionality needed for loading images, style sheets and html
    pages from the web. It has a memory cache for these objects.
*/
#include "config.h"
#include "GlyphPageTreeNode.h"

#if HAVE(QRAWFONT)
#include "SimpleFontData.h"
#include "Font.h"
#include <QFontMetricsF>
#include <QTextLayout>
#endif

namespace WebCore {

#if HAVE(QRAWFONT)
bool GlyphPage::fill(unsigned offset, unsigned length, UChar* buffer, unsigned bufferLength, const SimpleFontData* fontData)
{
    QRawFont rawFont = fontData->platformData().rawFont();
    QString qstring = QString::fromRawData(reinterpret_cast<const QChar*>(buffer), static_cast<int>(bufferLength));
    QVector<quint32> indexes = rawFont.glyphIndexesForString(qstring);
    quint32 *glyphs = indexes.data();

    bool haveGlyphs = false;
    bool lookVariants = false;

    if (fontData->platformData().rawFont().hasVerticalGlyphs()) {
#if ENABLE(EPUB)
        TextOrientation textOrientation = fontData->platformData().textOrientation();
        if (textOrientation == TextOrientationUpright)
            lookVariants = true;
        else if (textOrientation == TextOrientationVerticalRight) {
            for (unsigned i = 0; i < length; ++i) {
                if (Font::isUprightOrientation(buffer[i])) {
                    lookVariants = true;
                    break;
                }
            }
        }
#else
        for (unsigned i = 0; i < length; ++i) {
            if (!Font::isCJKIdeograph(buffer[i])) {
                lookVariants = true;
                break;
            }
        }
#endif
    }

    if (lookVariants)
        rawFont.substituteWithVerticalVariants(glyphs, indexes.size());

    for (unsigned i = 0; i < length; ++i) {
        Glyph glyph = (i < indexes.size()) ? glyphs[i] : 0;
        if (!glyph)
            setGlyphDataForIndex(offset + i, 0, 0);
        else {
            haveGlyphs = true;
            setGlyphDataForIndex(offset + i, glyph, fontData);
        }
    }
    return haveGlyphs;
}
#else

void GlyphPageTreeNode::pruneTreeCustomFontData(const FontData*)
{
}

void GlyphPageTreeNode::pruneTreeFontData(const WebCore::SimpleFontData*)
{
}
#endif // HAVE(QRAWFONT)

}
