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
    budget = Budget::getInstance();
}

// TaxSystem::~TaxSystem() { delete this->strategy; }
TaxSystem::~TaxSystem() 
{
    delete strategy;
}

void TaxSystem::setTaxStrategy(TaxStrategy* strategy) {
    if (this->strategy) {
        delete this->strategy;
        this->strategy = strategy;
    } else {
        this->strategy = strategy;
    }
}

void TaxSystem::toggleStrategy() {
    if(this->strategy) {
        // current Strategy is FlatTaxStrategy
        if(this->strategy->getStrategy() == "FlatTaxStrategy") {
            delete this->strategy;
            this->strategy = new ProgressiveTaxStrategy();

            std::cout << "Strategy changed from FlatTaxStrategy to ProgressiveTaxStrategy\n"; 

        } else { // current Strategy is ProgressiveTaxStrategy
            delete this->strategy;
            this->strategy = new FlatTaxStrategy();

            std::cout << "Strategy changed from ProgressiveTaxStrategy to FlatTaxStrategy\n"; 

        }
    }
    else {
        this->strategy = new FlatTaxStrategy();
            std::cout << "Strategy changed from none to FlatTaxStrategy\n"; 

    }
}

void TaxSystem::collectTax(CityGrowth* growth) {
    if (this->strategy) {
        int totalBuildings = growth->getTotalBuildingCount();
        float taxAmount = this->strategy->calculateTax(growth);
        this->collectedTaxes += taxAmount;
        budget->setCash(budget->getCash() + taxAmount);
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

std::string TaxSystem::currentStrategy() {
    return this->strategy->getStrategy();
}


/* ------------------------- ProgressiveTaxStrategy ------------------------- */

float ProgressiveTaxStrategy::calculateTax(CityGrowth* growth) {
    float totalTax = 0.0f;

    int governmentCitizens = 0;
    int industrialCitizens = 0;
    int commercialCitizens = 0;

    const float govTaxRateTier1 = 500.0f;
    const float indTaxRateTier1 = 1000.0f;
    const float comTaxRateTier1 = 1500.0f;

    const float govTaxRateTier2 = 700.0f;
    const float indTaxRateTier2 = 1500.0f;
    const float comTaxRateTier2 = 2000.0f;

    const float govTaxRateTier3 = 1000.0f;
    const float indTaxRateTier3 = 2000.0f;
    const float comTaxRateTier3 = 3000.0f;

    for( const auto& SectorOP : growth->getSectors()) {
        // Building* building = SectorOP->block[0];
        for( const auto& BuildingOP : SectorOP->getBlock()) {

            // Calculate PopulationCapacity and CurrentPopulation
            if(BuildingOP->getBuildingType() == "House") {
                if (House* house = dynamic_cast<House*>(BuildingOP)) {
                    std::vector<Citizen*> citizens = house->getCitizens();

                    for (const auto& citizensOP : citizens) {
                        if(citizensOP->getType() == "Government worker") {
                            governmentCitizens++;
                        } else if(citizensOP->getType() == "Industrial worker") {
                            industrialCitizens++;
                        } else if(citizensOP->getType() == "Commercial worker") {
                            commercialCitizens++;
                        }
                    }
                }
            } else if(BuildingOP->getBuildingType() == "Apartment") {
                if (Apartment* apartment = dynamic_cast<Apartment*>(BuildingOP)) {
                    std::vector<Citizen*> citizens = apartment->getCitizens();

                    for (const auto& citizensOP : citizens) {
                        if(citizensOP->getType() == "Government worker") {
                            governmentCitizens++;
                        } else if(citizensOP->getType() == "Industrial worker") {
                            industrialCitizens++;
                        } else if(citizensOP->getType() == "Commercial worker") {
                            commercialCitizens++;
                        }
                    }

                }
            } else if(BuildingOP->getBuildingType() == "Mansion") {
                if (Mansion* mansion = dynamic_cast<Mansion*>(BuildingOP)) {
                    std::vector<Citizen*> citizens = mansion->getCitizens();
                    
                    for (const auto& citizensOP : citizens) {
                        if(citizensOP->getType() == "Government worker") {
                            governmentCitizens++;
                        } else if(citizensOP->getType() == "Industrial worker") {
                            industrialCitizens++;
                        } else if(citizensOP->getType() == "Commercial worker") {
                            commercialCitizens++;
                        }
                    }
                }
            }
        }
    }




    int totalCitizens = governmentCitizens + industrialCitizens + commercialCitizens;
    if (totalCitizens <= 10) {
        totalTax = (governmentCitizens * govTaxRateTier1) +
                   (industrialCitizens * indTaxRateTier1) +
                   (commercialCitizens * comTaxRateTier1);
    } else if (totalCitizens <= 20) {
        totalTax = (10 * (govTaxRateTier1 + indTaxRateTier1 + comTaxRateTier1)) +
                   ((governmentCitizens - 10) * govTaxRateTier2) +
                   ((industrialCitizens - 10) * indTaxRateTier2) +
                   ((commercialCitizens - 10) * comTaxRateTier2);
    } else {
        totalTax = (10 * (govTaxRateTier1 + indTaxRateTier1 + comTaxRateTier1)) +
                   (10 * (govTaxRateTier2 + indTaxRateTier2 + comTaxRateTier2)) +
                   ((governmentCitizens - 20) * govTaxRateTier3) +
                   ((industrialCitizens - 20) * indTaxRateTier3) +
                   ((commercialCitizens - 20) * comTaxRateTier3);
    }
    return totalTax;
}

std::string ProgressiveTaxStrategy::getStrategy() {
    return "ProgressiveTaxStrategy";
}

/* ----------------------------- FlatTaxStrategy ---------------------------- */

float FlatTaxStrategy::calculateTax(CityGrowth* growth) {
    int governmentCitizens = 0;
    int industrialCitizens = 0;
    int commercialCitizens = 0;

    const float govTaxRate = 500.0f;
    const float indTaxRate = 1000.0f;
    const float comTaxRate = 1500.0f;

    for( const auto& SectorOP : growth->getSectors()) {
        // Building* building = SectorOP->block[0];
        for( const auto& BuildingOP : SectorOP->getBlock()) {

            // Calculate PopulationCapacity and CurrentPopulation
            if(BuildingOP->getBuildingType() == "House") {
                if (House* house = dynamic_cast<House*>(BuildingOP)) {
                    std::vector<Citizen*> citizens = house->getCitizens();

                    for (const auto& citizensOP : citizens) {
                        if(citizensOP->getType() == "Government worker") {
                            governmentCitizens++;
                        } else if(citizensOP->getType() == "Industrial worker") {
                            industrialCitizens++;
                        } else if(citizensOP->getType() == "Commercial worker") {
                            commercialCitizens++;
                        }
                    }
                }
            } else if(BuildingOP->getBuildingType() == "Apartment") {
                if (Apartment* apartment = dynamic_cast<Apartment*>(BuildingOP)) {
                    std::vector<Citizen*> citizens = apartment->getCitizens();

                    for (const auto& citizensOP : citizens) {
                        if(citizensOP->getType() == "Government worker") {
                            governmentCitizens++;
                        } else if(citizensOP->getType() == "Industrial worker") {
                            industrialCitizens++;
                        } else if(citizensOP->getType() == "Commercial worker") {
                            commercialCitizens++;
                        }
                    }

                }
            } else if(BuildingOP->getBuildingType() == "Mansion") {
                if (Mansion* mansion = dynamic_cast<Mansion*>(BuildingOP)) {
                    std::vector<Citizen*> citizens = mansion->getCitizens();
                    
                    for (const auto& citizensOP : citizens) {
                        if(citizensOP->getType() == "Government worker") {
                            governmentCitizens++;
                        } else if(citizensOP->getType() == "Industrial worker") {
                            industrialCitizens++;
                        } else if(citizensOP->getType() == "Commercial worker") {
                            commercialCitizens++;
                        }
                    }
                }
            }
        }
    }

    float totalTax = (governmentCitizens * govTaxRate) +
                     (industrialCitizens * indTaxRate) +
                     (commercialCitizens * comTaxRate);

    return totalTax;
}

std::string FlatTaxStrategy::getStrategy() {
    return "FlatTaxStrategy";
}