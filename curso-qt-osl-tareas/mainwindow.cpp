#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Setup database
    ConecToDb(db_, "tareas");

    db_.exec("CREATE TABLE IF NOT EXISTS tareas ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT,"
              "date TEXT"
              ");");
}

MainWindow::~MainWindow()
{

}
