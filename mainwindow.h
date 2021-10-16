#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAddressEntry>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openUrl(const QString& url );
    void testJson(QByteArray data);

protected slots:
    void handelNetFinished(QNetworkReply* reply);

private slots:
    void on_Edit_clicked();


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* mNetManager=NULL;
    QString id;
    QString url;
    QString height_Str;
    QString width_Str;
    int height;
    int width;
};
#endif // MAINWINDOW_H
