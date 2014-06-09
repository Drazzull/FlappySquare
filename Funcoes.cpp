#include <funcoes.h>
#include <tori.h>
#include <wand.h>

bool Funcoes::started = false;
int Funcoes::contadorMortes = 0;
int Funcoes::pontosJogador = 0;

Funcoes::Funcoes()
{

}

Funcoes::~Funcoes()
{

}

void Funcoes::detectarColisaoChao(int posicaoToriY)
{
    if(posicaoToriY >= 610)
    {
        posicaoToriY = 580;
        Tori::morto = true;
    }
}

void Funcoes::detectarColisaoCanos(Tori *tori, Wand *wand)
{
    /* Colisão Cano I */
    if (wand->getPosicaoXCanoUpI() < 200)
    {
        // Cano Up
        if ((tori->getToriX() > wand->getPosicaoXCanoUpI()) &&
                (tori->getToriX() < wand->getPosicaoXCanoUpI() + 70) &&
                (tori->getPosicaoToriY() < (wand->getHeightCanoUpI())))
        {
            Tori::morto = true;
            Funcoes::contadorMortes ++;
            return;
        }

        // Cano Down
        if (wand->getPosicaoXCanoUpI() < 200)
        {
            if ((tori->getToriX() > wand->getPosicaoXCanoDownI()) &&
                    (tori->getToriX() < wand->getPosicaoXCanoDownI() + 70) &&
                    ((tori->getPosicaoToriY() + tori->getToriHeight()) > (wand->getPosicaoYCanoDownI())))
            {
                Tori::morto = true;
                Funcoes::contadorMortes ++;
                return;
            }
        }
    }

    /* Colisão Cano II */
    if (wand->getPosicaoXCanoUpII() < 200)
    {
        // Cano Up
        if ((tori->getToriX() > wand->getPosicaoXCanoUpII()) &&
                (tori->getToriX() < wand->getPosicaoXCanoUpII() + 70) &&
                (tori->getPosicaoToriY() < (wand->getHeightCanoUpII())))
        {
            Tori::morto = true;
            Funcoes::contadorMortes ++;
            return;
        }

        // Cano Down
        if ((tori->getToriX() > wand->getPosicaoXCanoDownII()) &&
                (tori->getToriX() < wand->getPosicaoXCanoDownII() + 70) &&
                ((tori->getPosicaoToriY() + tori->getToriHeight()) < (wand->getPosicaoYCanoDownII())))
        {
            Tori::morto = true;
            Funcoes::contadorMortes ++;
            return;
        }
    }
}
