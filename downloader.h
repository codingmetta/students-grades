#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QDebug>
#include <QThread>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    void downloadCSVFiles(QList <QUrl> rr);
    void createRequests();

public slots:
    //eventuell als Q_INVOKABLE markieren?
    void replyFinished(QNetworkReply *reply);

    //wird aufgerufen wenn der User den Dowloadbutton betätigt
    void doDownload(QString urlAsAString);

    void testEvent(){
        qDebug() << "Test event occured in side thread:" << QThread::currentThreadId();
        QThread::sleep(2); //längere Berechnung imitieren
    }
signals:

    void valueComputed();
    void progressUpdated(int item, int itemCount);

private:
    QNetworkAccessManager *m_manager;
    int m_totalCsvFilesRequests;
    int m_currentCSVFileRequest;
};

#endif // DOWNLOADER_H
