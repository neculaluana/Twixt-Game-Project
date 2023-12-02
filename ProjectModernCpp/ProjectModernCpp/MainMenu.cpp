#include "MainMenu.h"
#include "Button.h"
#include <QGraphicsTextItem>
#include <qfiledialog.h>


void MainMenu::start() {

    scene->clear();
}

void MainMenu::displayMainMenu() {
    const int width = 150;
    const int height = 200;

   // QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());

    

    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width() / 2 - playButton->boundingRect().width() / 2;
    int byPos = 375;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width() / 2 - quitButton->boundingRect().width() / 2;
    int qyPos = 450;
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