#include "Government.h"

Government::Government()
{
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

Government::~Government()
{
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
    for (auto &water : waterSupply)
    {
        delete water;
    }
    for (auto &waste : wasteManagement)
    {
        delete waste;
    }
    for (auto &plant : powerPlant)
    {
        delete plant;
    }
}

enum class Color
{
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    RESET
};

inline void printC(const std::string &text, Color color)
{
    // ANSI escape codes for text colors
    switch (color)
    {
    case Color::RED:
        std::cout << "\033[31m";
        break;
    case Color::GREEN:
        std::cout << "\033[32m";
        break;
    case Color::YELLOW:
        std::cout << "\033[33m";
        break;
    case Color::BLUE:
        std::cout << "\033[34m";
        break;
    case Color::MAGENTA:
        std::cout << "\033[35m";
        break;
    case Color::CYAN:
        std::cout << "\033[36m";
        break;
    case Color::WHITE:
        std::cout << "\033[37m";
        break;
    case Color::RESET:
        std::cout << "\033[0m";
        break;
    }
    std::cout << text;
    std::cout << "\033[0m\n";
}

inline bool validateIntInput(int value, int lowerBound, int upperBound)
{
    return (value >= lowerBound && value <= upperBound);
}

inline int safeIntInput(int lowerBound, int upperBound)
{
    int input;
    while (true)
    {
        printC("Enter an integer between " + std::to_string(lowerBound) + " and " + std::to_string(upperBound) + ": ", Color::CYAN);

        if (std::cin >> input)
        {
            if (validateIntInput(input, lowerBound, upperBound))
            {
                printC("Valid input received.", Color::GREEN);
                return input;
            }
            printC("Input out of range. Try again.", Color::RED);
        }
        else
        {
            // Clear error flags and ignore invalid input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printC("Invalid input. Please enter an integer.", Color::RED);
        }
    }
}

void Government::createBuilding()
{
    printC("Select which type of building you would like to create (1-3):", Color::CYAN);
    printC("    1. Industrial", Color::WHITE);
    printC("    2. Commercial", Color::WHITE);
    printC("    3. Institutional", Color::WHITE);
    int type = safeIntInput(1, 3);

    std::string name;
    printC("Enter the name of the building: ", Color::CYAN);
    std::cin >> name;

    printC("Enter the sector you want the building (0-" + std::to_string(cityGrowth->getTotalSectorCount() - 1) + "):", Color::CYAN);
    int sector = safeIntInput(0, cityGrowth->getTotalSectorCount() - 1);

    Building *b = nullptr;
    bool check = false;

    switch (type)
    {
    case 1:
    { // Industrial
        int carbonFootprint, capacity;
        printC("Select which type of industrial building would you like to create (1-3):", Color::CYAN);
        printC("    1. Factory", Color::WHITE);
        printC("    2. Warehouse", Color::WHITE);
        printC("    3. Plant", Color::WHITE);
        int type2 = safeIntInput(1, 3);

        printC("Enter carbon footprint: ", Color::CYAN);
        carbonFootprint = safeIntInput(0, 50);

        printC("Enter capacity: ", Color::CYAN);
        capacity = safeIntInput(0, 50);

        switch (type2)
        {
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

    case 2:
    { // Commercial
        int capacity, numFloors;
        printC("Select which type of commercial building would you like to create (1-3):", Color::CYAN);
        printC("    1. Shop", Color::WHITE);
        printC("    2. Office", Color::WHITE);
        printC("    3. Mall", Color::WHITE);
        int type2 = safeIntInput(1, 3);

        printC("Enter capacity: ", Color::CYAN);
        capacity = safeIntInput(0, 50);

        printC("Enter number of floors: ", Color::CYAN);
        numFloors = safeIntInput(0, 50);

        switch (type2)
        {
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

    case 3:
    { // Institutional
        int capacity, numFloors;
        printC("Select which type of institutional building you would like to create (1-3):", Color::CYAN);
        printC("    1. School", Color::WHITE);
        printC("    2. Hospital", Color::WHITE);
        printC("    3. Government Building", Color::WHITE);
        int type2 = safeIntInput(1, 3);

        printC("Enter capacity: ", Color::CYAN);
        capacity = safeIntInput(0, 50);

        printC("Enter number of floors: ", Color::CYAN);
        numFloors = safeIntInput(0, 50);

        switch (type2)
        {
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

    if (b)
    {
        b->build();
        if (b->getBuilt())
        {
            check = cityGrowth->addBuilding(b, sector);
            //they dont like working
            this->updateSatisfaction(-5);
            
            Road r(5, b->getType());
            roadSystemAdapter->addRoute(r);
        }
        if (check)
        {
            printC("Successfully added a building!", Color::GREEN);
        }
        else
        {
            printC("Failed to add a building!", Color::RED);
            delete b;
            b = nullptr;
        }
    }
    else
    {
        printC("Something went quite wrong!", Color::RED);
    }
}

void Government::createUtility()
{
    printC("Select which type of utility you would like to create:", Color::CYAN);
    printC("    1. PowerPlant", Color::WHITE);
    printC("    2. Water Supply", Color::WHITE);
    printC("    3. Waste Management Plant", Color::WHITE);
    int type = safeIntInput(1, 3);

    switch (type)
    {
    case 1:
    {
        printC("Select which type of Power Plant you would like to create:", Color::CYAN);
        printC("    1. Hydro", Color::WHITE);
        printC("    2. Coal", Color::WHITE);
        printC("    3. Wind", Color::WHITE);
        printC("    4. Solar", Color::WHITE);
        int powerplant = safeIntInput(1, 4);

        if (powerplant >= 1 && powerplant <= 4)
        {
            printC("Creating Power Plant...", Color::CYAN);
            PowerPlant *plant = new FunctionalPowerPlant(static_cast<powerPlants>(powerplant - 1), true);
            if (plant->getPowerGenerationRaw() > 0)
            {
                powerPlant.push_back(plant);
                if(powerplant == 2){
                    updateSatisfaction(-3);
                }else{
                    updateSatisfaction(3);
                }
                updateBudget(-5000);
                printC("Power Plant created successfully! (Cost: 5000)", Color::GREEN);
            }
            else
            {
                delete plant;
                printC("Failed to create Power Plant: No power generation capacity!", Color::RED);
            }
        }
        else
        {
            printC("Invalid Power Plant type selected!", Color::RED);
        }
        break;
    }
    case 2:
    {
        printC("Creating Water Supply...", Color::CYAN);
        WaterSupply *water = new FunctionalWaterSupply(true);
        if (water->getWaterGenerationRaw() > 0)
        {
            waterSupply.push_back(water);
            updateSatisfaction(3);
            updateBudget(-5000);
            printC("Water Supply created successfully! (Cost: 5000)", Color::GREEN);
        }
        else
        {
            delete water;
            printC("Failed to create Water Supply: No water generation capacity!", Color::RED);
        }
        break;
    }
    case 3:
    {
        printC("Creating Waste Management Plant...", Color::CYAN);
        WasteManagement *waste = new FunctionalWasteManagement(true);
        if (waste->getWasteCollectionRaw() > 0)
        {
            wasteManagement.push_back(waste);
            updateSatisfaction(3);
            updateBudget(-5000);
            printC("Waste Management created successfully! (Cost: 5000)", Color::GREEN);
        }
        else
        {
            delete waste;
            printC("Failed to create Waste Management Plant: No waste collection capacity!", Color::RED);
        }
        break;
    }
    default:
        printC("Invalid selection!", Color::RED);
        break;
    }
}

void Government::increaseMaterials()
{
    printC("Select which type of resource you would like to obtain:", Color::CYAN);
    printC("    1. Wood", Color::WHITE);
    printC("    2. Steel", Color::WHITE);
    printC("    3. Concrete", Color::WHITE);
    printC("    4. All", Color::WHITE);
    int type = safeIntInput(1, 4);

    switch (type)
    {
    case 1:
        wood->increase();
        updateBudget(-10000);
        printC("Wood resources increased! (Cost: 10000)", Color::GREEN);
        break;
    case 2:
        steel->increase();
        updateBudget(-6000);
        printC("Steel resources increased!  (Cost: 6000)", Color::GREEN);
        break;
    case 3:
        concrete->increase();
        updateBudget(-10000);
        printC("Concrete resources increased! (Cost: 10000)", Color::GREEN);
        break;
    case 4:
        wood->increase();
        concrete->increase();
        steel->increase();
        updateBudget(-26000);
        printC("All resources increased! (Cost: 26000)", Color::GREEN);
        break;
    default:
        break;
    }
}

void Government::naturalDisaster()
{
    printC("Oh no, there was a natural disaster!", Color::RED);

    // Random PowerPlants
    std::random_device rd;
    std::mt19937 gen(rd());
    float totCounter = 0;
    std::uniform_int_distribution<> numDist(0, powerPlant.size());
    int numMalfunctions = numDist(gen);
    int counter = 0;
    for (int i = 0; i < numMalfunctions; i++)
    {
        std::uniform_int_distribution<> indexDist(0, powerPlant.size() - 1);
        int randomIndex = indexDist(gen);
        if (powerPlant[randomIndex]->getFunctional())
        {
            PowerPlant *p = powerPlant[randomIndex]->mulfunction();
            PowerPlant *plantToDelete = powerPlant[randomIndex];
            powerPlant.erase(powerPlant.begin() + randomIndex);
            delete plantToDelete;
            powerPlant.push_back(p);
            counter++;
        }
    }
    printC(std::to_string(counter) + " PowerPlants have malfunctioned.", Color::MAGENTA);
    totCounter += counter;
    // Random waterSupply
    std::random_device rd2;
    std::mt19937 gen2(rd2());

    std::uniform_int_distribution<> numDist2(0, waterSupply.size());
    numMalfunctions = numDist2(gen2);
    counter = 0;
    for (int i = 0; i < numMalfunctions; i++)
    {
        std::uniform_int_distribution<> indexDist(0, waterSupply.size() - 1);
        int randomIndex = indexDist(gen2);
        if (waterSupply[randomIndex]->getFunctional())
        {
            WaterSupply *w = waterSupply[randomIndex]->mulfunction();
            WaterSupply *supplyToDelete = waterSupply[randomIndex];
            waterSupply.erase(waterSupply.begin() + randomIndex);
            delete supplyToDelete;
            waterSupply.push_back(w);
            counter++;
        }
    }
    printC(std::to_string(counter) + " Water Supplies have malfunctioned.", Color::MAGENTA);
    totCounter += counter;
    // Random wasteManagement
    std::random_device rd3;
    std::mt19937 gen3(rd3());

    std::uniform_int_distribution<> numDist3(0, wasteManagement.size());
    numMalfunctions = numDist3(gen3);
    counter = 0;
    for (int i = 0; i < numMalfunctions; i++)
    {
        // Get random index
        std::uniform_int_distribution<> indexDist(0, wasteManagement.size() - 1);
        int randomIndex = indexDist(gen3);
        if (wasteManagement[randomIndex]->getFunctional())
        {
            WasteManagement *w = wasteManagement[randomIndex]->mulfunction();
            WasteManagement *wasteToDelete = wasteManagement[randomIndex];
            wasteManagement.erase(wasteManagement.begin() + randomIndex);
            delete wasteToDelete;
            wasteManagement.push_back(w);
            counter++;
        }
    }
    printC(std::to_string(counter) + " Waste Management Plants have malfunctioned.", Color::MAGENTA);
    totCounter += counter;

    updateSatisfaction(-totCounter);
}

void Government::upgradeTransport()
{
    monthlyRoutines->executueTransport();
    updateBudget(-5000);
    printC("Transport Upgraded (Cost: 5000)", Color::GREEN);
    updateSatisfaction(5);
}

void Government::cleanCity()
{
    float i = 0;
    for (WasteManagement *w : wasteManagement)
    {
        if (w->getFunctional())
        {
            w->collect();
            w->recycle();
            i += 1;
        }
        else
        {
            w->collect();
            w->recycle();
            i += 0.5;
        }
    }

    for (WaterSupply *ws : waterSupply)
    {
        if (ws->getFunctional())
        {
            ws->distribute();
            i += 1;
        }
        else
        {
            ws->distribute();
            i += 0.5;
        }
    }
    updateBudget(-3000);
    printC("Cleaned the city (Cost: 3000)", Color::GREEN);
    printC("Citizen satisfaction increased by: " + std::to_string(i), Color::MAGENTA);
    updateSatisfaction(i);
}

void Government::taxCitizens()
{
    taxSystem->collectTax(cityGrowth);
    printC("Citizen satisfaction decreased by: 5" , Color::RED);
    updateSatisfaction(-5);
}

void Government::changeTaxStartegy()
{
    taxSystem->toggleStrategy();
}

void Government::repairUtilities()
{
    printC("Select which utilities to repair:", Color::CYAN);
    printC("    1. Power Plants", Color::WHITE);
    printC("    2. Water Supplies", Color::WHITE);
    printC("    3. Waste Management", Color::WHITE);
    int u = safeIntInput(1, 3);
    int c = 0;
    switch (u)
    {
    case 1:
        for (auto it = powerPlant.begin(); it != powerPlant.end();)
        {
            if (!(*it)->getFunctional())
            {
                PowerPlant *repairedPlant = (*it)->repair();
                if (repairedPlant->getFunctional())
                {
                    c++;
                    delete *it;
                }

                if (repairedPlant)
                {
                    *it = repairedPlant;
                    ++it;
                }
                else
                {
                    it = powerPlant.erase(it);
                }
            }
            else
            {
                ++it;
            }
        }
        break;

    case 2:
        for (auto it = waterSupply.begin(); it != waterSupply.end();)
        {
            if (!(*it)->getFunctional())
            {
                WaterSupply *repairedSupply = (*it)->repair();
                if (repairedSupply->getFunctional())
                {
                    c++;
                    delete *it;
                }

                if (repairedSupply)
                {
                    *it = repairedSupply;
                    ++it;
                }
                else
                {
                    it = waterSupply.erase(it);
                }
            }
            else
            {
                ++it;
            }
        }
        break;

    case 3:
        for (auto it = wasteManagement.begin(); it != wasteManagement.end();)
        {
            if (!(*it)->getFunctional())
            {
                WasteManagement *repairedWaste = (*it)->repair();
                if (repairedWaste->getFunctional())
                {
                    c++;
                    delete *it;
                }

                if (repairedWaste)
                {
                    *it = repairedWaste;
                    ++it;
                }
                else
                {
                    it = wasteManagement.erase(it);
                }
            }
            else
            {
                ++it;
            }
        }
        break;

    default:
        printC("Invalid utility selection.", Color::RED);
        break;
    }
    updateBudget(-1000 * c);
    printC("Citizen satisfaction increased by: "+ std::to_string(c), Color::GREEN);
    updateSatisfaction(c);

}

void Government::createCitizen(int numCitizens)
{
    printC("Select which work sector your citizens should work in:", Color::CYAN);
    printC("  1. Industrial", Color::WHITE);
    printC("  2. Commercial", Color::WHITE);
    printC("  3. Institutional", Color::WHITE);
    int type = safeIntInput(1, 3);
    int type2;
    printC("Enter the sector you want the citizens to work in: (Select from 0-" + std::to_string(cityGrowth->getTotalSectorCount() - 1) + ")", Color::CYAN);
    int sector = safeIntInput(0, cityGrowth->getTotalSectorCount() - 1);

    CitizenFactory *factory = nullptr;

    switch (type)
    {
    case 1:
    { // Industrial
        factory = new IndWorkerFactory();
        printC("Select which type of industrial building would you like your citizens to work at:", Color::CYAN);
        std::cout << "  1. Factory" << std::endl;
        std::cout << "  2. Warehouse" << std::endl;
        std::cout << "  3. Plant" << std::endl;
        std::cin >> type2;

        // Create all citizens of the same type
        std::string buildingType;
        if (type2 == 1)
            buildingType = "Factory";
        else if (type2 == 2)
            buildingType = "Warehouse";
        else if (type2 == 3)
            buildingType = "Plant";

        for (int i = 0; i < numCitizens; i++)
        {
            bool assigned = false;
            CitySector *s = cityGrowth->getSectors()[sector];
            Citizen *c = factory->createCitizen(buildingType);

            // Try to assign to existing work building
            for (auto *b : s->getBuildings())
            {
                if (b->getType() == buildingType && b->getLeftOverCapacity() > 0)
                {
                    b->addCitizen(c);
                    printC("Citizen added to " + buildingType, Color::GREEN);
                    assigned = true;
                    break;
                }
            }

            // If no existing building has space, create new one
            if (!assigned)
            {
                if (type2 == 1)
                    promptForNewFactory(sector);
                else if (type2 == 2)
                    promptForNewWarehouse(sector);
                else if (type2 == 3)
                    promptForNewPlant(sector);

                for (auto *b : s->getBuildings())
                {
                    if (b->getType() == buildingType && b->getLeftOverCapacity() > 0)
                    {
                        updateSatisfaction(-5);
                        b->addCitizen(c);
                        printC("Citizen added to " + buildingType, Color::GREEN);
                        assigned = true;
                        break;
                    }
                }
            }

            if (assigned)
            {
                bool housingAssigned = false;
                for (auto *b : s->getBuildings())
                {
                    if (b->getType() == "Apartment" && b->getLeftOverCapacity() > 0)
                    {
                        b->addCitizen(c);
                        printC("Citizen added to " + buildingType, Color::GREEN);
                        housingAssigned = true;
                        break;
                    }
                }

                // If no apartment found, create new one
                if (!housingAssigned)
                {
                    promptForNewApartment(sector, c);
                    for (auto *b : s->getBuildings())
                    {
                        if (b->getType() == "Apartment" && b->getLeftOverCapacity() > 0)
                        {
                            updateSatisfaction(5);
                            b->addCitizen(c);
                            printC("Citizen added to " + buildingType, Color::GREEN);
                            housingAssigned = true;
                            break;
                        }
                    }
                }
            }
            else
            {
                delete c;
                c = nullptr;
            }
        }
        delete factory;
        break;
    }

    case 2:
    { // Commercial
        factory = new ComWorkerFactory();
        printC("Select which type of commercial building would you like your citizens to work at:", Color::CYAN);
        std::cout << "  1. Shop" << std::endl;
        std::cout << "  2. Office" << std::endl;
        std::cout << "  3. Mall" << std::endl;
        std::cin >> type2;

        std::string buildingType;
        if (type2 == 1)
            buildingType = "Shop";
        else if (type2 == 2)
            buildingType = "Office";
        else if (type2 == 3)
            buildingType = "Mall";

        for (int i = 0; i < numCitizens; i++)
        {
            bool assigned = false;
            CitySector *s = cityGrowth->getSectors()[sector];
            Citizen *c = factory->createCitizen(buildingType);
            // Try to assign to existing work building
            for (auto *b : s->getBuildings())
            {
                if (b->getType() == buildingType && b->getLeftOverCapacity() > 0)
                {
                    b->addCitizen(c);
                    printC("Citizen added to " + buildingType, Color::GREEN);
                    assigned = true;
                    break;
                }
            }

            // If no existing building has space, create new one
            if (!assigned)
            {
                if (type2 == 1)
                    promptForNewShop(sector);
                else if (type2 == 2)
                    promptForNewOffice(sector);
                else if (type2 == 3)
                    promptForNewMall(sector);
                for (auto *b : s->getBuildings())
                {
                    if (b->getType() == buildingType && b->getLeftOverCapacity() > 0)
                    {
                        updateSatisfaction(-5);
                        b->addCitizen(c);
                        printC("Citizen added to " + buildingType, Color::GREEN);
                        assigned = true;
                        break;
                    }
                }
            }

            if (assigned)
            {
                bool housingAssigned = false;
                for (auto *b : s->getBuildings())
                {
                    if (b->getType() == "House" && b->getLeftOverCapacity() > 0)
                    {
                        b->addCitizen(c);
                        printC("Citizen added to " + buildingType, Color::GREEN);
                        housingAssigned = true;
                        break;
                    }
                }

                // If no house found, create new one
                if (!housingAssigned)
                {
                    promptForNewHouse(sector, c);
                    for (auto *b : s->getBuildings())
                    {
                        if (b->getType() == "House" && b->getLeftOverCapacity() > 0)
                        {
                            updateSatisfaction(5);
                            b->addCitizen(c);
                            printC("Citizen added to " + buildingType, Color::GREEN);
                            housingAssigned = true;
                            break;
                        }
                    }
                }
            }
            else
            {
                delete c;
                c = nullptr;
            }
        }
        delete factory;
        break;
    }

    case 3:
    { // Institutional
        factory = new GovernmentWorkerFactory();
        printC("Select which type of institutional building would you like your citizens to work at:", Color::CYAN);
        std::cout << "  1. School" << std::endl;
        std::cout << "  2. Hospital" << std::endl;
        std::cout << "  3. Government Building" << std::endl;
        std::cin >> type2;

        std::string buildingType;
        if (type2 == 1)
            buildingType = "School";
        else if (type2 == 2)
            buildingType = "Hospital";
        else if (type2 == 3)
            buildingType = "GovernmentBuilding";

        for (int i = 0; i < numCitizens; i++)
        {
            bool assigned = false;
            CitySector *s = cityGrowth->getSectors()[sector];
            Citizen *c = factory->createCitizen(buildingType);
            // Try to assign to existing work building
            for (auto *b : s->getBuildings())
            {
                if (b->getType() == buildingType && b->getLeftOverCapacity() > 0)
                {
                    b->addCitizen(c);
                    printC("Citizen added to " + buildingType, Color::GREEN);
                    assigned = true;
                    break;
                }
            }

            // If no existing building has space, create new one
            if (!assigned)
            {
                if (type2 == 1)
                    promptForNewSchool(sector);
                else if (type2 == 2)
                    promptForNewHospital(sector);
                else if (type2 == 3)
                    promptForNewGovernmentBuilding(sector);
                for (auto *b : s->getBuildings())
                {
                    if (b->getType() == buildingType && b->getLeftOverCapacity() > 0)
                    {
                        updateSatisfaction(-5);
                        b->addCitizen(c);
                        printC("Citizen added to " + buildingType, Color::GREEN);
                        assigned = true;
                        break;
                    }
                }
            }

            // Try to assign to existing mansion
            if (assigned)
            {
                bool housingAssigned = false;
                for (auto *b : s->getBuildings())
                {
                    if (b->getType() == "Mansion" && b->getLeftOverCapacity() > 0)
                    {
                        b->addCitizen(c);
                        printC("Citizen added to " + buildingType, Color::GREEN);
                        housingAssigned = true;
                        break;
                    }
                }

                // If no mansion found, create new one
                if (!housingAssigned)
                {
                    promptForNewMansion(sector, c);
                    for (auto *b : s->getBuildings())
                    {
                        if (b->getType() == "Mansion" && b->getLeftOverCapacity() > 0)
                        {
                            updateSatisfaction(5);
                            b->addCitizen(c);
                            printC("Citizen added to " + buildingType, Color::GREEN);
                            housingAssigned = true;
                            break;
                        }
                    }
                }
            }
            else
            {
                delete c;
                c = nullptr;
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

float Government::avgSatisfaction()
{
    std::vector<CitySector *> sectors = cityGrowth->getSectors();
    float total = 0;
    float count = 0.0;
    for (int i = 0; i < sectors.size(); i++)
    {
        CitySector *sector = sectors.at(i);
        std::vector<Building *> block = sector->getBuildings();
        for (int j = 0; j < block.size(); j++)
        {
            if (block.at(j) != nullptr && block.at(j)->getBuildingType() != "House" && block.at(j)->getBuildingType() != "Mansion" && block.at(j)->getBuildingType() != "Apartment")
            {
                std::vector<Citizen *> citizens = block.at(j)->getCitizens();
                for (int k = 0; k < citizens.size(); k++)
                {
                    total += citizens.at(k)->getSatisfaction();
                    count += 1.0;
                }
            }
        }
    }
    return total / count;
}

void Government::updateSatisfaction(float amt)
{
    std::vector<CitySector *> sectors = cityGrowth->getSectors();
    float total = 0;
    float count = 0.0;
    for (int i = 0; i < sectors.size(); i++)
    {
        CitySector *sector = sectors.at(i);
        std::vector<Building *> block = sector->getBuildings();
        for (int j = 0; j < block.size(); j++)
        {
            if (block.at(j) != nullptr && block.at(j)->getBuildingType() != "House" && block.at(j)->getBuildingType() != "Mansion" && block.at(j)->getBuildingType() != "Apartment")
            {
                std::vector<Citizen *> citizens = block.at(j)->getCitizens();
                for (int k = 0; k < citizens.size(); k++)
                {
                    citizens.at(k)->changeSatisfaction(amt);
                }
            }
        }
    }
}

void Government::updateBudget(double amt)
{
    budget->setCash(budget->getCash() + amt);
}

void Government::insuffcientTransporrt()
{
    printC("There is insuffcient transport for citizens to go to work", Color::MAGENTA);
    updateSatisfaction(-5);
    printC("Citizen satisfaction decreased by: 5" , Color::RED);
}

void Government::setDifficulty(int difficulty)
{
    CitizenFactory *residentialFactory = nullptr;
    CitizenFactory *commercialFactory = nullptr;
    CitizenFactory *industrialFactory = nullptr;
    CitizenFactory *institutionalFactory = nullptr;

    commercialFactory = new ComWorkerFactory();
    industrialFactory = new IndWorkerFactory();
    institutionalFactory = new GovernmentWorkerFactory();

    int k = cityGrowth->getTotalSectorCount();
    for (int i = 0; i < k; i++)
    {
        Building *f = new Factory("Factory 1", 5, 500, 10000.00, 100, 5);
        Building *a = new Apartment("Apartment 1", 2, 50, 2000.00, 1, 1, 5, 2);
        Road r(5, "Industrial");
        roadSystemAdapter->addRoute(r);
        for (int j = 0; j < 3; j++)
        {
            Citizen *c = industrialFactory->createCitizen("Factory");
            f->addCitizen(c);
            a->addCitizen(c);
        }
        cityGrowth->addBuilding(f, i);
        cityGrowth->addBuilding(a, i);

        Building *p = new Plant("Plant 1", 5, 500, 10000.00, 100, 5);
        Building *a1 = new Apartment("Apartment 2", 2, 50, 2000.00, 1, 1, 5, 2);
        Road r2(5, "Industrial");
        roadSystemAdapter->addRoute(r2);
        for (int j = 0; j < 4; j++)
        {
            Citizen *c = industrialFactory->createCitizen("Plant");
            p->addCitizen(c);
            a1->addCitizen(c);
        }
        cityGrowth->addBuilding(p, i);
        cityGrowth->addBuilding(a1, i);

        Building *s = new Shop("Shop 1", 1, 50, 1000.00, 10, 1, 1);
        Building *h = new House("House 1", 2, 50, 100.00, 2, 2, 5, 3);
        Road com(5, "Commercial");
        roadSystemAdapter->addRoute(com);
        for (int n = 0; n < 4; n++)
        {
            Citizen *c = commercialFactory->createCitizen("Shop");
            s->addCitizen(c);
            h->addCitizen(c);
        }

        cityGrowth->addBuilding(s, i);
        cityGrowth->addBuilding(h, i);

        Building *m1 = new Mall("Mall 1", 1, 50, 1000.00, 10, 1, 1);
        Building *h1 = new House("House 1", 2, 50, 100.00, 2, 2, 7, 3);
        Road com1(5, "Commercial");
        roadSystemAdapter->addRoute(com1);
        for (int n = 0; n < 6; n++)
        {
            Citizen *c = commercialFactory->createCitizen("Mall");
            m1->addCitizen(c);
            h1->addCitizen(c);
        }

        cityGrowth->addBuilding(m1, i);
        cityGrowth->addBuilding(h1, i);

        Building *g = new GovernmentBuilding("Government Building 1", 5, 500, 10000.00, 50, 2);
        Building *m = new Mansion("Mansion 1", 6, 500, 2000.00, 6, 6, 10, false);

        Road in(5, "Instatutional");
        roadSystemAdapter->addRoute(in);
        for (int l = 0; l < 8; l++)
        {
            Citizen *c = institutionalFactory->createCitizen("GovernmentBuilding");
            g->addCitizen(c);
            m->addCitizen(c);
        }

        cityGrowth->addBuilding(g, i);
        cityGrowth->addBuilding(m, i);
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

        budget->setCash(200000.00);

        for (int i = 0; i < 4; i++)
        {
            // Create and validate PowerPlant
            FunctionalPowerPlant *plant = new FunctionalPowerPlant(static_cast<powerPlants>(i), true);
            if (plant->getPowerGenerationRaw() > 0)
            {
                powerPlant.push_back(plant);
            }
            else
            {
                delete plant;
            }

            // Create and validate WaterSupply
            FunctionalWaterSupply *water = new FunctionalWaterSupply(true);
            if (water->getWaterGenerationRaw() > 0)
            {
                waterSupply.push_back(water);
            }
            else
            {
                delete water;
            }

            // Create and validate WasteManagement
            FunctionalWasteManagement *waste = new FunctionalWasteManagement(true);
            if (waste->getWasteCollectionRaw() > 0)
            {
                wasteManagement.push_back(waste);
            }
            else
            {
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
            FunctionalPowerPlant *plant = new FunctionalPowerPlant(static_cast<powerPlants>(i), true);
            if (plant->getPowerGenerationRaw() > 0)
            {
                powerPlant.push_back(plant);
            }
            else
            {
                delete plant;
            }

            // Create and validate WaterSupply
            FunctionalWaterSupply *water = new FunctionalWaterSupply(true);
            if (water->getWaterGenerationRaw() > 0)
            {
                waterSupply.push_back(water);
            }
            else
            {
                delete water;
            }

            // Create and validate WasteManagement
            FunctionalWasteManagement *waste = new FunctionalWasteManagement(true);
            if (waste->getWasteCollectionRaw() > 0)
            {
                wasteManagement.push_back(waste);
            }
            else
            {
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
        wood->setKilo(5000);
        concrete->setKilo(5000);
        steel->setKilo(5000);
        budget->setCash(50000.00);
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

void Government::printSec()
{
    std::cout << cityGrowth->printSectors();
}

void Government::printSatisfaction()
{
    printC("---------------------------------", Color::YELLOW);
    printC("|     Satisfaction: " + std::to_string(std::round(avgSatisfaction())) + "   |", Color::YELLOW);
    printC("---------------------------------", Color::YELLOW);
    printC("|     Budget:       " + std::to_string(std::round(getBudget())) + "   |", Color::YELLOW);
    printC("---------------------------------", Color::YELLOW);
    printC("|     Debt:         " + std::to_string(std::round(getDebt())) + "   |", Color::YELLOW);
    printC("---------------------------------", Color::YELLOW);
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
    if (powerPlant.empty())
    {
        printC("  No power plants built yet.", Color::YELLOW);
    }
    else
    {
        for (size_t i = 0; i < powerPlant.size(); i++)
        {
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
    if (waterSupply.empty())
    {
        printC("  No water supply systems built yet.", Color::YELLOW);
    }
    else
    {
        for (size_t i = 0; i < waterSupply.size(); i++)
        {
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
    if (wasteManagement.empty())
    {
        printC("  No waste management facilities built yet.", Color::YELLOW);
    }
    else
    {
        for (size_t i = 0; i < wasteManagement.size(); i++)
        {
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

void Government::promptForNewApartment(int sector, Citizen *c)
{
    printC("No current apartment building available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);
        
        printC("Enter number of floors: ", Color::CYAN);
        int floors = safeIntInput(1, 5);

        Building *a = new Apartment(name, capacity * capacity, 5 * capacity * capacity, capacity * 5000, capacity, capacity, capacity, 2);
        a->build();
        if (a->getBuilt())
        {
            // a->addCitizen(c);
            cityGrowth->addBuilding(a, sector);
            Road r(5, "Industrial");
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete a;
            a = nullptr;
        }
    }
    else
    {
        printC("No apartment building created", Color::RED);
    }
}

// Function to prompt for creating a new house
void Government::promptForNewHouse(int sector, Citizen *c)
{
    printC("No current house available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);
        
        printC("Enter number of floors: ", Color::CYAN);
        int floors = safeIntInput(1, 5);

        Building *h = new House(name, capacity * capacity, 10 * capacity * capacity, capacity * 10000, capacity, capacity, capacity, capacity * 10);
        h->build();
        if (h->getBuilt())
        {
            // h->addCitizen(c);
            cityGrowth->addBuilding(h, sector);
            Road r(5, "Commercial");
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete h;
            h = nullptr;
        }
    }
    else
    {
        printC("No house created", Color::RED);
    }
}

void Government::promptForNewMansion(int sector, Citizen *c)
{
    printC("No current mansion available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);
        
        printC("Enter number of floors: ", Color::CYAN);
        int floors = safeIntInput(1, 5);

        Building *m = new Mansion(name, capacity * capacity + 5, 15 * capacity * capacity, capacity * 15000, capacity + 3, capacity + 2, capacity, true);
        m->build();
        if (m->getBuilt())
        {
            // m->addCitizen(c);
            cityGrowth->addBuilding(m, sector);
            Road r(5, "Government");
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete m;
            m = nullptr;
        }
    }
    else
    {
        printC("No mansion created", Color::RED);
    }
}

void Government::promptForNewFactory(int sector)
{
    printC("No current factory available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter carbon footprint: ", Color::CYAN);
        int carbonFootprint = safeIntInput(1, 100);

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);

        Building *f = new Factory(name, capacity * 2, capacity * 4, carbonFootprint * 1000, carbonFootprint, capacity);
        f->build();
        if (f->getBuilt())
        {
            cityGrowth->addBuilding(f, sector);
            Road r(5, f->getType());
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete f;
            f = nullptr;
        }
    }
    else
    {
        printC("No factory created", Color::RED);
    }
}

void Government::promptForNewWarehouse(int sector)
{
    printC("No current warehouse available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);

        Building *w = new Warehouse(name, capacity * 3, capacity * 5, capacity * 3000, capacity, 2);
        w->build();
        if (w->getBuilt())
        {
            cityGrowth->addBuilding(w, sector);
            Road r(5, w->getType());
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete w;
            w = nullptr;
        }
    }
    else
    {
        printC("No warehouse created", Color::RED);
    }
}

void Government::promptForNewPlant(int sector)
{
    printC("No current plant available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter carbon footprint: ", Color::CYAN);
        int carbonFootprint = safeIntInput(1, 100);

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);

        Building *p = new Plant(name, capacity * 3, capacity * 5, carbonFootprint * 1000, carbonFootprint, capacity);
        p->build();
        if (p->getBuilt())
        {
            cityGrowth->addBuilding(p, sector);
            Road r(5, p->getType());
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete p;
            p = nullptr;
        }
    }
    else
    {
        printC("No plant created", Color::RED);
    }
}

void Government::promptForNewShop(int sector)
{
    printC("No current shop available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);
        
        printC("Enter number of floors: ", Color::CYAN);
        int floors = safeIntInput(1, 5);

        Building *s = new Shop(name, capacity * 2, capacity * 5, capacity * 1000, capacity, floors, 3);
        s->build();
        if (s->getBuilt())
        {
            cityGrowth->addBuilding(s, sector);
            Road r(5, s->getType());
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete s;
            s = nullptr;
        }
    }
    else
    {
        printC("No shop created", Color::RED);
    }
}

void Government::promptForNewOffice(int sector)
{
    printC("No current office available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);
        
        printC("Enter number of floors: ", Color::CYAN);
        int floors = safeIntInput(1, 5);

        Building *o = new Office(name, capacity * 4, capacity * 15, capacity * 8000, capacity, floors, 5);
        o->build();
        if (o->getBuilt())
        {
            cityGrowth->addBuilding(o, sector);
            Road r(5, o->getType());
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete o;
            o = nullptr;
        }
    }
    else
    {
        printC("No office created", Color::RED);
    }
}

void Government::promptForNewMall(int sector)
{
    printC("No current mall available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);
        
        printC("Enter number of floors: ", Color::CYAN);
        int floors = safeIntInput(1, 8);

        Building *m = new Mall(name, capacity * 6, capacity * 20, capacity * 15000, capacity, floors, 8);
        m->build();
        if (m->getBuilt())
        {
            cityGrowth->addBuilding(m, sector);
            Road r(5, m->getType());
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete m;
            m = nullptr;
        }
    }
    else
    {
        printC("No mall created", Color::RED);
    }
}

void Government::promptForNewSchool(int sector)
{
    printC("No current school available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);
        
        printC("Enter number of floors: ", Color::CYAN);
        int floors = safeIntInput(1, 5);

        Building *sc = new School(name, capacity * 5, capacity * 15, capacity * 20000, capacity, floors);
        sc->build();
        if (sc->getBuilt())
        {
            cityGrowth->addBuilding(sc, sector);
            Road r(5, sc->getType());
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete sc;
            sc = nullptr;
        }
    }
    else
    {
        printC("No school created", Color::RED);
    }
}

void Government::promptForNewHospital(int sector)
{
    printC("No current hospital available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);
        
        printC("Enter number of floors: ", Color::CYAN);
        int floors = safeIntInput(1, 10);

        Building *h = new Hospital(name, capacity * 10, capacity * 20, capacity * 50000, capacity, floors);
        h->build();
        if (h->getBuilt())
        {
            cityGrowth->addBuilding(h, sector);
            Road r(5, h->getType());
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete h;
            h = nullptr;
        }
    }
    else
    {
        printC("No hospital created", Color::RED);
    }
}

void Government::promptForNewGovernmentBuilding(int sector)
{
    printC("No current government building available. Create a new one? (Type Y or N)", Color::CYAN);
    std::string choice;
    std::cin >> choice;

    if (choice == "Y" || choice == "y")
    {
        std::string name;
        printC("Enter the name of the building: ", Color::CYAN);
        std::cin >> name;

        printC("Enter capacity: ", Color::CYAN);
        int capacity = safeIntInput(1, 50);
        
        printC("Enter number of floors: ", Color::CYAN);
        int floors = safeIntInput(1, 8);

        Building *g = new GovernmentBuilding(name, capacity * 8, capacity * 25, capacity * 40000, capacity, floors);
        g->build();
        if (g->getBuilt())
        {
            cityGrowth->addBuilding(g, sector);
            Road r(5, g->getType());
            roadSystemAdapter->addRoute(r);
        }
        else
        {
            delete g;
            g = nullptr;
        }
    }
    else
    {
        printC("No government building created", Color::RED);
    }
}
