#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbconnection.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onAddTarea();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
};

#endif // MAINWINDOW_H
