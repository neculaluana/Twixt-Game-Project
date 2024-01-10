#include "SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget* parent) : QDialog(parent) {
    QSpinBox* boardSize = new QSpinBox(this);
    boardSize->setRange(10, 30);
    QSpinBox* numberOfBridges = new QSpinBox(this);
    numberOfBridges->setRange(1, 10);
    QSpinBox* numberOfPillars = new QSpinBox(this);
    numberOfPillars->setRange(1, 20);

    QPushButton* saveButton = new QPushButton("Save", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);

    connect(saveButton, &QPushButton::clicked, this, &SettingsWindow::accept);
    connect(cancelButton, &QPushButton::clicked, this, &SettingsWindow::reject);

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("Dimensiunea tablei de joc:", boardSize);
    formLayout->addRow("Numărul de poduri:", numberOfBridges);
    formLayout->addRow("Numărul de piloni:", numberOfPillars);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
}