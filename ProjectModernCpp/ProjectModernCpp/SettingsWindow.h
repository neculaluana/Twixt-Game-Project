#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QVBoxLayout>

class SettingsWindow : public QDialog
{
	Q_OBJECT
public:

	SettingsWindow(QGraphicsScene* scene,QWidget* parent = nullptr);
	void removeAllItems();

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
	QLabel* labelBoardSize;
	QLabel* labelNumberOfBridges;
	QLabel* labelNumberOfPillars;
	QHBoxLayout* hLayout1;
	QHBoxLayout* hLayout2;
	QHBoxLayout* hLayout3;
	QPushButton* saveButton;
	QPushButton* cancelButton;
	QHBoxLayout* buttonLayout;
	QVBoxLayout* vLayout;
	QWidget* container;
	QGraphicsProxyWidget* proxyContainer;
	QGraphicsRectItem* background;
	QGraphicsScene* scene;

};

#endif //SETTINGSWINDOW_H
