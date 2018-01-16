#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "ledindicator.h"
#include "qledindicator.h"
#include <QtWebSockets/QWebSocket>
#include <clientsocket2.h>
#include "cvimagewidget.h"


namespace Ui {
class MainWindow;
}

class ArrowPad;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    CVImageWidget *imageWidget;


private slots:
    void on_createButton_clicked();
    //void on_ledIndicator_0_toggled(bool checked);
    void on_initServo_clicked();
    void on_initMotors_clicked();
    void on_initIMU_clicked();
    void on_initToF_clicked();
    void on_initCam_clicked();
    void on_connectButton_clicked();
    void writeText();
    void imageChanged();
    void on_verticalSlider_valueChanged(int value);
    void on_speedText_textChanged(const QString &arg1);


private:
    Ui::MainWindow *ui;
    ArrowPad *arrowPad;
    void createLog();
    QLedIndicator *servoLED;
    QLedIndicator *motorLED;
    QLedIndicator *imuLED;
    QLedIndicator *tofLED;
    QLedIndicator *camLED;
    QTcpSocket *socket;
    EchoClient *client;


};

#endif // MAINWINDOW_H
