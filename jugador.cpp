#include "jugador.h"
#include <QDebug>
#include <QPainter>
#include "enemigo.h"
#include <QTimer>
#include "punto.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>


Jugador::Jugador(const QVector<QVector<int>> &mapa, int cellSize, QGraphicsItem *parent)
    : QObject(), QGraphicsEllipseItem(parent), mapa(mapa), cellSize(cellSize), velocidad(5) {
    setRect(0, 0, cellSize, cellSize);
    setBrush(Qt::yellow);

    // Configurar al jugador como enfocable
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    // Posición inicial lógica
    fila = 1;
    columna = 1;
    actualizarPosicion();

    // Inicializar teclas como no presionadas
    for (int i = 0; i < 4; ++i) {
        teclas[i] = false;
    }

    // Configurar temporizador para el movimiento continuo
    QTimer *timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Jugador::mover);
    timerMovimiento->start(50); // Ajustar velocidad de actualización
}

void Jugador::actualizarPosicion() {
    setPos(columna * cellSize, fila * cellSize);
    qDebug() << "Jugador movido a posición gráfica:" << pos();

    // Si el jugador es invulnerable, no procesar colisiones
    if (invulnerable) {
        qDebug() << "Jugador es invulnerable. Ignorando colisiones.";
        return;
    }

    // Comprobar colisiones con enemigos
    QList<QGraphicsItem *> itemsColisionados = collidingItems();
    for (QGraphicsItem *item : itemsColisionados) {
        Enemigo *enemigo = dynamic_cast<Enemigo *>(item);
        if (enemigo) {
            qDebug() << "¡Colisión con un enemigo!";
            emit colisionConEnemigo();
            activarInvulnerabilidad(); // Activar invulnerabilidad tras la colisión
            return;
        }
    }
}


void Jugador::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Tecla presionada:" << event->key();

    int nuevaFila = fila;
    int nuevaColumna = columna;

    switch (event->key()) {
    case Qt::Key_W: nuevaFila--; break;
    case Qt::Key_S: nuevaFila++; break;
    case Qt::Key_A: nuevaColumna--; break;
    case Qt::Key_D: nuevaColumna++; break;
    default:
        qDebug() << "Tecla no válida.";
        return;
    }

    qDebug() << "Nueva posición tentativa:" << nuevaFila << nuevaColumna;

    if (nuevaFila >= 0 && nuevaFila < mapa.size() &&
        nuevaColumna >= 0 && nuevaColumna < mapa[0].size()) {
        if (mapa[nuevaFila][nuevaColumna] == 0) {
            qDebug() << "Movimiento permitido a:" << nuevaFila << nuevaColumna;
            fila = nuevaFila;
            columna = nuevaColumna;
            actualizarPosicion();
        } else {
            qDebug() << "Movimiento bloqueado: es una pared.";
        }
    } else {
        qDebug() << "Movimiento fuera de los límites.";
    }
}

void Jugador::reiniciarPosicion() {
    fila = 1;       // Cambia a la posición inicial lógica
    columna = 1;    // Cambia a la posición inicial lógica
    actualizarPosicion(); // Mueve gráficamente al jugador
    qDebug() << "Jugador reiniciado a la posición inicial.";
}

void Jugador::activarInvulnerabilidad() {
    invulnerable = true; // Activar invulnerabilidad
    qDebug() << "Jugador es invulnerable temporalmente.";

    // Crear y configurar el temporizador
    if (!timerInvulnerabilidad) {
        timerInvulnerabilidad = new QTimer(this);
        connect(timerInvulnerabilidad, &QTimer::timeout, [=]() {
            invulnerable = false; // Desactivar invulnerabilidad
            timerInvulnerabilidad->stop(); // Detener el temporizador
            qDebug() << "Jugador ya no es invulnerable.";
        });
    }
    timerInvulnerabilidad->start(1000); // 1 segundo de invulnerabilidad
}

void Jugador::mover() {
    QPointF movimiento(0, 0);

    if (teclas[0]) movimiento.setY(-cellSize); // Arriba (W)
    if (teclas[1]) movimiento.setX(-cellSize); // Izquierda (A)
    if (teclas[2]) movimiento.setY(cellSize);  // Abajo (S)
    if (teclas[3]) movimiento.setX(cellSize);  // Derecha (D)

    // Validar si el movimiento es posible
    if (!puedeMoverse(QPointF(movimiento.x(), 0))) movimiento.setX(0);
    if (!puedeMoverse(QPointF(0, movimiento.y()))) movimiento.setY(0);

    // Actualizar posición lógica y gráfica
    if (movimiento != QPointF(0, 0)) {
        setPos(pos() + movimiento);
        columna += movimiento.x() / cellSize;
        fila += movimiento.y() / cellSize;
        actualizarPosicion();
    }

    // Verificar colisiones con puntos
    QList<QGraphicsItem *> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Punto *punto = dynamic_cast<Punto *>(item);
        if (punto) {
            emit puntoRecolectado();
            scene()->removeItem(punto);
            delete punto;
        }
    }
}

bool Jugador::puedeMoverse(const QPointF &delta) {
    QPointF nuevaPos = pos() + delta;
    QRectF nuevaRect(nuevaPos, rect().size());

    for (QGraphicsItem *item : scene()->items(nuevaRect)) {
        if (item == this) continue;
        if (dynamic_cast<QGraphicsRectItem *>(item)) return false;
    }
    return true;
}
