#ifndef MENSAJES_H
#define MENSAJES_H

#include <QDialog>
#include <QPushButton>

    class Mensajes : public QDialog {
    Q_OBJECT

public:
    explicit Mensajes(QWidget *parent = nullptr);
    QPushButton *reiniciarButton;
    QPushButton *salirButton;
};

#endif // MENSAJES_H
