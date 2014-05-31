#include <QT>
#include <QMainWindow>
#include <QFrame>
#include <QPainter>

class Grafico: public QFrame
{
    Q_OBJECT
public:
    Grafico();

    ~Grafico();

    void addSeries(QVector<QPoint> series, QColor color);

    void setAxisX(QVector<QString> values);

    void setAxisY(QVector<QString> values);

    void setLabelX(QString nome);

    void setLabelY(QString nome);

    void setTitle(QString tituloGrafico);

public slots:

private:
    QVector<QString> eixoX, eixoY;
    QVector< QVector<QPoint> > vetorOriginal;
    QVector<QColor> corGrafico;
    QString tituloGrafico, labelX, labelY;
    double maiorY, maiorX, menorX, menorY, intervaloEixoX, intervaloEixoY, percMenorX, percMenorY;
    int heightGrid, widthGrid;

    QVector<QPoint> redimensionarVetorX(QVector<QPoint> vetorRedimensionar);
    QVector<QPoint> redimensionarVetorY(QVector<QPoint> vetorRedimensionar);

    void calcularValoresFixos();
    void redimensionarEixoX(QPainter& paint);
    void redimensionarEixoY(QPainter& paint);
    void paintEvent(QPaintEvent* event);
};
