#include "WeatherApp.h"
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <qthread.h>

WeatherApp::WeatherApp(QWidget* parent) : QMainWindow(parent), manager(nullptr) {
    qDebug() << "WeatherApp constructor thread:" << QThread::currentThread();
    qDebug() << "WeatherApp thread:" << this->thread();

    // No need to move to another thread
    qDebug() << "WeatherApp thread:" << this->thread();

    // Initialize QNetworkAccessManager
    manager = new QNetworkAccessManager(this); // Now created in the correct thread

    qDebug() << "WeatherApp thread:" << this->thread();
    qDebug() << "Manager created in thread:" << manager->thread();
    ui.setupUi(this);
    ui.lineEdit->setPlaceholderText("Enter city name");
    ui.DisplayButton->setText("Display Weather");
    info = ui.info;
    info->setText("Weather info will appear here");

    connect(ui.DisplayButton, &QPushButton::clicked, this, [this]() {
        qDebug() << "Button clicked!";

        if (!manager) {
            qDebug() << "Manager not yet initialized!";
            return;
        }

        QString city = ui.lineEdit->text();
        if (city.isEmpty()) {
            info->setText("Please enter a city name.");
            return;
        }
        //weatherBringer(city);
        });
}

void WeatherApp::weatherBringer(const QString& city) {
    /*qDebug() << "weatherBringer called with city:" << city;
    qDebug() << "weatherBringer thread:" << QThread::currentThread();

    if (!manager) {
        qWarning() << "NetworkManager is nullptr!";
        return;
    }

    QUrl url(QString("https://localhost:7001/api/weather?city=%1").arg(city));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Origin", "http://localhost:7001");


    // Make the request in the correct thread
    QNetworkReply* reply = manager->get(request);
    qDebug() << "Reply created in thread:" << reply->thread();
    qDebug() << "Reply created:" << reply;

    // Connect to finished signal (make sure it's connected in the right thread)
    QObject::connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QString response = reply->readAll();
            qDebug() << "Response:" << response;

            QString weatherInfo = parseWeatherJson(response);

            updateWeatherLabel(weatherInfo);
        }
        else {
            qDebug() << "Error:" << reply->errorString();
            info->setText("Error fetching weather data!");
        }
        reply->deleteLater();
        });*/
}

QString WeatherApp::parseWeatherJson(const QString& response) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
    if (jsonDoc.isObject()) {
        QJsonObject jsonObj = jsonDoc.object();

        QString name = jsonObj["location"].toObject()["name"].toString();
        double tempC = jsonObj["current"].toObject()["temp_c"].toDouble();
        double tempF = jsonObj["current"].toObject()["temp_f"].toDouble();
        QString conditionText = jsonObj["current"].toObject()["condition"].toObject()["text"].toString();
        double windMph = jsonObj["current"].toObject()["wind_mph"].toDouble();
        int humidity = jsonObj["current"].toObject()["humidity"].toInt();
        int cloud = jsonObj["current"].toObject()["cloud"].toInt();

        return QString(
            "City: %1\n"
            "Temperature: %2°C / %3°F\n"
            "Condition: %4\n"
            "Wind Speed: %5 mph\n"
            "Humidity: %6%%\n"
            "Cloud Coverage: %7%%"
        ).arg(name).arg(tempC).arg(tempF).arg(conditionText).arg(windMph).arg(humidity).arg(cloud);
    }
    else {
        return "Invalid JSON response.";
    }
}

void WeatherApp::updateWeatherLabel(const QString& weatherInfo) {
    /*qDebug() << "Current thread:" << QThread::currentThread();
    if (QThread::currentThread() != this->thread()) {
        QMetaObject::invokeMethod(this, [this, weatherInfo]() {
            info->setText(weatherInfo);
            }, Qt::QueuedConnection);
    }
    else {
        info->setText(weatherInfo);
    }*/
}
WeatherApp::~WeatherApp() {
    qDebug() << "Destroying WeatherApp";
    if (manager) {
        manager->deleteLater();
        manager = nullptr;
    }
}
