#include "GAfunction.hpp"
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int pop = atoi(argv[1]);
	int iteration = atoi(argv[2]);
    int run = atoi(argv[3]);
    char * F=argv[4];

    if (argc > 4)
    {
        RUN(iteration,pop,run,F);
    }
    else
    {
        char K ='C';
        RUN(1000,30,30,&K);
    }    
   
}