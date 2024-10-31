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
    monthlyRoutines = new MonthlyRoutines(cityGrowth);
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

void Government::createBuilding() {
    std::cout << "Select which type of building you would like to create(1-4):" << std::endl;
    std::cout << "  1. Residential" << std::endl;
    std::cout << "  2. Industrial" << std::endl;
    std::cout << "  3. Commercial" << std::endl;
    std::cout << "  4. Landmark" << std::endl;
    std::cout << "  5. Institutional" << std::endl; 
    int type, type2, sector;
    std::cin >> type;

    std::string name;
    std::cout << "Enter the name of the building: ";
    std::cin >> name;

    std::cout << "Enter the sector you want the building: " << std::endl;
    std::cin >> sector;

    Building* b = nullptr;
    bool check;

    switch (type) {
        case 1: {  // Residential
            int capacity;
            std::cout << "Select which type of residential building would you like to create(1-3):" << std::endl;
            std::cout << "  1. House" << std::endl;
            std::cout << "  2. Apartment" << std::endl;
            std::cout << "  3. Mansion" << std::endl;
            std::cin >> type2;

            std::cout << "Enter how many people can live in the residential building: " << std::endl;
            std::cin >> capacity;

            switch (type2) {
                case 1:
                    b = new House(name, capacity * capacity, 10 * capacity * capacity, capacity * 10000, capacity, capacity, capacity, capacity * 10);
                    break;
                case 2:
                    b = new Apartment(name, capacity * capacity, 5 * capacity * capacity, capacity * 5000, capacity, capacity, capacity, 2);
                    break;
                case 3:
                    b = new Mansion(name, capacity * capacity + 5, 15 * capacity * capacity, capacity * 15000, capacity + 3, capacity + 2, capacity, true);
                    break;
            }
            break;
        }

        case 2: {  // Industrial
            int carbonFootprint, capacity;
            std::cout << "Select which type of industrial building would you like to create(1-3):" << std::endl;
            std::cout << "  1. Factory" << std::endl;
            std::cout << "  2. Warehouse" << std::endl;
            std::cout << "  3. Plant" << std::endl;
            std::cin >> type2;

            std::cout << "Enter carbon footprint: ";
            std::cin >> carbonFootprint;

            std::cout << "Enter capacity: ";
            std::cin >> capacity;

            switch (type2) {
                case 1:
                    b = new Factory(name, capacity * 2, capacity * 4, carbonFootprint * 1000, carbonFootprint, capacity);
                    break;
                case 2:
                    b = new Warehouse(name, capacity * 3, capacity * 5, carbonFootprint * 800, carbonFootprint, capacity);
                    break;
                case 3:
                    b = new Plant(name, capacity * 4, capacity * 6, carbonFootprint * 1200, carbonFootprint, capacity);
                    break;
            }
            break;
        }

        case 3: {  // Commercial
            int capacity, numFloors;
            std::cout << "Select which type of commercial building would you like to create(1-3):" << std::endl;
            std::cout << "  1. Shop" << std::endl;
            std::cout << "  2. Office" << std::endl;
            std::cout << "  3. Mall" << std::endl;
            std::cin >> type2;

            std::cout << "Enter capacity: ";
            std::cin >> capacity;

            std::cout << "Enter number of floors: ";
            std::cin >> numFloors;

            switch (type2) {
                case 1:
                    b = new Shop(name, capacity * 3, capacity * 10, capacity * 5000, capacity, numFloors, 3);
                    break;
                case 2:
                    b = new Office(name, capacity * 4, capacity * 15, capacity * 8000, capacity, numFloors, 5);
                    break;
                case 3:
                    b = new Mall(name, capacity * 6, capacity * 20, capacity * 15000, capacity, numFloors, 8);
                    break;
            }
            break;
        }

        case 4: {  // Landmark
            int culturalRelevance;
            std::cout << "Select which type of landmark would you like to create(1-2):" << std::endl;
            std::cout << "  1. Park" << std::endl;
            std::cout << "  2. Monument" << std::endl;
            std::cin >> type2;

            std::cout << "Enter cultural relevance (1-10): ";
            std::cin >> culturalRelevance;

            switch (type2) {
                case 1: {
                    int numTrees;
                    bool river;
                    std::cout << "Enter number of trees: ";
                    std::cin >> numTrees;
                    std::cout << "Is there a river? (1 for yes, 0 for no): ";
                    std::cin >> river;
                    b = new Park(name, 0, 0, culturalRelevance * 1000, culturalRelevance, numTrees, river);
                    break;
                }
                case 2: {
                    int detail;
                    std::cout << "Enter level of detail (1-5): ";
                    std::cin >> detail;
                    b = new Monument(name, 0, 0, culturalRelevance * 5000, culturalRelevance, detail);
                    break;
                }
            }
            break;
        }

        case 5: {  // Institutional
            int capacity, numFloors;
            std::cout << "Select which type of institutional building you would like to create(1-3):" << std::endl;
            std::cout << "  1. School" << std::endl;
            std::cout << "  2. Hospital" << std::endl;
            std::cout << "  3. Government Building" << std::endl;
            std::cin >> type2;

            std::cout << "Enter capacity: ";
            std::cin >> capacity;

            std::cout << "Enter number of floors: ";
            std::cin >> numFloors;

            switch (type2) {
                case 1:
                    b = new School(name, capacity * 3, capacity * 10, capacity * 7000, capacity, numFloors);
                    break;
                case 2:
                    b = new Hospital(name, capacity * 4, capacity * 15, capacity * 12000, capacity, numFloors);
                    break;
                case 3:
                    b = new GovermentBuilding(name, capacity * 5, capacity * 20, capacity * 15000, capacity, numFloors);
                    break;
            }
            break;
        }
    }

    if (b) {
        b->build();
        if (b->getBuilt()) {
            check = cityGrowth->addBuilding(b, sector);
        }
    }else{
        std::cout << "Tough cookies" << std::endl;
    }
}


