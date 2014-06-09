#include <tori.h>
#include <frmjogo.h>
#include <wand.h>
#include <QDebug>
#include <funcoes.h>

bool Tori::morto = false;

void Tori::reset()
{
    this->gravidade = 0.0;
    this->fps = 2.0;
    this->posicaoToriY = 230;
    this->posicaoDy = 1;
    Tori::morto = false;
    this->toriHeight = 22;
    this->toriWidth = 27;
    this->timer->stop();
    this->timer->start(100);
}

Tori::Tori()
{
    this->timer = new QTimer(this);
    this->contadorPlanar = -5;
    this->reset();

    QObject::connect(this->timer, SIGNAL(timeout()),
                     this, SLOT(cair()));
}

Tori::~Tori()
{

}

int Tori::getPosicaoToriY()
{
    return this->posicaoToriY;
}

int Tori::getToriX()
{
    return (70 + this->toriWidth);
}

int Tori::getToriHeight()
{
    return this->toriHeight;
}

void Tori::move(float dt)
{
    // Se está morto não realiza update
    if (Tori::morto)
    {
        return;
    }

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
}

void Tori::ziehen(QPainter &paint)
{
    paint.setBrush(Qt::red);
    paint.setPen(Qt::red);

    if (Funcoes::started)
    {
        paint.drawRect(70, this->posicaoToriY, this->toriWidth, this->toriHeight);
        return;
    }

    paint.drawRect(170, this->posicaoToriY, this->toriWidth, this->toriHeight);
}

void Tori::cair()
{
    if (!Funcoes::started)
    {
        return;
    }

    this->posicaoDy += 2 * this->gravidade;
    this->gravidade += 2;
    if (this->gravidade >= 30)
    {
        this->gravidade = 30;
    }
}

void Tori::flapUp()
{
    this->gravidade = 2;
    this->posicaoDy -= 70;
}
