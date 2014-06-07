#include <wand.h>
#include <frmjogo.h>

void Wand::reset()
{
    this->timerMove->stop();
    this->timerMove->start(60);
    this->timerCallI->stop();
    this->timerCallII->stop();
    this->timerCallI->start(60);
    this->timerCallII->start(60);
    this->posicaoDx = 0;
    this->showWand = false;
    this->posicoesWandUp.clear();
    this->posicoesWandDown.clear();
}

Wand::Wand()
{
    this->timerMove = new QTimer(this);
    this->timerCallI = new QTimer(this);
    this->timerCallII = new QTimer(this);
    this->reset();

    QObject::connect(this->timerCallI, SIGNAL(timeout()),
                     this, SLOT(callWandI()));

    QObject::connect(this->timerCallII, SIGNAL(timeout()),
                     this, SLOT(callWandII()));

    QObject::connect(this->timerMove, SIGNAL(timeout()),
                     this, SLOT(moveLeft()));
}

Wand::~Wand()
{

}

void Wand::callWandI()
{
    // Gera um número de tempo aleatório entre 5s e 7s para gerar as paredes
    int tempo = rand() % 3000 + 5000;
    this->timerCallI->stop();
    this->timerCallI->start(tempo);

    if (!FrmJogo::started)
    {
        return;
    }

    if (Tori::morto)
    {
        return;
    }

    this->showWand = true;

    // A falha deve ficar entre 150 e 450
    this->falhaEntreCanos = rand() % 300 + 150;

    // Limpa os canos
    this->posicoesWandUp.clear();
    this->posicoesWandDown.clear();

    // Redimensiona o cano de cima
    this->posicoesWandUp.append(QPoint(480, -10));
    this->posicoesWandUp.append(QPoint(480, (this->falhaEntreCanos - 100)));
    this->posicoesWandUp.append(QPoint(490, (this->falhaEntreCanos - 90)));
    this->posicoesWandUp.append(QPoint(490, (this->falhaEntreCanos - 60)));
    this->posicoesWandUp.append(QPoint(430, (this->falhaEntreCanos - 60)));
    this->posicoesWandUp.append(QPoint(430, (this->falhaEntreCanos - 90)));
    this->posicoesWandUp.append(QPoint(440, (this->falhaEntreCanos - 100)));
    this->posicoesWandUp.append(QPoint(440, -10));


    // Redimensiona o cano de baixo
    this->posicoesWandDown.append(QPoint(480, 700));
    this->posicoesWandDown.append(QPoint(480, (this->falhaEntreCanos + 120)));
    this->posicoesWandDown.append(QPoint(490, (this->falhaEntreCanos + 110)));
    this->posicoesWandDown.append(QPoint(490, (this->falhaEntreCanos + 80)));
    this->posicoesWandDown.append(QPoint(430, (this->falhaEntreCanos + 80)));
    this->posicoesWandDown.append(QPoint(430, (this->falhaEntreCanos + 110)));
    this->posicoesWandDown.append(QPoint(440, (this->falhaEntreCanos + 120)));
    this->posicoesWandDown.append(QPoint(440, 700));
}

void Wand::callWandII()
{
    // Gera um número de tempo aleatório entre 5s e 7s para gerar as paredes
    int tempo = rand() % 3000 + 5000;
    this->timerCallII->stop();
    this->timerCallII->start(tempo);

    if (!FrmJogo::started)
    {
        return;
    }

    if (Tori::morto)
    {
        return;
    }
}

void Wand::move(float dt)
{
    if (!this->showWand)
    {
        return;
    }

    if (Tori::morto)
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

    if (Tori::morto)
    {
        return;
    }

    this->posicaoDx = -5;
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
