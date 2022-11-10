#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

struct Task
{
    int mNumber;
    int pTime;
};

struct Job
{
    int id;
    std::vector<Task> tasks;
    int shortestPossiblePTime=0;
    //int currentTask=0;
    
    /* 
    void calcSPPT()
    {
        for(Task t : tasks)
        {
            this->shortestPossiblePTime+=t.pTime;
        }

    }
    */
};

struct Machine
{
    int workingOnJob=-1;
    int timeLeft=0;
};



std::ostream& operator<< (std::ostream& stream,Job& j)
{
    int i=0;
    for(Task t : j.tasks)
    {
        stream << "Task: " << i++ << " ( M " << t.mNumber << ", PT " << t.pTime << " ) "; 
    }
    return stream;
}

