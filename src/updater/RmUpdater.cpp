#include "RmUpdater.h"
#include "RmVersion.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QApplication>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTemporaryFile>
#include <QTemporaryDir>
#include <QDir>
#include <memory>
#include <QMessageBox>
#include "zlib/contrib/minizip/zip.h"
#include "zlib/contrib/minizip/unzip.h"

#ifdef WIN32
#include <io.h>
#endif

#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

#ifdef WIN32
#define UPDATER_PLATFORM "Windows"
#else
#define UPDATER_PLATFORM "Linux"
#endif

#ifdef ENVIRONMENT64
#define UPDATER_ARCH "64"
#else
#define UPDATER_ARCH "32"
#endif

#ifdef RM_DEVELOPMENT
#define UPDATER_DEV "/dev"
#else
#define UPDATER_DEV ""
#endif

RmUpdater::RmUpdater()
{
    m_Manager = new QNetworkAccessManager();
    m_Manager->setRedirectPolicy(QNetworkRequest::RedirectPolicy::NoLessSafeRedirectPolicy);
}

void RmUpdater::CheckForUpdates(RmUpdater::Response Callback, bool Client)
{
    QNetworkRequest Request;
    Request.setUrl(QUrl(QString("http://rm-mumble.skayahack.uk/latest/%1%2%3%4").arg(
            UPDATER_PLATFORM, (Client ? "Client" : "Server"), UPDATER_ARCH, UPDATER_DEV
    )));
    auto Reply = m_Manager->get(Request);
    QObject::connect(Reply, &QNetworkReply::finished, [Reply, Callback, this]() { OnCheckForUpdatesReply(Reply, Callback); });
}

void RmUpdater::OnCheckForUpdatesReply(class QNetworkReply* Reply, RmUpdater::Response Callback)
{
    if (Reply->error()) 
    {
        qDebug() << "Updater: " << Reply->errorString();
        return;
    }

    QJsonDocument Document = QJsonDocument::fromJson(Reply->readAll());
    if (Document.isEmpty())
    {
        qDebug() << "RmUpdater::OnCheckForUpdatesReply: Empty response";
        return;
    }

    QJsonValue Major = Document.object()["major"];
    QJsonValue Minor = Document.object()["minor"];
    QJsonValue Patch = Document.object()["patch"];

    if (Major.isNull() || Minor.isNull() || Patch.isNull())
    {
        qDebug() << "RmUpdater::OnCheckForUpdatesReply: Invalid version returned";
        qDebug() << "Major: " << Major << " Minor: " << Minor << " Patch: " << Patch;
        return;
    }

    int MajorInt = Major.toString().toInt();
    int MinorInt = Minor.toString().toInt();
    int PatchInt = Patch.toString().toInt();

    if (MajorInt > RM_MAJOR_VERSION
        || (MajorInt == RM_MAJOR_VERSION && MinorInt > RM_MINOR_VERSION)
        || (MajorInt == RM_MAJOR_VERSION && MinorInt == RM_MINOR_VERSION && PatchInt > RM_PATCH_VERSION)
    )
    {
        Callback(true);
    } 
    else
    {
        Callback(false);
    }
    
}

