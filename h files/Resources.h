#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>

/**
 * @class Resources
 * @brief Abstract base class representing different types of resources.
 *
 * This class serves as the base for various resource types that the government can manage,
 * such as energy, water, and materials.
 */
class Resources {
public:
    /**
     * @brief Default constructor for Resources.
     */
    Resources();
};




/**
 * @class Energy
 * @brief Singleton class representing energy resources in the city.
 *
 * The Energy class manages different types of energy sources such as coal, hydro, wind, and solar.
 * It provides access to their wattage values and follows the Singleton design pattern to ensure
 * that only one instance of this class exists throughout the application.
 */
class Energy : public Resources {
private:
    /**
     * @brief Private constructor to prevent instantiation.
     *
     * This constructor is private to enforce the Singleton pattern, ensuring that
     * instances of this class can only be created internally.
     */
    Energy();

    static Energy* instance; ///< Static pointer to hold the single instance of the Energy class.

    int wattsCoal; ///< Amount of energy generated from coal (in watts).
    int wattsHydro; ///< Amount of energy generated from hydro (in watts).
    int wattsWind; ///< Amount of energy generated from wind (in watts).
    int wattsSolar; ///< Amount of energy generated from solar (in watts).
    int totalWatts; ///< Total energy generated (sum of all sources).

public:
    /**
     * @brief Gets the singleton instance of the Energy class.
     * @return A pointer to the singleton Energy instance.
     *
     * This method checks if an instance of the Energy class already exists; if not,
     * it creates one and returns it. This guarantees that there is only one instance
     * of Energy throughout the application.
     */
    static Energy* getInstance();

    // Deleted copy constructor and assignment operator to prevent copying.
    Energy(const Energy&) = delete;
    void operator=(const Energy&) = delete;

    // Getters
    /**
     * @brief Gets the amount of energy generated from coal.
     * @return The amount of energy from coal (in watts).
     */
    int getWattsCoal() const { return wattsCoal; }

    /**
     * @brief Gets the amount of energy generated from hydro.
     * @return The amount of energy from hydro (in watts).
     */
    int getWattsHydro() const { return wattsHydro; }

    /**
     * @brief Gets the amount of energy generated from wind.
     * @return The amount of energy from wind (in watts).
     */
    int getWattsWind() const { return wattsWind; }

    /**
     * @brief Gets the amount of energy generated from solar.
     * @return The amount of energy from solar (in watts).
     */
    int getWattsSolar() const { return wattsSolar; }

    /**
     * @brief Gets the total amount of energy generated.
     * @return The total energy generated (in watts).
     */
    int getTotalWatts() const { return totalWatts; }

    // Setters
    /**
     * @brief Sets the amount of energy generated from coal.
     * @param value The amount of energy to set (in watts).
     */
    void setWattsCoal(int value) { wattsCoal = value; }

    /**
     * @brief Sets the amount of energy generated from hydro.
     * @param value The amount of energy to set (in watts).
     */
    void setWattsHydro(int value) { wattsHydro = value; }

    /**
     * @brief Sets the amount of energy generated from wind.
     * @param value The amount of energy to set (in watts).
     */
    void setWattsWind(int value) { wattsWind = value; }

    /**
     * @brief Sets the amount of energy generated from solar.
     * @param value The amount of energy to set (in watts).
     */
    void setWattsSolar(int value) { wattsSolar = value; }

    /**
     * @brief Sets the total amount of energy generated.
     * @param value The total energy to set (in watts).
     */
    void setTotalWatts(int value) { totalWatts = value; }
};






/**
 * @class Water
 * @brief Singleton class representing water resources in the city.
 *
 * The Water class manages the water supply in the city, tracking the total amount
 * of water available in liters. It follows the Singleton design pattern to ensure
 * that only one instance of this class exists throughout the application.
 */
