#include "Transportation.h"
#include <iostream>
#include <cmath>

// Adaptees
// PublicTransport
PublicTransport::PublicTransport(int c, string t, string tt)
{
    capacity = c;
    type = t;
    TransportType = tt;
}
void PublicTransport::add(int amount)
{

    int newAmount = currentAmount + amount;
    if (newAmount <= capacity)
    {
        currentAmount = newAmount;
        if (TransportType == "bus")
        {
            std::cout << "Passengers added to" + type + " bus" << std::endl;
        }
        else if (TransportType == "train")
        {
            std::cout << "Material added to" + type + " train" << std::endl;
        }
    }
    else
    {
        upgrade();
        add(amount);
    }
}

// Increases the capacity of the buses/trains
void PublicTransport::upgrade()
{
    capacity += 10;
}

int PublicTransport::getAmount()
{
    return currentAmount;
}

// Road
Road::Road(int mB, string t)
{
    maxNumOfBusses = mB;
    type = t;
}

void Road::addBus(PublicTransport bus)
{
    busses.push_back(bus);
}

string Road::getType() const
{
    return type;
}

int Road::getNumBusses()
{
    return numOfBusses;
}

int Road::getMaxNumOfBusses()
{
    return maxNumOfBusses;
}

// RoadSystem
void RoadSystem::addRoad(Road road)
{
    numRoads++;
    roads.push_back(road);
}

void RoadSystem::upgrade()
{
    int utilization = getUtilization();
    int CommercialTotal = 0;
    int GovernmentTotal = 0;
    int IndustrialTotal = 0;


    for (vector<Road>::iterator it = roads.begin(); it != roads.end(); ++it) {
        Road& road = *it;
        string currentType = road.getType();

        if(currentType=="Commercial") {CommercialTotal++;}
        if(currentType=="Government") {GovernmentTotal++;}
        if(currentType=="Industrial") {IndustrialTotal++;}

    }

    int smallestTotal = std::min(CommercialTotal, std::min(GovernmentTotal, IndustrialTotal));
    string fewestRoadType;

    if(smallestTotal==CommercialTotal){fewestRoadType="Commercial";}
    if(smallestTotal==GovernmentTotal){fewestRoadType="Government";}
    if(smallestTotal==IndustrialTotal){fewestRoadType="Industrial";}

    if (utilization >= 60 && utilization <= 69) {
        Road newRoad(10, fewestRoadType); 
        addRoad(newRoad);
    } 
    else if (utilization >= 70 && utilization <= 79) {
        Road newRoad(20, fewestRoadType);
        addRoad(newRoad);
    } 
    else if (utilization >= 80 && utilization <= 89) {
        Road newRoad(30, fewestRoadType);
        addRoad(newRoad);
    } 
    else if (utilization >= 90 && utilization <= 100) {
        Road newRoad(40, fewestRoadType);
        addRoad(newRoad);
    }
}

int RoadSystem::getUtilization()
{
    float totalUtilization = 0;
    ;

    for (vector<Road>::iterator it = roads.begin(); it != roads.end(); ++it)
    {
        Road &road = *it;

        float roadUsage = road.getNumBusses() / road.getMaxNumOfBusses();
        totalUtilization += roadUsage;
    }

    float utilizationPercentage = totalUtilization / numRoads * 100;
    int utilization = ceil(utilizationPercentage);

    return utilization;
}

vector<Road> &RoadSystem::getRoads()
{
    return roads;
}

// class Railway
Railway::Railway(){
}

void Railway::addTrain(PublicTransport train)
{
    trains.push_back(train);
}

int Railway::getNumTrains()
{
    return numOfTrains;
}

// RailSystem
void RailSystem::addRailway(Railway railway)
{
    numRailways++;
    railways.push_back(railway);
}

void RailSystem::upgrade()
{
    int utilization = getUtilization();
    // still need to figure out which type of railway is needed???
    if (utilization >= 7)
    {
        Railway newRailway;
        addRailway(newRailway);
    }
    else if (utilization >= 8)
    {
        for (int i = 0; i <= 1; i++)
        {
            Railway newRailway;
            addRailway(newRailway);
        }
    }
    else if (utilization >= 9)
    {
        for (int i = 0; i <= 2; i++)
        {
            Railway newRailway;
            addRailway(newRailway);
        }
    }
}

int RailSystem::getUtilization()
{

    int totalTrains = 0;
    for (vector<Railway>::iterator it = railways.begin(); it != railways.end(); ++it)
    {
        Railway &railway = *it;
        totalTrains += railway.getNumTrains();
    }

    float trainPerRailway = totalTrains / numRailways;

    int utilization = ceil(trainPerRailway);
    return utilization;
}

// Adapters
// PublicTransitAdapter
PublicTransitAdapter::PublicTransitAdapter(PublicTransport *publicTransport)
    : transitSystem(publicTransport) {}

void PublicTransitAdapter::addRoute(int amount)
{
    transitSystem->add(amount);
}

int PublicTransitAdapter::getUtilization()
{
    return transitSystem->getAmount();
}

void PublicTransitAdapter::performMaintenance()
{
    transitSystem->upgrade();
}

// RoadSystemAdapter
RoadSystemAdapter::RoadSystemAdapter(RoadSystem *roadSystem)
    : roadSystem(roadSystem) {}

RoadSystemAdapter::~RoadSystemAdapter()
{
    delete roadSystem;
}

void RoadSystemAdapter::addRoute(Road road)
{
    roadSystem->addRoad(road);
}

vector<Road> &RoadSystemAdapter::getRoads()
{
    return roadSystem->getRoads();
}

int RoadSystemAdapter::getUtilization()
{
    return roadSystem->getUtilization();
}

void RoadSystemAdapter::performMaintenance()
{
    roadSystem->upgrade();
}

// RailSystemAdapter
RailSystemAdapter::RailSystemAdapter(RailSystem *railSystem)
    : railSystem(railSystem) {}

void RailSystemAdapter::addRoute(Railway railway)
{
    railSystem->addRailway(railway);
}

int RailSystemAdapter::getUtilization()
{
    return railSystem->getUtilization();
}

void RailSystemAdapter::performMaintenance()
{
    railSystem->upgrade();
}
