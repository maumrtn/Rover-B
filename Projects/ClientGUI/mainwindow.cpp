#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arrowpad.h"
#include "ledindicator.h"
#include "qledindicator.h"
#include "clientsocket.h"
#include "cvimagewidget.h"


#include <QtWidgets>
#include <QDebug>
#include <QFile>


#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->client = NULL;

    ui->setupUi(this);
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

connect(ui->imageBotton,SIGNAL(clicked()),this,SLOT(imageChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeText()
{
    ui->console->append("UP");
}

void MainWindow::imageChanged()
{
    cv::Mat image = cv::imread("/home/maumrtn/Qt/Projects/ClientGUI/red_eyes2.jpg", true);
    cv::Size size(500,500);
    cv::resize(image,image,size);
    imageWidget->showImage(image);

}

void MainWindow::on_createButton_clicked()
{
    QString fileName = ui->lineEdit->text();
    QFile myFile(fileName);

    if ( myFile.open(QIODevice::ReadWrite))
   {
       QTextStream stream(&myFile);
        stream << "hello World";
   }
    myFile.close();
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
    servoLED->toggle();
    ui->console->append("Starting initialization of servos...");
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
}


void MainWindow::on_connectButton_clicked()
{
    /*clientSocket socket;
    socket.Test();*/

    if (this->client == NULL)
    {
        bool debug = 1;
        this->client = new EchoClient(QUrl(QStringLiteral("ws://localhost:8080")), debug);
        ui->console->append("Connected!");
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
