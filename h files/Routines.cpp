#include "Routines.h"
#include <iostream>
#include <algorithm>

GovernmentCommands::~GovernmentCommands() {}


void MonthlyRoutines::addRoutines(GovernmentCommands* command) 
{
    M_Routines.push_back(command);
}

std::string MonthlyRoutines::removeRoutines(GovernmentCommands* command) 
{
    if (!M_Routines.empty()) 
    {
        auto it = std::find(M_Routines.begin(), M_Routines.end(), command);

        if (it != M_Routines.end())
        {
            M_Routines.erase(it);
            return "Monthly Routine removed successfully";
        }
        else
        {
            return "Governement Command is not part of these Routines";
        }
        
    }
    else    
    {
        return "Governement Command does not exist";
    }
}

void MonthlyRoutines::execute()  
{
    if (!M_Routines.empty())
    {
        for (auto routine : M_Routines)
        {
            routine->execute();
        }
        
    }
    
}

// RenovateAllResidential class implementation

RenovateAllResidential::RenovateAllResidential(const std::vector<Residential*>& residentials) 
{
    this->residentials = residentials;
}

void RenovateAllResidential::execute() 
{
    // for (auto residential : residentials) 
    // {
    //     if (residential.getRenStatus() == true)
    //     {
    //         residential.renovate();
    //     }
        
    // }
}