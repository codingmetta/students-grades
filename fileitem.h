#ifndef FILEITEM_H
#define FILEITEM_H
#include <QString>



class FileItem
{

public:
     FileItem();

    //to do: Konstruktor der die Netzwerkantwort in ein FileObjekt umwanddelt
     FileItem(QString fileName, double fileSize, int studentsNum, QString bestGrades);

    const QString &fileName() const;

    double fileSize() const;

    int studentsNum() const;

    const QString &bestGrades() const;

    void setFileName(const QString &newFileName);

    void setFileSize(double newFileSize);

    void setStudentsNum(int newStudentsNum);

    void setBestGrades(const QString &newBestGrades);

private:
    QString m_fileName;
    double m_fileSize;
    int m_studentsNum;
    QString m_bestGrades;


};

#endif // FILEITEM_H
