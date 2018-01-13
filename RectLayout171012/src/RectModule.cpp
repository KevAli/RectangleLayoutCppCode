#include "RectModule.h"

void RectModule::trans()
{
    int a = this->height;
    this->height = this->width;
    this->width = a;
}

bool RectModule::operator<(RectModule other)
{
    if(other.priority!=this->priority)
    {
        return this->priority < other.priority;
    }
    else
    {
        return other.area < this->area;
    }
//    return other.value < this->value;
}
bool RectModule::sortByFitness(list<RectModule>::iterator a1,list<RectModule>::iterator a2)
{
    if(a1->priority!=a2->priority)
    {
        return a1->priority < a2->priority;
    }
    else
    {
        return a1->fitness > a2->fitness;

    }
}


RectModule::RectModule(string name, int height, int width, int timelim)
{
    this->name = name;
    //保证宽比长要小
//    if (height < width)
//    {
//        this->height = height;
//        this->width = width;
//    }
//    else
    {
        this->height = width;
        this->width = height;
    }
    this->timelim = timelim;
    this->priority = timelim;
    this->area = height*width;
    this->value = (height*width) * (timelim) / 1000;
    this->x = 0;
    this->y = 0;
    this->transable = true;
    this->packed = false;
}
RectModule::RectModule()
{

}

RectModule::~RectModule()
{

}
