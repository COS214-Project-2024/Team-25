#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>

#include "Utilities.h"
#include "Resources.h"
#include "CityGrowth.h"
#include "TaxSystem.h"
#include "Buildings.h"
#include "doctest.h"
#include "Transportation.h"
#include "Routines.h"
#include "Government.h"
#include "Citizen.h"


TEST_CASE("Testing TaxStrategies")
{
    static bool firstRun = true; // Control to avoid multiple header prints

    TaxSystem *taxSystem = new TaxSystem();

    if (firstRun)
    {
        std::cout << "----------\033[1;32m   Testing  doctest  \033[0m----------\n";
        firstRun = false;
    }

    SUBCASE("Initial Strategy")
    {
        std::cout << "TaxSystem initial Strategy: " << taxSystem->currentStrategy() << "\n";
        CHECK(taxSystem->currentStrategy() == "FlatTaxStrategy");
    }

    SUBCASE("Change to ProgressiveTaxStrategy")
    {
        TaxStrategy *flatStrat = new FlatTaxStrategy();
        TaxStrategy *progStrat = new ProgressiveTaxStrategy();

        taxSystem->setTaxStrategy(progStrat);
        std::cout << "TaxSystem current Strategy: " << taxSystem->currentStrategy() << "\n";

        CHECK(taxSystem->currentStrategy() == "ProgressiveTaxStrategy");
    }

    SUBCASE("Change to ProgressiveTaxStrategy then back to FlatTaxStrategy")
    {
        TaxStrategy *flatStrat = new FlatTaxStrategy();
        TaxStrategy *progStrat = new ProgressiveTaxStrategy();

        taxSystem->setTaxStrategy(progStrat);
        std::cout << "TaxSystem current Strategy: " << taxSystem->currentStrategy() << "\n";

        taxSystem->setTaxStrategy(flatStrat);
        std::cout << "TaxSystem current Strategy: " << taxSystem->currentStrategy() << "\n";

        CHECK(taxSystem->currentStrategy() == "FlatTaxStrategy");
    }

    SUBCASE("Test toggleStrategy")
    {
        taxSystem->toggleStrategy();
        std::cout << "TaxSystem current Strategy: " << taxSystem->currentStrategy() << "\n";

        taxSystem->toggleStrategy();
        std::cout << "TaxSystem current Strategy: " << taxSystem->currentStrategy() << "\n";

        CHECK(taxSystem->currentStrategy() == "FlatTaxStrategy");
    }
}
//std::cout << "\n\n";
 
TEST_CASE("Testing CityGrowth") {
        /* --------------------------- Testing CityGrowth --------------------------- */

    CityGrowth* citygrowth = new CityGrowth();

    std::cout << citygrowth->printSectors();

    // CitySector* citySector0 = new CitySector();
    // citygrowth->addSector(citySector0);
    // CitySector* citySector1 = new CitySector();
    // citygrowth->addSector(citySector1);

    for (int i = 0; i < 5; i++) {
        CitySector* newSector = new CitySector();
        citygrowth->addSector(newSector);
    }

    std::cout << citygrowth->printSectors();

    for (int i = 0; i < 18; i++) {
        // House(std::string name, int numRooms, int m_squared, float value,
        // int numBedrooms, int numBathrooms, int kitchenSize)
        House* newHouse = new House("0", 1, 500, 100000, 1, 1, 10, 2);
        CommercialWorker* commercialWorker = new CommercialWorker();
        // make sure the new houses only go into the valid sector positions
        newHouse->addCitizen(commercialWorker);
        
        citygrowth->addBuilding(newHouse,i % citygrowth->getTotalSectorCount());
    }
    Apartment* newApartment = new Apartment("0", 1, 500, 100000, 1, 1, 20, 2);
    citygrowth->addBuilding(newApartment, 2);

    std::cout << citygrowth->printSectors();

    // House(std::string name, int numRooms, int m_squared, float value, int
    // numBedrooms, int numBathrooms, int kitchenSize) House* house0 = new
    // House("0", 1, 500, 100000, 1, 1, 20); citygrowth->addBuilding(house0,
    // 0);

    /* ------------------------------ Testing Taxes ----------------------------- */
    TaxStrategy* flatStrat = new FlatTaxStrategy();
    TaxStrategy* progStrat = new ProgressiveTaxStrategy();
    TaxSystem* taxSystem = new TaxSystem();

    std::cout << "Using FlatTaxStrategy:\n";
    // taxSystem->setTaxStrategy(flatStrat);
    taxSystem->collectTax(citygrowth);

    std::cout <<"\n";
    taxSystem->toggleStrategy();
    taxSystem->toggleStrategy();
    std::cout <<"\n";

    std::cout << "Using ProgressiveTaxStrategy:\n";
    taxSystem->setTaxStrategy(progStrat);
    // taxSystem->toggleStrategy();
    taxSystem->collectTax(citygrowth);

    std::cout << "\n";
    std::cout << "Total collected taxes: " << taxSystem->getCollectedTaxes() << "\n";
    std::cout << "\n";
    std::cout << "Total collected taxes: " << taxSystem->getCollectedTaxes() << "\n";
}

