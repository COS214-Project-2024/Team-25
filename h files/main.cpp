// #ifndef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #ifndef TESTING
#include <iostream>
#include "Government.h"

// #include "Utilities.h"
// #include "Resources.h"
// #include "CityGrowth.h"
// #include "TaxSystem.h"
// #include "Buildings.h"

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

void printC(const std::string &text, Color color)
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

bool validateIntInput(int value, int lowerBound, int upperBound)
{
    return (value >= lowerBound && value <= upperBound);
}

int safeIntInput(int lowerBound, int upperBound)
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

void gameLoop()
{
    Government *government = new Government();
    bool game = true;
    int actionCount = 0;

    printC("Select which difficulty to play on:", Color::CYAN);
    printC("    1. Easy", Color::GREEN);
    printC("    2. Medium", Color::YELLOW);
    printC("    3. Hard", Color::RED);
    int difficulty = safeIntInput(1, 3);

    government->setDifficulty(difficulty);
    government->printUtilitiesDetails();
    government->printresources();
    government->printSec();
    government->printSatisfaction();

    while (game)
    {

        if (government->avgSatisfaction() >= 100)
        {
            printC("YOU HAVE WON BASED ON SATISFACTION", Color::GREEN);
            government->printUtilitiesDetails();
            government->printresources();
            government->printSec();
            government->printSatisfaction();
            break;
        }

        if (government->avgSatisfaction() <= 0)
        {
            printC("YOU HAVE LOST BASED ON SATISFACTION", Color::RED);
            government->printUtilitiesDetails();
            government->printresources();
            government->printSec();
            government->printSatisfaction();
            break;
        }

        if (government->getBudget() >= 300000)
        {
            printC("YOU HAVE WON BASED ON CASH", Color::GREEN);
            government->printUtilitiesDetails();
            government->printresources();
            government->printSec();
            government->printSatisfaction();
            break;
        }

        if (government->getDebt() <= -50000)
        {
            printC("YOU HAVE LOST BASED ON DEBT", Color::RED);
            government->printUtilitiesDetails();
            government->printresources();
            government->printSec();
            government->printSatisfaction();
            break;
        }

        // Check for natural disaster (1/6 chance)
        if (actionCount != 0 && (rand() % 6) == 0)
        {
            printC("A natural disaster has struck!", Color::RED);
            government->naturalDisaster();
            government->printSatisfaction();
        }

        // Display available actions
        printC("Choose an action to perform:", Color::CYAN);
        printC("    1. Create Building", Color::WHITE);
        printC("    2. Create Utility", Color::WHITE);
        printC("    3. Upgrade Transport", Color::WHITE);
        printC("    4. Clean city", Color::WHITE);
        printC("    5. Increase Materials", Color::WHITE);
        printC("    6. Change Tax Strategy", Color::WHITE);
        printC("    7. Repair Utilities", Color::WHITE);
        printC("    8. Create Citizens", Color::WHITE);
        printC("    9. EXIT", Color::RED);

        // Validate action input
        int action = safeIntInput(1, 9);

        if (actionCount != 0 && (rand() % 4) == 0 && action != 3 && action != 9)
        {
            government->insuffcientTransporrt();
        }

        // Perform selected action
        int numCitizen = 0;
        switch (action)
        {
        case 1:
            printC("Creating a building...", Color::GREEN);
            government->createBuilding();
            government->printSatisfaction();
            break;
        case 2:
            printC("Creating a utility...", Color::GREEN);
            government->createUtility();
            government->printSatisfaction();
            break;
        case 3:
            printC("Upgrading transport...", Color::GREEN);
            government->upgradeTransport();
            government->printSatisfaction();
            break;
        case 4:
            printC("Cleaning city and distributing water...", Color::GREEN);
            government->cleanCity();
            government->printSatisfaction();
            break;
        case 5:
            printC("Increasing materials...", Color::GREEN);
            government->increaseMaterials();
            government->printSatisfaction();
            break;
        case 6:
            printC("Changing tax strategy...", Color::GREEN);
            government->changeTaxStartegy();
            government->printSatisfaction();
            break;
        case 7:
            printC("Repairing utilities...", Color::GREEN);
            government->repairUtilities();
            government->printSatisfaction();
            break;
        case 8:
            printC("Creating new citizens...", Color::GREEN);
            printC("Enter how many citizens you would like to create: ", Color::CYAN);
            printC("NOTE! All the citizens you create now will be added to the same sector, and will have the same job. ", Color::RED);
            numCitizen = safeIntInput(1, 10);
            government->createCitizen(numCitizen);
            government->printSatisfaction();
            break;
        case 9:
            game = false;
            break;
        }

        if (action != 9)
        {

            printC("See a more detailed report:", Color::CYAN);
            printC("    1. Print Utilities", Color::WHITE);
            printC("    2. Print Resources", Color::WHITE);
            printC("    3. Print Sector", Color::WHITE);
            printC("    4. Print Satisfaction", Color::WHITE);
            printC("    5. Print All", Color::WHITE);
            printC("    6. Skip", Color::WHITE);

            int choice = safeIntInput(1, 6);
            std::string s = "";
            switch (choice)
            {
            case 1:
                government->printUtilitiesDetails();
                std::cout << "Press any button to continue." << std::endl;
                cin >> s;
                break;
            case 2:
                government->printresources();
                std::cout << "Press any button to continue." << std::endl;
                cin >> s;
                break;
            case 3:
                government->printSec();
                std::cout << "Press any button to continue." << std::endl;
                cin >> s;
                break;
            case 4:
                government->printSatisfaction();
                std::cout << "Press any button to continue." << std::endl;
                cin >> s;
                break;
            case 5:
                government->printUtilitiesDetails();
                government->printresources();
                government->printSec();
                government->printSatisfaction();
                std::cout << "Press any button to continue." << std::endl;
                cin >> s;
                break;
            case 6:
                break;
            }

            actionCount++;
            if (actionCount >= 8)
            {
                printC("Collecting annual taxes...", Color::YELLOW);
                government->taxCitizens();
                actionCount = 0;
                printC("A year has passed!", Color::CYAN);
            }
        }
    }

    delete government;
    government = nullptr;
}

