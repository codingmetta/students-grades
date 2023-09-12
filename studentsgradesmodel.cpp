#include "studentsgradesmodel.h"

StudentsGradesModel::StudentsGradesModel(QList <FileItem>* fileItems, QObject *parent)
    : QAbstractTableModel(parent),
        m_fileItems(fileItems)
{

}

QVariant StudentsGradesModel::headerData(int section, Qt::Orientation orientation, int role) const
{    /*Fixed*/
    if (role== Qt::DisplayRole){
        if (orientation == Qt::Horizontal){
            /*Gibt die Kopfzeile zurück*/
            switch (section){
                case 0: return "Filename";
                case 1: return "Filesize kB";
                case 2: return "Students";
                case 3: return "Best Grades";
            }
        } else {
            /*Gibt nur die Zeilennummer zurück; +1 da mit 0 indiziert*/
            return QString::number(section+1);
        }
    }
    /*!:MIT ANGEBEN SONST STUERZT PROGRAMM AB*/
    return QVariant();
    /*******/
}

int StudentsGradesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    /*Fixed*/
    //Anzahl der geladenen Files
    return m_fileItems->size();
    /*******/
}

int StudentsGradesModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

   /*Fixed*/
    return 4;
    /*******/
}

QVariant StudentsGradesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    /**Fixed***/
    //muss noch implementiert werden
    const FileItem& file = m_fileItems->at(index.row());
    if(role == Qt::DisplayRole){

        switch(index.column()){
            case 0: return file.fileName();
            case 1: return file.fileSize();
            case 2: return file.studentsNum();
            case 3: return file.bestGrades();


        }
     }


    /*************/
    return QVariant();
}


void StudentsGradesModel::addFileItem(FileItem newFileItem)
{
    //Model ankündigen das Daten hinzugefügt wurden
     beginInsertRows(QModelIndex(), rowCount(), rowCount());
     m_fileItems->append(newFileItem);
     endInsertRows();

}
