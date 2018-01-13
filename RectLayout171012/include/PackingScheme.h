#ifndef PACKINGSCHEME_H
#define PACKINGSCHEME_H
#include<string>
#include<LowLineList.h>

class PackingScheme
{
public:
    list<list<RectModule> > mdlsch;
    double x_weight;
    double y_weight;
    int boardNums;
    int lastBoardHeight;

    bool operator<(PackingScheme other);

    PackingScheme();
    PackingScheme(list<list<RectModule> >& mdlsch,double x_weight,double y_weight);
    virtual ~PackingScheme();

protected:

private:
};

#endif // PACKINGSCHEME_H
