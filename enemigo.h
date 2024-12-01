#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPolygonItem>
#include <QObject>
#include <QTimer>

class Enemigo : public QObject, public QGraphicsPolygonItem {
    Q_OBJECT

public:
    explicit Enemigo(const QVector<QVector<int>> &mapa, int x, int y, int cellSize, QGraphicsItem *parent = nullptr);


    void patrullar(); // Movimiento básico del enemigo

private:
     QVector<QVector<int>> mapa;
    int cellSize;      // Tamaño de cada celda
    int dx, dy;        // Dirección del movimiento
    QTimer *timer;     // Timer para actualizar el movimiento

signals:
    void colisionDetectada(); // Señal para manejar colisiones
};

#endif // ENEMIGO_H
