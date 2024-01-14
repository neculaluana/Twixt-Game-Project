
#include "Game.h"
#include <QtWidgets/QApplication>
#include<QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("Resources/icon.ico"));
    Game game("", "");

    return app.exec();
}
