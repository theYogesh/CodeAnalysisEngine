//String Concatenation

#include<iostream>
#include<String.h>

using namespace std;

int main()
{
    char a[25],b[25],c[50];
    cout<<"Enter String 1 : ";
    cin>>a;
    cout<<"\nEnter String 2: ";
    cin>>b;
    strcpy(c,a);
    strcat(c,b);
    cout<<"\nString 1="<<a<<"\tString 2="<<b<<"\nConcatenate="<<c;
}
