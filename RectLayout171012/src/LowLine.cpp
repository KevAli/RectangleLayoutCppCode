#include "LowLine.h"
using namespace std;
LowLine::~LowLine()
{
    //dtor
}
void LowLine::merge_left(LowLine& left_l)
{
    if (this->y == left_l.y)
    {
        this->x1 = left_l.x1;
        this->left_y = left_l.left_y;
        this->setWidth();
        left_l.x2 = left_l.x1;
        left_l.setWidth();
    }
    else
    {
        this->left_y=left_l.y;
        left_l.right_y=this->y;
    }
}

void LowLine::merge_right(LowLine& right_l)
{
    if (this->y == right_l.y)
    {
        this->x2 = right_l.x2;
        this->right_y = right_l.right_y;
        this->setWidth();
        right_l.x1 = right_l.x2;
        right_l.setWidth();
    }
    else
    {
        this->right_y = right_l.y;
        right_l.left_y = this->y;
    }
}

bool LowLine::operator<(LowLine o)
{
    return this->x1 < o.x1;
}

LowLine::LowLine(int x1, int x2, int y)
{
    this->x1 = x1;
    this->x2 = x2;
    this->y = y;
    this->left_y = -1;
    this->right_y = -1;
    this->setWidth();
}
void LowLine::setWidth()
{
    this->width = this->x2 - this->x1;
}
void LowLine::updateY(LowLine& leftLine, LowLine& rightLine)
{
    if(this->left_y <= this->right_y)
    {
        this->y = this->left_y;
    }
    else
    {
        this->y = this->right_y;
    }
    this->merge_left(leftLine);
    this->merge_right(rightLine);
}
