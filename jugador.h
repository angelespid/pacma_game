#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>
#include <QList>

class Jugador : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

public:
    explicit Jugador(const QVector<QVector<int>> &mapa, int cellSize, QGraphicsItem *parent = nullptr);

    //void keyReleaseEvent(QKeyEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override; // Manejar teclas presionadas
     void reiniciarPosicion();
     // Actualizar posición gráfica según posición lógica
    void activarInvulnerabilidad(); // Activar estado invulnerable
private:
    QVector<QVector<int>> mapa; // Mapa lógico del laberinto (0: camino, 1: pared)
    int cellSize;               // Tamaño de cada celda en píxeles
    int fila;                   // Posición lógica (fila) del jugador
    int columna;                // Posición lógica (columna) del jugador
    void actualizarPosicion();
    bool puedeMoverse(const QPointF &delta);
    bool teclas[4];
    int velocidad;
    bool invulnerable; // Controla si el jugador puede ser colisionado
    QTimer *timerInvulnerabilidad; // Temporizador para gestionar la invulnerabilidad
     void mover();
signals:
    void colisionConEnemigo();
    void puntoRecolectado();
};

#endif // JUGADOR_H
