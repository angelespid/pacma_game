#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QObject>
#include <QVector>

class Jugador : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

public:
    explicit Jugador(const QVector<QVector<int>> &mapa, int cellSize, QGraphicsItem *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override; // Manejar teclas presionadas

     // Actualizar posición gráfica según posición lógica

private:
    QVector<QVector<int>> mapa; // Mapa lógico del laberinto (0: camino, 1: pared)
    int cellSize;               // Tamaño de cada celda en píxeles
    int fila;                   // Posición lógica (fila) del jugador
    int columna;                // Posición lógica (columna) del jugador
    void actualizarPosicion();
};

#endif // JUGADOR_H
