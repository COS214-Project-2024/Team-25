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
    float efficiency; // percent of utility that is running
    Budget* budget;
    Concrete* concrete;
    Steel* steel;
    Wood* wood;
    bool isFunctional;

public:
    Utility();
    ~Utility();
    float getEfficiency() const { return efficiency; }
    void setEfficiency(float value) { efficiency = value; }
    bool getFunctional() const { return isFunctional; }
    void setFunctional(bool value) { isFunctional = value; }
};

class PowerPlant : public Utility {
protected:
    int powerGeneration; // in watts
    powerPlants type;
    Energy* energy;
    bool isInitialBuild = false;
public:
    PowerPlant(powerPlants type, bool isbuilt, int powerGen = 0);
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
    FunctionalPowerPlant(powerPlants type, bool built, int powerGen = 0);
    ~FunctionalPowerPlant();
    PowerPlant* repair() override; // Changed to PowerPlant*
    PowerPlant* mulfunction() override; // Changed to PowerPlant*
};

class NonFunctionalPowerPlant : public PowerPlant {
public:
    NonFunctionalPowerPlant(powerPlants type, bool built, int powerGen = 0);
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
    WaterSupply(bool built, int powerGen = 0);
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
    FunctionalWaterSupply(bool built, int powerGen = 0);
    ~FunctionalWaterSupply();
    WaterSupply* repair() override; // Changed to WaterSupply*
    WaterSupply* mulfunction() override; // Changed to WaterSupply*
};

class NonFunctionalWaterSupply : public WaterSupply {
public:
    NonFunctionalWaterSupply(bool built, int powerGen = 0);
    ~NonFunctionalWaterSupply();
    WaterSupply* repair() override; // Changed to WaterSupply*
    WaterSupply* mulfunction() override; // Changed to WaterSupply*
};

class WasteManagement : public Utility {
protected:
    int wasteCollection; // in kgs
    bool isInitialBuild = false;
public:
    WasteManagement(bool built, int powerGen = 0);
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
    FunctionalWasteManagement(bool built, int powerGen = 0);
    ~FunctionalWasteManagement();
    WasteManagement* repair() override; // Changed to WasteManagement*
    WasteManagement* mulfunction() override; // Changed to WasteManagement*
};

class NonFunctionalWasteManagement : public WasteManagement {
public:
    NonFunctionalWasteManagement(bool built, int powerGen = 0);
    ~NonFunctionalWasteManagement();
    WasteManagement* repair() override; // Changed to WasteManagement*
    WasteManagement* mulfunction() override; // Changed to WasteManagement*
};

#endif
