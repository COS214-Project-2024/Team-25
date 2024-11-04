#ifndef ROUTINES_H
#define ROUTINES_H

#include "Buildings.h"
#include "Transportation.h"
#include "CityGrowth.h"
#include <vector>

/**
 * @class GovernmentCommands
 * @brief Abstract base class for government command actions.
 *
 * This class defines the interface for all government commands that can be executed.
 * It provides a pure virtual function `execute()` that must be implemented by derived classes.
 */
class GovernmentCommands
{
public:
    /**
     * @brief Executes the command.
     *
     * This function should contain the logic for the specific command being executed.
     */
    virtual void execute() = 0;

    virtual ~GovernmentCommands(); ///< Virtual destructor for proper cleanup of derived classes.
};

/**
 * @class MonthlyRoutines
 * @brief Concrete invoker class that manages monthly government routines.
 *
 * This class manages the execution of various transport and building routines for the city.
 * It holds a reference to the CityGrowth object and maintains lists of commands to be executed.
 */
class MonthlyRoutines : public GovernmentCommands
{
protected:
    CityGrowth *citygrowth; ///< Pointer to the CityGrowth object for city management.
private:
    std::vector<GovernmentCommands*> transportRoutines; ///< List of transport routine commands.
    std::vector<GovernmentCommands*> buildingRoutines; ///< List of building routine commands.
public:
    /**
     * @brief Constructs a MonthlyRoutines object.
     * @param cg Pointer to the CityGrowth object.
     */
    MonthlyRoutines(CityGrowth* cg);

    /**
     * @brief Adds a transport routine command to the list.
     * @param command Pointer to a GovernmentCommands object representing the transport command.
     */
    void addtransportRoutines(GovernmentCommands* command);

    /**
     * @brief Adds a building routine command to the list.
     * @param command Pointer to a GovernmentCommands object representing the building command.
     */
    void addbuildingRoutines(GovernmentCommands* command);

    /**
     * @brief Executes all transport routines.
     *
     * This function iterates over the transport routines and executes each command.
     */
    void executueTransport();

    /**
     * @brief Executes all building routines.
     *
     * This function iterates over the building routines and executes each command.
     */
    void executueBuilding();

    /**
     * @brief Executes the monthly routines.
     *
     * This function executes both transport and building routines as part of the monthly routines.
     */
    void execute();
};

/**
 * @class RenovateAllBuildings
 * @brief Concrete command class that renovates all buildings.
 *
 * This command class encapsulates the action of renovating all buildings in the city.
 * It holds a vector of Building pointers to operate on during execution.
 */
class RenovateAllBuildings : public GovernmentCommands
{
private:
    std::vector<Building*> buildings; ///< List of buildings to be renovated.
public:
    /**
     * @brief Constructs a RenovateAllBuildings command.
     * @param buildings Vector of pointers to the buildings to be renovated.
     */
    RenovateAllBuildings(const std::vector<Building*>& buildings);

    /**
     * @brief Executes the renovation of all buildings.
     *
     * This function implements the renovation logic for each building in the list.
     */
    void execute() override;
};


// Any other Commands will be added here
// Example of EvaluateAllIndustrial, RestoreAllLandmarks 
// They will Inherit from GovernmentCommands and have a vector to
// store all of the relevent objects
// The government.h file will have and object of type MonthlyRoutines
// which will be used to execute all of the commands.

/**
 * @class UpgradeAllRail
 * @brief Concrete command class that upgrades all rail systems.
 *
 * This command class encapsulates the action of upgrading all rail systems in the city.
 * It holds a vector of RailSystemAdapter pointers representing the rail systems to be upgraded.
 */
class UpgradeAllRail : public GovernmentCommands
{
private:
    std::vector<RailSystemAdapter*> rails; ///< List of rail systems to be upgraded.
public:
    /**
     * @brief Constructs an UpgradeAllRail command.
     * @param rails Vector of pointers to the rail systems to be upgraded.
     */
    UpgradeAllRail(const std::vector<RailSystemAdapter*>& rails);

    /**
     * @brief Executes the upgrade of all rail systems.
     *
     * This function implements the logic for upgrading each rail system in the list.
     */
    void execute() override;
};



/**
 * @class UpgradeAllRoad
 * @brief Concrete command class that upgrades all road systems.
 *
 * This command class encapsulates the action of upgrading all road systems in the city.
 * It holds a vector of RoadSystemAdapter pointers representing the road systems to be upgraded.
 */
class UpgradeAllRoad : public GovernmentCommands
{
private: 
    std::vector<RoadSystemAdapter*> roads; ///< List of road systems to be upgraded.
public:
    /**
     * @brief Constructs an UpgradeAllRoad command.
     * @param roads Vector of pointers to the road systems to be upgraded.
     */
    UpgradeAllRoad(const std::vector<RoadSystemAdapter*>& roads);

    /**
     * @brief Executes the upgrade of all road systems.
     *
     * This function implements the logic for upgrading each road system in the list.
     */
    void execute() override;
};



/**
 * @class UpgradeAllPub
 * @brief Concrete command class that upgrades all public transit systems.
 *
 * This command class encapsulates the action of upgrading all public transit systems in the city.
 * It holds a vector of PublicTransitAdapter pointers representing the public transit systems to be upgraded.
 */
class UpgradeAllPub : public GovernmentCommands
{
private: 
    std::vector<PublicTransitAdapter*> pub; ///< List of public transit systems to be upgraded.
public:
    /**
     * @brief Constructs an UpgradeAllPub command.
     * @param pub Vector of pointers to the public transit systems to be upgraded.
     */
    UpgradeAllPub(const std::vector<PublicTransitAdapter*>& pub);

    /**
     * @brief Executes the upgrade of all public transit systems.
     *
     * This function implements the logic for upgrading each public transit system in the list.
     */
    void execute() override;
};


#endif // Routines.h

