#define CR 0.95
#define MR 0.1
#define dim 3
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include<vector>
#include<math.h>
using namespace std;

typedef vector<char> c1d;
typedef vector<c1d> c2d;
typedef vector<c2d> c3d;
typedef vector<c3d> c4d;
typedef vector<int> i1d;
typedef vector<i1d> i2d;
typedef vector<i2d> i3d;
typedef vector<i3d> i4d;
typedef vector<double>d1d;
typedef vector<d1d> d2d;
typedef vector<d2d> d3d;
typedef vector<d3d> d4d;

void tournament(i2d arr,i2d &temp,d1d Fitness,int pop){
    int i=0;
    while(i<pop){
        int c1=rand()%(pop);
        int c2=rand()%(pop);
        int chc;
        if(Fitness[c1] < Fitness[c2]){
            chc = c1;
        }
        else{
            chc = c2;
        }
        for(int k=0;k<arr[chc].size();k++)
        {
            temp[i][k] = arr[chc][k];
        }
        i++;
    }
}
void mutation(i1d &arr)//隨機選取一點做調換
{
    int len = arr.size();
    int c1 = rand()%(len-2)+1;
    int c2 = rand()%(len-2)+1;
    int temp;
    temp = arr[c1];
    arr[c1] = arr[c2];
    arr[c2] = temp;
    
}
int Find_Value(int F,i1d arr)//回傳該值的index
{
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i] == F)
            return i;
    }
    return -1;
}
void CX_crossover(i2d &arr,i2d temp){//隨機生成一個切割點，將兩個染色體做交配


    int len = temp[0].size();
    
    int i=0;
    while(i<temp.size())
    {
        i1d FIRST_check(arr[0].size()-1);
        i1d Second_check(arr[0].size()-1);

        FIRST_check[0] = 1;
        Second_check[0] = 1;
        int index = Find_Value(temp[i+1][0],temp[i]);
        
        while(true){
            if(FIRST_check[index] != 1)
            {
                FIRST_check[index] = 1;
                Second_check[index] = 1;
                index = Find_Value(temp[i+1][index],temp[i]);
            }
            else{
                break;
            }
        }
        for(int j=0;j<len-1;j++)
        {
            if(FIRST_check[j]==1)
            {
                arr[i][j] = temp[i][j];
                arr[i+1][j] = temp[i+1][j];
            }
            else{
                arr[i][j] = temp[i+1][j];
                arr[i+1][j] = temp[i][j];
            }
        }
        arr[i][len-1] = arr[i][0];
        arr[i+1][len-1] = arr[i+1][0];
        float x = (float) rand() / (RAND_MAX + 1.0);
        float y = (float) rand() / (RAND_MAX + 1.0);
        if(x < MR)
            mutation(arr[i]);
        if(y < MR)
            mutation(arr[i+1]);
        i += 2;
    }
    
        
}
void sum(i1d arr,int len,int &s)
{
    for(int i=0;i<len;i++)
    {
            s+=arr[i];
    }
}
void cut(i1d value,double *split,int sum,int pop)
{
    split[0]=0;split[pop]=1;
    double temp=0;
    for(int i=1;i<pop;i++)//設定區間用
    {
        temp+=value[i];
        split[i]=temp/sum;
    }
}
void tran(int &chc,double x,double *split,int len){
    for(int i=1;i<len;i++)
    {
        if(x>split[i-1]&&x<split[i])
        {

            chc=i-1;
            break;
        }
    }
}
void roulettechoose(c2d arr,c2d &temp,i1d value,int pop,int len)
{
    int i=0;
    int s=0;
    int chc;
    double split[pop+1];
    sum(value,len,s);
    cut(value,split,s,pop);
    while(i<pop){
        double x = (double) rand() / (RAND_MAX + 1.0);
        tran(chc,x,split,pop+1);
        for(int k=0;k<len;k++)
        {
           temp[i][k]=arr[chc][k];
        }
        i++;
    }
}