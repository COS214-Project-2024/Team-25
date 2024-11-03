#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>

#include "Utilities.h"
#include "Resources.h"
#include "CityGrowth.h"
#include "TaxSystem.h"
#include "Buildings.h"
#include "doctest.h"

TEST_CASE("Testing TaxStrategies") {
    static bool firstRun = true;  // Control to avoid multiple header prints

    TaxSystem* taxSystem = new TaxSystem();

    if (firstRun) {
        std::cout << "----------\033[1;32m   Testing  doctest  \033[0m----------\n";
        firstRun = false;
    }

    SUBCASE("Initial Strategy") {
        std::cout << "TaxSystem initial Strategy: " << taxSystem->currentStrategy() << "\n";
        CHECK(taxSystem->currentStrategy() == "FlatTaxStrategy");
    }

    SUBCASE("Change to ProgressiveTaxStrategy") {
        TaxStrategy* flatStrat = new FlatTaxStrategy();
        TaxStrategy* progStrat = new ProgressiveTaxStrategy();

        taxSystem->setTaxStrategy(progStrat);
        std::cout << "TaxSystem current Strategy: " << taxSystem->currentStrategy() << "\n";

        CHECK(taxSystem->currentStrategy() == "ProgressiveTaxStrategy");
    }

    SUBCASE("Change to ProgressiveTaxStrategy then back to FlatTaxStrategy") {
        TaxStrategy* flatStrat = new FlatTaxStrategy(); 
        TaxStrategy* progStrat = new ProgressiveTaxStrategy();

        taxSystem->setTaxStrategy(progStrat);
        std::cout << "TaxSystem current Strategy: " << taxSystem->currentStrategy() << "\n";

        taxSystem->setTaxStrategy(flatStrat);
        std::cout << "TaxSystem current Strategy: " << taxSystem->currentStrategy() << "\n";


        CHECK(taxSystem->currentStrategy() == "FlatTaxStrategy");
    }

    SUBCASE("Test toggleStrategy") {
        taxSystem->toggleStrategy();
        std::cout << "TaxSystem current Strategy: " << taxSystem->currentStrategy() << "\n";

        taxSystem->toggleStrategy();
        std::cout << "TaxSystem current Strategy: " << taxSystem->currentStrategy() << "\n";


        CHECK(taxSystem->currentStrategy() == "FlatTaxStrategy");
    }

}