void RmUpdater::DownloadLatest(RmUpdater::DownloadProgress Progress, RmUpdater::ExtractProgress ExtractCallback, std::string StdPath, bool Client)
{
    QNetworkRequest Request;
    Request.setUrl(QUrl(QString("http://rm-mumble.skayahack.uk/get-latest/%1%2%3%4").arg(
            UPDATER_PLATFORM, (Client ? "Client" : "Server"), UPDATER_ARCH, UPDATER_DEV
    )));
    qDebug() << "Downloading " << Request.url();
    auto Reply = m_Manager->get(Request);
    QObject::connect(Reply, &QNetworkReply::downloadProgress, Progress);
    QObject::connect(Reply, &QNetworkReply::finished, [StdPath, Reply, this, ExtractCallback]() 
    { 
        QString Path(StdPath.c_str());
        QTemporaryFile TempZip;
        if (TempZip.open())
        {
            TempZip.write(Reply->readAll());
            TempZip.close();
            
            unzFile ZipFile = unzOpen(TempZip.fileName().toStdString().c_str());
            if (!ZipFile)
            {
                QMessageBox::critical(nullptr, "Error", "Cannot open the downloaded update");
                QApplication::exit();
                return;
            }

            unz_global_info GlobalInfo;
            if (unzGetGlobalInfo(ZipFile, &GlobalInfo) != UNZ_OK )
            {
                QMessageBox::critical(nullptr, "Error", "Cannot read global info");
                unzClose(ZipFile);
                QApplication::exit();
                return;
            }

            QDir Directory(Path);
            for (unsigned long I = 0; I < GlobalInfo.number_entry; I++)
            {
                ExtractCallback(I + 1, GlobalInfo.number_entry);
                unz_file_info FileInfo;
                char FileName[512];
                if (unzGetCurrentFileInfo(ZipFile, &FileInfo, FileName, 512, nullptr, 0, nullptr, 0 ) != UNZ_OK)
                {
                    QMessageBox::critical(nullptr, "Error", "Cannot read file info");
                    unzClose(ZipFile);
                    QApplication::exit();
                    return;
                }

                QString FilePath(FileName);
                if (FilePath.endsWith('/'))
                {
                    Directory.mkpath(FilePath);
                    qInfo() << "Creating folder " << Directory.filePath(FileName);
                }
                else
                {
                    if (unzOpenCurrentFile(ZipFile) != UNZ_OK)
                    {
                        QMessageBox::critical(nullptr, "Error", "Could not open current file");
                        unzClose(ZipFile);
                        QApplication::exit();
                        return;
                    }

                    QFile File(Directory.filePath(FilePath));
                    if (!File.open(QIODevice::Truncate | QIODevice::WriteOnly))
                    {
                        QMessageBox::critical(nullptr, "Error", "Could not open " + File.fileName() + " for writing. " + File.errorString());
                        unzCloseCurrentFile(ZipFile);
                        unzClose(ZipFile);
                        QApplication::exit();
                    }

                    const size_t BufferSize = 8192;
                    char* Buffer = new char[BufferSize];
                    int Error = UNZ_OK;
                    do
                    {
                        Error = unzReadCurrentFile(ZipFile, Buffer, BufferSize);
                        if (Error < 0)
                        {
                            QMessageBox::critical(nullptr, "Error", "There was an error while reading file " + Directory.filePath(FilePath) + ". Error code: " + Error);
                            unzCloseCurrentFile(ZipFile);
                            unzClose(ZipFile);
                            QApplication::exit();
                            return;
                        }

                        File.write(Buffer, Error);
                    } while (Error > 0);
                    qInfo() << "Extracted " << Directory.filePath(FilePath);
                    File.close();
                }

                unzCloseCurrentFile(ZipFile);
                if ((I + 1) < GlobalInfo.number_entry)
                {
                    if (unzGoToNextFile(ZipFile) != UNZ_OK)
                    {
                        QMessageBox::critical(nullptr, "Error", "Could not read next file");
                        unzClose(ZipFile);
                        QApplication::exit();
                        return;
                    }
                }
            }
        }
        else
        {
            qCritical() << "Couldn't create a temporary file to store the update!";
            QApplication::exit();
        }
       // OnCheckForUpdatesReply(Reply);
    });
}

std::string RmUpdater::CopyUpdaterToTemporaryFile()
{
    QTemporaryDir Dir;
    Dir.setAutoRemove(false);
    QDir UpdaterDir(QCoreApplication::applicationDirPath());

    QString LibPostfix = "dll";
    QString UpdaterPostfix = ".exe";

    #ifndef WIN32
    LibPostfix += "so";
    QString UpdaterPostfix = "";
    #endif

    QStringList Libraries = UpdaterDir.entryList(QStringList() << ("*." + LibPostfix), QDir::Files);

    for(auto& Library : Libraries)
    {
        QFile::copy(UpdaterDir.filePath(Library), Dir.filePath(Library));
    }

    QFile::copy(UpdaterDir.filePath("RmUpdater" + UpdaterPostfix), Dir.filePath("RmUpdater" + UpdaterPostfix ));

    return Dir.path().toStdString();
}
