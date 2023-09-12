#include "fileitem.h"

FileItem::FileItem()

{

}


//FileItem::FileItem(QObject *parent)
//: QObject{parent}
//{

//}
//FileItem::FileItem(QString fileName, double fileSize, int studentsNum, QString bestGrades,QObject *parent)
//: QObject{parent}
//{
//m_fileName= fileName;
//m_fileSize = fileSize;
//m_studentsNum = studentsNum;
//m_bestGrades =bestGrades;
//}

FileItem::FileItem(QString fileName, double fileSize, int studentsNum, QString bestGrades)
{
m_fileName= fileName;
m_fileSize = fileSize;
m_studentsNum = studentsNum;
m_bestGrades =bestGrades;
}

const QString &FileItem::fileName() const
{
    return m_fileName;
}

double FileItem::fileSize() const
{
    return m_fileSize;
}

int FileItem::studentsNum() const
{
    return m_studentsNum;
}

const QString &FileItem::bestGrades() const
{
    return m_bestGrades;
}

void FileItem::setFileName(const QString &newFileName)
{
    m_fileName = newFileName;
}

void FileItem::setFileSize(double newFileSize)
{
    m_fileSize = newFileSize;
}

void FileItem::setStudentsNum(int newStudentsNum)
{
    m_studentsNum = newStudentsNum;
}

void FileItem::setBestGrades(const QString &newBestGrades)
{
    m_bestGrades = newBestGrades;
}
