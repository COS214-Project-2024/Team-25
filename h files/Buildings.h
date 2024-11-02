#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>
#include <iostream>
#include "Citizen.h"
#include "Resources.h"

/**
 * @class Building
 * @brief Abstract base class representing a generic building.
 *
 * The Building class serves as a base class for various types of buildings (e.g., Residential, Commercial).
 * It includes essential attributes such as name, type, number of rooms, area, value, and lists of citizens.
 * Derived classes must implement the pure virtual functions to define specific behaviors.
 */
class Building {
protected:
    std::string name;         ///< Name of the building
    std::string type;         ///< Type of the building (e.g., Residential, Commercial)
    int numRooms;             ///< Number of rooms in the building
    int m_squared;            ///< Area of the building in square meters
    float value;              ///< Value of the building
    bool built = false;       ///< Flag indicating if the building is built
    Budget* budget;           ///< Pointer to a Budget object for managing building finances
    Concrete* concrete;       ///< Pointer to a Concrete object for building materials
    Steel* steel;             ///< Pointer to a Steel object for building materials
    Wood* wood;               ///< Pointer to a Wood object for building materials
    std::vector<Citizen*> citizens; ///< List of citizens associated with the building

public:
    /**
     * @brief Constructor to initialize a Building object.
     * @param name Name of the building.
     * @param numRooms Number of rooms in the building.
     * @param m_squared Area of the building in square meters.
     * @param value Value of the building.
     * @param type Type of the building.
     */
    Building(std::string name, int numRooms, int m_squared, float value, std::string type);

    /**
     * @brief Virtual destructor for the Building class.
     */
    virtual ~Building();

    /**
     * @brief Gets the list of citizens in the building.
     * @return A vector of Citizen pointers.
     */
    std::vector<Citizen*> getCitizens() const { return citizens; }

    /**
     * @brief Pure virtual function to build the building.
     *
     * Must be implemented by derived classes to define specific building construction behavior.
     */
    virtual void build() = 0;

    /**
     * @brief Pure virtual function to clone the building object.
     * @return A pointer to a new Building object that is a clone of the current instance.
     */
    virtual Building* clone() = 0;

    /**
     * @brief Displays the list of citizens in the building.
     *
     * This function can be overridden by derived classes to provide specific display behavior.
     */
    virtual void displayCitizens();

    /**
     * @brief Pure virtual function to add a citizen to the building.
     * @param human Pointer to the Citizen to be added.
     *
     * Derived classes must implement this function to handle adding citizens.
     */
    virtual void addCitizen(Citizen* human) = 0;

    /**
     * @brief Pure virtual function to get the leftover capacity of the building.
     * @return The number of additional citizens the building can accommodate.
     *
     * Derived classes must implement this function to define capacity limits.
     */
    virtual int getLeftOverCapacity() = 0;

    /**
     * @brief Pure virtual function to get the type of the building.
     * @return The type of the building as a string.
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Gets the name of the building.
     * @return The name of the building as a string.
     */
    std::string getName();

    /**
     * @brief Gets the building's type description.
     * @return The type of the building as a string.
     */
    std::string getBuildingType();

    /**
     * @brief Checks if the building is built.
     * @return True if the building is built, false otherwise.
     */
    bool getBuilt() const { return built; }

    /**
     * @brief Renovates the building, updating any necessary properties.
     *
     * This function can be overridden by derived classes to provide specific renovation behaviors.
     */
    void renovate();
};







/******* RESIDENTIAL *******/

/**
 * @class Residential
 * @brief Abstract class representing a residential building.
 *
 * The Residential class is derived from the Building class and serves as a base class for different types
 * of residential buildings. It includes attributes specific to residential buildings, such as bedrooms,
 * bathrooms, and capacity.
 */
class Residential : public Building {
protected:
    int numBedrooms;    ///< Number of bedrooms in the residential building
    int numBathrooms;   ///< Number of bathrooms in the residential building
    int capacity;       ///< Maximum occupancy capacity of the building

public:
    /**
     * @brief Constructor for a Residential building.
     * @param name Name of the building.
     * @param numRooms Number of rooms in the building.
     * @param m_squared Area of the building in square meters.
     * @param value Value of the building.
     * @param numBedrooms Number of bedrooms.
     * @param numBathrooms Number of bathrooms.
     * @param capacity Maximum capacity of the building.
     * @param type Type of the building.
     */
    Residential(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, std::string type);

    /**
     * @brief Pure virtual function to build the residential building.
     */
    virtual void build() = 0;

