#include "BoardWindow.h"
#include <QDebug>

BoardWindow::BoardWindow(QGraphicsScene* scene, int width, int height,  Board& b, Player* currentPlayer)
    : m_board{ b }
    , m_currentPlayer{currentPlayer}
{
	QGraphicsRectItem* board = new QGraphicsRectItem(width/20, height/13, 630, 630);
	board->setBrush(QBrush(Qt::lightGray));
	scene->addItem(board);

    size_t boardSize = b.getBoardSize();
    //m_points.resize(boardSize);


    int cellWidth = 630 / boardSize;
    int cellHeight = 630 / boardSize;
    m_currentPlayerText = new QGraphicsTextItem();
    m_currentPlayerText->setPlainText("It is Red's turn" + QString::fromStdString(m_currentPlayer->getName()));
    m_currentPlayerText->setDefaultTextColor(Qt::red);
    QFont font("Helvetica", 12);
    QFont font2("Helvetica", 11);
    font.setBold(true);
    font2.setBold(true);
    m_currentPlayerText->setFont(font);
   
    m_currentPlayerText->setPos(30, 10);
    scene->addItem(m_currentPlayerText);

    m_currentPlayerPointsText = new QGraphicsTextItem();
    QString pointsLeft= QString::number(m_currentPlayer->getMaxPointsCount());
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
            connect(button, &CircleButton::clicked, this, [this, i, j,button]() { onButtonClicked(i, j,button); });

            
            
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

bool isBridgesIntersection(CircleButton* existingBridgeStart, CircleButton* existingBridgeEnd, CircleButton* futurePoint1, CircleButton* futurePoint2) {
    //auto orientation = [](CircleButton* a, CircleButton* b, CircleButton* c) {
    //    int val = (b->getY() - a->getY()) * (c->getX() - b->getX()) - (b->getX() - a->getX()) * (c->getY() - b->getY());
    //    if (val == 0) return 0; // Collinear
    //    return (val > 0) ? 1 : 2; // Clockwise or counterclockwise
    //    };

    //auto onSegment = [](CircleButton* p, CircleButton* q, CircleButton* r) {
    //    return q->getX() <= std::max(p->getX(), r->getX()) && q->getX() >= std::min(p->getX(), r->getX()) &&
    //        q->getY() <= std::max(p->getY(), r->getY()) && q->getY() >= std::min(p->getY(), r->getY());
    //    };

    //// Four orientations for the combination of line segment (future bridge) and existing bridge
    //int o1 = orientation(existingBridgeStart, existingBridgeEnd, futurePoint1);
    //int o2 = orientation(existingBridgeStart, existingBridgeEnd, futurePoint2);
    //int o3 = orientation(futurePoint1, futurePoint2, existingBridgeStart);
    //int o4 = orientation(futurePoint1, futurePoint2, existingBridgeEnd);

    //// General case
    //if (o1 != o2 && o3 != o4) return true;

    //// Special cases - existing bridge and one of the points of the potential bridge are collinear
    //if (o1 == 0 && onSegment(existingBridgeStart, futurePoint1, existingBridgeEnd)) return true;
    //if (o2 == 0 && onSegment(existingBridgeStart, futurePoint2, existingBridgeEnd)) return true;

    //// Special cases - potential bridge and one of the points of the existing bridge are collinear
    //if (o3 == 0 && onSegment(futurePoint1, existingBridgeStart, futurePoint2)) return true;
    //if (o4 == 0 && onSegment(futurePoint1, existingBridgeEnd, futurePoint2)) return true;

    //return false; // No intersection

    auto linesIntersect = [](const QPoint& p1, const QPoint& p2, const QPoint& p3, const QPoint& p4) -> bool {
        auto CCW = [](const QPoint& A, const QPoint& B, const QPoint& C) -> bool {
            return (C.y() - A.y()) * (B.x() - A.x()) > (B.y() - A.y()) * (C.x() - A.x());
            };
        return CCW(p1, p3, p4) != CCW(p2, p3, p4) && CCW(p1, p2, p3) != CCW(p1, p2, p4);
        };

    QPoint p1(existingBridgeStart->getX(), existingBridgeStart->getY());
    QPoint p2(existingBridgeEnd->getX(), existingBridgeEnd->getY());
    QPoint p3(futurePoint1->getX(), futurePoint1->getY());
    QPoint p4(futurePoint2->getX(), futurePoint2->getY());

    return linesIntersect(p1, p2, p3, p4);
}

void BoardWindow::drawLines(QGraphicsScene* scene)
{/*

    if (m_currentPlayer->getColor() == Point::Color::Red)
        qDebug() << "Desenare linii pentru jucatorul rosu";
    else
        if(m_currentPlayer->getColor() == Point::Color::Black)
        qDebug() << "Desenare linii pentru jucatorul negru";*/


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
                        bool canDrawBridge = true;

                        for (auto& bridge : m_lines) {
                               if (isBridgesIntersection(bridge->getStartButton(), bridge->getEndButton(), point1, point2)) {
                                    canDrawBridge = false;
                                    break;
                               }
                        }
                        if (canDrawBridge) {
                            BridgeLine* line = new BridgeLine(point1, point2);
                            scene->addItem(line);
                            m_lines.push_back(line);
                        }
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

    BaseLine* leftLine = new BaseLine(m_points[firstRowIndex +boardSize- 2], m_points[firstColumnIndex + (boardSize - 3)], Qt::black,nullptr,0); // Index is 0-based
    scene->addItem(leftLine);

    BaseLine* topLine = new BaseLine(m_points[firstColumnIndex-1], m_points[firstRowIndex + boardSize * (boardSize - 1) - 3], Qt::red,nullptr,0);
    scene->addItem(topLine);

    BaseLine* bottomLine = new BaseLine(m_points[boardSize - 3], m_points[lastRowIndex + boardSize * (boardSize - 2) - 2], Qt::red,nullptr,1);
    scene->addItem(bottomLine);

    BaseLine* rightLine = new BaseLine(m_points[firstRowIndex+boardSize*(boardSize-2)-3], m_points[lastRowIndex + boardSize*(boardSize-2)-2], Qt::black,nullptr,1); // Index is 0-based
    scene->addItem(rightLine);
    
}

void BoardWindow::showMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Schimbă Piesele");
    msgBox.setText("Al doilea jucător, dorești să preiei piesele roșii?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int result = msgBox.exec();

    if (result == QMessageBox::Yes) {
        emit requestPlayerChange();
    }
}


void BoardWindow::onButtonClicked(int x, int y, CircleButton* button)
{
    if (!m_currentPlayer->getfirstMoveMade() && m_currentPlayer->getColor() == Point::Color::Red) {
        QTimer::singleShot(1000, this, &BoardWindow::showMessage);
   

        m_currentPlayer->setfirstMoveMade(true);
    }
    else if(m_currentPlayer->getColor()==Point::Color::Black && m_currentPlayer->getfirstMoveMade() == false)
    {
        m_currentPlayer->setfirstMoveMade(true);
    }
    emit pointAdded(x, y, button);
    drawLines(s);

   
    if (m_currentPlayer->getColor() == Point::Color::Red)
    {
        m_currentPlayerText->setPlainText("It is Red's turn"+ QString::fromStdString(m_currentPlayer->getName()));

        m_currentPlayerText->setDefaultTextColor(Qt::red);
        m_currentPlayerPointsText->setDefaultTextColor(Qt::red);
        int pointsSize = m_currentPlayer->getPointsSize();
        int maxPoints = m_currentPlayer->getMaxPointsCount();
        m_currentPlayerPointsText->setPlainText("Points left: " + QString::number(maxPoints-pointsSize));

        m_currentPlayerBridgesText->setDefaultTextColor(Qt::red);
        int bridgesSize = m_currentPlayer->getBridgesSize();
        int maxBridges = m_currentPlayer->getMaxBridgesCount();
        m_currentPlayerBridgesText->setPlainText("Bridges left: " + QString::number(maxBridges - bridgesSize));
    }
    else
    {
        m_currentPlayerText->setPlainText("It is Black's turn"+ QString::fromStdString(m_currentPlayer->getName()));

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
