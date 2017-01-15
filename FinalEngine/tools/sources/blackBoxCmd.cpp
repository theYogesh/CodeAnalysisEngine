//BLACK BOX TESTER

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<limits.h>
#include<float.h>
#include<string>
#include<sstream>
#include<time.h>
#include<ctype.h>

using namespace std;

template<class T>
char* toString(T x);
char *dfile;
char limitData[6][2][25]={  "-129","128",
                            "-2147483649","2147483648",
                            "1.17550e-038","3.40283e+038",
                            "-2147483649","2147483648",
                            "2.22508e-308","1.79770e+308",
                            "1","24"
                        };

class inputData
{
    int type;   //data type of data
    char rOc;   //ranged'r' or choice'c' data
    int nd;     //no of data elements
    void *data;     //pointer to actual data

public:
    static int count;

    inputData()
    {
        count++;
        type=0;
        rOc='\0';
        nd=0;
        data=NULL;
    }
    void getdata(int type2,char rOc2,int nd2,void *data2)
    {
        type=type2;
        rOc=rOc2;
        nd=nd2;
        data=data2;
    }
    ~inputData()
    {
        count--;
        if(type==1)
        {
            delete [](char*)data;
        }
        else if(type==2)
        {
            delete [](int*)data;
        }
        else if(type==3)
        {
            delete [](float*)data;
        }
        else if(type==4)
        {
            delete [](long*)data;
        }
        else if(type==5)
        {
            delete [](double*)data;
        }
        else if(type==6)
        {
            char **ptr=(char**)data;

            for(int i=0;i<nd;i++)
            delete []ptr[i];
            delete (char**)data;
        }
    }
    int RETtype()
    {
        return type;
    }
    char RETrOc()
    {
        return rOc;
    }
    int RETnd()
    {
        return nd;
    }
    void* RETdata()
    {
        return data;
    }
};
int inputData::count=0;

inputData* getvalues();

void testCaseInitializer(inputData *idata,char ***tcase,int mode);

int isFileExist(char *fname);

int boundaryValueTest(inputData *idata,char *pname);

int robustnessTest(inputData *idata,char *pname);

void generateExpCases(char ***A,int i,int j,char **res,int lmt,char *dfile,char *command,int &n);

int worstcaseTest(inputData *idata,char *pname);

int robustWorstcaseTest(inputData *idata,char *pname);

int main(int argc,char *argv[])
{
    int choice,result;
    char str[51];
    if(argc!=3)
    {
        return (1);
    }
    
    inputData *ptr=getvalues();
    ofstream ofile;
    dfile=argv[2];

    char exeName[50]="test.exe";
    char cmd[100];
    strcpy(cmd,"g++ ");
    strcat(cmd,argv[1]);
    strcat(cmd," -o test");
    system(cmd);

    if(isFileExist(exeName)!=1)
    {
        ofile.open(argv[2],ios::out);
        ofile<<"Error in Code:-\n";
        ofile.close();
        strcpy(cmd,"g++ ");
        strcat(cmd,argv[1]);
        strcat(cmd," 2>> ");
        strcat(cmd,argv[2]);
        system(cmd);

        return (2);
    }

    cout<<"\n\nChoose the Testing Methodology:-\n\t1.Boundary Value Testing\n\t2.Robustness Testing\n\t3.Worst Case Testing\n\t4.Robust Worst Case Testing\nEnter your choice(1-4): ";
    do
    {
    	cin.getline(str,50);
        	if(strcmpi(str,"BVT")==0)
        		choice=1;
        	else if(strcmpi(str,"RT")==0)
        		choice=2;
        	else if(strcmpi(str,"WCT")==0)
        		choice=3;
        	else if(strcmpi(str,"RWCT")==0)
        		choice=4;
        	else
        		choice=-1;
    }while(choice==-1);

    switch(choice)
    {
        case 1: result=boundaryValueTest(ptr,exeName);
                break;
        case 2: result=robustnessTest(ptr,exeName);
                break;
        case 3: result=worstcaseTest(ptr,exeName);
                break;
        case 4: result=robustWorstcaseTest(ptr,exeName);
                break;
    }
    if(result==0)
    {
        ofile.open(argv[2],ios::out);
        ofile<<"Error Occurred During Execution\n";
        ofile.close();
        return (3);
    }

    cout<<"\n\nTesting successfully done.\nTest results are saved to file in the same directory";
    system("del test.exe");
    return 0;
}