    /**
     * @brief Pure virtual function to clone the residential building.
     * @return A pointer to a new Residential object that is a clone of the current instance.
     */
    virtual Residential* clone() = 0;

    /**
     * @brief Adds a citizen to the residential building.
     * @param human Pointer to the Citizen to be added.
     */
    void addCitizen(Citizen* human) override;

    /**
     * @brief Displays the list of citizens in the residential building.
     */
    void displayCitizens() override;

    /**
     * @brief Gets the remaining capacity of the residential building.
     * @return The number of additional citizens the building can accommodate.
     */
    int getLeftOverCapacity() override;

    /**
     * @brief Gets the maximum capacity of the residential building.
     * @return The capacity of the building.
     */
    int getCapacity();

    /**
     * @brief Gets the list of citizens in the residential building.
     * @return A vector of Citizen pointers.
     */
    std::vector<Citizen*> getCitizens();

    /**
     * @brief Pure virtual function to get the type of the residential building.
     * @return The type of the building as a string.
     */
    virtual std::string getType() const = 0;
};



/**
 * @class House
 * @brief Class representing a house, a specific type of residential building.
 *
 * The House class inherits from Residential and includes attributes specific to houses, such as kitchen size.
 */
class House : public Residential {
private:
    int kitchenSize;    ///< Size of the kitchen in the house

public:
    /**
     * @brief Constructor for the House class.
     * @param name Name of the house.
     * @param numRooms Number of rooms in the house.
     * @param m_squared Area of the house in square meters.
     * @param value Value of the house.
     * @param numBedrooms Number of bedrooms in the house.
     * @param numBathrooms Number of bathrooms in the house.
     * @param capacity Maximum capacity of the house.
     * @param kitchenSize Size of the kitchen in the house.
     */
    House(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, int kitchenSize);

    /**
     * @brief Builds the house.
     */
    void build() override;

    /**
     * @brief Clones the House object.
     * @return A pointer to a new House object that is a clone of the current instance.
     */
    House* clone() override;

    /**
     * @brief Gets the type of the building (House).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};



/**
 * @class Apartment
 * @brief Class representing an apartment, a specific type of residential building.
 *
 * The Apartment class inherits from Residential and includes attributes specific to apartments, such as the number of floors.
 */
class Apartment : public Residential {
private:
    int numFloors;      ///< Number of floors in the apartment building

public:
    /**
     * @brief Constructor for the Apartment class.
     * @param name Name of the apartment.
     * @param numRooms Number of rooms in the apartment.
     * @param m_squared Area of the apartment in square meters.
     * @param value Value of the apartment.
     * @param numBedrooms Number of bedrooms in the apartment.
     * @param numBathrooms Number of bathrooms in the apartment.
     * @param capacity Maximum capacity of the apartment.
     * @param numFloors Number of floors in the apartment building.
     */
    Apartment(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, int numFloors);

    /**
     * @brief Builds the apartment.
     */
    void build() override;

    /**
     * @brief Clones the Apartment object.
     * @return A pointer to a new Apartment object that is a clone of the current instance.
     */
    Apartment* clone() override;

    /**
     * @brief Gets the type of the building (Apartment).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};



/**
 * @class Mansion
 * @brief Class representing a mansion, a specific type of residential building.
 *
 * The Mansion class inherits from Residential and includes attributes specific to mansions, such as a water feature.
 */
class Mansion : public Residential {
private:
    bool waterFeature;  ///< Indicates if the mansion has a water feature (e.g., pool or fountain)

public:
    /**
     * @brief Constructor for the Mansion class.
     * @param name Name of the mansion.
     * @param numRooms Number of rooms in the mansion.
     * @param m_squared Area of the mansion in square meters.
     * @param value Value of the mansion.
     * @param numBedrooms Number of bedrooms in the mansion.
     * @param numBathrooms Number of bathrooms in the mansion.
     * @param capacity Maximum capacity of the mansion.
     * @param waterFeature Indicates if the mansion has a water feature.
     */
    Mansion(std::string name, int numRooms, int m_squared, float value, int numBedrooms, int numBathrooms, int capacity, bool waterFeature);

    /**
     * @brief Builds the mansion.
     */
    void build() override;

    /**
     * @brief Clones the Mansion object.
     * @return A pointer to a new Mansion object that is a clone of the current instance.
     */
    Mansion* clone() override;

