#include <tori.h>
#include <frmjogo.h>
bool Tori::morto = false;

void Tori::reset()
{
    /*this->velocidadeVoo = -515.0f;
    this->velocidadeMaxima = 680.0f;*/
    this->gravidade = 0.0;
    this->fps = 2.0;
    this->posicaoToriY = 230;
    this->posicaoDy = 1;
    Tori::morto = false;
    this->toriSize = 40;
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

    this->detectarColisaoChao();
}

void Tori::ziehen(QPainter &paint)
{
    paint.setBrush(Qt::red);
    paint.setPen(Qt::red);

    if (FrmJogo::started)
    {
        paint.drawRect(70, this->posicaoToriY, this->toriSize, this->toriSize);
        return;
    }

    paint.drawRect(170, this->posicaoToriY, this->toriSize, this->toriSize);
}

void Tori::detectarColisaoChao()
{
    if(this->posicaoToriY >= 600)
    {
        this->posicaoDy = 0;
        this->posicaoToriY = 560;
        Tori::morto = true;
    }
}

void Tori::cair()
{
    if (!FrmJogo::started)
    {
        return;
    }

    this->posicaoDy += 2 * this->gravidade;
    this->gravidade += 2;
    if (this->gravidade >= 20)
    {
        this->gravidade = 20;
    }
}

void Tori::flapUp()
{
    this->gravidade = 2;
    this->posicaoDy -= 70;
}
