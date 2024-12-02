#include "mensajes.h"
#include <QVBoxLayout>
#include <QLabel>

Mensajes::Mensajes(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Game Over");

    // Configurar botones
    reiniciarButton = new QPushButton("Reiniciar", this);
    salirButton = new QPushButton("Salir", this);

    // Layout
    QDialog dialog(this);
    dialog.setWindowTitle("Game Over");
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("¿Qué deseas hacer?"));
    layout->addWidget(reiniciarButton);
    layout->addWidget(salirButton);


    dialog.setLayout(layout);
    dialog.exec();
}
