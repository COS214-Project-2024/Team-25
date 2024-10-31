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
    roadSystem = new RoadSystem();
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

enum class Color {
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    RESET
};

void printC(const std::string& text, Color color) {
    // ANSI escape codes for text colors
    switch (color) {
        case Color::RED:     std::cout << "\033[31m"; break;
        case Color::GREEN:   std::cout << "\033[32m"; break;
        case Color::YELLOW:  std::cout << "\033[33m"; break;
        case Color::BLUE:    std::cout << "\033[34m"; break;
        case Color::MAGENTA: std::cout << "\033[35m"; break;
        case Color::CYAN:    std::cout << "\033[36m"; break;
        case Color::WHITE:   std::cout << "\033[37m"; break;
        case Color::RESET:   std::cout << "\033[0m";  break;
    }
    std::cout << text;
    std::cout << "\033[0m\n";
}

bool validateIntInput(int value, int lowerBound, int upperBound) {
    return (value >= lowerBound && value <= upperBound);
}

int safeIntInput(int lowerBound, int upperBound) {
    int input;
    while (true) {
        printC("Enter an integer between " + std::to_string(lowerBound) + " and " + std::to_string(upperBound) + ": ", Color::CYAN);
        
        if (std::cin >> input) {
            if (validateIntInput(input, lowerBound, upperBound)) {
                printC("Valid input received.", Color::GREEN);
                return input;
            }
            printC("Input out of range. Try again.", Color::RED);
        }
        else {
            // Clear error flags and ignore invalid input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printC("Invalid input. Please enter an integer.", Color::RED);
        }
    }
}

