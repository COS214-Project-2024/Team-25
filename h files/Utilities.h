#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Resources.h"

enum powerPlants {
    HYDRO, COAL, WIND, SOLAR
};

class Utility {
protected:
    std::string name;
    float efficiency; // percent of utility that is running
    Budget* budget;
    Concrete* concrete;
    Steel* steel;
    Wood* wood;
    bool isFunctional;

public:
    Utility();
    ~Utility();

    std::string getName() const { return name; }
    float getEfficiency() const { return efficiency; }

    void setName(const std::string& value) { name = value; }
    void setEfficiency(float value) { efficiency = value; }

    bool getFunctional() const { return isFunctional; }
};

class PowerPlant : public Utility {
protected:
    int powerGeneration; // in watts
    powerPlants type;
    Energy* energy;
    bool isInitialBuild = false;
public:
    PowerPlant(powerPlants type, bool isbuilt);
    ~PowerPlant();
    virtual PowerPlant* repair() = 0; // Changed to PowerPlant*
    virtual PowerPlant* mulfunction() = 0; // Changed to PowerPlant*
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
public:
    FunctionalPowerPlant(powerPlants type);
    ~FunctionalPowerPlant();
    PowerPlant* repair() override; // Changed to PowerPlant*
    PowerPlant* mulfunction() override; // Changed to PowerPlant*
};

class NonFunctionalPowerPlant : public PowerPlant {
public:
    NonFunctionalPowerPlant(powerPlants type);
    ~NonFunctionalPowerPlant();
    PowerPlant* repair() override; // Changed to PowerPlant*
    PowerPlant* mulfunction() override; // Changed to PowerPlant*
};

class WaterSupply : public Utility {
protected:
    int waterGeneration; // in liters
    Water* water;
    bool isInitialBuild = false;
public:
    WaterSupply(bool built);
    ~WaterSupply();
    virtual WaterSupply* repair() = 0; // Changed to WaterSupply*
    virtual WaterSupply* mulfunction() = 0; // Changed to WaterSupply*
    int getWaterGeneration();
    void distribute();

    int getWaterGenerationRaw() const { return waterGeneration; }
    void setWaterGeneration(int value) { waterGeneration = value; }
};

class FunctionalWaterSupply : public WaterSupply {
public:
    FunctionalWaterSupply();
    ~FunctionalWaterSupply();
    WaterSupply* repair() override; // Changed to WaterSupply*
    WaterSupply* mulfunction() override; // Changed to WaterSupply*
};

class NonFunctionalWaterSupply : public WaterSupply {
public:
    NonFunctionalWaterSupply();
    ~NonFunctionalWaterSupply();
    WaterSupply* repair() override; // Changed to WaterSupply*
    WaterSupply* mulfunction() override; // Changed to WaterSupply*
};

class WasteManagement : public Utility {
protected:
    int wasteCollection; // in kgs
    bool isInitialBuild = false;
public:
    WasteManagement(bool built);
    ~WasteManagement();
    virtual WasteManagement* repair() = 0; // Changed to WasteManagement*
    virtual WasteManagement* mulfunction() = 0; // Changed to WasteManagement*
    int getWasteCollection();
    void recycle();
    void collect();

    int getWasteCollectionRaw() const { return wasteCollection; }

    void setWasteCollection(int value) { wasteCollection = value; }
};

class FunctionalWasteManagement : public WasteManagement {
public:
    FunctionalWasteManagement();
    ~FunctionalWasteManagement();
    WasteManagement* repair() override; // Changed to WasteManagement*
    WasteManagement* mulfunction() override; // Changed to WasteManagement*
};

class NonFunctionalWasteManagement : public WasteManagement {
public:
    NonFunctionalWasteManagement();
    ~NonFunctionalWasteManagement();
    WasteManagement* repair() override; // Changed to WasteManagement*
    WasteManagement* mulfunction() override; // Changed to WasteManagement*
};

#endif
