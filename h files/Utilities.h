#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Resources.h"

/**
 * @enum powerPlants
 * @brief Enumeration for different types of power plants.
 */
enum powerPlants {
    HYDRO, ///< Hydro power plant
    COAL,  ///< Coal power plant
    WIND,  ///< Wind power plant
    SOLAR  ///< Solar power plant
};

/**
 * @class Utility
 * @brief Base class for all utility services.
 *
 * This class represents a utility service with attributes for efficiency,
 * budget, and functional status.
 */
class Utility {
protected:
    float efficiency; ///< Efficiency of the utility service (percentage). 
    Budget* budget; ///< Pointer to the budget for the utility.
    Concrete* concrete; ///< Pointer to concrete resources.
    Steel* steel; ///< Pointer to steel resources.
    Wood* wood; ///< Pointer to wood resources.
    bool isFunctional; ///< Indicates whether the utility is functional.

public:
    Utility(); ///< Constructor for Utility.
    ~Utility(); ///< Destructor for Utility.

    /**
     * @brief Gets the efficiency of the utility.
     * @return Efficiency as a float.
     */
    float getEfficiency() const { return efficiency; }

    /**
     * @brief Sets the efficiency of the utility.
     * @param value Efficiency value to set.
     */
    void setEfficiency(float value) { efficiency = value; }

    /**
     * @brief Checks if the utility is functional.
     * @return True if functional, false otherwise.
     */
    bool getFunctional() const { return isFunctional; }

    /**
     * @brief Sets the functional status of the utility.
     * @param value Functional status to set.
     */
    void setFunctional(bool value) { isFunctional = value; }
};




/**
 * @class PowerPlant
 * @brief Abstract class representing a power plant.
 *
 * This class includes attributes for power generation and type of power plant.
 */
class PowerPlant : public Utility {
protected:
    int powerGeneration; ///< Power generation capacity in watts.
    powerPlants type; ///< Type of power plant.
    Energy* energy; ///< Pointer to energy resources.
    bool isInitialBuild = false; ///< Indicates if it is an initial build.

public:
    /**
     * @brief Constructs a PowerPlant object.
     * @param type The type of power plant.
     * @param isbuilt Indicates if the power plant is built.
     * @param powerGen Initial power generation capacity.
     */
    PowerPlant(powerPlants type, bool isbuilt, int powerGen = 0);
    
    ~PowerPlant(); ///< Destructor for PowerPlant.

    /**
     * @brief Repairs the power plant.
     * @return Pointer to the repaired PowerPlant.
     */
    virtual PowerPlant* repair() = 0;   // Changed to PowerPlant*

    /**
     * @brief Indicates a malfunction in the power plant.
     * @return Pointer to the malfunctioning PowerPlant.
     */
    virtual PowerPlant* mulfunction() = 0;  // Changed to PowerPlant*

    /**
     * @brief Gets the effective power generation.
     * @return Effective power generation based on efficiency.
     */
    int getPowerGeneration();  // power gen * efficiency

    /**
     * @brief Gets the type of power plant.
     * @return The type of power plant.
     */
    powerPlants getType();

    /**
     * @brief Generates power.
     */
    void generate();

    /**
     * @brief Gets the raw power generation value.
     * @return The raw power generation capacity.
     */
    int getPowerGenerationRaw() const { return powerGeneration; }

    /**
     * @brief Gets the type of power plant.
     * @return The type of the power plant.
     */
    powerPlants getType() const { return type; }

    /**
     * @brief Sets the power generation capacity.
     * @param value Power generation value to set.
     */
    void setPowerGeneration(int value) { powerGeneration = value; }

    /**
     * @brief Sets the type of power plant.
     * @param value The type of power plant to set.
     */
    void setType(powerPlants value) { type = value; }
};

/**
 * @class FunctionalPowerPlant
 * @brief Class representing a functional power plant.
 */
class FunctionalPowerPlant : public PowerPlant 
{
public:
    /**
     * @brief Constructs a FunctionalPowerPlant object.
     * @param type The type of power plant.
     * @param built Indicates if the power plant is built.
     * @param powerGen Initial power generation capacity.
     */
    FunctionalPowerPlant(powerPlants type, bool built, int powerGen = 0);
    
