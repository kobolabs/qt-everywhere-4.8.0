/****************************************************************************
** Copyright (C) 2012 ACCESS, CO., LTD
** All rights reserved.
****************************************************************************/

#ifndef QFONTENGINEINTERFACE_H
#define QFONTENGINEINTERFACE_H

#include <QObject>
#include <QSharedData>
#include "accessplugininterface.h"
#if defined(Q_OS_LINUX)
#include "qharfbuzz_p.h"
#endif

class QFontEngineInterface
{
public:
    virtual ~QFontEngineInterface() {}
#if defined(Q_OS_LINUX)
    virtual bool hasVerticalGlyphs(HB_Face face) = 0;
    virtual quint32 substituteWithVerticalVariants(HB_Face face, quint32* glyph, const unsigned length) = 0;
#endif
};

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(QFontEngineInterface,
                    "com.access_company.qt.Plugin.QFontEngineInterface/1.0");

QT_END_NAMESPACE

#endif

