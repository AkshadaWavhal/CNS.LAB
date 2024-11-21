//
#include<iostream>
using namespace std;
int main()
{
	string txt;
	cout<<"enter the string: ";
	cin>>txt;
	for(int i=0;i<txt.length();i++)
	{
		txt[i]=txt[i]+3;
	}
	cout<<txt;
}
