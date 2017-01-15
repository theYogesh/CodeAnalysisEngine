#include<fstream>
#include<stdio.h>
#include<iostream>
#include<string.h>

using namespace std;

int isFileExist(char *fname);

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        return (1);
    }

    char exeName[50]="code.exe";
    char cmd[100];
    strcpy(cmd,"g++ ");
    strcat(cmd,argv[1]);
    strcat(cmd," -o code");
    system(cmd);

    ofstream ofile;
    ofile.open(argv[2],ios::out);
    ofile<<"GCC Report:-\n";
    ofile.close();
    if(isFileExist(exeName)==1)
    {
	    ofile.open(argv[2],ios::out|ios::app);
	    ofile<<"No Errors Found.";
	    ofile.close();
        
        strcpy(cmd,"del code.exe");
        system(cmd);
    }
    else
    {
        strcpy(cmd,"g++ ");
        strcat(cmd,argv[1]);
        strcat(cmd," 2>> ");
        strcat(cmd,argv[2]);
        system(cmd);
    }

    ofile.open(argv[2],ios::out|ios::app);
    ofile<<"\n\nCppCheck Report:-\n";
    ofile.close();

    strcpy(cmd,"cppcheck ");
    strcat(cmd,argv[1]);
    strcat(cmd," 2>>");
    strcat(cmd,argv[2]);
    system(cmd);
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
