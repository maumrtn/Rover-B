#ifndef ARROWPAD_H
#define ARROWPAD_H

#include <QWidget>

class QPushButton;


class ArrowPad : public QWidget
{
    Q_OBJECT
public:
    ArrowPad(QWidget *parent = 0);
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *stopButton;
private:




// Define slots
private slots:
    void onUpButtonClick();
    void onDownButtonClick();
    void onLeftButtonClick();
    void onRightButtonClick();
};
#endif // ARROWPAD_H
