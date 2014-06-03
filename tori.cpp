#include "tori.h"

Tori::Tori()
{
    this->canDown = false;
    this->vPulo = -515;
    this->vMax = 680.0;
    this->gravidade = 2000;
    this->fps = 2.0;
    this->posicaoToriY = 100;
    this->posicaoDy = 0;
    this->morto = false;
    this->toriSize = 40;
    this->timer = new QTimer(this);
    this->timer->start(100);

    QObject::connect(this->timer, SIGNAL(timeout()),
                     this, SLOT(cair()));
}

Tori::~Tori()
{

}

bool Tori::getMorto()
{
    return this->morto;
}

bool Tori::getCanDown()
{
    return this->canDown;
}

void Tori::setCanDown(bool canDown)
{
    this->canDown = canDown;
}

void Tori::move(float dt)
{
    /* Atualiza a posição do pássaro */
    if (this->posicaoDy > 0)
    {
        this->posicaoToriY += std::ceil((this->posicaoDy * dt * 60) / 1000);
    }
    else
    {
        this->posicaoToriY += std::floor((this->posicaoDy * dt * 60) / 1000);
    }

    // Zera a variável para que o mesmo se mova somente quando necessário
    this->posicaoDy = 0;

    this->detectarColisaoChao();
}

void Tori::ziehen(QPainter &paint)
{
    paint.drawRect(100, this->posicaoToriY, this->toriSize, this->toriSize);
}

void Tori::detectarColisaoChao()
{
    if(this->posicaoToriY >= 600)
    {
        this->posicaoDy = 0;
        this->posicaoToriY = 560;
        this->morto = true;
    }
}

void Tori::cair()
{
    if (!this->canDown)
    {
        return;
    }

    if (this->morto)
    {
        this->posicaoDy = 0;
        return;
    }

    this->posicaoDy = 20;
}

void Tori::flapUp()
{
    if (this->morto)
    {
        this->posicaoDy = 0;
        return;
    }
    this->posicaoDy = -60;
}

