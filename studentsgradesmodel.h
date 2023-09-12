#ifndef STUDENTSGRADESMODEL_H
#define STUDENTSGRADESMODEL_H
#include "fileitem.h"

#include <QAbstractTableModel>

class StudentsGradesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit StudentsGradesModel(QList <FileItem>* fileItems,QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
public slots:
    //Manuell: FileItem hinzufügen zu dem Model
    void addFileItem(FileItem newFileItem);
private:
    QList <FileItem>* m_fileItems;

};

#endif // STUDENTSGRADESMODEL_H
