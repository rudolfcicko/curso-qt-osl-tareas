#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionNuevaTarea->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));


    //Setup database
    ConecToDb(db_, "tareas");


    db_.exec("CREATE TABLE IF NOT EXISTS tareas ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT,"
              "descripcion TEXT,"
              "date TEXT,"
              "done INTEGER,"
              "id_categ INTEGER"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS categorias ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT,"
              "descripcion TEXT"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS etiquetas ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS tareas_etiq ("
              "id_tarea INTEGER,"
              "id_etiq INTEGER"
              ");");

    //db_.exec("DELETE FROM categorias");
    //db_.exec("DELETE FROM etiquetas");
    datos_cargados = false;

    connect(ui->actionNuevaTarea, SIGNAL(triggered()), this, SLOT(onAddTarea()));
    connect(ui->actionNuevaCateg, SIGNAL(triggered()), this, SLOT(onAddCategoria()));
    connect(ui->actionNuevaEtiq, SIGNAL(triggered()), this, SLOT(onAddEtiqueta()));
    connect(ui->actionEliminarTarea, SIGNAL(triggered()), this ,SLOT(onRemoveTarea()));
    connect(ui->actionEliminarCategoria, SIGNAL(triggered()), this, SLOT(onRemoveCategoria()));
    connect(ui->actionEliminarEtiqueta, SIGNAL(triggered()), this, SLOT(onRemoveEtiqueta()));
    connect(ui->tblTareas, SIGNAL(cellChanged(int,int)), this, SLOT(onTareasCellChanged(int,int)));
    connect(ui->tblCateg, SIGNAL(cellChanged(int,int)), this, SLOT(onCategoriasCellChanged(int,int)));
    connect(ui->tblEtiq, SIGNAL(cellChanged(int,int)), this, SLOT(onEtiquetasCellChanged(int,int)));
    connect(ui->comboCategoria, SIGNAL(currentIndexChanged(int)), this, SLOT(onLoadTareas()));

    addingTarea_ = false;
    addingCategoria_ = false;
    addingEtiqueta_ = false;

    CargarDatos();
    //Activamos el sorting en la tabla de categorias
    ui->tblCateg->setSortingEnabled(true);

    ui->comboCategoria->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::CargarDatos()
{
    //Cargamos las categorías
    QSqlQuery q = db_.exec("SELECT * "
                           "FROM categorias");


    while (q.next()){
        //Añadimos la categoria al combo y como userData su ID
        ui->comboCategoria->addItem(GetField(q,"name").toString(), GetField(q,"id").toInt());
        qDebug() << "Se aniade : " << GetField(q,"name").toString();
        //Añadimos la categoria a la tabla de categorias
        int rowNumber = ui->tblCateg->rowCount();
        ui->tblCateg->insertRow(rowNumber);
        QTableWidgetItem* item = new QTableWidgetItem(GetField(q, "name").toString());
        ui->tblCateg->setItem(rowNumber, 0, item);
    }

    //Cargamos las etiquetas

    QSqlQuery q2 = db_.exec("SELECT * "
                           "FROM etiquetas");


    while (q2.next()){
        //Añadimos la etiqueta al combo
        ui->comboEtiqueta->addItem(GetField(q2,"name").toString()/* GetField(q,"id").toInt()*/);
        qDebug() << "Se aniade : " << GetField(q2,"name").toString();
        //Añadimos la etiqueta a la tabla de etiquetas
        int rowNumber = ui->tblEtiq->rowCount();
        ui->tblEtiq->insertRow(rowNumber);
        QTableWidgetItem* item = new QTableWidgetItem(GetField(q2, "name").toString());
        ui->tblEtiq->setItem(rowNumber, 0, item);
    }

    datos_cargados = true;

}

void MainWindow::onAddTarea()
{
    addingTarea_ = true;


    ui->tblTareas->insertRow(ui->tblTareas->rowCount());
    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);
    ui->tblTareas->setItem(ui->tblTareas->rowCount()-1, 2, item);

    ui->tblTareas->setItem(ui->tblTareas->rowCount()-1, 0, new QTableWidgetItem(""));
    ui->tblTareas->setItem(ui->tblTareas->rowCount()-1, 1, new QTableWidgetItem(""));


    addingTarea_ = false;
}