    ~FunctionalPowerPlant(); ///< Destructor for FunctionalPowerPlant.

    /**
     * @brief Repairs the functional power plant.
     * @return Pointer to the repaired PowerPlant.
     */
    PowerPlant* repair() override;  // Changed to PowerPlant*

    /**
     * @brief Indicates a malfunction in the functional power plant.
     * @return Pointer to the malfunctioning PowerPlant.
     */
    PowerPlant* mulfunction() override;     // Changed to PowerPlant*
};

/**
 * @class NonFunctionalPowerPlant
 * @brief Class representing a non-functional power plant.
 */
class NonFunctionalPowerPlant : public PowerPlant {
public:
    /**
     * @brief Constructs a NonFunctionalPowerPlant object.
     * @param type The type of power plant.
     * @param built Indicates if the power plant is built.
     * @param powerGen Initial power generation capacity.
     */
    NonFunctionalPowerPlant(powerPlants type, bool built, int powerGen = 0);
    
    ~NonFunctionalPowerPlant(); ///< Destructor for NonFunctionalPowerPlant.

    /**
     * @brief Repairs the non-functional power plant.
     * @return Pointer to the repaired PowerPlant.
     */
    PowerPlant* repair() override;  // Changed to PowerPlant*

    /**
     * @brief Indicates a malfunction in the non-functional power plant.
     * @return Pointer to the malfunctioning PowerPlant.
     */
    PowerPlant* mulfunction() override;     // Changed to PowerPlant*
};

/**
 * @class WaterSupply
 * @brief Abstract class representing a water supply system.
 *
 * This class manages attributes related to water generation.
 */
class WaterSupply : public Utility {
protected:
    int waterGeneration; ///< Water generation capacity in liters.
    Water* water; ///< Pointer to water resources.
    bool isInitialBuild = false; ///< Indicates if it is an initial build.

public:
    /**
     * @brief Constructs a WaterSupply object.
     * @param built Indicates if the water supply system is built.
     * @param powerGen Initial water generation capacity.
     */
    WaterSupply(bool built, int powerGen = 0);
    
    ~WaterSupply(); ///< Destructor for WaterSupply.

    /**
     * @brief Repairs the water supply system.
     * @return Pointer to the repaired WaterSupply.
     */
    virtual WaterSupply* repair() = 0;  // Changed to WaterSupply*

    /**
     * @brief Indicates a malfunction in the water supply system.
     * @return Pointer to the malfunctioning WaterSupply.
     */
    virtual WaterSupply* mulfunction() = 0;     // Changed to WaterSupply*

    /**
     * @brief Gets the water generation capacity.
     * @return Water generation in liters.
     */
    int getWaterGeneration();

    /**
     * @brief Distributes water from the supply.
     */
    void distribute();

    /**
     * @brief Gets the raw water generation value.
     * @return The raw water generation capacity.
     */
    int getWaterGenerationRaw() const { return waterGeneration; }

    /**
     * @brief Sets the water generation capacity.
     * @param value Water generation value to set.
     */
    void setWaterGeneration(int value) { waterGeneration = value; }
};



/**
 * @class FunctionalWaterSupply
 * @brief Class representing a functional water supply system.
 */
class FunctionalWaterSupply : public WaterSupply {
public:
    /**
     * @brief Constructs a FunctionalWaterSupply object.
     * @param built Indicates if the water supply system is built.
     * @param powerGen Initial water generation capacity.
     */
    FunctionalWaterSupply(bool built, int powerGen = 0);
    
    ~FunctionalWaterSupply(); ///< Destructor for FunctionalWaterSupply.

    /**
     * @brief Repairs the functional water supply system.
     * @return Pointer to the repaired WaterSupply.
     */
    WaterSupply* repair() override;     // Changed to WaterSupply*

    /**
     * @brief Indicates a malfunction in the functional water supply system.
     * @return Pointer to the malfunctioning WaterSupply.
     */
    WaterSupply* mulfunction() override;    // Changed to WaterSupply*
};



/**
 * @class NonFunctionalWaterSupply
 * @brief Class representing a non-functional water supply system.
 */
