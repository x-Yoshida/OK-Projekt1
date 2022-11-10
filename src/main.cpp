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
        }
        jobs.push_back(tmpJob);
        res.push_back(std::vector<int>{});
        jIndex.push_back(i);
    }
    in.close();
    for(int i=0;i<numOfMachines;i++)
    {
        Machine tmpMachine;
        machines.push_back(tmpMachine);
    }
    // for( Job j : jobs)
    // {
    //     std::cout << j << std::endl;
    // }
    // std::cout << std::endl;

    std::vector<Job> testJobs = jobs;
    int timeElapsed=0;

    //if(0)
    while (!jIndex.empty())
    {
        int shortestTask = INT32_MAX;
        //int i=0;
        std::vector<int> neededMachines;
        for(int j : jIndex)
        {
            if(!isInVector(neededMachines,testJobs[j].tasks[0].mNumber))
            {
                neededMachines.push_back(testJobs[j].tasks[0].mNumber);
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
            for(int j : jIndex)
            {
                if(!(testJobs[j].tasks[0].mNumber==i))
                {
                    continue;
                }
                if(minTimeForMachine>testJobs[j].tasks[0].pTime)
                {
                    minTimeForMachine=testJobs[j].tasks[0].pTime;
                    jobId=testJobs[j].id;
                }
            }
            machines[i].timeLeft=minTimeForMachine;
            machines[i].workingOnJob=jobId;
            res[machines[i].workingOnJob].push_back(timeElapsed);
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
                //res[machines[i].workingOnJob].push_back(timeElapsed);
                testJobs[machines[i].workingOnJob].tasks.erase(testJobs[machines[i].workingOnJob].tasks.begin());
                if(testJobs[machines[i].workingOnJob].tasks.empty())
                {
                    jIndex.erase(std::find(jIndex.begin(),jIndex.end(),machines[i].workingOnJob));
                }
            }
        }
        timeElapsed+=shortestTask;
        //std::cout << timeElapsed << std::endl;
    }

    std::ofstream out;
    out.open("res.txt");
    out<< timeElapsed << std::endl;

    for(int i = 0;i<numOfJobs;i++)
    {
        for(int j= 0; j<numOfMachines;j++)
        {
            out << res[i][j] << " ";
        }
        out << std::endl;
    }
    //int jId=findShortest(testJobs,1);


    return 0;
}