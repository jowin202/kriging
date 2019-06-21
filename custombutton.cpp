#include "custombutton.h"

CustomButton::CustomButton()
{

}

void CustomButton::setData(int x, int y, int var)
{
    this->x = x;
    this->y = y;
    this->var = var;
}

int CustomButton::getx()
{
    return x;
}

int CustomButton::gety()
{
    return y;
}

int CustomButton::getvar()
{
    return var;
}
