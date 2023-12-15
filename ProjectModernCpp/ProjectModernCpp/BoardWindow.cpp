#include "BoardWindow.h"


BoardWindow::BoardWindow(QGraphicsScene* scene, int width, int height, Game& game, Board& b, Player& currentPlayer)
    : m_game(game)
    , m_board(b)
    , m_currentPlayer(currentPlayer)
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

            CircleButton* button = new CircleButton(x, y, 8, nullptr);
            scene->addItem(button);
            m_points.push_back(button);
            std::pair<uint8_t, uint8_t> coords = std::make_pair(i, j);
            connect(button, &CircleButton::clicked, this, &BoardWindow::onButtonClicked);
           
            
        }
    }
    s = scene;
}
void BoardWindow::onButtonClicked()
{

    drawLines(s);
}
void BoardWindow::drawLines(QGraphicsScene* scene)
{
    if (m_points.size() > 1)
    {
        for (size_t i = 0; i < m_points.size() - 1; ++i)
        {
            if (m_points[i] != nullptr && m_points[i + 1] != nullptr)
                if (m_points[i]->getIsClicked() && m_points[i + 1]->getIsClicked())

                {
                    BridgeLine* line = new BridgeLine(m_points[i], m_points[i + 1]);
                    scene->addItem(line);
                    m_lines.push_back(line);
                }
        }

    }
    
}
