#include "Barn.h"
#include "BuildingExceptions.h"
#include <iostream>
#include <algorithm>

Barn::Barn(const std::string& name, double area, int constructionYear, int animalCapacity)
        : Building(name, area, constructionYear) {
    // Дополнительные проверки для сарая
    if (animalCapacity <= 0) {
        throw BuildingException("Animal capacity must be positive: " +
                                std::to_string(animalCapacity));
    }
    if (animalCapacity > 1000) {
        throw BuildingException("Animal capacity too high: " +
                                std::to_string(animalCapacity) + " (max 1000)");
    }
    if (area < animalCapacity * 4) {
        throw BuildingException("Barn area too small for " +
                                std::to_string(animalCapacity) +
                                " animals (need at least " +
                                std::to_string(animalCapacity * 4) + " sq.m)");
    }

    this->animalCapacity = animalCapacity;
    this->numberOfStalls = animalCapacity / 2;
    this->hasHayloft = true;
    this->hayStorageCapacity = area * 0.5;
    this->ventilationSystem = "Natural with fans";
    this->milkingStations = 4;
    this->hasInsulation = true;
    this->manureManagement = "Daily removal";

    setBuildingMaterial("Wood and Steel");
    setRoofType("Gambrel");
    setLocationOnFarm("Northwest Corner");
    setName("Barn: " + name);

    housedAnimals = {"Cows", "Horses", "Sheep"};
}

