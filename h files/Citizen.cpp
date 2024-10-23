#include "citizen.h"
#include <iostream>


Citizen::Citizen() : name(""), age(0) {}


Worker::Worker() : occupation(""), salary(0.0) {
    name = "Default Worker";
    age = 25;
}

void Worker::displayInfo() {
    std::cout << "Worker Information:" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Occupation: " << occupation << std::endl;
    std::cout << "Salary: $" << salary << std::endl;
}

std::string Worker::getType() const {
    return "Worker";
}


GovernmentWorker::GovernmentWorker() 
    : department(""), securityClearance("None"), payGrade(0), salary(0.0) {
    name = "Default Gov Worker";
    age = 30;
}

void GovernmentWorker::displayInfo() {
    std::cout << "Government Worker Information:" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Department: " << department << std::endl;
    std::cout << "Security Clearance: " << securityClearance << std::endl;
    std::cout << "Pay Grade: GS-" << payGrade << std::endl;
    std::cout << "Salary: $" << salary << std::endl;
}

std::string GovernmentWorker::getType() const {
    return "Government Worker";
}


Retiree::Retiree() : yearsOfService(0), pension(0.0) {
    name = "Default Retiree";
    age = 65;
}

void Retiree::displayInfo() {
    std::cout << "Retiree Information:" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Years of Service: " << yearsOfService << std::endl;
    std::cout << "Pension: $" << pension << std::endl;
}

std::string Retiree::getType() const {
    return "Retiree";
}


CitizenFactory::CitizenFactory() {}

WorkerFactory::WorkerFactory() {}

Citizen* WorkerFactory::createCitizen() {
    return new Worker();
}

GovernmentWorkerFactory::GovernmentWorkerFactory() {}

Citizen* GovernmentWorkerFactory::createCitizen() {
    return new GovernmentWorker();
}

RetireeFactory::RetireeFactory() {}

Citizen* RetireeFactory::createCitizen() {
    return new Retiree();
}