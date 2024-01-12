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
    playerNameRedInput->setGeometry(QRect(bxPos, startY - 100, 200, 30));
    playerNameRedInput->setStyleSheet("border: 2px solid darkcyan;"); 
    scene->addWidget(playerNameRedInput);

    playerNameBlackInput = new QLineEdit();
    playerNameBlackInput->setPlaceholderText("Enter Black Player's Name");
    playerNameBlackInput->setGeometry(QRect(bxPos, startY - 55, 200, 30));
    playerNameBlackInput->setStyleSheet("border: 2px solid darkcyan;"); 
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
    std::regex validNameRegex("^[A-Za-z0-9_]+$");

    QString playerRedName = playerNameRedInput->text();
    QString playerBlackName = playerNameBlackInput->text();

    if (std::regex_match(playerRedName.toStdString(), validNameRegex) &&
        std::regex_match(playerBlackName.toStdString(), validNameRegex))
    {
        // Numele sunt valide, continuați cu crearea unui joc nou
        setIsNewGame(true);
        emit newGameStarted(playerRedName, playerBlackName);
    }
    else
    {
        QMessageBox::warning(this, "Invalid Names", "Player names can only contain letters.");

    }

    /*setIsNewGame(true);
    emit newGameStarted(playerNameRedInput->text(), playerNameBlackInput->text());*/

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
    settingsButton->setFlag(QGraphicsItem::ItemIsFocusable, false);
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

    emit loadGameStarted();
}



void MainMenu::displayMainMenu() {
    
    playerNameRedInput->show();
    playerNameBlackInput->show();
    playButton->show();
    playButton->enableButton = true;
    playButton->setFlag(QGraphicsItem::ItemIsSelectable, true);
    playButton->setFlag(QGraphicsItem::ItemIsFocusable, true);

    
    loadButton->show();
    loadButton->enableButton = true;
    loadButton->setFlag(QGraphicsItem::ItemIsSelectable, true);
    loadButton->setFlag(QGraphicsItem::ItemIsFocusable, true);

    settingsButton->show();
    settingsButton->enableButton = true;
    settingsButton->setFlag(QGraphicsItem::ItemIsSelectable, true);
    settingsButton->setFlag(QGraphicsItem::ItemIsFocusable, true);

    quitButton->show();
    quitButton->enableButton = true;
    quitButton->setFlag(QGraphicsItem::ItemIsSelectable, true);
    quitButton->setFlag(QGraphicsItem::ItemIsFocusable, true);

    image->show();
    image->setFlag(QGraphicsItem::ItemIsSelectable, true);
    image->setFlag(QGraphicsItem::ItemIsFocusable, true);


}
