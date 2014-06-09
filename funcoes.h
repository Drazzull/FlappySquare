#include <tori.h>
#include <wand.h>

class Funcoes
{
public:
    Funcoes();
    ~Funcoes();

    static int contadorMortes, pontosJogador;
    static bool started;

    static void detectarColisaoChao(int posicaoToriY);
    static void detectarColisaoCanos(Tori *tori, Wand *wand);
};
