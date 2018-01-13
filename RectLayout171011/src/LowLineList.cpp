#include "LowLineList.h"
using namespace std;

LowLineList::LowLineList()
{
    //ctor
}

LowLineList::~LowLineList()
{
    //dtor
}
void LowLineList::add_lowline(LowLine& o)
{
    this->lowlinelist.push_back(o);
}

void LowLineList::sortByx1()
{
    this->del_0_wid_line();
    this->lowlinelist.sort();
}

void LowLineList::del_0_wid_line()
{
    list<LowLine>::iterator iter = this->lowlinelist.begin();
    while (iter != this->lowlinelist.end())
    {
        //除了初始化以外不要对迭代器进行赋值操作,有可能引发类似指针的一系列问题
        iter->setWidth();
        //cout<<"delete_0width_lowline-------------set_width over"<<endl;
        //Sleep(1000);
        if (iter->width == 0)
        {
            list<LowLine>::iterator del = iter;
            iter++;
            this->lowlinelist.erase(del);
        }
        else
        {
            iter++;
        }
    }

}

void LowLineList::setGuard(int r_Guard_width, int MaxH)
{
    this->lowlinelist.clear();
    LowLine leftGuard = LowLine(-1,0,MaxH);
    LowLine rightGuard = LowLine(r_Guard_width,r_Guard_width+1,MaxH);
    LowLine firstLowLine = LowLine(0,r_Guard_width,0);
    firstLowLine.merge_left(leftGuard);
    firstLowLine.merge_right(rightGuard);
    this->add_lowline(leftGuard);
    this->add_lowline(firstLowLine);
    this->add_lowline(rightGuard);
}

int LowLineList::getMixY()
{
    list<LowLine>::iterator iter = this->lowlinelist.begin();
    int mixY = iter->y;
    while(iter!=this->lowlinelist.end())
    {
        if(iter->y >=0 && iter->y < mixY)
        {
            mixY = iter->y;
        }
        iter++;
    }
    return mixY;
}

LowLine& LowLineList::getByx1(int x1)
{
    list<LowLine>::iterator iter = this->lowlinelist.begin();
    while(iter != this->lowlinelist.end())
    {
        if(iter->width != 0 && iter->x1 == x1)
        {
            return *iter;
        }
        iter++;
    }
}

LowLine& LowLineList::getByx2(int x2)
{
    list<LowLine>::iterator iter = this->lowlinelist.begin();
    while(iter != this->lowlinelist.end())
    {
        if(iter->width != 0 && iter->x2 == x2)
        {
            return *iter;
        }
        iter++;
    }
}

LowLine& LowLineList::getMixLowline()
{
    return this->getByY(this->getMixY());
}

LowLine& LowLineList::getByY(int y)
{
    list<LowLine>::iterator iter = this->lowlinelist.begin();
    while(iter != this->lowlinelist.end())
    {
        if(iter->width != 0 && iter->y == y)
        {
            return *iter;
        }
        iter++;
    }
}