class Water : public Resources {
private:
    /**
     * @brief Private constructor to prevent instantiation.
     *
     * This constructor is private to enforce the Singleton pattern, ensuring that
     * instances of this class can only be created internally.
     */
    Water();

    static Water* instance; ///< Static pointer to hold the single instance of the Water class.

    int litres; ///< Total amount of water available (in liters).

public:
    /**
     * @brief Gets the singleton instance of the Water class.
     * @return A pointer to the singleton Water instance.
     *
     * This method checks if an instance of the Water class already exists; if not,
     * it creates one and returns it. This guarantees that there is only one instance
     * of Water throughout the application.
     */
    static Water* getInstance();

    // Deleted copy constructor and assignment operator to prevent copying.
    Water(const Water&) = delete;
    void operator=(const Water&) = delete;

    /**
     * @brief Gets the total amount of water available.
     * @return The total amount of water (in liters).
     */
    int getLiters() const { return litres; }

    /**
     * @brief Sets the total amount of water available.
     * @param value The amount of water to set (in liters).
     */
    void setliters(int value) { litres = value; }
};





/**
 * @class Budget
 * @brief Singleton class representing the financial budget of the city.
 *
 * The Budget class manages the city's financial resources, including cash and debt.
 * It follows the Singleton design pattern to ensure that only one instance of this class
 * exists throughout the application.
 */
class Budget : public Resources {
private:
    /**
     * @brief Private constructor to prevent instantiation.
     *
     * This constructor is private to enforce the Singleton pattern, ensuring that
     * instances of this class can only be created internally.
     */
    Budget();

    static Budget* instance; ///< Static pointer to hold the single instance of the Budget class.

    double cash; ///< The amount of cash available in the budget.
    double debt; ///< The total debt incurred by the city.

public:
    /**
     * @brief Gets the singleton instance of the Budget class.
     * @return A pointer to the singleton Budget instance.
     *
     * This method checks if an instance of the Budget class already exists; if not,
     * it creates one and returns it. This guarantees that there is only one instance
     * of Budget throughout the application.
     */
    static Budget* getInstance();

    // Deleted copy constructor and assignment operator to prevent copying.
    Budget(const Budget&) = delete;
    void operator=(const Budget&) = delete;

    /**
     * @brief Gets the current amount of cash in the budget.
     * @return The amount of cash available.
     */
    double getCash() const { return cash; }

    /**
     * @brief Gets the total amount of debt incurred by the city.
     * @return The total debt.
     */
    double getDebt() const { return debt; }

    /**
     * @brief Sets the amount of cash in the budget.
     * @param cash The amount of cash to set.
     *
     * If the new cash amount is negative, this method will automatically
     * set the debt to the absolute value of the cash amount.
     */
    void setCash(double cash) 
    {
        this->cash = cash;
        if (cash < 0) {
            setDebt(-cash);
        }
    }

    /**
     * @brief Sets the total amount of debt incurred by the city.
     * @param debt The amount of debt to set.
     */
    void setDebt(double debt) { this->debt = debt; }
};





/**
 * @class Materials
 * @brief Abstract base class representing materials used in resource management.
 *
 * The Materials class serves as an abstract base for different types of materials
 * that can be obtained and refined. It defines common functionality and properties
 * related to materials used within the city management system.
 */
class Materials : public Resources {
protected:
    int kilograms; ///< The quantity of materials in kilograms.

public:
    /**
     * @brief Default constructor for the Materials class.
     *
     * This constructor initializes the materials with default values.
     */
    Materials();

    /**
     * @brief Increases the quantity of materials.
     *
     * This method is responsible for calling the `obtain` and `refine` methods
     * to manage the material acquisition and refinement processes.
     */
    void increase(); // calls obtain and refine

    /**
     * @brief Abstract method to obtain materials.
     *
     * Derived classes must implement this method to define how materials are obtained.
     */
    virtual void obtain() = 0;

    /**
     * @brief Abstract method to refine materials.
     *
     * Derived classes must implement this method to define how materials are refined.
     */
    virtual void refine() = 0;

