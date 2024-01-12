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
    //m_points.resize(boardSize);


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



BoardWindow::BoardWindow(QGraphicsScene* scene, int width, int height, Board& b, Player* currentPlayer, bool loadFromFile)
    : m_board{ b }, m_currentPlayer{ currentPlayer }
{

    QGraphicsRectItem* board = new QGraphicsRectItem(width / 20, height / 13, 630, 630);
    board->setBrush(QBrush(Qt::lightGray));
    scene->addItem(board);

    int boardSize = b.getBoardSize();
    int cellWidth = 630 / boardSize;
    int cellHeight = 630 / boardSize;
    m_currentPlayerText = new QGraphicsTextItem();
    m_currentPlayerText->setPlainText("It is Red's turn");
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
}


void BoardWindow::setCurrentPlayer(Player* current)
{
    drawLines(s);
    m_currentPlayer = current;
}

//bool isBridgesIntersection(CircleButton* existingBridgeStart, CircleButton* existingBridgeEnd, CircleButton* startNewBridge, CircleButton* endNewBridge) {
//    // Check if two points are collinear to p1
//    auto collinear = [](CircleButton* p1, CircleButton* p2, CircleButton* p3) {
//        return (p2->y() - p1->y()) * (p3->x() - p2->x()) == (p3->y() - p2->y()) * (p2->x() - p1->x());
//        };
//
//    // Check the order of the points
//    auto orientation = [](CircleButton* p1, CircleButton* p2, CircleButton* p3) {
//        int val = (p2->y() - p1->y()) * (p3->x() - p2->x()) - (p2->x() - p1->x()) * (p3->y() - p2->y());
//        if (val == 0) return 0;  // Collinear
//        return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
//        };
//
//    // Given three collinear points p, q, r, check if point q lies on line segment 'pr'
//    auto onSegment = [](CircleButton* p, CircleButton* q, CircleButton* r) {
//        if (q->x() <= std::max(p->x(), r->x()) && q->x() >= std::min(p->x(), r->x()) &&
//            q->y() <= std::max(p->y(), r->y()) && q->y() >= std::min(p->y(), r->y()))
//            return true;
//        return false;
//        };
//
//    // Find the four orientations needed for the general and special cases
//    int o1 = orientation(existingBridgeStart, existingBridgeEnd, startNewBridge);
//    int o2 = orientation(existingBridgeStart, existingBridgeEnd, endNewBridge);
//    int o3 = orientation(startNewBridge, endNewBridge, existingBridgeStart);
//    int o4 = orientation(startNewBridge, endNewBridge, existingBridgeEnd);
//
//    // General case
//    if (o1 != o2 && o3 != o4)
//        return true;
//
//    // Special Cases
//    // p1, p2, and p3 are collinear and p3 lies on segment p1p2
//    if (o1 == 0 && onSegment(existingBridgeStart, startNewBridge, existingBridgeEnd)) return true;
//
//    // p1, p2, and p4 are collinear and p4 lies on segment p1p2
//    if (o2 == 0 && onSegment(existingBridgeStart, endNewBridge, existingBridgeEnd)) return true;
//
//    // p3, p4, and p1 are collinear and p1 lies on segment p3p4
//    if (o3 == 0 && onSegment(startNewBridge, existingBridgeStart, endNewBridge)) return true;
//
//    // p3, p4, and p2 are collinear and p2 lies on segment p3p4
//    if (o4 == 0 && onSegment(startNewBridge, existingBridgeEnd, endNewBridge)) return true;
//
//    // Check if the new bridge is collinear with the existing one but not overlapping
//    if (collinear(existingBridgeStart, existingBridgeEnd, startNewBridge) &&
//        collinear(existingBridgeStart, existingBridgeEnd, endNewBridge)) {
//        // Check if both points of the new bridge are outside the existing bridge
//        if (!onSegment(existingBridgeStart, startNewBridge, existingBridgeEnd) &&
//            !onSegment(existingBridgeStart, endNewBridge, existingBridgeEnd)) {
//            return false; // The new bridge is collinear but not intersecting
//        }
//    }
//
//    return false; // No intersection
//}
//
//void BoardWindow::drawLines(QGraphicsScene* scene)
//{
//    if (m_currentPlayer->getColor() == Point::Color::Red)
//        qDebug() << "Desenare linii pentru jucatorul rosu";
//    else
//        if(m_currentPlayer->getColor() == Point::Color::Black)
//        qDebug() << "Desenare linii pentru jucatorul negru";
//
//
//    std::vector<Bridge> bridges = m_currentPlayer->getBridges();
//    for (auto& bridge : bridges) {
//        for (auto point1 : m_points) {
//            if (!point1) {
//                qDebug() << "Punct null detectat";
//                continue;
//            }
//
//            if (point1->getLine() == bridge.getStartPoint().getCoordinates().first &&
//                point1->getColumn() == bridge.getStartPoint().getCoordinates().second) {
//
//                for (auto point2 : m_points) {
//
//                    if (point2 && point2->getLine() == bridge.getEndPoint().getCoordinates().first &&
//                        point2->getColumn() == bridge.getEndPoint().getCoordinates().second) {
//                        bool canDrawBridge = true;
//
//                        for (auto& bridge : m_lines) {
//                               if (isBridgesIntersection(bridge->getStartButton(), bridge->getEndButton(), point1, point2)) {
//                                    canDrawBridge = false;
//                                    break;
//                               }
//                        }
//                        if (canDrawBridge) {
//                            BridgeLine* line = new BridgeLine(point1, point2);
//                            scene->addItem(line);
//                            m_lines.push_back(line);
//                        }
//                    }
//                }
//            }
//        }
//    }
//}

