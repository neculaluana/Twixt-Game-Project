#include "MainMenu.h"


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
    //scene->clear();
    int startY = 375;
    int buttonInterval = 75;

    // Butonul "New game"
    playButton = new MenuButton(QString("New game"));
    int bxPos = this->width() / 2 - playButton->boundingRect().width() / 2;
    playButton->setPos(bxPos, startY);
    connect(playButton, SIGNAL(clicked()), this, SLOT(newGame()));
    scene->addItem(playButton);


    playerNameRedInput = new QLineEdit();
    playerNameRedInput->setPlaceholderText("Enter Red Player's Name");
    playerNameRedInput->setGeometry(QRect(bxPos, startY -100, 200, 30));
    scene->addWidget(playerNameRedInput);

    playerNameBlackInput = new QLineEdit();
    playerNameBlackInput->setPlaceholderText("Enter Black Player's Name");
    playerNameBlackInput->setGeometry(QRect(bxPos, startY - 50, 200, 30)); 
    scene->addWidget(playerNameBlackInput);

    // Butonul "Load game"
    loadButton = new MenuButton(QString("Load game"));
    int lxPos = this->width() / 2 - loadButton->boundingRect().width() / 2;
    loadButton->setPos(lxPos, startY + buttonInterval);
    connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));
    scene->addItem(loadButton);

    // Butonul "Settings"
    settingsButton = new MenuButton(QString("Settings"));
    int sxPos = this->width() / 2 - settingsButton->boundingRect().width() / 2;
    settingsButton->setPos(sxPos, startY + 2 * buttonInterval);
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(settings()));
    scene->addItem(settingsButton);

    // Butonul "Quit"
    quitButton = new MenuButton(QString("Quit"));
    int qxPos = this->width() / 2 - quitButton->boundingRect().width() / 2;
    quitButton->setPos(qxPos, startY + 3 * buttonInterval);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);


    QImage imageFile("Resources/twixt.jpg");
    int imxPos = this->width() / 2 - imageFile.width() / 4;
    int imyPos = 80;
    image = new QGraphicsPixmapItem(QPixmap::fromImage(imageFile));
    image->setScale(0.5);
    image->setPos(imxPos, imyPos);
    scene->addItem(image);
}

void MainMenu::newGame() 
{
    //scene->clear();
    setIsNewGame(true);
    emit newGameStarted(playerNameRedInput->text(), playerNameBlackInput->text());

}

void MainMenu::settings()
{
    //scene->clear();
    setSettings(true);
    emit SettingsClicked();

}

void MainMenu::setSettings(bool b)
{
    settingsClicked = b;
}

bool MainMenu::getSettingsClicked()
{
    return settingsClicked;
}

void MainMenu::removeAllItems()
{
  
    playButton->enableButton = false;
    playButton->hide();
    playButton->setFlag(QGraphicsItem::ItemIsSelectable, false);
    playButton->setFlag(QGraphicsItem::ItemIsFocusable, false);

    loadButton->enableButton = false;
    loadButton->hide();
    loadButton->setFlag(QGraphicsItem::ItemIsSelectable, false);
    loadButton->setFlag(QGraphicsItem::ItemIsFocusable, false);

    quitButton->enableButton = false;
    quitButton->hide();
    quitButton->setFlag(QGraphicsItem::ItemIsSelectable, false);
    quitButton->setFlag(QGraphicsItem::ItemIsFocusable, false);

    settingsButton->enableButton = false;
    settingsButton->hide();
    settingsButton->setFlag(QGraphicsItem::ItemIsSelectable, false);
    settingsButton->setFlag(QGraphicsItem::ItemIsFocusable, false);

    playerNameRedInput->hide();
    playerNameBlackInput->hide();

    image->hide();
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



void MainMenu::displayMainMenu() {
    //scene->clear();
   /* int startY = 375;
    int buttonInterval = 75;*/

    //// Butonul "New game"
    //MenuButton* playButton = new MenuButton(QString("New game"));
    //int bxPos = this->width() / 2 - playButton->boundingRect().width() / 2;
    //playButton->setPos(bxPos, startY);
    //connect(playButton, SIGNAL(clicked()), this, SLOT(newGame()));
    playerNameRedInput->show();
    playerNameBlackInput->show();
    scene->addItem(playButton);

    //// Butonul "Load game"
    //MenuButton* loadButton = new MenuButton(QString("Load game"));
    //int lxPos = this->width() / 2 - loadButton->boundingRect().width() / 2;
    //loadButton->setPos(lxPos, startY + buttonInterval);
    //connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));
    scene->addItem(loadButton);

    //// Butonul "Settings"
    //MenuButton* settingsButton = new MenuButton(QString("Settings"));
    //int sxPos = this->width() / 2 - settingsButton->boundingRect().width() / 2;
    //settingsButton->setPos(sxPos, startY + 2 * buttonInterval);
    //connect(settingsButton, SIGNAL(clicked()), this, SLOT(settings()));
    scene->addItem(settingsButton);

    // Butonul "Quit"
    //MenuButton* quitButton = new MenuButton(QString("Quit"));
    //int qxPos = this->width() / 2 - quitButton->boundingRect().width() / 2;
    //quitButton->setPos(qxPos, startY + 3 * buttonInterval);
    //connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);


    //QImage image("Resources/twixt.jpg");
    //int imxPos = this->width() / 2 - image.width() / 4;
    //int imyPos = 150;
    //QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    //item->setScale(0.5);
    //item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    //item->setPos(imxPos, imyPos);
    scene->addItem(image);


}



