#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnWeather_clicked()
{
    QNetworkAccessManager *managerlocation = new QNetworkAccessManager(this);
    connect(managerlocation, &QNetworkAccessManager::finished, this, &MainWindow::onResultLocation);

    QUrlQuery queryLocation;
    QString keyLocation = "1c4df264fd1fa4";
    QString cityName = ui->leLocation->text();

    queryLocation.addQueryItem("key", keyLocation);
    queryLocation.addQueryItem("q", cityName);
    queryLocation.addQueryItem("format", "json");

    QUrl urlLocation("https://eu1.locationiq.com/v1/search.php");
    urlLocation.setQuery(queryLocation);

    qDebug()<< "url hour: "<< urlLocation.toString(QUrl::FullyEncoded);
    managerlocation->get(QNetworkRequest(urlLocation));
}

void MainWindow::runWeather(QString latitude, QString longitude)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onResultWeather);

    QString privateAPI = "87497cc97ac7aa0361a5c71b31173ef3";

    QUrlQuery query;
    query.addQueryItem("lat", latitude);
    query.addQueryItem("lon", longitude);
    query.addQueryItem("exclude", "daily");
    query.addQueryItem("appid", privateAPI);

    QUrl url("https://api.openweathermap.org/data/2.5/onecall");
    url.setQuery(query);

    qDebug()<< "url: "<< url.toString(QUrl::FullyEncoded);
    manager->get(QNetworkRequest(url));
}


void MainWindow::onResultWeather(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError){
        QByteArray result = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
        getWeatherCurrent(jsonResponse);
        getWeatherHours(jsonResponse);
    }else{
        qDebug()<<"Error";
        QMessageBox msgWarning;
        msgWarning.setText("Warning!\n Error");
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Caution");
        msgWarning.exec();
    }
    reply->deleteLater();
}

void MainWindow::onResultLocation(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError){
        QByteArray result = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(result);

        QJsonArray array = jsonResponse.array();
        QString longitude = array.at(0).toObject().value("lon").toString();
        QString latitude = array.at(0).toObject().value("lat").toString();

        qDebug()<<"long "<<longitude;
        qDebug()<<"la "<<latitude;
        runWeather(latitude, longitude);
    }else{
        qDebug()<<"Error";
        QMessageBox msgWarning;
        msgWarning.setText("Warning!\n Error");
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Caution");
        msgWarning.exec();
    }
    reply->deleteLater();
}

void MainWindow::getWeatherCurrent(QJsonDocument jsonResponse)
{
    QJsonObject obj = jsonResponse.object();

    QJsonValue current = obj["current"].toObject();
    int temp = current[TEMP].toDouble() - 273.15;
    int feels_like = current[FEELS_LIKE].toDouble() - 273.15;
    uint pressure = current[PRESSURE].toInt();
    uint humidity = current[HUMIDITY].toInt();
    double wind_speed = current[WIND_SPEED].toDouble();

    QJsonArray weather = current["weather"].toArray();
    QString description = weather.at(0).toObject().value(DESCRIPTION).toString();
    QString mainWeather = weather.at(0).toObject().value(MAIN).toString();

    QPixmap img(imagePath(mainWeather));
    ui->lbImageCurrently->setPixmap(img);

    ui->lbTemp_2->setText(QString::number(temp)+"°C");
    ui->lbFeelsLike_2->setText(QString::number(feels_like)+"°C");
    ui->lbHumidity_2->setText(QString::number(humidity)+"%");
    ui->lbPressure_2->setText(QString::number(pressure)+"P");
    ui->lbWindSpeed_2->setText(QString::number(wind_speed)+"m/s");
    ui->lbStatus->setText(description.toUpper());
}

