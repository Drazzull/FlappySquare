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
    this->rotation = 0;
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
    /* Atualiza a posição do pássaro */
    if (this->posicaoDy > 0)
    {
        this->posicaoToriY += std::ceil((this->posicaoDy * dt * 60) / 1000);
    }
    else
    {
        this->posicaoToriY += std::floor((this->posicaoDy * dt * 60) / 1000);
    }

    // Posição máxima em relação ao chão
    if (this->posicaoToriY > 580)
    {
        this->posicaoToriY = 580;
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
        /*paint.save();
        paint.translate(70, this->posicaoToriY);
        paint.rotate(this->rotation);*/
        paint.drawRect(70, this->posicaoToriY, this->toriWidth, this->toriHeight);
        /*paint.restore();*/
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

    this->rotation += 10;
    if(this->rotation > 90)
    {
        this->rotation = 90;
    }
}

void Tori::flapUp()
{
    Funcoes::TocarSom('F');
    this->rotation = -20;
    this->gravidade = 2;
    this->posicaoDy -= 70;
}
