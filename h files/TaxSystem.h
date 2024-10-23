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
    void collectTax(CityGrowth* growth);
    float getCollectedTaxes();
    // void addObserver();
    // void notifyObservers();

   private:
    TaxStrategy* strategy;
    float collectedTaxes;
    // std::vector<Citizen*> observers;
};

class TaxStrategy {
   public:
    // TaxStrategy();
    // ~TaxStrategy();
    virtual float calculateTax(int totalBuildings) = 0;

   private:
};

class ProgressiveTaxStrategy : public TaxStrategy {
   public:
    // ProgressiveTaxStrategy();
    // ~ProgressiveTaxStrategy();
    virtual float calculateTax(int totalBuildings);

   private:
};

class FlatTaxStrategy : public TaxStrategy {
   public:
    // FlatTaxStrategy();
    // ~FlatTaxStrategy();
    virtual float calculateTax(int totalBuildings);

   private:
};

#endif  // TaxSystem_H