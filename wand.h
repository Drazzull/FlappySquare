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

private slots:
    void moveLeft();
    void callWandI();
    void callWandII();

private:
    QVector<QPoint> posicoesWandUp, posicoesWandDown;
    int posicaoDx, falhaEntreCanos;
    int posicaoYCanoUpI, posicaoYCanoUpII, posicaoXCanoUpI, posicaoXCanoUpII;
    int posicaoYCanoDownI, posicaoYCanoDownII, posicaoXCanoDownI, posicaoXCanoDownII;
    bool showWand;
    QTimer *timerMove, *timerCallI, *timerCallII;
};
