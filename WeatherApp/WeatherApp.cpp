#include "WeatherApp.h"
#include <qlabel.h>

#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
//reminder, set up limiter and tokens for weather API.
WeatherApp::WeatherApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QLineEdit* cityInput = new QLineEdit(this);
    cityInput->setPlaceholderText("Enter city name");
    QPushButton* DisplayButton = new QPushButton("Display Weather", this);
    connect(DisplayButton, &QPushButton::clicked, this, [this, cityInput]() {
        QString city = cityInput->text();
        if (city.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please enter a city name.");
            return;
        }
        weatherBringer(city);
        });

    QLabel* weatherLabel = new QLabel("Weather info will appear here", this);
    }

void weatherBringer(const QString& city) {
    QNetworkAccessManager* manager = n new QNetworkAccessManager();
    QString backendUrl = QString("http://localhost:7001/api/weather?city=%1").arg(city);
    QNetworkRequest request(QUrl(backendUrl));

    QNetworkReply* reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Parse and display weather data
            QString response = reply->readAll();
            qDebug() << "Weather Data:" << response;

            // Example: Show in a QLabel
            weatherLabel->setText(response);
        }
        else {
            qDebug() << "Error:" << reply->errorString();
            QMessageBox::critical(this, "Error", reply->errorString());
        }
        reply->deleteLater();
        });
    }

WeatherApp::~WeatherApp()
{}
