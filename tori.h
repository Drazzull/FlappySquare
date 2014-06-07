#pragma once

#include <QT>
#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QTimer>
#include <cmath>

class Tori : public QWidget
{
    Q_OBJECT
public:
    /* Normais */
    Tori();
    ~Tori();
    void ziehen(QPainter& paint);
    void flapUp();
    void move(float dt);
    void reset();

    /* Estáticos */
    static bool morto;

public slots:
    void cair();

private:
    /* Normais */
    double fps;
    int posicaoToriY, posicaoDy, toriSize, gravidade;
    int contadorPlanar;
    QTimer* timer;

    void detectarColisaoChao();
};
