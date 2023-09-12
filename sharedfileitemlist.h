#ifndef SHAREDFILEITEMLIST_H
#define SHAREDFILEITEMLIST_H
#include "fileitem.h"
#include <QList>


class SharedFileItemList
{
public:
    /*erlaubt einmaliges Instantiieren*/
    static SharedFileItemList *instanceOf();

    /*Getter gibt die Items zurück*/
    QList <FileItem>* fileItems();

private:
    QList<FileItem> m_fileItems;


    SharedFileItemList();
};

#endif // SHAREDFILEITEMLIST_H
