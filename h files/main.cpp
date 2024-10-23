#include <iostream>

#include "Utilities.h"
#include "Resources.h"
#include "CityGrowth.h"
#include "TaxSystem.h"
#include "Buildings.h"

int main(int argc, char const *argv[])
{
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
        // House(std::string name, int numRooms, int m_squared, float value, int
        // numBedrooms, int numBathrooms, int kitchenSize)
        House* newHouse = new House("0", 1, 500, 100000, 1, 1, 20);
        // make sure the new houses only go into the valid sector positions
        citygrowth->addBuilding(newHouse, i % citygrowth->getTotalSectorCount());
    }

    std::cout << citygrowth->printSectors();

    // House(std::string name, int numRooms, int m_squared, float value, int
    // numBedrooms, int numBathrooms, int kitchenSize) House* house0 = new
    // House("0", 1, 500, 100000, 1, 1, 20); citygrowth->addBuilding(house0, 0);

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

    return 0;
}
