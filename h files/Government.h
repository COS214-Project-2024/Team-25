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
    RoadSystemAdapter* roadSystemAdapter;
    std::vector<WaterSupply*> waterSupply;
    std::vector<WasteManagement*> wasteManagement;
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
    void promptForNewHouse(int sector, Citizen* c);
    void promptForNewApartment(int sector, Citizen* c);
    void promptForNewMansion(int sector, Citizen* c);
public:
    Government();
    ~Government();
    
    //Actions
    void createBuilding();    //action 1
    void createUtility();     //action 2
    void increaseMaterials(); //action 2
    void naturalDisaster();   //action 3
    void upgradeTransport();  //action 4
    void cleanCity(); 	      //action 5
    void taxCitizens();       //action 6
    void changeTaxStartegy(); //action 7
    void repairUtilities();   
    void createCitizen(int numCitizens);

    float avgSatisfaction();
    void updateSatisfaction(float amt);
    void printSec() {std::cout << cityGrowth->printSectors() << std::endl;} 
    
    void setDifficulty(int difficulty);
    void printresources();

    void printUtilitiesDetails();

};  

#endif 