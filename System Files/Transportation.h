#ifndef TRANSPORTATION_H
#define TRANSPORTATION_H

#include <vector>
#include <iostream>
using namespace std;

/**
 * @class PublicTransport
 * @brief Represents a public transport system, such as buses or trains.
 *
 * This class manages the type of transport, its capacity, and the current amount of vehicles.
 */
class PublicTransport
{
    //Commercial busses transport CommercialWorkers to/from Residence: House to/from Workplace: shop/mall/office
    //Government busses transport GovernmentWorkers to/from Residence: Mansion to/from Workplace: school/hospital/government 
    //Industrial busses transport IndustrialWorker to/from Residence: Apartment to/from Workplace: warehouse/plant/factory 
    private:
        string type; ///< The type of public transport (e.g., Commercial, Government, Industrial).
        string TransportType; ///< Specific transport classification (e.g., Bus, Train).
        int currentAmount; ///< The current number of vehicles in operation.
        int capacity; ///< The maximum capacity of vehicles.

    public:
        /**
         * @brief Constructs a PublicTransport object.
         * @param capacity The maximum capacity of the transport system.
         * @param type The type of public transport.
         * @param TransportType The specific transport classification.
         */
        PublicTransport(int capacity, string type, string TransportType);

        /**
         * @brief Adds a specified number of vehicles to the transport system.
         * @param amount The number of vehicles to add.
         */
        void add(int amount);

        /**
         * @brief Upgrades the transport system.
         */
        void upgrade();

        /**
         * @brief Gets the current number of vehicles in operation.
         * @return The current amount of vehicles.
         */
        int getAmount();
};



/**
 * @class Road
 * @brief Represents a road for public transport vehicles.
 *
 * This class maintains a list of public transport vehicles and manages their operations.
 */
class Road
{
    //Commercial busses transport CommercialWorkers to/from Residence: House to/from Workplace: shop/mall/office on a Commercial road
    //Government busses transport GovernmentWorkers to/from Residence: Mansion to/from Workplace: school/hospital/government on a Government road
    //Industrial busses transport IndustrialWorker to/from Residence: Apartment to/from Workplace: warehouse/plant/factory on a Industrial road
    private:
        int numOfBusses; ///< The current number of buses on the road.
        string type; ///< The type of road (e.g., Commercial, Government, Industrial).
        int maxNumOfBusses; ///< The maximum number of buses allowed on the road.
        vector<PublicTransport> busses; ///< List of public transport buses.

    public:
        /**
         * @brief Constructs a Road object.
         * @param maxBusses The maximum number of buses that can operate on this road.
         * @param type The type of the road.
         */
        Road(int maxBusses, string type);

        /**
         * @brief Adds a bus to the road.
         * @param bus The PublicTransport object representing the bus to add.
         */
        void addBus(PublicTransport bus);

        /**
         * @brief Gets the type of the road.
         * @return The type of the road.
         */
        string getType() const;

        /**
         * @brief Gets the current number of buses on the road.
         * @return The current number of buses.
         */
        int getNumBusses();

        /**
         * @brief Gets the maximum number of buses allowed on the road.
         * @return The maximum number of buses.
         */
        int getMaxNumOfBusses();
};



/**
 * @class RoadSystem
 * @brief Manages multiple roads and their respective public transport systems.
 *
 * This class tracks the number of roads and their utilization.
 */
class RoadSystem
{
    private:
        int numRoads; ///< The current number of roads in the system.
        vector<Road> roads; ///< List of roads managed by the system.

    public:
        /**
         * @brief Adds a road to the road system.
         * @param road The Road object to add.
         */
        void addRoad(Road road);

        /**
         * @brief Upgrades the road system.
         */
        void upgrade();

        /**
         * @brief Gets the overall utilization of the road system.
         * @return The utilization percentage.
         */
        int getUtilization();

        /**
         * @brief Gets the list of roads in the system.
         * @return A reference to the vector of roads.
         */
        vector<Road>& getRoads();
};



/**
 * @class Railway
 * @brief Represents a railway system for public transport.
 *
 * This class manages the number of trains and their operations.
 */
class Railway
{
    private:
        int numOfTrains; ///< The current number of trains in operation.
        vector<PublicTransport> trains; ///< List of public transport trains.

    public:
        /**
         * @brief Constructs a Railway object.
         */
        Railway();

        /**
         * @brief Adds a train to the railway system.
         * @param train The PublicTransport object representing the train to add.
         */
        void addTrain(PublicTransport train);

        /**
         * @brief Gets the current number of trains in operation.
         * @return The current number of trains.
         */
        int getNumTrains();
};