int main(int argc, char const *argv[])
{
    setvbuf(stdout, nullptr, _IONBF, 0);
    gameLoop();
    return 0;
}
// #endif

// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include <iostream>

// #include "Utilities.h"
// #include "Resources.h"
// #include "CityGrowth.h"
// #include "TaxSystem.h"
// #include "Buildings.h"

// void testCitizenFactories() {
//     // Creating factories for each type of worker
//     ComWorkerFactory comFactory;
//     GovernmentWorkerFactory govFactory;
//     IndWorkerFactory indFactory;

//     // Using factories to create citizens with specified workplaces
//     Citizen* commercialWorker1 = comFactory.createCitizen("Shop");
//     Citizen* governmentWorker1 = govFactory.createCitizen("School");
//     Citizen* industrialWorker1 = indFactory.createCitizen("Factory");

//     // Displaying information for each type of worker with specific workplace
//     std::cout << "\nTesting citizens with specified workplaces:" << std::endl;
//     commercialWorker1->displayInfo();
//     governmentWorker1->displayInfo();
//     industrialWorker1->displayInfo();

//     // Using factories to create citizens with random workplaces
//     Citizen* commercialWorker2 = comFactory.createCitizen();
//     Citizen* governmentWorker2 = govFactory.createCitizen();
//     Citizen* industrialWorker2 = indFactory.createCitizen();

//     // Displaying information for each type of worker with random workplace
//     std::cout << "\nTesting citizens with random workplaces:" << std::endl;
//     commercialWorker2->displayInfo();
//     governmentWorker2->displayInfo();
//     industrialWorker2->displayInfo();

//     // Clean up memory
//     delete commercialWorker1;
//     delete governmentWorker1;
//     delete industrialWorker1;
//     delete commercialWorker2;
//     delete governmentWorker2;
//     delete industrialWorker2;
// }

// int main(int argc, char const *argv[])
// {
//     testCitizenFactories();
//     std::cout << "\n\n";

//      Energy* energy = Energy::getInstance();
//      Water* water = Water::getInstance();
//      Concrete* concrete = Concrete::getInstance();
//      Wood* wood = Wood::getInstance();
//      Steel* steel = Steel::getInstance();

//      concrete->increase();
//      wood->increase();
//      steel->increase();

//      Utility* powerPlant = new FunctionalPowerPlant(HYDRO);
//     //  powerPlant = powerPlant->mulfunction();
//     // commented out because of error

//     /* --------------------------- Testing CityGrowth --------------------------- */
//     std::cout << "\n\n";