    /**
     * @brief Gets the type of the building (Mansion).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};








/******* COMMERCIAL *******/

/**
 * @class Commercial
 * @brief Abstract class representing a commercial building.
 *
 * The Commercial class is derived from the Building class and serves as a base class for various types
 * of commercial buildings. It includes attributes specific to commercial buildings, such as capacity and
 * the number of floors.
 */
class Commercial : public Building {
protected:
    int capacity;    ///< Maximum occupancy capacity of the commercial building
    int numFloors;   ///< Number of floors in the commercial building

public:
    /**
     * @brief Constructor for a Commercial building.
     * @param name Name of the building.
     * @param numRooms Number of rooms in the building.
     * @param m_squared Area of the building in square meters.
     * @param value Value of the building.
     * @param capacity Maximum capacity of the building.
     * @param numFloors Number of floors in the building.
     * @param type Type of the building.
     */
    Commercial(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, std::string type);

    /**
     * @brief Pure virtual function to build the commercial building.
     */
    virtual void build() = 0;

    /**
     * @brief Pure virtual function to clone the commercial building.
     * @return A pointer to a new Commercial object that is a clone of the current instance.
     */
    virtual Commercial* clone() = 0;

    /**
     * @brief Adds a citizen to the commercial building.
     * @param human Pointer to the Citizen to be added.
     */
    void addCitizen(Citizen* human) override;

    /**
     * @brief Displays the list of citizens in the commercial building.
     */
    void displayCitizens() override;

    /**
     * @brief Gets the remaining capacity of the commercial building.
     * @return The number of additional citizens the building can accommodate.
     */
    int getLeftOverCapacity() override;

    /**
     * @brief Pure virtual function to get the type of the commercial building.
     * @return The type of the building as a string.
     */
    virtual std::string getType() const = 0;
};



/**
 * @class Shop
 * @brief Class representing a shop, a specific type of commercial building.
 *
 * The Shop class inherits from Commercial and includes attributes specific to shops, such as the number of storage rooms.
 */
class Shop : public Commercial {
private:
    int storageRooms;    ///< Number of storage rooms in the shop

public:
    /**
     * @brief Constructor for the Shop class.
     * @param name Name of the shop.
     * @param numRooms Number of rooms in the shop.
     * @param m_squared Area of the shop in square meters.
     * @param value Value of the shop.
     * @param capacity Maximum capacity of the shop.
     * @param numFloors Number of floors in the shop.
     * @param storageRooms Number of storage rooms in the shop.
     */
    Shop(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int storageRooms);

    /**
     * @brief Builds the shop.
     */
    void build() override;

    /**
     * @brief Clones the Shop object.
     * @return A pointer to a new Shop object that is a clone of the current instance.
     */
    Shop* clone() override;

    /**
     * @brief Gets the type of the building (Shop).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};




/**
 * @class Office
 * @brief Class representing an office, a specific type of commercial building.
 *
 * The Office class inherits from Commercial and includes attributes specific to offices, such as the number of offices.
 */
class Office : public Commercial {
private:
    int offices;    ///< Number of individual office spaces in the office building

public:
    /**
     * @brief Constructor for the Office class.
     * @param name Name of the office building.
     * @param numRooms Number of rooms in the office building.
     * @param m_squared Area of the office building in square meters.
     * @param value Value of the office building.
     * @param capacity Maximum capacity of the office building.
     * @param numFloors Number of floors in the office building.
     * @param offices Number of individual office spaces in the building.
     */
    Office(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int offices);

    /**
     * @brief Builds the office building.
     */
    void build() override;

    /**
     * @brief Clones the Office object.
     * @return A pointer to a new Office object that is a clone of the current instance.
     */
    Office* clone() override;

    /**
     * @brief Gets the type of the building (Office).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};



/**
 * @class Mall
 * @brief Class representing a mall, a specific type of commercial building.
 *
 * The Mall class inherits from Commercial and includes attributes specific to malls, such as the number of shops.
 */
class Mall : public Commercial {
private:
    int shops;    ///< Number of shops within the mall

public:
    /**
     * @brief Constructor for the Mall class.
     * @param name Name of the mall.
     * @param numRooms Number of rooms in the mall.
     * @param m_squared Area of the mall in square meters.
     * @param value Value of the mall.
     * @param capacity Maximum capacity of the mall.
     * @param numFloors Number of floors in the mall.
     * @param shops Number of shops within the mall.
     */
    Mall(std::string name, int numRooms, int m_squared, float value, int capacity, int numFloors, int shops);

    /**
     * @brief Builds the mall.
     */
    void build() override;

    /**
     * @brief Clones the Mall object.
     * @return A pointer to a new Mall object that is a clone of the current instance.
     */
    Mall* clone() override;

