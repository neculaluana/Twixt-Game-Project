#include "BoardWindow.h"
#include <QDebug>

BoardWindow::BoardWindow(QGraphicsScene* scene, int width, int height,  Board& b, Player* currentPlayer)
    : m_board{ b }, m_currentPlayer{currentPlayer}
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
}

void BoardWindow::onButtonClicked(int x, int y, CircleButton* button)
{
    emit pointAdded(x, y,button);
    drawLines(s);
}
