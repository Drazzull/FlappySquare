#include "grafico.h"

///
/// \brief Grafico::redimensionarVetorX - Redimensiona o eixo X do vetor
///
QVector<QPoint> Grafico::redimensionarVetorX(QVector<QPoint> vetorOrigem)
{
    QVector<QPoint> vetorRedimensionar = vetorOrigem;

    // Obtém o último valor de X - será usado como base para posicionamento dos demais valores
    double menorX = vetorOrigem[0].x();
    for(int i = 0; i < vetorOrigem.length(); i++)
    {
        if (vetorOrigem[i].x() > this->maiorX)
        {
            this->maiorX = vetorOrigem[i].x();
        }

        if (menorX > vetorOrigem[i].x())
        {
            menorX = vetorOrigem[i].x();
        }
    }

    // Posição máxima e mínima que pode ter no grid
    double posMaiorX = this->widthGrid + ((this->width() - this->widthGrid) / 2);
    double posMenorX = (this->width() - this->widthGrid) / 2;
    double intervalo = posMaiorX - posMenorX;

    // Percorre o array recalculando os valores do eixo X
    for(int i = 0; i < vetorOrigem.length(); i++)
    {
        // Acha o percentual que o novo valor representa em relação ao maior
        double percX = ((vetorOrigem[i].x() * 100) / this->maiorX);

        // Calcula o valor da nova posição
        double posXValor = posMenorX + ((intervalo * percX) / 100);
        vetorRedimensionar[i].setX(posXValor);
    }

    return vetorRedimensionar;
}

///
/// \brief Grafico::redimensionarVetorY - Redimensiona o eixo Y do vetor
///
QVector<QPoint> Grafico::redimensionarVetorY(QVector<QPoint> vetorOrigem)
{
    QVector<QPoint> vetorRedimensionar = vetorOrigem;

    // Obtém o maior valor de Y
    double menorY = vetorOrigem[0].y();
    for(int i = 0; i < vetorOrigem.length(); i++)
    {
        if (vetorOrigem[i].y() > this->maiorY)
        {
            this->maiorY = vetorOrigem[i].y();
        }

        if (menorY > vetorOrigem[i].y())
        {
            menorY = vetorOrigem[i].y();
        }
    }

    double posMaiorY = ((this->height() - this->heightGrid) / 2);
    double posMenorY = this->heightGrid + ((this->height() - this->heightGrid) / 2);
    double intervalo = posMaiorY - posMenorY;

    // Percorre o array pintando os valores do eixo Y
    for(int i = 0; i < vetorOrigem.length(); i++)
    {
        // Acha o percentual que o novo valor representa em relação ao maior
        double percY = ((vetorOrigem[i].y() * 100) / this->maiorY);

        // Calcula o valor da nova posição
        double posYValor = posMenorY + ((intervalo * percY) / 100);
        vetorRedimensionar[i].setY(posYValor);
    }

    return vetorRedimensionar;
}
///
/// \brief Grafico::Grafico - Construtor sem parâmetros
///
Grafico::Grafico()
{
    this->heightGrid = this->height();
    this->widthGrid = this->width();
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Sunken);
    this->setMinimumSize(600, 400);
}

///
/// \brief Grafico::~Grafico - Desconstrutor
///
Grafico::~Grafico()
{

}

///
/// \brief Grafico::addSeries - Adiciona um vetor de pontos à tela
/// \param series - Vetor de pontos
/// \param color - Cor dos pontos
///
void Grafico::addSeries(QVector<QPoint> series, QColor color){
    this->vetorOriginal.append(series);
    this->corGrafico.append(color);
}

///
/// \brief setAxisX - Define os valores do eixo X
/// \param values - Valores do eixo X
///
void Grafico::setAxisX(QVector<QString> values)
{
    this->eixoX = values;
}

///
/// \brief setAxisY - Define os valores do eixo Y
/// \param values - Valores do eixo Y
///
void Grafico::setAxisY(QVector<QString> values)
{
    this->eixoY = values;
}

///
/// \brief setLabelX - Define um apelido pro eixo X
/// \param name - apelido
///
void Grafico::setLabelX(QString nome)
{
    this->labelX = nome;
}

///
/// \brief setLabelY
/// \param name
///
void Grafico::setLabelY(QString nome)
{
    this->labelY = nome;
}

///
/// \brief setTitle
/// \param title
///
void Grafico::setTitle(QString tituloGrafico)
{
    this->tituloGrafico = tituloGrafico;
}

