#include "WeatherApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    qputenv("QT_MESSAGE_PATTERN", QByteArray("%{time} [%{type}] %{message}"));
    WeatherApp w;

    w.show();
    return a.exec();
}
