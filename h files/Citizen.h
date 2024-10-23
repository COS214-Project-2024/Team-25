#ifndef CITIZEN_H
#define CITIZEN_H

#include <string>

// Abstract Product
class Citizen {
public:
    Citizen();
    virtual ~Citizen() = default;
    virtual void displayInfo() = 0;
    virtual std::string getType() const = 0;
protected:
    std::string name;
    int age;
    int satisfaction;
};

// Concrete Products
class Worker : public Citizen {
public:
    Worker();
    void displayInfo() override;
    std::string getType() const override;
private:
    std::string occupation;
    double salary;
};

class GovernmentWorker : public Citizen {
public:
    GovernmentWorker();
    void displayInfo() override;
    std::string getType() const override;
private:
    std::string department;
    std::string securityClearance;
    int payGrade;
    double salary;
};

class Retiree : public Citizen {
public:
    Retiree();
    void displayInfo() override;
    std::string getType() const override;
private:
    int yearsOfService;
    double pension;
};

// Abstract Creator
class CitizenFactory {
public:
    CitizenFactory();
    virtual ~CitizenFactory() = default;
    virtual Citizen* createCitizen() = 0;
};

// Concrete Creators
class WorkerFactory : public CitizenFactory {
public:
    WorkerFactory();
    Citizen* createCitizen() override;
};

class GovernmentWorkerFactory : public CitizenFactory {
public:
    GovernmentWorkerFactory();
    Citizen* createCitizen() override;
};

class RetireeFactory : public CitizenFactory {
public:
    RetireeFactory();
    Citizen* createCitizen() override;
};

#endif