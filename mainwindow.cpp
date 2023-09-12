#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "downloaddialog.h"
#include "sharedfileitemlist.h"
#include "studentsgradesmodel.h"
#include "calculator.h"
#include <QTimer>
#include <QDir>
#include "path.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);

    statusBar()->showMessage(tr("Progress"));
    statusBar()->addPermanentWidget(ui->progressBar);


    m_studentsGradesModel = new StudentsGradesModel(SharedFileItemList::instanceOf()->fileItems(), this);
    ui->tableView->setModel(m_studentsGradesModel);


    m_threadCalculator= new QThread();
    m_calc= new Calculator();


    connect(m_calc,&Calculator::fileItemComputed,this,&MainWindow::sendFileItemsToModel);
    connect(m_calc,&Calculator::oneFileItemComputed,this,&MainWindow::sendOneFileItemToModel);

    connect(m_calc, &Calculator::progressUpdated, this, &MainWindow::updateProgressbar);
    /*moveToThread() ist eine QObject Methode:
     * void QObject::moveToThread(QThread *targetThread)
     * Changes the thread affinity for this object and its children.
     * The object cannot be moved if it has a parent.
     * Event processing will continue in the targetThread.*/
    m_calc->moveToThread(m_threadCalculator);
    m_threadCalculator->start();
    qDebug() << "Main Thread ID is: " << QThread::currentThreadId();


//    QTimer* timer = new QTimer(this);
//    connect(timer,&QTimer::timeout,dlg->downloader(),&Downloader::testEvent);
//    timer->start(1000);
//    qDebug() << "Main Thread ID is: " << QThread::currentThreadId();

}

MainWindow::~MainWindow()
{
    m_threadCalculator->requestInterruption();
    m_threadCalculator->quit();
    m_threadCalculator->wait();
    delete m_threadCalculator;
    delete ui;
}


void MainWindow::on_download_button_clicked()
{
    dlg = new downloadDialog(this);
    connect(dlg->downloader(),&Downloader::progressUpdated, this, &MainWindow::updateProgressbar);
    connect(dlg->downloader(), &Downloader::valueComputed,this,&MainWindow::enableCalculateButton);
    connect(dlg,&downloadDialog::interrupt,this, &MainWindow::resetProgressBar);
    dlg->exec();

//        QTimer* timer = new QTimer(this);
//        connect(timer,&QTimer::timeout,dlg->downloader(),&Downloader::testEvent);
//        timer->start(1000);
//        qDebug() << "Main Thread ID is: " << QThread::currentThreadId();

}



void MainWindow::updateProgressbar(int item, int itemCount)
{
    ui->progressBar->setValue(item/(double) itemCount* 100.0);

}

void MainWindow::enableCalculateButton()
{
    ui->calculate_button->setEnabled(true);

}

void MainWindow::resetProgressBar()
{
    ui->progressBar->setValue(0);
}



void MainWindow::terminateCalculateThread()
{

}

void MainWindow::sendFileItemsToModel()
{
   for (int j = 0; j < m_calc->fileItemsList().size(); j++){
          FileItem item = m_calc->fileItemsList().at(j);
          m_studentsGradesModel->addFileItem(item);
   }
}

void MainWindow::sendOneFileItemToModel(int j)
{
          FileItem item = m_calc->fileItemsList().at(j);
          m_studentsGradesModel->addFileItem(item);

}

StudentsGradesModel *MainWindow::studentsGradesModel() const
{
    return m_studentsGradesModel;
}


void MainWindow::on_calculate_button_clicked()
{

    /* Statt dem direkten Aufruf des Slots:
     * Aufruf der Methode comupteFaculty mit int-Parameter
     * wird in die EventLoop des Arbeits-Threads gelegt.
     * Sobald dieser Kapazität hat, wird die Methode im
     * Arbeits-thread ausgeführt.*/

    QMetaObject::invokeMethod(m_calc, "start");

    ui->cancel_Button->setEnabled(true);

}


void MainWindow::on_cancel_Button_clicked()
{
    m_threadCalculator->requestInterruption();
    m_threadCalculator->quit();
    m_threadCalculator->wait();
}