//bool BoardWindow::isBridgesIntersection(CircleButton* existingBridgeStart, CircleButton* existingBridgeEnd, CircleButton* futurePoint1, CircleButton* futurePoint2) {
//    auto linesIntersect = [](const QPoint& p1, const QPoint& p2, const QPoint& p3, const QPoint& p4) -> bool {
//        auto CCW = [](const QPoint& A, const QPoint& B, const QPoint& C) -> bool {
//            return (C.y() - A.y()) * (B.x() - A.x()) > (B.y() - A.y()) * (C.x() - A.x());
//        };
//        return CCW(p1, p3, p4) != CCW(p2, p3, p4) && CCW(p1, p2, p3) != CCW(p1, p2, p4);
//    };
//
//    QPoint p1(existingBridgeStart->getX(), existingBridgeStart->getY());
//    QPoint p2(existingBridgeEnd->getX(), existingBridgeEnd->getY());
//    QPoint p3(futurePoint1->getX(), futurePoint1->getY());
//    QPoint p4(futurePoint2->getX(), futurePoint2->getY());
//
//    return linesIntersect(p1, p2, p3, p4);
//}

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
                            BridgeLine* line = new BridgeLine(point1, point2);
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
    if (!m_currentPlayer->getfirstMoveMade() && m_currentPlayer->getColor() == Point::Color::Red) {
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

}

//void BoardWindow::showNameInputMessage() {
//    bool ok1, ok2;
//    m_playerNameRed = QInputDialog::getText(this, tr("Nume jucător roșu"), tr("Introduceți numele jucătorului roșu:"), QLineEdit::Normal, "", &ok1);
//    m_playerNameBlack = QInputDialog::getText(this, tr("Nume jucător negru"), tr("Introduceți numele jucătorului negru:"), QLineEdit::Normal, "", &ok2);
//
//    if (!ok1 || m_playerNameRed.isEmpty()) {
//        m_playerNameRed = "Player Red";
//    }
//
//    if (!ok2 || m_playerNameBlack.isEmpty()) {
//        m_playerNameBlack = "Player Black";
//    }
//
//    // Actualizarea textului pentru a reflecta numele jucătorilor
//    m_currentPlayerText->setPlainText("Este rândul lui " + m_playerNameRed + ".");
//}