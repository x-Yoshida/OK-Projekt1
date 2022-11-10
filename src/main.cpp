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
    int min=INT32_MAX;
    int jobId;
    for(Job j : jobs)
    {
        if(j.tasks[0].mNumber==mId)
        {
            if(min>j.tasks[0].pTime)
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
    std::vector<int> jIndex;
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
        res.push_back(std::vector<int>{});
        jIndex.push_back(i);
    }
    in.close();

    for( Job j : jobs)
    {
        std::cout << j << std::endl;
    }
    std::cout << std::endl;

    std::vector<Job> testJobs = jobs;
    int timeElapsed=0;

    //if(0)
    while (!testJobs.empty())
    {
        int shortestTask = INT32_MAX;
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
                if(shortestTask>machines[i].timeLeft)
                {
                    shortestTask=machines[i].timeLeft;
                }
                continue;
            }
            
            int minTimeForMachine=INT32_MAX;
            int jobId;
            for(Job j : testJobs)
            {
                if(!(j.tasks[0].mNumber==i))
                {
                    continue;
                }
                if(minTimeForMachine>j.tasks[0].pTime)
                {
                    minTimeForMachine=j.tasks[0].pTime;
                    jobId=j.id;
                }
            }
            machines[i].timeLeft=minTimeForMachine;
            machines[i].workingOnJob=jobId;
            if(shortestTask>minTimeForMachine)
            {
                shortestTask=minTimeForMachine;
            }

        }
        for(int i : neededMachines)
        {
            machines[i].timeLeft-=shortestTask;
            if(machines[i].timeLeft==0)
            {
                res[machines[i].workingOnJob].push_back(timeElapsed);
                testJobs[machines[i].workingOnJob].tasks.erase(testJobs[machines[i].workingOnJob].tasks.begin() + 0);
                if(testJobs[machines[i].workingOnJob].tasks.empty())
                {
                    testJobs.erase(testJobs.begin()+machines[i].workingOnJob);
                }
            }
        }
        timeElapsed+=shortestTask;
        std::cout << timeElapsed << std::endl;
    }
    
    //int jId=findShortest(testJobs,1);

    std::cout<< timeElapsed << std::endl;

    return 0;
}