#include <QT>
#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QTimer>
#include <cmath>

class Tori : public QWidget
{
    Q_OBJECT
public:
    Tori();
    ~Tori();
    void ziehen(QPainter& paint);
    void flapUp();
    void move(float dt);
    bool getMorto();
    bool getCanDown();
    void setCanDown(bool canDown);

public slots:
    void cair();

private:
    double fps;
    float vConstante, vMax, vPulo, gravidade;
    int posicaoToriY, posicaoDy, toriSize;

    bool morto, canDown;
    QTimer* timer;

    void detectarColisaoChao();
};
