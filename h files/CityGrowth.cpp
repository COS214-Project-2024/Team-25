#include "CityGrowth.h"

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

// CitySector();
// ~CitySector();

/* ------------------------------- CitySector ------------------------------- */

void CitySector::addBuilding(Building* building) {
    this->block.push_back(building);
}

int CitySector::getBuildingCount() { return this->block.size(); }

const std::vector<Building*>& CitySector::getBuildings() const{
    return block;
}

// void PopulationGrowth();
// void HousingNeeds();
// void EconomicDevelopment();
// void InfrastructureExpansion();

/* ------------------------------- CityGrowth ------------------------------- */

CityGrowth::CityGrowth() {}

CityGrowth::~CityGrowth() {
    for (CitySector* sectorOP : this->sectors) {
        delete sectorOP;
    }
}

void CityGrowth::addSector() {
    CitySector* newSector = new CitySector();
    this->sectors.push_back(newSector);
}

void CityGrowth::addSector(CitySector* sector) {
    this->sectors.push_back(sector);
}

bool CityGrowth::addBuilding(Building* building, int sectorId) {
    if (this->sectors.size() == 0) {
        std::cout << "There are no existing CitySectors.\n";
        return false;
    }

    if ((sectorId < 0) || (sectorId >= this->sectors.size())) {
        std::cout << "Invalid sectorId chosen.\n";
        return false;
    }

    this->sectors[sectorId]->addBuilding(building);
    return true;
}

int CityGrowth::getTotalBuildingCount() {
    int totalBuildings = getBuildingCount();
    for (CitySector* sectorOP : this->sectors) {
        totalBuildings += sectorOP->getBuildingCount();
    }
    return totalBuildings;
}

int CityGrowth::getTotalSectorCount() { return this->sectors.size(); }

std::string CityGrowth::printSectors() {
    std::ostringstream output;
    output << "---------------------------------\n";
    output << "|\t CityGrowth Stats\t|\n";
    output << "|\t ---------------\t|\n";

    output << "| Total Sectors: " << std::setw(15) << std::left
           << this->sectors.size() << "|\n";
    output << "| Total buildings: " << std::setw(13) << std::left
           << this->getTotalBuildingCount() << "|\n";
    output << "|\t ---------------\t|\n";

    for (int i = 0; i < this->sectors.size(); i++) {
        output << "| Sector[" << i << "]: " << std::setw(1) << std::left
               << this->sectors[i]->getBuildingCount() << " buildings"
               << std::setw(10) << std::right << "|\n";
    }
    
    output << "---------------------------------\n";
    output << "\n";

    return output.str();
}

void CityGrowth::printSectorsCitizens(int sectorID){
    if (sectorID < 0 || sectorID > sectors.size())
    {
         std::cout << "Not a valid sector id. " << std::endl;
    }else{
        int sectorId = 1;
        for (const CitySector* sector : sectors) {
            if (sectorId == sectorID)
            {
                std::cout << "Sector " << sectorId << ":" << std::endl;
                for (Building* building : sector->getBuildings()) {
                    building->displayCitizens();
                }
            }
            sectorId++;
        }
    }
}

