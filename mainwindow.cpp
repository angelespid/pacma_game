#include "mainwindow.h"
#include "laberinto.h"
#include "jugador.h"
#include "enemigo.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    view->setSceneRect(0, 0, 640, 640); // Tamaño de la escena
    view->setFixedSize(640, 640);       // Tamaño de la vista
    this->setCentralWidget(view);
    view->setFocus(); // Permite capturar eventos de teclado
    QVector<Enemigo *> enemigos;
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
    // Crear y añadir enemigos
    // Crear y añadir el primer enemigo
    Enemigo *enemigo1 = new Enemigo(mapa, 160, 160, 80);
    scene->addItem(enemigo1);
    enemigos.append(enemigo1);

    // Crear y añadir el segundo enemigo
    Enemigo *enemigo2 = new Enemigo(mapa, 320, 320, 80);
    scene->addItem(enemigo2);
    enemigos.append(enemigo2);

    // Crear y añadir el tercer enemigo
    Enemigo *enemigo3 = new Enemigo(mapa, 480, 160, 80);
    scene->addItem(enemigo3);
    enemigos.append(enemigo3);

    // Establecer enfoque en la vista para recibir eventos de teclado
    view->setFocus();

    // Detectar colisiones entre el jugador y cada enemigo
    connect(enemigo1, &Enemigo::colisionDetectada, [=]() {
        qDebug() << "¡Colisión detectada entre el jugador y el enemigo 1!";
        jugador->reiniciarPosicion(); // O cualquier otra acción que quieras realizar
    });

    connect(enemigo2, &Enemigo::colisionDetectada, [=]() {
        qDebug() << "¡Colisión detectada entre el jugador y el enemigo 2!";
        jugador->reiniciarPosicion();
    });

    connect(enemigo3, &Enemigo::colisionDetectada, [=]() {
        qDebug() << "¡Colisión detectada entre el jugador y el enemigo 3!";
        jugador->reiniciarPosicion();
    });
}

MainWindow::~MainWindow() {
    delete laberinto;
    delete scene;
}

