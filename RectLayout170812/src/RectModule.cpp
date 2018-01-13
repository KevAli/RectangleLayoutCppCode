#include "RectModule.h"

void RectModule::trans()
{
    int a = this->height;
    this->height = this->width;
    this->width = a;
}

bool RectModule::operator<(RectModule other)
{
    return other.value < this->value;
}

RectModule::RectModule(string name, int height, int width, int timelim)
{
    this->name = name;
    //保证宽比长要小
    if (height < width)
    {
        this->height = height;
        this->width = width;
    }
    else
    {
        this->height = width;
        this->width = height;
    }
    this->timelim = timelim;
    this->area = height*width;
    this->value = (height * width ) / (timelim* 1000);
    this->x = 0;
    this->y = 0;
}

RectModule::~RectModule()
{

}