//     CityGrowth* citygrowth = new CityGrowth();

//     std::cout << citygrowth->printSectors();

//     // CitySector* citySector0 = new CitySector();
//     // citygrowth->addSector(citySector0);
//     // CitySector* citySector1 = new CitySector();
//     // citygrowth->addSector(citySector1);

//     for (int i = 0; i < 5; i++) {
//         CitySector* newSector = new CitySector();
//         citygrowth->addSector(newSector);
//     }

//     std::cout << citygrowth->printSectors();

//     for (int i = 0; i < 18; i++) {
//         // House(std::string name, int numRooms, int m_squared, float value,
//         // int numBedrooms, int numBathrooms, int kitchenSize)
//         House* newHouse = new House("0", 1, 500, 100000, 1, 1, 10, 2);
//         CommercialWorker* commercialWorker = new CommercialWorker();
//         // make sure the new houses only go into the valid sector positions
//         newHouse->addCitizen(commercialWorker);

//         citygrowth->addBuilding(newHouse,i % citygrowth->getTotalSectorCount());
//     }
//     Apartment* newApartment = new Apartment("0", 1, 500, 100000, 1, 1, 20, 2);
//     citygrowth->addBuilding(newApartment, 2);

//     std::cout << citygrowth->printSectors();

//     // House(std::string name, int numRooms, int m_squared, float value, int
//     // numBedrooms, int numBathrooms, int kitchenSize) House* house0 = new
//     // House("0", 1, 500, 100000, 1, 1, 20); citygrowth->addBuilding(house0,
//     // 0);

//     /* ------------------------------ Testing Taxes ----------------------------- */
//     TaxStrategy* flatStrat = new FlatTaxStrategy();
//     TaxStrategy* progStrat = new ProgressiveTaxStrategy();
//     TaxSystem* taxSystem = new TaxSystem();

//     std::cout << "Using FlatTaxStrategy:\n";
//     // taxSystem->setTaxStrategy(flatStrat);
//     taxSystem->collectTax(citygrowth);

//     std::cout <<"\n";
//     taxSystem->toggleStrategy();
//     taxSystem->toggleStrategy();
//     std::cout <<"\n";

//     std::cout << "Using ProgressiveTaxStrategy:\n";
//     taxSystem->setTaxStrategy(progStrat);
//     // taxSystem->toggleStrategy();
//     taxSystem->collectTax(citygrowth);

//     std::cout << "\n";
//     std::cout << "Total collected taxes: " << taxSystem->getCollectedTaxes() << "\n";
//     std::cout << "\n";
//     std::cout << "Total collected taxes: " << taxSystem->getCollectedTaxes() << "\n";

//     /* -------------------------------------------------------------------------- */

//      House* myHouse = new House("Dream House", 5, 120, 250000.0f, 3, 2, 5, 9);

//      ComWorkerFactory comWorkerFactory;
//      // Add citizens (workers) to the house

//      myHouse->addCitizen(comWorkerFactory.createCitizen("Shop"));
//      myHouse->addCitizen(comWorkerFactory.createCitizen("Shop"));
//      myHouse->addCitizen(comWorkerFactory.createCitizen("Mall"));
//      myHouse->addCitizen(comWorkerFactory.createCitizen("Office"));
//      myHouse->addCitizen(comWorkerFactory.createCitizen("Office"));
//      myHouse->addCitizen(comWorkerFactory.createCitizen("Mall"));

//      myHouse->displayCitizens();

//      Warehouse* myWarehouse =
//          new Warehouse("Warehouse 2", 5, 120, 250000.0f, 3, 200);

//      CitySector* newSector1 = new CitySector();
//      citygrowth->addSector(newSector1);

//      citygrowth->addBuilding(myHouse, 5);

//      CitySector* newSector2 = new CitySector();
//      citygrowth->addSector(newSector2);
//      citygrowth->addBuilding(myWarehouse, 6);

//      std::cout << "\n" << citygrowth->printSectors();
//      citygrowth->printSectorsCitizens(6);
//      std::cout << "\n";
//      citygrowth->printSectorsCitizens(7);
//      std::cout << "\n";
//      citygrowth->printSectorsCitizens(8);

//      delete myHouse;
//      delete myWarehouse;
//      delete newSector1;
//      delete newSector2;

//      return 0;
// }
