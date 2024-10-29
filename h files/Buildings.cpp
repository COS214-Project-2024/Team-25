#include "Buildings.h"
#include <iostream>

// Base Building class
Building::Building(std::string name, int numRooms, int m_squared, float value)
    : name(name), numRooms(numRooms), m_squared(m_squared), value(value), built(false) {}

// Residential class
Residential::Residential(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms)
    : Building(name, numRooms, m_squared, value), numBedrooms(numBedrooms), numBathrooms(numBathrooms) {}

// House class
House::House(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int kitchenSize)
    : Residential(name, numRooms, m_squared, value, numBedrooms, numBathrooms), kitchenSize(kitchenSize) {}

void House::build() {
    int concreteNeeded = m_squared + (numRooms * 100) + ((numBedrooms + numBathrooms) * 50);
    int woodNeeded = m_squared + (numRooms * 100) + ((numBedrooms + numBathrooms) * 50);
    
    if (concrete->getKilo() >= concreteNeeded && wood->getKilo() >= woodNeeded && budget->getCash() >= value) {
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        wood->setKilo(wood->getKilo() - woodNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "House built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the house." << std::endl;
    }
}

House* House::clone()
{

    //Check if materials are avialable to clone the current house
    if (this == nullptr) 
    {
        std::cout << "No Houses are currently built" << std::endl;    
    }

    return new House(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->numBedrooms,
        this->numBathrooms,
        this->kitchenSize
    );
}

// Apartment class
Apartment::Apartment(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int numFloors)
    : Residential(name, numRooms, m_squared, value, numBedrooms, numBathrooms), numFloors(numFloors) {}

void Apartment::build() {
    int baseNeeded = m_squared + (numRooms * 100) + ((numBedrooms + numBathrooms) * 50);
    int concreteNeeded = baseNeeded * numFloors;
    int woodNeeded = baseNeeded * numFloors;
    int steelNeeded = baseNeeded * numFloors;
    
    if (concrete->getKilo() >= concreteNeeded && wood->getKilo() >= woodNeeded && 
        steel->getKilo() >= steelNeeded && budget->getCash() >= value) {
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        wood->setKilo(wood->getKilo() - woodNeeded);
        steel->setKilo(steel->getKilo() - steelNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Apartment built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the apartment." << std::endl;
    }
}

Apartment *Apartment::clone()
{
    if (this == nullptr) 
    {
        std::cout << "No Apartments are currently built" << std::endl;    
    }

    return new Apartment(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->numBedrooms,
        this->numBathrooms,
        this->numFloors
    );
}

// Mansion class
Mansion::Mansion(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, bool waterFeature)
    : Residential(name, numRooms, m_squared, value, numBedrooms, numBathrooms), waterFeature(waterFeature) {}

void Mansion::build() {
    int concreteNeeded = m_squared + (numRooms * 100) + ((numBedrooms + numBathrooms) * 50) + (waterFeature ? 100 : 0);
    int woodNeeded = m_squared + (numRooms * 100) + ((numBedrooms + numBathrooms) * 50) + (waterFeature ? 100 : 0);
    
    if (concrete->getKilo() >= concreteNeeded && wood->getKilo() >= woodNeeded && budget->getCash() >= value) {
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        wood->setKilo(wood->getKilo() - woodNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Mansion built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the mansion." << std::endl;
    }
}

Mansion *Mansion::clone()
{
    
    if (this == nullptr) 
    {
        std::cout << "No Mansions are currently built" << std::endl;    
    }

    return new Mansion(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->numBedrooms,
        this->numBathrooms,
        this->waterFeature
    );
}

// Commercial class
Commercial::Commercial(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors)
    : Building(name, numRooms, m_squared, value), capacity(capacity), numFloors(numFloors) {}


// Shop class
Shop::Shop(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int storageRooms)
    : Commercial(name, numRooms, m_squared, value, capacity, numFloors), storageRooms(storageRooms) {}

void Shop::build() {
    int baseNeeded = m_squared + (numRooms * 100) + (capacity * 100) + (storageRooms * 100);
    int concreteNeeded = baseNeeded * numFloors;
    int woodNeeded = baseNeeded * numFloors;
    int steelNeeded = baseNeeded * numFloors;
    
    if (concrete->getKilo() >= concreteNeeded && wood->getKilo() >= woodNeeded && 
        steel->getKilo() >= steelNeeded && budget->getCash() >= value) {
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        wood->setKilo(wood->getKilo() - woodNeeded);
        steel->setKilo(steel->getKilo() - steelNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Shop built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the shop." << std::endl;
    }
}

Shop *Shop::clone()
{
    if (this == nullptr) 
    {
        std::cout << "No Shops are currently built" << std::endl;    
    }

    return new Shop(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->capacity,
        this->numFloors,
        this->storageRooms
    );
}

// Office class
Office::Office(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int offices)
    : Commercial(name, numRooms, m_squared, value, capacity, numFloors), offices(offices) {}

void Office::build() {
    int baseNeeded = m_squared + (numRooms * 100) + (capacity * 100) + (offices * 50);
    int concreteNeeded = baseNeeded * numFloors;
    int woodNeeded = baseNeeded * numFloors;
    int steelNeeded = baseNeeded * numFloors;
    
    if (concrete->getKilo() >= concreteNeeded && wood->getKilo() >= woodNeeded && 
        steel->getKilo() >= steelNeeded && budget->getCash() >= value) {
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        wood->setKilo(wood->getKilo() - woodNeeded);
        steel->setKilo(steel->getKilo() - steelNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Office built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the office." << std::endl;
    }
}

Office *Office::clone()
{
    if (this == nullptr) 
    {
        std::cout << "No Offices are currently built" << std::endl;    
    }

    return new Office(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->capacity,
        this->numFloors,
        this->offices
    );
}

// Mall class
Mall::Mall(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int shops)
    : Commercial(name, numRooms, m_squared, value, capacity, numFloors), shops(shops) {}

void Mall::build() {
    int baseNeeded = m_squared + (numRooms * 100) + (capacity * 100) + (shops * 250);
    int concreteNeeded = baseNeeded * numFloors;
    int woodNeeded = baseNeeded * numFloors;
    int steelNeeded = baseNeeded * numFloors;
    
    if (concrete->getKilo() >= concreteNeeded && wood->getKilo() >= woodNeeded && 
        steel->getKilo() >= steelNeeded && budget->getCash() >= value) {
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        wood->setKilo(wood->getKilo() - woodNeeded);
        steel->setKilo(steel->getKilo() - steelNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Mall built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the mall." << std::endl;
    }
}

Mall *Mall::clone()
{
    if (this == nullptr) 
    {
        std::cout << "No Malls are currently built" << std::endl;    
    }

    return new Mall(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->capacity,
        this->numFloors,
        this->shops
    );
}

// Industrial class
Industrial::Industrial(std::string name, int numRooms, int m_squared, float value, int carbonFootprint)
    : Building(name, numRooms, m_squared, value), carbonFootprint(carbonFootprint) {}


// Factory class
Factory::Factory(std::string name, int numRooms, int m_squared, float value, int carbonFootprint)
    : Industrial(name, numRooms, m_squared, value, carbonFootprint) {}

void Factory::build() {
    int steelNeeded = m_squared + (numRooms * 100) + (carbonFootprint * 50);
    int concreteNeeded = m_squared + (numRooms * 100) + (carbonFootprint * 50);
    
    if (steel->getKilo() >= steelNeeded && concrete->getKilo() >= concreteNeeded && budget->getCash() >= value) {
        steel->setKilo(steel->getKilo() - steelNeeded);
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Factory built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the factory." << std::endl;
    }
}

Factory *Factory::clone()
{
    if (this == nullptr) 
    {
        std::cout << "No Factories are currently built" << std::endl;    
    }

    return new Factory(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->carbonFootprint
    );
}

// Warehouse class
Warehouse::Warehouse(std::string name, int numRooms, int m_squared, float value, int carbonFootprint)
    : Industrial(name, numRooms, m_squared, value, carbonFootprint) {}

void Warehouse::build() {
    int steelNeeded = m_squared + (numRooms * 100) + (carbonFootprint * 50);
    int concreteNeeded = m_squared + (numRooms * 100) + (carbonFootprint * 50);
    
    if (steel->getKilo() >= steelNeeded && concrete->getKilo() >= concreteNeeded && budget->getCash() >= value) {
        steel->setKilo(steel->getKilo() - steelNeeded);
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Warehouse built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the warehouse." << std::endl;
    }
}

Warehouse *Warehouse::clone()
{
    if (this == nullptr) 
    {
        std::cout << "No Warehouses are currently built" << std::endl;    
    }

    return new Warehouse(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->carbonFootprint
    );
}

// Plant class
Plant::Plant(std::string name, int numRooms, int m_squared, float value, int carbonFootprint)
    : Industrial(name, numRooms, m_squared, value, carbonFootprint) {}

void Plant::build() {
    int steelNeeded = m_squared + (numRooms * 100) + (carbonFootprint * 50);
    int concreteNeeded = m_squared + (numRooms * 100) + (carbonFootprint * 50);
    
    if (steel->getKilo() >= steelNeeded && concrete->getKilo() >= concreteNeeded && budget->getCash() >= value) {
        steel->setKilo(steel->getKilo() - steelNeeded);
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Plant built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the plant." << std::endl;
    }
}

Plant *Plant::clone()
{
    if (this == nullptr) 
    {
        std::cout << "No Warehouses are currently built" << std::endl;    
    }

    return new Plant(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->carbonFootprint
    );
}

// Landmark class
Landmark::Landmark(std::string name, int numRooms, int m_squared, float value, int culturalRelevance)
    : Building(name, numRooms, m_squared, value), culturalRelevance(culturalRelevance) {}

// Park class
Park::Park(std::string name, int numRooms, int m_squared, float value, int culturalRelevance, int numTrees, bool river)
    : Landmark(name, numRooms, m_squared, value, culturalRelevance), numTrees(numTrees), river(river) {}

void Park::build() {
    int concreteNeeded = m_squared + (numRooms * 100) + (river ? 200 : 0);
    int woodNeeded = m_squared + (numRooms * 100) + (river ? 200 : 0) + (numTrees * 10);
    
    if (concrete->getKilo() >= concreteNeeded && wood->getKilo() >= woodNeeded && budget->getCash() >= value) {
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        wood->setKilo(wood->getKilo() - woodNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Park built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the park." << std::endl;
    }
}

Park *Park::clone()
{
    if (this == nullptr) 
    {
        std::cout << "No Parks are currently built" << std::endl;    
    }

    return new Park(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->culturalRelevance,
        this->numTrees,
        this->river
    );
}

// Monument class
Monument::Monument(std::string name, int numRooms, int m_squared, float value, int culturalRelevance, int detail)
    : Landmark(name, numRooms, m_squared, value, culturalRelevance), detail(detail) {}

void Monument::build() {
    int concreteNeeded = m_squared + (numRooms * 100) + (detail * 150);
    int woodNeeded = m_squared + (numRooms * 100) + (detail * 150);
    
    if (concrete->getKilo() >= concreteNeeded && wood->getKilo() >= woodNeeded && budget->getCash() >= value) {
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        wood->setKilo(wood->getKilo() - woodNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Monument built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the monument." << std::endl;
    }
}

Monument *Monument::clone()
{
    if (this == nullptr) 
    {
        std::cout << "No Monuments are currently built" << std::endl;    
    }

    return new Monument(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->culturalRelevance,
        this->detail
    );
}
