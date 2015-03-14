#ifndef CREADORTAREAS_H
#define CREADORTAREAS_H

#include <QMainWindow>

namespace Ui {
class CreadorTareas;
}

class CreadorTareas : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreadorTareas(QWidget *parent = 0);
    ~CreadorTareas();

private:
    Ui::CreadorTareas *ui;
private slots:
    void onCrear();

};

#endif // CREADORTAREAS_H
