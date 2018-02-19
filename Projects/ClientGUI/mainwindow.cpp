#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arrowpad.h"
#include "ledindicator.h"
#include "qledindicator.h"
#include "cvimagewidget.h"
#include "gamepadmonitor.h"
#include "simpleplayer.h"
#include <math.h>

#include <QFileDialog>
#include <QInputDialog>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/VideoStream.h>

#include "opencv2/opencv.hpp"
using namespace cv;
#include <QtWidgets>
#include <QDebug>
#include <QFile>
#include <QtGamepad/QGamepad>



#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _media(0)
{
    ui->setupUi(this);
   // this->setStyleSheet("background-color: black;");

    // Time for sending of commands
    timer = new QTimer(this);

    timer->start(100);

    // Video
    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->video);
    ui->video->setMediaPlayer(_player);
    connect(ui->openUrl, &QPushButton::clicked, this, &MainWindow::openUrl);
    //VlcVideoStream::renderFrame();
    // Gamepad
    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    if (gamepads.isEmpty()) {
        qWarning("No gamepad connected");
    }else
    {


    m_gamepad = new QGamepad(*gamepads.begin(), this);
    connect(m_gamepad, &QGamepad::axisLeftXChanged, this, &MainWindow::leftXChanged);
    connect(m_gamepad, &QGamepad::buttonR2Changed, this, &MainWindow::R2Changed);
    connect(m_gamepad, &QGamepad::buttonL2Changed, this, &MainWindow::L2Changed);
    connect(m_gamepad, &QGamepad::axisRightXChanged, this, &MainWindow::rightXChanged);
    connect(m_gamepad, &QGamepad::axisRightYChanged, this, &MainWindow::rightYChanged);
    connect(m_gamepad, &QGamepad::buttonYChanged, this, &MainWindow::buttonYChanged);

    connect(m_gamepad, &QGamepad::axisLeftYChanged, this, [](double value){
        qWarning() << "Left Y" << value;
    });
    connect(m_gamepad, &QGamepad::axisRightXChanged, this, [](double value){
        qWarning() << "Right X" << value;
    });
    connect(m_gamepad, &QGamepad::buttonAChanged, this, [](bool pressed){
        qWarning() << "Button A" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonBChanged, this, [](bool pressed){
        qWarning() << "Button B" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonXChanged, this, [](bool pressed){
        qWarning() << "Button X" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonYChanged, this, [](bool pressed){
        qWarning() << "Button Y" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonL1Changed, this, [](bool pressed){
        qWarning() << "Button L1" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonR1Changed, this, [](bool pressed){
        qWarning() << "Button R1" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonL2Changed, this, [](double value){
        qWarning() << "Button L2: " << value;
    });
    connect(m_gamepad, &QGamepad::buttonR2Changed, this, [](double value){
        qWarning() << "Button R2: " << value;
    });
    connect(m_gamepad, &QGamepad::buttonSelectChanged, this, [](bool pressed){
        qWarning() << "Button Select" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonStartChanged, this, [](bool pressed){
        qWarning() << "Button Start" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonGuideChanged, this, [](bool pressed){
        qWarning() << "Button Guide" << pressed;
    });
}



    this->client = NULL;

    //connect(ui->createButton,SIGNAL(clicked()),this,SLOT(createLog()));

    // Add ArrowPad
    arrowPad = new ArrowPad;
    ui->gridLayout->addWidget(arrowPad,1,0);

    // Add LEDs
    servoLED = new QLedIndicator(this);
    ui->gridLayout_2->addWidget(servoLED,2,1);
    servoLED->setEnabled(false);
    //servoLED->toggle();

    motorLED = new QLedIndicator(this);
    ui->gridLayout_2->addWidget(motorLED,4,1);
    motorLED->setEnabled(false);
    //motorLED->toggle();

    imuLED = new QLedIndicator(this);
    ui->gridLayout_2->addWidget(imuLED,6,1);
    imuLED->setEnabled(false);
    //imuLED->toggle();

    tofLED = new QLedIndicator(this);
    ui->gridLayout_2->addWidget(tofLED,8,1);
    tofLED->setEnabled(false);
    //tofLED->toggle();

    camLED = new QLedIndicator(this);
    ui->gridLayout_2->addWidget(camLED,10,1);
    camLED->setEnabled(false);
    //camLED->toggle();

    // Velocity slider
    ui->verticalSlider->setRange(0,100);

    connect(arrowPad->upButton,SIGNAL(clicked()),this,SLOT(writeText()));
/*
    // Image
    // Create the image widget
    CVImageWidget* imageWidget = new CVImageWidget();
    window.setCentralWidget(imageWidget);

    // Load an image
    cv::Mat image = cv::imread("somepicture.jpg", true);
    imageWidget->showImage(image);
*/
    //connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(toogleLED(myQledIndicator)));

    // TCP Connection: Signals and slots
    /*socket = new QTcpSocket(this);
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    //connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));*/

    // Images with opencv
    imageWidget = new CVImageWidget();
    ui->imageGrid->addWidget(imageWidget,0,0);
    // Load an image
    cv::Mat image = cv::imread("/home/maumrtn/Qt/Projects/ClientGUI/surface.jpg", true);
    cv::Size size(500,500);
    cv::resize(image,image,size);
    imageWidget->showImage(image);
    cv::Mat edges;
    cv::Canny(image,edges,100,20);
    imageWidget->showImage(edges);




    // Gauge widgets 1-4: From top left to top right and bottom left to bottom right
    float arcDistance = 30;
    float degDistance = 35;
    float degMinVal   = 0;
    float degMaxVal   = 100;
    float colorDistance = 25;
    float colorMinVal = 0;
    float colorMaxVal = 100;
    float valDistance = 45;
    float valSize     = 45;
    float labelDistance=25;
    float valMinVal   = 0;
    float valMaxVal   = 120;
    float labelSize   = 45;
    float needleSize  = 20;
    float needleMinVal= 0;
    float needleMaxVal= 100;
    float background  = 3.5;
    // Gauge 1
    RPMGauge_1 = new QcGaugeWidget;
    RPMGauge_1->addArc(arcDistance); // Radius
    RPMGauge_1->addDegrees(degDistance)->setValueRange(degMinVal,degMaxVal);
    //QcColorBand *clrBand_1 = RPMGauge_1->addColorBand(colorDistance);
    //clrBand_1->setValueRange(colorMinVal,colorMaxVal);
    RPMGauge_1->addValues(valDistance)->setValueRange(valMinVal,valMaxVal);
    RPMGauge_1->addLabel(labelSize)->setText("RPM");
    QcLabelItem *lab_1 = RPMGauge_1->addLabel(labelDistance);
    lab_1->setText("0");
    RPMNeedle_1 = RPMGauge_1->addNeedle(needleSize);
    RPMNeedle_1->setLabel(lab_1);
    RPMNeedle_1->setColor(Qt::blue);
    RPMNeedle_1->setValueRange(needleMinVal,needleMaxVal);
    RPMGauge_1->addBackground(background);

    // Gauge 2
    RPMGauge_2 = new QcGaugeWidget;
    RPMGauge_2->addArc(arcDistance); // Radius
    RPMGauge_2->addDegrees(degDistance)->setValueRange(degMinVal,degMaxVal);
    //QcColorBand *clrBand_2 = RPMGauge_2->addColorBand(colorDistance);
    //clrBand_2->setValueRange(colorMinVal,colorMaxVal);
    RPMGauge_2->addValues(valDistance)->setValueRange(valMinVal,valMaxVal);
    RPMGauge_2->addLabel(labelSize)->setText("RPM");
    QcLabelItem *lab_2 = RPMGauge_2->addLabel(labelDistance);
    lab_2->setText("0");
    RPMNeedle_2 = RPMGauge_2->addNeedle(needleSize);
    RPMNeedle_2->setLabel(lab_2);
    RPMNeedle_2->setColor(Qt::blue);
    RPMNeedle_2->setValueRange(needleMinVal,needleMaxVal);
    RPMGauge_2->addBackground(background);

    // Gauge 3
    RPMGauge_3 = new QcGaugeWidget;
    RPMGauge_3->addArc(arcDistance); // Radius
    RPMGauge_3->addDegrees(degDistance)->setValueRange(degMinVal,degMaxVal);
    //QcColorBand *clrBand_3 = RPMGauge_3->addColorBand(colorDistance);
    //clrBand_3->setValueRange(colorMinVal,colorMaxVal);
    RPMGauge_3->addValues(valDistance)->setValueRange(valMinVal,valMaxVal);
    RPMGauge_3->addLabel(labelSize)->setText("RPM");
    QcLabelItem *lab_3 = RPMGauge_3->addLabel(labelDistance);
    lab_3->setText("0");
    RPMNeedle_3 = RPMGauge_3->addNeedle(needleSize);
    RPMNeedle_3->setLabel(lab_3);
    RPMNeedle_3->setColor(Qt::blue);
    RPMNeedle_3->setValueRange(needleMinVal,needleMaxVal);
    RPMGauge_3->addBackground(background);

    // Gauge 4
    RPMGauge_4 = new QcGaugeWidget;
    RPMGauge_4->addArc(arcDistance); // Radius
    RPMGauge_4->addDegrees(degDistance)->setValueRange(degMinVal,degMaxVal);
    //QcColorBand *clrBand_4 = RPMGauge_4->addColorBand(colorDistance);
    //clrBand_4->setValueRange(colorMinVal,colorMaxVal);
    RPMGauge_4->addValues(valDistance)->setValueRange(valMinVal,valMaxVal);
    RPMGauge_4->addLabel(labelSize)->setText("RPM");
    QcLabelItem *lab_4 = RPMGauge_4->addLabel(labelDistance);
    lab_4->setText("0");
    RPMNeedle_4 = RPMGauge_4->addNeedle(needleSize);
    RPMNeedle_4->setLabel(lab_4);
    RPMNeedle_4->setColor(Qt::blue);
    RPMNeedle_4->setValueRange(needleMinVal,needleMaxVal);
    RPMGauge_4->addBackground(background);

    // Gauge 5
    RPMGauge_5 = new QcGaugeWidget;
    RPMGauge_5->addArc(arcDistance); // Radius
    RPMGauge_5->addDegrees(degDistance)->setValueRange(degMinVal,degMaxVal);
    //QcColorBand *clrBand_5 = RPMGauge_5->addColorBand(colorDistance);
    //clrBand_5->setValueRange(colorMinVal,colorMaxVal);
    RPMGauge_5->addValues(valDistance)->setValueRange(valMinVal,valMaxVal);
    RPMGauge_5->addLabel(labelSize)->setText("RPM");
    QcLabelItem *lab_5 = RPMGauge_5->addLabel(labelDistance);
    lab_5->setText("0");
    RPMNeedle_5 = RPMGauge_5->addNeedle(needleSize);
    RPMNeedle_5->setLabel(lab_5);
    RPMNeedle_5->setColor(Qt::blue);
    RPMNeedle_5->setValueRange(needleMinVal,needleMaxVal);
    RPMGauge_5->addBackground(background);

    // Gauge 6
    RPMGauge_6 = new QcGaugeWidget;
    RPMGauge_6->addArc(arcDistance); // Radius
    RPMGauge_6->addDegrees(degDistance)->setValueRange(degMinVal,degMaxVal);
    //QcColorBand *clrBand_6 = RPMGauge_6->addColorBand(colorDistance);
    //clrBand_6->setValueRange(colorMinVal,colorMaxVal);
    RPMGauge_6->addValues(valDistance)->setValueRange(valMinVal,valMaxVal);
    RPMGauge_6->addLabel(labelSize)->setText("RPM");
    QcLabelItem *lab_6 = RPMGauge_6->addLabel(labelDistance);
    lab_6->setText("0");
    RPMNeedle_6 = RPMGauge_6->addNeedle(needleSize);
    RPMNeedle_6->setLabel(lab_6);
    RPMNeedle_6->setColor(Qt::blue);
    RPMNeedle_6->setValueRange(needleMinVal,needleMaxVal);
    RPMGauge_6->addBackground(background);

    // Servos 1-4: top left, top right, bottom left, bottom right
    float backgroundServo = 99.0/3;
    float bkg1Size        = 92.0/3;
    float bkg2Size        = 88.0/3;
    float nSize           = 90.0/2;
    float degSize         = 70.0/3;
    float needleSizeServo = 60.0/3;
    // Servo 1
    servoGauge_1 = new QcGaugeWidget;
    //servoGauge_1->addBackground(backgroundServo);
    QcBackgroundItem *bkg1_1 = servoGauge_1->addBackground(bkg1Size);
    bkg1_1->clearrColors();
    bkg1_1->addColor(0.1,Qt::black);
    bkg1_1->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2_1 = servoGauge_1->addBackground(bkg2Size);
    bkg2_1->clearrColors();
    bkg2_1->addColor(0.1,Qt::white);
    bkg2_1->addColor(1.0,Qt::black);

    QcLabelItem *n_1 = servoGauge_1->addLabel(nSize);
    n_1->setText("-90");
    n_1->setAngle(0);
    n_1->setColor(Qt::black);

    QcLabelItem *e_1 = servoGauge_1->addLabel(nSize);
    e_1->setText("0");
    e_1->setAngle(90);
    e_1->setColor(Qt::black);

    QcLabelItem *s_1 = servoGauge_1->addLabel(nSize);
    s_1->setText("90");
    s_1->setAngle(180);
    s_1->setColor(Qt::black);

    QcDegreesItem *deg_1 = servoGauge_1->addDegrees(degSize);
    deg_1->setStep(5);
    deg_1->setMaxDegree(250);
    deg_1->setMinDegree(-70);
    deg_1->setColor(Qt::white);
    servoNeedle_1 = servoGauge_1->addNeedle(needleSizeServo);
    //mCompassNeedle->setNeedle(QcNeedleItem::CompassNeedle);
    servoNeedle_1->setValueRange(-160,160);
    servoNeedle_1->setMaxDegree(160);
    servoNeedle_1->setMinDegree(-160);
    servoGauge_1->addBackground(7);
    servoGauge_1->addGlass(bkg2Size);

    // Servo 2
    servoGauge_2 = new QcGaugeWidget;

    servoGauge_2->addBackground(backgroundServo);
    QcBackgroundItem *bkg1_2 = servoGauge_2->addBackground(bkg1Size);
    bkg1_2->clearrColors();
    bkg1_2->addColor(0.1,Qt::black);
    bkg1_2->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2_2 = servoGauge_2->addBackground(bkg2Size);
    bkg2_2->clearrColors();
    bkg2_2->addColor(0.1,Qt::white);
    bkg2_2->addColor(1.0,Qt::black);

    QcLabelItem *n_2 = servoGauge_2->addLabel(nSize);
    n_2->setText("-90");
    n_2->setAngle(0);
    n_2->setColor(Qt::black);

    QcLabelItem *e_2 = servoGauge_2->addLabel(nSize);
    e_2->setText("0");
    e_2->setAngle(90);
    e_2->setColor(Qt::black);

    QcLabelItem *s_2 = servoGauge_2->addLabel(nSize);
    s_2->setText("90");
    s_2->setAngle(180);
    s_2->setColor(Qt::black);

    QcDegreesItem *deg_2 = servoGauge_2->addDegrees(degSize);
    deg_2->setStep(5);
    deg_2->setMaxDegree(250);
    deg_2->setMinDegree(-70);
    deg_2->setColor(Qt::white);
    servoNeedle_2 = servoGauge_2->addNeedle(needleSizeServo);
    //mCompassNeedle->setNeedle(QcNeedleItem::CompassNeedle);
    servoNeedle_2->setValueRange(-160,160);
    servoNeedle_2->setMaxDegree(160);
    servoNeedle_2->setMinDegree(-160);
    servoGauge_2->addBackground(7);
    servoGauge_2->addGlass(bkg2Size);


    // Sevo 3
    servoGauge_3 = new QcGaugeWidget;

    servoGauge_3->addBackground(backgroundServo);
    QcBackgroundItem *bkg1_3 = servoGauge_3->addBackground(bkg1Size);
    bkg1_3->clearrColors();
    bkg1_3->addColor(0.1,Qt::black);
    bkg1_3->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2_3 = servoGauge_3->addBackground(bkg2Size);
    bkg2_3->clearrColors();
    bkg2_3->addColor(0.1,Qt::white);
    bkg2_3->addColor(1.0,Qt::black);

    QcLabelItem *n_3 = servoGauge_3->addLabel(nSize);
    n_3->setText("-90");
    n_3->setAngle(0);
    n_3->setColor(Qt::black);

    QcLabelItem *e_3 = servoGauge_3->addLabel(nSize);
    e_3->setText("0");
    e_3->setAngle(90);
    e_3->setColor(Qt::black);

    QcLabelItem *s_3 = servoGauge_3->addLabel(nSize);
    s_3->setText("90");
    s_3->setAngle(180);
    s_3->setColor(Qt::black);

    QcDegreesItem *deg_3 = servoGauge_3->addDegrees(degSize);
    deg_3->setStep(5);
    deg_3->setMaxDegree(250);
    deg_3->setMinDegree(-70);
    deg_3->setColor(Qt::white);
    servoNeedle_3 = servoGauge_3->addNeedle(needleSizeServo);
    //mCompassNeedle->setNeedle(QcNeedleItem::CompassNeedle);
    servoNeedle_3->setValueRange(-160,160);
    servoNeedle_3->setMaxDegree(160);
    servoNeedle_3->setMinDegree(-160);
    servoGauge_3->addBackground(7);
    servoGauge_3->addGlass(bkg2Size);


    // Servo 4
    servoGauge_4 = new QcGaugeWidget;

    servoGauge_4->addBackground(backgroundServo);
    QcBackgroundItem *bkg1_4 = servoGauge_4->addBackground(bkg1Size);
    bkg1_4->clearrColors();
    bkg1_4->addColor(0.1,Qt::black);
    bkg1_4->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2_4 = servoGauge_4->addBackground(bkg2Size);
    bkg2_4->clearrColors();
    bkg2_4->addColor(0.1,Qt::white);
    bkg2_4->addColor(1.0,Qt::black);

    QcLabelItem *n_4 = servoGauge_4->addLabel(nSize);
    n_4->setText("-90");
    n_4->setAngle(0);
    n_4->setColor(Qt::black);

    QcLabelItem *e_4 = servoGauge_4->addLabel(nSize);
    e_4->setText("0");
    e_4->setAngle(90);
    e_4->setColor(Qt::black);

    QcLabelItem *s_4 = servoGauge_4->addLabel(nSize);
    s_4->setText("90");
    s_4->setAngle(180);
    s_4->setColor(Qt::black);

    QcDegreesItem *deg_4 = servoGauge_4->addDegrees(degSize);
    deg_4->setStep(5);
    deg_4->setMaxDegree(250);
    deg_4->setMinDegree(-70);
    deg_4->setColor(Qt::white);
    servoNeedle_4 = servoGauge_4->addNeedle(needleSizeServo);
    //mCompassNeedle->setNeedle(QcNeedleItem::CompassNeedle);
    servoNeedle_4->setValueRange(-160,160);
    servoNeedle_4->setMaxDegree(160);
    servoNeedle_4->setMinDegree(-160);
    servoGauge_4->addBackground(7);
    servoGauge_4->addGlass(bkg2Size);

    // Add gauges to grid

    ui->gridLayout_3->addWidget(servoGauge_1,1,1);
    ui->gridLayout_3->addWidget(servoGauge_2,1,4);
    ui->gridLayout_3->addWidget(servoGauge_3,3,1);
    ui->gridLayout_3->addWidget(servoGauge_4,3,4);
    ui->gridLayout_3->addWidget(RPMGauge_1,1,2);
    ui->gridLayout_3->addWidget(RPMGauge_2,1,3);
    ui->gridLayout_3->addWidget(RPMGauge_3,2,2);
    ui->gridLayout_3->addWidget(RPMGauge_4,2,3);
    ui->gridLayout_3->addWidget(RPMGauge_5,3,2);
    ui->gridLayout_3->addWidget(RPMGauge_6,3,3);

    /*int widgetSize = 200;
    servoGauge_1->setFixedHeight(widgetSize);
    servoGauge_1->setFixedHeight(widgetSize);
    servoGauge_2->setFixedHeight(widgetSize);
    servoGauge_3->setFixedHeight(widgetSize);
    servoGauge_4->setFixedHeight(widgetSize);
    RPMGauge_1->setFixedHeight(widgetSize);
    RPMGauge_1->setFixedHeight(widgetSize);
    RPMGauge_2->setFixedWidth(widgetSize);
    RPMGauge_2->setFixedWidth(widgetSize);
    RPMGauge_3->setFixedWidth(widgetSize);
    RPMGauge_3->setFixedWidth(widgetSize);
    RPMGauge_4->setFixedWidth(widgetSize);
    RPMGauge_4->setFixedWidth(widgetSize);
    RPMGauge_5->setFixedWidth(widgetSize);
    RPMGauge_5->setFixedWidth(widgetSize);
    RPMGauge_6->setFixedWidth(widgetSize);
    RPMGauge_6->setFixedWidth(widgetSize);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeText()
{
    ui->console->append("UP");
}


void MainWindow::on_createButton_clicked()
{

    QString fileName = ui->lineEdit->text();
    //ui->lineEdit->
    rpmFile.setFileName(fileName.append("/rpm.txt"));
    servoFile.setFileName(fileName.append("/servo.txt"));
    bogieIMUFile.setFileName(fileName.append("/bogieIMU.txt"));
    mainIMUFile.setFileName(fileName.append("/mainIMU.txt"));
    batFile.setFileName(fileName.append("/bat.txt"));
    distSenFile.setFileName(fileName.append("/distSen.txt"));
    tempFile.setFileName(fileName.append("/temp.txt"));
    camServoFile.setFileName(fileName.append("/camServo.txt"));
    if ( rpmFile.open(QIODevice::ReadWrite))
   {
       rpmStream.setDevice(&rpmFile);
       QDateTime curTime = QDateTime::currentDateTime();
       QString header   = QStringLiteral("Motor RPM data created on: ");
       QString header2  = QStringLiteral("time;RPM1;RPM2;RPM3;RPM4;RPM5;RPM6\n");
       rpmStream << header << curTime.toString()<<"\n" <<header2;
   }
    if ( servoFile.open(QIODevice::ReadWrite))
   {
       servoStream.setDevice(&servoFile);
       QDateTime curTime = QDateTime::currentDateTime();
       QString header   = QStringLiteral("Servo data created on: ");
       QString header2  = QStringLiteral("time;servo1;servo2;servo3;servo4\n");
       servoStream << header << curTime.toString()<<"\n" <<header2;
   }
    if ( bogieIMUFile.open(QIODevice::ReadWrite))
   {
       bogieIMUStream.setDevice(&bogieIMUFile);
       QDateTime curTime = QDateTime::currentDateTime();
       QString header   = QStringLiteral("Bogie IMU data created on: ");
       QString header2  = QStringLiteral("time;bogieIMU1;bogieIMU2;bogieIMU3;bogieIMU4;bogieIMU5;bogieIMU7;bogieIMU8;bogieIMU9\n");
       bogieIMUStream << header << curTime.toString()<<"\n" <<header2;
   }
    if ( mainIMUFile.open(QIODevice::ReadWrite))
   {
       mainIMUStream.setDevice(&mainIMUFile);
       QDateTime curTime = QDateTime::currentDateTime();
       QString header   = QStringLiteral("Main IMU created on: ");
       QString header2  = QStringLiteral("time;mainIMU1;mainIMU2;mainIMU3\n");
       mainIMUStream << header << curTime.toString()<<"\n" <<header2;
   }
    if ( voltageFile.open(QIODevice::ReadWrite))
   {
       voltageStream.setDevice(&voltageFile);
       QDateTime curTime = QDateTime::currentDateTime();
       QString header   = QStringLiteral("Voltage data created on: ");
       QString header2  = QStringLiteral("time;voltage1;voltage2;voltage3;voltage4;voltage5;voltage6\n");
       voltageStream << header << curTime.toString()<<"\n" <<header2;
   }
    if ( batFile.open(QIODevice::ReadWrite))
   {
       batStream.setDevice(&batFile);
       QDateTime curTime = QDateTime::currentDateTime();
       QString header   = QStringLiteral("Battery data created on: ");
       QString header2  = QStringLiteral("time;bat1\n");
       batStream << header << curTime.toString()<<"\n" <<header2;
   }
    if ( distSenFile.open(QIODevice::ReadWrite))
   {
       distSenStream.setDevice(&distSenFile);
       QDateTime curTime = QDateTime::currentDateTime();
       QString header   = QStringLiteral("Distance sensor data created on: ");
       QString header2  = QStringLiteral("time;distSen1;distSen2;distSen3;distSen4\n");
       distSenStream << header << curTime.toString()<<"\n" <<header2;
   }
    if ( tempFile.open(QIODevice::ReadWrite))
   {
       tempStream.setDevice(&tempFile);
       QDateTime curTime = QDateTime::currentDateTime();
       QString header   = QStringLiteral("Temperature data created on: ");
       QString header2  = QStringLiteral("time;temp1;temp2;temp3;temp4\n");
       tempStream << header << curTime.toString()<<"\n" <<header2;
   }
    if ( camServoFile.open(QIODevice::ReadWrite))
   {
       camServoStream.setDevice(&camServoFile);
       QDateTime curTime = QDateTime::currentDateTime();
       QString header   = QStringLiteral("Camera Servo data created on: ");
       QString header2  = QStringLiteral("time;camServo1;camServo2\n");
       camServoStream << header << curTime.toString()<<"\n" <<header2;
   }

    QString textEditOutput = fileName;
    textEditOutput.prepend("File written to: ");
    ui->console->append(textEditOutput);

}


/*void MainWindow::on_ledIndicator_0_toggled(bool checked)
{
    qDebug() << "Led toggled: " << checked;
}*/



void toogleLED(QLedIndicator * led)
{
    led->toggle();
}



void MainWindow::on_initServo_clicked()
{
    if (initServo==false)
    {
        initServo = !initServo;
        servoLED->toggle();
        ui->console->append("Initializing servos...");
    }else
    {
        ui->console->append("Initializing again servos...");
    }

    QJsonObject msg;
    msg.insert("cmd", QJsonValue::fromVariant("init"));
    msg.insert("data", QJsonValue::fromVariant("servoReset"));

    QJsonDocument doc(msg);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    emit sendMsg(strJson);

}



void MainWindow::on_initMotors_clicked()
{
    motorLED->toggle();
    ui->console->append("Starting initialization of motors...");
}

void MainWindow::on_initIMU_clicked()
{
    imuLED->toggle();
    ui->console->append("Starting initialization of IMU...");
}

void MainWindow::on_initToF_clicked()
{
    tofLED->toggle();
    ui->console->append("Starting initialization of ToF..");
}

void MainWindow::on_initCam_clicked()
{
    camLED->toggle();
    ui->console->append("Starting initialization of Cam..");
    VideoCapture cap(0);
    Mat frame;
    Mat edges;
    cap >> frame; // get a new frame from camera
    cvtColor(frame, edges, COLOR_BGR2GRAY);
    GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    Canny(edges, edges, 0, 30, 3);
    imshow("edges", edges);
}


void MainWindow::on_connectButton_clicked()
{
    /*clientSocket socket;
    socket.Test();*/
    if (this->client == NULL)
    {
        bool debug = 1;
        QString command = "1";
        this->client = new EchoClient(QUrl(QStringLiteral("ws://192.168.7.2:1234")), debug,command);//Beagle bone ws://192.168.7.2:1234//IRS Konferenz:ws://192.168.21.174:8888

        if (this->client->sensorVal != NULL)
        {
            sensorVal=this->client->sensorVal;

        }

        connect(ui->connectButton_2,SIGNAL(clicked(bool)),this->client,SLOT(onDisconnection()));
        connect(ui->connectButton_2,SIGNAL(clicked(bool)),this,SLOT(onDisconnection()));
        connect(this->client,SIGNAL(messageReceived()),this,SLOT(onMessageReceived()));
        if (m_gamepad== NULL)
        {
            ui->console->append("Warning: Controller is not connected yet!");
        }else
        {
            connect(timer, SIGNAL(timeout()), this, SLOT(update()));
            connect(this,SIGNAL(sendMsg(QString)),this->client,SLOT(sendMsgTCP(QString)));
        }

    }
    else
    {
        ui->console->append("Already connected");
    }
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    ui->speedText->setText(QString::number(value));
}

void MainWindow::on_speedText_textChanged(const QString &arg1)
{
    ui->verticalSlider->setValue(arg1.toInt());
}
void MainWindow::onDisconnection()
{
    this->client = NULL;
    rpmFile.close();
    servoFile.close();
    bogieIMUFile.close();
    mainIMUFile.close();
    voltageFile.close();
    batFile.close();
    distSenFile.close();
    tempFile.close();
    camServoFile.close();
}

void MainWindow::onMessageReceived()
{
    // Take message from BB
    QString message = this->client->sensorVal;
    // Convert to JSON
    QJsonDocument messageJSONDoc = QJsonDocument::fromJson(message.toUtf8());
    // check validity of the document
        if(!messageJSONDoc.isNull())
        {
            if(messageJSONDoc.isObject())
            {
                // Convert to JSON Object
                QJsonObject objectJSON = messageJSONDoc.object();
                QJsonValue msgValue;
                QJsonObject messageJSON;

                // Check type of message (either console message or sensor data)

                // Check if JSON contains a message for the console
                if (objectJSON.contains("msg"))
                {
                    QJsonValue item = objectJSON["message"];
                    ui->console->append(item.toString());
                }

                if (objectJSON.contains("rpm"))
                {
                    // Find out sensor type
                    /*messageType = item.value(QString("rpm"));
                    QJsonArray array = item["rpm1"].toArray();
                    qWarning() <<array[1].toString();*/
                    msgValue = objectJSON.value(QString("rpm"));
                    messageJSON = msgValue.toObject();

                        QJsonValue val1  = messageJSON.value("rpm1");
                        QJsonValue time = messageJSON["timestamp"];

                        RPMNeedle_1->setCurrentValue(val1.toDouble());
                        rpmStream << time.toString()<<";"<<QString::number(val1.toDouble())<<";";

                        QJsonValue val2  = messageJSON.value("rpm2");
                        RPMNeedle_2->setCurrentValue(val2.toDouble());
                        rpmStream <<QString::number(val2.toDouble())<<";";

                        QJsonValue val3  = messageJSON.value("rpm3");
                        RPMNeedle_3->setCurrentValue(val3.toDouble());
                        rpmStream <<QString::number(val3.toDouble())<<";";

                        QJsonValue val4  = messageJSON.value("rpm4");
                        RPMNeedle_4->setCurrentValue(val4.toDouble());
                        rpmStream <<QString::number(val4.toDouble())<<";";

                        QJsonValue val5  = messageJSON.value("rpm5");
                        RPMNeedle_5->setCurrentValue(val5.toDouble());
                        rpmStream <<QString::number(val5.toDouble())<<";";

                        QJsonValue val6  = messageJSON.value("rpm6");
                        RPMNeedle_6->setCurrentValue(val6.toDouble());
                        rpmStream <<QString::number(val6.toDouble())<<"\n";
                    }
                    if (objectJSON.contains("servo"))
                    {
                        msgValue = objectJSON.value(QString("servo"));
                        messageJSON = msgValue.toObject();
                        QJsonValue val1  = messageJSON.value("servo1");
                        QJsonValue time = messageJSON["timestamp"];

                        servoNeedle_1->setCurrentValue(val1.toDouble());
                        servoStream << time.toString()<<";"<<QString::number(val1.toDouble())<<";";

                        QJsonValue val2  = messageJSON.value("servo2");
                        servoNeedle_2->setCurrentValue(val2.toDouble());
                        servoStream <<QString::number(val2.toDouble())<<";";

                        QJsonValue val3  = messageJSON.value("servo3");
                        servoNeedle_3->setCurrentValue(val3.toDouble());
                        servoStream <<QString::number(val3.toDouble())<<";";

                        QJsonValue val4  = messageJSON.value("servo4");
                        servoNeedle_4->setCurrentValue(val4.toDouble());
                        servoStream <<QString::number(val4.toDouble())<<"\n";
                    }
                    if (objectJSON.contains("bogieIMU"))
                    {
                        msgValue = objectJSON.value(QString("bogieIMU"));
                        messageJSON = msgValue.toObject();
                        QJsonValue time = messageJSON["timestamp"];
                        QJsonValue val1  = messageJSON.value("bogieIMU1");
                        ui->bogieIMU1->setText(QString::number(val1.toDouble()));
                        bogieIMUStream << time.toString()<<";"<<QString::number(val1.toDouble())<<";";

                        QJsonValue val2  = messageJSON.value("bogieIMU2");
                        ui->bogieIMU1->setText(QString::number(val2.toDouble()));
                        bogieIMUStream <<QString::number(val2.toDouble())<<";";

                        QJsonValue val3  = messageJSON.value("bogieIMU3");
                        ui->bogieIMU1->setText(QString::number(val3.toDouble()));
                        bogieIMUStream <<QString::number(val3.toDouble())<<";";

                        QJsonValue val4  = messageJSON.value("bogieIMU4");
                        bogieIMUStream <<QString::number(val4.toDouble())<<";";

                        QJsonValue val5  = messageJSON.value("bogieIMU5");
                        bogieIMUStream <<QString::number(val5.toDouble())<<";";

                        QJsonValue val6  = messageJSON.value("bogieIMU6");
                        bogieIMUStream <<QString::number(val6.toDouble())<<";";

                        QJsonValue val7  = messageJSON.value("bogieIMU7");
                        bogieIMUStream <<QString::number(val7.toDouble())<<";";

                        QJsonValue val8  = messageJSON.value("bogieIMU8");
                        bogieIMUStream <<QString::number(val8.toDouble())<<";";

                        QJsonValue val9  = messageJSON.value("bogieIMU9");
                        bogieIMUStream <<QString::number(val9.toDouble())<<"\n";
                    }


            if (objectJSON.contains("mainIMU"))
            {
                // Find out sensor type

                    msgValue = objectJSON.value(QString("mainIMU"));
                    messageJSON = msgValue.toObject();
                    QJsonValue val1  = messageJSON.value("mainIMU1");
                    QJsonValue time = messageJSON["timestamp"];

                    ui->eulerIndicatorX->setText(QString::number(val1.toDouble()));
                    mainIMUStream << time.toString()<<";"<<QString::number(val1.toDouble())<<";";

                    QJsonValue val2  = messageJSON.value("mainIMU2");
                    ui->eulerIndicatorY->setText(QString::number(val2.toDouble()));
                    mainIMUStream <<QString::number(val2.toDouble())<<";";

                    QJsonValue val3  = messageJSON.value("mainIMU3");
                    ui->eulerIndicatorZ->setText(QString::number(val3.toDouble()));
                    mainIMUStream <<QString::number(val3.toDouble())<<";";
                }
            if (objectJSON.contains("voltage"))
            {
                // Find out sensor type

                    msgValue = objectJSON.value(QString("voltage"));
                    messageJSON = msgValue.toObject();
                    QJsonValue val1  = messageJSON.value("voltage1");
                    QJsonValue time = messageJSON["timestamp"];

                    voltageStream << time.toString()<<";"<<QString::number(val1.toDouble())<<";";

                    QJsonValue val2  = messageJSON.value("voltage2");
                    voltageStream <<QString::number(val2.toDouble())<<";";

                    QJsonValue val3  = messageJSON.value("voltage3");
                    voltageStream <<QString::number(val3.toDouble())<<";";

                    QJsonValue val4  = messageJSON.value("voltage4");
                    voltageStream <<QString::number(val4.toDouble())<<";";

                    QJsonValue val5  = messageJSON.value("voltage5");
                    voltageStream <<QString::number(val5.toDouble())<<";";

                    QJsonValue val6  = messageJSON.value("voltage6");
                    voltageStream <<QString::number(val6.toDouble())<<"\n";

                    double voltageTotal = val1.toDouble()+val2.toDouble()+val3.toDouble()+val4.toDouble()+val5.toDouble()+val6.toDouble();
                    ui->voltageIndicator->setText(QString::number(voltageTotal));
            }

            if (objectJSON.contains("bat"))
            {
                    // Find out sensor type
                    msgValue = objectJSON.value(QString("bat"));
                    messageJSON = msgValue.toObject();

                    QJsonValue val1  = messageJSON.value("bat1");
                    QJsonValue time = messageJSON["timestamp"];

                    ui->batteryStatus->setValue(val1.toDouble());
                    batStream << time.toString()<<";"<<QString::number(val1.toDouble())<<";";
            }
            if (objectJSON.contains("distSen"))
            {
                // Find out sensor type
                msgValue = objectJSON.value(QString("distSen"));
                messageJSON = msgValue.toObject();

                    QJsonValue val1  = messageJSON.value("distSen1");
                    QJsonValue time = messageJSON["timestamp"];

                    ui->distanceIndicator1->setText(QString::number(val1.toDouble()));
                    distSenStream << time.toString()<<";"<<QString::number(val1.toDouble())<<";";

                    QJsonValue val2  = messageJSON.value("distSen2");
                    ui->distanceIndicator2->setText(QString::number(val2.toDouble()));
                    distSenStream <<QString::number(val2.toDouble())<<";";

                    QJsonValue val3  = messageJSON.value("distSen3");
                    ui->distanceIndicator3->setText(QString::number(val3.toDouble()));
                    distSenStream <<QString::number(val3.toDouble())<<";";

                    QJsonValue val4  = messageJSON.value("distSen4");
                    ui->distanceIndicator4->setText(QString::number(val4.toDouble()));
                    distSenStream <<QString::number(val4.toDouble())<<"\n";
                }
            if (objectJSON.contains("temp"))
            {

                    // Find out sensor type
                    msgValue = objectJSON.value(QString("temp"));
                    messageJSON = msgValue.toObject();
                    QJsonValue val1  = messageJSON.value("temp1");
                    QJsonValue time = messageJSON["timestamp"];

                    tempStream << time.toString()<<";"<<QString::number(val1.toDouble())<<";";

                    QJsonValue val2  = messageJSON.value("temp2");
                    tempStream <<QString::number(val2.toDouble())<<";";

                    QJsonValue val3  = messageJSON.value("temp3");
                    tempStream <<QString::number(val3.toDouble())<<";";

                    QJsonValue val4  = messageJSON.value("temp4");
                    tempStream <<QString::number(val4.toDouble())<<"\n";

                    double array[4] = {val1.toDouble(),val2.toDouble(),val3.toDouble(),val4.toDouble()};
                    double temp = 0;

                    for(int i=0;i<4;i++)
                    {
                        if(array[i]>temp)
                        temp=array[i];
                    }
                    ui->tempIndicator->setText(QString::number(temp));
            }

            if (objectJSON.contains("camServo"))
            {
                    // Find out sensor type
                    msgValue = objectJSON.value(QString("camServo"));
                    messageJSON = msgValue.toObject();

                    QJsonValue val1  = messageJSON.value("camServo1");
                    QJsonValue time = messageJSON["timestamp"];

                    ui->camAzIndicator->setText(QString::number(val1.toDouble()));
                    camServoStream << time.toString()<<";"<<QString::number(val1.toDouble())<<";";

                    QJsonValue val2  = messageJSON.value("camServo2");
                    ui->camElIndicator->setText(QString::number(val2.toDouble()));
                    camServoStream <<QString::number(val2.toDouble())<<";";
            }else
            {
                ui->console->append("Message could not be interpreted");
            }
            }
        }else
        {
            ui->console->append("Message could not be interpreted");
        }



}

void MainWindow::leftXChanged()
{
    ui->roverSteer->setValue(static_cast<int>(m_gamepad->axisLeftX()*100));
}

void MainWindow::rightXChanged()
{
    ui->camPan->setValue(static_cast<int>(m_gamepad->axisRightX()*100));
}
void MainWindow::rightYChanged()
{
    ui->camTilt->setValue(static_cast<int>(m_gamepad->axisRightY()*100));
}
void MainWindow::R2Changed()
{
    ui->roverVel->setValue(static_cast<int>(m_gamepad->buttonR2()*100));
}
void MainWindow::buttonYChanged()
{

    flagDropClicked = !flagDropClicked;

    if (flagDropClicked)
    {
        flagDrop = !flagDrop;
        QString flagDropString = QString::number(flagDrop);
        if (flagDropString.compare("1")==0)
        {
            flagDropString = "true";
        }
        else if (flagDropString.compare("0")==0)
        {
            flagDropString = "false";
        }
        else
        {
            flagDropString = "error";
        }

        ui->console->append("Dropping the flag...: "+flagDropString);
        QJsonObject msg;
        msg.insert("cmd", QJsonValue::fromVariant("flag"));
        msg.insert("data", QJsonValue::fromVariant(flagDrop));
        QJsonDocument doc(msg);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        emit sendMsg(strJson);
    }
}

void MainWindow::L2Changed()
{
    //ui->console->append(QString::number(m_gamepad->buttonR2()));
    if (m_gamepad->buttonR2()==0)
    {
        ui->roverVel->setValue(static_cast<int>(-m_gamepad->buttonL2()*100));
    }else
    {
        ui->roverVel->setValue(static_cast<int>(m_gamepad->buttonR2()*100));
    }
}


void MainWindow::update()
{

    if(m_gamepad!=NULL)
    {
    // Debug
    /*ui->console->append(QString::number(m_gamepad->axisLeftX()));
    ui->console->append(QString::number(m_gamepad->axisLeftY()));
    ui->console->append(QString::number(m_gamepad->axisRightY()));*/
    // Create JSON File and send via TCP
    // Drive input
    if ((gamepadDrive!=m_gamepad->buttonL2())||gamepadDrive!=m_gamepad->buttonR2())
    {
        QJsonObject msg;
        msg.insert("cmd", QJsonValue::fromVariant("drive"));
        // Check if right button is activated
        if(m_gamepad->buttonR2()==0) // Send L2
        {
            msg.insert("data", QJsonValue::fromVariant(round(-m_gamepad->buttonL2()*64+64)));
        }else // Send R2
        {
            msg.insert("data", QJsonValue::fromVariant(round(m_gamepad->buttonR2()*63+64)));
        }

        QJsonDocument doc(msg);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        emit sendMsg(strJson);
    }
    if(m_gamepad->buttonR2()==0) // Send L2
    {
        gamepadDrive = m_gamepad->buttonL2();
    }else
    {
        gamepadDrive = m_gamepad->buttonR2();
    }


    // Steering input
    double steeringVal = m_gamepad->axisLeftX(); // From -1 to 1
    double grad        = 80.0; // max steering in deg
    double steps       = 1023.0/320.0*grad*2.0;
    double L           = 0.33; // Distance from wheel in rear and front
    double B           = 0.39;
    double lowerVal    = (1023.0-steps)/2.0;
    double upperVal    = lowerVal + steps;
    double cmd_dez     = (upperVal-512.0)*steeringVal+512.0;

    if (steeringVal!=gamepadAxisLeftX)
    {
        QJsonObject msg2;
        msg2.insert("cmd", QJsonValue::fromVariant("steer"));
        msg2.insert("data", QJsonValue::fromVariant(round(cmd_dez)));
        QJsonDocument doc2(msg2);
        QString strJson2(doc2.toJson(QJsonDocument::Compact));
        emit sendMsg(strJson2);
    }
    gamepadAxisLeftX   = steeringVal; // to check old one

    // Camera tilt input
    if((m_gamepad->axisRightX()!=gamepadAxisRightX)|| (m_gamepad->axisRightY()!=gamepadAxisRightY))
    {
        QJsonObject msg3;
        QJsonObject panTiltData;
        msg3.insert("cmd", QJsonValue::fromVariant("pantilt"));
        panTiltData.insert("pan", QJsonValue::fromVariant(round(127.0*m_gamepad->axisRightX()+127.0)));
        panTiltData.insert("tilt", QJsonValue::fromVariant(round(-127.0*m_gamepad->axisRightY()+127.0)));

        msg3.insert("data",panTiltData);
        QJsonDocument doc3(msg3);
        QString strJson3(doc3.toJson(QJsonDocument::Compact));
        emit sendMsg(strJson3);
    }
    gamepadAxisRightX = m_gamepad->axisRightX();
    gamepadAxisRightY = m_gamepad->axisRightY();
    }


}

void MainWindow::on_PointTurn_clicked()
{
    turnPoint = !turnPoint;
    QJsonObject msg;
    msg.insert("cmd", QJsonValue::fromVariant("pointturn"));
    msg.insert("data", QJsonValue::fromVariant(turnPoint));
    QJsonDocument doc(msg);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    emit sendMsg(strJson);
}


void MainWindow::on_flagDrop_clicked()
{
    flagDrop = !flagDrop;
    QJsonObject msg;
    msg.insert("cmd", QJsonValue::fromVariant("flag"));
    msg.insert("data", QJsonValue::fromVariant(flagDrop));
    QJsonDocument doc(msg);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    emit sendMsg(strJson);
}

void MainWindow::openUrl()
{
    QString url =
            QInputDialog::getText(this, tr("Open Url"), tr("Enter the URL you want to play"));

    if (url.isEmpty())
        return;

    _media = new VlcMedia(url, _instance);

    _player->open(_media);
}

