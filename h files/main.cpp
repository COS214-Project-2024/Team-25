#include <iostream>
#include <unistd.h>

#include "Government.h"
#include "NewTerminal.h"

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
    std::ostringstream message;

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
            printC("YOU HAVE WON BASED ON SATISFACTION", Color::GREEN);
            break;
        }

        if (government->avgSatisfaction() <= 0)
        {
            printC("YOU HAVE LOST BASED ON SATISFACTION", Color::RED);
            government->printUtilitiesDetails();
            government->printresources();
            government->printSec();
            government->printSatisfaction();
            printC("YOU HAVE LOST BASED ON SATISFACTION", Color::RED);
            break;
        }

        if (government->getBudget() >= 300000)
        {
            printC("YOU HAVE WON BASED ON CASH", Color::GREEN);
            government->printUtilitiesDetails();
            government->printresources();
            government->printSec();
            government->printSatisfaction();
            printC("YOU HAVE WON BASED ON CASH", Color::GREEN);
            break;
        }

        if (government->getDebt() <= -50000 || government->getBudget() <= -50000)
        {
            printC("YOU HAVE LOST BASED ON DEBT", Color::RED);
            government->printUtilitiesDetails();
            government->printresources();
            government->printSec();
            government->printSatisfaction();
            printC("YOU HAVE LOST BASED ON DEBT", Color::RED);
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
            actionCount++;

            writeMessageToFile(" ");
            sleep(1.1);

            message.str("");
            message.clear();

            message << "---------------------------\n";
            message << "Tax collection progress " << to_string(actionCount) << "/8\n";
            message << "---------------------------\n";

            // message << "\n\n (imagine City stats being here)\n";
            message << government->getSatisfactionDetails();
            message << "\n";
            message << government->getSec();
            message << government->getUtilitiesDetails();
            writeMessageToFile(message.str());
            // sendMessageToTerminal(message.str());

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

            // actionCount++;

        // message.str("");
        // message.clear();

        // message << "---------------------------\n";
        // message << "Tax collection progress " << to_string(actionCount) << "/8\n";
        // message << "---------------------------\n";

        // // message << "\n\n (imagine City stats being here)\n";
        // message << government->getSatisfactionDetails();
        // message << "\n";
        // message << government->getSec();
        // writeMessageToFile(message.str());
        // // sendMessageToTerminal(message.str());

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
    // gameLoop();
    // return 0;

    std::ostringstream message;

    openNewTerminal();
    writeMessageToFile(" ");  // Write message to temp file

    message << "---Welcome message can be displayed---\n\n";
    message << "---Game rules and goals can be listed---\n\n";


    // message << "---------\n";
    // message << "| Day 0" << " |\n";
    // message << "---------\n";
    // message << "\033[32m this is green\033[0m";

    writeMessageToFile(message.str());  // Write message to temp file
    // sendMessageToTerminal(message.str());

    gameLoop();

    return 0;
}