void MainWindow::getWeatherHours(QJsonDocument jsonResponse)
{
    QJsonObject obj = jsonResponse.object();
    QJsonArray current = obj["hourly"].toArray();

    QJsonValue hourZero = current.at(0);
    QJsonValue hourOne = current.at(1);
    QJsonValue hourTwo = current.at(2);

    ////////////////
    /// \brief HourZero
    ///
    int tempHourZero = hourZero.toObject().value(TEMP).toDouble() - 273.15;
    int feels_like_hour_zero = hourZero.toObject().value(FEELS_LIKE).toDouble() - 273.15;
    uint humidityHourZero = hourZero.toObject().value(HUMIDITY).toInt();

    QJsonArray weatherHourZero = hourZero.toObject().value("weather").toArray();
    QString descriptionHourZero = weatherHourZero.at(0).toObject().value(DESCRIPTION).toString();
    QString mainHourZero = weatherHourZero.at(0).toObject().value(MAIN).toString();
    QPixmap imgHourZero(imagePath(mainHourZero));
    ui->lbHour0Image->setPixmap(imgHourZero);
    ui->lbHour0Info->setText(descriptionHourZero.toUpper()+"\nTemp: "+QString::number(tempHourZero)+"°C\n"+"Feels like: "+QString::number(feels_like_hour_zero)+"°C\n"+"Humidity: "+QString::number(humidityHourZero)+"%");

    ////////////////
    /// \brief HourOne
    ///
    int tempHourOne = hourOne.toObject().value(TEMP).toDouble() - 273.15;
    int feels_like_hour_one = hourOne.toObject().value(FEELS_LIKE).toDouble() - 273.15;
    uint humidityHourOne = hourOne.toObject().value(HUMIDITY).toInt();

    QJsonArray weatherHourOne = hourOne.toObject().value("weather").toArray();
    QString descriptionHourOne = weatherHourOne.at(0).toObject().value(DESCRIPTION).toString();
    QString mainHourOne = weatherHourOne.at(0).toObject().value(MAIN).toString();
    QPixmap imgHourOne(imagePath(mainHourOne));
    ui->lbHour1Image->setPixmap(imgHourOne);
    ui->lbHour1Info->setText(descriptionHourOne.toUpper()+"\nTemp: "+QString::number(tempHourOne)+"°C\n"+"Feels like: "+QString::number(feels_like_hour_one)+"°C\n"+"Humidity: "+QString::number(humidityHourOne)+"%");

    ///////////////
    /// \brief HourTwo
    ///
    int tempHourTwo = hourTwo.toObject().value(TEMP).toDouble() - 273.15;
    int feels_like_hour_two = hourTwo.toObject().value(FEELS_LIKE).toDouble() - 273.15;
    uint humidityHourTwo = hourTwo.toObject().value(HUMIDITY).toInt();

    QJsonArray weatherHourTwo = hourTwo.toObject().value("weather").toArray();
    QString descriptionHourTwo = weatherHourTwo.at(0).toObject().value(DESCRIPTION).toString();
    QString mainHourTwo = weatherHourTwo.at(0).toObject().value(MAIN).toString();
    QPixmap imgHourTwo(imagePath(mainHourTwo));
    ui->lbHour2Image->setPixmap(imgHourTwo);
    ui->lbHour2Info->setText(descriptionHourTwo.toUpper()+"\nTemp: "+QString::number(tempHourTwo)+"°C\n"+"Feels like: "+QString::number(feels_like_hour_two)+"°C\n"+"Humidity: "+QString::number(humidityHourTwo)+"%");

}

QString MainWindow::imagePath(QString mainWeather)
{
    if(mainWeather.toLower().contains("rain") || mainWeather.toLower().contains("storm")){
        return QDir::currentPath()+"/Icon Weather/Rainin_big.png";
    }else if(mainWeather.toLower().contains("clouds")){
        return QDir::currentPath()+"/Icon Weather/Cloudy_big.png";
    }else if(mainWeather.toLower().contains("clouds sunny")){
        return QDir::currentPath()+"/Icon Weather/Cloudy_Sunny_big.png.png";
    }else if(mainWeather.toLower().contains("foggy")){
        return QDir::currentPath()+"/Icon Weather/Foggy_big.png";
    }else if(mainWeather.toLower().contains("foggy cloud")){
        return QDir::currentPath()+"/Icon Weather/Foggy_Cloud_big.png";
    }else if(mainWeather.toLower().contains("lightning")){
        return QDir::currentPath()+"/Icon Weather/Lightning_big.png";
    }else if(mainWeather.toLower().contains("lightning cloud")){
        return QDir::currentPath()+"/Icon Weather/Lightning_Cloudy_big.png";
    }else if(mainWeather.toLower().contains("moon") || mainWeather.toLower().contains("clear")){
        return QDir::currentPath()+"/Icon Weather/Moon_big.png";
    }else if(mainWeather.toLower().contains("raining moon")){
        return QDir::currentPath()+"/Icon Weather/Raining_Moon_big.png";
    }else if(mainWeather.toLower().contains("raining sun")){
        return QDir::currentPath()+"/Icon Weather/Raining_Sun_big.png";
    }else if(mainWeather.toLower().contains("snow clody")){
        return QDir::currentPath()+"/Icon Weather/Snow_Clody_big.png";
    }else if(mainWeather.toLower().contains("snow")){
        return QDir::currentPath()+"/Icon Weather/Snowing_big.png";
    }else if(mainWeather.toLower().contains("snowy")){
        return QDir::currentPath()+"/Icon Weather/Snowy_big.png";
    }else if(mainWeather.toLower().contains("sunny")){
        return QDir::currentPath()+"/Icon Weather/Sunny_big.png";
    }else if(mainWeather.toLower().contains("windy")){
        return QDir::currentPath()+"/Icon Weather/Windy_big.png";
    }
}

