/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qunicodetables_p.h"
#include "qlibrary.h"
#include "qtextcodec.h"

#include "qharfbuzz_p.h"

QT_USE_NAMESPACE

extern "C" {

HB_GraphemeClass HB_GetGraphemeClass(HB_UChar32 ch)
{
    const QUnicodeTables::Properties *prop = QUnicodeTables::properties(ch);
    return (HB_GraphemeClass) prop->graphemeBreak;
}

HB_WordClass HB_GetWordClass(HB_UChar32 ch)
{
    const QUnicodeTables::Properties *prop = QUnicodeTables::properties(ch);
    return (HB_WordClass) prop->wordBreak;
}

HB_SentenceClass HB_GetSentenceClass(HB_UChar32 ch)
{
    const QUnicodeTables::Properties *prop = QUnicodeTables::properties(ch);
    return (HB_SentenceClass) prop->sentenceBreak;
}

HB_LineBreakClass HB_GetLineBreakClass(HB_UChar32 ch)
{
    return (HB_LineBreakClass)QUnicodeTables::lineBreakClass(ch);
}


void HB_GetGraphemeAndLineBreakClass(HB_UChar32 ch, HB_GraphemeClass *grapheme, HB_LineBreakClass *lineBreak)
{
    const QUnicodeTables::Properties *prop = QUnicodeTables::properties(ch);
    *grapheme = (HB_GraphemeClass) prop->graphemeBreak;
    *lineBreak = (HB_LineBreakClass) prop->line_break_class;
}

void HB_GetUnicodeCharProperties(HB_UChar32 ch, HB_CharCategory *category, int *combiningClass)
{
    const QUnicodeTables::Properties *prop = QUnicodeTables::properties(ch);
    *category = (HB_CharCategory)prop->category;
    *combiningClass = prop->combiningClass;
}

HB_CharCategory HB_GetUnicodeCharCategory(HB_UChar32 ch)
{
    return (HB_CharCategory)QChar::category(ch);
}

int HB_GetUnicodeCharCombiningClass(HB_UChar32 ch)
{
    return QChar::combiningClass(ch);
}

HB_UChar16 HB_GetMirroredChar(HB_UChar16 ch)
{
    return QChar::mirroredChar(ch);
}

void *HB_Library_Resolve(const char *library, int version, const char *symbol)
{
#ifdef QT_NO_LIBRARY
    return 0;
#else
    return QLibrary::resolve(QLatin1String(library), version, symbol);
#endif
}

} // extern "C"

QT_BEGIN_NAMESPACE

HB_Bool qShapeItem(HB_ShaperItem *item)
{
    return HB_ShapeItem(item);
}

HB_Face qHBNewFace(void *font, HB_GetFontTableFunc tableFunc)
{
    return HB_NewFace(font, tableFunc);
}

void qHBFreeFace(HB_Face face)
{
    HB_FreeFace(face);
}

HB_Error qHB_GSUB_Select_Script(HB_GSUBHeader*  gsub,
				 HB_UInt         script_tag,
				 HB_UShort*       script_index)
{
    return HB_GSUB_Select_Script(gsub, script_tag, script_index);
}

HB_Error qHB_GSUB_Select_Feature(HB_GSUBHeader*  gsub,
				  HB_UInt         feature_tag,
				  HB_UShort        script_index,
				  HB_UShort        language_index,
				  HB_UShort*       feature_index)
{
    return HB_GSUB_Select_Feature(gsub, feature_tag, script_index, language_index, feature_index);
}

void qGetCharAttributes(const HB_UChar16 *string, hb_uint32 stringLength,
                        const HB_ScriptItem *items, hb_uint32 numItems,
                        HB_CharAttributes *attributes)
{
    HB_GetCharAttributes(string, stringLength, items, numItems, attributes);
}


HB_Error qHBBufferNew(HB_Buffer *buffer)
{
    return hb_buffer_new(buffer);
}

HB_Error qHBBufferAddGlyph(HB_Buffer buffer,
                           HB_UInt glyph_index,
                           HB_UInt properties,
                           HB_UInt cluster )
{
    return hb_buffer_add_glyph(buffer, glyph_index, properties, cluster);
}

HB_Error qHB_GSUB_Add_Feature(HB_GSUBHeader* gsub,
                               HB_UShort feature_index,
                               HB_UInt property)
{
    return HB_GSUB_Add_Feature(gsub, feature_index, property);
}

HB_Error qHB_GSUB_Clear_Features(HB_GSUBHeader* gsub)
{
 return HB_GSUB_Clear_Features(gsub);
}

HB_Error qHB_GSUB_Apply_String(HB_GSUBHeader* gsub, HB_Buffer buffer)
{
    return HB_GSUB_Apply_String(gsub, buffer);
}

QT_END_NAMESPACE
