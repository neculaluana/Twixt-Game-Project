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

public slots:
	void saveButtonClicked(QSpinBox* boardSize, QSpinBox* numberOfPoints, QSpinBox* numberOfBridges);
signals:   
	void settingsChanged(int boardSize, int numberOfBridges, int numberOfPillars);

};

#endif //SETTINGSWINDOW_H
