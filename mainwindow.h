#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "laberinto.h"
#include "enemigo.h"
#include "punto.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void colocarPuntos();
     QGraphicsTextItem *textoPuntaje;
    ~MainWindow();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Laberinto *laberinto;
    int puntaje;
};

#endif // MAINWINDOW_H
