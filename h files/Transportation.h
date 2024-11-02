#ifndef TRANSPORTATION_H
#define TRANSPORTATION_H

#include <vector>
#include <iostream>
using namespace std;

class PublicTransport
{
private:
    //Commercial busses transport CommercialWorkers to/from Residence: House to/from Workplace: shop/mall/office
    //Government busses transport GovernmentWorkers to/from Residence: Mansion to/from Workplace: school/hospital/government 
    //Industrial busses transport IndustrialWorker to/from Residence: Apartment to/from Workplace: warehouse/plant/factory    
    string type; 
    string TransportType;     
    int currentAmount;
    int capacity;
public:
    PublicTransport(int capacity, string type,string TransportType);
    void add(int amount);
    void upgrade();
    int getAmount();
};


class Road
{
private:
    int numOfBusses;
    //Commercial busses transport CommercialWorkers to/from Residence: House to/from Workplace: shop/mall/office on a Commercial road
    //Government busses transport GovernmentWorkers to/from Residence: Mansion to/from Workplace: school/hospital/government on a Government road
    //Industrial busses transport IndustrialWorker to/from Residence: Apartment to/from Workplace: warehouse/plant/factory on a Industrial road
    string type;   
    int maxNumOfBusses;
    vector<PublicTransport> busses;

public:
    Road(int maxBusses, string type);
    void addBus(PublicTransport bus);
    string getType() const;
    int getNumBusses();
    int getMaxNumOfBusses();

};

class RoadSystem
{
private:
    int numRoads;
    vector<Road> roads;
public:
    void addRoad(Road road);
    void upgrade();
    int getUtilization();
    vector<Road>& getRoads();
};

class Railway
{
    private:
        int numOfTrains;
        string type;
        vector<PublicTransport> trains;
    public:
        Railway(string type);
        void addTrain(PublicTransport train);
        string getType();
        int getNumTrains();

};

class RailSystem
{
private:
  int numRailways;
  vector<Railway> railways;
public:
    void addRailway(Railway railway);
    void upgrade();
    int getUtilization();
};

class UnifiedTransportSystem 
{
private:
    
public:
    virtual int getUtilization() = 0;
    virtual void performMaintenance() = 0;
    virtual ~UnifiedTransportSystem() {}
};

// So in the addRoute, getUtilization and performMaintenace function
// of the Adapter classes, the respective method will be called from the 
// original Adaptee class via the object kept in each Adapter class.
// The interface (UnifiedTransportSystem) provides the generic methods each transport system should have.

class PublicTransitAdapter : public UnifiedTransportSystem {
private:
    PublicTransport* transitSystem;

public:
    PublicTransitAdapter(PublicTransport* pts);

    void addRoute(int amount);

    int getUtilization() override;

    void performMaintenance() override;
};

class RoadSystemAdapter : public UnifiedTransportSystem {
private:
    RoadSystem* roadSystem;

public:
    RoadSystemAdapter(RoadSystem* rs);
    ~RoadSystemAdapter();
    void addRoute(Road road);

    vector<Road>& getRoads();

    int getUtilization() override;

    void performMaintenance() override;
};

class RailSystemAdapter : public UnifiedTransportSystem {
private:
    RailSystem* railSystem;

public:
    RailSystemAdapter(RailSystem* rs);

    void addRoute(Railway railway);

    int getUtilization() override ;

    void performMaintenance() override;
};

#endif // Transportation.h

