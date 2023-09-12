#include "downloaddialog.h"
#include "ui_downloaddialog.h"
#include <QString>
#include <QTimer>
#include <QDir>
#include "path.h"



downloadDialog::downloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downloadDialog)
{
    ui->setupUi(this);

    /*Lineedit auf korrekte URL setzen zu Testzwecken*/
    ui->lineEdit_url->setText("http://students-grades.talia-deckardt.de/list.txt");

    /*Löschen aller Dateien aus dem Directory zu Testzwecken*/
    QDir dir("/Users/talia/Desktop/C++/ueb/ueb09-studentsGrades/StudentsGradesComputer/downloadedFiles/");
    dir.setNameFilters(QStringList() << "*");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList())
    {
        dir.remove(dirFile);
    }

    /*************************************************/


    m_downloader = new Downloader();
    m_thread = new QThread();
    connect(m_downloader, &Downloader::valueComputed,this,&QDialog::close);


    /*moveToThread() ist eine QObject Methode:
     * void QObject::moveToThread(QThread *targetThread)
     * Changes the thread affinity for this object and its children.
     * The object cannot be moved if it has a parent.
     * Event processing will continue in the targetThread.*/
    m_downloader->moveToThread(m_thread);
    m_thread->start();

}

downloadDialog::~downloadDialog()
{
    delete ui;
}




void downloadDialog::on_pushButton_weiter_clicked()
{
    /* Statt dem direkten Aufruf des Slots:
     * Aufruf der Methode doDownload mit String-Parameter
     * wird in die EventLoop des Arbeits-Threads gelegt.
     * Sobald dieser Kapazität hat, wird die Methode im
     * Arbeits-thread ausgeführt.*/
    QMetaObject::invokeMethod(m_downloader, "doDownload",
                              Q_ARG(QString,ui->lineEdit_url->text()));

}



void downloadDialog::on_pushButton_abbrechen_clicked()
{
    m_thread->requestInterruption();
    m_thread->quit();
    m_thread->wait();
    delete m_thread;
    delete m_downloader;

    emit interrupt();

    this->close();
}

Downloader *downloadDialog::downloader() const
{
    return m_downloader;
}

