#include "wand.h"

Wand::Wand()
{
    this->timer = new QTimer(this);
    this->timer->start(60);

    QObject::connect(this->timer, SIGNAL(timeout()),
                     this, SLOT(repaint()));
}

Wand::~Wand()
{

}

void Tori::ziehen(QPainter &paint)
{
   paint.drawRect(this->posicaoToriX, this->posicaoToriY, 40, 40);
}
