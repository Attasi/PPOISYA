#include "ChickenCoop.h"
#include "BuildingExceptions.h"
#include <iostream>

ChickenCoop::ChickenCoop(const std::string& name, double area, int constructionYear,
                         int chickenCapacity)
        : Building(name, area, constructionYear) {
    // Дополнительные проверки для курятника
    if (chickenCapacity <= 0) {
        throw BuildingException("Chicken capacity must be positive: " +
                                std::to_string(chickenCapacity));
    }
    if (chickenCapacity > 5000) {
        throw BuildingException("Chicken capacity too high: " +
                                std::to_string(chickenCapacity) + " (max 5000)");
    }
    if (area < chickenCapacity * 0.3) {
        throw BuildingException("Coop area too small for " +
                                std::to_string(chickenCapacity) +
                                " chickens (need at least " +
                                std::to_string(chickenCapacity * 0.3) + " sq.m)");
    }

    this->chickenCapacity = chickenCapacity;
    this->numberOfNestingBoxes = chickenCapacity / 4;
    this->numberOfRoosts = chickenCapacity / 5;
    this->hasRun = true;
    this->runArea = area * 2;
    this->predatorProtection = "Fenced with netting";
    this->eggsCollectedDaily = 75;
    this->beddingMaterial = "Straw";
    this->hasAutomaticFeeder = false;

    setBuildingMaterial("Wood with wire mesh");
    setRoofType("Shed");
    setLocationOnFarm("Southeast Area");
    setName("Chicken Coop: " + name);
}

void ChickenCoop::displayInfo() const {
    Building::displayInfo();
    std::cout << "--- Chicken Coop Specific ---" << std::endl;
    std::cout << "Chicken Capacity: " << chickenCapacity << std::endl;
    std::cout << "Nesting Boxes: " << numberOfNestingBoxes << std::endl;
    std::cout << "Roosts: " << numberOfRoosts << std::endl;
    std::cout << "Has Run: " << (hasRun ? "Yes" : "No") << std::endl;
    if (hasRun) {
        std::cout << "Run Area: " << runArea << " sq.m" << std::endl;
    }
    std::cout << "Predator Protection: " << predatorProtection << std::endl;
    std::cout << "Eggs Collected Daily: " << eggsCollectedDaily << std::endl;
    std::cout << "Bedding Material: " << beddingMaterial << std::endl;
    std::cout << "Automatic Feeder: " << (hasAutomaticFeeder ? "Yes" : "No") << std::endl;
}

void ChickenCoop::addChickens(int count) {
    if (count <= 0) {
        throw BuildingException("Chicken count must be positive: " + std::to_string(count));
    }

    // Проверка текущего количества (примерная оценка)
    int currentChickens = eggsCollectedDaily / 0.7; // 70% несушек
    if (currentChickens + count > chickenCapacity) {
        throw BuildingCapacityException(getName(), chickenCapacity, currentChickens + count);
    }
    if (count > 1000) {
        throw BuildingException("Cannot add " + std::to_string(count) +
                                " chickens at once (max 1000 per addition)");
    }

    std::cout << "Added " << count << " chickens to the coop." << std::endl;
    eggsCollectedDaily += count * 0.7; // 70% несушек
    std::cout << "Expected daily egg collection now: " << eggsCollectedDaily << " eggs" << std::endl;
}

void ChickenCoop::collectEggs() {
    if (eggsCollectedDaily <= 0) {
        throw BuildingException("No eggs to collect (egg production: " +
                                std::to_string(eggsCollectedDaily) + ")");
    }
    if (numberOfNestingBoxes <= 0) {
        throw BuildingException("No nesting boxes available for egg collection");
    }

    std::cout << "Collecting eggs from nesting boxes..." << std::endl;
    std::cout << "Collected " << eggsCollectedDaily << " eggs today." << std::endl;

    double eggValue = eggsCollectedDaily * 0.25; // $0.25 per egg
    std::cout << "Daily egg value: $" << eggValue << std::endl;
    std::cout << "Weekly value: $" << eggValue * 7 << std::endl;

    // Сбрасываем счетчик после сбора
    eggsCollectedDaily = 0;
}

void ChickenCoop::cleanCoop() {
    if (beddingMaterial.empty()) {
        throw BuildingException("Bedding material not specified");
    }
    if (getCondition() == "Poor") {
        throw BuildingSafetyException(getName(), "Poor condition coop - cleaning may not be safe", 4);
    }

    std::cout << "Cleaning the chicken coop..." << std::endl;
    std::cout << "Replacing " << beddingMaterial << " bedding." << std::endl;
    std::cout << "Disinfecting nesting boxes and roosts." << std::endl;
    std::cout << "Removing droppings and refreshing water." << std::endl;

    setCondition("Excellent");
    eggsCollectedDaily = static_cast<int>(eggsCollectedDaily * 1.1); // Чистота увеличивает яйценоскость
    std::cout << "Coop cleaning completed. Egg production may increase." << std::endl;
}

void ChickenCoop::checkForPredators() {
    if (predatorProtection.empty()) {
        throw BuildingException("Predator protection not specified");
    }

    std::cout << "Checking predator protection: " << predatorProtection << std::endl;

    if (predatorProtection.find("Fenced") != std::string::npos) {
        if (predatorProtection.find("electric") == std::string::npos) {
            std::cout << "Warning: Fencing present but no electric fence - predators may climb over." << std::endl;
        }
    }
    if (predatorProtection.find("netting") != std::string::npos) {
        std::cout << "Netting is intact." << std::endl;
    }
    if (predatorProtection.find("electric") != std::string::npos) {
        if (!hasElectricity) {
            throw BuildingSafetyException(getName(), "Electric fence without electricity - ineffective", 5);
        }
        std::cout << "Electric fence is operational." << std::endl;
    }

    if (predatorProtection == "None" || predatorProtection.find("None") != std::string::npos) {
        throw BuildingSafetyException(getName(), "No predator protection - high risk", 9);
    }

    std::cout << "Common predators checked: Foxes, Raccoons, Hawks" << std::endl;
}

