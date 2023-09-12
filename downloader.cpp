#include "downloader.h"
#include <QMessageBox>
#include <QDebug>
#include "path.h"
#include <QDir>


Downloader::Downloader(QObject *parent)
: QObject{parent}
{


}

void Downloader::downloadCSVFiles(QList<QUrl> rr)
{
   m_currentCSVFileRequest = 1;

   for (int i = 0; i < rr.size(); i++){
        qDebug() << "Request Nummer "<< i+1 << "wird gesendet";
        m_manager->get(QNetworkRequest(rr[i]));
    }


}

void Downloader::createRequests()
{
    QList <QUrl> remainingRequests;
    QFile f1("/Users/talia/Desktop/C++/ueb/ueb09-studentsGrades/StudentsGradesComputer/downloadedFiles/list.txt");
    f1.open(QIODevice::ReadOnly);
    QTextStream s1(&f1);
    while (!s1.atEnd()){
      QString s=s1.readLine(); // reads line from file
      QUrl url(s);
      remainingRequests.append(url);
    }
    f1.close();

    m_totalCsvFilesRequests = remainingRequests.length();
    qDebug() << "Es sind "<< remainingRequests.length()<< " Requests vorhanden.";

    downloadCSVFiles(remainingRequests);
}



void Downloader::replyFinished(QNetworkReply *reply)
{
    if(reply->error())
        {
            qDebug() << "ERROR!";
            qDebug() << reply->errorString();
        }
        else
        {
            qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
            qDebug() << reply->header(QNetworkRequest::ContentDispositionHeader).toString();
            qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();;
            qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
            qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();



            //Überprüfen ob Header des HTTP einen filenamen enthalten
            QByteArray filename=  reply->rawHeader("Content-Disposition");
            QString name = QString(filename);
            qDebug() << "Filename:" <<name;

            //Ausgabe aller Header aus dem HTTP Protokoll
            qDebug() << reply->rawHeaderList().length();
            QList <QByteArray> headerList = reply->rawHeaderList();
            QString headerAsString;

            for (int i =0; i < reply->rawHeaderList().length(); i++){
                headerAsString = QString(headerList[i]);
                qDebug() << "HeaderListe: "<< headerAsString;
            }

            /*falls es sich beim Dowload um eine .txt Datei handelt tu dies*/
            if (reply->header(QNetworkRequest::ContentTypeHeader).toString() == "text/plain"){
                //QString filenam = "list.txt";

                //QFile *file = new QFile(path::absolute+filenam);
                QFile *file = new QFile("/Users/talia/Desktop/C++/ueb/ueb09-studentsGrades/StudentsGradesComputer/downloadedFiles/list.txt");


                if(file->open(QFile::Append))
                {
                    file->write(reply->readAll());
                    file->flush();
                    file->close();
                    qDebug() << "all good";
                } else {
                    qDebug() << "something went wrong";
                }
                delete file;

                createRequests();
            }

            /*falls es sich beim Dowload um eine .csv Datei handelt tu dies*/
            if (reply->header(QNetworkRequest::ContentTypeHeader).toString() == "text/csv"){

                qDebug() << "csv wird abgespeichert";

                //File unter bestimmten Namen fortlaufend speichern
                QString fileNumber = QString::number(m_currentCSVFileRequest);
                QString filename = "grades_"+fileNumber+".csv";
                qDebug() << "Dateiname ist: " << filename;
                QFile *file = new QFile(path::absolute+filename);
                if(file->open(QFile::Append))
                {
                    file->write(reply->readAll());
                    file->flush();
                    file->close();
                }
                delete file;



                emit progressUpdated(m_currentCSVFileRequest, m_totalCsvFilesRequests);

                qDebug()<< "    Progress of " << QThread::currentThreadId() << " is "
                        << m_currentCSVFileRequest<< "/"<< m_totalCsvFilesRequests;

                //Warten ob eine Unterbrechung abgefragt wird


                //QThread::sleep(1);//Imitieren einer intensiven Rechenzeit


                if(m_currentCSVFileRequest == m_totalCsvFilesRequests){
                    emit valueComputed();
                }

                if (QThread::currentThread()->isInterruptionRequested()){
                    qDebug() << "Interrupting now.";
                    reply->abort();
                    return;
                }
                m_currentCSVFileRequest++;

            }

        }

        reply->deleteLater();
}

void Downloader::doDownload(QString urlAsAString)
{
    qDebug() << "Running Thread " << QThread::currentThreadId();
    qDebug() << "Download startet.";

    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(replyFinished(QNetworkReply*)));

   /*String von der GUI in eine QUrl umwandeln*/
    QUrl url(urlAsAString);

   /*überprüfen ob dei URL das korrekte Format hat*/
    if(!url.isValid()){
        qDebug() << "Invalid URL";
        QMessageBox box(QMessageBox::Warning, "Warnung", "Die eingegebene URL ist inkorrekt. Bitte korrigieren Sie ihre Eingabe.");
        box.exec();
    }

   m_manager->get(QNetworkRequest(url));

}

