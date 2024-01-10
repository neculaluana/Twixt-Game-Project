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
	void saveButtonClicked(int boardSize, int numberOfPoints, int numberOfBridges);
	void cancelButtonClicked();
signals:   
	void settingsSaved();
	void settingsCanceled();
	void settingsChanged(int boardSize, int numberOfBridges, int numberOfPillars);
private:
	QSpinBox* boardSize;
	QSpinBox* numberOfPoints;
	QSpinBox* numberOfBridges;

};

#endif //SETTINGSWINDOW_H
