/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Designer of the Qt Toolkit.
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

#ifndef DEFAULT_ACTIONPROVIDER_H
#define DEFAULT_ACTIONPROVIDER_H

#include "formeditor_global.h"
#include "actionprovider_p.h"
#include <extensionfactory_p.h>

#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>

QT_BEGIN_NAMESPACE

namespace qdesigner_internal {

class FormWindow;

class QT_FORMEDITOR_EXPORT ActionProviderBase: public QDesignerActionProviderExtension
{
protected:
    explicit ActionProviderBase(QWidget *widget);

public:
    virtual void adjustIndicator(const QPoint &pos);
    virtual Qt::Orientation orientation() const = 0;

protected:
    virtual QRect indicatorGeometry(const QPoint &pos, Qt::LayoutDirection layoutDirection) const;

private:
    QWidget *m_indicator;
};

class QT_FORMEDITOR_EXPORT QToolBarActionProvider: public QObject, public ActionProviderBase
{
    Q_OBJECT
    Q_INTERFACES(QDesignerActionProviderExtension)
public:
    explicit QToolBarActionProvider(QToolBar *widget, QObject *parent = 0);

    virtual QRect actionGeometry(QAction *action) const;
    virtual QAction *actionAt(const QPoint &pos) const;
    Qt::Orientation orientation() const;

protected:
    virtual QRect indicatorGeometry(const QPoint &pos, Qt::LayoutDirection layoutDirection) const;

private:
    QToolBar *m_widget;
};

class QT_FORMEDITOR_EXPORT QMenuBarActionProvider: public QObject, public ActionProviderBase
{
    Q_OBJECT
    Q_INTERFACES(QDesignerActionProviderExtension)
public:
    explicit QMenuBarActionProvider(QMenuBar *widget, QObject *parent = 0);

    virtual QRect actionGeometry(QAction *action) const;
    virtual QAction *actionAt(const QPoint &pos) const;
    Qt::Orientation orientation() const;

private:
    QMenuBar *m_widget;
};

class QT_FORMEDITOR_EXPORT QMenuActionProvider: public QObject, public ActionProviderBase
{
    Q_OBJECT
    Q_INTERFACES(QDesignerActionProviderExtension)
public:
    explicit QMenuActionProvider(QMenu *widget, QObject *parent = 0);

    virtual QRect actionGeometry(QAction *action) const;
    virtual QAction *actionAt(const QPoint &pos) const;
    Qt::Orientation orientation() const;

private:
    QMenu *m_widget;
};

typedef ExtensionFactory<QDesignerActionProviderExtension, QToolBar, QToolBarActionProvider> QToolBarActionProviderFactory;
typedef ExtensionFactory<QDesignerActionProviderExtension, QMenuBar, QMenuBarActionProvider> QMenuBarActionProviderFactory;
typedef ExtensionFactory<QDesignerActionProviderExtension, QMenu, QMenuActionProvider> QMenuActionProviderFactory;

} // namespace qdesigner_internal

QT_END_NAMESPACE

#endif // DEFAULT_ACTIONPROVIDER_H
