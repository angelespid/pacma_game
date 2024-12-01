#include "laberinto.h"
#include <QDebug>

Laberinto::Laberinto(QGraphicsScene *scene, int cellSize) : scene(scene), cellSize(cellSize) {}

void Laberinto::dibujarLaberinto(const QVector<QVector<int>> &mapa) {
    for (int fila = 0; fila < mapa.size(); ++fila) {
        for (int columna = 0; columna < mapa[fila].size(); ++columna) {
            int tipo = mapa[fila][columna];
            Bloque *bloque = new Bloque(tipo, columna * cellSize, fila * cellSize, cellSize);

            if (tipo == 1) {
                qDebug() << "Pared creada en posición:" << columna * cellSize << "," << fila * cellSize;
            } else {
                qDebug() << "Camino creado en posición:" << columna * cellSize << "," << fila * cellSize;
            }

            scene->addItem(bloque); // Añadir bloque a la escena
        }
    }
}
