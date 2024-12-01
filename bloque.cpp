#include "bloque.h"

Bloque::Bloque(int tipo, int x, int y, int size) : tipo(tipo) {
    setRect(x, y, size, size); // Definir la posición y tamaño del bloque

    if (tipo == 1) {
        setBrush(QBrush(Qt::blue)); // Pared (azul)
    } else {
        setBrush(QBrush(Qt::white)); // Camino (blanco)
    }
}

int Bloque::getTipo() const {
    return tipo;
}