    /**
     * @brief Gets the quantity of materials in kilograms.
     * @return The amount of materials in kilograms.
     */
    int getKilo() const { return kilograms; }

    /**
     * @brief Sets the quantity of materials in kilograms.
     * @param k The quantity of materials to set in kilograms.
     */
    void setKilo(int k) { kilograms = k; }
};




// Derived classes from Materials

/*************************** Example implementation of the singleton **********************************/

// Concrete* Concrete::instance = nullptr;

// Concrete* Concrete::getInstance() {
//     if (instance == nullptr) {
//         instance = new Concrete();
//     }
//     return instance;
// }

/*************************** creating the singletons in the Government class **********************************/

// Energy* energy = Energy::getInstance();
// Water* water = Water::getInstance();
// Concrete* concrete = Concrete::getInstance();



/**
 * @class Concrete
 * @brief Singleton class representing concrete as a material resource.
 *
 * The Concrete class inherits from the Materials class and implements the singleton
 * design pattern to ensure that only one instance of concrete exists within the
 * resource management system. It provides methods to obtain and refine concrete.
 */
class Concrete : public Materials {
private:
    Concrete(); ///< Private constructor for the singleton pattern.
    static Concrete* instance; ///< Static instance pointer for the singleton.

public:
    /**
     * @brief Gets the instance of the Concrete class.
     * @return A pointer to the singleton instance of Concrete.
     */
    static Concrete* getInstance();

    // Delete copy constructor and assignment operator to prevent copies.
    Concrete(const Concrete&) = delete;
    void operator=(const Concrete&) = delete;

    /**
     * @brief Obtains concrete material.
     *
     * This method implements the logic for obtaining concrete.
     */
    void obtain() override;

    /**
     * @brief Refines concrete material.
     *
     * This method implements the logic for refining concrete.
     */
    void refine() override;   
};

/**
 * @class Steel
 * @brief Singleton class representing steel as a material resource.
 *
 * The Steel class inherits from the Materials class and implements the singleton
 * design pattern to ensure that only one instance of steel exists within the
 * resource management system. It provides methods to obtain and refine steel.
 */
class Steel : public Materials {
private:
    Steel(); ///< Private constructor for the singleton pattern.
    static Steel* instance; ///< Static instance pointer for the singleton.

public:
    /**
     * @brief Gets the instance of the Steel class.
     * @return A pointer to the singleton instance of Steel.
     */
    static Steel* getInstance();

    // Delete copy constructor and assignment operator to prevent copies.
    Steel(const Steel&) = delete;
    void operator=(const Steel&) = delete;

    /**
     * @brief Obtains steel material.
     *
     * This method implements the logic for obtaining steel.
     */
    void obtain() override;

    /**
     * @brief Refines steel material.
     *
     * This method implements the logic for refining steel.
     */
    void refine() override;  
};





/**
 * @class Wood
 * @brief Singleton class representing wood as a material resource.
 *
 * The Wood class inherits from the Materials class and implements the singleton
 * design pattern to ensure that only one instance of wood exists within the
 * resource management system. It provides methods to obtain and refine wood.
 */
class Wood : public Materials {
private:
    Wood(); ///< Private constructor for the singleton pattern.
    static Wood* instance; ///< Static instance pointer for the singleton.

public:
    /**
     * @brief Gets the instance of the Wood class.
     * @return A pointer to the singleton instance of Wood.
     */
    static Wood* getInstance();

    // Delete copy constructor and assignment operator to prevent copies.
    Wood(const Wood&) = delete;
    void operator=(const Wood&) = delete;

    /**
     * @brief Obtains wood material.
     *
     * This method implements the logic for obtaining wood.
     */
    void obtain() override;

    /**
     * @brief Refines wood material.
     *
     * This method implements the logic for refining wood.
     */
    void refine() override;  
};


#endif