TEST_CASE("Testing CityGrowth") {
        /* --------------------------- Testing CityGrowth --------------------------- */
    std::cout << "\n\n";

    CityGrowth* citygrowth = new CityGrowth();

    std::cout << citygrowth->printSectors();

    // CitySector* citySector0 = new CitySector();
    // citygrowth->addSector(citySector0);
    // CitySector* citySector1 = new CitySector();
    // citygrowth->addSector(citySector1);

    for (int i = 0; i < 5; i++) {
        CitySector* newSector = new CitySector();
        citygrowth->addSector(newSector);
    }

    std::cout << citygrowth->printSectors();

    for (int i = 0; i < 18; i++) {
        // House(std::string name, int numRooms, int m_squared, float value,
        // int numBedrooms, int numBathrooms, int kitchenSize)
        House* newHouse = new House("0", 1, 500, 100000, 1, 1, 10, 2);
        CommercialWorker* commercialWorker = new CommercialWorker();
        // make sure the new houses only go into the valid sector positions
        newHouse->addCitizen(commercialWorker);
        
        citygrowth->addBuilding(newHouse,i % citygrowth->getTotalSectorCount());
    }
    Apartment* newApartment = new Apartment("0", 1, 500, 100000, 1, 1, 20, 2);
    citygrowth->addBuilding(newApartment, 2);

    std::cout << citygrowth->printSectors();

    // House(std::string name, int numRooms, int m_squared, float value, int
    // numBedrooms, int numBathrooms, int kitchenSize) House* house0 = new
    // House("0", 1, 500, 100000, 1, 1, 20); citygrowth->addBuilding(house0,
    // 0);

    /* ------------------------------ Testing Taxes ----------------------------- */
    TaxStrategy* flatStrat = new FlatTaxStrategy();
    TaxStrategy* progStrat = new ProgressiveTaxStrategy();
    TaxSystem* taxSystem = new TaxSystem();

    std::cout << "Using FlatTaxStrategy:\n";
    // taxSystem->setTaxStrategy(flatStrat);
    taxSystem->collectTax(citygrowth);

    std::cout <<"\n";
    taxSystem->toggleStrategy();
    taxSystem->toggleStrategy();
    std::cout <<"\n";

    std::cout << "Using ProgressiveTaxStrategy:\n";
    taxSystem->setTaxStrategy(progStrat);
    // taxSystem->toggleStrategy();
    taxSystem->collectTax(citygrowth);

    std::cout << "\n";
    std::cout << "Total collected taxes: " << taxSystem->getCollectedTaxes() << "\n";
    std::cout << "\n";
    std::cout << "Total collected taxes: " << taxSystem->getCollectedTaxes() << "\n";
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
        RoadSystem* roadSystem = new RoadSystem();
        RoadSystemAdapter roadAdapter(roadSystem);

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
        RailSystem* railSystem = new RailSystem();
        RailSystemAdapter railAdapter(railSystem);

        Railway railway1;
        Railway railway2;

        railAdapter.addRoute(railway1);
        railAdapter.addRoute(railway2);

        CHECK(railAdapter.getUtilization() >= 0);  // Utilization should reflect rail utilization
        railAdapter.performMaintenance();  // Ensure maintenance can be called without errors
        delete railSystem;
    }
}

