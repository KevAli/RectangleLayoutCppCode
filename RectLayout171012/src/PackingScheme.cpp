#include "PackingScheme.h"
using namespace std;
PackingScheme::PackingScheme()
{

}

PackingScheme::PackingScheme(list<list<RectModule> >& mdlsch,double x_weight,double y_weight)
{
    this->mdlsch=mdlsch;
    this->x_weight=x_weight;
    this->y_weight=y_weight;
    this->boardNums = mdlsch.size();
    list<RectModule> lastboard = this->mdlsch.back();
    list<RectModule>::iterator iter = lastboard.begin();
    int maxheight=0;
    while(iter!=lastboard.end())
    {
        if(iter->y+iter->height > maxheight)
        {
            maxheight=iter->y+iter->height;
        }
        iter++;
    }
    this->lastBoardHeight = maxheight;

//    list<RectModule> lastboard1 = mdlsch.back();
//    list<RectModule>::iterator iter = lastboard.begin();
//    int maxheight=0;
//    while(iter!=lastboard.end())
//    {
//        if(iter->y+iter->height > maxheight)
//        {
//            maxheight = iter->y+iter->height;
//        }
//        iter++;
//    }
//    this->lastBoardHeight = maxheight;
}

PackingScheme::~PackingScheme()
{
    //dtor
}
bool PackingScheme::operator<(PackingScheme other)
{
    if(this->boardNums!=other.boardNums)
    {
        return this->boardNums<other.boardNums;
    }
    else
    {
        return this->lastBoardHeight < other.lastBoardHeight;
    }
}
