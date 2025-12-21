#include "Building.h"
#include "BuildingExceptions.h"
#include <iostream>

Building::Building(const std::string& name, double area, int constructionYear) {
    // Проверка входных параметров
    if (name.empty()) {
        throw BuildingException("Building name cannot be empty");
    }
    if (area <= 0) {
        throw BuildingException("Building area must be positive: " + std::to_string(area));
    }
    if (area > 10000) {
        throw BuildingException("Building area unrealistically large: " +
                                std::to_string(area) + " sq.m (max 10,000)");
    }
    if (constructionYear < 1900) {
        throw BuildingException("Construction year too old: " +
                                std::to_string(constructionYear) + " (min 1900)");
    }
    if (constructionYear > 2024) {
        throw BuildingException("Construction year in future: " +
                                std::to_string(constructionYear) + " (max 2024)");
    }

    this->name = name;
    this->area = area;
    this->constructionYear = constructionYear;
    this->buildingMaterial = "Wood";
    this->condition = "Good";
    this->locationOnFarm = "Central Area";
    this->hasElectricity = true;
    this->hasWaterSupply = true;
    this->roofType = "Gable";
    this->maintenanceCost = 1000.0;

    static int counter = 1;
    this->buildingId = "B" + std::to_string(counter++);
}

void Building::displayInfo() const {
    std::cout << "=== Building Information ===" << std::endl;
    std::cout << "Building ID: " << buildingId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Area: " << area << " sq.m" << std::endl;
    std::cout << "Construction Year: " << constructionYear << std::endl;
    std::cout << "Building Material: " << buildingMaterial << std::endl;
    std::cout << "Condition: " << condition << std::endl;
    std::cout << "Location: " << locationOnFarm << std::endl;
    std::cout << "Electricity: " << (hasElectricity ? "Yes" : "No") << std::endl;
    std::cout << "Water Supply: " << (hasWaterSupply ? "Yes" : "No") << std::endl;
    std::cout << "Roof Type: " << roofType << std::endl;
    std::cout << "Annual Maintenance Cost: $" << maintenanceCost << std::endl;
    std::cout << "Estimated Value: $" << calculateValue() << std::endl;
}

double Building::calculateValue() const {
    double baseValue = area * 500; // $500 за кв.м
    if (condition == "Excellent") baseValue *= 1.2;
    else if (condition == "Poor") baseValue *= 0.7;

    if (hasElectricity && hasWaterSupply) baseValue *= 1.15;

    return baseValue;
}

void Building::performMaintenance() {
    if (condition == "Excellent") {
        throw BuildingException(name + " is already in excellent condition, no maintenance needed");
    }

    std::cout << "Performing maintenance on " << name << std::endl;
    if (condition == "Poor") {
        condition = "Fair";
        std::cout << "Condition improved from Poor to Fair." << std::endl;
    } else if (condition == "Fair") {
        condition = "Good";
        std::cout << "Condition improved from Fair to Good." << std::endl;
    } else {
        std::cout << "Building is already in good condition." << std::endl;
    }
}

void Building::inspectBuilding() {
    std::cout << "Inspecting " << name << "..." << std::endl;
    std::cout << "Current condition: " << condition << std::endl;

    int age = calculateAge(2024);
    if (condition == "Poor" && age > 30) {
        throw BuildingSafetyException(name, "Structural damage due to age", 8);
    }
    if (condition == "Poor" && !hasElectricity) {
        throw BuildingSafetyException(name, "No electricity in poor condition building", 5);
    }

    if (condition == "Poor") {
        std::cout << "URGENT: Building needs immediate attention!" << std::endl;
    } else if (condition == "Fair") {
        std::cout << "Building needs some repairs." << std::endl;
    } else {
        std::cout << "Building is in satisfactory condition." << std::endl;
    }
}

