#include "enemigo.h"
#include <QBrush>
#include <QDebug>
#include "jugador.h"

Enemigo::Enemigo(const QVector<QVector<int>> &mapa, int x, int y, int cellSize, QGraphicsItem *parent)
    : QObject(), QGraphicsPolygonItem(parent), mapa(mapa), cellSize(cellSize), dx(cellSize), dy(0) {
    // Crear un triángulo para representar al enemigo
    QPolygonF triangle;
    triangle << QPointF(0, 0) << QPointF(cellSize, cellSize / 2) << QPointF(0, cellSize);
    setPolygon(triangle);

    setBrush(QBrush(Qt::red)); // Color rojo para el enemigo

    // Establecer la posición inicial
    setPos(x, y);

    // Configurar el timer para el patrullaje
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemigo::patrullar);
    timer->start(500); // Actualizar cada 500 ms
}




void Enemigo::patrullar() {
    // Calcular la nueva posición lógica
    int nuevaColumna = (x() + dx) / cellSize;
    int nuevaFila = (y() + dy) / cellSize;

    // Comprobar si la nueva posición es válida en el mapa lógico
    if (nuevaFila >= 0 && nuevaFila < mapa.size() &&
        nuevaColumna >= 0 && nuevaColumna < mapa[0].size() &&
        mapa[nuevaFila][nuevaColumna] == 0) {
        // Si es un camino, moverse
        setPos(x() + dx, y() + dy);
    } else {
        // Si es un muro, cambiar de dirección aleatoriamente
        qDebug() << "Enemigo encontró un muro. Cambiando dirección.";

        int randomDirection = rand() % 4; // Generar una nueva dirección aleatoria
        switch (randomDirection) {
        case 0: dx = 0; dy = -cellSize; break; // Arriba
        case 1: dx = 0; dy = cellSize; break;  // Abajo
        case 2: dx = -cellSize; dy = 0; break; // Izquierda
        case 3: dx = cellSize; dy = 0; break;  // Derecha
        }
    }

    // Verificar colisiones con el jugador
    QList<QGraphicsItem *> itemsColisionados = collidingItems();
    for (QGraphicsItem *item : itemsColisionados) {
        Jugador *jugador = dynamic_cast<Jugador *>(item);
        if (jugador) {
            qDebug() << "¡Enemigo colisionó con el jugador!";
            emit colisionDetectada(); // Emitir señal para manejar la colisión
            return; // Detener el patrullaje para este ciclo
        }
    }

    qDebug() << "Enemigo movido a posición:" << pos();
}
