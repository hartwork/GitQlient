#pragma once

/****************************************************************************************
 ** GitQlient is an application to manage and operate one or several Git repositories. With
 ** GitQlient you will be able to add commits, branches and manage all the options Git provides.
 ** Copyright (C) 2022 Francesc Martinez
 **
 ** LinkedIn: www.linkedin.com/in/cescmm/
 ** Web: www.francescmm.com
 **
 ** This program is free software; you can redistribute it and/or
 ** modify it under the terms of the GNU Lesser General Public
 ** License as published by the Free Software Foundation; either
 ** version 2 of the License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 ** Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public
 ** License along with this library; if not, write to the Free Software
 ** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 ***************************************************************************************/

#include <QMap>
#include <QObject>
#include <QVector>

#include <cstdint>

class QNetworkAccessManager;
class QProgressDialog;
class QNetworkReply;

struct PluginInfo
{
   QString name;
   QString version;
   QString url;
};

class PluginsDownloader : public QObject
{
   Q_OBJECT

signals:
   void availablePlugins(const QVector<PluginInfo> &pluginsInfo);
   void pluginStored();

public:
   explicit PluginsDownloader(QObject *parent = nullptr);

   void checkAvailablePlugins();
   void downloadPlugin(const QString &url);

private:
   QNetworkAccessManager *mManager = nullptr;
   QProgressDialog *mDownloadLog = nullptr;
   QMap<QNetworkReply *, QPair<uint8_t, QString>> mDownloads;
   uint64_t mTotal = 0U;
   QVector<PluginInfo> mPluginsInfo;

   void processPluginsFile();
   void onDownloadProgress(qint64 read, qint64 total);
   void onDownloadFinished();
};
