#include "sharedfileitemlist.h"


SharedFileItemList::SharedFileItemList()
{
     //m_fileItems.append(FileItem("grades_0.csv", 12.4, 120,"Ada Lovelace"));


}

SharedFileItemList *SharedFileItemList::instanceOf()
{
    static SharedFileItemList* model= new SharedFileItemList();
    return model;
}


QList<FileItem> *SharedFileItemList::fileItems()
{
    return &m_fileItems;
}
