#include <iostream>
#include <string>
#include <list>
using namespace std;


bool compareMethod(string a,string b)
{
    return a.size() < b.size();
}
int main()
{
    string srtList[]= {"a","ab","ab2","a1234","a23451","a125","a125125","a125","a",};
    list<string> strlist;

    for(int i=0; i<9; i++)
    {
        cout<<srtList[i]<<endl;
        strlist.push_back(srtList[i]);
    }
    cout<<"________________________________"<<endl;

    strlist.sort(compareMethod);
    list<string>::iterator iter = strlist.begin();
    while(iter!=strlist.end())
    {
        cout<<*iter<<endl;
        iter++;
    }


}