void Barn::displayInfo() const {
    Building::displayInfo();
    std::cout << "--- Barn Specific ---" << std::endl;
    std::cout << "Animal Capacity: " << animalCapacity << std::endl;
    std::cout << "Number of Stalls: " << numberOfStalls << std::endl;
    std::cout << "Has Hayloft: " << (hasHayloft ? "Yes" : "No") << std::endl;
    std::cout << "Hay Storage Capacity: " << hayStorageCapacity << " tons" << std::endl;
    std::cout << "Ventilation System: " << ventilationSystem << std::endl;
    std::cout << "Milking Stations: " << milkingStations << std::endl;
    std::cout << "Has Insulation: " << (hasInsulation ? "Yes" : "No") << std::endl;
    std::cout << "Manure Management: " << manureManagement << std::endl;

    if (housedAnimals.empty()) {
        throw BuildingException(getName() + " has no housed animals");
    }

    std::cout << "Currently Housed Animals: ";
    for (size_t i = 0; i < housedAnimals.size(); ++i) {
        std::cout << housedAnimals[i];
        if (i < housedAnimals.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void Barn::houseAnimal(const std::string& animalType, int count) {
    if (animalType.empty()) {
        throw BuildingException("Animal type cannot be empty");
    }
    if (count <= 0) {
        throw BuildingException("Animal count must be positive: " + std::to_string(count));
    }

    int currentAnimals = housedAnimals.size() * 10; // Примерная оценка
    if (currentAnimals + count > animalCapacity) {
        throw BuildingCapacityException(getName(), animalCapacity, currentAnimals + count);
    }
    if (count > 100) {
        throw BuildingException("Cannot house " + std::to_string(count) +
                                " animals at once (max 100 per operation)");
    }

    // Проверка совместимости животных
    if (animalType == "Pig" && std::find(housedAnimals.begin(), housedAnimals.end(), "Horse") != housedAnimals.end()) {
        throw BuildingException("Pigs cannot be housed with horses in same barn");
    }

    housedAnimals.push_back(animalType);
    std::cout << "Housed " << count << " " << animalType
              << " in the barn." << std::endl;
    std::cout << "Current animal count: " << housedAnimals.size() << " types" << std::endl;
}

void Barn::storeHay(double amount) {
    if (amount <= 0) {
        throw BuildingException("Hay amount must be positive: " + std::to_string(amount));
    }
    if (!hasHayloft) {
        throw BuildingException("Cannot store hay: barn has no hayloft");
    }
    if (amount > hayStorageCapacity) {
        throw BuildingCapacityException(getName() + " hayloft", hayStorageCapacity, amount);
    }
    if (amount > 1000) {
        throw BuildingException("Hay amount too large for single storage: " +
                                std::to_string(amount) + " tons (max 1000)");
    }

    // Проверка пожарной безопасности
    if (amount > 500 && ventilationSystem == "Natural") {
        throw BuildingSafetyException(getName(), "Large hay storage with poor ventilation - fire risk", 6);
    }

    std::cout << "Stored " << amount << " tons of hay in the hayloft." << std::endl;
    hayStorageCapacity -= amount;
    std::cout << "Remaining hay storage capacity: " << hayStorageCapacity << " tons" << std::endl;
}

void Barn::cleanBarn() {
    if (manureManagement.empty()) {
        throw BuildingException("Manure management system not specified");
    }

    std::cout << "Cleaning the barn..." << std::endl;
    std::cout << "Removing manure, replacing bedding, disinfecting stalls." << std::endl;
    setCondition("Good");
    std::cout << "Barn cleaning completed." << std::endl;
}

void Barn::checkVentilation() {
    if (ventilationSystem.empty()) {
        throw BuildingException("Ventilation system not specified");
    }

    std::cout << "Checking ventilation system: " << ventilationSystem << std::endl;
    if (ventilationSystem == "Natural with fans") {
        if (housedAnimals.size() > animalCapacity * 0.8) {
            throw BuildingException("Barn overcrowded, ventilation may be insufficient");
        }
        std::cout << "Ventilation system is working properly." << std::endl;
    } else {
        std::cout << "Checking airflow and fan operation..." << std::endl;
    }
}

int Barn::getAnimalCapacity() const { return animalCapacity; }
std::vector<std::string> Barn::getHousedAnimals() const { return housedAnimals; }
int Barn::getNumberOfStalls() const { return numberOfStalls; }
bool Barn::getHasHayloft() const { return hasHayloft; }
double Barn::getHayStorageCapacity() const { return hayStorageCapacity; }
std::string Barn::getVentilationSystem() const { return ventilationSystem; }
int Barn::getMilkingStations() const { return milkingStations; }
bool Barn::getHasInsulation() const { return hasInsulation; }
std::string Barn::getManureManagement() const { return manureManagement; }

void Barn::setAnimalCapacity(int capacity) {
    if (capacity <= 0 || capacity > 1000) {
        throw BuildingException("Animal capacity must be between 0-1000: " + std::to_string(capacity));
    }
    animalCapacity = capacity;
}

void Barn::setHousedAnimals(const std::vector<std::string>& animals) {
    housedAnimals = animals;
}

void Barn::setNumberOfStalls(int stalls) {
    if (stalls < 0 || stalls > 500) {
        throw BuildingException("Number of stalls must be between 0-500: " + std::to_string(stalls));
    }
    numberOfStalls = stalls;
}

void Barn::setHasHayloft(bool hayloft) { hasHayloft = hayloft; }

void Barn::setHayStorageCapacity(double capacity) {
    if (capacity < 0 || capacity > 5000) {
        throw BuildingException("Hay storage capacity must be between 0-5000 tons: " +
                                std::to_string(capacity));
    }
    hayStorageCapacity = capacity;
}

void Barn::setVentilationSystem(const std::string& system) {
    if (system.empty()) {
        throw BuildingException("Ventilation system cannot be empty");
    }
    ventilationSystem = system;
}

void Barn::setMilkingStations(int stations) {
    if (stations < 0 || stations > 20) {
        throw BuildingException("Milking stations must be between 0-20: " + std::to_string(stations));
    }
    milkingStations = stations;
}

void Barn::setHasInsulation(bool insulation) { hasInsulation = insulation; }

void Barn::setManureManagement(const std::string& management) {
    if (management.empty()) {
        throw BuildingException("Manure management cannot be empty");
    }
    manureManagement = management;
}

double Barn::calculateAvailableSpace() const {
    double usedSpace = housedAnimals.size() * 4.0; // 4 кв.м на животное
    double availableSpace = getArea() - usedSpace;

    if (availableSpace < 0) {
        throw BuildingCapacityException(getName(), getArea(), usedSpace);
    }

    return availableSpace > 0 ? availableSpace : 0;
}

void Barn::prepareForWinter() {
    if (getCondition() == "Poor") {
        throw BuildingSafetyException(getName(), "Poor condition barn cannot withstand winter", 7);
    }

    if (hasInsulation) {
        std::cout << "Barn is already insulated for winter." << std::endl;
    } else {
        std::cout << "Adding insulation and winterizing the barn..." << std::endl;
        hasInsulation = true;
        setCondition("Good");
    }

    // Запасаем сено на зиму
    if (hayStorageCapacity <= 0) {
        throw BuildingException("No hay storage capacity available for winter");
    }

    double winterHay = hayStorageCapacity * 0.8;
    storeHay(winterHay);
    std::cout << "Barn prepared for winter conditions." << std::endl;
}

void Barn::installMilkingEquipment() {
    if (milkingStations > 0) {
        throw BuildingException("Milking equipment already installed (" +
                                std::to_string(milkingStations) + " stations)");
    }

    if (!hasElectricity) {
        throw BuildingException("Cannot install milking equipment without electricity");
    }

    milkingStations = 2;
    std::cout << "Installed " << milkingStations << " milking stations." << std::endl;
    setMaintenanceCost(getMaintenanceCost() + 500);
}

void Barn::manageManure() {
    if (manureManagement.empty()) {
        throw BuildingException("Manure management system not specified");
    }

    std::cout << "Managing manure using system: " << manureManagement << std::endl;
    if (manureManagement == "Daily removal") {
        if (housedAnimals.size() > 100) {
            throw BuildingException("Daily removal impractical for " +
                                    std::to_string(housedAnimals.size()) + " animals");
        }
        std::cout << "Manure is removed daily for composting." << std::endl;
    } else if (manureManagement == "Pit storage") {
        std::cout << "Manure is stored in pits for later use as fertilizer." << std::endl;
    } else {
        throw BuildingException("Unknown manure management system: " + manureManagement);
    }
    std::cout << "This helps maintain hygiene and provides fertilizer." << std::endl;
}