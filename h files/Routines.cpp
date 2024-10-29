#include "Routines.h"
#include <iostream>
#include <algorithm>

GovernmentCommands::~GovernmentCommands() {}

MonthlyRoutines::MonthlyRoutines(CityGrowth *cg)
{
    citygrowth = cg;
}

void MonthlyRoutines::addtransportRoutines(GovernmentCommands *command)
{
    transportRoutines.push_back(command);
}

void MonthlyRoutines::addbuildingRoutines(GovernmentCommands *command)
{
    buildingRoutines.push_back(command);
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

void RenovateAllBuildings::execute()
{
    for (auto building : buildings)
    {
        building->renovate();
    }
}

// RenovateAllBuildings::RenovateAllBuildings()
// {
//     this->buildings = citygrowth->getBuildings();
// }

