#include <QT>
#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QDateTime>
#include <tori.h>
#include <wand.h>

class FrmJogo: public QFrame
{
    Q_OBJECT
public:
    FrmJogo();
    ~FrmJogo();

private slots:
    void callWand();
    void tick();

private:
    QTimer *timerRepaint, *timerWand;
    Tori *tori;
    Wand *wand;

    int fps;
    int counter;
    float constantDt;
    bool started;
    qint64 lastTime, accumulator60;

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
};
