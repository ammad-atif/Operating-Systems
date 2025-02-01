#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	string str;
	fstream f;
	f.open("input.txt");
	while (!f.eof())
	{
		char c;
		f.get(c);
		if (c>='0'&&c<='9')
		{
			str = str + c;
		}
	}
	f.close();
	cout << str;
}
