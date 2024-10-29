#ifndef TRANSPORTAION_H
#define TRASNPORTAION_H

#include <vector>

class PublicTransport
{
private:
  
public:
    void addTransport();
    void upgrade();
    int getPassengers();
};

class RoadSystem
{
private:
  
public:
    void addRoads();
    void upgrade();
    int getTrafficFlow();
};

class RailSystem
{
private:
  
public:
    void addRailway();
    void upgrade();
    int getTrainSchedule();
};

class UnifiedTransportSystem 
{
private:
    
public:
    virtual void addRoute() = 0;
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

    void addRoute();

    int getUtilization() override;

    void performMaintenance() override;
};

class RoadSystemAdapter : public UnifiedTransportSystem {
private:
    RoadSystem* roadSystem;

public:
    RoadSystemAdapter(RoadSystem* rs);

    void addRoute() override;

    int getUtilization() override;

    void performMaintenance() override;
};

class RailSystemAdapter : public UnifiedTransportSystem {
private:
    RailSystem* railSystem;

public:
    RailSystemAdapter(RailSystem* rs);

    void addRoute() override;

    int getUtilization() override ;

    void performMaintenance() override;
};

#endif // Transportation.h

