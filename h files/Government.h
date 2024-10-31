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
#include "Transportation.h"
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
    RoadSystem* roadSystem;
    std::vector<PublicTransitAdapter*> publicTransitAdapter;
    std::vector<RoadSystemAdapter*> roadSystemAdapter;
    std::vector<RailSystemAdapter*> railSystemAdapter;
    std::vector<WaterSupply*> waterSupply;
    std::vector<WasteManagement*> wasteManagement;
    // std::vector<SewageSystems*> sewageSystems;
    std::vector<PowerPlant*> powerPlant;
    MonthlyRoutines* monthlyRoutines;


      // Function prototypes
    void promptForNewFactory(int sector);
    void promptForNewWarehouse(int sector);
    void promptForNewPlant(int sector);
    void promptForNewShop(int sector);
    void promptForNewOffice(int sector);
    void promptForNewMall(int sector);
    void promptForNewSchool(int sector);
    void promptForNewHospital(int sector);
    void promptForNewGovernmentBuilding(int sector);
    void promptForNewHouse(int sector);
    void promptForNewApartment(int sector);
    void promptForNewMansion(int sector);
public:
    Government();
    ~Government();
    
    //Actions
    void createBuilding(); //action 1
    void createUtility(); //action 2
    void increaseMaterials(); //action 2 as well
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
    void callRoutines();
    void repair(std::string name); //name of utility, also notifies citizens
    void mulfunction(std::string name); //name of utility, also notifies citizens
    

};  

#endif 