void MainWindow::onAddCategoria()
{
    addingCategoria_ = true;

    ui->tblCateg->insertRow(ui->tblCateg->rowCount());
    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);
    ui->tblCateg->setItem(ui->tblCateg->rowCount()-1, 2, item);

    ui->tblCateg->setItem(ui->tblCateg->rowCount()-1, 0, new QTableWidgetItem(""));
    ui->tblCateg->setItem(ui->tblCateg->rowCount()-1, 1, new QTableWidgetItem(""));


    addingCategoria_ = false;
}

void MainWindow::onAddEtiqueta()
{
    addingEtiqueta_ = true;


    ui->tblEtiq->insertRow(ui->tblEtiq->rowCount());
    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);
    ui->tblEtiq->setItem(ui->tblEtiq->rowCount()-1, 2, item);

    ui->tblEtiq->setItem(ui->tblEtiq->rowCount()-1, 0, new QTableWidgetItem(""));
    ui->tblEtiq->setItem(ui->tblEtiq->rowCount()-1, 1, new QTableWidgetItem(""));


    addingEtiqueta_ = false;

}

void MainWindow::onRemoveTarea()
{
    qDebug () << "Borramos tarea";
    //Borrar todos las tareas seleccionadas.
    while(ui->tblTareas->selectedItems().size() > 0)
    {
        int id = ui->tblTareas->currentItem()->row()+ 1;
        qDebug () << "El id es " << id ;
        ui->tblTareas->removeRow(ui->tblTareas->currentRow());
        db_.exec("DELETE FROM tareas WHERE id = '" + QString("%1").arg(id) + "';");
    }
    qDebug() << "Terminamos de borrar tarea";
}

void MainWindow::onRemoveCategoria()
{
    while(ui->tblCateg->selectedItems().size() > 0)
    {
        QString name = ui->tblCateg->currentItem()->text();
        ui->tblCateg->removeRow(ui->tblCateg->currentRow());   
        db_.exec("DELETE FROM categorias WHERE name = '"+name+"';");
        ui->comboCategoria->removeItem(ui->tblCateg->currentRow()+1);
    }
}

void MainWindow::onRemoveEtiqueta()
{
    while(ui->tblEtiq->selectedItems().size() > 0)
    {
        QString name = ui->tblEtiq->currentItem()->text();
        ui->tblEtiq->removeRow(ui->tblEtiq->currentRow());
        db_.exec("DELETE FROM etiquetas WHERE name = '"+name+"';");
        ui->comboEtiqueta->removeItem(ui->tblEtiq->currentRow()+1);
    }
}

void MainWindow::onTareasCellChanged(int row, int column)
{
    if (addingTarea_ )
        return;

    addingTarea_ = true;

    int checked = (ui->tblTareas->item(row, 2)->checkState() == Qt::Checked);

    QSqlQuery query;

    if (ui->tblTareas->item(row, 0)->data(Qt::UserRole).isNull()) {
        query = db_.exec("INSERT INTO tareas (name, descripcion, date, done, id_categ) "
                 "VALUES ("+QString("'%1','%2','%3','%4','%5');" )\
                 .arg(ui->tblTareas->item(row, 0)->text())\
                 .arg(ui->txtTareaDescr->toPlainText())\
                 .arg(ui->tblTareas->item(row, 1)->text())\
                 .arg(checked)\
                 .arg(ui->comboCategoria->currentData().toInt()));
        ui->tblTareas->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    } else {
        query = db_.exec("UPDATE tareas "
                 "SET "+QString("name='%1',descripcion='%2',date='%3',done='%4',id_categ='%5' " )\
                 .arg(ui->tblTareas->item(row, 0)->text())\
                 .arg(ui->txtTareaDescr->toPlainText())\
                 .arg(ui->tblTareas->item(row, 1)->text())\
                 .arg(checked)\
                 .arg(ui->comboCategoria->currentData().toInt()) +
                 "WHERE id = " + ui->tblTareas->item(row, 0)->data(Qt::UserRole).toString() + ";");
    }

    qDebug() << query.lastQuery() ;

    addingTarea_ = false;
}

