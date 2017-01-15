#include<fstream>
#include<stdio.h>
#include<iostream>
#include<string.h>

using namespace std;

int isFileExist(char *fname);

int main(int argc,char *argv[])
{
    if(argc!=4)
    {
        cerr<<"\nInvalid Syntax!!!\n";
        return (1);
    }

    char exeName[50]="test.exe";
    char cmd[100];
    strcpy(cmd,"g++ ");
    strcat(cmd,argv[1]);
    strcat(cmd," -o test>");
    strcat(cmd,argv[3]);
    system(cmd);
    if(isFileExist(exeName)==1)
    {
        strcpy(cmd,"test.exe<");
        strcat(cmd,argv[2]);
        strcat(cmd,">");
        strcat(cmd,argv[3]);
        system(cmd);
        
        strcpy(cmd,"del test.exe");
        system(cmd);
    }
    else
    {
        strcpy(cmd,"g++ ");
        strcat(cmd,argv[1]);
        strcat(cmd," 2> ");
        strcat(cmd,argv[3]);
        system(cmd);
        }
}


int isFileExist(char *fname)
{
    ifstream ftest;
    ftest.open(fname,ios::in);
    if(!ftest)
    {
        ftest.close();
        return 0;
    }
    else
    {
        ftest.close();
        return 1;
    }
}
