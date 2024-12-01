#ifndef LABERINTO_H
#define LABERINTO_H

#include <QGraphicsScene>
#include <QVector>
#include "bloque.h"

class Laberinto {
public:
     Laberinto(QGraphicsScene *scene, int cellSize);
    void dibujarLaberinto(const QVector<QVector<int>> &mapa); // Genera el laberinto
    const QVector<QVector<int>>& getMapa() const; // Sin calificación 'Laberinto::'

private:
    QGraphicsScene *scene; // Escena para dibujar los elementos
    int cellSize;          // Tamaño de cada celda en píxeles
    QVector<QVector<int>> mapa; // El mapa se almacena aquí


};

#endif // LABERINTO_H
