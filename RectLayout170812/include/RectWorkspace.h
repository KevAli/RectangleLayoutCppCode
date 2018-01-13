#ifndef RECTWORKSPACE_H
#define RECTWORKSPACE_H
#include<string>
#include<LowLineList.h>

class RectWorkspace
{
public:
    string name;
    int height;
    int width;
    list<RectModule> mdls;
    list<RectModule> mdsr;
    list<list<RectModule> > mdlsch;

    LowLineList lowlinelist;

    void sortByValue();
    void layoutWithLowLine();
    void putModule(RectModule& curModule,LowLine& curLowLine);
    int getMixHeight();
    RectWorkspace(string name,int height ,int width);
    virtual ~RectWorkspace();

protected:

private:
};

#endif // RECTWORKSPACE_H
