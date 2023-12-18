#include "BoardWindow.h"


BoardWindow::BoardWindow(QGraphicsScene* scene, int width, int height,  Board& b, Player* currentPlayer)
    : m_board{ b }, m_currentPlayer{currentPlayer}
{
	QGraphicsRectItem* board = new QGraphicsRectItem(width/20, height/13, 630, 630);
	board->setBrush(QBrush(Qt::lightGray));
	scene->addItem(board);

    size_t boardSize = b.getBoardSize();
    m_points.resize(boardSize);


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
}/*
void BoardWindow::onButtonClicked()
{
    
    drawLines(s);
}*/
void BoardWindow::drawLines(QGraphicsScene* scene)
{
    std::vector<Bridge> bridges=m_currentPlayer->getBridges();
    for(auto& bridge:bridges)
        for (auto point1 : m_points)
        {
            if (point1->getLine() == bridge.getStartPoint().getCoordinates().first && point1->getColumn() == bridge.getStartPoint().getCoordinates().second)
            {
                for (auto point2 : m_points)
                {
                    if (point2->getLine() == bridge.getEndPoint().getCoordinates().first && point2->getColumn() == bridge.getEndPoint().getCoordinates().second)
                    {
                        BridgeLine* line = new BridgeLine(point1, point2);
                        scene->addItem(line);
                        m_lines.push_back(line);
                    }
                }
            }
            /*if (m_points[i] != nullptr && m_points[i + 1] != nullptr)
                if (m_points[i]->getIsClicked() && m_points[i + 1]->getIsClicked())

                {
                    BridgeLine* line = new BridgeLine(m_points[i], m_points[i + 1]);
                    scene->addItem(line);
                    m_lines.push_back(line);
                }*/
        }

    
    
}

void BoardWindow::onButtonClicked(int x, int y, CircleButton* button)
{
    emit pointAdded(x, y,button);
    drawLines(s);
}
