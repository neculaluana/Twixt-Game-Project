#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsScene>

class SettingsWindow : public QDialog
{
	Q_OBJECT
public:

	SettingsWindow(QGraphicsScene* scene,QWidget* parent = nullptr);

signals:   
	void settingsChanged(int boardSize, int numberOfBridges, int numberOfPillars);

};

#endif //SETTINGSWINDOW_H
