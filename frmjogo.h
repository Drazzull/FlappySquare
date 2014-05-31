#include <QT>
#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <tori.h>
#include <wand.h>

class FrmJogo: public QFrame
{
    Q_OBJECT
public:
    FrmJogo();
    ~FrmJogo();

private:
    void paintEvent(QPaintEvent* event);
    QTimer* timer;
    Tori* tori;
    Wand* wand;
};
