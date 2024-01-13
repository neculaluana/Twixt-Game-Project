#include "BoardWindow.h"
#include <QDebug>

BoardWindow::BoardWindow(QGraphicsScene* scene, int width, int height, Board& b, Player* currentPlayer)
    : m_board{ b }
    , m_currentPlayer{ currentPlayer }
{
    QGraphicsRectItem* board = new QGraphicsRectItem(width / 20, height / 13, 630, 630);
    board->setBrush(QBrush(Qt::lightGray));
    scene->addItem(board);

    size_t boardSize = b.getBoardSize();


    int cellWidth = 630 / boardSize;
    int cellHeight = 630 / boardSize;

    m_currentPlayerText = new QGraphicsTextItem();
    m_currentPlayerText->setPlainText("It is Red's turn: " + QString::fromStdString(m_currentPlayer->getName()));
    m_currentPlayerText->setDefaultTextColor(Qt::red);
    QFont font("Helvetica", 12);
    QFont font2("Helvetica", 11);
    font.setBold(true);
    font2.setBold(true);
    m_currentPlayerText->setFont(font);

    m_currentPlayerText->setPos(30, 10);
    scene->addItem(m_currentPlayerText);

    m_currentPlayerPointsText = new QGraphicsTextItem();
    QString pointsLeft = QString::number(m_currentPlayer->getMaxPointsCount());
    m_currentPlayerPointsText->setPlainText("Points left:   " + pointsLeft);
    m_currentPlayerPointsText->setDefaultTextColor(Qt::red);
    m_currentPlayerPointsText->setFont(font2);
    m_currentPlayerPointsText->setPos(550, 4);
    scene->addItem(m_currentPlayerPointsText);

    m_currentPlayerBridgesText = new QGraphicsTextItem();
    QString bridgesLeft = QString::number(m_currentPlayer->getMaxBridgesCount());
    m_currentPlayerBridgesText->setPlainText("Bridges left: " + bridgesLeft);
    m_currentPlayerBridgesText->setDefaultTextColor(Qt::red);
    m_currentPlayerBridgesText->setFont(font2);
    m_currentPlayerBridgesText->setPos(550, 25);
    scene->addItem(m_currentPlayerBridgesText);

    saveButton = new QPushButton("Save game", nullptr);
    int buttonWidth = 100;
    int buttonHeight = 30;
    int margin = 10;
    saveButton->setGeometry((width - buttonWidth) / 2, margin, buttonWidth, buttonHeight);
    scene->addWidget(saveButton);
    connect(saveButton, &QPushButton::clicked, this, &BoardWindow::onSaveGameClicked);

    for (int i = 0; i < boardSize; ++i) {

        for (int j = 0; j < boardSize; ++j) {

            bool isCorner = (i == 0 && j == 0) || // Top-left corner
                (i == 0 && j == boardSize - 1) || // Top-right corner
                (i == boardSize - 1 && j == 0) || // Bottom-left corner
                (i == boardSize - 1 && j == boardSize - 1); // Bottom-right corner

            if (isCorner) {
                continue;
            }

            int x = width / 20 + i * cellWidth + cellWidth / 2;
            int y = height / 13 + j * cellHeight + cellHeight / 2;

            CircleButton* button = new CircleButton(x, y, i, j, 8, nullptr, currentPlayer);

            scene->addItem(button);
            m_points.push_back(button);
            std::pair<uint8_t, uint8_t> coords = std::make_pair(i, j);
            connect(button, &CircleButton::clicked, this, [this, i, j, button]() { onButtonClicked(i, j, button); });



        }
    }
    s = scene;
    drawBaseLines(scene);

}



