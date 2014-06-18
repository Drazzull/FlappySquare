/*
 * Flappy Bird -> "Clone"
 * Encapsular o desenho do personagem do jogo em uma classe
 * Encapsular o desenho dos "Muros" do jogo em uma classe
 * A abertura dos "Muros" deve ser feita de forma procedural (aleatória)
 * Por "Clone", subentende-se a reprodução visual e da jogabilidade da forma mais fiel possível do original!
 * A cada 5 ou 10 vidas que o jogador perder, o jogo deve exibir um "Line Chart" com dados interessantes do gameplay nesse período;
 *
 */
#include <frmjogo.h>
#include <QApplication>
#include <QWidget>

/*int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    FrmJogo* frmJogo = new FrmJogo();

    // Propriedades do form
    QMainWindow window;
    window.setCentralWidget(frmJogo);
    frmJogo->setFocus();
    window.setFixedSize(400, 600);
    window.show();

    return app.exec();
}*/