template<class T>
char* toString(T x)
{
    stringstream st;
    st<<x;
    string s=st.str();
    char *res=new char[s.length()+1];
    strcpy(res,s.c_str());
    return (res);
}


inputData* getvalues()
{
    int n;
    int type;
    char rOc;
    int nd;
    void *data;
    char ch;

    char str[51];

    cout<<"\nEnter number of Inputs : ";
    cin>>n;
    inputData *idata=new inputData[n];
    for(int c=0;c<n;c++)
    {
        cout<<"\nEnter Details of Input "<<c+1;
        cout<<"\nData type of Input:-\n\t1.Char\n\t2.Int\n\t3.Float\n\t4.Long\n\t5.Double\n\t6.String\nEnter your choice(1-6) : ";
        do
        {
        	cin.getline(str,50);
        	if(strcmpi(str,"char")==0)
        		type=1;
        	else if(strcmpi(str,"int")==0)
        		type=2;
        	else if(strcmpi(str,"float")==0)
        		type=3;
        	else if(strcmpi(str,"long")==0)
        		type=4;
        	else if(strcmpi(str,"double")==0)
        		type=5;
        	else if(strcmpi(str,"string")==0)
        		type=6;
        	else
        		type=-1;
        }while(type==-1);

        cout<<"\n\nInput is Ranged or Choice('r' or 'c') : ";
        do
        {
            cin>>rOc;
            toupper(rOc);
        }while((rOc!='r')&&(rOc!='c')&&(rOc!='R')&&(rOc!='C'));

        if(rOc=='r'||rOc=='R')
        {
            nd=2;
            cout<<"\nDoes it have any specific range('Y' or 'N')\n(Else Default range for that datatype will be used) : ";
            do
            {
                cin>>ch;
                toupper(ch);
            }while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'));

            if((ch=='Y')||(ch=='y'))
            {

                if(type==1)
                {
                    char *ptr=new char[2];
                    cout<<"\nEnter Lower Limit : ";
                    cin>>ptr[0];
                    cout<<"\nEnter Upper Limit : ";
                    cin>>ptr[1];
                    data=ptr;
                }

                else if(type==2)
                {
                    int *ptr=new int[2];
                    cout<<"\nEnter Lower Limit : ";
                    cin>>ptr[0];
                    cout<<"\nEnter Upper Limit : ";
                    cin>>ptr[1];
                    data=ptr;
                }

                else if(type==3)
                {
                    float *ptr=new float[2];
                    cout<<"\nEnter Lower Limit : ";
                    cin>>ptr[0];
                    cout<<"\nEnter Upper Limit : ";
                    cin>>ptr[1];
                    data=ptr;
                }

                else if(type==4)
                {
                    long *ptr=new long[2];
                    cout<<"\nEnter Lower Limit : ";
                    cin>>ptr[0];
                    cout<<"\nEnter Upper Limit : ";
                    cin>>ptr[1];
                    data=ptr;
                }

                else if(type==5)
                {
                    double *ptr=new double[2];
                    cout<<"\nEnter Lower Limit : ";
                    cin>>ptr[0];
                    cout<<"\nEnter Upper Limit : ";
                    cin>>ptr[1];
                    data=ptr;
                }

                else if(type==6)
                {
                    int *ptr=new int[2];
                    cout<<"\nEnter minimum number of characters in the string (>0) : ";
                    cin>>ptr[0];
                    cout<<"\nEnter maximum number of characters in the string (<25): ";
                    cin>>ptr[1];
                    data=ptr;
                }
            }
            else
            {
                if(type==1)
                {
                    char *ptr=new char[2];
                    ptr[0]=SCHAR_MIN;
                    ptr[1]=SCHAR_MAX;
                    data=ptr;
                }

                else if(type==2)
                {
                    int *ptr=new int[2];
                    ptr[0]=INT_MIN;
                    ptr[1]=INT_MAX;
                    data=ptr;
                }

                else if(type==3)
                {
                    float *ptr=new float[2];
                    ptr[0]=FLT_MIN;
                    ptr[1]=FLT_MAX;
                    data=ptr;
                }

                else if(type==4)
                {
                    long *ptr=new long[2];
                    ptr[0]=LONG_MIN;
                    ptr[1]=LONG_MAX;
                    data=ptr;
                }

                else if(type==5)
                {
                    double *ptr=new double[2];
                    ptr[0]=DBL_MIN;
                    ptr[1]=DBL_MAX;
                    data=ptr;
                }

                else if(type==6)
                {
                    int *ptr=new int[2];
                    ptr[0]=1;
                    ptr[1]=24;
                    data=ptr;
                }
            }
        }

        else
        {
            cout<<"\nEnter number of choices : ";
            cin>>nd;
            cout<<"\nEnter choices:-\n";

            if(type==1)
            {
                char *ptr=new char[nd];
                for(int i=0;i<nd;i++)
                {
                    cout<<"\nEnter choice "<<i+1<<" : ";
                    cin>>ptr[i];
                }
                data=ptr;
            }
            else if(type==2)
            {
                int *ptr=new int[nd];
                for(int i=0;i<nd;i++)
                {
                    cout<<"\nEnter choice "<<i+1<<" : ";
                    cin>>ptr[i];
                }
                    data=ptr;
           }
            else if(type==3)
            {
                float *ptr=new float[nd];
                for(int i=0;i<nd;i++)
                {
                    cout<<"\nEnter choice "<<i+1<<" : ";
                    cin>>ptr[i];
                }
                data=ptr;
            }
            else if(type==4)
            {
                long *ptr=new long[nd];
                for(int i=0;i<nd;i++)
                {
                    cout<<"\nEnter choice "<<i+1<<" : ";
                    cin>>ptr[i];
                }
                data=ptr;
            }
            else if(type==5)
            {
                double *ptr=new double[nd];
                for(int i=0;i<nd;i++)
                {
                    cout<<"\nEnter choice "<<i+1<<" : ";
                    cin>>ptr[i];
                }
                data=ptr;
            }
            else if(type==6)
            {
                char **ptr=new char*[nd];

                for(int i=0;i<nd;i++)
                    ptr[i]=new char[25];

                cin.ignore();       //to clear the left out data from input buffer
                for(int i=0;i<nd;i++)
                {
                    cout<<"\nEnter choice "<<i+1<<" : ";
                    cin.getline(ptr[i],25);
                }
                data=ptr;
            }
        }
        idata[c].getdata(type,rOc,nd,data);
    }
    return idata;
}