    /**
     * @brief Gets the type of the building (Mall).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};








/******* INDUSTRIAL *******/

/**
 * @class Industrial
 * @brief Abstract class representing an industrial building.
 *
 * The Industrial class is derived from the Building class and serves as a base class for various types
 * of industrial buildings. It includes attributes specific to industrial buildings, such as carbon footprint
 * and capacity.
 */
class Industrial : public Building {
protected:
    int carbonFootprint;  ///< The carbon footprint of the industrial building
    int capacity;         ///< Maximum occupancy capacity of the industrial building

public:
    /**
     * @brief Constructor for an Industrial building.
     * @param name Name of the building.
     * @param numRooms Number of rooms in the building.
     * @param m_squared Area of the building in square meters.
     * @param value Value of the building.
     * @param carbonFootprint The carbon footprint of the building.
     * @param capacity Maximum capacity of the building.
     * @param type Type of the building.
     */
    Industrial(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity, std::string type);

    /**
     * @brief Pure virtual function to build the industrial building.
     */
    virtual void build() = 0;

    /**
     * @brief Pure virtual function to clone the industrial building.
     * @return A pointer to a new Industrial object that is a clone of the current instance.
     */
    virtual Industrial* clone() = 0;

    /**
     * @brief Adds a citizen to the industrial building.
     * @param human Pointer to the Citizen to be added.
     */
    void addCitizen(Citizen* human) override;

    /**
     * @brief Displays the list of citizens in the industrial building.
     */
    void displayCitizens() override;

    /**
     * @brief Gets the remaining capacity of the industrial building.
     * @return The number of additional citizens the building can accommodate.
     */
    int getLeftOverCapacity() override;

    /**
     * @brief Pure virtual function to get the type of the industrial building.
     * @return The type of the building as a string.
     */
    virtual std::string getType() const = 0;
};

/**
 * @class Factory
 * @brief Class representing a factory, a specific type of industrial building.
 *
 * The Factory class inherits from Industrial and represents a building used for manufacturing.
 */
class Factory : public Industrial {
public:
    /**
     * @brief Constructor for the Factory class.
     * @param name Name of the factory.
     * @param numRooms Number of rooms in the factory.
     * @param m_squared Area of the factory in square meters.
     * @param value Value of the factory.
     * @param carbonFootprint The carbon footprint of the factory.
     * @param capacity Maximum capacity of the factory.
     */
    Factory(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity);

    /**
     * @brief Builds the factory.
     */
    void build() override;

    /**
     * @brief Clones the Factory object.
     * @return A pointer to a new Factory object that is a clone of the current instance.
     */
    Factory* clone() override;

    /**
     * @brief Gets the type of the building (Factory).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};

/**
 * @class Warehouse
 * @brief Class representing a warehouse, a specific type of industrial building.
 *
 * The Warehouse class inherits from Industrial and represents a storage facility for goods and materials.
 */
class Warehouse : public Industrial {
public:
    /**
     * @brief Constructor for the Warehouse class.
     * @param name Name of the warehouse.
     * @param numRooms Number of rooms in the warehouse.
     * @param m_squared Area of the warehouse in square meters.
     * @param value Value of the warehouse.
     * @param carbonFootprint The carbon footprint of the warehouse.
     * @param capacity Maximum capacity of the warehouse.
     */
    Warehouse(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity);

    /**
     * @brief Builds the warehouse.
     */
    void build() override;

    /**
     * @brief Clones the Warehouse object.
     * @return A pointer to a new Warehouse object that is a clone of the current instance.
     */
    Warehouse* clone() override;

    /**
     * @brief Gets the type of the building (Warehouse).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};

/**
 * @class Plant
 * @brief Class representing a plant, a specific type of industrial building.
 *
 * The Plant class inherits from Industrial and represents a building used for processing or production.
 */
class Plant : public Industrial {
public:
    /**
     * @brief Constructor for the Plant class.
     * @param name Name of the plant.
     * @param numRooms Number of rooms in the plant.
     * @param m_squared Area of the plant in square meters.
     * @param value Value of the plant.
     * @param carbonFootprint The carbon footprint of the plant.
     * @param capacity Maximum capacity of the plant.
     */
    Plant(std::string name, int numRooms, int m_squared, float value, int carbonFootprint, int capacity);

    /**
     * @brief Builds the plant.
     */
    void build() override;

    /**
     * @brief Clones the Plant object.
     * @return A pointer to a new Plant object that is a clone of the current instance.
     */
    Plant* clone() override;

