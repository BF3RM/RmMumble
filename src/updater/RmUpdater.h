#include <functional>
#include <cstdint>

class RmUpdater
{
public:
    typedef std::function<void(int64_t BytesReceived, int64_t BytesTotal)> DownloadProgress; 
    typedef std::function<void(bool UpdateAvailable)> Response; 

public:
    RmUpdater();
    void CheckForUpdates(RmUpdater::Response Callback, bool Client = true);
    void DownloadLatest(RmUpdater::DownloadProgress Progress, std::string Path, bool Client = true);
    //downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
protected:
    void OnCheckForUpdatesReply(class QNetworkReply* Reply, RmUpdater::Response Callback);
protected:
    class QNetworkAccessManager* m_Manager = nullptr;
};