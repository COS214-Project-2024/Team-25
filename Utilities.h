#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Resources.h"



enum powerPlants{
    HYDRO, COAL, WIND, SOLAR
};

class Utility
{
protected:
    std::string name;
    float efficiency; // percent of utility that is running
    Budget* budget;
    Concrete* concrete;
    Steel* steel;
    Wood* wood;
public:
    Utility();
    ~Utility();
    virtual Utility* repair() = 0;
    virtual Utility* mulfunction() = 0;

    std::string getName() const { return name; }
    float getEfficiency() const { return efficiency; }

    void setName(const std::string& value) { name = value; }
    void setEfficiency(float value) { efficiency = value; }
};

class PowerPlant : public Utility
{
protected:
    int powerGeneration; //in watts
    powerPlants type;
    Energy* energy;
    
public:
    PowerPlant(powerPlants type);
    ~PowerPlant();
    virtual Utility* repair() = 0;
    virtual Utility* mulfunction() = 0;
    int getPowerGeneration(); // power gen * efficiency
    powerPlants getType();
    void generate();

    int getPowerGenerationRaw() const { return powerGeneration; }
    powerPlants getType() const { return type; }

    void setPowerGeneration(int value) { powerGeneration = value; }
    void setType(powerPlants value) { type = value; }
};

class FunctionalPowerPlant : public PowerPlant
{
private:
public:
    FunctionalPowerPlant(powerPlants type);
    ~FunctionalPowerPlant();
    Utility* repair() override; //does nothing in this class
    Utility* mulfunction() override;
};

class NonFunctionalPowerPlant : public PowerPlant
{
private:
public:
    NonFunctionalPowerPlant(powerPlants type);
    ~NonFunctionalPowerPlant();
    Utility* repair() override; 
    Utility* mulfunction() override; //does nothing in this class
};


class WaterSupply : public Utility
{
protected:
    int waterGeneration; //in liters
    Water* water;
public:
    WaterSupply();
    ~WaterSupply();
    virtual Utility* repair() = 0;
    virtual Utility* mulfunction() = 0;
    int getWaterGeneration();
    void distribute();

    int getWaterGenerationRaw() const { return waterGeneration; }
    void setWaterGeneration(int value) { waterGeneration = value; }
};

class FunctionalWaterSupply : public WaterSupply
{
private:
public:
    FunctionalWaterSupply();
    ~FunctionalWaterSupply();
    Utility* repair() override; //does nothing in this class
    Utility* mulfunction() override;
};

class NonFunctionalWaterSupply : public WaterSupply
{
private:
public:
    NonFunctionalWaterSupply();
    ~NonFunctionalWaterSupply();
    Utility* repair() override; 
    Utility* mulfunction() override; //does nothing in this class
};


class WasteManagement : public Utility
{
protected:
    int wasteCollection; //in kgs
public:
    WasteManagement(/* args */);
    ~WasteManagement();
    virtual Utility* repair() = 0;
    virtual Utility* mulfunction() = 0;
    int getWasteCollection();
    void recycle();
    void collect();

    int getWasteCollectionRaw() const { return wasteCollection; }

    void setWasteCollection(int value) { wasteCollection = value; }
};

class FunctionalWasteManagement : public WasteManagement
{
private:
public:
    FunctionalWasteManagement();
    ~FunctionalWasteManagement();
    Utility* repair() override; //does nothing in this class
    Utility* mulfunction() override;
};

class NonFunctionalWasteManagement : public WasteManagement
{
private:
public:
    NonFunctionalWasteManagement();
    ~NonFunctionalWasteManagement();
    Utility* repair() override; 
    Utility* mulfunction() override; //does nothing in this class
};



#endif