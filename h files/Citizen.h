#ifndef CITIZEN_H
#define CITIZEN_H

#include <string>
using namespace std;

// Abstract Product
class Citizen {
    private:
        string residence;
        string workplace;
        string type;
        float satisfaction;
    public:
        Citizen();
        virtual ~Citizen() = default;
        virtual void setCitizen(string type, string residence, string workplace);
        virtual std::string getType();
        //void update();
        virtual string getResidence();
        virtual string getWorkplace();
        virtual float getSatisfaction();
        virtual void displayInfo() = 0;
        void changeSatisfaction(int amt);
};

// Concrete Products
class CommercialWorker : public Citizen {
public:
    CommercialWorker();
    CommercialWorker(string workplace);
    virtual void displayInfo();
};

class GovernmentWorker : public Citizen {
public:
    GovernmentWorker();
    GovernmentWorker(string workplace);
    virtual void displayInfo();
};

class IndustrialWorker : public Citizen {
public:
    IndustrialWorker();
    IndustrialWorker(string workplace);
    virtual void displayInfo();
};

// Abstract Creator
class CitizenFactory {
private: 
    Citizen* citizen;
public:
   // CitizenFactory();
    virtual ~CitizenFactory() = default;
    virtual Citizen* createCitizen() = 0;
    virtual Citizen* createCitizen(string workplace) = 0;
};

// Concrete Creators
class ComWorkerFactory : public CitizenFactory {
public:
    Citizen* createCitizen() override;
    Citizen* createCitizen(string workplace);
};

class GovernmentWorkerFactory : public CitizenFactory {
public:
    Citizen* createCitizen() override;
    Citizen* createCitizen(string workplace);
};

class IndWorkerFactory : public CitizenFactory {
public:
    Citizen* createCitizen() override;
    Citizen* createCitizen(string workplace);
};

#endif