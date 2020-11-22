#include "GAfunction.hpp"
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int pop = atoi(argv[1]);
	int iteration = atoi(argv[2]);
    int run = atoi(argv[3]);    
    RUN(iteration,pop,run);
   
}