void Government::createUtility() {
    std::cout << "Select which type of utility you would like to create: " << std::endl;
    std::cout << "1. PowerPlant \n2. Water Supply \n3. Waste Management Plant" << std::endl;
    int type;
    std::cin >> type;

    switch (type) {
        case 1:
            std::cout << "Select which type of Power Plant you would like to create: " << std::endl;
            std::cout << "1. Hyrdo  \n2. Coal \n3. Wind \n4 Solar" << std::endl;
            int powerplant;
            std::cin >> powerplant;
            std::cout << "Creating Power Plant..." << std::endl;
            powerPlant.push_back(new FunctionalPowerPlant(static_cast<powerPlants>(powerplant-1)));
            break;
        case 2:
            std::cout << "Creating Water Supply..." << std::endl;
            waterSupply.push_back(new FunctionalWaterSupply());
            break;
        case 3:
            std::cout << "Creating Waste Management Plant..." << std::endl;
            wasteManagement.push_back(new FunctionalWasteManagement());
            break;
        default:
            std::cout << "Invalid selection!" << std::endl;
            break;
    }
}

void Government::increaseMaterials(){
    std::cout << "Select which type of resource you would like to obtain: " << std::endl;
    std::cout << "1. Wood \n2. Steel \n3. Concrete \n4. All";
    int type;
    std::cin >> type;

    switch (type) {
        case 1:
            wood->increase();
            break;
        case 2:
            steel->increase();
            break;
        case 3:
            concrete->increase();
            break;
        case 4:
            wood->increase();
            concrete->increase();
            steel->increase();
            break;
        default:
            std::cout << "Invalid selection!" << std::endl;
            break;
    }
}


void Government::naturalDisaster(){
    std::cout << "Oh no, there was a natural distaster!" << std::endl;

    //Random PowerPlants
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> numDist(0, powerPlant.size());
    int numMalfunctions = numDist(gen);

    for(int i = 0; i < numMalfunctions; i++) {
        std::uniform_int_distribution<> indexDist(0, powerPlant.size() - 1);
        int randomIndex = indexDist(gen);
        if(powerPlant[randomIndex]->getFunctional()){
            PowerPlant* p = powerPlant[randomIndex]->mulfunction();
            PowerPlant* plantToDelete = powerPlant[randomIndex];
            powerPlant.erase(powerPlant.begin() + randomIndex);
            delete plantToDelete;
            powerPlant.push_back(p);
        }
        
    }
    std::cout << numMalfunctions << " PowerPlants have mulfunctioned." << std::endl;


//Random waterSupply
    std::random_device rd2;
    std::mt19937 gen2(rd2());

    std::uniform_int_distribution<> numDist2(0, waterSupply.size());
     numMalfunctions = numDist2(gen2);

    for(int i = 0; i < numMalfunctions; i++) {
        std::uniform_int_distribution<> indexDist(0, waterSupply.size() - 1);
        int randomIndex = indexDist(gen2);
        if(waterSupply[randomIndex]->getFunctional()){
            WaterSupply* w = waterSupply[randomIndex]->mulfunction();
            WaterSupply* supplyToDelete = waterSupply[randomIndex];
            waterSupply.erase(waterSupply.begin() + randomIndex);
            delete supplyToDelete;
            waterSupply.push_back(w);
        }
    }
    std::cout << numMalfunctions << " Water Supplies have mulfunctioned." << std::endl;



 //Random wasteManagement
    std::random_device rd3;
    std::mt19937 gen3(rd3());

    std::uniform_int_distribution<> numDist3(0, wasteManagement.size());
     numMalfunctions = numDist3(gen3);

    for(int i = 0; i < numMalfunctions; i++) {
    // Get random index
        std::uniform_int_distribution<> indexDist(0, wasteManagement.size() - 1);
        int randomIndex = indexDist(gen3);
        if(wasteManagement[randomIndex]->getFunctional()){
            WasteManagement* w = wasteManagement[randomIndex]->mulfunction();
            WasteManagement* wasteToDelete = wasteManagement[randomIndex];
            wasteManagement.erase(wasteManagement.begin() + randomIndex);
            delete wasteToDelete;
            wasteManagement.push_back(w);
        }
    }
    std::cout << numMalfunctions << " Waste Management Plants have mulfunctioned." << std::endl;

}

void Government::upgradeTransport(){
    monthlyRoutines->executueTransport();
}

void Government::upgradeBuildings(){
    monthlyRoutines->executueBuilding();
}

void Government::taxCitizens(){
    taxSystem->collectTax(cityGrowth);
}

void Government::changeTaxStartegy(){
    taxSystem->toggleStrategy();
}

void Government::repairUtilities(){
    std::cout << "Select which utilities to repair: " << std::endl;
    std::cout << "  1. Power Plants\n    2. Water Supplies\n    3. Waste management" << std::endl;
    int u;
    std::cin >> u;

    switch (u){
    case 1:
        for (auto x : powerPlant){
            if(!x->getFunctional()){
                PowerPlant* p = x->repair();
                delete x;
                
            }
        }
        
        break;
    case 2:
        for (auto x : waterSupply){
            if(!x->getFunctional()){
                x->repair();
            }
        }
        
        break;
    case 3:
        for (auto x : wasteManagement){
            if(!x->getFunctional()){
                x->repair();
            }
        }
        
        break;
    default:
        break;
    }
}

void Government::createCitizen()
{
}
