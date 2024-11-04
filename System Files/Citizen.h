#ifndef CITIZEN_H
#define CITIZEN_H

#include <string>
using namespace std;

/**
 * @class Citizen
 * @brief Abstract base class representing a citizen.
 *
 * The Citizen class serves as a base class for various types of citizens, encapsulating common properties
 * such as residence, workplace, and satisfaction levels. This class defines the interface for all citizen types.
 */
class Citizen {
private:
    string residence;    ///< Residence of the citizen
    string workplace;    ///< Workplace of the citizen
    string type;         ///< Type of the citizen (e.g., worker type)
    float satisfaction;  ///< Satisfaction level of the citizen

public:
    /**
     * @brief Default constructor for Citizen.
     */
    Citizen();

    /**
     * @brief Virtual destructor for Citizen.
     */
    virtual ~Citizen() = default;

    /**
     * @brief Sets the properties of the citizen.
     * @param type The type of the citizen.
     * @param residence The residence of the citizen.
     * @param workplace The workplace of the citizen.
     */
    virtual void setCitizen(string type, string residence, string workplace);

    /**
     * @brief Gets the type of the citizen.
     * @return The type of the citizen as a string.
     */
    virtual std::string getType();

    /**
     * @brief Gets the residence of the citizen.
     * @return The residence of the citizen as a string.
     */
    virtual string getResidence();

    /**
     * @brief Gets the workplace of the citizen.
     * @return The workplace of the citizen as a string.
     */
    virtual string getWorkplace();

    /**
     * @brief Gets the satisfaction level of the citizen.
     * @return The satisfaction level as a float.
     */
    virtual float getSatisfaction();

    /**
     * @brief Pure virtual function to display citizen information.
     * This function must be implemented by derived classes.
     */
    virtual void displayInfo() = 0;

    /**
     * @brief Changes the satisfaction level of the citizen.
     * @param amt The amount to change satisfaction by (can be positive or negative).
     */
    void changeSatisfaction(float amt);
};



/**
 * @class CommercialWorker
 * @brief Class representing a commercial worker, a type of citizen.
 *
 * The CommercialWorker class inherits from Citizen and represents a worker in the commercial sector.
 */
class CommercialWorker : public Citizen {
public:
    /**
     * @brief Default constructor for CommercialWorker.
     */
    CommercialWorker();

    /**
     * @brief Constructor for CommercialWorker with specified workplace.
     * @param workplace The workplace of the commercial worker.
     */
    CommercialWorker(string workplace);

    /**
     * @brief Displays information about the commercial worker.
     */
    virtual void displayInfo();
};



/**
 * @class GovernmentWorker
 * @brief Class representing a government worker, a type of citizen.
 *
 * The GovernmentWorker class inherits from Citizen and represents a worker in the government sector.
 */
class GovernmentWorker : public Citizen {
public:
    /**
     * @brief Default constructor for GovernmentWorker.
     */
    GovernmentWorker();

    /**
     * @brief Constructor for GovernmentWorker with specified workplace.
     * @param workplace The workplace of the government worker.
     */
    GovernmentWorker(string workplace);

    /**
     * @brief Displays information about the government worker.
     */
    virtual void displayInfo();
};



/**
 * @class IndustrialWorker
 * @brief Class representing an industrial worker, a type of citizen.
 *
 * The IndustrialWorker class inherits from Citizen and represents a worker in the industrial sector.
 */
class IndustrialWorker : public Citizen {
public:
    /**
     * @brief Default constructor for IndustrialWorker.
     */
    IndustrialWorker();

    /**
     * @brief Constructor for IndustrialWorker with specified workplace.
     * @param workplace The workplace of the industrial worker.
     */
    IndustrialWorker(string workplace);

    /**
     * @brief Displays information about the industrial worker.
     */
    virtual void displayInfo();
};



/**
 * @class CitizenFactory
 * @brief Abstract base class for creating citizens.
 *
 * The CitizenFactory class defines the interface for factories that create different types of citizens.
 */
class CitizenFactory {
private:
    Citizen* citizen;  ///< Pointer to a Citizen object

public:
    /**
     * @brief Virtual destructor for CitizenFactory.
     */
    virtual ~CitizenFactory() = default;

    /**
     * @brief Pure virtual function to create a citizen.
     * @return A pointer to a newly created Citizen object.
     */
    virtual Citizen* createCitizen() = 0;

    /**
     * @brief Pure virtual function to create a citizen with a specified workplace.
     * @param workplace The workplace for the new citizen.
     * @return A pointer to a newly created Citizen object.
     */
    virtual Citizen* createCitizen(string workplace) = 0;
};



/**
 * @class ComWorkerFactory
 * @brief Factory class for creating CommercialWorker objects.
 *
 * The ComWorkerFactory class inherits from CitizenFactory and implements the methods to create
 * CommercialWorker instances.
 */
class ComWorkerFactory : public CitizenFactory {
public:
    /**
     * @brief Creates a new CommercialWorker object.
     * @return A pointer to the newly created CommercialWorker object.
     */
    Citizen* createCitizen() override;

    /**
     * @brief Creates a new CommercialWorker object with specified workplace.
     * @param workplace The workplace for the new CommercialWorker.
     * @return A pointer to the newly created CommercialWorker object.
     */
    Citizen* createCitizen(string workplace);
};



/**
 * @class GovernmentWorkerFactory
 * @brief Factory class for creating GovernmentWorker objects.
 *
 * The GovernmentWorkerFactory class inherits from CitizenFactory and implements the methods to create
 * GovernmentWorker instances.
 */
class GovernmentWorkerFactory : public CitizenFactory {
public:
    /**
     * @brief Creates a new GovernmentWorker object.
     * @return A pointer to the newly created GovernmentWorker object.
     */
    Citizen* createCitizen() override;

    /**
     * @brief Creates a new GovernmentWorker object with specified workplace.
     * @param workplace The workplace for the new GovernmentWorker.
     * @return A pointer to the newly created GovernmentWorker object.
     */
    Citizen* createCitizen(string workplace);
};



/**
 * @class IndWorkerFactory
 * @brief Factory class for creating IndustrialWorker objects.
 *
 * The IndWorkerFactory class inherits from CitizenFactory and implements the methods to create
 * IndustrialWorker instances.
 */
class IndWorkerFactory : public CitizenFactory {
public:
    /**
     * @brief Creates a new IndustrialWorker object.
     * @return A pointer to the newly created IndustrialWorker object.
     */
    Citizen* createCitizen() override;

    /**
     * @brief Creates a new IndustrialWorker object with specified workplace.
     * @param workplace The workplace for the new IndustrialWorker.
     * @return A pointer to the newly created IndustrialWorker object.
     */
    Citizen* createCitizen(string workplace);
};

#endif
