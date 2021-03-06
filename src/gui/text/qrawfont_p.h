/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QRAWFONTPRIVATE_P_H
#define QRAWFONTPRIVATE_P_H

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

#include "qrawfont.h"
#include "qfontengine_p.h"
#include <QtCore/qthreadstorage.h>
#include "qrawfontinterface.h"

#if !defined(QT_NO_RAWFONT)

QT_BEGIN_NAMESPACE

namespace { class CustomFontFileLoader; }

class QRawFontInterface;

class Q_AUTOTEST_EXPORT QRawFontPrivate
{
public:
    QRawFontPrivate()
        : fontEngine(0)
        , hintingPreference(QFont::PreferDefaultHinting)
        , thread(0)
#if defined(Q_WS_WIN)
        , fontHandle(NULL)
        , ptrAddFontMemResourceEx(NULL)
        , ptrRemoveFontMemResourceEx(NULL)
#endif
    {}

    QRawFontPrivate(const QRawFontPrivate &other)
        : hintingPreference(other.hintingPreference)
        , thread(other.thread)
#if defined(Q_WS_WIN)
        , fontHandle(NULL)
        , ptrAddFontMemResourceEx(other.ptrAddFontMemResourceEx)
        , ptrRemoveFontMemResourceEx(other.ptrRemoveFontMemResourceEx)
#endif
    {
        fontEngine = other.fontEngine;
        if (fontEngine != 0)
            fontEngine->ref.ref();
    }

    ~QRawFontPrivate()
    {
        Q_ASSERT(ref == 0);
        //cleanUp();
    }

    void cleanUp();
    void platformCleanUp();
    void platformLoadFromData(const QByteArray &fontData,
                              int pixelSize,
                              QFont::HintingPreference hintingPreference);

    static QRawFontPrivate *get(const QRawFont &font) { return font.d.data(); }

    QFontEngine *fontEngine;
    QFont::HintingPreference hintingPreference;
    QThread *thread;
    QAtomicInt ref;

#if defined(Q_WS_WIN)
    HANDLE fontHandle;

    typedef HANDLE (WINAPI *PtrAddFontMemResourceEx)(PVOID, DWORD, PVOID, DWORD *);
    typedef BOOL (WINAPI *PtrRemoveFontMemResourceEx)(HANDLE);

    PtrAddFontMemResourceEx ptrAddFontMemResourceEx;
    PtrRemoveFontMemResourceEx ptrRemoveFontMemResourceEx;

#endif // Q_WS_WIN

    bool loadPlugin();
    static QRawFontInterface *pluginInterface;
};

QT_END_NAMESPACE

#endif // QT_NO_RAWFONT

#endif // QRAWFONTPRIVATE_P_H
