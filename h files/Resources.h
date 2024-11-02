#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>

class Resources {
public:
    Resources();
};

class Energy : public Resources {
private:
    Energy();
    static Energy* instance;
    int wattsCoal;
    int wattsHydro;
    int wattsWind;
    int wattsSolar;
    int totalWatts;

public:
    static Energy* getInstance();
    Energy(const Energy&) = delete;
    void operator=(const Energy&) = delete;
    // Getters
    int getWattsCoal() const { return wattsCoal; }
    int getWattsHydro() const { return wattsHydro; }
    int getWattsWind() const { return wattsWind; }
    int getWattsSolar() const { return wattsSolar; }
    int getTotalWatts() const { return totalWatts; }

    // Setters
    void setWattsCoal(int value) { wattsCoal = value; }
    void setWattsHydro(int value) { wattsHydro = value; }
    void setWattsWind(int value) { wattsWind = value; }
    void setWattsSolar(int value) { wattsSolar = value; }
    void setTotalWatts(int value) { totalWatts = value; }
};

class Water : public Resources {
private:
    Water();
    static Water* instance;
    int litres; //in litres

public:
    static Water* getInstance();
    Water(const Water&) = delete;
    void operator=(const Water&) = delete;
    int getLiters() const { return litres; }
    void setliters(int value) { litres = value; }
};

class Budget : public Resources {
private:
    Budget();
    static Budget* instance;
    double cash;
    double debt;
public:
    static Budget* getInstance();
    Budget(const Budget&) = delete;
    void operator=(const Budget&) = delete;

    double getCash() const {return cash;}
    double getDebt() const {return debt;}

    void setCash(double cash) 
    {
        this->cash = cash;
        if(cash < 0){
            setDebt(-cash);
        }
    } 
    void setDebt(double debt) {this->debt = debt;} 
};

class Materials : public Resources {
protected:
    int kilograms;
public:
    Materials();
    void increase(); // calls obtain and refine
    virtual void obtain() = 0;
    virtual void refine() = 0; 
    int getKilo() const {return kilograms;}
    void setKilo(int k) {kilograms = k;}
};

// Derived classes from Materials

/*************************** Example implementation of the singleton **********************************/

// Concrete* Concrete::instance = nullptr;

// Concrete* Concrete::getInstance() {
//     if (instance == nullptr) {
//         instance = new Concrete();
//     }
//     return instance;
// }

/*************************** creating the singletons in the Government class **********************************/

// Energy* energy = Energy::getInstance();
// Water* water = Water::getInstance();
// Concrete* concrete = Concrete::getInstance();

class Concrete : public Materials {
private:
    Concrete();
    static Concrete* instance;

public:
    static Concrete* getInstance();
    Concrete(const Concrete&) = delete;
    void operator=(const Concrete&) = delete;
    void obtain() override;
    void refine() override;   
};

class Steel : public Materials {
private:
    Steel();
    static Steel* instance;

public:
    static Steel* getInstance();
    Steel(const Steel&) = delete;
    void operator=(const Steel&) = delete;
    void obtain() override;
    void refine() override;  
};

class Wood : public Materials {
private:
    Wood();
    static Wood* instance;

public:
    static Wood* getInstance();
    Wood(const Wood&) = delete;
    void operator=(const Wood&) = delete;
    void obtain() override;
    void refine() override;  
};

#endif