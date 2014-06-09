#pragma once

#include <QT>
#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QTimer>
#include <cmath>
#include <tori.h>

class Wand : public QWidget
{
    Q_OBJECT
public:
    Wand();
    ~Wand();
    void ziehen(QPainter& paint);
    void move(float dt);
    void reset();

    int getPosicaoXCanoUpI();
    int getPosicaoXCanoDownI();
    int getHeightCanoUpI();
    int getPosicaoYCanoDownI();
    int getPosicaoXCanoUpII();
    int getPosicaoXCanoDownII();
    int getHeightCanoUpII();
    int getPosicaoYCanoDownII();


private slots:
    void moveLeft();
    void callWandI();
    void callWandII();

private:
    int posicaoDx;
    int posicaoXCanoUpI, posicaoXCanoUpII, heightCanoUpI, heightCanoUpII;
    int posicaoYCanoDownI, posicaoYCanoDownII, posicaoXCanoDownI, posicaoXCanoDownII, heightCanoDownI, heightCanoDownII;
    QTimer *timerMove, *timerCallI, *timerCallII;
};