TEST_CASE("Testing Buildings"){
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Testing Buildings" << std::endl;
    std::cout << "------------------------" << std::endl;
    SUBCASE("Testing connecting buildings and citizens"){
        House* myHouse = new House("Dream House", 5, 120, 250000.0f, 3, 2, 5, 9);

        ComWorkerFactory comWorkerFactory;
        
        // Add citizens (workers) to the house

        myHouse->addCitizen(comWorkerFactory.createCitizen("Shop"));
        CHECK(comWorkerFactory.createCitizen("Shop")->getType() == "Commercial worker");
        CHECK(comWorkerFactory.createCitizen("Shop")->getResidence() == "House");
        CHECK(comWorkerFactory.createCitizen("Shop")->getWorkplace() == "Shop");
        myHouse->addCitizen(comWorkerFactory.createCitizen("Shop"));
        myHouse->addCitizen(comWorkerFactory.createCitizen("Mall"));
        myHouse->addCitizen(comWorkerFactory.createCitizen("Office"));
        myHouse->addCitizen(comWorkerFactory.createCitizen("Office"));
        CHECK(myHouse->getLeftOverCapacity() == 0);
        myHouse->addCitizen(comWorkerFactory.createCitizen("Mall"));

        myHouse->displayCitizens();

        Warehouse* myWarehouse =
        new Warehouse("Warehouse 2", 5, 120, 250000.0f, 3, 200);

        CityGrowth* citygrowth = new CityGrowth();
       std::cout << citygrowth->printSectors();

        CitySector* newSector1 = new CitySector();
        citygrowth->addSector(newSector1);

        citygrowth->addBuilding(myHouse, 0);

        CitySector* newSector2 = new CitySector();
        citygrowth->addSector(newSector2);
        citygrowth->addBuilding(myWarehouse, 1);
        CHECK(citygrowth->getBuildingCount() == 0);

        std::cout << "\n" << citygrowth->printSectors();
        citygrowth->printSectorsCitizens(0);
        std::cout << "\n";
        citygrowth->printSectorsCitizens(1);
        std::cout << "\n";
        citygrowth->printSectorsCitizens(2);

      delete myHouse;
      delete myWarehouse;
      delete newSector1;
      delete newSector2;
    }
}

TEST_CASE("Testing Routines class") 
{
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Testing Routines class" << std::endl;
    std::cout << "------------------------" << std::endl;
    SUBCASE("Verify Road constructor") 
    {
        std::cout << "\n############## Testing Road constructor ##############" << std::endl;
        Road road1(5, "Industrial");
        std::cout << "Road1 Max Busses: " << road1.getMaxNumOfBusses() << std::endl;
        std::cout << "Road1 Type: " << road1.getType() << std::endl;
        std::cout << "Road1 Num Busses: " << road1.getNumBusses() << std::endl;
        CHECK(road1.getMaxNumOfBusses() == 5);
        CHECK(road1.getType() == "Industrial");
        CHECK(road1.getNumBusses() == 0);

        SUBCASE("Test RoadSystem constructor")
        {
            std::cout << "\n############## Testing RoadSystem constructor ##############" << std::endl;
            RoadSystem *roadSystem = new RoadSystem();
            std::cout << "Road System Created" << std::endl;

            SUBCASE("Testing RoadSystemAdapter")
            {
                std::cout << "\n############## Testing RoadSystemAdapter ##############" << std::endl;
                RoadSystemAdapter *roadSystemAdapter = new RoadSystemAdapter(roadSystem);
                std::cout << "Road System Adapter Created" << std::endl;
                roadSystemAdapter->addRoute(road1);
                std::cout << "Route Added to Road System Adapter" << std::endl;
                CHECK(roadSystemAdapter->getRoads().size() == 1);
                CHECK(roadSystemAdapter->getRoads()[0].getType() == "Industrial");
                CHECK(roadSystemAdapter->getRoads()[0].getMaxNumOfBusses() == 5);

                SUBCASE("Creating a Command")
                {
                    std::cout << "\n############## Testing Creating a Command ##############" << std::endl;
                    std::vector<RoadSystemAdapter*> roads = {roadSystemAdapter};
                    GovernmentCommands* upgradeAllRoad = new UpgradeAllRoad(roads);
                    std::cout << "UpgradeAllRoad Command Created" << std::endl;
                    CHECK(upgradeAllRoad != nullptr);

                    SUBCASE("Calling the command")
                    {
                        std::cout << "\n############## Testing Calling the command ##############" << std::endl;
                        upgradeAllRoad->execute();
                        std::cout << "Command Executed" << std::endl;
                        CHECK(roadSystemAdapter->getUtilization() == 0);
                        CHECK(roadSystemAdapter->getRoads().size() == 1);
                        CHECK(roadSystemAdapter->getRoads()[0].getMaxNumOfBusses() == 5);
                        CHECK(roadSystemAdapter->getUtilization() == 0);
                    }
                }
            }
        }
    }
}

