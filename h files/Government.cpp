#include "Government.h"

Government::Government(){
    water = Water::getInstance();
    budget = Budget::getInstance();
    energy = Energy::getInstance();
    wood = Wood::getInstance();
    concrete = Concrete::getInstance();
    steel = Steel::getInstance();
    taxSystem = new TaxSystem();
    cityGrowth = new CityGrowth();
}

Government::~Government(){
    delete water;
    delete budget; 
    delete energy;
    delete wood;
    delete concrete;
    delete steel;
    delete taxSystem;
}

void Government::createBuilding(){
    std::cout << "Select which type of building you would like to create(1-4):" << std::endl;
    std::cout << "  1. Residential" << std::endl;
    std::cout << "  2. Industrial" << std::endl;
    std::cout << "  3. Commertial" << std::endl;
    std::cout << "  4. Landmark" << std::endl;
    int type;
    int type2;
    std::cin >> type;

    std::string name;
    std::cout << "Enter the name of the building:" <<std::endl;
    std::cin >> name;

    switch (type)
    {
    case 1:
        int capacity;
        
        std::cout << "Select which type of residential building would you like to create(1-3):" << std::endl;
        std::cout << "  1. House" << std::endl;
        std::cout << "  2. Apartment" << std::endl;
        std::cout << "  3. Mansion" << std::endl;
        cin >> type2;
        
        std::cout << "Enter how many people can live in the residential building: " << std::endl;
        std::cin >> capacity;
        switch (type2)
        {
        case 1:
            //Building* b = new House("House", );
            break;
        
        default:
            break;
        }
        break;
    case 2:
        std::cout << "Select which type of commertial building would you like to create(1-3):" << std::endl;
        std::cout << "  1. Shop" << std::endl;
        std::cout << "  2. Office" << std::endl;
        std::cout << "  3. Mall" << std::endl;
        cin >> type2;
        break;
    case 3:
        std::cout << "Select which type of industrial building would you like to create(1-3):" << std::endl;
        std::cout << "  1. Factory" << std::endl;
        std::cout << "  2. Warehouse" << std::endl;
        std::cout << "  3. Plant" << std::endl;
        cin >> type2;
        break;
    case 4:
        std::cout << "Select which type of landmark would you like to create(1-3):" << std::endl;
        std::cout << "  1. Park" << std::endl;
        std::cout << "  2. Monument" << std::endl;
        cin >> type2;
    default:
        break;
    }
}
