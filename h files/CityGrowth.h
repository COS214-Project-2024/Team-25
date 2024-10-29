#ifndef CityGrowth_H
#define CityGrowth_H

#include <iostream>
#include <vector>

#include "Buildings.h"
#include "Citizen.h"

class CitySector {
   public:
    // CitySector();
    // ~CitySector();
    void addBuilding(Building* building);
    int getBuildingCount();
    const std::vector<Building*>& getBuildings() const;

   private:
    std::vector<Building*> block;
    // std::vector<Citizen*> population;
};

class CityGrowth : public CitySector {
   public:
    CityGrowth();
    ~CityGrowth();
    void PopulationGrowth();
    void HousingNeeds();
    void EconomicDevelopment();
    void InfrastructureExpansion();
    void addSector();
    void addSector(CitySector* sector);
    void addBuilding(Building* building, int sectorId);
    int getTotalBuildingCount();
    int getTotalSectorCount();
    std::string printSectors();
    void printSectorsCitizens(int sectorID);
    

   private:
    std::vector<CitySector*> sectors;
};

#endif  // CityGrowth_H