int ChickenCoop::getChickenCapacity() const { return chickenCapacity; }
int ChickenCoop::getNumberOfNestingBoxes() const { return numberOfNestingBoxes; }
int ChickenCoop::getNumberOfRoosts() const { return numberOfRoosts; }
bool ChickenCoop::getHasRun() const { return hasRun; }
double ChickenCoop::getRunArea() const { return runArea; }
std::string ChickenCoop::getPredatorProtection() const { return predatorProtection; }
int ChickenCoop::getEggsCollectedDaily() const { return eggsCollectedDaily; }
std::string ChickenCoop::getBeddingMaterial() const { return beddingMaterial; }
bool ChickenCoop::getHasAutomaticFeeder() const { return hasAutomaticFeeder; }

void ChickenCoop::setChickenCapacity(int capacity) {
    if (capacity <= 0 || capacity > 5000) {
        throw BuildingException("Chicken capacity must be between 0-5000: " + std::to_string(capacity));
    }
    chickenCapacity = capacity;
}

void ChickenCoop::setNumberOfNestingBoxes(int boxes) {
    if (boxes < 0 || boxes > 1000) {
        throw BuildingException("Number of nesting boxes must be between 0-1000: " + std::to_string(boxes));
    }
    numberOfNestingBoxes = boxes;
}

void ChickenCoop::setNumberOfRoosts(int roosts) {
    if (roosts < 0 || roosts > 1000) {
        throw BuildingException("Number of roosts must be between 0-1000: " + std::to_string(roosts));
    }
    numberOfRoosts = roosts;
}

void ChickenCoop::setHasRun(bool run) { hasRun = run; }

void ChickenCoop::setRunArea(double area) {
    if (area < 0 || area > 10000) {
        throw BuildingException("Run area must be between 0-10000 sq.m: " + std::to_string(area));
    }
    runArea = area;
}

void ChickenCoop::setPredatorProtection(const std::string& protection) {
    if (protection.empty()) {
        throw BuildingException("Predator protection cannot be empty");
    }
    predatorProtection = protection;
}

void ChickenCoop::setEggsCollectedDaily(int eggs) {
    if (eggs < 0 || eggs > 10000) {
        throw BuildingException("Eggs collected daily must be between 0-10000: " + std::to_string(eggs));
    }
    eggsCollectedDaily = eggs;
}

void ChickenCoop::setBeddingMaterial(const std::string& material) {
    if (material.empty()) {
        throw BuildingException("Bedding material cannot be empty");
    }
    beddingMaterial = material;
}

void ChickenCoop::setHasAutomaticFeeder(bool feeder) { hasAutomaticFeeder = feeder; }

double ChickenCoop::calculateEggProductionValue() const {
    if (eggsCollectedDaily <= 0) {
        throw BuildingException("No egg production to calculate value");
    }

    double dailyValue = eggsCollectedDaily * 0.25;
    double monthlyValue = dailyValue * 30;
    double annualValue = dailyValue * 365;

    std::cout << "Egg Production Value Analysis:" << std::endl;
    std::cout << "Daily: $" << dailyValue << std::endl;
    std::cout << "Monthly: $" << monthlyValue << std::endl;
    std::cout << "Annual: $" << annualValue << std::endl;

    return annualValue;
}

void ChickenCoop::installAutomaticSystems() {
    if (!hasElectricity) {
        throw BuildingException("Cannot install automatic systems without electricity");
    }

    if (!hasAutomaticFeeder) {
        hasAutomaticFeeder = true;
        std::cout << "Installed automatic feeder and waterer." << std::endl;
        setMaintenanceCost(getMaintenanceCost() + 200);
        eggsCollectedDaily = static_cast<int>(eggsCollectedDaily * 1.05); // Автоматика увеличивает продуктивность
    } else {
        throw BuildingException("Automatic systems already installed");
    }

    std::cout << "Considering automatic egg collection system..." << std::endl;
}

void ChickenCoop::maintainRoosts() {
    if (numberOfRoosts <= 0) {
        throw BuildingException("No roosts to maintain");
    }

    std::cout << "Maintaining chicken roosts..." << std::endl;
    std::cout << numberOfRoosts << " roosts inspected and cleaned." << std::endl;
    std::cout << "Ensuring proper spacing (15-20cm per chicken)." << std::endl;

    if (numberOfRoosts < chickenCapacity / 5) {
        std::cout << "Adding more roosts for comfortable perching." << std::endl;
        numberOfRoosts = chickenCapacity / 5;
    }
}

void ChickenCoop::ventilateCoop() {
    if (getCondition() == "Poor") {
        throw BuildingSafetyException(getName(), "Poor ventilation in already poor condition coop", 6);
    }

    std::cout << "Ventilating chicken coop..." << std::endl;
    std::cout << "Opening windows and vents for fresh air." << std::endl;
    std::cout << "Reducing ammonia levels from droppings." << std::endl;

    // Вентиляция улучшает здоровье кур
    eggsCollectedDaily = static_cast<int>(eggsCollectedDaily * 1.03);
    std::cout << "Ventilation complete. Improved air quality benefits egg production." << std::endl;
}