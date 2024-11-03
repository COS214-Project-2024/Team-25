#ifndef CityGrowth_H
#define CityGrowth_H

#include <iostream>
#include <vector>
#include <map>

#include "Buildings.h"
#include "Citizen.h"
#include "Transportation.h"

/**
 * @class CitySector
 * @brief Represents a sector within the city containing buildings.
 *
 * The CitySector class manages a collection of buildings in a specific area of the city. It provides methods 
 * to add buildings, retrieve the number of buildings, and access the list of buildings in the sector.
 */
class CitySector {
public:
    /**
     * @brief Destructor for CitySector.
     */
    ~CitySector();

    /**
     * @brief Adds a building to the city sector.
     * @param building A pointer to the Building object to be added.
     */
    void addBuilding(Building* building);

    /**
     * @brief Gets the count of buildings in the sector.
     * @return The number of buildings in the sector.
     */
    int getBuildingCount();

    /**
     * @brief Gets a constant reference to the vector of buildings in the sector.
     * @return A constant reference to a vector containing pointers to Building objects.
     */
    const std::vector<Building*>& getBuildings() const;

    /**
     * @brief Gets a vector representing the block of buildings.
     * @return A vector containing pointers to Building objects in the block.
     */
    std::vector<Building*> getBlock();

private:
    std::vector<Building*> block;  ///< Vector of pointers to buildings in the sector.
    // std::vector<Citizen*> population;  // Future implementation could include a population vector.
};




/**
 * @class CityGrowth
 * @brief Represents the overall growth and management of the city.
 *
 * The CityGrowth class inherits from CitySector and manages multiple city sectors. It handles 
 * the addition of sectors and buildings, tracks total building and sector counts, and manages 
 * city infrastructure such as roads.
 */
class CityGrowth : public CitySector {
public:
    /**
     * @brief Default constructor for CityGrowth.
     */
    CityGrowth();

    /**
     * @brief Destructor for CityGrowth.
     */
    ~CityGrowth();

    // Future implementations could include methods for managing population growth, housing needs, 
    // economic development, and infrastructure expansion.

    /**
     * @brief Adds a new sector to the city growth management.
     */
    void addSector();

    /**
     * @brief Adds an existing sector to the city growth management.
     * @param sector A pointer to the CitySector object to be added.
     */
    void addSector(CitySector* sector);

    /**
     * @brief Adds a building to a specified sector.
     * @param building A pointer to the Building object to be added.
     * @param sectorId The identifier of the sector where the building should be added.
     * @return True if the building was successfully added, false otherwise.
     */
    bool addBuilding(Building* building, int sectorId);

    /**
     * @brief Gets the total count of buildings across all sectors.
     * @return The total number of buildings in the city.
     */
    int getTotalBuildingCount();

    /**
     * @brief Gets the total count of sectors in the city.
     * @return The total number of sectors.
     */
    int getTotalSectorCount();

    /**
     * @brief Gets a vector of pointers to the sectors in the city.
     * @return A vector containing pointers to CitySector objects.
     */
    std::vector<CitySector*> getSectors();

    /**
     * @brief Prints information about all sectors in the city.
     * @return A string containing information about the sectors.
     */
    std::string printSectors();

    /**
     * @brief Prints the citizens in a specified sector.
     * @param sectorID The identifier of the sector whose citizens will be printed.
     */
    void printSectorsCitizens(int sectorID);

    /**
     * @brief Sets the road system for the city.
     * @param rs A pointer to a RoadSystemAdapter object representing the road system.
     */
    void setRoads(RoadSystemAdapter* rs); 

private:
    std::vector<CitySector*> sectors; ///< Vector of pointers to sectors in the city.
    RoadSystemAdapter* roadsAdapted;   ///< Pointer to the adapted road system.
};

#endif  // CityGrowth_H
