#include <functional>

class RmUpdater
{
public:
    void CheckForUpdates(std::function<void(bool UpdateAvailable)> Callback, bool Client = true);
protected:
    void OnCheckForUpdatesReply(class QNetworkReply* Reply);
protected:
    std::function<void(bool UpdateAvailable)> m_UpdateCheckCallback;
};