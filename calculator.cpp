#include "calculator.h"
#include <QDebug>
#include <QStringList>
#include <QDir>
#include <math.h>
#include <QByteArray>


Calculator::Calculator(QObject *parent)
    : QObject{parent}
{

}


//void Calculator::start()
//{

//    m_fileNamesList = getFileList();
//    m_fileCount = fileNamesList().count();

//    for (int i =0; i < fileCount(); i++){

//        //1.Initialisieren eines FileItems
//        FileItem fileItem;


//        //2. Name des Fileitems wird gesetzt
//        fileItem.setFileName(m_fileNamesList[i]);


//        // 3. Dateigröße wird gesetzt
//        fileItem.setFileSize(getFileSize(m_fileNamesList[i]));


//        //todo:4. Studierendenanzahl wird gesetzt
//        fileItem.setStudentsNum(countStudents(m_fileNamesList[i]));


//        //todo:5.Studierende mit Bestnote wird gesetzt
//        fileItem.setBestGrades(calculateBestGrade(m_fileNamesList[i]));


//        //temporäres FileItem der FileItemListe hinzufügen um es abzuspeichern
//        m_fileItemsList.append(fileItem);

//        //qDebug() <<"Item"<< i<< "Name is" <<m_fileItemsList.value(i).fileName();
//        //qDebug() <<"Item"<< i<< "Size is" <<m_fileItemsList.value(i).fileSize();


//        //Signal emittieren das die Progressbar aktualisiert werden soll
//        emit progressUpdated(i+1, fileCount());

//        //QThread::sleep(1);

//    }

//    //das MainWindow ruft m_calc->m_fileItemsList ab und übergibt die berechneten FileItems an das Model
//    emit fileItemComputed();
//}

void Calculator::start()
{

    m_fileNamesList = getFileList();
    m_fileCount = fileNamesList().count();

    for (int i =0; i < fileCount(); i++){
        qDebug()<<"Calculation Request of Fileitem Nr." << i+1 << "send.";
        calculateItem(m_fileNamesList[i],i+1);
    }
}


void Calculator::calculateItem(QString fileName,int counter)
{

     qDebug()<<"Calculation  of Fileitem Nr." << counter << "started.";

    //1.Initialisieren eines FileItems
    FileItem fileItem;


    //2. Name des Fileitems wird gesetzt
    fileItem.setFileName(fileName);


    // 3. Dateigröße wird gesetzt
    fileItem.setFileSize(getFileSize(fileName));


    //todo:4. Studierendenanzahl wird gesetzt
    fileItem.setStudentsNum(countStudents(fileName));


    //todo:5.Studierende mit Bestnote wird gesetzt
    fileItem.setBestGrades(calculateBestGrade(fileName));


    //temporäres FileItem der FileItemListe hinzufügen um es abzuspeichern
    m_fileItemsList.append(fileItem);

    //qDebug() <<"Item"<< i<< "Name is" <<m_fileItemsList.value(i).fileName();
    //qDebug() <<"Item"<< i<< "Size is" <<m_fileItemsList.value(i).fileSize();

    QThread::sleep(1);

    //Signal emittieren das die Progressbar aktualisiert werden soll
    emit progressUpdated(counter, fileCount());

    //Signal emittieren das ein neues FileItem dem Model hinzugefügt wird
    emit oneFileItemComputed(counter-1);

    qDebug()<<"Calculation  of Fileitem Nr." << counter << "finished.";

    if (QThread::currentThread()->isInterruptionRequested()){
        qDebug() << "Interrupting now.";
        return;
    }

}


/*Funktion lädt die Namen der Dateien aus dem Directory in eine QStringList;
*/
QStringList Calculator::getFileList()
{
    QDir dir = QDir(path::absolute);
    dir.setNameFilters(QStringList("*.csv"));

    qDebug() << "Scanning: " << dir.path();

    //QStringList enthält alle Dateinamen mit .csv Endung
    QStringList fileNamesList = dir.entryList();


    /**************nur zu Testzwecken*****************/
     for (int i=0; i<fileNamesList.count(); i++)
     {
         if(fileNamesList[i] != "main.nut" &&
            fileNamesList[i] != "info.nut")
         {

            // m_fileItemsList.append(new FileItem());
             //m_fileItemsList[i]->setFileName(m_fileNamesList[i]);
             //qDebug() << "Filename in QList is: " << m_fileItemsList[i]->fileName();
             qDebug() << "Found file: " << fileNamesList[i];
         }
     }

     /*****************************************************/

   return fileNamesList;

}


