//Triangle

#include<iostream>

using namespace std;



int isTriangle(double,double,double);

int main()
{double a,b,c;
    

cout<<"\nEnter 3 sides of the triangle : ";cin>>a>>b>>c;
if(isTriangle(a,b,c))
{
if((a==b)&&(a==c))
{
            cout<<"\nResult : Equilateral Triangle";
}
   else if((a==b)||(a==c)||(b==c))
 {
cout<<"\nResult : Isosceles Triangle";
        }
else
        {cout<<"\nResult : Scalene Triangle";
        }
}
else
    {        cout<<"\nResult : NOT A TRIANGLE ";
    }return 0;}

int isTriangle(double a,double b,double c)
{    if((a<=0)||(b<=0)||(c<=0))
    {   return 0;
    }
    	if(a+b<=c)
    	{   return 0;}
    	if(a+c<=b)
    	{
        		return 0;
    			}
    if(b+c<=a)
    {    return 0;
    }}
