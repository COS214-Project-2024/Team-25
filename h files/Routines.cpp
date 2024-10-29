#include "Routines.h"
#include <iostream>
#include <algorithm>

GovernmentCommands::~GovernmentCommands() {}


void MonthlyRoutines::addRoutines(GovernmentCommands* command) 
{
    M_Routines.push_back(command);
}

void MonthlyRoutines::addtransportRoutines(GovernmentCommands *command)
{
    transportRoutines.push_back(command);
}

void MonthlyRoutines::addbuildingRoutines(GovernmentCommands *command)
{
    buildingRoutines.push_back(command);
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

std::string MonthlyRoutines::removetransportRoutines(GovernmentCommands *command)
{
    if (!transportRoutines.empty()) 
    {
        auto it = std::find(transportRoutines.begin(), transportRoutines.end(), command);

        if (it != transportRoutines.end())
        {
            transportRoutines.erase(it);
            return "Trnasport Routine removed successfully";
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

std::string MonthlyRoutines::removebuildingRoutines(GovernmentCommands *command)
{
     if (!buildingRoutines.empty()) 
    {
        auto it = std::find(buildingRoutines.begin(), buildingRoutines.end(), command);

        if (it != buildingRoutines.end())
        {
            buildingRoutines.erase(it);
            return "Building Routine removed successfully";
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

void MonthlyRoutines::executueTransport()
{
    if (!transportRoutines.empty())
    {
        for (auto tRoutine : transportRoutines)
        {
            tRoutine->execute();
        }
    }
    
}

void MonthlyRoutines::executueBuilding()
{
   if (!buildingRoutines.empty())
   {
       for (auto buildings : buildingRoutines)
       {
            buildings->execute();
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

void UpgradeAllRail::execute()
{
    for (auto rail : rails) 
    {        
        rail->performMaintenance();
    } 
}

UpgradeAllRail::UpgradeAllRail(const std::vector<RailSystemAdapter*> &rails)
{
    this->rails = rails;
}

void UpgradeAllRoad::execute()
{
    for (auto road : roads) 
    {        
        road->performMaintenance();
    } 
}

UpgradeAllRoad::UpgradeAllRoad(const std::vector<RoadSystemAdapter *> &roads)
{
    this->roads = roads;
}

void UpgradeAllPub::execute()
{
    for (auto pt : pub) 
    {        
        pt->performMaintenance();
    } 
}

UpgradeAllPub::UpgradeAllPub(const std::vector<PublicTransitAdapter *> &pub)
{
    this->pub = pub;
}
