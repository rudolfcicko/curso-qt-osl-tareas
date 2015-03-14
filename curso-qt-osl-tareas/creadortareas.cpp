#include "creadortareas.h"
#include <QDebug>
#include <QTableWidgetItem>
#include "ui_creadortareas.h"

CreadorTareas::CreadorTareas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreadorTareas)
{
    ui->setupUi(this);

    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);

    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(rowCount, 1, item);

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(ui->lineEdit->text()));


    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onCrear()));
}

CreadorTareas::~CreadorTareas()
{
    delete ui;
}

void CreadorTareas::onCrear()
{

    delete this;
}
