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
    cout<<"01--01   begin layoutWithFitness inside"<<endl;
    //清空需要用到的列表结构
    this->mdsr.clear();
    this->mdlsch.clear();
    this->lowlinelist.setGuard(this->width,this->height);
    list<RectModule> mymdls;
    list<RectModule>::iterator copyIter = this->mdls.begin();
    cout<<"Begin         Copy RectModule"<<endl;
    while(copyIter!=this->mdls.end())
    {
        mymdls.push_back(*copyIter);
        copyIter++;
    }
    cout<<"After         Copy RectModule"<<endl;

    cout<<"Begin         while(!mymdls.empty())"<<endl;
    while(!mymdls.empty())
    {
        int mixHeightOfModule = this->getMixHeight();
        list<RectModule>::iterator curRectIter = mymdls.begin();
        while(curRectIter!=mymdls.end())
        {
            cout<<"Begin         while(curRectIter!=mymdls.end())"<<endl;
            this->lowlinelist.del_0_wid_line();//获取最低水平线前先删除长度为0的水平线
            LowLine& mixLowline = this->lowlinelist.getMixLowline();
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

            list<RectModule> packingList;
            for(int i=0; i<maxNum || curRectIter==mymdls.end(); i++)
            {
                cout<<"Begin         for(int i=0; i<maxNum || curRectIter==mymdls.end(); i++)"<<endl;
                if(curRectIter->width <= mixLowline.width && curRectIter->height+mixLowline.y <=this->height)//如果横着可以放得下
                {
                    //先计算适应度，再创建一个PackingRectModule对象
                    double x_fitness = curRectIter->width/mixLowline.width;
                    double y_fitness = curRectIter->height/(this->height-mixLowline.y);
                    double fitness =x_weight*x_fitness+y_weight*y_fitness;
//                    PackingRectModule curPackingMD = PackingRectModule((*curRectIter),fitness);
                    curRectIter->fitness = fitness;
                    packingList.push_back(*curRectIter);
                    curRectIter++;
                }
                //如果可以转置,且竖着可以放得下则转置后排放，否则什么也不做
                else if(curRectIter->transable==true && curRectIter->height <= mixLowline.width && curRectIter->width+mixLowline.y <= this->height)
                {
                    curRectIter->trans();
                    int x_fitness = curRectIter->width/mixLowline.width;
                    int y_fitness = curRectIter->height/(this->height-mixLowline.y);
                    int fitness =x_weight*x_fitness+y_weight*y_fitness;
                    //PackingRectModule curPackingMD = PackingRectModule(*curRectIter,fitness);
                    //packingList.push_back(curPackingMD);
                    curRectIter->fitness = fitness;
                    packingList.push_back(*curRectIter);
                    curRectIter++;
                }
                else
                {
                    //总之该当前模块放不下
                    curRectIter++;
                    i--;
                    if(curRectIter==mymdls.end())
                    {
                        break;
                    }
                }
            }
            cout<<"After         for(int i=0; i<maxNum || curRectIter==mymdls.end(); i++)"<<endl;
            //根据packlist是否为空来确定要如何操作
            if(packingList.empty())
            {
                cout<<"packinglist is empty"<<endl;
                //为空则表示当前水平线放不下任何一个矩形，必须更新水平线
                mixLowline.updateY(this->lowlinelist.getByx2(mixLowline.x1),this->lowlinelist.getByx1(mixLowline.x2));
            }
            else
            {
                cout<<"packinglist is not empty     "<<packingList.size()<<"    mymdls:"<<mymdls.size()<<endl;
                //列表不为空，表示至少有一个能放的进去，则把优先级最高且适应度最高的放进去
                packingList.sort(RectModule::sortByFitness);
                list<RectModule>::iterator packIter = packingList.begin();
                packIter->packed =  true;
                this->putModule(*packIter,mixLowline);
//                RectModule firstPacking = packingList.front();
//                this->putModule(firstPacking,mixLowline);
//                firstPacking.packed = 1;
                packingList.clear();

                list<RectModule>::iterator delIter = mymdls.begin();
                while(delIter!=mymdls.end())
                {
                    cout<<"inside  while(delIter!=mymdls.end())"<<endl;
                    cout<<"x="<<delIter->x<<",y="<<delIter->y<<",packed:"<<delIter->packed<<endl;
                    if(delIter->packed==true)
                    {
                        mymdls.erase(delIter);
                        break;
                    }
                    delIter++;
                    //cout<<mymdls.size()<<endl;
                }
                cout<<"After  while(delIter!=mymdls.end())"<<endl;
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
    return PackingScheme(this->mdlsch,x_weight,y_weight);
}

