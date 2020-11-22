#include "GAfunction.hpp"
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int pop = atoi(argv[1]);
	int iteration = atoi(argv[2]);
    int run = atoi(argv[3]);
    if (argc > 3)
    {
        RUN(iteration,pop,run);
    }
    else
    {
        RUN(1000,30,30);
    }    
   
}