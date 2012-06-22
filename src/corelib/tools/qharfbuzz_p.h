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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#ifndef QHARFBUZZ_P_H
#define QHARFBUZZ_P_H

#include <QtCore/qglobal.h>
#include <harfbuzz-shaper.h>

QT_BEGIN_NAMESPACE

// temporary forward until all the textengine code has been moved to QtCore
Q_CORE_EXPORT void qGetCharAttributes(const HB_UChar16 *string, hb_uint32 stringLength,
                                      const HB_ScriptItem *items, hb_uint32 numItems,
                                      HB_CharAttributes *attributes);

Q_CORE_EXPORT HB_Bool qShapeItem(HB_ShaperItem *item);

// ### temporary
Q_CORE_EXPORT HB_Face qHBNewFace(void *font, HB_GetFontTableFunc tableFunc);
Q_CORE_EXPORT void qHBFreeFace(HB_Face);

Q_CORE_EXPORT HB_Error qHB_GSUB_Select_Script(HB_GSUBHeader*  gsub,
				 HB_UInt         script_tag,
				 HB_UShort*       script_index);

Q_CORE_EXPORT HB_Error qHB_GSUB_Select_Feature(HB_GSUBHeader* gsub,
				                               HB_UInt feature_tag,
				                               HB_UShort script_index,
				                               HB_UShort language_index,
				                               HB_UShort* feature_index);

Q_CORE_EXPORT HB_Error qHB_GSUB_Add_Feature(HB_GSUBHeader* gsub,
                                            HB_UShort feature_index,
                                            HB_UInt property);

Q_CORE_EXPORT HB_Error qHBBufferNew(HB_Buffer *buffer);
Q_CORE_EXPORT HB_Error qHBBufferAddGlyph(HB_Buffer buffer,
                                         HB_UInt glyph_index,
                                         HB_UInt properties,
                                         HB_UInt cluster );

Q_CORE_EXPORT HB_Error qHB_GSUB_Clear_Features(HB_GSUBHeader* gsub);

Q_CORE_EXPORT HB_Error qHB_GSUB_Apply_String(HB_GSUBHeader* gsub, HB_Buffer buffer);

Q_DECLARE_TYPEINFO(HB_GlyphAttributes, Q_PRIMITIVE_TYPE);
Q_DECLARE_TYPEINFO(HB_FixedPoint, Q_PRIMITIVE_TYPE);

QT_END_NAMESPACE

#endif
