#ifndef TaxSystem_H
#define TaxSystem_H

#include <iostream>

// #include "Citizen.h"
#include "CityGrowth.h"

class TaxStrategy;

class TaxSystem {
   public:
    TaxSystem();
    ~TaxSystem();
    void setTaxStrategy(TaxStrategy* strategy);
    void toggleStrategy();
    void collectTax(CityGrowth* growth);
    float getCollectedTaxes();
    std::string currentStrategy();
    // void addObserver();
    // void notifyObservers();

   private:
    TaxStrategy* strategy;
    float collectedTaxes;
    Budget* budget; 
    // std::vector<Citizen*> observers;
};

class TaxStrategy {
   public:
    // TaxStrategy();
    virtual ~TaxStrategy() = default;
    virtual float calculateTax(CityGrowth* growth) = 0;
    virtual std::string getStrategy() = 0;
   private:
};

class ProgressiveTaxStrategy : public TaxStrategy {
   public:
    // ProgressiveTaxStrategy();
    // ~ProgressiveTaxStrategy();
    virtual float calculateTax(CityGrowth* growth);
    virtual std::string getStrategy();

   private:
};

class FlatTaxStrategy : public TaxStrategy {
   public:
    // FlatTaxStrategy();
    // ~FlatTaxStrategy();
    virtual float calculateTax(CityGrowth* growth);
    virtual std::string getStrategy();

   private:
};

#endif  // TaxSystem_H