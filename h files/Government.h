#ifndef GOVERNMENT_H
#define GOVERNMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <random>

#include "Citizen.h"
#include "Resources.h"
#include "CityGrowth.h"
#include "TaxSystem.h"
// #include "Transportation.h"
#include "Utilities.h"
#include "Routines.h"
class Government{
private:
    std::vector<Citizen> citizens;
    Water* water;
    Budget* budget;
    Energy* energy;
    Wood* wood;
    Concrete* concrete;
    Steel* steel;
    CityGrowth* cityGrowth;
    TaxSystem* taxSystem;
    std::vector<PublicTransitAdapter*> publicTransitAdapter;
    std::vector<RoadSystemAdapter*> roadSystemAdapter;
    std::vector<RailSystemAdapter*> railSystemAdapter;
    std::vector<WaterSupply*> waterSupply;
    std::vector<WasteManagement*> wasteManagement;
    // std::vector<SewageSystems*> sewageSystems;
    std::vector<PowerPlant*> powerPlant;
    MonthlyRoutines* monthlyRoutines;
public:
    Government();
    virtual ~Government();
    
    //Actions
    void createBuilding(); //action 1
    void createUtility(); //action 2
    void increaseMaterials(); //action 8
    void naturalDisaster(); //action 3
    void upgradeTransport(); //action 4
    void upgradeBuildings(); //action 5
    void taxCitizens(); //action 6
    void changeTaxStartegy(); //action 7
    void repairUtilities();
    void createCitizen();

    // virtual void attach(Citizen Citizen);
    // virtual void detach(Citizen Citizen);
    // virtual void notifyBuilding(Citizen Citizen);
    // void callRoutines();
    // void repair(std::string name); //name of utility, also notifies citizens
    // void mulfunction(std::string name); //name of utility, also notifies citizens
    

    /*getters*/
    // std::vector<Citizen> getCitizens();
    // Water* getWater();
    // Budget* getBudget();
    // Energy* getEnergy();
    // Wood* getWood();
    // Concrete* getConcrete();
    // Steel* getSteel();
    // CitySector* getCitySector();
    // TaxSystem* getTaxSystem();
    // std::vector<PublicTransitAdapter*> getPublicTransitAdapter();
    // std::vector<RoadSystemAdapter*> getRoadSystemAdapter();
    // std::vector<RailSystemAdapter*> getRailSystemAdapter();
    // std::vector<WaterSupply*> getWaterSupply();
    // std::vector<WasteManagement*> getWasteManagement();
    // // std::vector<SewageSystems*> getSewageSystems();
    // std::vector<PowerPlant*> getPowerPlant();
    // std::vector<MonthlyRoutines*> getMonthlyRoutines();
};  

#endif 