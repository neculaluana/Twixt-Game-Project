#include "ProjectModernCpp.h"
#include "Game.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProjectModernCpp w;
    w.show();
    Game game("Ana", "Ion");
    game.initializeGame();
    return a.exec();
}
