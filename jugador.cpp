#include "jugador.h"
#include <QDebug>
#include <QPainter>

void Jugador::actualizarPosicion() {
    setPos(columna * cellSize, fila * cellSize);
    qDebug() << "Jugador movido a posición lógica:" << fila << columna
             << "y posición gráfica:" << pos();}


Jugador::Jugador(const QVector<QVector<int>> &mapa, int cellSize, QGraphicsItem *parent)
    : QObject(), QGraphicsEllipseItem(parent), mapa(mapa), cellSize(cellSize) {
    // Definir tamaño del jugador como una celda
    setRect(0, 0, cellSize, cellSize);

    // Crear un pincel amarillo para el jugador
    setBrush(QBrush(QColor(Qt::yellow)));
    // Configurar al jugador como enfocable
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    // Posición inicial en el mapa lógico (debe coincidir con una celda libre)
    fila = 1;
    columna = 1;
    actualizarPosicion();
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
