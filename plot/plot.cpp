#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<sstream>
#define dim 3
using namespace std;
int* read(int &sum){//讀檔

    fstream file;
    int ind=0;
    file.open("readfile1.txt",ios::in);
    int* temp=new int[510];
    while(file)
    {
        file>>temp[ind];
        ind++;
    }
    sum=(ind-1)/3;
    return temp;
}
void makearr(int *arr,int *input,int len)//將測資讀為整理好的陣列
{
    int chc=0;
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<dim;j++)
        {
            *((int*)arr +dim*i+j)=*(input+chc);
            cout<<*((int*)arr +dim*i+j)<<' ';
            chc++;
        }
        cout<<endl<<endl;
    }
}
int main(void){
	fstream file;
    int ind=0;
    file.open("readfile.txt",ios::in);
    int* temp=new int[510];
    while(file)
    {
        file>>temp[ind];
        ind++;
    }
    file.close();
    int len;
    int *a=read(len);//讀檔用的pointer
    int city[len][dim];
    makearr((int*)city,a,len);
   	file.open("2Dplot.txt",ios::out);
   	for(int i=0;i<len;i++)
   	{
   		int num=temp[i]-1;
		file<<city[num][1]<<' '<<city[num][2]<<endl;
   	}
}
