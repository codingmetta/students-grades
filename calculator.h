#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include "fileitem.h"
#include <QFile>
#include <QList>
#include <QStringList>
#include <path.h>
#include <QThread>

class Calculator : public QObject
{
    Q_OBJECT
public:

    explicit Calculator(QObject *parent = nullptr);

    /*startet den Calculator nach dem der Konstruktor aufgerufen wurde */
    Q_INVOKABLE void start();


    void calculateItem(QString fileName,int counter);

    /*lädt alle namen der dateien aus dem directory herunter*/
    QStringList getFileList();

    /*extrahiert die Anzahl der Reihen und gibt einen int an das FileObjekt zurück*/
    int countStudents(QString filename);

    /*extrahiert die Größe des files und gibt es an das fileitem objekt zurück*/
    double getFileSize(QString filename);

    /* gibt den String der besten Studienrende(n) zurück */
    QString calculateBestGrade(QString filename);




    int fileCount() const;
    void setFileCount(int newFileCount);

    const QStringList &fileNamesList() const;
    void setFileNamesList(const QStringList &newFileNamesList);

    /*wird von MainWindow aufgerufen*/
    const QList<FileItem> &fileItemsList() const;

signals:

    void fileItemComputed();
    void oneFileItemComputed(int j);

    void progressUpdated(int item, int itemCount);

private:

    QStringList m_fileNamesList;
    int m_fileCount;

    QList <FileItem> m_fileItemsList;

};

#endif // CALCULATOR_H
