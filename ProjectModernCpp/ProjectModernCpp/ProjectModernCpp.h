#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProjectModernCpp.h"

class ProjectModernCpp : public QMainWindow
{
    Q_OBJECT

public:
    ProjectModernCpp(QWidget *parent = nullptr);
    ~ProjectModernCpp();

private:
    Ui::ProjectModernCppClass ui;
};
