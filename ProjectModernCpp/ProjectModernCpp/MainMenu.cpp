#include "MainMenu.h"
#include "MenuButton.h"
#include <QGraphicsTextItem>
#include <qfiledialog.h>


void MainMenu::newGame() 
{
    scene->clear();
    setIsNewGame(true);
    emit newGameStarted();

}

void MainMenu::displayMainMenu() {

    MenuButton* playButton = new MenuButton(QString("New game"));
    int bxPos = this->width() / 2 - playButton->boundingRect().width() / 2;
    int byPos = 375;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(newGame()));
    scene->addItem(playButton);

    MenuButton* loadButton = new MenuButton(QString("Load game"));
    int lxPos = this->width() / 2 - loadButton->boundingRect().width() / 2;
    int lyPos = 450;
    loadButton->setPos(lxPos, lyPos);
    connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));
    scene->addItem(loadButton);

    MenuButton* quitButton = new MenuButton(QString("Quit"));
    int qxPos = this->width() / 2 - quitButton->boundingRect().width() / 2;
    int qyPos = 525;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

    QImage image("Resources/twixt.jpg");
    int imxPos = this->width() / 2 - image.width() / 4;
    int imyPos = 150;
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    item->setScale(0.5);
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    item->setPos(imxPos, imyPos);
    scene->addItem(item);
}

void MainMenu::setIsNewGame(bool a)
{
    isNewGame = a;
}

bool MainMenu::getIsNewGame()
{
    return isNewGame;
}

void MainMenu::load()
{
}


MainMenu::MainMenu(QWidget* parent) {
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(700, 700);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 700, 700);
    setScene(scene);
    isNewGame = false;
}