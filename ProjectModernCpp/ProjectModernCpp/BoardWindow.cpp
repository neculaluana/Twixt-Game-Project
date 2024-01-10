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
    int lastRowIndex = boardSize - 1;
    int lastColumnIndex = (boardSize - 1) * boardSize;

    // Calculate the indices of the points you want to use
    int startButtonTopIndex = 0;
    int endButtonTopIndex = lastRowIndex * boardSize - 1;

    int startButtonBottomIndex = lastColumnIndex + 1;
    int endButtonBottomIndex = lastColumnIndex + lastRowIndex - 2;

    int startButtonRightIndex = lastRowIndex;
    int endButtonRightIndex = lastColumnIndex - 23;

    int startButtonLeftIndex = lastRowIndex * 2 - 1;
    int endButtonLeftIndex = lastColumnIndex - 1;

    // Check if the calculated indices are within the valid range
    if (startButtonTopIndex < m_points.size() && endButtonTopIndex < m_points.size() &&
        startButtonBottomIndex < m_points.size() && endButtonBottomIndex < m_points.size() &&
        startButtonRightIndex < m_points.size() && endButtonRightIndex < m_points.size() &&
        startButtonLeftIndex < m_points.size() && endButtonLeftIndex < m_points.size()) {

        CircleButton* startButtonTop = m_points[startButtonTopIndex];
        CircleButton* endButtonTop = m_points[endButtonTopIndex];

        BridgeLine* lineTop = new BridgeLine(startButtonTop, endButtonTop, Qt::red);
        scene->addItem(lineTop);
        m_lines.push_back(lineTop);

        CircleButton* startButtonBottom = m_points[startButtonBottomIndex];
        CircleButton* endButtonBottom = m_points[endButtonBottomIndex];

        BridgeLine* lineBottom = new BridgeLine(startButtonBottom, endButtonBottom, Qt::red);
        scene->addItem(lineBottom);
        m_lines.push_back(lineBottom);

        CircleButton* startButtonRight = m_points[startButtonRightIndex];
        CircleButton* endButtonRight = m_points[endButtonRightIndex];

        BridgeLine* lineRight = new BridgeLine(startButtonRight, endButtonRight, Qt::red);
        scene->addItem(lineRight);
        m_lines.push_back(lineRight);

        CircleButton* startButtonLeft = m_points[startButtonLeftIndex];
        CircleButton* endButtonLeft = m_points[endButtonLeftIndex];

        BridgeLine* lineLeft = new BridgeLine(startButtonLeft, endButtonLeft, Qt::red);
        scene->addItem(lineLeft);
        m_lines.push_back(lineLeft);
    }
    else {
        qDebug() << "Invalid indices for drawing base lines.";
    }
}


void BoardWindow::onButtonClicked(int x, int y, CircleButton* button)
{
    emit pointAdded(x, y,button);
    drawLines(s);
}
