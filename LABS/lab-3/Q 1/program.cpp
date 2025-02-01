#include <iostream>
#include<fstream>
#include<string>
using namespace std;
int frequency_Substr(string str,string substr)
{
    int count=0;
    for (int i = 0; i <str.size()-1; i++)
    {
        int m = 0;
        int n = i;
        for (int j = 0; j < substr.size(); j++)
        {
            if (str[n] == substr[j])
            {
                m++;
            }
            n++;
        }
        if (m == substr.size())
        {
            count++;
        }
    
    }
    return count;
}
int main(int n,char*arg[])
{
    fstream a;
    int count=0;
    a.open(arg[1]);
    if(a.is_open())
    {
    while (!a.eof())
    {
        string str;
        getline(a,str);
        count+=frequency_Substr(str,arg[2]);
    }
     cout<<count<<endl;
    }
    else
    {
        cout<<"NO SUCH FILE EXISTS"<<endl;
    }
}