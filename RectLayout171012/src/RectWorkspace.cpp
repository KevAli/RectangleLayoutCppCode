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
            //如果可以转置,且竖着可以放得下则转置后排放，否则什么也不做
            else if(curRectIter->transable==true && curRectIter->height <= mixLowline.width && curRectIter->width+mixLowline.y <= this->height)
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
PackingScheme RectWorkspace::layoutWithFitness(double x_weight,double y_weight,int maxNum)
{
    //cout<<"01--01   begin layoutWithFitness inside"<<endl;
    //清空需要用到的列表结构
    this->mdsr.clear();
    this->mdlsch.clear();
    this->lowlinelist.setGuard(this->width,this->height);
    list<RectModule> mymdls;
    list<RectModule>::iterator copyIter = this->mdls.begin();
    //cout<<"Begin         Copy RectModule"<<endl;
    while(copyIter!=this->mdls.end())
    {
        //copyIter->selfIter = copyIter;
        mymdls.push_back(*copyIter);
        copyIter++;
    }
    while(!mymdls.empty())
    {//待排序矩形件列表不为空
        int mixHeightOfModule = this->getMixHeight();//获取最低高度的矩形件
        list<RectModule>::iterator curRectIter = mymdls.begin();
        while(curRectIter!=mymdls.end())
        {
            this->lowlinelist.del_0_wid_line();//获取最低水平线前先删除长度为0的水平线
            //cout<<"before get MixLowLine"<<endl;
            LowLine& mixLowline = this->lowlinelist.getMixLowline();//获取最低水平线
            //cout<<"After get MixLowLine, Mixlowline.y="<<mixLowline.y<<",   Mixlowline.width="<<mixLowline.width<<endl;
            if(mixLowline.y == this->height)
            {//最低水平线已经达到了工作台的高度，换板子
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
            list<list<RectModule>::iterator> packingIter;
            for(int i=0; i<maxNum && curRectIter!=mymdls.end();)
            {//选取maxNum个可以放得下的矩形计算适应度，选取适应度最高的排放
                //cout<<i<<endl;
                if(curRectIter->width <= mixLowline.width && curRectIter->height+mixLowline.y <=this->height)//如果横着可以放得下
                {
                    double x_fitness = (double)curRectIter->width/(double)mixLowline.width;
                    double y_fitness = (double)curRectIter->height/(double)(this->height-mixLowline.y);
                    double fitness = x_fitness*x_weight+y_fitness*y_weight;
                    curRectIter->fitness = fitness;
                    //packingIter[i]=curRectIter;
                    packingIter.push_back(curRectIter);
                    curRectIter++;
                    i++;
                    continue;
                }
                //如果可以转置,且竖着可以放得下则转置后排放，否则什么也不做
                else if(curRectIter->transable==true && curRectIter->height <= mixLowline.width && curRectIter->width+mixLowline.y <= this->height)
                {
                    curRectIter->trans();
                    double x_fitness = (double)curRectIter->width/(double)mixLowline.width;
                    double y_fitness = (double)curRectIter->height/(double)(this->height-mixLowline.y);
                    double fitness = x_fitness*x_weight+y_fitness*y_weight;
                    curRectIter->fitness = fitness;
                    //packingIter[i]=curRectIter;
                    packingIter.push_back(curRectIter);
                    curRectIter++;
                    i++;
                    continue;
                }
                else
                {
                    curRectIter++;
                }
            }
            if(packingIter.empty())
            {
                //为空，则更新最低水平线
                //cout<<"packingIter is empty! "<<endl;
                mixLowline.updateY(this->lowlinelist.getByx2(mixLowline.x1),this->lowlinelist.getByx1(mixLowline.x2));
                break;
            }
            else
            {
                //不为空，则找到fitness最大的那个值，放入到mdsr中
                //cout<<"packingIter is not empty! "<<endl;
                packingIter.sort(RectModule::sortByFitness);
                this->putModule(*packingIter.front(),mixLowline);
                mymdls.erase(packingIter.front());
                break;
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


    //以下代码验证了iterator可以二次赋值
//    copyIter=mymdls.begin();
//    list<RectModule>::iterator copyIter2;
//    while(copyIter!=mymdls.end())
//    {
//        copyIter2=copyIter;
//        //copyIter->selfIter = copyIter;
//        cout<<copyIter2->name<<endl;
//        copyIter++;
//    }
    return PackingScheme(this->mdlsch,x_weight,y_weight);
}

