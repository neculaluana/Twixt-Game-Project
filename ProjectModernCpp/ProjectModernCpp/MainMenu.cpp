#include "MainMenu.h"
#include "Button.h"
#include <QGraphicsTextItem>
#include <qfiledialog.h>


void MainMenu::start() {

    scene->clear();
}

void MainMenu::displayMainMenu() {

    Button* playButton = new Button(QString("New game"));
    int bxPos = this->width() / 2 - playButton->boundingRect().width() / 2;
    int byPos = 375;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    Button* loadButton = new Button(QString("Load game"));
    int lxPos = this->width() / 2 - loadButton->boundingRect().width() / 2;
    int lyPos = 450;
    loadButton->setPos(lxPos, lyPos);
    connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));
    scene->addItem(loadButton);

    Button* quitButton = new Button(QString("Quit"));
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

void MainMenu::load()
{
}


MainMenu::MainMenu(QWidget* parent) {
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024, 768);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1024, 768);
    setScene(scene);
}