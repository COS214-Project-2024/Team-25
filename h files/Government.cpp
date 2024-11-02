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
    roadSystemAdapter = new RoadSystemAdapter(new RoadSystem());
    cityGrowth->setRoads(roadSystemAdapter);
}

Government::~Government(){
    delete water;
    delete budget; 
    delete energy;
    delete wood;
    delete concrete;
    delete steel;
    delete taxSystem;
    delete monthlyRoutines;
    delete roadSystemAdapter;
    delete cityGrowth;
    for (auto& water : waterSupply) {
        delete water;
    }
    for (auto& waste : wasteManagement) {
        delete waste;
    }
    for (auto& plant : powerPlant) {
        delete plant;
    }
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

inline void printC(const std::string& text, Color color) {
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

inline bool validateIntInput(int value, int lowerBound, int upperBound) {
    return (value >= lowerBound && value <= upperBound);
}

inline int safeIntInput(int lowerBound, int upperBound) {
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
    std::cout << "Select which type of building you would like to create(1-3):" << std::endl;
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

    sector = safeIntInput(0, cityGrowth->getTotalSectorCount()-1);

    Building* b = nullptr;
    bool check = false;

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
                    b = new Factory(name, capacity * 2, capacity * 4, capacity * 1000, carbonFootprint, capacity);
                    break;
                case 2:
                    b = new Warehouse(name, capacity * 3, capacity * 5, capacity * 800, carbonFootprint, capacity);
                    break;
                case 3:
                    b = new Plant(name, capacity * 4, capacity * 6, capacity * 1200, carbonFootprint, capacity);
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
            Road r(5, b->getType()); 
            roadSystemAdapter->addRoute(r);
        }
        if(check){
            printC("Successfully added a building!", Color::GREEN);
        }else{
            printC("Failed to add a building!", Color::RED);
        }
    }else{
        std::cout << "Tough cookies" << std::endl;
    }
}


void Government::createUtility() {
    std::cout << "Select which type of utility you would like to create: " << std::endl;
    std::cout << "    1. PowerPlant \n    2. Water Supply \n    3. Waste Management Plant" << std::endl;
    int type;
    std::cin >> type;

    switch (type) {
        case 1:{
            std::cout << "Select which type of Power Plant you would like to create: " << std::endl;
            std::cout << "    1. Hydro  \n    2. Coal \n    3. Wind \n    4. Solar" << std::endl;
            int powerplant;
            std::cin >> powerplant;
            
            if (powerplant >= 1 && powerplant <= 4) {
                std::cout << "Creating Power Plant..." << std::endl;
                PowerPlant* plant = new FunctionalPowerPlant(static_cast<powerPlants>(powerplant-1), true);
                if (plant->getPowerGenerationRaw() > 0) {
                    powerPlant.push_back(plant);
                    std::cout << "Power Plant created successfully!" << std::endl;
                } else {
                    delete plant;
                    std::cout << "Failed to create Power Plant: No power generation capacity!" << std::endl;
                }
            } else {
                std::cout << "Invalid Power Plant type selected!" << std::endl;
            }
            break;
        }
        case 2:{
            std::cout << "Creating Water Supply..." << std::endl;
            WaterSupply* water = new FunctionalWaterSupply(true);
            if (water->getWaterGenerationRaw() > 0) {
                waterSupply.push_back(water);
                std::cout << "Water Supply created successfully!" << std::endl;
            } else {
                delete water;
                std::cout << "Failed to create Water Supply: No water generation capacity!" << std::endl;
            }
            break;
        }
        case 3:{
            std::cout << "Creating Waste Management Plant..." << std::endl;
            WasteManagement* waste = new FunctionalWasteManagement(true);
            if (waste->getWasteCollectionRaw() > 0) {
                wasteManagement.push_back(waste);
                std::cout << "Waste Management Plant created successfully!" << std::endl;
            } else {
                delete waste;
                std::cout << "Failed to create Waste Management Plant: No waste collection capacity!" << std::endl;
            }
            break;
        }
        default:
            std::cout << "Invalid selection!" << std::endl;
            break;
    }
}