BoardWindow::BoardWindow(QGraphicsScene* scene, int width, int height, Board& b, Player* currentPlayer, bool loadFromFile, Player* otherPlayer)
    : m_board{ b }, m_currentPlayer{ currentPlayer }
{

    QGraphicsRectItem* board = new QGraphicsRectItem(width / 20, height / 13, 630, 630);
    board->setBrush(QBrush(Qt::lightGray));
    scene->addItem(board);

    int boardSize = b.getBoardSize();
    int cellWidth = 630 / boardSize;
    int cellHeight = 630 / boardSize;
    m_currentPlayerText = new QGraphicsTextItem();
    if (m_currentPlayer->getColor() == Point::Color::Red)
    {
        m_currentPlayerText->setPlainText("It is Red's turn: " + QString::fromStdString(m_currentPlayer->getName()));
        m_currentPlayerText->setDefaultTextColor(Qt::red);

    }
    else
    {
        m_currentPlayerText->setPlainText("It is Black's turn: " + QString::fromStdString(m_currentPlayer->getName()));
        m_currentPlayerText->setDefaultTextColor(Qt::black);

    }
    QFont font("Helvetica", 12);
    QFont font2("Helvetica", 11);
    font.setBold(true);
    font2.setBold(true);
    m_currentPlayerText->setFont(font);

    m_currentPlayerText->setPos(30, 10);
    scene->addItem(m_currentPlayerText);

    m_currentPlayerPointsText = new QGraphicsTextItem();
    int pointsSize = m_currentPlayer->getPointsSize();
    int maxPoints = m_currentPlayer->getMaxPointsCount();
    m_currentPlayerPointsText->setPlainText("Points left: " + QString::number(maxPoints - pointsSize));
    if (m_currentPlayer->getColor() == Point::Color::Red)
    {
        m_currentPlayerPointsText->setDefaultTextColor(Qt::red);
    }
    if (m_currentPlayer->getColor() == Point::Color::Black)
    {
        m_currentPlayerPointsText->setDefaultTextColor(Qt::black);
    }
    m_currentPlayerPointsText->setFont(font2);
    m_currentPlayerPointsText->setPos(550, 4);
    scene->addItem(m_currentPlayerPointsText);

    m_currentPlayerBridgesText = new QGraphicsTextItem();
    int bridgesSize = m_currentPlayer->getBridgesSize();
    int maxBridges = m_currentPlayer->getMaxBridgesCount();
    m_currentPlayerBridgesText->setPlainText("Bridges left: " + QString::number(maxBridges - bridgesSize)); 
    if (m_currentPlayer->getColor() == Point::Color::Red)
    {
        m_currentPlayerBridgesText->setDefaultTextColor(Qt::red);
    }
    if (m_currentPlayer->getColor() == Point::Color::Black)
    {
        m_currentPlayerBridgesText->setDefaultTextColor(Qt::black);
    }
    m_currentPlayerBridgesText->setFont(font2);
    m_currentPlayerBridgesText->setPos(550, 25);
    scene->addItem(m_currentPlayerBridgesText);



    saveButton = new QPushButton("Save game", nullptr);
    int buttonWidth = 100;
    int buttonHeight = 30;
    int margin = 10;
    saveButton->setGeometry((width - buttonWidth) / 2, margin, buttonWidth, buttonHeight);
    scene->addWidget(saveButton);
    connect(saveButton, &QPushButton::clicked, this, &BoardWindow::onSaveGameClicked);
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {

            bool isCorner = (i == 0 && j == 0) || // Top-left corner
                (i == 0 && j == boardSize - 1) || // Top-right corner
                (i == boardSize - 1 && j == 0) || // Bottom-left corner
                (i == boardSize - 1 && j == boardSize - 1); // Bottom-right corner

            if (isCorner) {
                continue;
            }


            int x = width / 20 + i * cellWidth + cellWidth / 2;
            int y = height / 13 + j * cellHeight + cellHeight / 2;

            CircleButton* button = new CircleButton(x, y, i, j, 8, nullptr, currentPlayer);
            button->setIsClicked(true);
            scene->addItem(button);
            m_points.push_back(button);

            if (loadFromFile) {
                auto cellStatus = b.getStatus({ i, j });
                if (cellStatus == Board::Status::PlayerRed) {
                    button->updateColor(Point::Color::Red);
                }
                else if (cellStatus == Board::Status::PlayerBlack) {
                    button->updateColor(Point::Color::Black);
                }
            }

            connect(button, &CircleButton::clicked, this, [this, i, j, button]() {
                onButtonClicked(i, j, button);
                });
        }
    }
    s = scene;
    drawBaseLines(scene);
    drawLines(scene);

    m_currentPlayer = otherPlayer;
    drawLines(scene);

    m_currentPlayer = currentPlayer;

    for (auto& p : m_points)
    {
        qDebug() <<"point:"<< p->getLine() << " " << p->getColumn();
    }
    for (auto& b : m_lines)
    {
        qDebug() << "bridge:" << b->getStartButton()->getLine() << " " << b->getStartButton()->getColumn() << " si " << b->getEndButton()->getLine() << " " << b->getEndButton()->getColumn();
    }
}


