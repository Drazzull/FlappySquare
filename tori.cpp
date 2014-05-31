#include "tori.h"

Tori::Tori()
{
    this->posicaoToriX = 100;
    this->posicaoToriY = 100;
    this->timer = new QTimer(this);
    this->timer->start(60);

    QObject::connect(this->timer, SIGNAL(timeout()),
                     this, SLOT(cair()));
}

Tori::~Tori()
{

}

void Tori::ziehen(QPainter &paint)
{
   paint.drawRect(this->posicaoToriX, this->posicaoToriY, 40, 40);
}

void Tori::cair()
{

}
