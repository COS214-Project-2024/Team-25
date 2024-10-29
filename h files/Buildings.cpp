#include "Buildings.h"
#include <iostream>

// Base Building class
Building::Building(std::string name, int numRooms, int m_squared, float value, std::string type)
    : name(name), numRooms(numRooms), m_squared(m_squared), value(value), built(false), type(type) {}

std::string Building::getName(){
    return this->name;
}

std::string Building::getBuildingType(){
    return this->type;
}

void Building::renovate()
{
    if (built)
    {
        value = value + value * 0.1;
    }
    
}

void Building::displayCitizens(){

}


/******* RESIDENTAIL CLASS *******/
Residential::Residential(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, std::string type)
    : Building(name, numRooms, m_squared, value, type), numBedrooms(numBedrooms), numBathrooms(numBathrooms), capacity(capacity) {}

void Residential::addCitizen(Citizen* human){
    if (this->getLeftOverCapacity() != 0)
    {
       residents.push_back(human);
    }else{
        std::cout << "Total capacity reached for " <<  this->getName() << ". Make a new building... "<< "\n";
    }
 }

void Residential::displayCitizens(){
    if (residents.empty())
    {
        std::cout << this->getName() << ": has no residents"<< "\n";
    }else{
        std::cout << "Residents in " << this->getName() << ":\n";
        for (Citizen* person : residents) {
            person->displayInfo();  // Each Citizen class has its own displayInfo method
        }
    }
}

int Residential::getLeftOverCapacity(){
    return (this->capacity - residents.size());
}



// House class
House::House(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, int kitchenSize)
    : Residential(name, numRooms, m_squared, value, numBedrooms, numBathrooms, capacity,"House"), kitchenSize(kitchenSize) {}

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
        this->capacity,
        this->kitchenSize
    );
}

// Apartment class
Apartment::Apartment(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, int numFloors)
    : Residential(name, numRooms, m_squared, value, numBedrooms, numBathrooms, capacity, "Apartment"), numFloors(numFloors) {}

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
        this->capacity,
        this->numFloors
    );
}



// Mansion class
Mansion::Mansion(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, bool waterFeature)
    : Residential(name, numRooms, m_squared, value, numBedrooms, numBathrooms, capacity, "Mansion"), waterFeature(waterFeature) {}

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
        this->capacity,
        this->waterFeature
    );
}


/******* COMMERCIAL CLASS *******/
Commercial::Commercial(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, std::string type)
    : Building(name, numRooms, m_squared, value,type), capacity(capacity), numFloors(numFloors) {}

void Commercial::addCitizen(Citizen* human){
    if (this->getLeftOverCapacity() != 0)
    {
       employees.push_back(human);
    }else{
        std::cout << "No more employees needed for " <<  this->getName() << ". Make a new building... "<< "\n";
    }
 }

void Commercial::displayCitizens(){
    if (employees.empty())
    {
        std::cout << this->getName() << ": has no employees"<< "\n";
    }else{
        std::cout << "Employees in " << this->getName() << ":\n";
        for (Citizen* person : employees) {
            person->displayInfo();  // Each Citizen class has its own displayInfo method
        }
    }
    
    
}

int Commercial::getLeftOverCapacity(){
    return (this->capacity - employees.size());
    
}


// Shop class
Shop::Shop(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int storageRooms)
    : Commercial(name, numRooms, m_squared, value, capacity, numFloors, "Shop"), storageRooms(storageRooms) {}

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
    : Commercial(name, numRooms, m_squared, value, capacity, numFloors, "Office"), offices(offices) {}

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
    : Commercial(name, numRooms, m_squared, value, capacity, numFloors, "Mall"), shops(shops) {}

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





/******* INDUSTRIAL CLASS *******/
Industrial::Industrial(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity, std::string type)
    : Building(name, numRooms, m_squared, value, type), carbonFootprint(carbonFootprint), capacity(capacity) {}

void Industrial::addCitizen(Citizen* human){
    if (this->getLeftOverCapacity() != 0)
    {
       employees.push_back(human);
    }else{
        std::cout << "No more employees needed for " <<  this->getName() << ". Make a new building... "<< "\n";
    }
 }

void Industrial::displayCitizens(){
    if (employees.empty())
    {
        std::cout << this->getName() << ": has no employees"<< "\n";
    }else{
        std::cout << "Employees in " << this->getName() << ":\n";
        for (Citizen* person : employees) {
            person->displayInfo();  
        }
    }
}

int  Industrial::getLeftOverCapacity(){
    return (this->capacity - employees.size());
}


// Factory class
Factory::Factory(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity)
    : Industrial(name, numRooms, m_squared, value, carbonFootprint, capacity, "Factory") {}

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
        this->carbonFootprint,
        this->capacity
    );
}

// Warehouse class
Warehouse::Warehouse(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity)
    : Industrial(name, numRooms, m_squared, value, carbonFootprint, capacity, "Warehouse") {}

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
        this->carbonFootprint,
        this->capacity
    );
}

// Plant class
Plant::Plant(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity)
    : Industrial(name, numRooms, m_squared, value, carbonFootprint, capacity, "Plant") {}

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
        this->carbonFootprint,
        this->capacity
    );
}





