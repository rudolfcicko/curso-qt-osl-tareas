/********************************************************************************
** Form generated from reading UI file 'creadortareas.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREADORTAREAS_H
#define UI_CREADORTAREAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreadorTareas
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label;
    QTableWidget *tableWidget;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CreadorTareas)
    {
        if (CreadorTareas->objectName().isEmpty())
            CreadorTareas->setObjectName(QStringLiteral("CreadorTareas"));
        CreadorTareas->resize(385, 228);
        centralwidget = new QWidget(CreadorTareas);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 150, 75, 23));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 30, 113, 20));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 47, 13));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(155, 21, 221, 171));
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget->verticalHeader()->setDefaultSectionSize(20);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(240, 0, 47, 13));
        CreadorTareas->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CreadorTareas);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 385, 21));
        CreadorTareas->setMenuBar(menubar);
        statusbar = new QStatusBar(CreadorTareas);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        CreadorTareas->setStatusBar(statusbar);

        retranslateUi(CreadorTareas);

        QMetaObject::connectSlotsByName(CreadorTareas);
    } // setupUi

    void retranslateUi(QMainWindow *CreadorTareas)
    {
        CreadorTareas->setWindowTitle(QApplication::translate("CreadorTareas", "MainWindow", 0));
        pushButton->setText(QApplication::translate("CreadorTareas", "Crear", 0));
        lineEdit->setText(QApplication::translate("CreadorTareas", "Pepe", 0));
        label->setText(QApplication::translate("CreadorTareas", "Nombre :", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CreadorTareas", "Etiqueta", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CreadorTareas", "Insertar?", 0));
        label_2->setText(QApplication::translate("CreadorTareas", "Etiquetas", 0));
    } // retranslateUi

};

namespace Ui {
    class CreadorTareas: public Ui_CreadorTareas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREADORTAREAS_H
