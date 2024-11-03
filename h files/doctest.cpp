#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>

#include "Utilities.h"
#include "Resources.h"
#include "CityGrowth.h"
#include "TaxSystem.h"
#include "Buildings.h"
#include "doctest.h"

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