TEST_CASE("Testing Resources") {
    SUBCASE("Energy Singleton") {
        Energy* energy1 = Energy::getInstance();
        Energy* energy2 = Energy::getInstance();
        
        CHECK(energy1 == energy2);
        CHECK(energy1->getWattsCoal() == 0);
        CHECK(energy1->getWattsHydro() == 0);
        CHECK(energy1->getWattsWind() == 0);
        CHECK(energy1->getWattsSolar() == 0);
        CHECK(energy1->getTotalWatts() == 0);
    }

    SUBCASE("Water Singleton") {
        Water* water1 = Water::getInstance();
        Water* water2 = Water::getInstance();
        
        CHECK(water1 == water2);
        CHECK(water1->getLiters() == 0);
    }

    SUBCASE("Budget Singleton") {
        Budget* b = Budget::getInstance();
        delete b;
        b= nullptr;
        Budget* budget1 = Budget::getInstance();
        Budget* budget2 = Budget::getInstance();
        
        CHECK(budget1 == budget2);
        CHECK(budget1->getCash() == doctest::Approx(0.0));
        CHECK(budget1->getDebt() == doctest::Approx(0.0));
    }

    SUBCASE("Concrete Material Processing") {
        Concrete* concrete1 = Concrete::getInstance();
        Concrete* concrete2 = Concrete::getInstance();
        
        CHECK(concrete1 == concrete2);
        CHECK(concrete1->getKilo() == 0);

        concrete1->increase();
        // After obtaining 10000kg and refining with 10% loss
        CHECK(concrete1->getKilo() == doctest::Approx(9000));
    }

    SUBCASE("Steel Material Processing") {
        Steel* steel1 = Steel::getInstance();
        Steel* steel2 = Steel::getInstance();
        
        CHECK(steel1 == steel2);
        CHECK(steel1->getKilo() == 0);

        steel1->increase();
        // After obtaining 6000kg and refining with 5% loss
        CHECK(steel1->getKilo() == doctest::Approx(5700));
    }

    SUBCASE("Wood Material Processing") {
        Wood* wood1 = Wood::getInstance();
        Wood* wood2 = Wood::getInstance();
        
        CHECK(wood1 == wood2);
        CHECK(wood1->getKilo() == 0);

        wood1->increase();
        // After obtaining 20000kg and refining with 10% loss
        CHECK(wood1->getKilo() == doctest::Approx(18000));
    }

    SUBCASE("Multiple Material Processing") {
        Concrete* concrete = Concrete::getInstance();
        Steel* steel = Steel::getInstance();
        Wood* wood = Wood::getInstance();

        // Reset all materials to 0 (assuming there are setter methods)
        // If there aren't setters, you might need to modify the class or
        // handle this differently
        concrete->setKilo(0);
        steel->setKilo(0);
        wood->setKilo(0);

        // Process all materials
        concrete->increase();
        steel->increase();
        wood->increase();

        // Check final amounts after processing
        CHECK(concrete->getKilo() == doctest::Approx(9000));
        CHECK(steel->getKilo() == doctest::Approx(5700));
        CHECK(wood->getKilo() == doctest::Approx(18000));
    }
}