void BoardWindow::setCurrentPlayer(Player* current)
{
    drawLines(s);
    m_currentPlayer = current;
}

void BoardWindow::drawLines(QGraphicsScene* scene)
{
    std::vector<Bridge> bridges = m_currentPlayer->getBridges();
    for (auto& bridge : bridges) {
        for (auto point1 : m_points) {
            if (!point1) {
                qDebug() << "Punct null detectat";
                continue;
            }

            if (point1->getLine() == bridge.getStartPoint().getCoordinates().first &&
                point1->getColumn() == bridge.getStartPoint().getCoordinates().second) {

                for (auto point2 : m_points) {

                    if (point2 && point2->getLine() == bridge.getEndPoint().getCoordinates().first &&
                        point2->getColumn() == bridge.getEndPoint().getCoordinates().second) {
                        QColor currentPlayerColor;
                        if (m_currentPlayer->getColor() == Point::Color::Red)
                            currentPlayerColor = Qt::red;
                        else
                            currentPlayerColor = Qt::black;
                            BridgeLine* line = new BridgeLine(point1, point2, currentPlayerColor);
                            connect(line, &BridgeLine::bridgeClicked, this, &BoardWindow::handleBridgeLineClicked);
                            scene->addItem(line);
                            m_lines.push_back(line);
                    }
                }
            }
        }
    }
}

void BoardWindow::drawBaseLines(QGraphicsScene* scene)
{
    int boardSize = m_board.getBoardSize();
    int firstRowIndex = 1;
    int lastRowIndex = boardSize - 2;

    int firstColumnIndex = boardSize;
    int lastColumnIndex = boardSize * (boardSize - 2);

    BaseLine* leftLine = new BaseLine(m_points[firstRowIndex + boardSize - 2], m_points[firstColumnIndex + (boardSize - 3)], Qt::black, nullptr, 0); // Index is 0-based
    scene->addItem(leftLine);

    BaseLine* topLine = new BaseLine(m_points[firstColumnIndex - 1], m_points[firstRowIndex + boardSize * (boardSize - 1) - 3], Qt::red, nullptr, 0);
    scene->addItem(topLine);

    BaseLine* bottomLine = new BaseLine(m_points[boardSize - 3], m_points[lastRowIndex + boardSize * (boardSize - 2) - 2], Qt::red, nullptr, 1);
    scene->addItem(bottomLine);

    BaseLine* rightLine = new BaseLine(m_points[firstRowIndex + boardSize * (boardSize - 2) - 3], m_points[lastRowIndex + boardSize * (boardSize - 2) - 2], Qt::black, nullptr, 1); // Index is 0-based
    scene->addItem(rightLine);

}

void BoardWindow::showMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Switch sides");
    msgBox.setText("Player Black, do you wish to take over the pieces of Player Red?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int result = msgBox.exec();

    if (result == QMessageBox::Yes) {
        emit requestPlayerChange();
    }
}


