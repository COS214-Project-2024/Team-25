#ifndef CityGrowth_H
#define CityGrowth_H

#include <iostream>
#include <vector>
#include <map>

#include "Buildings.h"
#include "Citizen.h"
#include "Transportation.h"

class CitySector {
   public:
    // CitySector();
    // ~CitySector();
    void addBuilding(Building* building);
    int getBuildingCount();
    const std::vector<Building*>& getBuildings() const;
    std::vector<Building*> getBlock();

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
    bool addBuilding(Building* building, int sectorId);
    int getTotalBuildingCount();
    int getTotalSectorCount();
    std::vector<CitySector*> getSectors();
    std::string printSectors();
    void printSectorsCitizens(int sectorID);
    void setRoads(RoadSystemAdapter* rs); 
    

   private:
    std::vector<CitySector*> sectors;
    RoadSystem* roads;
    RoadSystemAdapter* roadsAdapted;
};

#endif  // CityGrowth_H