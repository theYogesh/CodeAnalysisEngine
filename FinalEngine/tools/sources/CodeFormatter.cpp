//Code Formatter

#include<fstream>
#include<stdio.h>
#include<iostream>
#include<string.h>

using namespace std;

void cFormatter(char *sourceFile,char *destinationFile);

int main(int argc,char *argv[])
{
    if(argc!=3)
        return (1);

    cFormatter(argv[1],argv[2]);
    return (0);
}


void cFormatter(char *sourceFile,char *destinationFile)
{

    int tab,isNL,isS,isD,isTrim,printflag;
    char x;

    /*  variables purpose:-
        tab: to keep track of number of tabs to print in each line
        isNL(is New Line): to check whether we have printed new line or not.To make sure we do not print more than 1 new line continuosly
        isS(is Space): to check whether we have printed space or not.It is to make sure we do not print more than 1 whitespace continuosly
        isD(is in Double Quoted i.e. Sting literal): If we are in string litereal then double spaces are allowed in between
        isTrim(is left part of the statement is trimmed or not):It is to remove extra white spaces on the left if the statement
        printflag: to make sure we do not consider a single character twice
        x: it is to hold the current character from the input stream
    */

    ifstream ifile;
    ofstream ofile;

    ifile.open(sourceFile,ios::in);
    ofile.open(destinationFile,ios::out);

    tab=0;
    isNL=1;
    isS=0;
    isTrim=0;
    isD=0;

    while(ifile.get(x))
    {
        printflag=1;

        if(isTrim==0)
        {
            if((x==' ')||(x=='\t'))
                printflag=0;
            else
                isTrim=1;
        }

        if(printflag)
        {
            if(isD==0)
            {
                if(isS==0)
                {
                    if((x==' ')||(x=='\t'))
                    {
                        isS=1;
                        ofile<<x;
                        printflag=0;
                    }
                }
                else
                {
                    if((x==' ')||(x=='\t'))
                        printflag=0;
                    else
                        isS=0;
                }
                if(x=='\"')
                {
                    isD=1;
                    ofile<<x;
                    printflag=0;
                }

            }
            else
            {
                if(x=='\"')
                    isD=0;
                ofile<<x;
                printflag=0;
            }
        }

        if(printflag)
        {
            if(isNL<2)
            {
                if(x=='\n')
                {
                    isNL++;
                    ofile<<x;
                    printflag=0;
                    isTrim=0;
                }
            }
            else
            {
                if(x=='\n')
                {
                    printflag=0;
                    isTrim=0;
                }
            }
        }

        if(printflag)
        {
            if(x=='{')
            {
                if(isNL==0)
                    ofile<<'\n';
                for(int i=1;i<=tab;i++)
                    ofile<<'\t';
                ofile<<x;
                ofile<<'\n';
                isNL=2;
                tab++;
                printflag=0;
                isTrim=0;
            }

            else if(x=='}')
            {
                if(isNL==0)
                    ofile<<'\n';
                tab--;
                for(int i=1;i<=tab;i++)
                    ofile<<'\t';
                ofile<<x;
                ofile<<'\n';
                isNL=2;
                printflag=0;
                isTrim=0;
            }

            else if(x==';')
            {
                ofile<<x;
                ofile<<'\n';
                isNL=2;
                printflag=0;
                isTrim=0;
            }
        }

        if(printflag)
        {
            if(isNL>0)
            {
                isNL=0;
                for(int i=1;i<=tab;i++)
                    ofile<<'\t';
            }

            ofile<<x;
        }
    }

    ifile.close();
    ofile.close();
}