    /**
     * @brief Gets the type of the building (Plant).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};







/******* INSTITUTIONAL *******/

/**
 * @class Instatutional
 * @brief Abstract class representing an institutional building.
 *
 * The Instatutional class is derived from the Building class and serves as a base class for various types
 * of institutional buildings. It includes attributes specific to institutions, such as capacity.
 */
class Instatutional : public Building {
protected:
    int capacity;  ///< Maximum occupancy capacity of the institutional building

public:
    /**
     * @brief Constructor for an Instatutional building.
     * @param name Name of the building.
     * @param numRooms Number of rooms in the building.
     * @param m_squared Area of the building in square meters.
     * @param value Value of the building.
     * @param capacity Maximum capacity of the building.
     * @param type Type of the building.
     */
    Instatutional(std::string name, int numRooms, int m_squared, float value, int capacity, std::string type);

    /**
     * @brief Pure virtual function to build the institutional building.
     */
    virtual void build() = 0;

    /**
     * @brief Pure virtual function to clone the institutional building.
     * @return A pointer to a new Instatutional object that is a clone of the current instance.
     */
    virtual Instatutional* clone() = 0;

    /**
     * @brief Adds a citizen to the institutional building.
     * @param human Pointer to the Citizen to be added.
     */
    void addCitizen(Citizen* human) override;

    /**
     * @brief Displays the list of citizens in the institutional building.
     */
    void displayCitizens() override;

    /**
     * @brief Gets the remaining capacity of the institutional building.
     * @return The number of additional citizens the building can accommodate.
     */
    int getLeftOverCapacity() override;

    /**
     * @brief Pure virtual function to get the type of the institutional building.
     * @return The type of the building as a string.
     */
    virtual std::string getType() const = 0;
};

/**
 * @class School
 * @brief Class representing a school, a specific type of institutional building.
 *
 * The School class inherits from Instatutional and represents an educational institution with multiple floors.
 */
class School : public Instatutional {
private:
    int numfloors;  ///< Number of floors in the school

public:
    /**
     * @brief Constructor for the School class.
     * @param name Name of the school.
     * @param numRooms Number of rooms in the school.
     * @param m_squared Area of the school in square meters.
     * @param value Value of the school.
     * @param capacity Maximum capacity of the school.
     * @param numfloors Number of floors in the school.
     */
    School(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors);

    /**
     * @brief Builds the school.
     */
    void build() override;

    /**
     * @brief Clones the School object.
     * @return A pointer to a new School object that is a clone of the current instance.
     */
    School* clone() override;

    /**
     * @brief Gets the type of the building (School).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};

/**
 * @class Hospital
 * @brief Class representing a hospital, a specific type of institutional building.
 *
 * The Hospital class inherits from Instatutional and represents a medical facility with multiple floors.
 */
class Hospital : public Instatutional {
private:
    int numfloors;  ///< Number of floors in the hospital

public:
    /**
     * @brief Constructor for the Hospital class.
     * @param name Name of the hospital.
     * @param numRooms Number of rooms in the hospital.
     * @param m_squared Area of the hospital in square meters.
     * @param value Value of the hospital.
     * @param capacity Maximum capacity of the hospital.
     * @param numfloors Number of floors in the hospital.
     */
    Hospital(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors);

    /**
     * @brief Builds the hospital.
     */
    void build() override;

    /**
     * @brief Clones the Hospital object.
     * @return A pointer to a new Hospital object that is a clone of the current instance.
     */
    Hospital* clone() override;

    /**
     * @brief Gets the type of the building (Hospital).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};

/**
 * @class GovernmentBuilding
 * @brief Class representing a government building, a specific type of institutional building.
 *
 * The GovernmentBuilding class inherits from Instatutional and represents a building used for government offices, with multiple floors.
 */
class GovernmentBuilding : public Instatutional {
private:
    int numfloors;  ///< Number of floors in the government building

public:
    /**
     * @brief Constructor for the GovernmentBuilding class.
     * @param name Name of the government building.
     * @param numRooms Number of rooms in the building.
     * @param m_squared Area of the building in square meters.
     * @param value Value of the building.
     * @param capacity Maximum capacity of the building.
     * @param numfloors Number of floors in the building.
     */
    GovernmentBuilding(std::string name, int numRooms, int m_squared, float value, int capacity, int numfloors);

    /**
     * @brief Builds the government building.
     */
    void build() override;

    /**
     * @brief Clones the GovernmentBuilding object.
     * @return A pointer to a new GovernmentBuilding object that is a clone of the current instance.
     */
    GovernmentBuilding* clone() override;

    /**
     * @brief Gets the type of the building (GovernmentBuilding).
     * @return A string indicating the type of the building.
     */
    std::string getType() const override { return type; }
};


#endif // BUILDING_H
