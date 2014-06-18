#include <tori.h>
#include <wand.h>
#include <grafico.h>
#include <QString>
#include <QMediaPlayer>
#include <QMainWindow>

class Funcoes
{
public:
    Funcoes();
    ~Funcoes();

    static int contadorMortes, pontosJogador;
    static QVector<QPoint> series;
    static bool started, pontoMarcadoI, pontoMarcadoII;
    static QMediaPlayer *playerDead, *playerCoin, *playerFlap;

    static void DetectarColisaoChao(int posicaoToriY);
    static void RedefinirPropriedades();
    static void DetectarColisaoCanos(Tori *tori, Wand *wand);
    static void TocarSom(char som);
    static void MatarPassaro();
    static void MostrarGrafico();
    static void MarcarPonto(bool pontoI);
};
