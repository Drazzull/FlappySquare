#include <QT>
#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QTimer>

class Tori
{
public:
    Tori();
    ~Tori();
    void ziehen(QPainter& paint);

private slots:
    void cair();

private:
    int posicaoToriX;
    int posicaoToriY;
    QTimer* timer;
};
