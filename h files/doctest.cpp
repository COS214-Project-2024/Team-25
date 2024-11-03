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


TEST_CASE("Testing Buildings"){
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

