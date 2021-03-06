#include <QT>
#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QTimer>
#include <QDateTime>
#include <tori.h>
#include <wand.h>
#include <QMediaPlayer>

class FrmJogo: public QFrame
{
    Q_OBJECT
public:
    FrmJogo();
    ~FrmJogo();
    static int heightFrm, widthFrm;

private slots:
    void tick();

private:
    QTimer *timerRepaint;
    Tori *tori;
    Wand *wand;
    QFont *font;

    int fps;
    float constantDt;
    qint64 lastTime, accumulator60;

    void reset();
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
};
