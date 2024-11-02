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
    bool built = false;
    Budget* budget;
    Concrete* concrete;
    Steel* steel;
    Wood* wood;
    std::vector<Citizen*> citizens;

public:
    Building(std::string name, int numRooms, int m_squared, float value, std::string type);
    virtual ~Building();
    std::vector<Citizen*> getCitizens() const {return citizens;}
    virtual void build() = 0;
    virtual Building* clone() = 0;
    virtual void displayCitizens();
    virtual void addCitizen(Citizen* human) = 0;  // Pure virtual function
    virtual int getLeftOverCapacity() = 0;        // Now a pure virtual function
    virtual std::string getType() const = 0;
    
    std::string getName();
    std::string getBuildingType();
    bool getBuilt() const { return built; }
    void renovate();
};

/******* RESIDENTIAL *******/

class Residential : public Building {
protected:
    int numBedrooms;
    int numBathrooms;
    int capacity;
public:
    Residential(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, std::string type);
    virtual void build() = 0;
    virtual Residential* clone() = 0;

    void addCitizen(Citizen* human) override;
    void displayCitizens() override;
    int getLeftOverCapacity() override;  // Implementation of pure virtual function
    int getCapacity();
    std::vector<Citizen*> getCitizens();
    virtual std::string getType() const = 0;
};

class House : public Residential {
private:
    int kitchenSize;
public:
    House(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, int kitchenSize);
    void build() override;
    House* clone() override;
    std::string getType() const override { return type; }
};

class Apartment : public Residential {
private:
    int numFloors;

public:
    Apartment(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, int numFloors);
    void build() override;
    Apartment* clone() override;
    std::string getType() const override { return type; }
};

class Mansion : public Residential {
private:
    bool waterFeature;
public:
    Mansion(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, bool waterFeature);
    void build() override;
    Mansion* clone() override;
    std::string getType() const override { return type; }
};

/******* COMMERCIAL *******/

class Commercial : public Building {
protected:
    int capacity;
    int numFloors;
public:
    Commercial(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, std::string type);
    virtual void build() = 0;
    virtual Commercial* clone() = 0;

    void addCitizen(Citizen* human) override;
    void displayCitizens() override;
    int getLeftOverCapacity() override;  // Implementation of pure virtual function
    virtual std::string getType() const = 0;
};

class Shop : public Commercial {
private:
    int storageRooms;
public:
    Shop(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int storageRooms);
    void build() override;
    Shop* clone() override;
    std::string getType() const override { return type; }
};

class Office : public Commercial {
private:
    int offices;
public:
    Office(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int offices);
    void build() override;
    Office* clone() override;
    std::string getType() const override { return type; }
};

class Mall : public Commercial {
private:
    int shops;
public:
    Mall(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int shops);
    void build() override;
    Mall* clone() override;
    std::string getType() const override { return type; }
};

/******* INDUSTRIAL *******/

class Industrial : public Building {
protected:
    int carbonFootprint;
    int capacity;
public:
    Industrial(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity, std::string type);
    virtual void build() = 0;
    virtual Industrial* clone() = 0;

    void addCitizen(Citizen* human) override;
    void displayCitizens() override;
    int getLeftOverCapacity() override;  // Implementation of pure virtual function
    virtual std::string getType() const = 0;
};

class Factory : public Industrial {
public:
    Factory(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity);
    void build() override;
    Factory* clone() override;
    std::string getType() const override { return type; }
};

class Warehouse : public Industrial {
public:
    Warehouse(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity);
    void build() override;
    Warehouse* clone() override;
    std::string getType() const override { return type; }
};

class Plant : public Industrial {
public:
    Plant(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity);
    void build() override;
    Plant* clone() override;
    std::string getType() const override { return type; }
};

/******* INSTITUTIONAL *******/

class Instatutional : public Building {
protected:
    int capacity;
public:
    Instatutional(std::string name, int numRooms, int m_squared, float value, int capacity, std::string type);
    virtual void build() = 0;
    virtual Instatutional* clone() = 0;

    void addCitizen(Citizen* human) override;
    void displayCitizens() override;
    int getLeftOverCapacity() override;  // Implementation of pure virtual function
    virtual std::string getType() const = 0;
};

class School : public Instatutional {
private:
    int numfloors;
public:
    School(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors);
    void build() override;
    School* clone() override;
    std::string getType() const override { return type; }
};

class Hospital : public Instatutional {
private:
    int numfloors;
public:
    Hospital(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors);
    void build() override;
    Hospital* clone() override;
    std::string getType() const override { return type; }
};

class GovernmentBuilding : public Instatutional {
private:
    int numfloors;
public:
    GovernmentBuilding(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors);
    void build() override;
    GovernmentBuilding* clone() override;
    std::string getType() const override { return type; }
};

#endif // BUILDING_H
