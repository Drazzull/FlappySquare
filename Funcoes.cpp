#include <funcoes.h>
#include <tori.h>
#include <wand.h>

bool Funcoes::started = false;
int Funcoes::contadorMortes = 0;
int Funcoes::pontosJogador = 0;
bool Funcoes::pontoMarcadoI = true;
bool Funcoes::pontoMarcadoII = true;
QMediaPlayer *Funcoes::playerFlap = new QMediaPlayer();
QMediaPlayer *Funcoes::playerDead = new QMediaPlayer();
QMediaPlayer *Funcoes::playerCoin = new QMediaPlayer();
QVector<QPoint> Funcoes::series;

Funcoes::Funcoes()
{

}

Funcoes::~Funcoes()
{

}

void Funcoes::RedefinirPropriedades()
{
    Funcoes::pontosJogador = 0;
    Funcoes::pontoMarcadoI = true;
    Funcoes::pontoMarcadoII = true;
}

void Funcoes::DetectarColisaoChao(int posicaoToriY)
{
    if(posicaoToriY >= 580)
    {
        Funcoes::MatarPassaro();
    }
}

void Funcoes::DetectarColisaoCanos(Tori *tori, Wand *wand)
{
    /* Colisão Cano I */
    if (wand->getPosicaoXCanoUpI() < 200)
    {
        // Cano Up
        if (tori->getToriX() > wand->getPosicaoXCanoUpI())
        {
            if ((tori->getToriX() < wand->getPosicaoXCanoUpI() + 70) &&
                    (tori->getPosicaoToriY() < (wand->getHeightCanoUpI())))
            {
                Funcoes::MatarPassaro();
                return;
            }

            if ((!Funcoes::pontoMarcadoI) &&
                    (tori->getToriX() >= ((wand->getPosicaoXCanoUpI() + 70) / 2)))
            {
                Funcoes::MarcarPonto(true);
            }
        }

        // Cano Down
        if (wand->getPosicaoXCanoUpI() < 200)
        {
            if ((tori->getToriX() > wand->getPosicaoXCanoDownI()) &&
                    (tori->getToriX() < wand->getPosicaoXCanoDownI() + 70) &&
                    ((tori->getPosicaoToriY() + tori->getToriHeight()) > (wand->getPosicaoYCanoDownI())))
            {
                Funcoes::MatarPassaro();
                return;
            }
        }
    }

    /* Colisão Cano II */
    if (wand->getPosicaoXCanoUpII() < 200)
    {
        // Cano Up
        if (tori->getToriX() > wand->getPosicaoXCanoUpII())
        {
            if ((tori->getToriX() < wand->getHeightCanoUpII()) &&
                    (tori->getPosicaoToriY() < (wand->getPosicaoXCanoUpII()) + 70))
            {
                Funcoes::MatarPassaro();
                return;
            }

            if ((!Funcoes::pontoMarcadoII) &&
                    (tori->getToriX() >= ((wand->getPosicaoXCanoUpII() + 70) / 2)))
            {
                Funcoes::MarcarPonto(false);
            }
        }

        // Cano Down
        if (wand->getPosicaoXCanoUpII() < 200)
        {
            if ((tori->getToriX() > wand->getPosicaoXCanoDownII()) &&
                    (tori->getToriX() < wand->getPosicaoXCanoDownII() + 70) &&
                    ((tori->getPosicaoToriY() + tori->getToriHeight()) > (wand->getPosicaoYCanoDownII  ())))
            {
                Funcoes::MatarPassaro();
                return;
            }
        }
    }
}

void Funcoes::TocarSom(char som)
{
    switch(som)
    {
    case 'D':
        Funcoes::playerDead->play();
        break;

    case 'C':
        Funcoes::playerCoin->play();
        break;

    case 'F':
        Funcoes::playerFlap->play();
        break;
    }
}

void Funcoes::MatarPassaro()
{
    Tori::morto = true;
    Funcoes::TocarSom('D');
    Funcoes::contadorMortes++;
    Funcoes::series.append(QPoint(Funcoes::contadorMortes, Funcoes::pontosJogador));
    if (Funcoes::contadorMortes == 5)
    {
        Funcoes::MostrarGrafico();
        Funcoes::contadorMortes = 0;
    }
}

void Funcoes::MarcarPonto(bool pontoI)
{
    Funcoes::TocarSom('C');
    if (pontoI)
    {
        Funcoes::pontoMarcadoI = true;
    }
    else
    {
        Funcoes::pontoMarcadoII = true;
    }
    Funcoes::pontosJogador++;
}

void Funcoes::MostrarGrafico()
{
    // Obtém o maior valor de Y (quantidade de pontos)
    int maior = 0;
    for(int i = 0; i < Funcoes::series.size(); i++)
    {
        if (Funcoes::series[i].y() > maior)
        {
            maior = Funcoes::series[i].y();
        }
    }

    // Define os valores dos eixos
    QVector<QString> axisY;
    axisY.clear();
    axisY.append("0");
    axisY.append(QString::number(maior * 0.25));
    axisY.append(QString::number(maior * 0.5));
    axisY.append(QString::number(maior * 0.75));
    axisY.append(QString::number(maior));

    QVector<QString> axisX;
    axisX.clear();
    axisX.append("1");
    axisX.append("2");
    axisX.append("3");
    axisX.append("4");
    axisX.append("5");

    // cria o objeto do gráfico
    Grafico *grafico = new Grafico();
    grafico->addSeries(Funcoes::series, Qt::red);
    grafico->setAxisX(axisX);
    grafico->setAxisY(axisY);
    grafico->setLabelX("Morte Nº");
    grafico->setLabelY("Pontos por Morte");
    grafico->setTitle("Resumo das Últimas 5 Mortes");

    // Abre a nova janela
    QMainWindow *window = new QMainWindow;
    window->setWindowTitle("Pontuação Teste");
    window->setCentralWidget(grafico);
    window->resize(800, 600);
    window->show();

    Funcoes::series.clear();
}
