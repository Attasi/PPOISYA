#include "Plant.h"
#include "PlantExceptions.h"
#include <iostream>

Plant::Plant(const std::string& plantName, double plantHeight)
        : name(plantName), height(plantHeight), age(0), isPlanted(true), waterLevel(50.0), health(100.0) {

    // Проверка входных параметров
    if (plantName.empty()) {
        throw PlantException("Plant name cannot be empty");
    }
    if (plantHeight <= 0) {
        throw PlantException("Plant height must be positive: " + std::to_string(plantHeight) + "m");
    }
    if (plantHeight > 50.0) {
        throw PlantException("Plant height unrealistically large: " +
                             std::to_string(plantHeight) + "m (max 50m)");
    }
}

void Plant::water(double amount) {
    if (!isPlanted) {
        throw PlantException(name + " is not planted, cannot water");
    }
    if (amount <= 0) {
        throw PlantException("Water amount must be positive: " + std::to_string(amount));
    }
    if (amount > 100.0) {
        throw PlantException("Water amount too large: " + std::to_string(amount) +
                             " (max 100.0 units)");
    }

    waterLevel += amount;
    if (waterLevel > 100.0) {
        throw WateringException("Overwatering detected", name, "Plant",
                                waterLevel, 100.0, "Too much water");
        waterLevel = 100.0;
    }

    health += 5.0;
    if (health > 100.0) health = 100.0;

    std::cout << name << " watered with " << amount << " units." << std::endl;
}

void Plant::grow() {
    if (!isPlanted) {
        throw PlantException(name + " is not planted, cannot grow");
    }

    if (health <= 0) {
        throw PlantDiseaseException("Plant is dead", name, "Plant",
                                    "Complete Death", 10, {"all"});
    }

    if (waterLevel > 20.0 && health > 30.0) {
        height += 0.01;
        age++;

        // Проверка на аномальный рост
        if (height > 100.0) {
            throw GrowthException("Abnormal growth detected", name, "Plant",
                                  height, 100.0);
        }

        waterLevel -= 10.0;
        if (waterLevel < 0) waterLevel = 0;

        health -= 1.0;
        if (health < 0) health = 0;

        // Проверка на недостаток воды
        if (waterLevel < 10.0) {
            throw WateringException("Critical water deficiency", name, "Plant",
                                    waterLevel, 30.0, "Severe drought");
        }
    } else {
        if (waterLevel <= 20.0) {
            throw WateringException("Insufficient water for growth", name, "Plant",
                                    waterLevel, 20.0, "Need watering");
        }
        if (health <= 30.0) {
            throw PlantDiseaseException("Plant too weak to grow", name, "Plant",
                                        "Weakness", 7, {"stems", "leaves"});
        }
    }
}

void Plant::harvest() {
    if (!isPlanted) {
        throw PlantException(name + " is not planted, cannot harvest");
    }

    if (!isReadyForHarvest()) {
        double readiness = (age / 30.0) * 100.0;
        throw HarvestException("Plant not ready for harvest", name, "Plant",
                               100.0, readiness, "Immature plant");
    }

    std::cout << name << " harvested successfully!" << std::endl;
    isPlanted = false;
}

std::string Plant::getName() const { return name; }
double Plant::getHeight() const { return height; }
int Plant::getAge() const { return age; }
bool Plant::getIsPlanted() const { return isPlanted; }
double Plant::getWaterLevel() const { return waterLevel; }
double Plant::getHealth() const { return health; }

void Plant::setHeight(double h) {
    if (h <= 0) {
        throw PlantException("Height must be positive: " + std::to_string(h));
    }
    if (h > 100.0) {
        throw PlantException("Height unrealistically large: " +
                             std::to_string(h) + "m (max 100m)");
    }
    height = h;
}

void Plant::setAge(int a) {
    if (a < 0) {
        throw PlantException("Age cannot be negative: " + std::to_string(a));
    }
    if (a > 3650) {
        throw PlantException("Age unrealistically large: " +
                             std::to_string(a) + " days (max 10 years)");
    }
    age = a;
}

void Plant::setIsPlanted(bool planted) { isPlanted = planted; }

void Plant::setWaterLevel(double level) {
    if (level < 0 || level > 100.0) {
        throw WateringException("Water level out of range", name, "Plant",
                                level, 50.0, "Invalid water level");
    }
    waterLevel = level;
}

void Plant::setHealth(double h) {
    if (h < 0 || h > 100.0) {
        throw PlantException("Health must be between 0-100%: " + std::to_string(h));
    }

    if (h < 20.0) {
        throw PlantDiseaseException("Critical health level set", name, "Plant",
                                    "Critical Condition", 9, {"all systems"});
    }

    health = h;
}

void Plant::displayInfo() const {
    std::cout << "Plant: " << name
              << ", Height: " << height << "m"
              << ", Age: " << age << " days"
              << ", Water level: " << waterLevel << "%"
              << ", Health: " << health << "%"
              << ", Planted: " << (isPlanted ? "Yes" : "No") << std::endl;
}

bool Plant::isReadyForHarvest() const {
    return age > 30 && health > 70.0 && waterLevel > 40.0;
}

void Plant::heal(double amount) {
    if (amount <= 0) {
        throw PlantException("Healing amount must be positive: " + std::to_string(amount));
    }

    health += amount;
    if (health > 100.0) health = 100.0;
    if (health < 0) health = 0;

    std::cout << name << " healed by " << amount << "%. New health: " << health << "%" << std::endl;
}

bool Plant::needsWatering() const {
    return waterLevel < 40.0;
}