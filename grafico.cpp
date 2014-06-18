#include "grafico.h"

Grafico::Grafico()
{
    this->heightGrid = this->height();
    this->widthGrid = this->width();
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Sunken);
    this->setMinimumSize(1024, 768);
}

Grafico::~Grafico()
{

}

void Grafico::addSeries(QVector<QPoint> series, QColor color){
    this->vetorOriginal.append(series);
    this->corGrafico.append(color);
}

void Grafico::setAxisX(QVector<QString> values)
{
    this->eixoX = values;

    // Fixa um valor disponível, no caso do menor valor ser maior que zero
    this->maiorX = this->eixoX[this->eixoX.size() - 1].toDouble();
    this->menorX = this->eixoX[0].toDouble();
}

void Grafico::setAxisY(QVector<QString> values)
{
    this->eixoY = values;

    // Fixa um valor disponível, no caso do menor valor ser maior que zero
    this->maiorY = this->eixoY[this->eixoY.size() - 1].toDouble();
    this->menorY = this->eixoY[0].toDouble();
}

void Grafico::setLabelX(QString nome)
{
    this->labelX = nome;
}

void Grafico::setLabelY(QString nome)
{
    this->labelY = nome;
}

void Grafico::setTitle(QString tituloGrafico)
{
    this->tituloGrafico = tituloGrafico;
}

void Grafico::calcularValoresFixos()
{
    /* Menor Ponto dos Eixos */
    // Eixo X
    for(int j=0; j < this->vetorOriginal.length(); j++)
    {
        QVector<QPoint> vetorOrigem = this->vetorOriginal[j];
        for(int i = 0; i < vetorOrigem.length(); i++)
        {
            if (vetorOrigem[i].x() > this->maiorX)
            {
                this->maiorX = vetorOrigem[i].x();
            }

            if (this->menorX > vetorOrigem[i].x())
            {
                this->menorX = vetorOrigem[i].x();
            }
        }

        // Eixo Y
        for(int i = 0; i < vetorOrigem.length(); i++)
        {
            if (vetorOrigem[i].y() > this->maiorY)
            {
                this->maiorY = vetorOrigem[i].y();
            }

            if (this->menorY > vetorOrigem[i].y())
            {
                this->menorY = vetorOrigem[i].y();
            }
        }
    }

    /* Menor texto */
    // Eixo X
    for(int i = 0; i < this->eixoX.size(); i++)
    {
        if (eixoX[i].toDouble() > this->maiorX)
        {
            this->maiorX = eixoX[i].toDouble();
        }

        if (this->menorX > eixoX[i].toDouble())
        {
            this->menorX = eixoX[i].toDouble();
        }
    }

    // Eixo Y
    for(int i = 0; i < eixoY.size(); i++)
    {
        if (eixoY[i].toDouble() > this->maiorY)
        {
            this->maiorY = eixoY[i].toDouble();
        }

        if (this->menorY > eixoY[i].toDouble())
        {
            this->menorY = eixoY[i].toDouble();
        }
    }

    // Outros Valores
    this->intervaloEixoX = this->maiorX - this->menorX;
    this->percMenorX = ((this->menorX * 100) / this->intervaloEixoX);
    this->intervaloEixoY = this->maiorY - this->menorY;
    this->percMenorY = ((this->menorY * 100) / this->intervaloEixoY);
}

QVector<QPoint> Grafico::redimensionarVetorX(QVector<QPoint> vetorOrigem)
{
    QVector<QPoint> vetorRedimensionar = vetorOrigem;

    // Posição máxima e mínima que pode ter no grid
    double posMaiorX = this->widthGrid + ((this->width() - this->widthGrid) / 2);
    double posMenorX = (this->width() - this->widthGrid) / 2;
    double intervalo = posMaiorX - posMenorX;

    // Percorre o array recalculando os valores do eixo X
    for(int i = 0; i < vetorOrigem.length(); i++)
    {
        // Acha o percentual que o novo valor representa em relação ao maior
        double percX = ((vetorOrigem[i].x() * 100) / this->intervaloEixoX) - this->percMenorX;

        // Calcula o valor da nova posição
        double posXValor = posMenorX + ((intervalo * percX) / 100);
        vetorRedimensionar[i].setX(posXValor);
    }

    return vetorRedimensionar;
}