std::string Building::getName() const { return name; }
double Building::getArea() const { return area; }
int Building::getConstructionYear() const { return constructionYear; }
std::string Building::getBuildingMaterial() const { return buildingMaterial; }
std::string Building::getCondition() const { return condition; }
std::string Building::getLocationOnFarm() const { return locationOnFarm; }
bool Building::getHasElectricity() const { return hasElectricity; }
bool Building::getHasWaterSupply() const { return hasWaterSupply; }
std::string Building::getRoofType() const { return roofType; }
double Building::getMaintenanceCost() const { return maintenanceCost; }
std::string Building::getBuildingId() const { return buildingId; }

void Building::setName(const std::string& name) {
    if (name.empty()) {
        throw BuildingException("Building name cannot be empty");
    }
    this->name = name;
}

void Building::setArea(double area) {
    if (area <= 0) {
        throw BuildingException("Building area must be positive: " + std::to_string(area));
    }
    if (area > 10000) {
        throw BuildingException("Building area unrealistically large: " +
                                std::to_string(area) + " sq.m (max 10,000)");
    }
    this->area = area;
}

void Building::setConstructionYear(int year) {
    if (year < 1900 || year > 2024) {
        throw BuildingException("Construction year must be between 1900-2024: " +
                                std::to_string(year));
    }
    constructionYear = year;
}

void Building::setBuildingMaterial(const std::string& material) {
    if (material.empty()) {
        throw BuildingException("Building material cannot be empty");
    }
    buildingMaterial = material;
}

void Building::setCondition(const std::string& condition) {
    if (condition.empty()) {
        throw BuildingException("Condition cannot be empty");
    }
    if (condition != "Excellent" && condition != "Good" &&
        condition != "Fair" && condition != "Poor") {
        throw BuildingException("Invalid condition: " + condition +
                                " (must be Excellent/Good/Fair/Poor)");
    }
    this->condition = condition;
}

void Building::setLocationOnFarm(const std::string& location) {
    if (location.empty()) {
        throw BuildingException("Location cannot be empty");
    }
    locationOnFarm = location;
}

void Building::setHasElectricity(bool electricity) { hasElectricity = electricity; }

void Building::setHasWaterSupply(bool water) { hasWaterSupply = water; }

void Building::setRoofType(const std::string& roofType) {
    if (roofType.empty()) {
        throw BuildingException("Roof type cannot be empty");
    }
    this->roofType = roofType;
}

void Building::setMaintenanceCost(double cost) {
    if (cost < 0) {
        throw BuildingException("Maintenance cost cannot be negative: $" + std::to_string(cost));
    }
    if (cost > 100000) {
        throw BuildingException("Maintenance cost unrealistically high: $" +
                                std::to_string(cost) + " (max $100,000)");
    }
    maintenanceCost = cost;
}

void Building::setBuildingId(const std::string& id) {
    if (id.empty()) {
        throw BuildingException("Building ID cannot be empty");
    }
    buildingId = id;
}

int Building::calculateAge(int currentYear) const {
    if (currentYear < constructionYear) {
        throw BuildingException("Current year " + std::to_string(currentYear) +
                                " is before construction year " +
                                std::to_string(constructionYear));
    }
    return currentYear - constructionYear;
}

void Building::upgradeFacilities() {
    if (!hasElectricity) {
        hasElectricity = true;
        std::cout << "Electricity installed in " << name << std::endl;
        maintenanceCost += 200;
    } else {
        throw BuildingException(name + " already has electricity");
    }

    if (!hasWaterSupply) {
        hasWaterSupply = true;
        std::cout << "Water supply installed in " << name << std::endl;
        maintenanceCost += 300;
    } else {
        throw BuildingException(name + " already has water supply");
    }
}

bool Building::needsRenovation() const {
    int age = calculateAge(2024);
    if (age > 50) {
        throw BuildingException(name + " is over 50 years old, needs major renovation");
    }
    return age > 20 || condition == "Poor";
}

void Building::calculateInsuranceCost() const {
    double insurance = calculateValue() * 0.01; // 1% от стоимости
    std::cout << "Annual insurance cost for " << name << ": $" << insurance << std::endl;
}