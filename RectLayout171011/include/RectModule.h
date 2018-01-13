#ifndef RECTMODULE_H
#define RECTMODULE_H
#include<string>
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
    static bool sortByFitness(RectModule a1,RectModule a2);
    RectModule();
    RectModule(string name, int height, int width, int timelim);
    virtual ~RectModule();

protected:

private:
};

#endif // RECTMODULE_H
