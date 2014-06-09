#include <frmjogo.h>
#include <funcoes.h>

#include <QDebug>

int FrmJogo::heightFrm = 0;
int FrmJogo::widthFrm = 0;

void FrmJogo::reset()
{
    Funcoes::pontosJogador = 0;
    Funcoes::started = false;
    this->fps = 60;
    this->constantDt = 1000 / this->fps;
    this->lastTime = QDateTime::currentMSecsSinceEpoch();
    this->accumulator60 = 0;
}

FrmJogo::FrmJogo()
{
    this->timerRepaint = new QTimer(this);
    this->tori = new Tori();
    this->wand = new Wand();

    this->setMinimumSize(400, 600);
    this->setMaximumSize(400, 600);
    this->setStyleSheet("background-image: url(:/img/Background.jpg);");

    FrmJogo::heightFrm = this->height();
    FrmJogo::widthFrm = this->width();

    this->timerRepaint->start(60);
    this->reset();

    QObject::connect(this->timerRepaint, SIGNAL(timeout()),
                     this, SLOT(repaint()));

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

void FrmJogo::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);

    // Insere o quadrado verde
    QPainter paint(this);

    QFont font = paint.font();
    font.setFamily("Consolas");
    font.setPointSize(font.pointSize() * 2);
    paint.setFont(font);

    this->tori->ziehen(paint);
    this->wand->ziehen(paint);

    paint.setPen(Qt::black);
    paint.setBrush(Qt::black);
    paint.drawText(180, 60, QString::number(Funcoes::pontosJogador));
    if (!Funcoes::started)
    {
        paint.drawText(100, 130, "Press Space");
    }

    if (Tori::morto)
    {
        paint.drawText(100, 130, " GAMEOVER! ");
        paint.drawText(100, 160, "Press Space");
    }

    Funcoes::detectarColisaoCanos(this->tori, this->wand);
    Funcoes::detectarColisaoChao(this->tori->getPosicaoToriY());
}

void FrmJogo::keyPressEvent(QKeyEvent *event)
{
    QFrame::keyPressEvent(event);

    if (event->key() == Qt::Key_Space)
    {
        if (Tori::morto)
        {
            this->reset();
            this->tori->reset();
            this->wand->reset();
        }

        if (!Funcoes::started)
        {
            Funcoes::started = true;
        }

        this->tori->flapUp();
    }
}

void FrmJogo::mousePressEvent(QMouseEvent* event)
{
    QFrame::mousePressEvent(event);

    if (Tori::morto)
    {
        this->reset();
        this->tori->reset();
        this->wand->reset();
    }

    if (!Funcoes::started)
    {
        Funcoes::started = true;
    }

    this->tori->flapUp();
}
