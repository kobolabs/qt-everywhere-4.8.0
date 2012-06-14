/****************************************************************************
** Copyright (C) 2012 ACCESS, CO., LTD
** All rights reserved.
****************************************************************************/

#ifndef QACCESSPLUGININTERFACE_H
#define QACCESSPLUGININTERFACE_H

/* undef for X11 */
#undef Unsorted
#undef Bool

#include <QPluginLoader>
#include <QDir>
#include <QApplication>

class ACCESSPluginInterface
{

public:
    virtual ~ACCESSPluginInterface() {}
};


QT_BEGIN_NAMESPACE

class ACCESSPlugin
{
    QStringList list;
    QDir pluginsDir;
    int i;
public:
    ACCESSPlugin() : i(-1){
        pluginsDir = QDir(qApp->applicationDirPath());
        pluginsDir.cd(QString::fromAscii("plugins", 7));
        list = pluginsDir.entryList(QDir::Files);
    }
    QObject * next() {
        i++;
        if (i >= list.size())
            return NULL;
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(list.at(i)));
        return pluginLoader.instance();
    }
};


Q_DECLARE_INTERFACE(ACCESSPluginInterface,
                    "com.access_company.qt.Plugin.ACCESSPluginInterface/1.0");

QT_END_NAMESPACE

#endif
