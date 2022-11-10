#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <structs.hpp>



int main(int argc, char** argv)
{
    std::ifstream in;
    in.open("test.txt");
    std::vector<Job> jobs;
    std::vector<Machine> machines;
    int numOfJobs,numOfMachines;
    in>>numOfJobs>>numOfMachines;
    for(int i=0;i<numOfJobs;i++)
    {
        Job tmpJob;
        for(int j=0;j<numOfMachines;j++)
        {
            Task tmpTask;
            in >> tmpTask.mNumber >> tmpTask.pTime;
            tmpJob.tasks.push_back(tmpTask);
            Machine tmpMachine;
            machines.push_back(tmpMachine);
        }
        jobs.push_back(tmpJob);
    }
    in.close();

    for( Job j : jobs)
    {
        std::cout << j << std::endl;
    }
    std::cout << std::endl;

    std::vector<Job> testJobs = jobs;
    int timeElapsed;
    
    while (!testJobs.empty())
    {
        for(Job j : testJobs)
        {

        }
    }
    

    return 0;
}