void testCaseInitializer(inputData *idata,char ***tcase,int mode)
{
    int n=mode-1;

    for(int i=0;i<inputData::count;i++)
    {
        if(idata[i].RETrOc()=='R')
        {
            if(idata[i].RETtype()==1)
            {
                char *ptr=(char*)idata[i].RETdata();
                if(mode==2)
                {
                    if(ptr[0]==SCHAR_MIN)
                    {
                        strcpy(tcase[i][0],limitData[idata[i].RETtype()-1][0]);
                    }
                    else
                        strcpy(tcase[i][0],toString((char)(ptr[0]-1)));

                    if(ptr[1]==SCHAR_MAX)
                        strcpy(tcase[i][6],limitData[idata[i].RETtype()-1][1]);
                    else
                        strcpy(tcase[i][6],toString((char)(ptr[1]+1)));
                }
                strcpy(tcase[i][n],toString((char)(ptr[0])));
                strcpy(tcase[i][n+1],toString((char)(ptr[0]+1)));
                strcpy(tcase[i][(n+5)/2],toString((char)((ptr[0]+ptr[1])/2)));
                strcpy(tcase[i][(n+5)-2],toString((char)(ptr[1]-1)));
                strcpy(tcase[i][(n+5)-1],toString((char)(ptr[1])));
            }
            else if(idata[i].RETtype()==2)
            {
                int *ptr=(int*)idata[i].RETdata();
                if(mode==2)
                {
                    if(ptr[0]==INT_MIN)
                    {
                        strcpy(tcase[i][0],limitData[idata[i].RETtype()-1][0]);
                    }
                    else
                        strcpy(tcase[i][0],toString(ptr[0]-1));

                    if(ptr[1]==INT_MAX)
                        strcpy(tcase[i][6],limitData[idata[i].RETtype()-1][1]);
                    else
                        strcpy(tcase[i][6],toString(ptr[1]+1));
                }
                strcpy(tcase[i][n],toString(ptr[0]));
                strcpy(tcase[i][n+1],toString(ptr[0]+1));
                strcpy(tcase[i][(n+5)/2],toString((ptr[0]+ptr[1])/2));
                strcpy(tcase[i][(n+5)-2],toString((ptr[1]-1)));
                strcpy(tcase[i][(n+5)-1],toString(ptr[1]));
            }
            else if(idata[i].RETtype()==3)
            {
                float *ptr=(float*)idata[i].RETdata();
                if(mode==2)
                {
                    if(ptr[0]==FLT_MIN)
                    {
                        strcpy(tcase[i][0],limitData[idata[i].RETtype()-1][0]);
                    }
                    else
                        strcpy(tcase[i][0],toString(ptr[0]-1));

                    if(ptr[1]==FLT_MAX)
                        strcpy(tcase[i][6],limitData[idata[i].RETtype()-1][1]);
                    else
                        strcpy(tcase[i][6],toString(ptr[1]+1));
                }
                strcpy(tcase[i][n],toString(ptr[0]));
                strcpy(tcase[i][n+1],toString(ptr[0]+1));
                strcpy(tcase[i][(n+5)/2],toString((ptr[0]+ptr[1])/2));
                strcpy(tcase[i][(n+5)-2],toString((ptr[1]-1)));
                strcpy(tcase[i][(n+5)-1],toString(ptr[1]));
            }
            else if(idata[i].RETtype()==4)
            {
                long *ptr=(long*)idata[i].RETdata();

                if(mode==2)
                {
                    if(ptr[0]==LONG_MIN)
                    {
                        strcpy(tcase[i][0],limitData[idata[i].RETtype()-1][0]);
                    }
                    else
                        strcpy(tcase[i][0],toString(ptr[0]-1));

                    if(ptr[1]==LONG_MAX)
                        strcpy(tcase[i][6],limitData[idata[i].RETtype()-1][1]);
                    else
                        strcpy(tcase[i][6],toString(ptr[1]+1));
                }
                strcpy(tcase[i][n],toString(ptr[0]));
                strcpy(tcase[i][n+1],toString(ptr[0]+1));
                strcpy(tcase[i][(n+5)/2],toString((ptr[0]+ptr[1])/2));
                strcpy(tcase[i][(n+5)-2],toString((ptr[1]-1)));
                strcpy(tcase[i][(n+5)-1],toString(ptr[1]));
            }
            else if(idata[i].RETtype()==5)
            {
                double *ptr=(double*)idata[i].RETdata();

                if(mode==2)
                {
                    if(ptr[0]==DBL_MIN)
                    {
                        strcpy(tcase[i][0],limitData[idata[i].RETtype()-1][0]);
                    }
                    else
                        strcpy(tcase[i][0],toString(ptr[0]-1));

                    if(ptr[1]==DBL_MAX)
                        strcpy(tcase[i][6],limitData[idata[i].RETtype()-1][1]);
                    else
                        strcpy(tcase[i][6],toString(ptr[1]+1));
                }
                strcpy(tcase[i][n],toString(ptr[0]));
                strcpy(tcase[i][n+1],toString(ptr[0]+1));
                strcpy(tcase[i][(n+5)/2],toString((ptr[0]+ptr[1])/2));
                strcpy(tcase[i][(n+5)-2],toString((ptr[1]-1)));
                strcpy(tcase[i][(n+5)-1],toString(ptr[1]));
            }
            else if(idata[i].RETtype()==6)
            {
                int *ptr=(int*)idata[i].RETdata();
                char temp[25];
                int j;
                srand((unsigned)time(NULL));
                if(mode==2)
                {
                    int size=atoi(limitData[idata[i].RETtype()-1][0]);
                    if(ptr[0]==size)
                    {
                        for(j=0;j<size;j++)
                        {
                            temp[j]=(char)((rand()%26)+65);
                        }
                        temp[j]='\0';
                        strcpy(tcase[i][0],temp);
                    }
                    else
                    {
                        for(j=0;j<ptr[0]-1;j++)
                        {
                            temp[j]=(char)((rand()%26)+65);
                        }
                        temp[j]='\0';

                        strcpy(tcase[i][0],temp);
                    }
                    size=atoi(limitData[idata[i].RETtype()-1][1]);
                    if(ptr[1]>=size)
                    {
                        for(j=0;j<size;j++)
                        {
                            temp[j]=(char)((rand()%26)+65);
                        }
                        temp[j]='\0';
                        strcpy(tcase[i][6],temp);
                    }
                    else
                    {
                        for(j=0;j<ptr[1]+1;j++)
                        {
                            temp[j]=(char)((rand()%26)+65);
                        }
                        temp[j]='\0';
                        strcpy(tcase[i][6],temp);
                    }
                }

                for(j=0;j<ptr[0];j++)
                {
                    temp[j]=(char)((rand()%26)+65);
                }
                temp[j]='\0';
                strcpy(tcase[i][n],temp);

                for(j=0;j<ptr[0]+1;j++)
                {
                    temp[j]=(char)((rand()%26)+65);
                }
                temp[j]='\0';
                strcpy(tcase[i][n+1],temp);

                for(j=0;j<(ptr[0]+ptr[1])/2;j++)
                {
                    temp[j]=(char)((rand()%26)+65);
                }
                temp[j]='\0';
                strcpy(tcase[i][(n+5)/2],temp);

                for(j=0;j<ptr[1]-1;j++)
                {
                    temp[j]=(char)((rand()%26)+65);
                }
                temp[j]='\0';
                strcpy(tcase[i][(n+5)-2],temp);

                for(j=0;j<ptr[1];j++)
                {
                    temp[j]=(char)((rand()%26)+65);
                }
                temp[j]='\0';
                strcpy(tcase[i][(n+5)-1],temp);
            }
        }

        if(idata[i].RETrOc()=='Y')
        {
            if(idata[i].RETtype()==1)
            {
                char *ptr=(char*)idata[i].RETdata();

                if(mode==2)
                {
                    if(ptr[0]==SCHAR_MIN)
                    {
                        strcpy(tcase[i][0],limitData[idata[i].RETtype()-1][0]);
                    }
                    else
                        strcpy(tcase[i][0],toString((char)(ptr[0]-1)));

                    if(ptr[idata[i].RETnd()-1]==SCHAR_MAX)
                        strcpy(tcase[i][6],limitData[idata[i].RETtype()-1][1]);

                    else
                        strcpy(tcase[i][6],toString((char)(ptr[idata[i].RETnd()-1]+1)));
                }
                strcpy(tcase[i][n],toString((char)(ptr[0])));
                strcpy(tcase[i][n+1],toString((char)(ptr[1])));
                strcpy(tcase[i][(n+5)/2],toString((char)(ptr[idata[i].RETnd()/2])));
                strcpy(tcase[i][(n+5)-2],toString((char)(ptr[idata[i].RETnd()-2])));
                strcpy(tcase[i][(n+5)-1],toString((char)(ptr[idata[i].RETnd()-1])));
            }
            else if(idata[i].RETtype()==2)
            {
                int *ptr=(int*)idata[i].RETdata();
                if(mode==2)
                {
                    if(ptr[0]==INT_MIN)
                    {
                        strcpy(tcase[i][0],limitData[idata[i].RETtype()-1][0]);
                    }
                    else
                        strcpy(tcase[i][0],toString(ptr[0]-1));

                    if(ptr[idata[i].RETnd()-1]==INT_MAX)
                        strcpy(tcase[i][6],limitData[idata[i].RETtype()-1][1]);
                    else
                        strcpy(tcase[i][6],toString(ptr[idata[i].RETnd()-1]+1));
                }
                strcpy(tcase[i][n],toString(ptr[0]));
                strcpy(tcase[i][n+1],toString(ptr[1]));
                strcpy(tcase[i][(n+5)/2],toString(ptr[idata[i].RETnd()/2]));
                strcpy(tcase[i][(n+5)-2],toString(ptr[idata[i].RETnd()-2]));
                strcpy(tcase[i][(n+5)-1],toString(ptr[idata[i].RETnd()-1]));
            }
            else if(idata[i].RETtype()==3)
            {
                float *ptr=(float*)idata[i].RETdata();
                if(mode==2)
                {
                    if(ptr[0]==FLT_MIN)
                    {
                        strcpy(tcase[i][0],limitData[idata[i].RETtype()-1][0]);
                    }
                    else
                        strcpy(tcase[i][0],toString(ptr[0]-1));

                    if(ptr[idata[i].RETnd()-1]==FLT_MAX)
                        strcpy(tcase[i][6],limitData[idata[i].RETtype()-1][1]);
                    else
                        strcpy(tcase[i][6],toString(ptr[idata[i].RETnd()-1]+1));
                }
                strcpy(tcase[i][n],toString(ptr[0]));
                strcpy(tcase[i][n+1],toString(ptr[1]));
                strcpy(tcase[i][(n+5)/2],toString(ptr[idata[i].RETnd()/2]));
                strcpy(tcase[i][(n+5)-2],toString(ptr[idata[i].RETnd()-2]));
                strcpy(tcase[i][(n+5)-1],toString(ptr[idata[i].RETnd()-1]));
            }
            else if(idata[i].RETtype()==4)
            {
                long *ptr=(long*)idata[i].RETdata();
                if(mode==2)
                {
                    if(ptr[0]==LONG_MIN)
                    {
                        strcpy(tcase[i][0],limitData[idata[i].RETtype()-1][0]);
                    }
                    else
                        strcpy(tcase[i][0],toString(ptr[0]-1));

                    if(ptr[idata[i].RETnd()-1]==LONG_MAX)
                        strcpy(tcase[i][6],limitData[idata[i].RETtype()-1][1]);
                    else
                        strcpy(tcase[i][6],toString(ptr[idata[i].RETnd()-1]+1));
                }
                strcpy(tcase[i][n],toString(ptr[0]));
                strcpy(tcase[i][n+1],toString(ptr[1]));
                strcpy(tcase[i][(n+5)/2],toString(ptr[idata[i].RETnd()/2]));
                strcpy(tcase[i][(n+5)-2],toString(ptr[idata[i].RETnd()-2]));
                strcpy(tcase[i][(n+5)-1],toString(ptr[idata[i].RETnd()-1]));
            }
            else if(idata[i].RETtype()==5)
            {
                double *ptr=(double*)idata[i].RETdata();
                if(mode==2)
                {
                    if(ptr[0]==DBL_MIN)
                    {
                        strcpy(tcase[i][0],limitData[idata[i].RETtype()-1][0]);
                    }
                    else
                        strcpy(tcase[i][0],toString(ptr[0]-1));

                    if(ptr[idata[i].RETnd()-1]==DBL_MAX)
                        strcpy(tcase[i][6],limitData[idata[i].RETtype()-1][1]);
                    else
                        strcpy(tcase[i][6],toString(ptr[idata[i].RETnd()-1]+1));
                }
                strcpy(tcase[i][n],toString(ptr[0]));
                strcpy(tcase[i][n+1],toString(ptr[1]));
                strcpy(tcase[i][(n+5)/2],toString(ptr[idata[i].RETnd()/2]));
                strcpy(tcase[i][(n+5)-2],toString(ptr[idata[i].RETnd()-2]));
                strcpy(tcase[i][(n+5)-1],toString(ptr[idata[i].RETnd()-1]));
            }
            else if(idata[i].RETtype()==6)
            {
                char **ptr=(char**)idata[i].RETdata();
                char temp[25];
                int j;
                srand((unsigned)time(NULL));
                if(mode==2)
                {
                    if(strlen(ptr[0])==atoi(limitData[idata[i].RETtype()-1][0]))
                    {
                        for(j=0;j<atoi(limitData[idata[i].RETtype()-1][0]);j++)
                        {
                            temp[j]=(char)((rand()%26)+65);
                        }
                        temp[j]='\0';
                        strcpy(tcase[i][0],temp);
                    }
                    else
                    {
                        for(j=0;j<strlen(ptr[0])-1;j++)
                        {
                            temp[j]=(char)((rand()%26)+65);
                        }
                        temp[j]='\0';
                        strcpy(tcase[i][0],temp);
                    }
                    if(strlen(ptr[idata[i].RETnd()-1])>=atoi(limitData[idata[i].RETtype()-1][1]))
                    {
                        for(j=0;j<atoi(limitData[idata[i].RETtype()-1 ][1]);j++)
                        {
                            temp[j]=(char)((rand()%26)+65);
                        }
                        temp[j]='\0';
                        strcpy(tcase[i][6],temp);
                    }
                    else
                    {
                        for(j=0;j<strlen(ptr[idata[i].RETnd()-1])+1;j++)
                        {
                            temp[j]=(char)((rand()%26)+65);
                        }
                        temp[j]='\0';
                        strcpy(tcase[i][6],temp);
                    }
                }
                strcpy(tcase[i][n],ptr[0]);
                strcpy(tcase[i][n+1],ptr[1]);
                strcpy(tcase[i][(n+5)/2],ptr[idata[i].RETnd()/2]);
                strcpy(tcase[i][(n+5)-2],ptr[idata[i].RETnd()-2]);
                strcpy(tcase[i][(n+5)-1],ptr[idata[i].RETnd()-1]);
            }
        }
    }
}

