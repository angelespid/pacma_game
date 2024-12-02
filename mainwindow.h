#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "laberinto.h"
#include "enemigo.h"
#include "punto.h"
#include "jugador.h"
#include<QLabel>
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void colocarPuntos();
     QGraphicsTextItem *textoPuntaje;
    ~MainWindow();
 private slots: // Usa slots aquí para integrarlo con Qt si necesitas que reaccione a señales
     void manejarColisionConEnemigo();
     void verificarVictoria();
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Laberinto *laberinto;
    int puntaje;
    QGraphicsTextItem *textoVidas; // Texto para mostrar las vidas restantes
    Jugador *jugador; // Variable miembro para el jugador
    void mostrarGameOver();
    void iniciarJuego();
    void reiniciarJuego();
    QVector<Enemigo *> enemigos;
    int vidas;
    int inicioX, inicioY;  // Coordenadas iniciales del jugador
    QLabel *labelVidas;    // Etiqueta para mostrar las vidas
    QLabel *labelPuntaje;  // Etiqueta para mostrar el puntaje

};

#endif // MAINWINDOW_H