/******* LANDMARK CLASS *******/
Landmark::Landmark(std::string name, int numRooms, int m_squared, float value, int culturalRelevance, std::string type)
    : Building(name, numRooms, m_squared, value, type), culturalRelevance(culturalRelevance) {}

// Park class
Park::Park(std::string name, int numRooms, int m_squared, float value, int culturalRelevance, int numTrees, bool river)
    : Landmark(name, numRooms, m_squared, value, culturalRelevance, "Park"), numTrees(numTrees), river(river) {}

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
    : Landmark(name, numRooms, m_squared, value, culturalRelevance, "Monument"), detail(detail) {}

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





/******* INSTATUTIONAL CLASS *******/
Instatutional::Instatutional(std::string name, int numRooms, int m_squared, float value, int capacity, std::string type)
 : Building(name, numRooms, m_squared, value, type), capacity(capacity) {}

void Instatutional::addCitizen(Citizen* human){
   if (this->getLeftOverCapacity() != 0)
    {
       employees.push_back(human);
    }else{
        std::cout << "No more employees needed for " <<  this->getName() << ". Make a new building... "<< "\n";
    }
}

void Instatutional::displayCitizens(){
     if (employees.empty())
    {
        std::cout << this->getName() << ": has no employees"<< "\n";
    }else{
        std::cout << "Employees in " << this->getName() << ":\n";
        for (Citizen* person : employees) {
            person->displayInfo();  
        }
    }
}

int  Instatutional::getLeftOverCapacity(){
    return (this->capacity - employees.size());
}


//School
School::School(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors)
    : Instatutional(name, numRooms, m_squared, value, capacity,"School"), numfloors(numfloors) {}

void School::build(){
    int baseNeeded = m_squared + (numRooms * 150) + (numfloors * 200);
    int concreteNeeded = baseNeeded * numfloors;
    int woodNeeded = baseNeeded * numfloors;
    int steelNeeded = baseNeeded * numfloors;

    if (concrete->getKilo() >= concreteNeeded && wood->getKilo() >= woodNeeded &&
        steel->getKilo() >= steelNeeded && budget->getCash() >= value) {
        
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        wood->setKilo(wood->getKilo() - woodNeeded);
        steel->setKilo(steel->getKilo() - steelNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "School built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the school." << std::endl;
    }
}

School* School::clone(){
    //Check if materials are avialable to clone the current house
    if (this == nullptr) 
    {
        std::cout << "No School was currently built" << std::endl;    
    }

    return new School(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->capacity,
        this->numfloors
    );
}


//Hospital
Hospital::Hospital(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors)
    : Instatutional(name, numRooms, m_squared, value, capacity,"Hospital"), numfloors(numfloors) {}

void Hospital::build(){
    int baseNeeded = m_squared + (numRooms * 150) + (numfloors * 200);
    int concreteNeeded = baseNeeded * numfloors;
    int woodNeeded = baseNeeded * numfloors;
    int steelNeeded = baseNeeded * numfloors;

    if (concrete->getKilo() >= concreteNeeded && wood->getKilo() >= woodNeeded &&
        steel->getKilo() >= steelNeeded && budget->getCash() >= value) {
        
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        wood->setKilo(wood->getKilo() - woodNeeded);
        steel->setKilo(steel->getKilo() - steelNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Hospital built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the hospital." << std::endl;
    }
}

Hospital* Hospital::clone(){
    //Check if materials are avialable to clone the current house
    if (this == nullptr) 
    {
        std::cout << "No hospital was currently built" << std::endl;    
    }

    return new Hospital(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->capacity,
        this->numfloors
    );
}


//GovermentBuilding
GovermentBuilding::GovermentBuilding(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors)
    : Instatutional(name, numRooms, m_squared, value, capacity,"GovermentBuilding"), numfloors(numfloors) {}

void GovermentBuilding::build(){
    int baseNeeded = m_squared + (numRooms * 150) + (numfloors * 200);
    int concreteNeeded = baseNeeded * numfloors;
    int woodNeeded = baseNeeded * numfloors;
    int steelNeeded = baseNeeded * numfloors;

    if (concrete->getKilo() >= concreteNeeded && wood->getKilo() >= woodNeeded &&
        steel->getKilo() >= steelNeeded && budget->getCash() >= value) {
        
        concrete->setKilo(concrete->getKilo() - concreteNeeded);
        wood->setKilo(wood->getKilo() - woodNeeded);
        steel->setKilo(steel->getKilo() - steelNeeded);
        budget->setCash(budget->getCash() - value);
        built = true;
        std::cout << "Goverment building built successfully!" << std::endl;
    } else {
        built = false;
        std::cout << "Not enough resources to build the Goverment building." << std::endl;
    }
}

GovermentBuilding* GovermentBuilding::clone(){
    //Check if materials are avialable to clone the current house
    if (this == nullptr) 
    {
        std::cout << "No hospital was currently built" << std::endl;    
    }

    return new GovermentBuilding(
        this->name,
        this->numRooms,
        this->m_squared,
        this->value,
        this->capacity,
        this->numfloors
    );
}