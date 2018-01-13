#ifndef LOWLINE_H
#define LOWLINE_H
#include<list>

class LowLine
{
public:
    int x1;
    int x2;
    int y;
    int left_y;
    int right_y;
    int width;

    void setWidth();
    void merge_left(LowLine &left_l);
    void merge_right(LowLine &right_l);
    void updateY(LowLine& leftLine,LowLine& rightLine);
    bool operator<(LowLine o);

    LowLine(int x1, int x2, int y);
    virtual ~LowLine();

protected:

private:
};

#endif // LOWLINE_H
