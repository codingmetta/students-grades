#include "mainwindow.h"

#include <QApplication>
#include <path.h>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    path::absolute= "/Users/talia/Desktop/C++/ueb/ueb09-studentsGrades/StudentsGradesComputer/downloadedFiles/";
    w.show();
    return a.exec();
}
