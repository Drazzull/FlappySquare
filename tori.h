#pragma once

#include <QT>
#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QTimer>
#include <cmath>
#include <QMediaPlayer>

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
    int getPosicaoToriY();
    int getToriX();
    int getToriHeight();

    /* Estáticos */
    static bool morto;

public slots:
    void cair();

private:
    /* Normais */
    double fps;
    int posicaoToriY, posicaoDy, gravidade, toriHeight, toriWidth;
    int contadorPlanar;
    int rotation;
    QTimer *timer;

    void detectarColisaoChao();
    void detectarColisaoCanos();
};
