#include "CityGrowth.h"

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

// CitySector();
// ~CitySector();

/* ------------------------------- CitySector ------------------------------- */

CitySector::~CitySector(){
    for (Building* b : this->block){
        delete b;
    }
    
}

void CitySector::addBuilding(Building *building)
{
    this->block.push_back(building);
}

int CitySector::getBuildingCount() { return this->block.size(); }

const std::vector<Building*>& CitySector::getBuildings() const{
    return block;
}

std::vector<Building*> CitySector::getBlock() {
    return this->block;
}

// void PopulationGrowth();
// void HousingNeeds();
// void EconomicDevelopment();
// void InfrastructureExpansion();

/* ------------------------------- CityGrowth ------------------------------- */

CityGrowth::CityGrowth() {
    for (int i = 0; i < 5; i++)
    {
        addSector();
    }
    
}

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

    this->sectors.at(sectorId)->addBuilding(building);
    std::cout << "Building added successfully to sector " << sectorId << std::endl;
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

std::vector<CitySector*> CityGrowth::getSectors() {
    return this->sectors;
}

std::string CityGrowth::printSectors() {
    std::ostringstream output;
    std::ostringstream BuildingType;
    std::ostringstream populationStream;
    std::ostringstream RoadType;
    int PopulationCapacity = 0;
    int CurrentPopulation = 0;

    output << "---------------------------------\n";
    output << "|\t CityGrowth Stats\t|\n";
    output << "|\t ---------------\t|\n";

    output << "| Total Sectors: " << std::setw(15) << std::left 
           << this->sectors.size() << "|\n";
    output << "| Total buildings: " << std::setw(13) << std::left 
           << this->getTotalBuildingCount() << "|\n";

    // Map to track road types using getRoads()
    std::map<std::string, int> roadMap;

    if (roadsAdapted != nullptr) 
    {
        for (const Road& road : roadsAdapted->getRoads()) 
        {
            roadMap[road.getType()]++;
        }
    }

    // Map to track building types
    std::map<std::string, int> buildingMap;

    for (const auto& SectorOP : this->sectors) {
        for (const auto& BuildingOP : SectorOP->getBlock()) {
            // Track building types
            buildingMap[BuildingOP->getBuildingType()]++;

            // Calculate population for residential buildings
            if (BuildingOP->getBuildingType() == "House") {
                if (House* house = dynamic_cast<House*>(BuildingOP)) {
                    PopulationCapacity += house->getCapacity();
                    CurrentPopulation += house->getCitizens().size();
                }
            } else if (BuildingOP->getBuildingType() == "Apartment") {
                if (Apartment* apartment = dynamic_cast<Apartment*>(BuildingOP)) {
                    PopulationCapacity += apartment->getCapacity();
                    CurrentPopulation += apartment->getCitizens().size();
                }
            } else if (BuildingOP->getBuildingType() == "Mansion") {
                if (Mansion* mansion = dynamic_cast<Mansion*>(BuildingOP)) {
                    PopulationCapacity += mansion->getCapacity();
                    CurrentPopulation += mansion->getCitizens().size();
                }
            }
        }
    }

    // Print building types
    for (auto it = buildingMap.begin(); it != buildingMap.end(); it++) {
        BuildingType << "| " << std::setw(10) << std::left << it->first
                     << " : " << std::setw(2) << std::right << it->second
                     << std::setw(17) << std::right << "|\n";
    }

    // Print road types
    for (auto it = roadMap.begin(); it != roadMap.end(); it++) {
        RoadType << "| " << std::setw(10) << std::left << it->first + " Roads"
                 << " : " << std::setw(2) << std::right << it->second
                 << std::setw(11) << std::right << "|\n";
    }

    populationStream << CurrentPopulation << "/" << PopulationCapacity;

    output << "| Population: \t" << populationStream.str()
           << std::setw(18 - populationStream.str().size()) << std::right << "|\n";
    output << "|\t ---------------\t|\n";
    output << BuildingType.str();
    output << "|\t ---------------\t|\n";
    output << RoadType.str();
    output << "|\t ---------------\t|\n";

    // Display building count for each sector
    for (int i = 0; i < this->sectors.size(); i++) {
        output << "| Sector[" << i << "]: " << std::setw(1) << std::left
               << this->sectors[i]->getBuildingCount() << " buildings"
               << std::setw(10) << std::right << "|\n";
    }

    output << "---------------------------------\n\n";

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

void CityGrowth::setRoads(RoadSystemAdapter *rs)
{
    this->roadsAdapted = rs;
}
