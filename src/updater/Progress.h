#ifndef PROGRESS_H
#define PROGRESS_H

#include <QWidget>

class QProgressBar;

class Progress : public QWidget
{
    Q_OBJECT

public:
    Progress(QWidget *parent = 0);

public slots:
    void updateProgress();

private:
    QProgressBar* m_ProgressBar = nullptr;
};

#endif