/**
 * @class RailSystem
 * @brief Manages multiple railways and their respective public transport systems.
 *
 * This class tracks the number of railways and their utilization.
 */
class RailSystem
{
    private:
        int numRailways; ///< The current number of railways in the system.
        vector<Railway> railways; ///< List of railways managed by the system.

    public:
        /**
         * @brief Adds a railway to the rail system.
         * @param railway The Railway object to add.
         */
        void addRailway(Railway railway);

        /**
         * @brief Upgrades the rail system.
         */
        void upgrade();

        /**
         * @brief Gets the overall utilization of the rail system.
         * @return The utilization percentage.
         */
        int getUtilization();
};



/**
 * @class UnifiedTransportSystem
 * @brief Interface for a unified transport system.
 *
 * This interface defines methods that all transport systems must implement for maintenance and utilization.
 */
class UnifiedTransportSystem 
{
    private:

    public:
        /**
         * @brief Gets the utilization of the transport system.
         * @return The utilization percentage.
         */
        virtual int getUtilization() = 0;

        /**
         * @brief Performs maintenance on the transport system.
         */
        virtual void performMaintenance() = 0;

        /**
         * @brief Virtual destructor for proper cleanup of derived classes.
         */
        virtual ~UnifiedTransportSystem() {}
};


// So in the addRoute, getUtilization and performMaintenace function
// of the Adapter classes, the respective method will be called from the 
// original Adaptee class via the object kept in each Adapter class.
// The interface (UnifiedTransportSystem) provides the generic methods each transport system should have.



/**
 * @class PublicTransitAdapter
 * @brief Adapter for integrating PublicTransport into a unified transport system.
 *
 * This class adapts the PublicTransport class to fit the UnifiedTransportSystem interface.
 */
class PublicTransitAdapter : public UnifiedTransportSystem 
{
    private:
        PublicTransport* transitSystem; ///< Pointer to the PublicTransport system being adapted.

    public:
        /**
         * @brief Constructs a PublicTransitAdapter object.
         * @param pts Pointer to the PublicTransport system to adapt.
         */
        PublicTransitAdapter(PublicTransport* pts);

        /**
         * @brief Adds a route to the public transport system.
         * @param amount The number of vehicles to add.
         */
        void addRoute(int amount);

        /**
         * @brief Gets the utilization of the public transport system.
         * @return The utilization percentage.
         */
        int getUtilization() override;

        /**
         * @brief Performs maintenance on the public transport system.
         */
        void performMaintenance() override;
};



/**
 * @class RoadSystemAdapter
 * @brief Adapter for integrating RoadSystem into a unified transport system.
 *
 * This class adapts the RoadSystem class to fit the UnifiedTransportSystem interface.
 */
class RoadSystemAdapter : public UnifiedTransportSystem 
{
    private:
        RoadSystem* roadSystem; ///< Pointer to the RoadSystem being adapted.

    public:
        /**
         * @brief Constructs a RoadSystemAdapter object.
         * @param rs Pointer to the RoadSystem to adapt.
         */
        RoadSystemAdapter(RoadSystem* rs);

        /**
         * @brief Destroys the RoadSystemAdapter object.
         */
        ~RoadSystemAdapter();

        /**
         * @brief Adds a road to the road system.
         * @param road The Road object to add.
         */
        void addRoute(Road road);

        /**
         * @brief Gets the list of roads in the road system.
         * @return A reference to the vector of roads.
         */
        vector<Road>& getRoads();

        /**
         * @brief Gets the utilization of the road system.
         * @return The utilization percentage.
         */
        int getUtilization() override;

        /**
         * @brief Performs maintenance on the road system.
         */
        void performMaintenance() override;
};



/**
 * @class RailSystemAdapter
 * @brief Adapter for integrating RailSystem into a unified transport system.
 *
 * This class adapts the RailSystem class to fit the UnifiedTransportSystem interface.
 */
class RailSystemAdapter : public UnifiedTransportSystem 
{
    private:
        RailSystem* railSystem; ///< Pointer to the RailSystem being adapted.

    public:
        /**
         * @brief Constructs a RailSystemAdapter object.
         * @param rs Pointer to the RailSystem to adapt.
         */
        RailSystemAdapter(RailSystem* rs);

        /**
         * @brief Adds a railway to the rail system.
         * @param railway The Railway object to add.
         */
        void addRoute(Railway railway);

        /**
         * @brief Gets the utilization of the rail system.
         * @return The utilization percentage.
         */
        int getUtilization() override;

        /**
         * @brief Performs maintenance on the rail system.
         */
        void performMaintenance() override;
};


#endif // Transportation.h