void Government::increaseMaterials(){
    std::cout << "Select which type of resource you would like to obtain: " << std::endl;
    std::cout << "1. Wood \n2. Steel \n3. Concrete \n4. All\n";
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
    int counter = 0;
    for(int i = 0; i < numMalfunctions; i++) {
        std::uniform_int_distribution<> indexDist(0, powerPlant.size() - 1);
        int randomIndex = indexDist(gen);
        if(powerPlant[randomIndex]->getFunctional()){
            PowerPlant* p = powerPlant[randomIndex]->mulfunction();
            PowerPlant* plantToDelete = powerPlant[randomIndex];
            powerPlant.erase(powerPlant.begin() + randomIndex);
            delete plantToDelete;
            powerPlant.push_back(p);
            counter++;
        }
        
    }
    std::cout << counter << " PowerPlants have mulfunctioned." << std::endl;


//Random waterSupply
    std::random_device rd2;
    std::mt19937 gen2(rd2());

    std::uniform_int_distribution<> numDist2(0, waterSupply.size());
     numMalfunctions = numDist2(gen2);
    counter = 0;
    for(int i = 0; i < numMalfunctions; i++) {
        std::uniform_int_distribution<> indexDist(0, waterSupply.size() - 1);
        int randomIndex = indexDist(gen2);
        if(waterSupply[randomIndex]->getFunctional()){
            WaterSupply* w = waterSupply[randomIndex]->mulfunction();
            WaterSupply* supplyToDelete = waterSupply[randomIndex];
            waterSupply.erase(waterSupply.begin() + randomIndex);
            delete supplyToDelete;
            waterSupply.push_back(w);
            counter++;
        }
    }
    std::cout << counter << " Water Supplies have mulfunctioned." << std::endl;



 //Random wasteManagement
    std::random_device rd3;
    std::mt19937 gen3(rd3());

    std::uniform_int_distribution<> numDist3(0, wasteManagement.size());
     numMalfunctions = numDist3(gen3);
    counter = 0;
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
            counter++;
        }
    }
    std::cout << counter << " Waste Management Plants have mulfunctioned." << std::endl;

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
                if(repairedPlant->getFunctional()){
                    delete *it;
                }
                
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
                if(repairedSupply->getFunctional()){
                    delete *it;
                }
                
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
                if(repairedWaste->getFunctional()){
                    delete *it;
                }
                
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