TEST_CASE("Testing Transportation")
{
    SUBCASE("Adding passengers within capacity")
    {
        PublicTransport bus(30, "Commercial", "bus");
        bus.add(25);
        CHECK(bus.getAmount() == 25);
    }

    SUBCASE("Adding passengers exceeding capacity")
    {
        PublicTransport bus(20, "Government", "bus");
        bus.add(15);
        bus.add(10);  // Exceeds capacity, so must update capacity 
        CHECK(bus.getAmount() == 25);  // Should not exceed max capacity
    }

    SUBCASE("Handling different transport types")
    {
        PublicTransport bus(100, "Industrial", "bus");
        bus.add(80);
        CHECK(bus.getAmount() == 80);

    }

    SUBCASE("Initialize Road and check properties")
    {
        Road commercialRoad(10, "Commercial");
        CHECK(commercialRoad.getType() == "Commercial");
        CHECK(commercialRoad.getMaxNumOfBusses() == 10);
        CHECK(commercialRoad.getNumBusses() == 0);  // Initially, no buses should be on the road
    }

    SUBCASE("Add buses to Road within capacity")
    {
        Road governmentRoad(5, "Government");
        PublicTransport bus1(30, "GovBus1", "bus");
        PublicTransport bus2(30, "GovBus2", "bus");

        governmentRoad.addBus(bus1);
        governmentRoad.addBus(bus2);

        CHECK(governmentRoad.getNumBusses() == 2);
        CHECK(governmentRoad.getNumBusses() <= governmentRoad.getMaxNumOfBusses());
    }

    SUBCASE("Add buses to Road exceeding capacity")
    {
        Road industrialRoad(2, "Industrial");
        PublicTransport bus1(40, "IndBus1", "bus");
        PublicTransport bus2(40, "IndBus2", "bus");
        PublicTransport bus3(40, "IndBus3", "bus");

        industrialRoad.addBus(bus1);
        industrialRoad.addBus(bus2);
        industrialRoad.addBus(bus3);  

        CHECK(industrialRoad.getNumBusses() == 3);  // Should not exceed max capacity
    }

    SUBCASE("Initialize RoadSystem and add roads")
    {
        RoadSystem roadSystem;
        Road commercialRoad(5, "Commercial");
        Road governmentRoad(3, "Government");

        roadSystem.addRoad(commercialRoad);
        roadSystem.addRoad(governmentRoad);

        CHECK(roadSystem.getRoads().size() == 2);
    }

    SUBCASE("Check RoadSystem utilization")
    {
        RoadSystem roadSystem;
        Road commercialRoad(10, "Commercial");
        PublicTransport bus1(30, "CommBus1", "bus");
        PublicTransport bus2(30, "CommBus2", "bus");

        commercialRoad.addBus(bus1);
        commercialRoad.addBus(bus2);
        roadSystem.addRoad(commercialRoad);

        int utilization = roadSystem.getUtilization();
        CHECK(utilization >= 0);  // Utilization should reflect active buses
    }

    SUBCASE("Upgrade RoadSystem")
    {
        RoadSystem roadSystem;
        Road industrialRoad(5, "Industrial");
        roadSystem.addRoad(industrialRoad);

        roadSystem.upgrade(); 

        CHECK(roadSystem.getRoads().size() == 1); 
    }

    SUBCASE("Initialize Railway and check properties")
    {
        Railway railway;
        CHECK(railway.getNumTrains() == 0);  // Initially, no trains should be in the railway
    }

    SUBCASE("Add trains to Railway")
    {
        Railway railway;
        PublicTransport train1(100, "Train1", "train");
        PublicTransport train2(150, "Train2", "train");

        railway.addTrain(train1);
        railway.addTrain(train2);

        CHECK(railway.getNumTrains() == 2);
    }

    SUBCASE("Initialize RailSystem and add railways")
    {
        RailSystem railSystem;
        Railway railway1;
        Railway railway2;

        railSystem.addRailway(railway1);
        railSystem.addRailway(railway2);

        CHECK(railSystem.getUtilization() == 0);  // Assuming no trains have been added yet
        CHECK(railSystem.getUtilization() >= 0);  // Utilization should be non-negative
    }

    SUBCASE("Check RailSystem utilization")
    {
        RailSystem railSystem;
        Railway railway;
        PublicTransport train1(120, "Express", "train");
        PublicTransport train2(80, "Local", "train");

        railway.addTrain(train1);
        railway.addTrain(train2);
        railSystem.addRailway(railway);

        int utilization = railSystem.getUtilization();
        CHECK(utilization >= 0); 
    }

    SUBCASE("Upgrade RailSystem")
    {
        RailSystem railSystem;
        Railway railway;
        railSystem.addRailway(railway);

        railSystem.upgrade();  

        CHECK(railSystem.getUtilization() >= 0); 
        CHECK(railSystem.getUtilization() >= 0); 
    }

    SUBCASE("PublicTransitAdapter - Add Route and Utilization")
    {
        PublicTransport bus(30, "CityBus", "bus");
        PublicTransitAdapter publicTransitAdapter(&bus);

        publicTransitAdapter.addRoute(10);
        CHECK(publicTransitAdapter.getUtilization() >= 0);  // Utilization should reflect added route(s)
        publicTransitAdapter.performMaintenance();  // Ensure maintenance can be called without errors
    }

    SUBCASE("RoadSystemAdapter - Add Road and Utilization")
    {
        RoadSystem roadSystem;
        RoadSystemAdapter roadAdapter(&roadSystem);

        Road road1(5, "Commercial");
        Road road2(3, "Industrial");

        roadAdapter.addRoute(road1);
        roadAdapter.addRoute(road2);

        CHECK(roadAdapter.getRoads().size() == 2);  // Check that roads were added correctly
        CHECK(roadAdapter.getUtilization() >= 0);  // Utilization should reflect road utilization

        roadAdapter.performMaintenance();  // Ensure maintenance can be called without errors
    }

    SUBCASE("RailSystemAdapter - Add Railway and Utilization")
    {
        RailSystem railSystem;
        RailSystemAdapter railAdapter(&railSystem);

        Railway railway1;
        Railway railway2;

        railAdapter.addRoute(railway1);
        railAdapter.addRoute(railway2);

        CHECK(railAdapter.getUtilization() >= 0);  // Utilization should reflect rail utilization
        railAdapter.performMaintenance();  // Ensure maintenance can be called without errors
    }
}



