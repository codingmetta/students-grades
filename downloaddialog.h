#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QDialog>
#include "downloader.h"
#include <QString>
#include <QThread>

namespace Ui {
class downloadDialog;
}

class downloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit downloadDialog(QWidget *parent = nullptr);
    ~downloadDialog();

    Downloader *downloader() const;

signals:
    //void sendUrlString(QString url);
    void interrupt();
    //void startThread();

private slots:


    void on_pushButton_weiter_clicked();

    void on_pushButton_abbrechen_clicked();


private:
    Ui::downloadDialog *ui;
    Downloader *m_downloader;
    QThread *m_thread;
};

#endif // DOWNLOADDIALOG_H