void Government::createCitizen(int numCitizens) {
    std::cout << "Select which work sector your citizens should work in: " << std::endl;
    std::cout << "  1. Industrial" << std::endl;
    std::cout << "  2. Commercial" << std::endl;
    std::cout << "  3. Institutional" << std::endl;

    int sector, type2, type;
    std::cin >> type;
    bool valid = false;

    while (!valid) {
        std::cout << "Enter the sector you want the citizens to work in: (Select from 0- " << cityGrowth->getTotalSectorCount() -1 << ")" << std::endl;
        std::cin >> sector;

        if (sector < 1 || sector > cityGrowth->getTotalSectorCount()) {
            std::cout << "Invalid sector number" << std::endl;
        } else 
        {
            valid = true;
        }
    }

    CitizenFactory* factory = nullptr;

    switch (type) {
        case 1: {  // Industrial
            factory = new IndWorkerFactory();
            std::cout << "Select which type of industrial building would you like your citizens to work at:" << std::endl;
            std::cout << "  1. Factory" << std::endl;
            std::cout << "  2. Warehouse" << std::endl;
            std::cout << "  3. Plant" << std::endl;
            std::cin >> type2;

            // Create all citizens of the same type
            std::string buildingType;
            if (type2 == 1) buildingType = "Factory";
            else if (type2 == 2) buildingType = "Warehouse";
            else if (type2 == 3) buildingType = "Plant";

            for(int i = 0; i < numCitizens; i++) {
                bool assigned = false;
                CitySector* s = cityGrowth->getSectors()[sector];
                Citizen* c = factory->createCitizen(buildingType);

                // Try to assign to existing work building
                for (auto* b : s->getBuildings()) 
                {
                    if (b->getType() == buildingType && b->getLeftOverCapacity() > 0) {
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                
                // If no existing building has space, create new one
                if (!assigned) {
                    if (type2 == 1) promptForNewFactory(sector);
                    else if (type2 == 2) promptForNewWarehouse(sector);
                    else if (type2 == 3) promptForNewPlant(sector);
                }

                // Try to assign to existing apartment
                bool housingAssigned = false;
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Apartment" && b->getLeftOverCapacity() > 0) {
                        b->addCitizen(c);
                        housingAssigned = true;
                        break;
                    }
                }
                
                // If no apartment found, create new one
                if (!housingAssigned) {
                    promptForNewApartment(sector, c);
                }
            }
            delete factory;
            break;
        }

        case 2: {  // Commercial
            factory = new ComWorkerFactory();
            std::cout << "Select which type of commercial building would you like your citizens to work at:" << std::endl;
            std::cout << "  1. Shop" << std::endl;
            std::cout << "  2. Office" << std::endl;
            std::cout << "  3. Mall" << std::endl;
            std::cin >> type2;

            std::string buildingType;
            if (type2 == 1) buildingType = "Shop";
            else if (type2 == 2) buildingType = "Office";
            else if (type2 == 3) buildingType = "Mall";

            for(int i = 0; i < numCitizens; i++) {
                bool assigned = false;
                CitySector* s = cityGrowth->getSectors()[sector];
                Citizen* c = factory->createCitizen(buildingType);
                // Try to assign to existing work building
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == buildingType && b->getLeftOverCapacity() > 0) {
                        
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                
                // If no existing building has space, create new one
                if (!assigned) {
                    if (type2 == 1) promptForNewShop(sector);
                    else if (type2 == 2) promptForNewOffice(sector);
                    else if (type2 == 3) promptForNewMall(sector);
                }

                // Try to assign to existing house
                bool housingAssigned = false;
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "House" && b->getLeftOverCapacity() > 0) {
                        b->addCitizen(c);
                        housingAssigned = true;
                        break;
                    }
                }
                
                // If no house found, create new one
                if (!housingAssigned) {
                    promptForNewHouse(sector, c);
                }
            }
            delete factory;
            break;
        }

        case 3: {  // Institutional
            factory = new GovernmentWorkerFactory();
            std::cout << "Select which type of institutional building would you like your citizens to work at:" << std::endl;
            std::cout << "  1. School" << std::endl;
            std::cout << "  2. Hospital" << std::endl;
            std::cout << "  3. Government Building" << std::endl;
            std::cin >> type2;

            std::string buildingType;
            if (type2 == 1) buildingType = "School";
            else if (type2 == 2) buildingType = "Hospital";
            else if (type2 == 3) buildingType = "GovernmentBuilding";

            for(int i = 0; i < numCitizens; i++) {
                bool assigned = false;
                CitySector* s = cityGrowth->getSectors()[sector];
                Citizen* c = factory->createCitizen(buildingType);
                // Try to assign to existing work building
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == buildingType && b->getLeftOverCapacity() > 0) {
                        b->addCitizen(c);
                        assigned = true;
                        break;
                    }
                }
                
                // If no existing building has space, create new one
                if (!assigned) {
                    if (type2 == 1) promptForNewSchool(sector);
                    else if (type2 == 2) promptForNewHospital(sector);
                    else if (type2 == 3) promptForNewGovernmentBuilding(sector);
                }

                // Try to assign to existing mansion
                bool housingAssigned = false;
                for (auto* b : s->getBuildings()) {
                    if (b->getType() == "Mansion" && b->getLeftOverCapacity() > 0) {
                        b->addCitizen(c);
                        housingAssigned = true;
                        break;
                    }
                }
                
                // If no mansion found, create new one
                if (!housingAssigned) {
                    promptForNewMansion(sector, c);
                }
            }
            delete factory;
            break;
        }

        default:
            std::cout << "Invalid type entered" << std::endl;
            break;
    }
}

