#include "Resources.h"

Resources::Resources() {}


Energy* Energy::instance = nullptr;

Energy::Energy() : wattsCoal(0), wattsHydro(0), wattsWind(0), wattsSolar(0), totalWatts(0) {}

Energy* Energy::getInstance() {
    if (instance == nullptr) {
        instance = new Energy();
    }
    return instance;
}


Water* Water::instance = nullptr;

Water::Water() : litres(0) {}

Water* Water::getInstance() {
    if (instance == nullptr) {
        instance = new Water();
    }
    return instance;
}


Budget* Budget::instance = nullptr;

Budget::Budget() : cash(0.0), debt(0.0) {}

Budget* Budget::getInstance() {
    if (instance == nullptr) {
        instance = new Budget();
    }
    return instance;
}


Materials::Materials() : kilograms(0) {}

void Materials::increase() {
    obtain();
    refine();
}


Concrete* Concrete::instance = nullptr;

Concrete::Concrete() {}

Concrete* Concrete::getInstance() {
    if (instance == nullptr) {
        instance = new Concrete();
    }
    return instance;
}

void Concrete::obtain() {
    kilograms += 10000;
    std::cout << "Concrete obtained: 10000 kg" << std::endl;
}

void Concrete::refine() {
    
    
    kilograms *= 0.9;  
    std::cout << "Concrete refined: " << kilograms << " kg" << std::endl;
}


Steel* Steel::instance = nullptr;

Steel::Steel() {}

Steel* Steel::getInstance() {
    if (instance == nullptr) {
        instance = new Steel();
    }
    return instance;
}

void Steel::obtain() {
    kilograms += 6000;
    std::cout << "Steel obtained: 6000 kg" << std::endl;
}

void Steel::refine() {
    kilograms *= 0.95;  
    std::cout << "Steel refined: " << kilograms << " kg" << std::endl;
}


Wood* Wood::instance = nullptr;

Wood::Wood() {}

Wood* Wood::getInstance() {
    if (instance == nullptr) {
        instance = new Wood();
    }
    return instance;
}

void Wood::obtain() {
    kilograms += 20000;
    std::cout << "Wood obtained: 20000 kg" << std::endl;
}

void Wood::refine() { 
    kilograms *= 0.9;  
    std::cout << "Wood refined: " << kilograms << " kg" << std::endl;
}