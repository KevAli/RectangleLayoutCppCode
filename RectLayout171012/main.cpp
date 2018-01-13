#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "RectWorkspace.h"

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    vector<string> dataParams;
    int wk_height,wk_width;
    ifstream in("/a.txt");
    if(!in)
    {
        cout<<"Fail in opening file 'a.txt'"<<endl;
        return -1;
    }
    ofstream out("/b.txt");
    if(!out)
    {
        cout<<"Fail in opening file 'b.txt'"<<endl;
        return -1;
    }
    string s,p;
    getline(in,s);
    //cout<<s<<endl;
    for(unsigned int i=0; i<=s.size(); i++)
    {
        //读取工作台的数据
        char c=s[i];
        if(c!='-')
        {
            p+=c;
        }
        if(c=='-')
        {
            dataParams.push_back(p);
            //cout<<p<<endl;
            p="";
        }
        if(c=='\0')
        {
            dataParams.push_back(p);
            //cout<<p<<endl;
            p="";
            //cout<<dataParams[0]<<","<<dataParams[1]<<endl;
            wk_height=atoi(dataParams[0].c_str());
            wk_width=atoi(dataParams[1].c_str());

//            cout<<"name="<<workspace.name<<",height="<<workspace.height<<",width="<<workspace.width<<endl<<endl;
            dataParams.clear();
        }
    }

    RectWorkspace workspace = RectWorkspace("RectLayoutWithLowLine",wk_height,wk_width);
    //cout<<"name="<<workspace.name<<",   height="<<workspace.height<<",  width="<<workspace.width<<endl<<endl;
    //cout<<"spaceInitOver——工作台数据读取成功"<<endl;

    while(!in.eof())
    {
        getline(in,s);
        //cout<<s<<endl;
        for(unsigned int i=0; i<=s.size(); i++)
        {
            char c=s[i];
            if(c!='-')
            {
                p+=c;
            }
            if(c=='-')
            {
                dataParams.push_back(p);
                //cout<<p<<"-";
                p="";
            }
            if(c=='\0')
            {
                dataParams.push_back(p);
                //cout<<p<<endl;
                p="";
                // atof(str.c_str())
                double cnt =atof(dataParams[4].c_str()); //stringtoNum(dataParams[4]);
                //double mdl_heitht = atof()
                for(int i=0; i<cnt; i++)
                {
                    //char c0=i;
                    RectModule mdl=RectModule((dataParams[0]),atof(dataParams[1].c_str()),atof(dataParams[2].c_str()),atof(dataParams[3].c_str()));
                    workspace.mdls.push_back(mdl);
                    //cout<<mdl.name<<endl;

                }
                //cout<<dataParams[0]<<","<<dataParams[1]<<','<<dataParams[2]<<','<<dataParams[3]<<','<<dataParams[4]<<endl;
                dataParams.clear();

            }
        }

    }
    //cout<<"RectModule Data Init Over矩形部件数据读取成功"<<endl;
    in.close();
    workspace.sortByValue();
    //cout<<"workspace sortOfValue Over"<<endl;

    for(list<RectModule>::iterator iter = workspace.mdls.begin(); iter!=workspace.mdls.end(); iter++)
    {
        //cout<<"Start Write"<<endl;
        out<<"     name="<<iter->name<<"- height="<<iter->height<<"- width="<<iter->width<<"- timelimit="<<iter->timelim<<"- value="<<iter->value;
        out<<"- X="<<iter->x<<"- Y="<<iter->y<<endl;
    }
    out<<"-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;

    //直接排列
    //workspace.layoutWithLowLine();
    //cout<<"Layout with Lowline Over"<<endl;
    //用适应度排列
    cout<<"01--     Begin layoutWithFitness"<<endl;
    //PackingScheme firScheme =workspace.layoutWithFitness(1,1,10);
    //workspace.mdlsch = firScheme.mdlsch;
    list<PackingScheme> Schemes;
    double BigestTimes = 100;
    int BigestDetects = 100;
    for(double i=0; i<BigestTimes; i++)
    {
        double x_weight=0+i*(1.0/BigestTimes);
        double y_weight=1-i*(1.0/BigestTimes);
        PackingScheme Scheme =workspace.layoutWithFitness(x_weight,y_weight,BigestDetects);
        cout<<Scheme.boardNums<<"       "<<Scheme.lastBoardHeight<<endl;
        Schemes.push_back(Scheme);
    }
//    for(list<PackingScheme>::iterator schiter=Schemes.begin();schiter!=Schemes.end();schiter++)
//    {
//        cout<<schiter->boardNums<<"       "<<schiter->lastBoardHeight<<endl;
//    }

    Schemes.sort();
    workspace.mdlsch = Schemes.front().mdlsch;
    cout<<"02--     After layoutWithFitness"<<endl;



    out<<"Board Numbers:   "<<Schemes.front().boardNums<<endl;
    out<<"lastBoardHeight:   "<<Schemes.front().lastBoardHeight<<endl;
    int i=0;
    while(!workspace.mdlsch.empty())
    {

        list<RectModule> layoutsch = workspace.mdlsch.front();
        i++;
        out<<"this is the NO."<<i<<" Workspace:"<<endl;
        for(list<RectModule>::iterator iter = layoutsch.begin(); iter!=layoutsch.end(); iter++)
        {
            //cout<<"Start Write"<<endl;
            out<<"     name="<<iter->name<<"- height="<<iter->height<<"- width="<<iter->width<<"- timelimit="<<iter->timelim<<"- value="<<iter->value;
            out<<"- X="<<iter->x<<"- Y="<<iter->y<<",   fitness=" <<iter->fitness<<endl;
        }
        workspace.mdlsch.pop_front();
    }

    out<<endl<<"the least of mdsr :"<<endl;
    for(list<RectModule>::iterator iter = workspace.mdsr.begin(); iter!=workspace.mdsr.end(); iter++)
    {
        //cout<<"Start Write"<<endl;
        out<<"     name="<<iter->name<<"- height="<<iter->height<<"- width="<<iter->width<<"- timelimit="<<iter->timelim<<"- value="<<iter->value;
        out<<"- X="<<iter->x<<"- Y="<<iter->y<<endl;
    }

    out.close();

    return 0;
}