float Government::avgSatisfaction(){
    std::vector<CitySector*> sectors = cityGrowth->getSectors();
    float total = 0;
    float count  = 0.0;
    for (int i = 0; i < sectors.size(); i++)
    {
        CitySector* sector = sectors.at(i);
        std::vector<Building*> block = sector->getBuildings();
        for (int j = 0; j < block.size(); j++)
        {
            if(block.at(j) != nullptr && block.at(j)->getBuildingType() != "House" && block.at(j)->getBuildingType() != "Mansion" && block.at(j)->getBuildingType() != "Apartment"){
                std::vector<Citizen*> citizens = block.at(j)->getCitizens(); 
                for (int k = 0; k < citizens.size(); k++)
                {
                   total += citizens.at(k)->getSatisfaction();
                   count += 1.0; 
                }
                
            //     if (repairedPlant) {
            //         *it = repairedPlant;
            //         ++it;
            //     } else {
            //         it = powerPlant.erase(it);
            //     }
            // } else {
            //     ++it;
            }
        }
        
    }
    return total/count;
    
}

void Government::updateSatisfaction(int amt){
    std::vector<CitySector*> sectors = cityGrowth->getSectors();
    float total = 0;
    float count  = 0.0;
    for (int i = 0; i < sectors.size(); i++){
        CitySector* sector = sectors.at(i);
        std::vector<Building*> block = sector->getBuildings();
        for (int j = 0; j < block.size(); j++){
            if(block.at(j) != nullptr && block.at(j)->getBuildingType() != "House" && block.at(j)->getBuildingType() != "Mansion" && block.at(j)->getBuildingType() != "Apartment"){
                std::vector<Citizen*> citizens = block.at(j)->getCitizens();            
                for (int k = 0; k < citizens.size(); k++){
                   citizens.at(k)->changeSatisfaction(amt);
                   
                }
                
            }
        }
        
    }
        
 
}

