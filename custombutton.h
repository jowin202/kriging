#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include <QToolButton>

class CustomButton : public QToolButton
{

public:
    CustomButton();
    void setData(int x, int y, int var);
    int getx();
    int gety();
    int getvar();

private:
    int x;
    int y;
    int var;
};

#endif // CUSTOMBUTTON_H
