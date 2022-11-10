#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <structs.hpp>

bool isInVector(std::vector<int> v, int num)
{
    for(int i : v)
    {
        if(i == num)
        {
            return true;
        }
    }
    return false;
}

int findShortest(std::vector<Job> jobs,int mId)
{
    int min=-1;
    int jobId;
    for(Job j : jobs)
    {
        if(j.tasks[0].mNumber==mId)
        {
            if(min==-1 or min>j.tasks[0].pTime)
            {
                min=j.tasks[0].pTime;
                jobId=j.id;
            }
        }
    }
    return jobId;
}



int main(int argc, char** argv)
{
    std::ifstream in;
    in.open("test.txt");
    std::vector<Job> jobs;
    std::vector<Machine> machines;
    std::vector<std::vector<int>> res;
    int numOfJobs,numOfMachines;
    in>>numOfJobs>>numOfMachines;
    for(int i=0;i<numOfJobs;i++)
    {
        Job tmpJob;
        tmpJob.id=i;
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

    if(0)
    while (!testJobs.empty())
    {
        int shortestTask = -1;
        //int i=0;
        std::vector<int> neededMachines;
        for(Job j : testJobs)
        {
            if(!isInVector(neededMachines,j.tasks[0].mNumber))
            {
                neededMachines.push_back(j.tasks[0].mNumber);
            }
            //i++;
        }

        for(int i : neededMachines)
        {
            if(machines[i].timeLeft!=0)
            {
                continue;
            }
            int minTimeForMachine=-1;
            int jobId;
            machines[i].timeLeft=minTimeForMachine;
            machines[i].workingOnJob=jobId;
            if(shortestTask==-1 or shortestTask>minTimeForMachine)
            {
                shortestTask=minTimeForMachine;
            }

        }

    }
    
    res.push_back(std::vector<int>{1});
    //int jId=findShortest(testJobs,1);

    std::cout<< res[0][0] << std::endl;

    return 0;
}