#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

class SettingsWindow : public QDialog
{
	Q_OBJECT
public:

	SettingsWindow(QWidget* parent = nullptr);

signals:   
	void settingsChanged(int boardSize, int numberOfBridges, int numberOfPillars);

};

