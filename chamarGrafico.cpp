#include "grafico.h"
#include <QApplication>
#include <QWidget>

void adicionarVetores(Grafico* grafico)
{
    // Vetor com os pontos do gráfico
    QVector<QPoint> points;
    points.push_back(QPoint(0, 6));
    points.push_back(QPoint(2, 4));
    points.push_back(QPoint(3, 8));
    points.push_back(QPoint(7, 4));
    points.push_back(QPoint(10, 5));
    points.push_back(QPoint(11, 1));
    points.push_back(QPoint(13, 3));
    points.push_back(QPoint(17, 6));
    points.push_back(QPoint(18, 3));
    points.push_back(QPoint(20, 2));

    // Vetor com os pontos do gráfico
    QVector<QPoint> points2;
    points2.push_back(QPoint(0, 5));
    points2.push_back(QPoint(5, 10));
    points2.push_back(QPoint(10, 3));
    points2.push_back(QPoint(15, 6));
    points2.push_back(QPoint(20, 8));

    // Cara do robô
    QVector<QPoint> pointsBot;
    pointsBot.push_back(QPoint(6, 8));
    pointsBot.push_back(QPoint(9, 8));
    pointsBot.push_back(QPoint(9, 7));
    pointsBot.push_back(QPoint(10, 6));
    pointsBot.push_back(QPoint(9, 6));
    pointsBot.push_back(QPoint(10, 7));
    pointsBot.push_back(QPoint(10, 8));
    pointsBot.push_back(QPoint(13, 8));
    pointsBot.push_back(QPoint(12, 7));
    pointsBot.push_back(QPoint(12, 5));
    pointsBot.push_back(QPoint(10, 3));
    pointsBot.push_back(QPoint(9, 3));
    pointsBot.push_back(QPoint(7, 5));
    pointsBot.push_back(QPoint(7, 7));
    pointsBot.push_back(QPoint(6, 8));

    // Vetor com o eixo X
    QVector<QString> xValues;
    xValues.push_back("0.0");
    xValues.push_back("5.0");
    xValues.push_back("10.0");
    xValues.push_back("15.0");
    xValues.push_back("20.0");

    // Vetor com o eixo Y
    QVector<QString> yValues;
    yValues.push_back("0.0");
    yValues.push_back("2.0");
    yValues.push_back("4.0");
    yValues.push_back("6.0");
    yValues.push_back("8.0");
    yValues.push_back("10.0");

    grafico->addSeries(points, QColor(Qt::blue));
    grafico->addSeries(points2, QColor(Qt::red));
    grafico->addSeries(pointsBot, QColor(Qt::black));
    grafico->setAxisX(xValues);
    grafico->setAxisY(yValues);
    grafico->setLabelX("Eixo X");
    grafico->setLabelY("Eixo Y");
    grafico->setTitle("Teste de Gráfico");
}

int chamarGrafico(int argc, char **argv)
{
    QApplication app(argc, argv);
    Grafico* grafico = new Grafico();

    adicionarVetores(grafico);

    // Propriedades do form
    QMainWindow window;
    window.setWindowTitle("Line Chart");
    window.setCentralWidget(grafico);
    window.resize(600, 400);

    window.show();

    return app.exec();
}

