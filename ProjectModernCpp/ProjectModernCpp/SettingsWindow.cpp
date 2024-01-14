#include "SettingsWindow.h"



SettingsWindow::SettingsWindow(QGraphicsScene* scene, QWidget* parent) : QDialog(parent) {
    this->scene = scene;
    QFont widgetFont;
    widgetFont.setPointSize(12);

    // Spin Boxes
    boardSize = new QSpinBox(this);
    boardSize->setRange(5, 35);
    boardSize->setValue(24);
    boardSize->setFont(widgetFont);
    boardSize->setFixedSize(150, 50);

    numberOfBridges = new QSpinBox(this);
    numberOfBridges->setRange(1, 70);
    numberOfBridges->setValue(50);
    numberOfBridges->setFont(widgetFont);
    numberOfBridges->setFixedSize(150, 50);

    numberOfPoints = new QSpinBox(this);
    numberOfPoints->setRange(2, 70);
    numberOfPoints->setValue(50);
    numberOfPoints->setFont(widgetFont);
    numberOfPoints->setFixedSize(150, 50);

    // Labels
    labelBoardSize = new QLabel("Board Size:");
    labelBoardSize->setFont(widgetFont);
    labelNumberOfBridges = new QLabel("Number of Bridges per Player:");
    labelNumberOfBridges->setFont(widgetFont);
    labelNumberOfPillars = new QLabel("Number of Points per Player:");
    labelNumberOfPillars->setFont(widgetFont);

    // Horizontal Layouts for Label and Spin Box with Spacers
    hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(labelBoardSize);
    hLayout1->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hLayout1->addWidget(boardSize);

    hLayout2 = new QHBoxLayout();
    hLayout2->addWidget(labelNumberOfBridges);
    hLayout2->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hLayout2->addWidget(numberOfBridges);

    hLayout3 = new QHBoxLayout();
    hLayout3->addWidget(labelNumberOfPillars);
    hLayout3->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hLayout3->addWidget(numberOfPoints);

    // Buttons
    saveButton = new QPushButton("Save");
    saveButton->setFont(widgetFont);
    saveButton->setFixedSize(200, 50);
    cancelButton = new QPushButton("Cancel");
    cancelButton->setFont(widgetFont);
    cancelButton->setFixedSize(200, 50);

    // Horizontal Layout for Buttons with Centering
    buttonLayout = new QHBoxLayout();
    buttonLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    buttonLayout->addWidget(saveButton);
    buttonLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum));  
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // Vertical Layout for the entire window
    vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);
    vLayout->addLayout(buttonLayout);

    // Create a container widget for the layout
    container = new QWidget();
    container->setLayout(vLayout);

    // Add the container widget to the scene using QGraphicsProxyWidget
    proxyContainer = scene->addWidget(container);

    QRectF sceneRect = scene->sceneRect();
    proxyContainer->setPos((sceneRect.width() - container->width()) / 2,
        (sceneRect.height() - container->height()) / 2);

    // Background
    background = new QGraphicsRectItem();
    float backgroundWidth = sceneRect.width() * 0.8;  
    float backgroundHeight = sceneRect.height() * 0.4; 
    float posX = (sceneRect.width() - backgroundWidth) / 2;
    float posY = (sceneRect.height() - backgroundHeight) / 2;
    background->setRect(posX, posY, backgroundWidth, backgroundHeight);
    background->setBrush(QBrush(Qt::darkCyan));
    background->setZValue(-1); 
    scene->addItem(background);

    connect(saveButton, &QPushButton::clicked, this, [this]() {
        int boardSizeValue = boardSize->value();
        int numberOfPointsValue = numberOfPoints->value();
        int numberOfBridgesValue = numberOfBridges->value();
        saveButtonClicked(boardSizeValue, numberOfPointsValue, numberOfBridgesValue);
        });
    
    connect(cancelButton, &QPushButton::clicked, this, &SettingsWindow::cancelButtonClicked);

}

void SettingsWindow::showAllItems()
{
    proxyContainer->show();
    background->show();
}

void SettingsWindow::removeAllItems()
{
    proxyContainer->hide();
    background->hide();
}

void SettingsWindow::saveButtonClicked(int boardSize, int numberOfPoints, int numberOfBridges) {
    emit settingsChanged(boardSize, numberOfPoints, numberOfBridges);
    emit settingsSaved();
    removeAllItems();
}

void SettingsWindow::cancelButtonClicked() {
    emit(settingsCanceled());
    removeAllItems();
}
