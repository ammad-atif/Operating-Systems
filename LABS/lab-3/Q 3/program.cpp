 #include <iostream> 
#include <unistd.h> 
#include<fstream>
#include<sys/wait.h>
using namespace std; 

int frequency_Substr(string str)
{
    int count=0;
    for (int n = 0; n <str.size(); n++)
    {
            if (str[n] == 'a' || str[n] == 'o' || str[n] == 'e' || str[n] == 'i' || str[n] == 'u' || str[n] == 'A' ||str[n] == 'E' ||str[n] == 'O' ||str[n] == 'I' ||str[n] == 'U')
            {
               count++;
            }
    }
    return count;
}
void print()
{
    fstream a;
    int count=0;
    a.open("question1.txt");
    if(a.is_open())
    {
    while (!a.eof())
    {
        string str;
        getline(a,str);
        count+=frequency_Substr(str);
    }
     cout<<count<<endl;
    }
    else
    {
        cout<<"NO SUCH FILE EXISTS"<<endl;
    }
}

int main() 
{ 
    int c_pid = fork(); 

	if (c_pid <0) { 
		cout<<"ERROR"<<endl;
	} 
	else if (c_pid > 0) { 
		 wait(nullptr); 
		cout << "PROGRAM COMPLETED"<< endl; 
	} 
	else { 
		print();
	} 

	return 0; 
}
