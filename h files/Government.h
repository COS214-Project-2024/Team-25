#ifndef GOVERNMENT_H
#define GOVERNMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <random>
#include <iomanip>

#include "Citizen.h"
#include "Resources.h"
#include "CityGrowth.h"
#include "TaxSystem.h"
// #include "Transportation.h"
#include "Utilities.h"
#include "Routines.h"

/**
 * @class Government
 * @brief Represents the governing body responsible for managing the city.
 *
 * The Government class is responsible for overseeing the city's resources, citizens, utilities,
 * and various actions to enhance the city's growth and functionality. It manages the creation of 
 * buildings, utility services, taxation, and responses to natural disasters.
 */
class Government {
private:
    std::vector<Citizen> citizens; ///< List of citizens in the city.
    Water* water;                   ///< Pointer to the city's water resources.
    Budget* budget;                 ///< Pointer to the city's budget management.
    Energy* energy;                 ///< Pointer to the city's energy resources.
    Wood* wood;                     ///< Pointer to the city's wood resources.
    Concrete* concrete;             ///< Pointer to the city's concrete resources.
    Steel* steel;                   ///< Pointer to the city's steel resources.
    CityGrowth* cityGrowth;         ///< Pointer to the city's growth management.
    TaxSystem* taxSystem;           ///< Pointer to the city's taxation management.
    RoadSystemAdapter* roadSystemAdapter; ///< Pointer to the adapted road system for the city.
    std::vector<WaterSupply*> waterSupply; ///< Vector of water supply systems.
    std::vector<WasteManagement*> wasteManagement; ///< Vector of waste management systems.
    std::vector<PowerPlant*> powerPlant; ///< Vector of power plants in the city.
    MonthlyRoutines* monthlyRoutines; ///< Pointer to monthly routine management.

    // Function prototypes for prompting the creation of different building types.
    void promptForNewFactory(int sector);
    void promptForNewWarehouse(int sector);
    void promptForNewPlant(int sector);
    void promptForNewShop(int sector);
    void promptForNewOffice(int sector);
    void promptForNewMall(int sector);
    void promptForNewSchool(int sector);
    void promptForNewHospital(int sector);
    void promptForNewGovernmentBuilding(int sector);
    void promptForNewHouse(int sector, Citizen* c);
    void promptForNewApartment(int sector, Citizen* c);
    void promptForNewMansion(int sector, Citizen* c);

public:
    /**
     * @brief Default constructor for Government.
     */
    Government();

    /**
     * @brief Destructor for Government.
     */
    ~Government();

    // Actions that the government can perform.
    /**
     * @brief Initiates the process of creating a new building in the city.
     */
    void createBuilding();    // Action 1

    /**
     * @brief Initiates the process of creating a new utility service.
     */
    void createUtility();     // Action 2

    /**
     * @brief Increases the amount of available materials for construction.
     */
    void increaseMaterials(); // Action 2

    /**
     * @brief Responds to a natural disaster affecting the city.
     */
    void naturalDisaster();   // Action 3

    /**
     * @brief Upgrades the transportation infrastructure in the city.
     */
    void upgradeTransport();  // Action 4

    /**
     * @brief Cleans the city by managing waste and other factors.
     */
    void cleanCity();        // Action 5

    /**
     * @brief Taxes citizens to generate revenue for the city.
     */
    void taxCitizens();      // Action 6

    /**
     * @brief Changes the tax strategy employed by the government.
     */
    void changeTaxStartegy(); // Action 7

    /**
     * @brief Repairs utility services in the city.
     */
    void repairUtilities();

    /**
     * @brief Creates a specified number of citizens in the city.
     * @param numCitizens The number of citizens to be created.
     */
    void createCitizen(int numCitizens);

    /**
     * @brief Calculates and returns the average satisfaction of citizens.
     * @return The average satisfaction score of the citizens.
     */
    float avgSatisfaction();

    /**
     * @brief Updates the satisfaction level of citizens by a specified amount.
     * @param amt The amount to adjust the satisfaction level.
     */
    void updateSatisfaction(float amt);

    /**
     * @brief Updates the budget by a specified amount.
     * @param amt The amount to adjust the budget.
     */
    void updateBudget(double amt);

    /**
     * @brief Handles insufficient transportation resources in the city.
     */
    void insuffcientTransporrt();

    /**
     * @brief Sets the difficulty level for managing city operations.
     * @param difficulty The level of difficulty for city management tasks.
     */
    void setDifficulty(int difficulty);

    /**
     * @brief Prints the current resources available to the government.
     */
    void printresources();

    /**
     * @brief Prints details about the sectors in the city.
     */
    void printSec();

    /**
     * @brief Prints the satisfaction levels of citizens in the city.
     */
    void printSatisfaction();

    /**
     * @brief Prints details about the utility services in the city.
     */
    void printUtilitiesDetails();

    /**
     * @brief Gets the current budget available to the government.
     * @return The amount of cash in the budget.
     */
    float getBudget() { return budget->getCash(); }

    /**
     * @brief Gets the current debt of the government.
     * @return The amount of debt held by the government.
     */
    float getDebt() { return budget->getDebt(); }
};

#endif 
