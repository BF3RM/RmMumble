#include <QApplication>
#include <QDebug>
#include <QProgressDialog>
#include <QTimer>
#include <QMessageBox>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QDir>
#include <QProcess>
#include "RmUpdater.h"

QProgressDialog* Progress = nullptr;
RmUpdater* Updater = nullptr;

void DownloadUpdate(std::string Path, bool isClient);

int main(int Argc, char** Argv)
{
    QApplication App(Argc, Argv);
    QCommandLineParser Parser;
    Parser.addOption(QCommandLineOption("path", "Path to mumble/murmur", "Path", ""));
    Parser.addOption(QCommandLineOption("server"));
    Parser.addOption(QCommandLineOption("force-update"));
    Parser.addHelpOption();
    Parser.process(App);

    bool IsClient = !Parser.isSet("server");
    bool ForceUpdate = Parser.isSet("force-update");
    QDir Path = QDir(Parser.value("path"));

    Updater = new RmUpdater;

    QString ExeName = (IsClient ? "RmMumble" : "RmMurmur");
    #ifdef WIN32
    ExeName += ".exe";
    #endif;

    QFile BinPath(Path.filePath(ExeName));
    //.\build\bin\RmUpdater.exe --path "C:\Users\Jury\Documents\dev\rm-mumble\build\bin"

    if (!BinPath.exists())
    {
        QMessageBox::critical(Progress, "Error", "--path not valid or not specified!");
        QApplication::quit();
        return 1;
    }

    for (int I = 0; I < Argc; I++)
    {
        if (Argv[I] == "-server")
        {
            IsClient = false;
        }
    }

    Progress = new QProgressDialog("Checking for updates...", "Abort", 0, 100);
    Progress->setCancelButton(nullptr);
    Progress->show();

    if (!ForceUpdate)
    {
        Updater->CheckForUpdates([Path, IsClient](bool UpdateAvailable) 
        {
            if (!UpdateAvailable)
            {
                QString Name = (IsClient ? "RmMumble" : "RmMurmur");
                QMessageBox::information(Progress, "No new update available", "You seem to already have the latest version. If you want to force-download the latest update just run this with --force-update");
                QApplication::quit();
            }
            else
            {
                DownloadUpdate(Path.absolutePath().toStdString(), IsClient);
            }
        }, IsClient);
    }
    else
    {
        DownloadUpdate(Path.absolutePath().toStdString(), IsClient);
    }

    return App.exec();
}

void DownloadUpdate(std::string Path, bool IsClient)
{
    Updater->DownloadLatest([](uint64_t DownloadProgress, uint64_t Total) 
    {
        Progress->setLabelText("Downloading");
        if (Total == DownloadProgress)
        {
            return;
        }
        Progress->setMaximum(Total);
        Progress->setValue(DownloadProgress);
    }, [IsClient, Path](uint32_t FileIndex, uint32_t FileTotal) 
    {
        Progress->setLabelText("Extracting");
        Progress->setMaximum(FileTotal);
        Progress->setValue(FileIndex);

        if (FileIndex == FileTotal)
        {
            QDir MumblePath(Path.c_str());
            QString Name = (IsClient ? "RmMumble" : "RmMurmur");
            QMessageBox::information(Progress, "Update Complete", "Well done! You survived the update. Will restart " + Name + " in a moment...");
            QProcess UpdaterProcess;
            #ifdef WIN32
            UpdaterProcess.setProgram(MumblePath.filePath(Name + ".exe"));
            #else
            UpdaterProcess.setProgram(MumblePath.filePath(Name));
            #endif
            UpdaterProcess.setWorkingDirectory(QString(Path.c_str()));
            UpdaterProcess.startDetached();
            QApplication::quit();
        }

    }, Path);
}