void Government::setDifficulty(int difficulty)
{
    CitizenFactory* residentialFactory = nullptr;
    CitizenFactory* commercialFactory = nullptr;
    CitizenFactory* industrialFactory = nullptr;
    CitizenFactory* institutionalFactory = nullptr;

    commercialFactory = new ComWorkerFactory();
    industrialFactory = new IndWorkerFactory();
    institutionalFactory = new GovernmentWorkerFactory();

    int k = cityGrowth->getTotalSectorCount();
     for (int i = 0; i < k; i++)
    {
        Building* f = new Factory("Factory 1", 5, 500, 10000.00, 100, 5);
        Building* a = new Apartment("Apartment 1", 2, 50, 2000.00, 1, 1, 5, 2);
        Road r(5, "Industrial"); 
        roadSystemAdapter->addRoute(r);
        for (int j = 0; j < 3; j++)
        {
            Citizen* c = industrialFactory->createCitizen("Factory");
            f->addCitizen(c);
            a->addCitizen(c);
        }
        cityGrowth->addBuilding(f,i);
        cityGrowth->addBuilding(a,i);


        Building* p = new Plant("Plant 1", 5, 500, 10000.00, 100, 5);
        Building* a1 = new Apartment("Apartment 2", 2, 50, 2000.00, 1, 1, 5, 2);
        Road r2(5, "Industrial"); 
        roadSystemAdapter->addRoute(r2);
        for (int j = 0; j < 4; j++)
        {
            Citizen* c = industrialFactory->createCitizen("Plant");
            p->addCitizen(c);
            a1->addCitizen(c);
        }
        cityGrowth->addBuilding(p,i);
        cityGrowth->addBuilding(a1,i);

        Building* s = new Shop("Shop 1", 1, 50, 1000.00, 10, 1, 1);
        Building* h = new House("House 1",2,50,100.00,2,2,5,3);
        Road com(5, "Commercial"); 
        roadSystemAdapter->addRoute(com);
        for (int n = 0; n < 4; n++)
        {
            Citizen* c = commercialFactory->createCitizen("Shop");
            s->addCitizen(c);
            h->addCitizen(c);
        }

        cityGrowth->addBuilding(s,i);
        cityGrowth->addBuilding(h,i);

        Building* m1 = new Mall("Mall 1", 1, 50, 1000.00, 10, 1, 1);
        Building* h1 = new House("House 1",2,50,100.00,2,2,7,3);
        Road com1(5, "Commercial"); 
        roadSystemAdapter->addRoute(com1);
        for (int n = 0; n < 6; n++)
        {
            Citizen* c = commercialFactory->createCitizen("Mall");
            m1->addCitizen(c);
            h1->addCitizen(c);
        }

        cityGrowth->addBuilding(m1,i);
        cityGrowth->addBuilding(h1,i);
        
        Building* g = new GovernmentBuilding("Government Building 1", 5, 500, 10000.00, 50, 2);
        Building* m = new Mansion("Mansion 1",6,500,2000.00,6,6,10,false);

        Road in(5,"Instatutional");
        roadSystemAdapter->addRoute(in);
        for (int l = 0; l < 8; l++)
        {
            Citizen* c = institutionalFactory->createCitizen("GovernmentBuilding");
            g->addCitizen(c);
            m->addCitizen(c);
        }

        cityGrowth->addBuilding(g,i);
        cityGrowth->addBuilding(m,i);
    }

    delete commercialFactory;
    delete industrialFactory;
    delete institutionalFactory; 

    switch (difficulty)
    {
    case 1: 
    {
        wood->setKilo(100000);
        concrete->setKilo(100000);
        steel->setKilo(100000);

        budget->setCash(2000000.00);

        for (int i = 0; i < 4; i++)
        {
            // Create and validate PowerPlant
            FunctionalPowerPlant* plant = new FunctionalPowerPlant(static_cast<powerPlants>(i), true);
            if (plant->getPowerGenerationRaw() > 0) {
                powerPlant.push_back(plant);
            } else {
                delete plant;  
            }

            // Create and validate WaterSupply
            FunctionalWaterSupply* water = new FunctionalWaterSupply(true);
            if (water->getWaterGenerationRaw() > 0) {
                waterSupply.push_back(water);
            } else {
                delete water;
            }

            // Create and validate WasteManagement
            FunctionalWasteManagement* waste = new FunctionalWasteManagement(true);
            if (waste->getWasteCollectionRaw() > 0) {
                wasteManagement.push_back(waste);
            } else {
                delete waste;
            }
        }

        wood->setKilo(30000);
        concrete->setKilo(30000);
        steel->setKilo(30000);
        
    }
        break;

    case 2: 
    {
        wood->setKilo(100000);
        concrete->setKilo(100000);
        steel->setKilo(100000);
        budget->setCash(100000.00);

        // Add 2 of each utility type if they're functional
        for (int i = 0; i < 1; i++)
        {
            // Create and validate PowerPlant
            FunctionalPowerPlant* plant = new FunctionalPowerPlant(static_cast<powerPlants>(i), true);
            if (plant->getPowerGenerationRaw() > 0) {
                powerPlant.push_back(plant);
            } else {
                delete plant;
            }

            // Create and validate WaterSupply
            FunctionalWaterSupply* water = new FunctionalWaterSupply(true);
            if (water->getWaterGenerationRaw() > 0) {
                waterSupply.push_back(water);
            } else {
                delete water;
            }

            // Create and validate WasteManagement
            FunctionalWasteManagement* waste = new FunctionalWasteManagement(true);
            if (waste->getWasteCollectionRaw() > 0) {
                wasteManagement.push_back(waste);
            } else {
                delete waste;
            }
        }

        wood->setKilo(10000);
        concrete->setKilo(10000);
        steel->setKilo(10000);
    }
        break;

    case 3:
    {
        // Hardest difficulty - only basic resources, no utilities
        wood->setKilo(2000);
        concrete->setKilo(2000);
        steel->setKilo(2000);        
        budget->setCash(10000.00);

    }
        break;      

    default:
    {
        std::cout << "Invalid difficulty level. Please choose 1 (Easy), 2 (Medium), or 3 (Hard)." << std::endl;
    }
        break;
    }
}

