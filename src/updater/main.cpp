#include <QApplication>
#include <QDebug>
#include <QProgressDialog>
#include <QTimer>
#include <QMessageBox>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QDir>
#include "RmUpdater.h"

QProgressDialog* Progress = nullptr;
RmUpdater* Updater = nullptr;

int main(int Argc, char** Argv)
{
    QApplication App(Argc, Argv);
    QCommandLineParser Parser;
    Parser.addOption(QCommandLineOption("path", "Path to mumble/murmur", "Path", ""));
    Parser.addOption(QCommandLineOption("server"));
    Parser.addHelpOption();
    Parser.process(App);

    bool IsClient = !Parser.isSet("server");
    QDir Path = QDir(Parser.value("path"));

    QString ExeName = (IsClient ? "RmMumble" : "RmMurmur");
    #ifdef WIN32
    ExeName += ".exe";
    #endif;

    QFile BinPath(Path.filePath(ExeName));
    //.\build\bin\RmUpdater.exe --path "C:\Users\Jury\Documents\dev\rm-mumble\build\bin"

    if (!BinPath.exists())
    {
        qCritical() << "--path not valid or not specified!";
        //QApplication::quit();
        //return 1;
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

    Updater = new RmUpdater;
   // Updater->DownloadLatest([](uint64_t, uint64_t) {}, Path.absolutePath().toStdString());
    Updater->CheckForUpdates([](bool UpdateAvailable) 
    {
        if (!UpdateAvailable)
        {
            Progress->setLabelText("No new update available");
            QTimer* QuitTimer = new QTimer;
            QObject::connect(QuitTimer, &QTimer::timeout, []() {QApplication::quit();});
            QuitTimer->start(5000);
        }
        else
        {
            Progress->setLabelText("Downloading");

        }
    }, IsClient);

    return App.exec();
}
