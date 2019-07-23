#include <QLayout>
#include <QProgressBar>

#include "Progress.h"

Progress::Progress(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();

    m_ProgressBar = new QProgressBar();
    m_ProgressBar->setMinimum(0);
    m_ProgressBar->setMaximum(100);

    layout->addWidget(m_ProgressBar);
    setLayout(layout);

    setWindowTitle(tr("Progress"));
    resize(200, 200);
}

void Progress::updateProgress()
{
    m_ProgressBar->setValue(m_ProgressBar->value()+1);
}