void Government::printresources()
{
    printC("\nCurrent Resources and Utilities:", Color::CYAN);
    printC("-------------------------------", Color::CYAN);

    printC("Materials:", Color::GREEN);
    std::cout << "  Wood: " << wood->getKilo() << " kg" << std::endl;
    std::cout << "  Concrete: " << concrete->getKilo() << " kg" << std::endl;
    std::cout << "  Steel: " << steel->getKilo() << " kg" << std::endl;

    printC("\nUtilities:", Color::GREEN);
    std::cout << "  Power Plants: " << powerPlant.size() << std::endl;
    std::cout << "  Water Supply Systems: " << waterSupply.size() << std::endl;
    std::cout << "  Waste Management Facilities: " << wasteManagement.size() << std::endl;

    printC("\nBudget:", Color::GREEN);
    std::cout << "  Cash: $" << budget->getCash() << std::endl;

    printC("-------------------------------\n", Color::CYAN); 
}

void Government::printUtilitiesDetails()
{
    printC("================================", Color::CYAN);
    printC("Detailed Utilities Information:", Color::CYAN);
    printC("================================", Color::CYAN);

    // Power Plants
    printC("------------------------------", Color::GREEN);
    printC("Power Plants:", Color::GREEN);
    printC("------------------------------", Color::GREEN);
    if (powerPlant.empty()) {
        printC("  No power plants built yet.", Color::YELLOW);
    } else {
        for (size_t i = 0; i < powerPlant.size(); i++) {
            printC("\nPower Plant #" + std::to_string(i + 1) + ":", Color::YELLOW);
            std::cout << "  Type: " << static_cast<int>(powerPlant[i]->getType()) << std::endl;
            printC("  Status: " + std::string(powerPlant[i]->getFunctional() ? "Functional" : "Malfunctioning"), 
                   powerPlant[i]->getFunctional() ? Color::GREEN : Color::RED);
            printC("  Efficiency: " + std::to_string(powerPlant[i]->getEfficiency()) + "%", Color::MAGENTA);
            printC("  Power Generation: " + std::to_string(powerPlant[i]->getPowerGeneration()) + " watts", Color::BLUE);
            printC("  Raw Generation Capacity: " + std::to_string(powerPlant[i]->getPowerGenerationRaw()) + " watts", Color::WHITE);
        }
    }

    // Water Supply Systems
    printC("------------------------------", Color::GREEN);
    printC("Water Supply Systems:", Color::GREEN);
    printC("------------------------------", Color::GREEN);
    if (waterSupply.empty()) {
        printC("  No water supply systems built yet.", Color::YELLOW);
    } else {
        for (size_t i = 0; i < waterSupply.size(); i++) {
            printC("\nWater Supply System #" + std::to_string(i + 1) + ":", Color::YELLOW);
            printC("  Status: " + std::string(waterSupply[i]->getFunctional() ? "Functional" : "Malfunctioning"),
                   waterSupply[i]->getFunctional() ? Color::GREEN : Color::RED);
            printC("  Efficiency: " + std::to_string(waterSupply[i]->getEfficiency()) + "%", Color::MAGENTA);
            printC("  Water Generation: " + std::to_string(waterSupply[i]->getWaterGeneration()) + " liters", Color::BLUE);
            printC("  Raw Generation Capacity: " + std::to_string(waterSupply[i]->getWaterGenerationRaw()) + " liters", Color::WHITE);
        }
    }

    // Waste Management Facilities
    printC("------------------------------", Color::GREEN);
    printC("Waste Management Facilities:", Color::GREEN);
    printC("------------------------------", Color::GREEN);
    if (wasteManagement.empty()) {
        printC("  No waste management facilities built yet.", Color::YELLOW);
    } else {
        for (size_t i = 0; i < wasteManagement.size(); i++) {
            printC("\nWaste Management Facility #" + std::to_string(i + 1) + ":", Color::YELLOW);
            printC("  Status: " + std::string(wasteManagement[i]->getFunctional() ? "Functional" : "Malfunctioning"),
                   wasteManagement[i]->getFunctional() ? Color::GREEN : Color::RED);
            printC("  Efficiency: " + std::to_string(wasteManagement[i]->getEfficiency()) + "%", Color::MAGENTA);
            printC("  Waste Collection: " + std::to_string(wasteManagement[i]->getWasteCollection()) + " kg", Color::BLUE);
            printC("  Raw Collection Capacity: " + std::to_string(wasteManagement[i]->getWasteCollectionRaw()) + " kg", Color::WHITE);
        }
    }

    printC("\n================================\n", Color::CYAN);
}