int Calculator::countStudents(QString filename)
{
    int studentNum=0;
    QStringList studentsList;

    QFile file(path::absolute+ filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    while (!file.atEnd()) {
        QString line = file.readLine();
        studentsList.append(line.split(',').first());
    }
    file.close();

    studentsList.pop_front(); //löscht den Header "name"
    //qDebug() << "File contains"<<studentsList<< "Elements";

    studentNum= studentsList.size();


    return studentNum;

    /****************alterantive Lösung: *********************/
    // int studentNum=0;
 //    QStringList elementList;

 //    QFile file(path::absolute+ filename);
 //    if (!file.open(QIODevice::ReadOnly)) {
 //        qDebug() << file.errorString();
 //    }

 //    while (!file.atEnd()) {
 //        QString line = file.readLine();
 //        elementList.append(line.split(','));
 //    }
 //    file.close();

 //    //qDebug() << "File contains "<<elementList.size()<< "Elements";
 //    studentNum= elementList.size()/6;
 //    studentNum = studentNum-1; //abzüglich Kopfzeile
 //    //qDebug() << "File contains "<<studentNum<< "Students";
//      return studentNum;
    /**************************************************************/
}

double Calculator::getFileSize(QString filename)
{
    double filesize = 0;


    QFile f(path::absolute+ filename);
   // qDebug() << "Dateigröße ist "<<f.size();
    qint64 size=f.size();
    filesize = static_cast<double>(size);
    filesize = filesize/1000;
    double scale = 0.01;  // i.e. round to nearest one-hundreth
    filesize = floor(filesize / scale + 0.5) * scale;
    //qDebug() << "Dateigröße nach cast ist "<<filesize;
    return filesize;
}


/* - extrahiert die paarweise den Namen + Durchschnittsnote (Summe aller Noten/Anzahl der Noten) und speichert sie in einer key/value liste
 * - sucht das Maximum aus den values der liste heraus
 * - vergleich wie viele keys den gleichen value haben und zwischenspeichern in konkattenierten string*/
QString Calculator::calculateBestGrade(QString filename)
{
    QString bestStudent;
    QMultiMap <double,QString> results;
    QFile file(path::absolute+ filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    while (!file.atEnd()) {

        QList <QStringList> allStudents;

        /*liest eine Zeile (=Studierende) aus dem File als String aus */
        QString str = file.readLine();


        /*splittet die Zeile,sodass eine StringListe mit einzelnen
         * Werten für name, math, programming1, programming2 etc. entsteht*/
        QStringList student = str.split(QLatin1Char(','));
        //qDebug() << "each Line splitted: " << student;


        /*fügt die StringListe(Student) der Liste(allStudents) hinzu*/
        allStudents.append(student);


        /*iteriert über die Liste (alle Studierenden) und berechnet pro QStringlist (Studierende*r)
         * die Durchschnittsnote;
         * fügt Durchschnittsnote und Name einer QMultimap hinzu */
        for (int i = 0; i < allStudents.size(); i++){
            QString name;
            double durchschnittsnote;
            double note1; double note2; double note3; double note4;double note5;

            name =allStudents.at(i).first();
            //qDebug() << "Name: " << name;

            QString note1Str = allStudents.at(i)[i+1];
            note1 =note1Str.toDouble();
            //qDebug() << "Note1: " << note1;
            QString note2Str = allStudents.at(i)[i+2];
            note2 =note2Str.toDouble();
            //qDebug() << "Note2: " << note2;
            QString note3Str = allStudents.at(i)[i+3];
            note3 =note3Str.toDouble();
            //qDebug() << "Note3: " << note3;
            QString note4Str = allStudents.at(i)[i+4];
            note4 =note4Str.toDouble();
           // qDebug() << "Note4: " << note4;
            QString note5Str = allStudents.at(i)[i+5];
            note5 =note5Str.toDouble();
            //qDebug() << "Note5: " << note5;

            durchschnittsnote = (note1+note2+note3+note4+note5)/5;
            //qDebug() << "DS: " << durchschnittsnote;
            results.insert( durchschnittsnote,name);

            /*++++++++++++++++++Zum testen was passiert, falls es mehrere Studierende mit Bestnoten gibt+++++++++++++++++++++*/
            //results.insert( durchschnittsnote,"Talia Deckardt");
            /***************************************************************************************************************/
            }
    }

    file.close();

    /*Zum Testen: Über die Map iterieren und Werte ausgeben*/
    //    QMapIterator<double, QString> m(results);
    //    while (m.hasNext()) {
    //        m.next();
    //        qDebug() << m.key() << ": " << m.value();
    //    }

    /*Alle Wert(e) aus der QMultiMap laden die im letzten Key "Beste Durchschnittsnote" gespecihert sind;
     * es sind mehrere Werte vorhanden falls es mehrmals die Bestnote gibt*/
    QStringList values = results.values(results.lastKey());

    /*Zusammenführen der StringList die ggf. mehrere Namen von Studierenden mit Bestnote enthält
     * zu dem QString mittels Seperator */
    bestStudent = values.join(",");


    qDebug() << "Best student: "<<results.last(); //letzter Wert in einer QMultiMap ist immer der mit dem max Key(hier: beste Durchschnittsnote)

    return bestStudent;
}

int Calculator::fileCount() const
{
    return m_fileCount;
}

void Calculator::setFileCount(int newFileCount)
{
    m_fileCount = newFileCount;
}

const QStringList &Calculator::fileNamesList() const
{
    return m_fileNamesList;
}

void Calculator::setFileNamesList(const QStringList &newFileNamesList)
{
    m_fileNamesList = newFileNamesList;
}

const QList<FileItem> &Calculator::fileItemsList() const
{
    return m_fileItemsList;
}


