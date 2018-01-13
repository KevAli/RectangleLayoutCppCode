#include "PackingRectModule.h"

//PackingRectModule::PackingRectModule()
//{
//    //ctor
//}

PackingRectModule::~PackingRectModule()
{
    //dtor
}
bool PackingRectModule::operator<(PackingRectModule other)
{
    if(this->weight!=other.weight)
    {
        return this->weight < other.weight;
    }
    else
    {
        return other.fitness < this->fitness;
    }
}
PackingRectModule::PackingRectModule(RectModule packingRectMD, int fit)
{
    this->packingRectModule = packingRectMD;
    this->fitness=fit;
    this->weight=packingRectMD.priority;
}
