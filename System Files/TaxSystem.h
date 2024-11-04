#ifndef TaxSystem_H
#define TaxSystem_H

#include <iostream>

// #include "Citizen.h"
#include "CityGrowth.h"

class TaxStrategy;

/**
 * @class TaxSystem
 * @brief Manages the tax collection system for the city.
 *
 * The TaxSystem class is responsible for setting the tax strategy, collecting taxes, 
 * and keeping track of the total taxes collected. It allows for toggling between different tax strategies.
 */
class TaxSystem {
   public:
    /**
     * @brief Constructs a TaxSystem object.
     */
    TaxSystem();

    /**
     * @brief Destroys the TaxSystem object.
     */
    ~TaxSystem();

    /**
     * @brief Sets the current tax strategy.
     * @param strategy Pointer to a TaxStrategy object to be set as the current strategy.
     */
    void setTaxStrategy(TaxStrategy* strategy);

    /**
     * @brief Toggles the current tax strategy between available strategies.
     */
    void toggleStrategy();

    /**
     * @brief Collects taxes based on the current tax strategy.
     * @param growth Pointer to a CityGrowth object used to gather relevant data for tax calculation.
     */
    void collectTax(CityGrowth* growth);

    /**
     * @brief Gets the total taxes collected.
     * @return The total amount of taxes collected.
     */
    float getCollectedTaxes();

    /**
     * @brief Retrieves the name of the current tax strategy.
     * @return A string representing the current tax strategy.
     */
    std::string currentStrategy();
    // void addObserver();
    // void notifyObservers();

   private:
    TaxStrategy* strategy; ///< Pointer to the current tax strategy.
    float collectedTaxes;   ///< Total amount of taxes collected.
    Budget* budget;         ///< Pointer to the budget associated with the city.
    // std::vector<Citizen*> observers;
};



/**
 * @class TaxStrategy
 * @brief Abstract base class for tax strategies.
 *
 * This class defines the interface for different tax strategies that can be implemented.
 * Each strategy will have its own method of calculating taxes.
 */
class TaxStrategy {
   public:
   // TaxStrategy();
    /**
     * @brief Destroys the TaxStrategy object.
     */
    virtual ~TaxStrategy() = default;

    /**
     * @brief Calculates the tax based on the implemented strategy.
     * @param growth Pointer to a CityGrowth object used to gather relevant data for tax calculation.
     * @return The calculated tax amount.
     */
    virtual float calculateTax(CityGrowth* growth) = 0;

    /**
     * @brief Gets the name of the tax strategy.
     * @return A string representing the name of the strategy.
     */
    virtual std::string getStrategy() = 0;
};



/**
 * @class ProgressiveTaxStrategy
 * @brief Concrete implementation of a progressive tax strategy.
 *
 * This class calculates taxes based on a progressive rate structure, where higher incomes are taxed at higher rates.
 */
class ProgressiveTaxStrategy : public TaxStrategy {
   public:
   // ProgressiveTaxStrategy();
   // ~ProgressiveTaxStrategy();
    /**
     * @brief Calculates the tax based on the progressive tax rate.
     * @param growth Pointer to a CityGrowth object used to gather relevant data for tax calculation.
     * @return The calculated tax amount using the progressive tax strategy.
     */
    virtual float calculateTax(CityGrowth* growth);

    /**
     * @brief Gets the name of the progressive tax strategy.
     * @return A string representing the name of the progressive tax strategy.
     */
    virtual std::string getStrategy();
};



/**
 * @class FlatTaxStrategy
 * @brief Concrete implementation of a flat tax strategy.
 *
 * This class calculates taxes using a flat rate, where all incomes are taxed at the same percentage.
 */
class FlatTaxStrategy : public TaxStrategy {
   public:
   // FlatTaxStrategy();
   // ~FlatTaxStrategy();

    /**
     * @brief Calculates the tax based on the flat tax rate.
     * @param growth Pointer to a CityGrowth object used to gather relevant data for tax calculation.
     * @return The calculated tax amount using the flat tax strategy.
     */
    virtual float calculateTax(CityGrowth* growth);

    /**
     * @brief Gets the name of the flat tax strategy.
     * @return A string representing the name of the flat tax strategy.
     */
    virtual std::string getStrategy();
};

#endif  // TaxSystem_H
