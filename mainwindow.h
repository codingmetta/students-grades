#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "downloaddialog.h"
#include "studentsgradesmodel.h"
#include "calculator.h"
#include "fileitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    StudentsGradesModel *studentsGradesModel() const;

private slots:
    void on_download_button_clicked();
    void on_calculate_button_clicked();

    void on_cancel_Button_clicked();

public slots:
    void updateProgressbar(int item, int itemCount);
    void enableCalculateButton();
    void resetProgressBar();

    void terminateCalculateThread();
    void sendFileItemsToModel();//nicht genutzt
    void sendOneFileItemToModel(int j);


private:
    Ui::MainWindow *ui;
    StudentsGradesModel *m_studentsGradesModel;
    downloadDialog *dlg;


    QThread *m_threadCalculator;
    Calculator *m_calc;



};
#endif // MAINWINDOW_H
