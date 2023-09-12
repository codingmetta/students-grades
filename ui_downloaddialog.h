/********************************************************************************
** Form generated from reading UI file 'downloaddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADDIALOG_H
#define UI_DOWNLOADDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_downloadDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_anweisung;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_url;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_weiter;
    QPushButton *pushButton_abbrechen;

    void setupUi(QDialog *downloadDialog)
    {
        if (downloadDialog->objectName().isEmpty())
            downloadDialog->setObjectName(QString::fromUtf8("downloadDialog"));
        downloadDialog->resize(443, 162);
        verticalLayout_2 = new QVBoxLayout(downloadDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_anweisung = new QLabel(downloadDialog);
        label_anweisung->setObjectName(QString::fromUtf8("label_anweisung"));

        verticalLayout->addWidget(label_anweisung);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit_url = new QLineEdit(downloadDialog);
        lineEdit_url->setObjectName(QString::fromUtf8("lineEdit_url"));

        horizontalLayout_2->addWidget(lineEdit_url);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 33, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_weiter = new QPushButton(downloadDialog);
        pushButton_weiter->setObjectName(QString::fromUtf8("pushButton_weiter"));

        horizontalLayout->addWidget(pushButton_weiter);

        pushButton_abbrechen = new QPushButton(downloadDialog);
        pushButton_abbrechen->setObjectName(QString::fromUtf8("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);


        horizontalLayout_3->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(downloadDialog);

        QMetaObject::connectSlotsByName(downloadDialog);
    } // setupUi

    void retranslateUi(QDialog *downloadDialog)
    {
        downloadDialog->setWindowTitle(QCoreApplication::translate("downloadDialog", "Download", nullptr));
        label_anweisung->setText(QCoreApplication::translate("downloadDialog", "Bitte gebe die gew\303\274nschte URL ein.", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_url->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        lineEdit_url->setText(QString());
        lineEdit_url->setPlaceholderText(QCoreApplication::translate("downloadDialog", "URL eingeben", nullptr));
        pushButton_weiter->setText(QCoreApplication::translate("downloadDialog", "Weiter", nullptr));
        pushButton_abbrechen->setText(QCoreApplication::translate("downloadDialog", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class downloadDialog: public Ui_downloadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADDIALOG_H
