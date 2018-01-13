#ifndef RECTMODULE_H
#define RECTMODULE_H
#include<string>
#include<list>
using namespace std;

class RectModule
{
public:
    string name;
    int height;
    int width;
    int timelim;
    int area;
    int value;
    int x;
    int y;
    int priority;
    double fitness;
    bool transable;
    bool packed;

    void trans();
    bool operator<(RectModule other);
    static bool sortByFitness(list<RectModule>::iterator a1,list<RectModule>::iterator a2);
    RectModule();
    RectModule(string name, int height, int width, int timelim);
    virtual ~RectModule();

protected:

private:
};

#endif // RECTMODULE_H
