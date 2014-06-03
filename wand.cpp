#include "wand.h"

Wand::Wand()
{
    this->timer = new QTimer(this);
    this->timer->start(60);

    QObject::connect(this->timer, SIGNAL(timeout()),
                     this, SLOT(moveLeft()));
}

Wand::~Wand()
{

}

void Wand::callWand(bool started, bool morto)
{
    if (!started)
    {
        return;
    }

    /*if (morto)
    {
        return;
    }*/

    this->showWand = true;

    // A falha deve ficar entre 100 e 450
    this->falhaEntreCanos = rand() % 450 + 100;

    // Redimensiona o cano de cima
    this->posicoesWandUp.clear();
    this->posicoesWandUp.append(QPoint(380, -10));
    this->posicoesWandUp.append(QPoint(380, (this->falhaEntreCanos - 90)));
    this->posicoesWandUp.append(QPoint(400, (this->falhaEntreCanos - 80)));
    this->posicoesWandUp.append(QPoint(400, (this->falhaEntreCanos - 50)));
    this->posicoesWandUp.append(QPoint(330, (this->falhaEntreCanos - 50)));
    this->posicoesWandUp.append(QPoint(330, (this->falhaEntreCanos - 80)));
    this->posicoesWandUp.append(QPoint(350, (this->falhaEntreCanos - 90)));
    this->posicoesWandUp.append(QPoint(350, -10));

    // Redimensiona o cano de baixo
    this->posicoesWandDown.clear();
    this->posicoesWandDown.append(QPoint(380, 700));
    this->posicoesWandDown.append(QPoint(380, (this->falhaEntreCanos + 110)));
    this->posicoesWandDown.append(QPoint(400, (this->falhaEntreCanos + 100)));
    this->posicoesWandDown.append(QPoint(400, (this->falhaEntreCanos + 70)));
    this->posicoesWandDown.append(QPoint(330, (this->falhaEntreCanos + 70)));
    this->posicoesWandDown.append(QPoint(330, (this->falhaEntreCanos + 100)));
    this->posicoesWandDown.append(QPoint(350, (this->falhaEntreCanos + 110)));
    this->posicoesWandDown.append(QPoint(350, 700));
}

void Wand::move(float dt)
{
    if (!this->showWand)
    {
        return;
    }

    /* Atualiza a posição da parede de cima, sempre para a esquerda */
    for(int i = 0; i < this->posicoesWandUp.size(); i++)
    {
        this->posicoesWandUp[i].setX(this->posicoesWandUp[i].x() + std::floor((this->posicaoDx * dt * 60) / 1000));
    }

    /* Atualiza a posição da parede de baixo, sempre para a esquerda */
    for(int i = 0; i < this->posicoesWandDown.size(); i++)
    {
        this->posicoesWandDown[i].setX(this->posicoesWandDown[i].x() + std::floor((this->posicaoDx * dt * 60) / 1000));
    }

    // Zera a variável para que o mesmo se mova somente quando necessário
    this->posicaoDx = 0;
}

void Wand::moveLeft()
{
    if (!this->showWand)
    {
        return;
    }

    this->posicaoDx = -10;
}

void Wand::ziehen(QPainter &paint)
{
    QPen caneta;
    caneta.setBrush(Qt::green);
    caneta.setWidth(4);
    paint.setPen(caneta);
    paint.drawPolyline(this->posicoesWandUp);
    paint.drawPolyline(this->posicoesWandDown);
}
