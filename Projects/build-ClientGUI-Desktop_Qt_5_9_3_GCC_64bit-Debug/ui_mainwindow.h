/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionTCP_Connection;
    QWidget *centralWidget;
    QPushButton *connectButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QPushButton *initServo;
    QSpacerItem *verticalSpacer_2;
    QPushButton *initMotors;
    QSpacerItem *verticalSpacer_3;
    QPushButton *initIMU;
    QSpacerItem *verticalSpacer_4;
    QPushButton *initToF;
    QSpacerItem *verticalSpacer_5;
    QPushButton *initCam;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_2;
    QLabel *label_8;
    QLineEdit *lineEdit_3;
    QLabel *label_10;
    QLineEdit *lineEdit_4;
    QLabel *label_9;
    QLineEdit *lineEdit_5;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QLineEdit *speedText;
    QPushButton *createButton;
    QTextEdit *console;
    QLabel *label;
    QSlider *verticalSlider;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer;
    QWidget *gridLayoutWidget;
    QGridLayout *imageGrid;
    QPushButton *imageBotton;
    QMenuBar *menuBar;
    QMenu *menuSettings;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1194, 685);
        actionTCP_Connection = new QAction(MainWindow);
        actionTCP_Connection->setObjectName(QStringLiteral("actionTCP_Connection"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(650, 380, 91, 21));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(430, 10, 185, 272));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setTextFormat(Qt::AutoText);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(82, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 1);

        initServo = new QPushButton(layoutWidget);
        initServo->setObjectName(QStringLiteral("initServo"));

        gridLayout_2->addWidget(initServo, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(82, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 0, 1, 1);

        initMotors = new QPushButton(layoutWidget);
        initMotors->setObjectName(QStringLiteral("initMotors"));

        gridLayout_2->addWidget(initMotors, 4, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(82, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 5, 0, 1, 1);

        initIMU = new QPushButton(layoutWidget);
        initIMU->setObjectName(QStringLiteral("initIMU"));

        gridLayout_2->addWidget(initIMU, 6, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(82, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 7, 0, 1, 1);

        initToF = new QPushButton(layoutWidget);
        initToF->setObjectName(QStringLiteral("initToF"));

        gridLayout_2->addWidget(initToF, 8, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(82, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_5, 9, 0, 1, 1);

        initCam = new QPushButton(layoutWidget);
        initCam->setObjectName(QStringLiteral("initCam"));

        gridLayout_2->addWidget(initCam, 10, 0, 1, 1);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(650, 10, 290, 167));
        gridLayout_3 = new QGridLayout(layoutWidget1);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setTextFormat(Qt::AutoText);

        gridLayout_3->addWidget(label_3, 0, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(78, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(78, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 3, 1, 1);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setTextFormat(Qt::AutoText);

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setTextFormat(Qt::AutoText);

        gridLayout_3->addWidget(label_5, 1, 1, 1, 2);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setTextFormat(Qt::AutoText);

        gridLayout_3->addWidget(label_6, 1, 3, 1, 1);

        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setTextFormat(Qt::AutoText);

        gridLayout_3->addWidget(label_7, 2, 0, 1, 1);

        lineEdit_2 = new QLineEdit(layoutWidget1);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_3->addWidget(lineEdit_2, 2, 1, 1, 2);

        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setTextFormat(Qt::AutoText);

        gridLayout_3->addWidget(label_8, 3, 0, 1, 1);

        lineEdit_3 = new QLineEdit(layoutWidget1);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout_3->addWidget(lineEdit_3, 3, 1, 1, 2);

        label_10 = new QLabel(layoutWidget1);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setTextFormat(Qt::AutoText);

        gridLayout_3->addWidget(label_10, 4, 0, 1, 1);

        lineEdit_4 = new QLineEdit(layoutWidget1);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout_3->addWidget(lineEdit_4, 4, 1, 1, 2);

        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setTextFormat(Qt::AutoText);

        gridLayout_3->addWidget(label_9, 5, 0, 1, 1);

        lineEdit_5 = new QLineEdit(layoutWidget1);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        gridLayout_3->addWidget(lineEdit_5, 5, 1, 1, 2);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 380, 641, 228));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        speedText = new QLineEdit(layoutWidget2);
        speedText->setObjectName(QStringLiteral("speedText"));
        speedText->setMaximumSize(QSize(25, 25));

        gridLayout->addWidget(speedText, 0, 1, 1, 2);

        createButton = new QPushButton(layoutWidget2);
        createButton->setObjectName(QStringLiteral("createButton"));

        gridLayout->addWidget(createButton, 0, 5, 1, 1);

        console = new QTextEdit(layoutWidget2);
        console->setObjectName(QStringLiteral("console"));

        gridLayout->addWidget(console, 1, 3, 1, 3);

        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 3, 1, 1);

        verticalSlider = new QSlider(layoutWidget2);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verticalSlider, 1, 2, 1, 1);

        lineEdit = new QLineEdit(layoutWidget2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(218, 28, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(218, 28, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 2);

        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 431, 381));
        imageGrid = new QGridLayout(gridLayoutWidget);
        imageGrid->setSpacing(6);
        imageGrid->setContentsMargins(11, 11, 11, 11);
        imageGrid->setObjectName(QStringLiteral("imageGrid"));
        imageGrid->setContentsMargins(0, 0, 0, 0);
        imageBotton = new QPushButton(centralWidget);
        imageBotton->setObjectName(QStringLiteral("imageBotton"));
        imageBotton->setGeometry(QRect(780, 280, 85, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1194, 22));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSettings->menuAction());
        menuSettings->addAction(actionTCP_Connection);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Rover-B GUI", Q_NULLPTR));
        actionTCP_Connection->setText(QApplication::translate("MainWindow", "TCP Connection", Q_NULLPTR));
        connectButton->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Initialization", Q_NULLPTR));
        initServo->setText(QApplication::translate("MainWindow", "Servos", Q_NULLPTR));
        initMotors->setText(QApplication::translate("MainWindow", "Motors", Q_NULLPTR));
        initIMU->setText(QApplication::translate("MainWindow", "IMU", Q_NULLPTR));
        initToF->setText(QApplication::translate("MainWindow", "ToF", Q_NULLPTR));
        initCam->setText(QApplication::translate("MainWindow", "Cam", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Measurements", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Variable", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Value", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Unit", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "A", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "B", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "A", Q_NULLPTR));
        lineEdit_4->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "B", Q_NULLPTR));
        lineEdit_5->setText(QString());
        createButton->setText(QApplication::translate("MainWindow", "Create", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "LOG:", Q_NULLPTR));
        imageBotton->setText(QApplication::translate("MainWindow", "Servos", Q_NULLPTR));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
