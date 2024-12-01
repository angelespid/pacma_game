#include "mainwindow.h"
#include "laberinto.h"
#include "jugador.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    view->setSceneRect(0, 0, 640, 640); // Tamaño de la escena
    view->setFixedSize(640, 640);       // Tamaño de la vista
    this->setCentralWidget(view);
    view->setFocus(); // Permite capturar eventos de teclado
    QVector<QVector<int>> mapa = {
                                  {1, 1, 1, 1, 1, 1, 1, 1},
                                  {1, 0, 1, 0, 0, 0, 0, 1},
                                  {1, 0, 1, 1, 1, 1, 0, 1},
                                  {1, 0, 0, 0, 0, 1, 0, 1},
                                  {1, 0, 1, 0, 0, 1, 0, 1},
                                  {1, 0, 1, 1, 0, 1, 0, 1},
                                  {1, 0, 0, 0, 0, 0, 0, 1},
                                  {1, 1, 1, 1, 1, 1, 1, 1},
                                  };

    laberinto = new Laberinto(scene, 80); // Tamaño de cada celda: 80x80 píxeles

    laberinto->dibujarLaberinto(mapa);    // Generar el laberinto
    // Crear el jugador
    Jugador *jugador = new Jugador(mapa, 80);
    scene->addItem(jugador);

    // Establecer enfoque en la vista para recibir eventos de teclado
    view->setFocus();
}

MainWindow::~MainWindow() {
    delete laberinto;
    delete scene;
}