TEST_CASE("Testing Utility classes") 
{
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Testing Utility classes" << std::endl;
    std::cout << "------------------------" << std::endl;

    SUBCASE("PowerPlant Construction and Type Verification") 
    {
        std::cout << "\n############## Testing PowerPlant Construction and Type Verification ##############" << std::endl;

        PowerPlant* plant = new FunctionalPowerPlant(HYDRO, true);
        CHECK(plant != nullptr);
        CHECK(plant->getType() == HYDRO);
        std::cout << "PowerPlant Type: HYDRO" << std::endl;

        SUBCASE("Verify Power Generation Calculation") 
        {
            std::cout << "\n############## Verifying Power Generation Calculation ##############" << std::endl;
            int powerGen = plant->getPowerGeneration();
            std::cout << "Power Generation: " << powerGen << " watts" << std::endl;

            CHECK(powerGen >= 1000);
            CHECK(powerGen <= 5000);

            SUBCASE("Simulate Malfunction and Repair") 
            {
                std::cout << "\n############## Simulating PowerPlant Malfunction ##############" << std::endl;

                CHECK(plant != nullptr);

                std::cout << "Plant functionality before malfunction: " 
                          << (plant->getFunctional() ? "true" : "false") << std::endl;

                PowerPlant *malfunctioningPlant = plant->mulfunction();
                PowerPlant *originalPlant = plant;

                if (malfunctioningPlant != plant) {
                    plant=nullptr;
                    delete plant;
                }
                plant = malfunctioningPlant;

                CHECK(malfunctioningPlant != nullptr);
                std::cout << "Plant functionality after malfunction: " 
                          << (malfunctioningPlant->getFunctional() ? "true" : "false") << std::endl;
                CHECK(!malfunctioningPlant->getFunctional());
                std::cout << "PowerPlant is now non-functional." << std::endl;

                SUBCASE("Repair PowerPlant") 
                {
                    std::cout << "\n############## Repairing PowerPlant ##############" << std::endl;

                    PowerPlant *repairedPlant = plant->repair();

                    if (repairedPlant != plant) {
                        delete plant;
                    }
                    plant = repairedPlant;

                    CHECK(repairedPlant != nullptr);

                    std::cout << "Plant functionality after repair: " 
                              << (repairedPlant->getFunctional() ? "true" : "false") << std::endl;
                    CHECK(repairedPlant->getFunctional());
                    std::cout << "PowerPlant has been repaired and is now functional." << std::endl;
                }

                if (plant != originalPlant) {
                    plant=nullptr;
                    delete plant;
                } else {
                    delete originalPlant;
                }
            } 
        }

       if (plant != nullptr)
        delete plant;  
    }
}

TEST_CASE("Testing Citizen Class") {
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Testing Citizen" << std::endl;
    std::cout << "------------------------" << std::endl;
    SUBCASE("Default Constructor") {
        CommercialWorker citizen;
        CHECK(citizen.getResidence() == "House");
        CHECK(citizen.getType() == "Commercial worker");

        // Break down the workplace check into multiple lines
        bool workplaceIsValid = (citizen.getWorkplace() == "Shop") ||
                                (citizen.getWorkplace() == "Office") ||
                                (citizen.getWorkplace() == "Mall");
        CHECK(workplaceIsValid);

        CHECK(citizen.getSatisfaction() >= 20); // Satisfaction should be between 20 and 80
        CHECK(citizen.getSatisfaction() <= 80);
        citizen.displayInfo();
    }

    SUBCASE("SetCitizen Method") {
        CommercialWorker citizen;
        citizen.setCitizen("Test Type", "Test Building", "Test Workplace");
        CHECK(citizen.getType() == "Test Type");
        CHECK(citizen.getResidence() == "Test Building");
        CHECK(citizen.getWorkplace() == "Test Workplace");
        citizen.displayInfo();
    }

    SUBCASE("ChangeSatisfaction Method") {
        CommercialWorker citizen;
        citizen.changeSatisfaction(10.0f);
        CHECK(citizen.getSatisfaction() <= 100); // Ensure satisfaction is capped at 100
        citizen.changeSatisfaction(-200.0f);
        CHECK(citizen.getSatisfaction() == 0);    // Ensure satisfaction is floored at 0
        citizen.displayInfo();
    }
}

