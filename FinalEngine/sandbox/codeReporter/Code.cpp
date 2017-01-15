#include<iostream>
using namespace std;

void f()
{
    char *p; //Uninitialized
    *p = new char;
}

int main()
{
	//This is an example code
  	//Replace this code
  	char str[5];
  	cout<<str[5]; //Out of Bound
	int a;
  	f();
  	cout<<b; //Not declared
  	return 0;
}