#define CR 0.95
#define MR 0
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
int  FIND_Correspond(int K,i2d Correspond_Number)
{
    for(int i=0;i<Correspond_Number.size();i++)
    {
        for(int j=0;j<Correspond_Number[i].size();j++)
        {
            if (Correspond_Number[i][j] == K )
            {
                if(j == 0)
                    return Correspond_Number[i][1];
                else 
                    return Correspond_Number[i][0];
            }    
        }
    }
    return K;
}
void PMS(i2d &arr ,i2d temp)
{
    int pop = arr.size();
    int len = arr[0].size();
    int k = 0;
    while (k < pop)
    {
        int c1 = rand()%(len-7);
        int c2 = c1 +3;
        i2d Correspond_Number;
        Correspond_Number.clear();
        for(int i = c1; i < c2;i++)
        {
            i1d T(2,0);
            T[0] = temp[k][i];
            T[1] = temp[k+1][i];
            Correspond_Number.push_back(T);
        }
        
       
        for(int i=0;i < Correspond_Number.size();i++)
        {
            for(int j= 0 ;j < Correspond_Number.size();j++)
            {
                if( i == j )
                        ;
                else if (Correspond_Number[i][0] == Correspond_Number[j][1])
                {
                    Correspond_Number[i][0]= Correspond_Number[i][1];
                    Correspond_Number[i][1] = Correspond_Number[j][0];
                    
                    Correspond_Number.erase(Correspond_Number.begin()+j);
                    i = i-1;
                    break;
                  
                }
                else if(Correspond_Number[i][1]  == Correspond_Number[j][0])
                {
                    Correspond_Number[i][0] = Correspond_Number[i][0];
                    Correspond_Number[i][1] = Correspond_Number[j][1];
                    Correspond_Number.erase(Correspond_Number.begin()+j);
                    i = i-1;
                    break;
                }

            }
        }
      
        for(int i=0;i<len-1;i++)
        {   
            if (i >=c1 && i < c2)
            {
                arr[k][i] = temp[k+1][i];
                arr[k+1][i] = temp[k][i];
            }
            else
            {
                int A = FIND_Correspond(temp[k][i],Correspond_Number);
                arr[k][i] = A;

                int B = FIND_Correspond(temp[k+1][i],Correspond_Number);
                arr[k+1][i] = B;
            }
           
        }
        arr[k][len-1] = arr[k][0];
        arr[k+1][len-1] = arr[k+1][0] ;
        k += 2;
    }
    

}
void OX_Crossover(i2d &arr,i2d temp)
{
    int pop = arr.size();
    int len = arr[0].size();
    int k = 0;
    while (k < pop)
    {
        int c1 = rand()%(len-8)+2;
        int c2 = c1 +5;
        i1d Number_One;
        i1d Number_Two;
        i1d Middle_One;
        i1d Middle_Two;
        Number_One.clear();
        Number_Two.clear();
        Middle_One.clear();
        Middle_Two.clear();
        for(int i = c2;i < len-1;i++)
        {
            Number_One.push_back(temp[k+1][i]);
            Number_Two.push_back(temp[k][i]);
        }
        for(int i=0;i<c1;i++)
        {
            Number_One.push_back(temp[k+1][i]);
            Number_Two.push_back(temp[k][i]);
        }
        for(int i = c1;i < c2;i++)
        {
            Middle_One.push_back(temp[k][i]);
            Middle_Two.push_back(temp[k+1][i]);

            Number_One.push_back(temp[k+1][i]);
            Number_Two.push_back(temp[k][i]);
        }

        
        int i;
        for( i=0;i<Number_One.size();i++)
        {
            for(int j=0;j<Middle_One.size();j++)
            {
                if(Number_One[i] == Middle_One[j])
                {
                    Number_One.erase(Number_One.begin()+i);
                    Middle_One.erase(Middle_One.begin()+j);
                    i = i-1;
                    break;
                }
                
            }
            if(Middle_One.size()== 0)
                break;
        }

       
        int z;
        for(z=0;z<Number_Two.size();z++)
        {
            for(int j=0;j<Middle_Two.size();j++)
            {
                if(Number_Two[z]  == Middle_Two[j])
                {
                    Number_Two.erase(Number_Two.begin()+z);
                    Middle_Two.erase(Middle_Two.begin()+j);
                    z = z-1;
                    break;
                }
                
            }
            if(Middle_Two.size()== 0)
                break;
        }
        for(int i=c2;i<len-1;i++)
        {
            arr[k][i] = Number_One.front();
            Number_One.erase(Number_One.begin());
            arr[k+1][i] = Number_Two.front();
            Number_Two.erase(Number_Two.begin());
        }
        for(int i=c1;i<c2;i++)
        {
            arr[k][i] = temp[k][i];
            arr[k+1][i] = temp[k+1][i];
        }
        for(int i=0;i<c1;i++)
        {
            arr[k][i] = Number_One.front();
            Number_One.erase(Number_One.begin());
            arr[k+1][i] = Number_Two.front();
            Number_Two.erase(Number_Two.begin());
        }

        arr[k][len-1] = arr[k][0];
        arr[k+1][len-1] = arr[k+1][0];
        
        k+=2;
    }
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