QVector<QPoint> Grafico::redimensionarVetorY(QVector<QPoint> vetorOrigem)
{
    QVector<QPoint> vetorRedimensionar = vetorOrigem;

    double posMaiorY = ((this->height() - this->heightGrid) / 2);
    double posMenorY = this->heightGrid + ((this->height() - this->heightGrid) / 2);
    double intervalo = posMaiorY - posMenorY;

    // Percorre o array pintando os valores do eixo Y
    for(int i = 0; i < vetorOrigem.length(); i++)
    {
        // Acha o percentual que o novo valor representa em relação ao maior
        double percY = ((vetorOrigem[i].y() * 100) / this->intervaloEixoY) - this->percMenorY;

        // Calcula o valor da nova posição
        double posYValor = posMenorY + ((intervalo * percY) / 100);
        vetorRedimensionar[i].setY(posYValor);
    }

    return vetorRedimensionar;
}

void Grafico::redimensionarEixoX(QPainter& paint)
{
    // Obtém o último valor de X - será usado como base para posicionamento dos demais valores
    double posMaiorX = this->widthGrid + ((this->width() - this->widthGrid) / 2);
    double posMenorX = (this->width() - this->widthGrid) / 2;
    double intervalo = posMaiorX - posMenorX;

    // Percorre o array pintando os valores do eixo X
    int yTemp = 20 + this->heightGrid + ((this->height() - this->heightGrid) / 2);
    for(int i = 0; i < this->eixoX.size(); i++)
    {
        double percX = 0;
        double posXValor = 0;

        // Acha o percentual que o novo valor representa em relação ao maior
        percX = ((this->eixoX[i].toDouble() * 100) / this->intervaloEixoX) - this->percMenorX;

        // Calcula o valor da nova posição
        posXValor = ((percX * intervalo) / 100) + posMenorX;
        paint.drawText(posXValor, yTemp, this->eixoX[i]);
    }
}

void Grafico::redimensionarEixoY(QPainter& paint)
{
    // Obtém o último valor de Y - será usado como base para posicionamento dos demais valores
    double posMaiorY = ((this->height() - this->heightGrid) / 2);
    double posMenorY = this->heightGrid + ((this->height() - this->heightGrid) / 2);
    double intervalo = posMenorY - posMaiorY;

    // Percorre o array pintando os valores do eixo Y
    int xTemp = ((this->width() - this->widthGrid) / 2) - 30;
    for(int i = 0; i < eixoY.size(); i++)
    {
        // Variáveis de controle
        double percY = 0;
        double posYValor = 0;

        // Acha o percentual que o novo valor representa em relação ao maior
        percY = 100 - ((this->eixoY[i].toDouble() * 100) / this->intervaloEixoY) + this->percMenorY;

        // Calcula o valor da nova posição
        posYValor = ((percY * intervalo)/100) + posMaiorY;
        paint.drawText(xTemp, posYValor, this->eixoY[i]);
        paint.setPen(Qt::gray);
        paint.drawLine(xTemp + 30, posYValor, (xTemp + 30) + this->widthGrid, posYValor);
        paint.setPen(Qt::black);
    }
}

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

    // Recalcula os valores fixos antes de repintar a tela
    this->calcularValoresFixos();

    /* Eixo X */
    this->redimensionarEixoX(paint);

    /* Eixo Y */
    this->redimensionarEixoY(paint);

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
        QPen caneta;
        caneta.setColor(this->corGrafico[i]);
        caneta.setWidth(2);
        paint.setPen(caneta);
        paint.drawPolyline(vetorRedimensionar);
    }
}
