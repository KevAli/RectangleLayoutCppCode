#include "RectWorkspace.h"
#include<iostream>
using namespace std;
RectWorkspace::~RectWorkspace()
{
    //dtor
}
void RectWorkspace::sortByValue()
{
    this->mdls.sort();
}

int RectWorkspace::getMixHeight()
{
    list<RectModule>::iterator iter = this->mdls.begin();
    int mixH=iter->height;
    while(iter != this->mdls.end())
    {
        if(iter->height < mixH)
        {
            mixH = iter->height;
        }
        iter++;
    }
    return mixH;
}

RectWorkspace::RectWorkspace(string name, int height, int width)
{
    this->name = name;
    if(height<=width)
    {
        this->width = width;
        this->height = height;
    }
    else
    {
        this->width = height;
        this->height = width;
    }
    this->lowlinelist.setGuard(this->width,this->height);
}
void RectWorkspace::putModule(RectModule& curModule,LowLine& curLowLine)
{
    //cout<<"PutModule is called"<<endl;
    curModule.x = curLowLine.x1;
    curModule.y = curLowLine.y;
    LowLine newLowLine = LowLine(curLowLine.x1,curLowLine.x1+curModule.width,curLowLine.y+curModule.height);
    curLowLine.x1 = newLowLine.x2;
    curLowLine.setWidth();
    newLowLine.merge_left(this->lowlinelist.getByx2(newLowLine.x1));
    newLowLine.merge_right(this->lowlinelist.getByx1(newLowLine.x2));
    this->lowlinelist.add_lowline(newLowLine);
    this->mdsr.push_back(curModule);

}

void RectWorkspace::layoutWithLowLine()
{
    while(!this->mdls.empty())
    {
        //cout<<"mdls is not empty "<<endl;
        int mixHeightOfModule = this->getMixHeight();
        list<RectModule>::iterator curRectIter = this->mdls.begin();
        while(curRectIter!=this->mdls.end())
        {
            this->lowlinelist.del_0_wid_line();//获取最低水平线前先删除长度为0的水平线
            //cout<<"before get MixLowLine"<<endl;
            LowLine& mixLowline = this->lowlinelist.getMixLowline();
            //cout<<"After get MixLowLine, Mixlowline.y="<<mixLowline.y<<",   Mixlowline.width="<<mixLowline.width<<endl;
            if(mixLowline.y == this->height)
            {
                //cout<<"mixLowLine.y == this->height"<<endl;
                this->mdlsch.push_back(this->mdsr);
                this->mdsr.clear();
                this->lowlinelist.setGuard(this->width,this->height);
                continue;
            }
            if(mixLowline.width<mixHeightOfModule)//如果最小的肯定放不下，更新最低水平线，跳出此次循环继续下一次循环
            {
                //cout<<"mixLowline.width<mixHeightOfModule"<<endl;
                mixLowline.updateY(this->lowlinelist.getByx2(mixLowline.x1),this->lowlinelist.getByx1(mixLowline.x2));
                continue;
            }
            if(curRectIter->width <= mixLowline.width && curRectIter->height+mixLowline.y <=this->height)//如果横着可以放得下
            {
                this->putModule(*curRectIter,mixLowline);
                this->mdls.erase(curRectIter);
                break;
            }
            else if(curRectIter->height <= mixLowline.width && curRectIter->width+mixLowline.y <= this->height)//如果竖着可以放得下
            {
                curRectIter->trans();
                this->putModule(*curRectIter,mixLowline);
                this->mdls.erase(curRectIter);
                break;
            }
            else//横竖都放不下
            {
                curRectIter++;
                if(curRectIter==this->mdls.end())
                {
                    //cout<<"curRectIter==this->mdls.end()"<<endl;
                    mixLowline.updateY(this->lowlinelist.getByx2(mixLowline.x1),this->lowlinelist.getByx1(mixLowline.x2));
                }
            }
        }

    }
    if(!this->mdsr.empty())
    {
        //cout<<"The mdls is empty but the mdsr is not empty "<<endl;
        this->mdlsch.push_back(this->mdsr);
        this->mdsr.clear();
        this->lowlinelist.setGuard(this->width,this->height);

    }

}
