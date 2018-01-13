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

    void trans();
    bool operator<(RectModule other);
    RectModule(string name, int height, int width, int timelim);
    virtual ~RectModule();

protected:

private:
};

#endif // RECTMODULE_H
