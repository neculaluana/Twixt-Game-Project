#include "SettingsWindow.h"

#include "SettingsWindow.h"
#include <QGraphicsProxyWidget>

#include "SettingsWindow.h"
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "SettingsWindow.h"
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QVBoxLayout>

SettingsWindow::SettingsWindow(QGraphicsScene* scene, QWidget* parent) : QDialog(parent) {
    QFont widgetFont;
    widgetFont.setPointSize(12);

    // Spin Boxes
    QSpinBox* boardSize = new QSpinBox();
    boardSize->setRange(5, 100);
    boardSize->setValue(24);
    boardSize->setFont(widgetFont);
    boardSize->setFixedSize(150, 50);

    QSpinBox* numberOfBridges = new QSpinBox();
    numberOfBridges->setRange(1, 100);
    numberOfBridges->setValue(50);
    numberOfBridges->setFont(widgetFont);
    numberOfBridges->setFixedSize(150, 50);

    QSpinBox* numberOfPoints = new QSpinBox();
    numberOfPoints->setRange(1, 100);
    numberOfPoints->setValue(10);
    numberOfPoints->setFont(widgetFont);
    numberOfPoints->setFixedSize(150, 50);

    // Labels
    QLabel* labelBoardSize = new QLabel("Board Size:");
    labelBoardSize->setFont(widgetFont);
    QLabel* labelNumberOfBridges = new QLabel("Number of Bridges:");
    labelNumberOfBridges->setFont(widgetFont);
    QLabel* labelNumberOfPillars = new QLabel("Number of Pillars:");
    labelNumberOfPillars->setFont(widgetFont);

    // Horizontal Layouts for Label and Spin Box with Spacers
    QHBoxLayout* hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(labelBoardSize);
    hLayout1->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hLayout1->addWidget(boardSize);

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->addWidget(labelNumberOfBridges);
    hLayout2->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hLayout2->addWidget(numberOfBridges);

    QHBoxLayout* hLayout3 = new QHBoxLayout();
    hLayout3->addWidget(labelNumberOfPillars);
    hLayout3->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hLayout3->addWidget(numberOfPoints);

    // Buttons
    QPushButton* saveButton = new QPushButton("Save");
    saveButton->setFont(widgetFont);
    saveButton->setFixedSize(200, 50);
    QPushButton* cancelButton = new QPushButton("Cancel");
    cancelButton->setFont(widgetFont);
    cancelButton->setFixedSize(200, 50);

    // Horizontal Layout for Buttons with Centering
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    buttonLayout->addWidget(saveButton);
    buttonLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum));  // Fixed spacer for separating buttons
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // Vertical Layout for the entire window
    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);
    vLayout->addLayout(buttonLayout);

    // Create a container widget for the layout
    QWidget* container = new QWidget();
    container->setLayout(vLayout);

    // Add the container widget to the scene using QGraphicsProxyWidget
    QGraphicsProxyWidget* proxyContainer = scene->addWidget(container);

    QRectF sceneRect = scene->sceneRect();
    proxyContainer->setPos((sceneRect.width() - container->width()) / 2,
        (sceneRect.height() - container->height()) / 2);

    // Background
    QGraphicsRectItem* background = new QGraphicsRectItem();
    float backgroundWidth = sceneRect.width() * 0.8;  
    float backgroundHeight = sceneRect.height() * 0.4; 
    float posX = (sceneRect.width() - backgroundWidth) / 2;
    float posY = (sceneRect.height() - backgroundHeight) / 2;
    background->setRect(posX, posY, backgroundWidth, backgroundHeight);
    background->setBrush(QBrush(Qt::darkCyan));
    background->setZValue(-1); 
    scene->addItem(background);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked(boardSize,numberOfPoints,numberOfBridges)));

}

void SettingsWindow::saveButtonClicked(QSpinBox* boardSize, QSpinBox* numberOfPoints, QSpinBox* numberOfBridges) {
    emit settingsChanged(boardSize->value(), numberOfBridges->value(), numberOfPoints->value());
}