void Government::createBuilding() {
    std::cout << "Select which type of building you would like to create(1-4):" << std::endl;
    //std::cout << "  1. Residential" << std::endl;
    std::cout << "  1. Industrial" << std::endl;
    std::cout << "  2. Commercial" << std::endl;
    std::cout << "  3. Institutional" << std::endl; 
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
        // case 1: {  // Residential
        //     int capacity;
        //     std::cout << "Select which type of residential building would you like to create(1-3):" << std::endl;
        //     std::cout << "  1. House" << std::endl;
        //     std::cout << "  2. Apartment" << std::endl;
        //     std::cout << "  3. Mansion" << std::endl;
        //     std::cin >> type2;

        //     std::cout << "Enter how many people can live in the residential building: " << std::endl;
        //     std::cin >> capacity;

        //     switch (type2) {
        //         case 1:
        //             b = new House(name, capacity * capacity, 10 * capacity * capacity, capacity * 10000, capacity, capacity, capacity, capacity * 10);
        //             break;
        //         case 2:
        //             b = new Apartment(name, capacity * capacity, 5 * capacity * capacity, capacity * 5000, capacity, capacity, capacity, 2);
        //             break;
        //         case 3:
        //             b = new Mansion(name, capacity * capacity + 5, 15 * capacity * capacity, capacity * 15000, capacity + 3, capacity + 2, capacity, true);
        //             break;
        //     }
        //     break;
        // }

        case 1: {  // Industrial
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

        case 2: {  // Commercial
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

        case 3: {  // Institutional
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
                    b = new GovernmentBuilding(name, capacity * 5, capacity * 20, capacity * 15000, capacity, numFloors);
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
    printC("Select which utilities to repair:", Color::CYAN);
    printC("    1. Power Plants", Color::WHITE);
    printC("    2. Water Supplies", Color::WHITE);
    printC("    3. Waste Management", Color::WHITE);
    int u = safeIntInput(1, 3);

    switch (u){
    case 1:
        for (auto it = powerPlant.begin(); it != powerPlant.end(); ) {
            if (!(*it)->getFunctional()) {
                PowerPlant* repairedPlant = (*it)->repair();
                delete *it;
                
                if (repairedPlant) {
                    *it = repairedPlant;
                    ++it;
                } else {
                    it = powerPlant.erase(it);
                }
            } else {
                ++it;
            }
        }
        break;

    case 2:
        for (auto it = waterSupply.begin(); it != waterSupply.end(); ) {
            if (!(*it)->getFunctional()) {
                WaterSupply* repairedSupply = (*it)->repair();
                delete *it;
                
                if (repairedSupply) {
                    *it = repairedSupply;
                    ++it;
                } else {
                    it = waterSupply.erase(it);
                }
            } else {
                ++it;
            }
        }
        break;
    
    case 3:
        for (auto it = wasteManagement.begin(); it != wasteManagement.end(); ) {
            if (!(*it)->getFunctional()) {
                WasteManagement* repairedWaste = (*it)->repair();
                delete *it;
                
                if (repairedWaste) {
                    *it = repairedWaste;
                    ++it;
                } else {
                    it = wasteManagement.erase(it);
                }
            } else {
                ++it;
            }
        }
        break;

    default:
        printC("Invalid utility selection.", Color::RED);
        break;
    }
}

void Government::createCitizen() {
    std::cout << "Select which work sector your citizen should work in: " << std::endl;
    std::cout << "  1. Industrial" << std::endl;
    std::cout << "  2. Commercial" << std::endl;
    std::cout << "  3. Institutional" << std::endl;

    int sector, type2, type;
    std::cin >> type;
    bool valid = false;

    while (!valid) {
        std::cout << "Enter the sector you want the citizen to work in: (Select from 1-" << cityGrowth->getTotalSectorCount() << ")" << std::endl;
        std::cin >> sector;

        if (sector < 1 || sector > cityGrowth->getTotalSectorCount()) {
            std::cout << "Invalid sector number" << std::endl;
        } else valid = true;
    }

    CitySector* s = cityGrowth->getSectors()[sector - 1];
    bool assigned = false;
    CitizenFactory* factory = nullptr;

    switch (type) {
        case 1: {  // Industrial
            factory = new IndWorkerFactory();
            std::cout << "Select which type of industrial building would you like your citizen to work at:" << std::endl;
            std::cout << "  1. Factory" << std::endl;
            std::cout << "  2. Warehouse" << std::endl;
            std::cout << "  3. Plant" << std::endl;
            std::cin >> type2;

            // Handle assignment to industrial buildings
            if (type2 == 1) {  // Factory
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Factory" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("Factory");
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                if (!assigned) {
                    promptForNewFactory(sector);
                }
            }
            else if (type2 == 2) {  // Warehouse
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Warehouse" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("Warehouse");
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                if (!assigned) {
                    promptForNewWarehouse(sector);
                }
            }
            else if (type2 == 3) {  // Plant
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Plant" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("Plant");
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                if (!assigned) {
                    promptForNewPlant(sector);
                }
            }

            // Check for Apartment Building assignment
            if (assigned) {
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Apartment Building" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("Apartment Building");
                        b->addCitizen(c);
                        break;
                    }
                }
                // If no apartment found, prompt to create one
                if (!assigned) {
                    promptForNewApartment(sector);
                }
            }
            delete factory; // Clean up the factory
            break;
        }

        case 2: {  // Commercial
            factory = new ComWorkerFactory();
            std::cout << "Select which type of commercial building would you like your citizen to work at:" << std::endl;
            std::cout << "  1. Shop" << std::endl;
            std::cout << "  2. Office" << std::endl;
            std::cout << "  3. Mall" << std::endl;
            std::cin >> type2;

            // Handle assignment to commercial buildings
            if (type2 == 1) {  // Shop
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Shop" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("Shop");
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                if (!assigned) {
                    promptForNewShop(sector);
                }
            }
            else if (type2 == 2) {  // Office
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Office" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("Office");
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                if (!assigned) {
                    promptForNewOffice(sector);
                }
            }
            else if (type2 == 3) {  // Mall
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Mall" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("Mall");
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                if (!assigned) {
                    promptForNewMall(sector);
                }
            }

            // Check for House assignment
            if (assigned) {
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "House" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("House");
                        b->addCitizen(c);
                        break;
                    }
                }
                // If no house found, prompt to create one
                if (!assigned) {
                    promptForNewHouse(sector);
                }
            }
            delete factory; // Clean up the factory
            break;
        }

        case 3: {  // Institutional
            factory = new GovernmentWorkerFactory();
            std::cout << "Select which type of institutional building would you like your citizen to work at:" << std::endl;
            std::cout << "  1. School" << std::endl;
            std::cout << "  2. Hospital" << std::endl;
            std::cout << "  3. Government Building" << std::endl;
            std::cin >> type2;

            // Handle assignment to institutional buildings
            if (type2 == 1) {  // School
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "School" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("School");
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                if (!assigned) {
                    promptForNewSchool(sector);
                }
            }
            else if (type2 == 2) {  // Hospital
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Hospital" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("Hospital");
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                if (!assigned) {
                    promptForNewHospital(sector);
                }
            }
            else if (type2 == 3) {  // Government Building
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Government Building" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("Government Building");
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                if (!assigned) {
                    promptForNewGovernmentBuilding(sector);
                }
            }

            // Check for Mansion assignment
            if (assigned) {
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Mansion" && b->getLeftOverCapacity() > 0) {
                        Citizen* c = factory->createCitizen("Mansion");
                        b->addCitizen(c);
                        break;
                    }
                }
                // If no mansion found, prompt to create one
                if (!assigned) {
                    promptForNewMansion(sector);
                }
            }
            delete factory; // Clean up the factory
            break;
        }

        default:
            std::cout << "Invalid type entered" << std::endl;
            break;
    }
}


