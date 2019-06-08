#include <functional>
#include <cstdint>
#include <string>

class RmUpdater
{
public:
    typedef std::function<void(int64_t BytesReceived, int64_t BytesTotal)> DownloadProgress; 
    typedef std::function<void(uint32_t FileIndex, uint32_t TotalFiles)> ExtractProgress; 
    typedef std::function<void(bool UpdateAvailable)> Response; 

public:
    RmUpdater();
    void CheckForUpdates(RmUpdater::Response Callback, bool Client = true);
    void DownloadLatest(RmUpdater::DownloadProgress Progress, RmUpdater::ExtractProgress ExtractCallback, std::string Path, bool Client = true);
    std::string CopyUpdaterToTemporaryFile();
    //downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
protected:
    void OnCheckForUpdatesReply(class QNetworkReply* Reply, RmUpdater::Response Callback);
protected:
    class QNetworkAccessManager* m_Manager = nullptr;
};