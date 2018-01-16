#include <QtWidgets>
#include "arrowpad.h"

ArrowPad::ArrowPad(QWidget *parent)
    : QWidget(parent)
{
        // define Buttons
        upButton = new QPushButton(tr("&Up"));
        downButton = new QPushButton(tr("&Down"));
        leftButton = new QPushButton(tr("&Left"));
        rightButton = new QPushButton(tr("&Right"));
        stopButton = new QPushButton(tr("&STOP"));

        // Connect signals to slots
        connect(upButton,SIGNAL(clicked()),this,SLOT(onUpButtonClick()));
        connect(downButton, SIGNAL(clicked()), this, SLOT(onDownButtonClick()));
        connect(rightButton, SIGNAL(clicked()), this, SLOT(onRightButtonClick()));
        connect(leftButton, SIGNAL(clicked()), this, SLOT(onLeftButtonClick()));

        // Define Layout
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(upButton, 0, 1);
        mainLayout->addWidget(leftButton, 1, 0);
        mainLayout->addWidget(rightButton, 1, 2);
        mainLayout->addWidget(downButton, 2, 1);
        mainLayout->addWidget(stopButton, 1, 1);
        setLayout(mainLayout);
}
        // Define Slots
        void ArrowPad::onUpButtonClick()
        {
          qDebug() << "onUpButtonClick clicked";
        }
        void ArrowPad::onDownButtonClick()
        {
          qDebug() << "onDownButtonClick clicked";
        }
        void ArrowPad::onLeftButtonClick()
        {
          qDebug() << "onLeftButtonClick clicked";
        }
        void ArrowPad::onRightButtonClick()
        {
          qDebug() << "onRightButtonClick clicked";
        }


