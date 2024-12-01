#include "mainwindow.h"
#include "laberinto.h"
#include "jugador.h"
#include "enemigo.h"
#include "punto.h"
#include <QPainter>
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), laberinto(nullptr), puntaje(0) {

    // Configuración de la escena y la vista
    view = new QGraphicsView(scene, this);
    view->setSceneRect(0, 0, 640, 640);
    view->setFixedSize(640, 640);
    this->setCentralWidget(view);

    // Mapa local
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

    // Crear el laberinto
    laberinto = new Laberinto(scene, 80);
    laberinto->dibujarLaberinto(mapa);

    // Colocar puntos (galletas)
    colocarPuntos();

    // Crear el texto del puntaje
    textoPuntaje = new QGraphicsTextItem(QString("Puntaje: %1").arg(puntaje));
    textoPuntaje->setDefaultTextColor(Qt::white);
    textoPuntaje->setFont(QFont("Arial", 16));
    textoPuntaje->setZValue(1);
    scene->addItem(textoPuntaje);
    // Mostrar el número de vidas
    textoVidas = new QGraphicsTextItem(QString("Vidas: %1").arg(3));
    textoVidas->setDefaultTextColor(Qt::white);
    textoVidas->setFont(QFont("Arial", 16));
    textoVidas->setPos(0, 20); // Posición debajo del puntaje
    scene->addItem(textoVidas);

    // Crear el jugador
    jugador = new Jugador(mapa, 80);
    scene->addItem(jugador);
    jugador->inicializarVidas(3); // Inicializar las vidas del jugador

    // Crear y añadir enemigos
    QVector<Enemigo *> enemigos;
    Enemigo *enemigo1 = new Enemigo(mapa, 160, 160, 80);
    scene->addItem(enemigo1);
    enemigos.append(enemigo1);

    Enemigo *enemigo2 = new Enemigo(mapa, 320, 320, 80);
    scene->addItem(enemigo2);
    enemigos.append(enemigo2);

    Enemigo *enemigo3 = new Enemigo(mapa, 480, 160, 80);
    scene->addItem(enemigo3);
    enemigos.append(enemigo3);

    // Conectar señales
    connect(enemigo1, &Enemigo::colisionDetectada, [=]() {
        qDebug() << "¡Colisión detectada entre el jugador y el enemigo 1!";
        jugador->reiniciarPosicion();
    });

    connect(enemigo2, &Enemigo::colisionDetectada, [=]() {
        qDebug() << "¡Colisión detectada entre el jugador y el enemigo 2!";
        jugador->reiniciarPosicion();
    });

    connect(enemigo3, &Enemigo::colisionDetectada, [=]() {
        qDebug() << "¡Colisión detectada entre el jugador y el enemigo 3!";
        jugador->reiniciarPosicion();
    });

    connect(jugador, &Jugador::puntoRecolectado, [this]() {
        puntaje++;
        textoPuntaje->setPlainText(QString("Puntaje: %1").arg(puntaje));
        qDebug() << "Puntaje actualizado:" << puntaje;
    });
    connect(jugador, &Jugador::vidasActualizadas, [this](int vidas) {
        textoVidas->setPlainText(QString("Vidas: %1").arg(vidas));
        qDebug() << "Vidas actualizadas:" << vidas;
    });
    connect(jugador, &Jugador::gameOver, [this]() {
        qDebug() << "¡Game Over!";
        textoVidas->setPlainText("Vidas: 0");

        QGraphicsTextItem *gameOverText = new QGraphicsTextItem("GAME OVER");
        gameOverText->setDefaultTextColor(Qt::red);
        gameOverText->setFont(QFont("Arial", 36));
        gameOverText->setPos(scene->width() / 2 - 100, scene->height() / 2 - 50);
        scene->addItem(gameOverText);

        // Deshabilitar eventos de teclado
        view->setEnabled(false);
    });


    // Configurar foco
    view->setFocus();
}

void MainWindow::colocarPuntos() {
    QVector<QVector<int>> mapa = laberinto->getMapa(); // Asegúrate de acceder al mapa desde `laberinto`

    for (int fila = 0; fila < mapa.size(); ++fila) {
        for (int columna = 0; columna < mapa[fila].size(); ++columna) {
            if (mapa[fila][columna] == 0) { // Si la celda está vacía
                Punto *punto = new Punto(80); // Tamaño de la celda
                punto->setPos(columna * 80 + 80 / 2 - punto->rect().width() / 2,
                              fila * 80 + 80 / 2 - punto->rect().height() / 2);
                scene->addItem(punto);
            }
        }
    }
}

MainWindow::~MainWindow() {
    delete laberinto;
    delete scene;
    delete jugador; // Libera la memoria del jugador
}
