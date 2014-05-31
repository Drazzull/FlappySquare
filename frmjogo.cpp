#include "frmjogo.h"

FrmJogo::FrmJogo()
{
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Sunken);
    this->setMinimumSize(400, 800);
    this->setMaximumSize(400, 800);

    this->timer = new QTimer(this);
    this->timer->start(60);
    this->tori = new Tori();

    QObject::connect(this->timer, SIGNAL(timeout()),
                     this, SLOT(repaint()));
}

FrmJogo::~FrmJogo()
{

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
}