void Government::promptForNewApartment(int sector) {
    std::cout << "No current apartment building available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity, floors;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        std::cout << "Enter number of floors: ";
        std::cin >> floors;
        Building* a =new Apartment(name, capacity * capacity, 5 * capacity * capacity, capacity * 5000, capacity, capacity, capacity, 2);
        a->build();
        if (a->getBuilt()){
            cityGrowth->addBuilding(a, sector);
        }
    }
    else {
        std::cout << "No apartment building created" << std::endl;
    }
}

// Function to prompt for creating a new house
void Government::promptForNewHouse(int sector) {
    std::cout << "No current house available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity, floors;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        std::cout << "Enter number of floors: ";
        std::cin >> floors;
        Building* h = new House(name, capacity * capacity, 10 * capacity * capacity, capacity * 10000, capacity, capacity, capacity, capacity * 10);
        h->build();
        if (h->getBuilt()){
            cityGrowth->addBuilding(h, sector);
        }
    }
    else {
        std::cout << "No house created" << std::endl;
    }
}

// Function to prompt for creating a new mansion
void Government::promptForNewMansion(int sector) {
    std::cout << "No current mansion available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity, floors;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        std::cout << "Enter number of floors: ";
        std::cin >> floors;
        Building* m = new Mansion(name, capacity * capacity + 5, 15 * capacity * capacity, capacity * 15000, capacity + 3, capacity + 2, capacity, true);
        m->build();
        if (m->getBuilt()){
            cityGrowth->addBuilding(m, sector);
        }
    }
    else {
        std::cout << "No mansion created" << std::endl;
    }
}


// Function definitions
void Government::promptForNewFactory(int sector) {
    // Prompt for new factory details
    std::cout << "No current factory available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity, carbonFootprint;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter carbon footprint: ";
        std::cin >> carbonFootprint;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        Building* f = new Factory(name, capacity * 2, capacity * 4, carbonFootprint * 1000, carbonFootprint, capacity);
        f->build();
        if (f->getBuilt()){
            cityGrowth->addBuilding(f, sector);
        }
    }
    else {
        std::cout << "No factory created" << std::endl;
    }
}