void BoardWindow::onButtonClicked(int x, int y, CircleButton* button)
{
    if (!m_currentPlayer->getfirstMoveMade() && m_currentPlayer->getColor() == Point::Color::Red&&m_currentPlayer->getPoints().size()<2) {
        QTimer::singleShot(500, this, &BoardWindow::showMessage);


        m_currentPlayer->setfirstMoveMade(true);
    }
    else if (m_currentPlayer->getColor() == Point::Color::Black && m_currentPlayer->getfirstMoveMade() == false)
    {
        m_currentPlayer->setfirstMoveMade(true);
    }
    emit pointAdded(x, y, button);
    drawLines(s);



    if (m_currentPlayer->getColor() == Point::Color::Red)
    {
        m_currentPlayerText->setPlainText("It is Red's turn: " + QString::fromStdString(m_currentPlayer->getName()));

        m_currentPlayerText->setDefaultTextColor(Qt::red);
        m_currentPlayerPointsText->setDefaultTextColor(Qt::red);
        int pointsSize = m_currentPlayer->getPointsSize();
        int maxPoints = m_currentPlayer->getMaxPointsCount();
        m_currentPlayerPointsText->setPlainText("Points left: " + QString::number(maxPoints - pointsSize));

        m_currentPlayerBridgesText->setDefaultTextColor(Qt::red);
        int bridgesSize = m_currentPlayer->getBridgesSize();
        int maxBridges = m_currentPlayer->getMaxBridgesCount();
        m_currentPlayerBridgesText->setPlainText("Bridges left: " + QString::number(maxBridges - bridgesSize));
    }
    else
    {
        m_currentPlayerText->setPlainText("It is Black's turn: " + QString::fromStdString(m_currentPlayer->getName()));

        m_currentPlayerText->setDefaultTextColor(Qt::black);

        m_currentPlayerPointsText->setDefaultTextColor(Qt::black);
        int pointsSize = m_currentPlayer->getPointsSize();
        int maxPoints = m_currentPlayer->getMaxPointsCount();
        m_currentPlayerPointsText->setPlainText("Points left: " + QString::number(maxPoints - pointsSize));

        m_currentPlayerBridgesText->setDefaultTextColor(Qt::black);
        int bridgesSize = m_currentPlayer->getBridgesSize();
        int maxBridges = m_currentPlayer->getMaxBridgesCount();
        m_currentPlayerBridgesText->setPlainText("Bridges left: " + QString::number(maxBridges - bridgesSize));

    }
    int pointsSize = m_currentPlayer->getPointsSize();
    int maxPoints = m_currentPlayer->getMaxPointsCount();

    if (maxPoints - pointsSize == 0)
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Draw");
        msgBox.setText("The players have reached the maximum number of points"); 
        msgBox.addButton("Quit", QMessageBox::AcceptRole);

        if (msgBox.exec() == QMessageBox::AcceptRole) {
            QApplication::quit(); 
        }
    }

    int bridgesSize = m_currentPlayer->getBridgesSize();
    int maxBridges = m_currentPlayer->getMaxBridgesCount();

    if (maxBridges - bridgesSize == 0)
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Draw");
        msgBox.setText("The players have reached the maximum number of bridges");
        msgBox.addButton("Quit", QMessageBox::AcceptRole);

        if (msgBox.exec() == QMessageBox::AcceptRole) {
            QApplication::quit();
        }
    }

}

void BoardWindow::handleBridgeLineClicked(BridgeLine* line) {
    if (!line) return;

    QColor currentPlayerColor;

    if (m_currentPlayer->getColor() == Point::Color::Red)
        currentPlayerColor = Qt::red;
    else
        currentPlayerColor = Qt::black;

    if (line->getIsClicked() && currentPlayerColor == line->getColor()) {
        s->removeItem(line);
        m_lines.erase(std::remove(m_lines.begin(), m_lines.end(), line), m_lines.end());

        std::vector<Bridge> bridges = m_currentPlayer->getBridges();
        for (const auto& bridge : bridges)
        {
            if (bridge.getStartPoint().getCoordinates().first == line->getStartButton()->getLine() && bridge.getStartPoint().getCoordinates().second == line->getStartButton()->getColumn() &&
                bridge.getEndPoint().getCoordinates().first == line->getEndButton()->getLine() && bridge.getEndPoint().getCoordinates().second == line->getEndButton()->getColumn())
                m_currentPlayer->removeBridge(bridge);
        }

        delete line;
    }
}
