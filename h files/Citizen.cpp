#include "Citizen.h"
#include <iostream>


Citizen::Citizen() : residence(""), type(""), workplace(""), satisfaction(50.00){}//, age(0) {}

void Citizen:: setCitizen(std::string type, std::string building, std::string work){
    this->residence = building;
    this->workplace = work;
    this->type = type;
}

std::string Citizen:: getType(){
    return type;
}

std::string Citizen:: getResidence(){
    return residence;
}

std::string Citizen:: getWorkplace(){
    return workplace;
}

float Citizen:: getSatisfaction(){
    return satisfaction;
}

CommercialWorker:: CommercialWorker(): Citizen(){
    int operation = std::rand() % 3 + 1;
    std::string workplace;
   
    switch (operation) {
        case 1:
            workplace = "Shop";
            break;
        case 2:
            workplace = "Office";
            break;
        case 3:
            workplace = "Mall";
            break;
    }
    this->setCitizen("Commercial worker","House",workplace);
}
CommercialWorker:: CommercialWorker(std::string workplace): Citizen(){
    this->setCitizen("Commercial worker","House",workplace);
}

void CommercialWorker:: displayInfo(){
    std::cout << "---------------Worker Information:---------------" << std::endl;
    cout<<"Type of Citizen: \t"<<this->getType()<<endl;
    cout<<"Residence: \t"<<this->getResidence()<<endl;
    cout<<"Workplace: \t"<<this->getWorkplace()<<endl;
    cout<<"Satisfaction: \t"<<this->getSatisfaction()<<endl;
}

GovernmentWorker::GovernmentWorker() : Citizen(){
    int operation = std::rand() % 3 + 1;
    std::string workplace;
    // Perform the selected operation
    switch (operation) {
        case 1:
            workplace = "School";
            break;
        case 2:
            workplace = "Hospital";
            break;
        case 3:
            workplace = "Government";
            break;
    }
    this->setCitizen("Government worker","Mansion",workplace);
}

void GovernmentWorker::displayInfo(){
    std::cout << "---------------Worker Information:---------------" << std::endl;
    cout<<"Type of Citizen: \t"<<this->getType()<<endl;
    cout<<"Residence: \t"<<this->getResidence()<<endl;
    cout<<"Workplace: \t"<<this->getWorkplace()<<endl;
    cout<<"Satisfaction: \t"<<this->getSatisfaction()<<endl;
}

GovernmentWorker::GovernmentWorker(std::string workplace) : Citizen(){
    this->setCitizen("Government worker","Mansion",workplace);
}

IndustrialWorker::IndustrialWorker():Citizen(){
    int operation = std::rand() % 3 + 1;
    std::string workplace;
    // Perform the selected operation
    switch (operation) {
        case 1:
            workplace = "Warehouse";
            break;
        case 2:
            workplace = "Plant";
            break;
        case 3:
            workplace = "Factory";
            break;
    }
    this->setCitizen("Industrial worker","Apartment",workplace);
}

void IndustrialWorker::displayInfo(){
    std::cout << "---------------Worker Information:---------------" << std::endl;
    cout<<"Type of Citizen: \t"<<this->getType()<<endl;
    cout<<"Residence: \t"<<this->getResidence()<<endl;
    cout<<"Workplace: \t"<<this->getWorkplace()<<endl;
    cout<<"Satisfaction: \t"<<this->getSatisfaction()<<endl;
}

IndustrialWorker::IndustrialWorker(std::string workplace):Citizen(){
    this->setCitizen("Industrial worker","Apartment",workplace);
}


Citizen* ComWorkerFactory::createCitizen(std::string workplace) {
    return new CommercialWorker(workplace);
}

Citizen* GovernmentWorkerFactory::createCitizen(std::string workplace) {
    return new GovernmentWorker(workplace);
}

Citizen* IndWorkerFactory::createCitizen(std::string workplace) {
    return new IndustrialWorker(workplace);
}

Citizen* ComWorkerFactory::createCitizen() {
    return new CommercialWorker();
}

Citizen* GovernmentWorkerFactory::createCitizen() {
    return new GovernmentWorker();
}

Citizen* IndWorkerFactory::createCitizen() {
    return new IndustrialWorker();
}