TEST_CASE("Testing CommercialWorker Class") {
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Testing CommercialWorker" << std::endl;
    std::cout << "------------------------" << std::endl;
    SUBCASE("Default Constructor") {
        CommercialWorker worker;
        CHECK(worker.getType() == "Commercial worker");
        CHECK(worker.getResidence() == "House");

        // Check for valid workplaces without using complex expressions
        bool workplaceIsValid = (worker.getWorkplace() == "Shop") ||
                                (worker.getWorkplace() == "Office") ||
                                (worker.getWorkplace() == "Mall");
        CHECK(workplaceIsValid);
        worker.displayInfo();
    }

    SUBCASE("Parameterized Constructor") {
        CommercialWorker worker("Office");
        CHECK(worker.getType() == "Commercial worker");
        CHECK(worker.getResidence() == "House");
        CHECK(worker.getWorkplace() == "Office");
        worker.displayInfo();
    }
}

TEST_CASE("Testing GovernmentWorker Class") {
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Testing GovernmentWorker" << std::endl;
    std::cout << "------------------------" << std::endl;
    SUBCASE("Default Constructor") {
        GovernmentWorker worker;
        CHECK(worker.getType() == "Government worker");
        CHECK(worker.getResidence() == "Mansion");

        // Check for valid workplaces without using complex expressions
        bool workplaceIsValid = (worker.getWorkplace() == "School") ||
                                (worker.getWorkplace() == "Hospital") ||
                                (worker.getWorkplace() == "Government");
        CHECK(workplaceIsValid);
        worker.displayInfo();
    }

    SUBCASE("Parameterized Constructor") {
        GovernmentWorker worker("Hospital");
        CHECK(worker.getType() == "Government worker");
        CHECK(worker.getResidence() == "Mansion");
        CHECK(worker.getWorkplace() == "Hospital");
        worker.displayInfo();
    }
}

TEST_CASE("Testing IndustrialWorker Class") {
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Testing IndustrialWorker" << std::endl;
    std::cout << "------------------------" << std::endl;
    SUBCASE("Default Constructor") {
        IndustrialWorker worker;
        CHECK(worker.getType() == "Industrial worker");
        CHECK(worker.getResidence() == "Apartment");

        // Check for valid workplaces without using complex expressions
        bool workplaceIsValid = (worker.getWorkplace() == "Warehouse") ||
                                (worker.getWorkplace() == "Plant") ||
                                (worker.getWorkplace() == "Factory");
        CHECK(workplaceIsValid);
        worker.displayInfo();
    }

    SUBCASE("Parameterized Constructor") {
        IndustrialWorker worker("Factory");
        CHECK(worker.getType() == "Industrial worker");
        CHECK(worker.getResidence() == "Apartment");
        CHECK(worker.getWorkplace() == "Factory");
        worker.displayInfo();
    }
}

TEST_CASE("Testing WorkerFactory Classes") {
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Testing WorkerFactory" << std::endl;
    std::cout << "------------------------" << std::endl;
    SUBCASE("CommercialWorkerFactory") {
        ComWorkerFactory factory;
        Citizen* worker = factory.createCitizen("Mall");
        CHECK(worker->getType() == "Commercial worker");
        CHECK(worker->getWorkplace() == "Mall");
        worker->displayInfo();
        delete worker;  // Clean up
    }

    SUBCASE("GovernmentWorkerFactory") {
        GovernmentWorkerFactory factory;
        Citizen* worker = factory.createCitizen("Government");
        CHECK(worker->getType() == "Government worker");
        CHECK(worker->getWorkplace() == "Government");
        worker->displayInfo();
        delete worker;  // Clean up
    }

    SUBCASE("IndustrialWorkerFactory") {
        IndWorkerFactory factory;
        Citizen* worker = factory.createCitizen("Plant");
        CHECK(worker->getType() == "Industrial worker");
        CHECK(worker->getWorkplace() == "Plant");
        worker->displayInfo();
        delete worker;  // Clean up
    }
}

