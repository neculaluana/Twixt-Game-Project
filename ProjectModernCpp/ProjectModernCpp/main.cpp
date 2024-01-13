
#include "Game.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game("", "");

    return a.exec();
}
