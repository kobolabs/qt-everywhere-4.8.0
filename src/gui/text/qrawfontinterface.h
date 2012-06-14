/****************************************************************************
** Copyright (C) 2012 ACCESS, CO., LTD
** All rights reserved.
****************************************************************************/

#ifndef QRAWFONTINTERFACE_H
#define QRAWFONTINTERFACE_H

#include <QObject>
#include <QSharedData>
#include "qfont.h"
#include "qrawfont_p.h"
#include "accessplugininterface.h"

class QRawFontInterface : public ACCESSPluginInterface
{
public:
    virtual ~QRawFontInterface() {}
    virtual bool hasVerticalGlyphs(QExplicitlySharedDataPointer<QRawFontPrivate> d) = 0;
    virtual quint32 substituteWithVerticalVariants(QExplicitlySharedDataPointer<QRawFontPrivate> d, quint32* glyphs, const unsigned length) = 0;
};

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(QRawFontInterface,
                    "com.access_company.qt.Plugin.QRawFontInterface/1.0");

QT_END_NAMESPACE

#endif