///
/// \brief Grafico::paintEvent - Evento de pintura da tela
/// \param event - Evento de pintura
///
void Grafico::paintEvent(QPaintEvent* event){
    QFrame::paintEvent(event);

    // Insere o quadrado verde
    QPainter paint(this);
    paint.setPen(Qt::white);
    paint.setBrush(Qt::white);

    QFont font = paint.font();
    font.setFamily("Consolas");
    paint.setFont(font);

    /* Quadrado com borda arredondada, apenas estilo */
    int heightPercent = this->height() *0.98;
    int widthPercent = this->width()*0.98;
    int xTemp = (this->width() - widthPercent)/2;
    int yTemp = (this->height() - heightPercent)/2;
    paint.drawRoundedRect(xTemp, yTemp, widthPercent, heightPercent, 8.0, 8.0);

    /* Grid interno */
    paint.setPen(Qt::black);
    this->heightGrid = this->height() *0.7;
    this->widthGrid = this->width()*0.7;
    xTemp = (this->width() - this->widthGrid)/2;
    yTemp = (this->height() - this->heightGrid)/2;
    paint.drawRect(xTemp, yTemp, this->widthGrid, this->heightGrid);

    /* Eixo X */
    // Obtém o último valor de X - será usado como base para posicionamento dos demais valores
    this->maiorX = this->eixoX[this->eixoX.size() - 1].toDouble();
    double menorX = this->eixoX[0].toDouble();
    double posMaiorX = this->widthGrid + ((this->width() - this->widthGrid) / 2);
    double posMenorX = (this->width() - this->widthGrid) / 2;

    // Percorre o array pintando os valores do eixo X
    yTemp = 20 + this->heightGrid + ((this->height() - this->heightGrid) / 2);
    for(int i = 0; i < this->eixoX.size(); i++)
    {
        double percX = 0;
        double posXValor = 0;
        double intervalo = posMaiorX - posMenorX;
        if (this->eixoX[i].toDouble() == menorX)
        {
            paint.drawText(posMenorX, yTemp, this->eixoX[i]);
            continue;
        }

        // Acha o percentual que o novo valor representa em relação ao maior
        percX = ((this->eixoX[i].toDouble() * 100) / this->maiorX);

        // Calcula o valor da nova posição
        posXValor = ((percX * intervalo) / 100) + posMenorX;
        paint.drawText(posXValor, yTemp, this->eixoX[i]);
    }

    /* Eixo Y */
    // Obtém o último valor de Y - será usado como base para posicionamento dos demais valores
    this->maiorY = this->eixoY[this->eixoY.size() - 1].toDouble();
    double posMaiorY = ((this->height() - this->heightGrid) / 2);
    double posMenorY = this->heightGrid + ((this->height() - this->heightGrid) / 2);

    // Percorre o array pintando os valores do eixo Y
    xTemp = ((this->width() - this->widthGrid) / 2) - 30;
    for(int i = 0; i < eixoY.size(); i++)
    {
        // Variáveis de controle
        double percY = 0;
        double posYValor = 0;
        double intervalo = posMenorY - posMaiorY;

        // Acha o percentual que o novo valor representa em relação ao maior
        percY = 100 - ((this->eixoY[i].toDouble() * 100) / this->maiorY);

        // Calcula o valor da nova posição
        posYValor = ((percY * intervalo)/100) + posMaiorY;
        paint.drawText(xTemp, posYValor, this->eixoY[i]);
        paint.setPen(Qt::gray);
        paint.drawLine(xTemp + 30, posYValor, (xTemp + 30) + this->widthGrid, posYValor);
        paint.setPen(Qt::black);
    }

    /* Corrige a fonte para os títulos */
    font.setPointSize(font.pointSize() * 2);
    paint.setFont(font);

    /* Texto X */
    yTemp = 50 + this->heightGrid + ((this->height() - this->heightGrid) / 2);
    xTemp = (this->width() - (this->labelX.size() * 15)) / 2;
    paint.drawText(xTemp, yTemp, this->labelX);

    /* Texto Y */
    yTemp = this->height() / 2;
    xTemp = ((this->width() - this->widthGrid) / 2) - 50;
    paint.save();
    paint.translate(xTemp, yTemp);
    paint.rotate(270);
    paint.drawText(0, 0, this->labelY);
    paint.restore();

    /* Título */
    yTemp = ((this->height() - this->heightGrid) / 2) - 10;
    xTemp = (this->width() - (this->tituloGrafico.size() * 15)) / 2;
    paint.drawText(xTemp, yTemp, this->tituloGrafico);

    /* Gráfico */
    // Percorre o vetor de vetores para redimensioná-los
    for(int i=0; i < this->vetorOriginal.length(); i++)
    {
        // Redimensiona o eixo X do vetor atual
        QVector<QPoint> vetorRedimensionar = this->redimensionarVetorX(this->vetorOriginal[i]);

        // Redimensiona o eixo Y do vetor retornado da função anterior (o mesmo já possui o eixo X redimensionado)
        vetorRedimensionar = this->redimensionarVetorY(vetorRedimensionar);

        // Muda a cor de acordo com a cor do gráfico atual e pinta a cor
        paint.setPen(this->corGrafico[i]);
        paint.drawPolyline(vetorRedimensionar);
    }
}
