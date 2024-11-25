#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WeatherApp.h"

class WeatherApp : public QMainWindow
{
    Q_OBJECT

public:
    WeatherApp(QWidget *parent = nullptr);
    ~WeatherApp();

private:
    Ui::WeatherAppClass ui;
};