void Government::promptForNewWarehouse(int sector) {
    // Prompt for new warehouse details
    std::cout << "No current warehouse available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        Building* w = new Warehouse(name, capacity * 3, capacity * 5, capacity * 3000, capacity, 2);
        w->build();
        if (w->getBuilt()){
            cityGrowth->addBuilding(w, sector);
        }
    }
    else {
        std::cout << "No warehouse created" << std::endl;
    }
}

void Government::promptForNewPlant(int sector) {
    // Prompt for new plant details
    std::cout << "No current plant available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity, carbonFootprint;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter carbon footprint: ";
        std::cin >> carbonFootprint;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        Building* p = new Plant(name, capacity * 3, capacity * 5, carbonFootprint * 1000, carbonFootprint, capacity);
        p->build();
        if (p->getBuilt()){
            cityGrowth->addBuilding(p, sector);
        }
    }
    else {
        std::cout << "No plant created" << std::endl;
    }
}

void Government::promptForNewShop(int sector) {
    // Prompt for new shop details
    std::cout << "No current shop available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity, floors;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        std::cout << "Enter number of floors: ";
        std::cin >> floors;
        Building* s = new Shop(name, capacity * 2, capacity * 5, capacity * 1000, capacity, floors, 3);
        s->build();
        if (s->getBuilt()){
            cityGrowth->addBuilding(s, sector);
        }
    }
    else {
        std::cout << "No shop created" << std::endl;
    }
}

void Government::promptForNewOffice(int sector) {
    // Prompt for new office details
    std::cout << "No current office available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity, floors;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        std::cout << "Enter number of floors: ";
        std::cin >> floors;
        Building* o = new Office(name, capacity * 4, capacity * 15, capacity * 8000, capacity, floors, 5);
        o->build();
        if (o->getBuilt()){
            cityGrowth->addBuilding(o, sector);
        }
    }
    else {
        std::cout << "No office created" << std::endl;
    }
}

void Government::promptForNewMall(int sector) {
    // Prompt for new mall details
    std::cout << "No current mall available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity, floors;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        std::cout << "Enter number of floors: ";
        std::cin >> floors;
        Building* m = new Mall(name, capacity * 6, capacity * 20, capacity * 15000, capacity, floors, 8);
        m->build();
        if (m->getBuilt()){
            cityGrowth->addBuilding(m, sector);
        }
    }
    else {
        std::cout << "No mall created" << std::endl;
    }
}

void Government::promptForNewSchool(int sector) {
    // Prompt for new school details
    std::cout << "No current school available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity, floors;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        std::cout << "Enter number of floors: ";
        std::cin >> floors;
        Building* sc = new School(name, capacity * 5, capacity * 15, capacity * 20000, capacity, floors);
        sc->build();
        if (sc->getBuilt()){
            cityGrowth->addBuilding(sc, sector);
        }
    }
    else {
        std::cout << "No school created" << std::endl;
    }
}

void Government::promptForNewHospital(int sector) {
    // Prompt for new hospital details
    std::cout << "No current hospital available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity, floors;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        std::cout << "Enter number of floors: ";
        std::cin >> floors;
        Building* h = new Hospital(name, capacity * 10, capacity * 20, capacity * 50000, capacity, floors);
        h->build();
        if (h->getBuilt()){
            cityGrowth->addBuilding(h, sector);
        }
    }
    else {
        std::cout << "No hospital created" << std::endl;
    }
}

void Government::promptForNewGovernmentBuilding(int sector) {
    // Prompt for new government building details
    std::cout << "No current government building available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y") {
        int capacity, floors;
        std::string name;
        std::cout << "Enter the name of the building: ";
        std::cin >> name;
        std::cout << "Enter capacity: ";
        std::cin >> capacity;
        std::cout << "Enter number of floors: ";
        std::cin >> floors;
        Building* g = new GovernmentBuilding(name, capacity * 8, capacity * 25, capacity * 40000, capacity, floors);
        g->build();
        if (g->getBuilt()){
            cityGrowth->addBuilding(g, sector);
        }
    }
    else {
        std::cout << "No government building created" << std::endl;
    }
}

