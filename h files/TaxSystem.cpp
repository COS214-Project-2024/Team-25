#include "TaxSystem.h"

#include <iostream>

using namespace std;

// void setTaxStrategy();
// void collectTax(CitySector* sector);
// void getCollectedTaxes();
// void addObserver();
// void notifyObservers();

/* -------------------------------- TaxSystem ------------------------------- */

TaxSystem::TaxSystem() {
    this->strategy = new FlatTaxStrategy();
    this->collectedTaxes = 0;
}

TaxSystem::~TaxSystem() { delete this->strategy; }

void TaxSystem::setTaxStrategy(TaxStrategy* strategy) {
    if (this->strategy) {
        delete this->strategy;
        this->strategy = strategy;
    } else {
        this->strategy = strategy;
    }
}

void TaxSystem::collectTax(CityGrowth* growth) {
    if (this->strategy) {
        int totalBuildings = growth->getTotalBuildingCount();
        float taxAmount = this->strategy->calculateTax(totalBuildings);
        this->collectedTaxes += taxAmount;

        std::cout << "R " << taxAmount << " tax collected.\n";
        std::cout << "R " << this->collectedTaxes
                  << " Total current collected taxes available\n";
    } else {
        std::cout << "No strategy is selected. No taxes collected.\n";
    }
}

float TaxSystem::getCollectedTaxes() {
    // Value to be returned
    float collectedAmount = this->collectedTaxes;

    this->collectedTaxes = 0;

    return collectedAmount;
}

/* ------------------------- ProgressiveTaxStrategy ------------------------- */

float ProgressiveTaxStrategy::calculateTax(int totalBuildings) {
    float totalTax = 0.0f;

    const float taxRateTier1 = 2000.0f;
    const float taxRateTier2 = 3000.0f;
    const float taxRateTier3 = 6000.0f;

    if (totalBuildings <= 10) {
        totalTax = totalBuildings * taxRateTier1;
    } else if (totalBuildings <= 20) {
        totalTax = (10 * taxRateTier1) + ((totalBuildings - 10) * taxRateTier2);
    } else {
        totalTax = (10 * taxRateTier1) + (10 * taxRateTier2) +
                   ((totalBuildings - 20) * taxRateTier3);
    }
    return totalTax;
}

/* ----------------------------- FlatTaxStrategy ---------------------------- */

float FlatTaxStrategy::calculateTax(int totalBuildings) {
    const float ratePerBuilding = 2000.0f;
    return totalBuildings * ratePerBuilding;
}