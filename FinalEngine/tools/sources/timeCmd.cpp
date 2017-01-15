#include<iostream>
#include<fstream>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include <sys/time.h>

using namespace std;


int isFileExist(char *fname);
double programExecuter(char *pname,char *inputfile,int n);


int main(int argc,char *argv[])
{
    double avg;
    int n;

    if(argc!=5)
    {
    	return 1;
    }

    n=atoi(argv[3]);


    char exeName[50]="test.exe";
    char cmd[100];
    strcpy(cmd,"g++ ");
    strcat(cmd,argv[1]);
    strcat(cmd," -o test");
    system(cmd);
    if(isFileExist(exeName)==1)
    {
        avg=programExecuter(exeName,argv[2],n);

        if(avg==-1)
        {
            return 2;
        }

        ofstream ofile;
        ofile.open(argv[4],ios::out);
        ofile<<avg<<" milliseconds";
        ofile.close();
        system("del test.exe");
        return 0;
    }
    else
    {
        ofstream ofile;
        ofile.open(argv[4],ios::out);
        ofile<<"Error in Code";
        ofile.close();
        return 3;
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


double programExecuter(char *pname,char *inputfile,int n)
{
	struct timeval t1,t2;
    long totalTime;
    double avg; 
    register int i;
    register int lmt;
    char *cmd=new char[strlen(pname)+strlen(inputfile)+10];
    strcpy(cmd,pname);
    strcat(cmd,"<");
    strcat(cmd,inputfile);
    strcat(cmd,">/NULL");
    
    i=1;
    lmt=n;
    gettimeofday (&t1, NULL);
    while(i<=lmt)
    {
        if(system(cmd)==-1)
        {
            break;
        }
        i++;
    }
    
    gettimeofday (&t2, NULL);

    totalTime=((double)(t2.tv_sec - t1.tv_sec)*1000000)+((double)(t2.tv_usec - t1.tv_usec));

    totalTime=totalTime/1000;
    delete[] cmd;
    if(i<lmt)
        return (-1);

    avg=((double)totalTime/n);
    return (avg);
}