int isFileExist(char *fname)
{
    char pname[50];
    strcpy(pname,fname);
    char exe[]=".exe";
    int len,flag;
    len=strlen(fname);
    if(len<=4)
    {
        flag=0;
    }
    else
    {
        flag=1;
        for(int i=len-4,j=0;i<len;i++,j++)
        {
            if(exe[j]!=fname[i])
            {
                flag=0;
                break;
            }
        }
    }
    if(flag==0)
        strcat(pname,".exe");

    ifstream ftest;
    ftest.open(pname,ios::in);
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

int boundaryValueTest(inputData *idata,char *pname)
{
    char command[80];
    
    strcpy(command,pname);
    strcat(command,"<tempin_YRM.txt>>");
    strcat(command,dfile);
    int n;
    FILE *ftemp;
    FILE *fout;
    fout=fopen(dfile,"w");
    fprintf(fout,"~~~~BOUNDARY VALUE TESTING~~~~\n\nNumber of Inputs : %d",inputData::count);
    char ***testcase=new char**[inputData::count];
    for(int i=0;i<inputData::count;i++)
        testcase[i]=new char*[5];

    for(int i=0;i<inputData::count;i++)
    {
        for(int j=0;j<5;j++)
        {
            testcase[i][j]=new char[25];
        }
    }

    testCaseInitializer(idata,testcase,1);
    fputs("\nTest Case Values:-",fout);

    for(int i=0;i<inputData::count;i++)
    {
        fprintf(fout,"\nFor Input '%d' :-",i+1);
        for(int j=0;j<5;j++)
        {
            fprintf(fout,"\n%s",testcase[i][j]);
        }
    }
    fprintf(fout,"\n\nNumber of Test Case(4n+1)= %d\n\nTest Results:-",4*inputData::count+1);
    fclose(fout);
    n=0;
    for(int i=0;i<inputData::count;i++)
    {
        for(int j=0;j<5;j++)
        {
            if((i!=0)&&(j==2))
                continue;
            fout=fopen(dfile,"a");
            ftemp=fopen("tempin_YRM.txt","w");
            fprintf(fout,"\n\n\nTEST CASE : %d",++n);
            for(int k=0;k<inputData::count;k++)
            {
                if(k==(inputData::count-i-1))
                {
                    fputs(testcase[k][j],ftemp);;
                    fprintf(fout,"\nInput %d= %s",k+1,testcase[k][j]);
                }

                else
                {
                    fputs(testcase[k][2],ftemp);
                    fprintf(fout,"\nInput %d= %s",k+1,testcase[k][2]);
                }

                fputc('\n',ftemp);
            }
            fputs("\nOutput:-\n\n",fout);
            fclose(ftemp);
            fclose(fout);
            if(system(command)==-1)
            {
                remove("tempin_YRM.txt");
                return 0;
            }
        }
    }
    remove("tempin_YRM.txt");
    return 1;
}

int robustnessTest(inputData *idata,char *pname)
{
    char command[80];
    
    strcpy(command,pname);
    strcat(command,"<tempin_YRM.txt>>");
    strcat(command,dfile);
    int n;
    FILE *ftemp;
    FILE *fout;
    fout=fopen(dfile,"w");
    fprintf(fout,"~~~~ROBUSTNESS TESTING~~~~\n\nNumber of Inputs : %d",inputData::count);
    char ***testcase=new char**[inputData::count];
    for(int i=0;i<inputData::count;i++)
        testcase[i]=new char*[7];

    for(int i=0;i<inputData::count;i++)
    {
        for(int j=0;j<7;j++)
        {
            testcase[i][j]=new char[25];
        }
    }

    testCaseInitializer(idata,testcase,2);
    fputs("\nTest Case Values:-",fout);

    for(int i=0;i<inputData::count;i++)
    {
        fprintf(fout,"\nFor Input '%d' :-",i+1);
        for(int j=0;j<7;j++)
        {
            fprintf(fout,"\n%s",testcase[i][j]);
        }
    }
    fprintf(fout,"\n\nNumber of Test Case(6n+1)= %d\n\nTest Results:-",6*inputData::count+1);
    fclose(fout);
    n=0;
    for(int i=0;i<inputData::count;i++)
    {
        for(int j=0;j<7;j++)
        {
            if((i!=0)&&(j==3))
                continue;
            fout=fopen(dfile,"a");
            ftemp=fopen("tempin_YRM.txt","w");
            fprintf(fout,"\n\n\nTEST CASE : %d",++n);
            for(int k=0;k<inputData::count;k++)
            {
                if(k==(inputData::count-i-1))
                {
                    fputs(testcase[k][j],ftemp);;
                    fprintf(fout,"\nInput %d= %s",k+1,testcase[k][j]);
                }

                else
                {
                    fputs(testcase[k][2],ftemp);
                    fprintf(fout,"\nInput %d= %s",k+1,testcase[k][2]);
                }

                fputc('\n',ftemp);
            }
            fputs("\nOutput:-\n\n",fout);
            fclose(ftemp);
            fclose(fout);
            if(system(command)==-1)
            {
                remove("tempin_YRM.txt");
                return 0;
            }
        }
    }
    remove("tempin_YRM.txt");
    return 1;
}


void generateExpCases(char ***A,int i,int j,char **res,int lmt,char *dfile,char *command,int &n)
{
    if(n==-1)
        return;
    if(i==(inputData::count-1))
    {
        strcpy(res[i],A[i][j]);

        FILE *ftemp;
        FILE *fout;
        fout=fopen(dfile,"a");

        ftemp=fopen("tempin_YRM.txt","w");
        fprintf(fout,"\n\n\nTEST CASE : %d",++n);

        for(int k=0;k<inputData::count;k++)
        {
            fputs(res[k],ftemp);
            fprintf(fout,"\nInput %d= %s\n",k+1,res[k]);
            fputc('\n',ftemp);
        }
        fputs("\nOutput:-\n\n",fout);
        fclose(ftemp);
        fclose(fout);
        if(system(command)==-1)
        {
            n=-1;
            return;
        }
    }
    else
    {
        strcpy(res[i],A[i][j]);
        for(int k=0;k<lmt;k++)
        {
            generateExpCases(A,i+1,k,res,lmt,dfile,command,n);
        }
    }
    return;
}

int worstcaseTest(inputData *idata,char *pname)
{
    char command[80];
    
    strcpy(command,pname);
    strcat(command,"<tempin_YRM.txt>>");
    strcat(command,dfile);

    FILE *fout;
    fout=fopen(dfile,"w");
    fprintf(fout,"~~~~WORSTCASE TESTING~~~~\n\nNumber of Inputs : %d",inputData::count);
    char ***testcase=new char**[inputData::count];
    for(int i=0;i<inputData::count;i++)
        testcase[i]=new char*[5];

    for(int i=0;i<inputData::count;i++)
    {
        for(int j=0;j<5;j++)
        {
            testcase[i][j]=new char[25];
        }
    }

    testCaseInitializer(idata,testcase,1);
    fputs("\nTest Case Values:-",fout);

    for(int i=0;i<inputData::count;i++)
    {
        fprintf(fout,"\nFor Input '%d' :-",i+1);
        for(int j=0;j<5;j++)
        {
            fprintf(fout,"\n%s",testcase[i][j]);
        }
    }
    int ntc=1;
    for(int i=1;i<=inputData::count;i++)
    {
        ntc=ntc*5;
    }
    fprintf(fout,"\n\nNumber of Test Case(5^n)= %d\n\nTest Results:-",ntc);
    fclose(fout);

    char **str=new char*[inputData::count];
    for(int i=0;i<inputData::count;i++)
        str[i]=new char[25];

    int n=0;
    for(int i=0;i<5;i++)
    {
        generateExpCases(testcase,0,i,str,5,dfile,command,n);
    }

    remove("tempin_YRM.txt");
    if(n==-1)
        return 0;
    else
        return 1;
}

int robustWorstcaseTest(inputData *idata,char *pname)
{
    char command[80];
    
    strcpy(command,pname);
    strcat(command,"<tempin_YRM.txt>>");
    strcat(command,dfile);

    FILE *fout;
    fout=fopen(dfile,"w");
    fprintf(fout,"~~~~ROBUST WORSTCASE TESTING~~~~\n\nNumber of Inputs : %d",inputData::count);
    char ***testcase=new char**[inputData::count];
    for(int i=0;i<inputData::count;i++)
        testcase[i]=new char*[7];

    for(int i=0;i<inputData::count;i++)
    {
        for(int j=0;j<7;j++)
        {
            testcase[i][j]=new char[25];
        }
    }

    testCaseInitializer(idata,testcase,2);
    fputs("\nTest Case Values:-",fout);

    for(int i=0;i<inputData::count;i++)
    {
        fprintf(fout,"\nFor Input '%d' :-",i+1);
        for(int j=0;j<7;j++)
        {
            fprintf(fout,"\n%s",testcase[i][j]);
        }
    }
    int ntc=1;
    for(int i=1;i<=inputData::count;i++)
    {
        ntc=ntc*7;
    }
    fprintf(fout,"\n\nNumber of Test Case(7^n)= %d\n\nTest Results:-",ntc);
    fclose(fout);

    char **str=new char*[inputData::count];
    for(int i=0;i<inputData::count;i++)
        str[i]=new char[25];

    int n=0;
    for(int i=0;i<7;i++)
    {
        generateExpCases(testcase,0,i,str,7,dfile,command,n);
    }

    remove("tempin_YRM.txt");
    if(n==-1)
        return 0;
    else
        return 1;
}