class NonFunctionalWaterSupply : public WaterSupply {
public:
    /**
     * @brief Constructs a NonFunctionalWaterSupply object.
     * @param built Indicates if the water supply system is built.
     * @param powerGen Initial water generation capacity.
     */
    NonFunctionalWaterSupply(bool built, int powerGen = 0);
    
    ~NonFunctionalWaterSupply(); ///< Destructor for NonFunctionalWaterSupply.

    /**
     * @brief Repairs the non-functional water supply system.
     * @return Pointer to the repaired WaterSupply.
     */
    WaterSupply* repair() override;     // Changed to WaterSupply*

    /**
     * @brief Indicates a malfunction in the non-functional water supply system.
     * @return Pointer to the malfunctioning WaterSupply.
     */
    WaterSupply* mulfunction() override;    // Changed to WaterSupply*
};



/**
 * @class WasteManagement
 * @brief Abstract class representing a waste management system.
 *
 * This class manages attributes related to waste collection.
 */
class WasteManagement : public Utility {
protected:
    int wasteCollection; ///< Waste collection capacity in kilograms.
    bool isInitialBuild = false; ///< Indicates if it is an initial build.

public:
    /**
     * @brief Constructs a WasteManagement object.
     * @param built Indicates if the waste management system is built.
     * @param powerGen Initial waste collection capacity.
     */
    WasteManagement(bool built, int powerGen = 0);
    
    ~WasteManagement(); ///< Destructor for WasteManagement.

    /**
     * @brief Repairs the waste management system.
     * @return Pointer to the repaired WasteManagement.
     */
    virtual WasteManagement* repair() = 0;  // Changed to WasteManagement*

    /**
     * @brief Indicates a malfunction in the waste management system.
     * @return Pointer to the malfunctioning WasteManagement.
     */
    virtual WasteManagement* mulfunction() = 0;     // Changed to WasteManagement*

    /**
     * @brief Gets the waste collection capacity.
     * @return Waste collection in kilograms.
     */
    int getWasteCollection();

    /**
     * @brief Recycles the collected waste.
     */
    void recycle();

    /**
     * @brief Collects waste for management.
     */
    void collect();

    /**
     * @brief Gets the raw waste collection value.
     * @return The raw waste collection capacity.
     */
    int getWasteCollectionRaw() const { return wasteCollection; }

    /**
     * @brief Sets the waste collection capacity.
     * @param value Waste collection value to set.
     */
    void setWasteCollection(int value) { wasteCollection = value; }
};



/**
 * @class FunctionalWasteManagement
 * @brief Class representing a functional waste management system.
 */
class FunctionalWasteManagement : public WasteManagement {
public:
    /**
     * @brief Constructs a FunctionalWasteManagement object.
     * @param built Indicates if the waste management system is built.
     * @param powerGen Initial waste collection capacity.
     */
    FunctionalWasteManagement(bool built, int powerGen = 0);
    
    ~FunctionalWasteManagement(); ///< Destructor for FunctionalWasteManagement.

    /**
     * @brief Repairs the functional waste management system.
     * @return Pointer to the repaired WasteManagement.
     */
    WasteManagement* repair() override;     // Changed to WasteManagement*

    /**
     * @brief Indicates a malfunction in the functional waste management system.
     * @return Pointer to the malfunctioning WasteManagement.
     */
    WasteManagement* mulfunction() override;    // Changed to WasteManagement*
};



/**
 * @class NonFunctionalWasteManagement
 * @brief Class representing a non-functional waste management system.
 */
class NonFunctionalWasteManagement : public WasteManagement {
public:
    /**
     * @brief Constructs a NonFunctionalWasteManagement object.
     * @param built Indicates if the waste management system is built.
     * @param powerGen Initial waste collection capacity.
     */
    NonFunctionalWasteManagement(bool built, int powerGen = 0);
    
    ~NonFunctionalWasteManagement(); ///< Destructor for NonFunctionalWasteManagement.

    /**
     * @brief Repairs the non-functional waste management system.
     * @return Pointer to the repaired WasteManagement.
     */
    WasteManagement* repair() override;     // Changed to WasteManagement*

    /**
     * @brief Indicates a malfunction in the non-functional waste management system.
     * @return Pointer to the malfunctioning WasteManagement.
     */
    WasteManagement* mulfunction() override;    // Changed to WasteManagement*
};

#endif
