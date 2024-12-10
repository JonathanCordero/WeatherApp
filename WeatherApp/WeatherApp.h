#include <QtWidgets/QMainWindow>
#include <QNetworkAccessManager>
#include "ui_WeatherApp.h"
#ifndef WEATHERAPP_H
#define WEATHERAPP_H
#include <QNetworkReply>

class WeatherApp : public QMainWindow
{
    Q_OBJECT

public:
    WeatherApp(QWidget* parent = nullptr);
    ~WeatherApp();

private slots:
    void weatherBringer(const QString& city);
    void updateWeatherLabel(const QString& weatherInfo);

private:
    QNetworkAccessManager* manager;
    Ui::WeatherAppClass ui;
    QLabel* info; // Example label for displaying weather info
    QString parseWeatherJson(const QString& response);
};

#endif // WEATHERAPP_H