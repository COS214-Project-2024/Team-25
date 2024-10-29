#ifndef ROUTINES_H
#define ROUTINES_H

#include "Buildings.h"
#include "Transportation.h"
#include "CityGrowth.h"
#include <vector>

//Command
class GovernmentCommands
{
public:
    virtual void execute() = 0;
    ~GovernmentCommands();
};

//Invoker
class MonthlyRoutines : public GovernmentCommands
{
protected:
    CityGrowth *citygrowth;
private:
    std::vector<GovernmentCommands*> transportRoutines;
    std::vector<GovernmentCommands*> buildingRoutines;
public:
    MonthlyRoutines(CityGrowth* cg);
    void addtransportRoutines(GovernmentCommands* command);
    void addbuildingRoutines(GovernmentCommands* command);
    void executueTransport();
    void executueBuilding();
    void execute();
};

//ConcreteCommand
class RenovateAllBuildings : public GovernmentCommands
{
private:
    std::vector<Building*> buildings;
public:
    void execute() override;
    RenovateAllBuildings(const std::vector<Building*>& buildings);
};

// Any other Commands will be added here
// Example of EvaluateAllIndustrial, RestoreAllLandmarks 
// They will Inherit from GovernmentCommands and have a vector to
// store all of the relevent objects
// The government.h file will have and object of type MonthlyRoutines
// which will be used to execute all of the commands.

class UpgradeAllRail : public GovernmentCommands
{
private:
    std::vector<RailSystemAdapter*> rails;
public:
    void execute() override;
    UpgradeAllRail(const std::vector<RailSystemAdapter*>& rails);
};

class UpgradeAllRoad : public GovernmentCommands
{
private: 
    std::vector<RoadSystemAdapter*> roads;
public:
    void execute() override;
    UpgradeAllRoad(const std::vector<RoadSystemAdapter*>& roads);
};

class UpgradeAllPub : public GovernmentCommands
{
private: 
    std::vector<PublicTransitAdapter*> pub;
public:
    void execute() override;
    UpgradeAllPub(const std::vector<PublicTransitAdapter*>& pub);
};

#endif // Routines.h

