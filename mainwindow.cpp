#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
/*

https://api.thecatapi.com/v1/images/7nA3AVPKO

*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mNetManager = new QNetworkAccessManager(this);
    connect(mNetManager,&QNetworkAccessManager::finished,
            this,&MainWindow::handelNetFinished);
    ui->lineEdit->setText("https://api.thecatapi.com/v1/images/search");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openUrl(const QString &url)
{
    mNetManager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::testJson(QByteArray data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray obj = doc.array();
    foreach (const QJsonValue & v, obj)
    {
        id = v.toObject().value("id").toString();
        ui->MainWindow::ID->setText(id);
    }
    foreach (const QJsonValue & v, obj){
        url = v.toObject().value("url").toString();
        ui->MainWindow::lineEdit_2->setText(url);
    }
    foreach (const QJsonValue & v, obj){
       height = v.toObject().value("height").toInt();
       height_Str = QString::number(height);
       ui->MainWindow::HEIGHT->setText(height_Str);
    }
    foreach (const QJsonValue & v, obj){
       width = v.toObject().value("width").toInt();
       width_Str = QString::number(width);
       ui->MainWindow::WIDTH->setText(width_Str);
    }

//    QJsonDocument doc = QJsonDocument::fromJson(data);
//    QJsonObject obj = doc.object();
//    QVariantMap map = obj.toVariantMap();
//    ui->MainWindow::ID->setText(map["id"].toString());
//    ui->MainWindow::lineEdit_2->setText(map["url"].toString());
//    ui->MainWindow::WIDTH->setText(map["width"].toString());
//    ui->MainWindow::HEIGHT->setText(map["height"].toString());
//    qDebug() << "id:" << map["id"].toString();
//    qDebug()<< "url:" << map["url"].toString();
//    qDebug() << "width:" << map["width"].toString();
//    qDebug()<< "height:" << map["height"].toString();
}

void MainWindow::handelNetFinished(QNetworkReply *reply)
{
    if (reply->error()==QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        qDebug()<<data;
        testJson(data);
        qDebug("sukses");
    }
    else{
        qDebug("Error");
    }
}


void MainWindow::on_Edit_clicked()
{
    openUrl(ui->lineEdit->text());

}
