#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onResultWeather(QNetworkReply *reply);
    void onResultLocation(QNetworkReply *reply);
    void on_btnWeather_clicked();
private:
    Ui::MainWindow *ui;
    void runWeather(QString latitude, QString longitude);
    void getWeatherCurrent(QJsonDocument jsonResponse);
    void getWeatherHours(QJsonDocument jsonResponse);
    QString imagePath(QString mainWeather);
    const QString TEMP = "temp";
    const QString FEELS_LIKE = "feels_like";
    const QString HUMIDITY = "humidity";
    const QString PRESSURE = "pressure";
    const QString WIND_SPEED = "wind_speed";
    const QString DESCRIPTION = "description";
    const QString MAIN = "main";
};
#endif // MAINWINDOW_H