void Government::promptForNewApartment(int sector, Citizen* c) {
    std::cout << "No current apartment building available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y") {
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
            a->addCitizen(c);
            cityGrowth->addBuilding(a, sector);
            Road r(5, "Industrial"); 
            roadSystemAdapter->addRoute(r);
        }
    }
    else {
        std::cout << "No apartment building created" << std::endl;
    }
}

// Function to prompt for creating a new house
void Government::promptForNewHouse(int sector, Citizen* c) {
    std::cout << "No current house available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y") {
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
            h->addCitizen(c);
            cityGrowth->addBuilding(h, sector);
            Road r(5, "Commercial"); 
            roadSystemAdapter->addRoute(r);
        }
    }
    else {
        std::cout << "No house created" << std::endl;
    }
}

void Government::promptForNewMansion(int sector, Citizen* c) {
    std::cout << "No current mansion available. Create a new one? (Type Y or N)" << std::endl;
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y") {
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
            m->addCitizen(c);
            cityGrowth->addBuilding(m, sector);
            Road r(5,"Government"); 
            roadSystemAdapter->addRoute(r);
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

    if (choice == "Y" || choice == "y") {
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
            Road r(5, f->getType()); 
            roadSystemAdapter->addRoute(r);
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

    if (choice == "Y" || choice == "y") {
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
            Road r(5, w->getType()); 
            roadSystemAdapter->addRoute(r);
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

    if (choice == "Y" || choice == "y") {
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
            Road r(5, p->getType()); 
            roadSystemAdapter->addRoute(r);
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

    if (choice == "Y" || choice == "y") {
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
            Road r(5, s->getType()); 
            roadSystemAdapter->addRoute(r);
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

    if (choice == "Y" || choice == "y") {
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
            Road r(5, o->getType()); 
            roadSystemAdapter->addRoute(r);
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

    if (choice == "Y" || choice == "y") {
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
            Road r(5, m->getType()); 
            roadSystemAdapter->addRoute(r);
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

    if (choice == "Y" || choice == "y") {
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
            Road r(5, sc->getType()); 
            roadSystemAdapter->addRoute(r);
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

    if (choice == "Y" || choice == "y") {
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
            Road r(5, h->getType()); 
            roadSystemAdapter->addRoute(r);
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

    if (choice == "Y" || choice == "y") {
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
            Road r(5, g->getType()); 
            roadSystemAdapter->addRoute(r);
        }
    }
    else {
        std::cout << "No government building created" << std::endl;
    }
}

