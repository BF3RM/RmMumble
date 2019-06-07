#include "RmUpdater.h"
#include "RmVersion.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>

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

void RmUpdater::CheckForUpdates(std::function<void(bool UpdateAvailable)> Callback, bool Client)
{
    m_UpdateCheckCallback = Callback;
    QNetworkAccessManager* Manager = new QNetworkAccessManager();
    QObject::connect(Manager, &QNetworkAccessManager::finished, std::bind(&RmUpdater::OnCheckForUpdatesReply, this, std::placeholders::_1));
    QNetworkRequest Request;
    Request.setUrl(QUrl(QString("http://rm-mumble.skayahack.uk/latest/%1%2%3%4").arg(
            UPDATER_PLATFORM, (Client ? "Client" : "Server"), UPDATER_ARCH, UPDATER_DEV
    )));
    Manager->get(Request);
}

void RmUpdater::OnCheckForUpdatesReply(class QNetworkReply* Reply)
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

    QJsonValue Major = Document["major"];
    QJsonValue Minor = Document["minor"];
    QJsonValue Patch = Document["patch"];

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
        m_UpdateCheckCallback(true);
    } 
    else
    {
        m_UpdateCheckCallback(false);
    }
    
}
