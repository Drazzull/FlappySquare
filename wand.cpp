#include <wand.h>
#include <frmjogo.h>
#include <funcoes.h>

void Wand::reset()
{
    this->timerMove->stop();
    this->timerMove->start(60);
    this->timerCallI->stop();
    this->timerCallII->stop();
    this->timerCallI->start(60);
    this->timerCallII->start(60);
    this->posicaoDx = 0;

    // Localização e dimensões do cano
    this->posicaoXCanoUpI = 0;
    this->posicaoXCanoUpII = 0;
    this->posicaoXCanoDownI = 0;
    this->posicaoXCanoDownII = 0;
    this->posicaoYCanoDownI = 0;
    this->posicaoYCanoDownII = 0;

    this->heightCanoUpI = 0;
    this->heightCanoUpII = 0;
    this->heightCanoDownI = 0;
    this->heightCanoDownII = 0;
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

int Wand::getPosicaoXCanoUpI()
{
    return this->posicaoXCanoUpI;
}

int Wand::getPosicaoXCanoDownI()
{
    return this->posicaoXCanoDownI;
}

int Wand::getHeightCanoUpI()
{
    return this->heightCanoUpI;
}

int Wand::getPosicaoYCanoDownI()
{
    return this->posicaoYCanoDownI;
}

int Wand::getPosicaoXCanoUpII()
{
    return this->posicaoXCanoUpII;
}

int Wand::getPosicaoXCanoDownII()
{
    return this->posicaoXCanoDownII;
}

int Wand::getHeightCanoUpII()
{
    return this->heightCanoUpII;
}

int Wand::getPosicaoYCanoDownII()
{
    return this->posicaoYCanoDownII;
}

void Wand::callWandI()
{
    // Gera a próxima parede apenas se o X inicial for menor que -100
    if (this->posicaoXCanoUpI > - 100)
    {
        return;
    }

    if (!Funcoes::started)
    {
        return;
    }

    if (Tori::morto)
    {
        return;
    }

    Funcoes::pontoMarcadoI = false;

    // A falha deve ficar entre 150 e 550
    int falhaEntreCanos = FrmJogo::heightFrm - ((rand() % 400) + 150);

    this->posicaoXCanoUpI = 430;
    this->posicaoXCanoDownI = 430;
    this->posicaoYCanoDownI = (falhaEntreCanos + 100);

    this->heightCanoUpI = (falhaEntreCanos);
    this->heightCanoDownI = (450);
}

void Wand::callWandII()
{
    // Gera a próxima parede apenas se o X inicial for menor que -100
    if (this->posicaoXCanoUpII > - 100)
    {
        return;
    }

    // Gera a próxima parede se a posição X do cano I tiver passado da metade da tela
    if (((this->posicaoXCanoUpI + 35) > (FrmJogo::widthFrm / 2)) || (this->posicaoXCanoUpI <= -100) )
    {
        return;
    }

    if (!Funcoes::started)
    {
        return;
    }

    if (Tori::morto)
    {
        return;
    }

    Funcoes::pontoMarcadoII = false;

    // A falha deve ficar entre 150 e 550
    int falhaEntreCanos = FrmJogo::heightFrm - ((rand() % 400) + 150);

    this->posicaoXCanoUpII = 430;
    this->posicaoXCanoUpII = 430;
    this->posicaoXCanoDownII = 430;
    this->posicaoYCanoDownII = (falhaEntreCanos + 100);

    this->heightCanoUpII = (falhaEntreCanos);
    this->heightCanoDownII = (450);
}

void Wand::move(float dt)
{
    this->posicaoXCanoUpI += std::floor((this->posicaoDx * dt * 60) / 1000);
    this->posicaoXCanoDownI += std::floor((this->posicaoDx * dt * 60) / 1000);

    this->posicaoXCanoUpII += std::floor((this->posicaoDx * dt * 60) / 1000);
    this->posicaoXCanoDownII += std::floor((this->posicaoDx * dt * 60) / 1000);

    // Zera a variável para que o mesmo se mova somente quando necessário
    this->posicaoDx = 0;
}

void Wand::moveLeft()
{
    if (!Funcoes::started)
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
    if (!Funcoes::started)
    {
        return;
    }

    QPen caneta;
    caneta.setBrush(Qt::green);
    caneta.setWidth(4);
    paint.setBrush(Qt::green);
    paint.setPen(caneta);

    paint.drawRect(this->posicaoXCanoDownI, this->posicaoYCanoDownI, 70, this->heightCanoDownI);
    paint.drawRect(this->posicaoXCanoUpI, 0, 70, this->heightCanoUpI);

    paint.drawRect(this->posicaoXCanoDownII, this->posicaoYCanoDownII, 70, this->heightCanoDownII);
    paint.drawRect(this->posicaoXCanoUpII, 0, 70, this->heightCanoUpII);
}
