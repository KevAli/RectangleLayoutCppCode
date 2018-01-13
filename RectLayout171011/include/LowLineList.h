#ifndef LOWLINELIST_H
#define LOWLINELIST_H
#include"LowLine.h"
#include<list>
#include"RectModule.h"

class LowLineList
{
public:
    list<LowLine> lowlinelist;

    void add_lowline(LowLine &o);
    void sortByx1();
    void del_0_wid_line();
    void setGuard(int r_Guard_width,int MaxH);

    int getMixY();

    LowLine &getByx1(int x1);
    LowLine &getByx2(int x2);
    LowLine &getByY(int y);
    LowLine &getMixLowline();

    LowLineList();
    virtual ~LowLineList();

protected:

private:
};

#endif // LOWLINELIST_H
