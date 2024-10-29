#ifndef ROUTINES_H
#define ROUTINES_H

#include "Buildings.h"
#include "Transportation.h"
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
private:

    std::vector<GovernmentCommands*> M_Routines;

public:
    void addRoutines(GovernmentCommands* command);
    std::string removeRoutines(GovernmentCommands* command);
    void execute() override;
};

//ConcreteCommand
class RenovateAllResidential : public GovernmentCommands
{
private:
    std::vector<Residential*> residentials;
public:
    void execute() override;
    RenovateAllResidential(const std::vector<Residential*>& residentials);
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

