#include <QT>
#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QTimer>

class Wand
{
public:
    Wand();
    ~Wand();
    void ziehen(QPainter& paint);

private:
    int posicaoWandX;
    int posicaoWandY;
    QTimer* timer;
};
