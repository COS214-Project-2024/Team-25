#include <iostream>

#include "Utilities.h"
#include "Resources.h"
#include "CityGrowth.h"
#include "TaxSystem.h"
#include "Buildings.h"

void testCitizenFactories() {
    // Creating factories for each type of worker
    ComWorkerFactory comFactory;
    GovernmentWorkerFactory govFactory;
    IndWorkerFactory indFactory;

    // Using factories to create citizens with specified workplaces
    Citizen* commercialWorker1 = comFactory.createCitizen("Shop");
    Citizen* governmentWorker1 = govFactory.createCitizen("School");
    Citizen* industrialWorker1 = indFactory.createCitizen("Factory");

    // Displaying information for each type of worker with specific workplace
    std::cout << "\nTesting citizens with specified workplaces:" << std::endl;
    commercialWorker1->displayInfo();
    governmentWorker1->displayInfo();
    industrialWorker1->displayInfo();

    // Using factories to create citizens with random workplaces
    Citizen* commercialWorker2 = comFactory.createCitizen();
    Citizen* governmentWorker2 = govFactory.createCitizen();
    Citizen* industrialWorker2 = indFactory.createCitizen();

    // Displaying information for each type of worker with random workplace
    std::cout << "\nTesting citizens with random workplaces:" << std::endl;
    commercialWorker2->displayInfo();
    governmentWorker2->displayInfo();
    industrialWorker2->displayInfo();

    // Clean up memory
    delete commercialWorker1;
    delete governmentWorker1;
    delete industrialWorker1;
    delete commercialWorker2;
    delete governmentWorker2;
    delete industrialWorker2;
}

int main(int argc, char const *argv[])
{
    testCitizenFactories();
    std::cout << "\n\n";
    
     Energy* energy = Energy::getInstance();
     Water* water = Water::getInstance();
     Concrete* concrete = Concrete::getInstance();
     Wood* wood = Wood::getInstance();
     Steel* steel = Steel::getInstance();

     concrete->increase();
     wood->increase();
     steel->increase();

     Utility* powerPlant = new FunctionalPowerPlant(HYDRO);
     powerPlant = powerPlant->mulfunction();


    // /* --------------------------- Testing CityGrowth --------------------------- */
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
        House* newHouse = new House("0", 1, 500, 100000, 1, 1, 20, 2);
        // make sure the new houses only go into the valid sector positions
        citygrowth->addBuilding(newHouse,i % citygrowth->getTotalSectorCount());
    }

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

    std::cout << "Using ProgressiveTaxStrategy:\n";
    taxSystem->setTaxStrategy(progStrat);
    taxSystem->collectTax(citygrowth);

    std::cout << "\n";
    std::cout << "Total collected taxes: " << taxSystem->getCollectedTaxes() << "\n";
    std::cout << "\n";
    std::cout << "Total collected taxes: " << taxSystem->getCollectedTaxes() << "\n";

     House* myHouse = new House("Dream House", 5, 120, 250000.0f, 3, 2, 5, 9);

     ComWorkerFactory comWorkerFactory;
     // Add citizens (workers) to the house

     myHouse->addCitizen(comWorkerFactory.createCitizen("Shop"));
     myHouse->addCitizen(comWorkerFactory.createCitizen("Shop"));
     myHouse->addCitizen(comWorkerFactory.createCitizen("Mall"));
     myHouse->addCitizen(comWorkerFactory.createCitizen("Office"));
     myHouse->addCitizen(comWorkerFactory.createCitizen("Office"));
     myHouse->addCitizen(comWorkerFactory.createCitizen("Mall"));

     myHouse->displayCitizens();

     Warehouse* myWarehouse =
         new Warehouse("Warehouse 2", 5, 120, 250000.0f, 3, 200);

     CitySector* newSector1 = new CitySector();
     citygrowth->addSector(newSector1);

     citygrowth->addBuilding(myHouse, 5);

     CitySector* newSector2 = new CitySector();
     citygrowth->addSector(newSector2);
     citygrowth->addBuilding(myWarehouse, 6);

     std::cout << "\n" << citygrowth->printSectors();
     citygrowth->printSectorsCitizens(6);
     std::cout << "\n";
     citygrowth->printSectorsCitizens(7);
     std::cout << "\n";
     citygrowth->printSectorsCitizens(8);

     delete myHouse;
     delete myWarehouse;
     delete newSector1;
     delete newSector2;

     return 0;
}
