#include <QT>
#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QTimer>
#include <cmath>

class Wand : public QWidget
{
    Q_OBJECT
public:
    Wand();
    ~Wand();
    void ziehen(QPainter& paint);
    void move(float dt);
    void callWand(bool started, bool morto);

public slots:
    void moveLeft();

private:
    QVector<QPoint> posicoesWandUp, posicoesWandDown;
    int posicaoDx, falhaEntreCanos;
    bool showWand;
    QTimer* timer;
};
