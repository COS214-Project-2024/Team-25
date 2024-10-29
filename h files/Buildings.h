#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>
#include <iostream>
#include "Citizen.h"
#include "Resources.h"

class Building {
protected:
    std::string name;
    std::string type; 
    int numRooms;
    int m_squared;
    float value;
    bool built=false;
    Budget* budget;
    Concrete* concrete;
    Steel* steel;
    Wood* wood;
public:
    Building(std::string name, int numRooms, int m_squared, float value, std::string type);
    virtual ~Building() = default;
    virtual void build() = 0;
    virtual Building* clone() = 0;
    virtual void displayCitizens();
    std::string getName();
    std::string getBuildingType();
    bool getBuilt() const {return built;}
};

/******* RESIDENTIAL *******/

class Residential : public Building {
protected:
    int numBedrooms;
    int numBathrooms;
    int capacity;
    std::vector<Citizen*> residents;
public:
    Residential(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity,  std::string type );
    virtual void build() = 0;
    virtual Residential* clone() = 0;
    void addCitizen(Citizen* human);
    void displayCitizens();
    int getLeftOverCapacity();

};

class House : public Residential {
private:
    int kitchenSize;
public:
    House(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, int kitchenSize);
    void build() override;
    House* clone();
};

class Apartment : public Residential {
private:
    int numFloors;
public:
    Apartment(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, int numFloors);
    void build() override;
    Apartment* clone();
};

class Mansion : public Residential {
private:
    bool waterFeature;
public:
    Mansion(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, bool waterFeature);
    void build() override;
    Mansion* clone();
};

/******* COMMERCIAL *******/

class Commercial : public Building {
protected:
    int capacity;
    int numFloors;
    std::vector<Citizen*> employees;
public:
    Commercial(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, std::string type);
    virtual void build() = 0;
    virtual Commercial* clone() = 0;
    void addCitizen(Citizen* human);
    void displayCitizens();
    int getLeftOverCapacity();
};

class Shop : public Commercial {
private:
    int storageRooms;
public:
    Shop(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int storageRooms);
    void build() override;
    Shop* clone();
};

class Office : public Commercial {
private:
    int offices;
public:
    Office(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int offices);
    void build() override;
    Office* clone();
};

class Mall : public Commercial {
private:
    int shops;
public:
    Mall(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int shops);
    void build() override;
    Mall* clone();
};

/******* INDUSTRIAL *******/

class Industrial : public Building {
protected:
    int carbonFootprint;
    int capacity;
    std::vector<Citizen*> employees;
public:
    Industrial(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity, std::string type);
    virtual void build() = 0;
    virtual Industrial* clone() = 0;
    void addCitizen(Citizen* human);
    void displayCitizens();
    int getLeftOverCapacity();
};

class Factory : public Industrial {
public:
    Factory(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity);
    void build() override;
    Factory* clone();
};

class Warehouse : public Industrial {
public:
    Warehouse(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity);
    void build() override;
    Warehouse* clone();
};

class Plant : public Industrial {
public:
    Plant(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity);
    void build() override;
    Plant* clone();
};

/******* LANDMARK *******/

class Landmark : public Building {
protected:
    int culturalRelevance;
public:
    Landmark(std::string name, int numRooms, int m_squared, float value, int culturalRelevance, std::string type);
    virtual void build() = 0;
    virtual Landmark* clone() = 0;
};

class Park : public Landmark {
private:
    int numTrees;
    bool river;
public:
    Park(std::string name, int numRooms, int m_squared, float value, int culturalRelevance, int numTrees, bool river);
    void build() override;
    Park* clone();
};

class Monument : public Landmark {
private:
    int detail;
public:
    Monument(std::string name, int numRooms, int m_squared, float value, int culturalRelevance, int detail);
    void build() override;
    Monument* clone();
};


/******* INSTATUTIONAL *******/

class Instatutional : public Building{
    protected:
        int capacity;
        std::vector<Citizen*> employees;
    public:
        Instatutional(std::string name, int numRooms, int m_squared, float value, int capacity, std::string type);
        void build() = 0;
        virtual Instatutional* clone() = 0;
        void addCitizen(Citizen* human);
        void displayCitizens();
        int  getLeftOverCapacity();
};

class School : public Instatutional {
private:
    int numfloors;
public:
    School(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors);
    void build() override;
    School* clone();
};

class Hospital : public Instatutional {
private:
    int numfloors;
public:
    Hospital(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors);
    void build() override;
    Hospital* clone();
};

class GovermentBuilding : public Instatutional {
private:
    int numfloors;
public:
    GovermentBuilding(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors);
    void build() override;
    GovermentBuilding* clone();
};

#endif //Building.h 