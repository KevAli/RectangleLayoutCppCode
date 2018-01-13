#ifndef PACKINGRECTMODULE_H
#define PACKINGRECTMODULE_H
#include "RectModule.h"

class PackingRectModule
{
public:
    RectModule packingRectModule;
    int fitness;
    int weight;

    bool operator<(PackingRectModule other);
    //PackingRectModule();
    PackingRectModule(RectModule packingRectMD,int fit );
    virtual ~PackingRectModule();

protected:

private:
};

#endif // PACKINGRECTMODULE_H
