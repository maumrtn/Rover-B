#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "ledindicator.h"
#include "qledindicator.h"
#include <QtWebSockets/QWebSocket>
#include "clientsocket2.h"
#include "cvimagewidget.h"
#include "gauge.h"
#include <QDateTime>
QT_BEGIN_NAMESPACE
class QGamepad;
QT_END_NAMESPACE

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
    QString cmdString;

signals:
    void sendMsg(QString msg);


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
    void on_verticalSlider_valueChanged(int value);
    void on_speedText_textChanged(const QString &arg1);
    void leftXChanged();
    void R2Changed();
    void L2Changed();
    void rightXChanged();
    void rightYChanged();
    void update();

    void onDisconnection();
    void onMessageReceived();

    void on_PointTurn_clicked();


    void on_flagDrop_clicked();

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
    QString sensorVal;
    QcGaugeWidget *RPMGauge_1;
    QcNeedleItem *RPMNeedle_1;
    QcGaugeWidget *RPMGauge_2;
    QcNeedleItem *RPMNeedle_2;
    QcGaugeWidget *RPMGauge_3;
    QcNeedleItem *RPMNeedle_3;
    QcGaugeWidget *RPMGauge_4;
    QcNeedleItem *RPMNeedle_4;
    QcGaugeWidget *RPMGauge_5;
    QcNeedleItem *RPMNeedle_5;
    QcGaugeWidget *RPMGauge_6;
    QcNeedleItem *RPMNeedle_6;
    QcGaugeWidget * servoGauge_1;
    QcNeedleItem *servoNeedle_1;
    QcGaugeWidget * servoGauge_2;
    QcNeedleItem *servoNeedle_2;
    QcGaugeWidget * servoGauge_3;
    QcNeedleItem *servoNeedle_3;
    QcGaugeWidget * servoGauge_4;
    QcNeedleItem *servoNeedle_4;
    QString fileName;
    QTextStream rpmStream,servoStream,bogieIMUStream,mainIMUStream,voltageStream,batStream,distSenStream,tempStream,camServoStream;
    QFile rpmFile,servoFile,bogieIMUFile,mainIMUFile,voltageFile,batFile,distSenFile,tempFile,camServoFile;
    QGamepad *m_gamepad;
    QTimer *timer;
    bool turnPoint = false;
    bool flagDrop = false;



};

#endif // MAINWINDOW_H
