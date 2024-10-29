#include "Citizen.h"
#include <iostream>


Citizen::Citizen() : residence(""), type(""), workplace(""), satisfaction(50.00){}//, age(0) {}

void Citizen:: setCitizen(string type, string building, string work){
    this->residence = building;
    this->workplace = work;
    this->type = type;
}

string Citizen:: getType(){
    return type;
}

string Citizen:: getResidence(){
    return residence;
}

string Citizen:: getWorkplace(){
    return workplace;
}

float Citizen:: getSatisfaction(){
    return satisfaction;
}

// Worker::Worker() : occupation(""), salary(0.0) {
//     name = "Default Worker";
//     age = 25;
// }

// void Worker::displayInfo() {
//     std::cout << "Worker Information:" << std::endl;
//     std::cout << "Name: " << name << std::endl;
//     std::cout << "Age: " << age << std::endl;
//     std::cout << "Occupation: " << occupation << std::endl;
//     std::cout << "Salary: $" << salary << std::endl;
// }

// std::string Worker::getType() const {
//     return "Worker";
// }



CommercialWorker:: CommercialWorker(): Citizen(){
    int operation = std::rand() % 3 + 1;
    string workplace;
   
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
CommercialWorker:: CommercialWorker(string workplace): Citizen(){
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
    string workplace;
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

GovernmentWorker::GovernmentWorker(string workplace) : Citizen(){
    this->setCitizen("Government worker","Mansion",workplace);
}

IndustrialWorker::IndustrialWorker():Citizen(){
    int operation = std::rand() % 3 + 1;
    string workplace;
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

IndustrialWorker::IndustrialWorker(string workplace):Citizen(){
    this->setCitizen("Industrial worker","Apartment",workplace);
}


// GovernmentWorker::GovernmentWorker() 
//     : department(""), securityClearance("None"), payGrade(0), salary(0.0) {
//     name = "Default Gov Worker";
//     age = 30;
// }

// void GovernmentWorker::displayInfo() {
//     std::cout << "Government Worker Information:" << std::endl;
//     std::cout << "Name: " << name << std::endl;
//     std::cout << "Age: " << age << std::endl;
//     std::cout << "Department: " << department << std::endl;
//     std::cout << "Security Clearance: " << securityClearance << std::endl;
//     std::cout << "Pay Grade: GS-" << payGrade << std::endl;
//     std::cout << "Salary: $" << salary << std::endl;
// }

// std::string GovernmentWorker::getType() const {
//     return "Government Worker";
// }


// Retiree::Retiree() : yearsOfService(0), pension(0.0) {
//     name = "Default Retiree";
//     age = 65;
// }

// void Retiree::displayInfo() {
//     std::cout << "Retiree Information:" << std::endl;
//     std::cout << "Name: " << name << std::endl;
//     std::cout << "Age: " << age << std::endl;
//     std::cout << "Years of Service: " << yearsOfService << std::endl;
//     std::cout << "Pension: $" << pension << std::endl;
// }

// std::string Retiree::getType() const {
//     return "Retiree";
// }


Citizen* ComWorkerFactory::createCitizen(string workplace) {
    return new CommercialWorker(workplace);
}

Citizen* GovernmentWorkerFactory::createCitizen(string workplace) {
    return new GovernmentWorker(workplace);
}

Citizen* IndWorkerFactory::createCitizen(string workplace) {
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