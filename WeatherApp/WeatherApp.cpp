#include "WeatherApp.h"
#include <qlabel.h>

WeatherApp::WeatherApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.label_2->setText("chilly");
}

WeatherApp::~WeatherApp()
{}
