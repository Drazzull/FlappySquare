#include "frmjogo.h"

#include <QDebug>

FrmJogo::FrmJogo()
{
    this->started = false;
    this->fps = 60;
    this->constantDt = 1000 / this->fps;
    this->lastTime = QDateTime::currentMSecsSinceEpoch();
    this->accumulator60 = 0;

    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Sunken);
    this->setMinimumSize(400, 800);
    this->setMaximumSize(400, 800);

    this->timerRepaint = new QTimer(this);
    this->timerRepaint->start(60);

    // Gera um número de tempo aleatório entre 5s e 7s para gerar as paredes
    int tempo = rand() % 7000 + 5000;
    this->timerWand = new QTimer(this);
    this->timerWand->start(tempo);
    this->tori = new Tori();
    this->wand = new Wand();

    QObject::connect(this->timerRepaint, SIGNAL(timeout()),
                     this, SLOT(repaint()));

    QObject::connect(this->timerWand, SIGNAL(timeout()),
                     this, SLOT(callWand()));

    // Start timer
    QTimer::singleShot(1000/this->fps, this, SLOT(tick()));
}

FrmJogo::~FrmJogo()
{

}

void FrmJogo::tick()
{
    // Grava o número de segundos até agora
    qint64 now = QDateTime::currentMSecsSinceEpoch();

    // Define o escopo das variáveis
    {
        // Verifica a quantidade de tempo que passou desde o último tempo
        qint64 passed = now - this->lastTime;

        this->accumulator60 += passed;
        while (this->accumulator60 >= this->constantDt)
        {
            this->tori->move(this->constantDt);
            this->wand->move(this->constantDt);

            this->accumulator60 -= this->constantDt;
        }

        this->repaint();
        this->lastTime = now;
    }

    // Reset the timer
    QTimer::singleShot(1000/this->fps, this, SLOT(tick()));
}

void FrmJogo::callWand()
{
    this->wand->callWand(this->started, this->tori->getMorto());
}

void FrmJogo::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);

    // Insere o quadrado verde
    QPainter paint(this);
    paint.setPen(Qt::red);
    paint.setBrush(Qt::red);

    QFont font = paint.font();
    font.setFamily("Consolas");
    paint.setFont(font);

    this->tori->ziehen(paint);
    this->wand->ziehen(paint);
}

void FrmJogo::keyPressEvent(QKeyEvent *event)
{
    QFrame::keyPressEvent(event);

    if ((event->key() == Qt::Key_Space) || (event->key() == Qt::Key_Return))
    {

        this->started = true;
        this->tori->setCanDown(true);

        this->tori->flapUp();
    }
}

void FrmJogo::mousePressEvent(QMouseEvent* event) {
    QFrame::mousePressEvent(event);

    this->started = true;
    this->tori->setCanDown(true);
    this->tori->flapUp();
}
