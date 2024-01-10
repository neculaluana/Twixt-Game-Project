#include "SettingsWindow.h"

#include "SettingsWindow.h"
#include <QGraphicsProxyWidget>

SettingsWindow::SettingsWindow(QGraphicsScene* scene, QWidget* parent) : QDialog(parent) {
    QSpinBox* boardSize = new QSpinBox();
    boardSize->setRange(10, 30);
    QSpinBox* numberOfBridges = new QSpinBox();
    numberOfBridges->setRange(1, 10);
    QSpinBox* numberOfPillars = new QSpinBox();
    numberOfPillars->setRange(1, 20);

    QPushButton* saveButton = new QPushButton("Save");
    QPushButton* cancelButton = new QPushButton("Cancel");

    // Adăugarea widget-urilor la scena grafică folosind QGraphicsProxyWidget
    QGraphicsProxyWidget* proxyBoardSize = scene->addWidget(boardSize);
    QGraphicsProxyWidget* proxyNumberOfBridges = scene->addWidget(numberOfBridges);
    QGraphicsProxyWidget* proxyNumberOfPillars = scene->addWidget(numberOfPillars);
    QGraphicsProxyWidget* proxySaveButton = scene->addWidget(saveButton);
    QGraphicsProxyWidget* proxyCancelButton = scene->addWidget(cancelButton);

    // Poziționarea widget-urilor pe scenă
    proxyBoardSize->setPos(50, 50);
    proxyNumberOfBridges->setPos(50, 100);
    proxyNumberOfPillars->setPos(50, 150);
    proxySaveButton->setPos(50, 200);
    proxyCancelButton->setPos(150, 200);

    // Opțional: Adăugarea unui fundal pentru a îmbunătăți vizibilitatea
    QGraphicsRectItem* background = new QGraphicsRectItem(0, 0, 300, 300);
    background->setBrush(QBrush(Qt::lightGray));
    background->setZValue(-1); // Asigură-te că fundalul este în spatele widget-urilor
    scene->addItem(background);
}