void MainWindow::onCategoriasCellChanged(int row, int column)
{
    qDebug() << "Cambiamos algo en una celda de categoria" ;
    if (addingCategoria_ || !datos_cargados)
        return;

    addingCategoria_ = true;


    QSqlQuery query;

    if (ui->tblCateg->item(row, 0)->data(Qt::UserRole).isNull()) {
        query = db_.exec("INSERT INTO categorias (name, descripcion) "
                 "VALUES ("+QString("'%1','%2');" )\
                 .arg(ui->tblCateg->item(row, 0)->text())\
                 .arg(ui->txtCategDescr->toPlainText()));
        ui->tblCateg->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    } else {
        query = db_.exec("UPDATE categorias "
                 "SET "+QString("name='%1',descripcion='%2'" )\
                 .arg(ui->tblCateg->item(row, 0)->text())\
                 .arg(ui->txtCategDescr->toPlainText()));
    }

    ui->comboCategoria->addItem(ui->tblCateg->item(row, 0)->text());
    qDebug() << "Ultima actualizacion : " << query.lastQuery() ;

    //ui->comboCategoria->setItemData(0,"pedro");

    addingCategoria_ = false;
}


void MainWindow::onEtiquetasCellChanged(int row, int column)
{
    qDebug() << "Cambiamos algo en una celda de Etiqueta" ;
    if (addingEtiqueta_ || !datos_cargados)
        return;

    addingEtiqueta_ = true;


    QSqlQuery query;

    if (ui->tblEtiq->item(row, 0)->data(Qt::UserRole).isNull()) {
        query = db_.exec("INSERT INTO etiquetas (name) "
                 "VALUES ("+QString("'%1');" )\
                 .arg(ui->tblEtiq->item(row, 0)->text()));
        ui->tblEtiq->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    } else {
        query = db_.exec("UPDATE etiquetas "
                 "SET "+QString("name='%1'")\
                 .arg(ui->tblEtiq->item(row, 0)->text()));
    }
    ui->comboEtiqueta->addItem(ui->tblEtiq->item(row, 0)->text());
    qDebug() << "Ultima actualizacion : " << query.lastQuery() ;


    addingEtiqueta_ = false;
}

void MainWindow::onLoadTareas()
{
    addingTarea_ = true;
    qDebug() << "Cargamos Tareas" ;
    while (ui->tblTareas->rowCount())
        ui->tblTareas->removeRow(0);

    //Obtenemos las tareas
    QSqlQuery q = db_.exec("SELECT * "
                 "FROM tareas "
                 "WHERE id_categ = " + ui->comboCategoria->currentData().toString());

    while (q.next()) {
        //Añadimos la tarea a la tabla de categorias
        int rowNumber = ui->tblTareas->rowCount();
        int id = GetField(q, "id").toInt();
        ui->tblTareas->insertRow(rowNumber);

        QTableWidgetItem* item = new QTableWidgetItem(GetField(q, "name").toString());
        item->setData(Qt::UserRole, id);
        ui->tblTareas->setItem(rowNumber, 0, item);

        ui->tblTareas->setItem(rowNumber, 1, new QTableWidgetItem(GetField(q, "date").toString()));

        item = new QTableWidgetItem("");
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        if (GetField(q, "done").toInt())
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
        ui->tblTareas->setItem(rowNumber, 2, item);
    }
    //Activamos el sorting en la tabla de categorias
    ui->tblTareas->setSortingEnabled(true);
    addingTarea_ = false;
}


