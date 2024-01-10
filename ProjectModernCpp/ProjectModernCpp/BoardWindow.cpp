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

    for (int i = 0; i < boardSize; ++i) {

        for (int j = 0; j < boardSize; ++j) {

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
{
    if (m_currentPlayer->getColor() == Point::Color::Red)
        qDebug() << "Desenare linii pentru jucătorul rosu";
    else
        if(m_currentPlayer->getColor() == Point::Color::Black)
        qDebug() << "Desenare linii pentru jucătorul negru";


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

 
    CircleButton* startButtonTop = m_points[25];
    CircleButton* endButtonTop = m_points[2*boardSize - 2];

    BridgeLine* lineTop = new BridgeLine(startButtonTop, endButtonTop, Qt::red);
    scene->addItem(lineTop);
    m_lines.push_back(lineTop);

    CircleButton* startButtonBottom = m_points[(boardSize - 1) * boardSize + 1]; 
    CircleButton* endButtonBottom = m_points[(boardSize ) * boardSize - 2]; 

    BridgeLine* lineBottom = new BridgeLine(startButtonBottom, endButtonBottom, Qt::red);
    scene->addItem(lineBottom);
    m_lines.push_back(lineBottom);

    CircleButton* startButtonRight = m_points[25];
    CircleButton* endButtonRight = m_points[(boardSize) * boardSize - 23];

    BridgeLine* lineRight = new BridgeLine(startButtonRight, endButtonRight, Qt::red);
    scene->addItem(lineRight);
    m_lines.push_back(lineRight);

    CircleButton* startButtonLeft = m_points[2*boardSize-1];
    CircleButton* endButtonLeft = m_points[(boardSize)*boardSize - 1];

    BridgeLine* lineLeft = new BridgeLine(startButtonLeft, endButtonLeft, Qt::red);
    scene->addItem(lineLeft);
    m_lines.push_back(lineLeft);

}

void BoardWindow::onButtonClicked(int x, int y, CircleButton* button)
{
    emit pointAdded(x, y,button);
    drawLines(s);
}
