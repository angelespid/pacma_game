#include "mainwindow.h"
#include "laberinto.h"
#include "jugador.h"
#include "enemigo.h"
#include "punto.h"
#include <QPainter>
#include <QGraphicsTextItem>
#include <QMessageBox> // Incluir para el cuadro de diálogo
#include "mensajes.h"
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), laberinto(nullptr), puntaje(0),vidas(3) {

    // Configuración de la escena y la vista
    view = new QGraphicsView(scene, this);
    view->setSceneRect(0, 0, 640, 640);
    view->setFixedSize(640, 640);
    this->setCentralWidget(view);

    // Mapa local
    QVector<QVector<int>> mapa = {
                                  {1, 1, 1, 1, 1, 1, 1, 1},
                                  {1, 0, 0, 0, 0, 0, 0, 1},
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

    for (Enemigo *enemigo : enemigos) {
        connect(enemigo, &Enemigo::colisionDetectada, this, &MainWindow::manejarColisionConEnemigo);
    }

    connect(jugador, &Jugador::puntoRecolectado, [this]() {
        puntaje++;
        textoPuntaje->setPlainText(QString("Puntaje: %1").arg(puntaje));
        qDebug() << "Puntaje actualizado:" << puntaje;
    });
    connect(jugador, &Jugador::vidasActualizadas, [this](int nuevasVidas) {
        textoVidas->setPlainText(QString("Vidas: %1").arg(nuevasVidas));
        qDebug() << "Vidas actualizadas desde señal:" << nuevasVidas;
    });

    connect(jugador, &Jugador::gameOver, [this]() {
        qDebug() << "¡Game Over!";
        textoVidas->setPlainText("Vidas: 0");

        QGraphicsTextItem *gameOverText = new QGraphicsTextItem("GAME OVER");
        gameOverText->setDefaultTextColor(Qt::red);
        gameOverText->setFont(QFont("Arial", 36));
        gameOverText->setPos(scene->width() / 2 - 100, scene->height() / 2 - 50);
        scene->addItem(gameOverText);
        connect(jugador, &Jugador::gameOver, this, &MainWindow::mostrarGameOver);

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
//Menu para reiniciar el juego o fin del juego

void MainWindow::mostrarGameOver() {
    QDialog dialog(this);
    dialog.setWindowTitle("Game Over");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(new QLabel("Has perdido todas tus vidas. ¿Qué deseas hacer?"));

    QPushButton *reiniciarButton = new QPushButton("Reiniciar");
    QPushButton *salirButton = new QPushButton("Salir");

    layout->addWidget(reiniciarButton);
    layout->addWidget(salirButton);

    connect(reiniciarButton, &QPushButton::clicked, [&dialog, this]() {
        dialog.accept();
        reiniciarJuego();
    });
    connect(salirButton, &QPushButton::clicked, [&dialog, this]() {
        dialog.reject();
        close();
    });

    dialog.exec();
    connect(jugador, &Jugador::puntoRecolectado, [this]() {
        puntaje++;
        textoPuntaje->setPlainText(QString("Puntaje: %1").arg(puntaje));
        qDebug() << "Puntaje actualizado:" << puntaje;

        verificarVictoria(); // Llamar para verificar si quedan puntos
    });


}

void MainWindow::manejarColisionConEnemigo() {
    qDebug() << "Colisión detectada. Vidas actuales:" << vidas;
    vidas--;
    qDebug() << "Vidas después de la colisión:" << vidas;

    // Actualizar el texto de vidas en la interfaz
    textoVidas->setPlainText(QString("Vidas: %1").arg(vidas));

    if (vidas <= 0) {
        qDebug() << "¡Game Over!";
        mostrarGameOver();
    } else {
        jugador->reiniciarPosicion();
    }
}


void MainWindow::reiniciarJuego() {
    qDebug() << "Reiniciando juego...";

    // Reiniciar puntaje
    puntaje = 0;
    textoPuntaje->setPlainText(QString("Puntaje: %1").arg(puntaje));

    // Reiniciar vidas
    vidas = 3;
    textoVidas->setPlainText(QString("Vidas: %1").arg(vidas));

    // Restablecer posición del jugador
    QPointF jugadorPosInicial(80, 80); // Asume que esta es la posición inicial
    jugador->setPos(jugadorPosInicial);

    // Verificar y reubicar enemigos si están en la posición del jugador
    for (Enemigo *enemigo : enemigos) {
        QPointF nuevaPos;
        do {
            // Generar una nueva posición aleatoria dentro del rango válido del laberinto
            int nuevoX = (rand() % 7 + 1) * 80; // Ajustar los límites
            int nuevoY = (rand() % 7 + 1) * 80;
            nuevaPos = QPointF(nuevoX, nuevoY);
        } while (nuevaPos == jugadorPosInicial); // Repetir si coincide con el jugador

        enemigo->setPos(nuevaPos);
        qDebug() << "Enemigo reubicado en:" << nuevaPos;
    }

    // Eliminar todos los puntos y volver a colocarlos
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        Punto *punto = dynamic_cast<Punto *>(item);
        if (punto) {
            scene->removeItem(punto);
            delete punto;
        }
    }
    colocarPuntos();

    // Habilitar nuevamente los controles
    view->setEnabled(true);

    qDebug() << "Juego reiniciado.";
}
void MainWindow::verificarVictoria() {
    // Iterar sobre todos los elementos en la escena y verificar si quedan puntos
    QList<QGraphicsItem *> items = scene->items();
    bool hayPuntosRestantes = false;

    for (QGraphicsItem *item : items) {
        Punto *punto = dynamic_cast<Punto *>(item); // Verificar si el objeto es de tipo Punto
        if (punto) {
            hayPuntosRestantes = true; // Si encontramos al menos un punto, establecemos la bandera
            break; // No necesitamos buscar más, basta con encontrar un punto
        }
    }

    // Si no hay puntos restantes, se considera victoria
    if (!hayPuntosRestantes) {
        qDebug() << "¡Victoria! Todos los puntos recolectados.";
        QMessageBox::information(this, "¡Victoria!", "¡Has recolectado todos los puntos y ganado el juego!");
        reiniciarJuego(); // Reinicia el juego tras la victoria
    }
}

/*
void MainWindow::reiniciarJuego() {
    qDebug() << "Reiniciando juego...";

    // Reiniciar puntaje
    puntaje = 0;
    textoPuntaje->setPlainText(QString("Puntaje: %1").arg(puntaje));

    // Reiniciar vidas
    jugador->inicializarVidas(3);
    textoVidas->setPlainText(QString("Vidas: %1").arg(3));

    // Restablecer posición del jugador
    jugador->reiniciarPosicion();

    // Eliminar todos los puntos y volver a colocarlos
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        Punto *punto = dynamic_cast<Punto *>(item);


        if (punto) {
            scene->removeItem(punto);
            delete punto;
        }
    }
    colocarPuntos();

    // Restablecer posición de los enemigos (si aplica)
    for (Enemigo *enemigo : enemigos) {
        enemigo->reiniciarPosicion(); // Asegúrate de implementar un método `reiniciarPosicion` en la clase `Enemigo`.
    }

    // Volver a habilitar la vista
    view->setEnabled(true);

    qDebug() << "Juego reiniciado.";
}
*/
MainWindow::~MainWindow() {
    delete laberinto;
    delete scene;
    delete jugador; // Libera la memoria del jugador
}
