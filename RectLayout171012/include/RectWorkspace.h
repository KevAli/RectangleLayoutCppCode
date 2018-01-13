#ifndef RECTWORKSPACE_H
#define RECTWORKSPACE_H
#include<string>
#include"LowLineList.h"
#include"PackingScheme.h"
#include<vector>


class RectWorkspace
{
public:
    string name;
    int height;
    int width;
    list<RectModule> mdls;
    list<RectModule> mdsr;
    list<list<RectModule> > mdlsch;
    PackingScheme bestPackingScheme;

    LowLineList lowlinelist;

    void sortByValue();
    void layoutWithLowLine();
    PackingScheme layoutWithFitness(double x_weight,double y_weight,int maxNum);
    void putModule(RectModule& curModule,LowLine& curLowLine);
    int getMixHeight();
    RectWorkspace(string name,int height ,int width);
    virtual ~RectWorkspace();

protected:

private:
};

#endif // RECTWORKSPACE_H
