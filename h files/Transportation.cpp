#include "Transportation.h"
#include <iostream>

// Adaptees
// PublicTransport
void PublicTransport::addTransport() {
    std::cout << "Public transport added." << std::endl;
}

void PublicTransport::upgrade() {
}

int PublicTransport::getPassengers() {
    return 0 ;
}

// RoadSystem
void RoadSystem::addRoads() {
    std::cout << "RoadSystem added." << std::endl;
}

void RoadSystem::upgrade() {
}

int RoadSystem::getTrafficFlow() {
    return 0 ;
}

// RailSystem
void RailSystem::addRailway() {
    std::cout << "Railway added." << std::endl;
}

void RailSystem::upgrade() {
}

int RailSystem::getTrainSchedule() {
    return 0 ;
}

// Adapters
// PublicTransitAdapter
PublicTransitAdapter::PublicTransitAdapter(PublicTransport* publicTransport)
    :transitSystem(publicTransport){}

void PublicTransitAdapter::addRoute() {
    transitSystem->addTransport();
}

int PublicTransitAdapter::getUtilization() {
    transitSystem->getPassengers();
}

void PublicTransitAdapter::performMaintenance() {
    transitSystem->upgrade() ;
}

// RoadSystemAdapter
RoadSystemAdapter::RoadSystemAdapter(RoadSystem* roadSystem)
    :roadSystem(roadSystem){}

void RoadSystemAdapter::addRoute() {
    roadSystem->addRoads();
}

int RoadSystemAdapter::getUtilization() {
    roadSystem->getTrafficFlow();
}

void RoadSystemAdapter::performMaintenance() {
    roadSystem->upgrade() ;
}

// RailSystemAdapter
RailSystemAdapter::RailSystemAdapter(RailSystem* railSystem)
    :railSystem(railSystem){}

void RailSystemAdapter::addRoute() {
    railSystem->addRailway();
}

int RailSystemAdapter::getUtilization() {
    return railSystem->getTrainSchedule();
}

void RailSystemAdapter::performMaintenance() {
    railSystem->upgrade();
}

