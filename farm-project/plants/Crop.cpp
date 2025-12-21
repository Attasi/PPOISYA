#include "Crop.h"
#include "PlantExceptions.h"
#include <iostream>

Crop::Crop(const std::string& cropName, double height, double initialYield)
        : Plant(cropName, height), yield(initialYield), isIrrigated(false),
          season("summer"), fertilizerLevel(0.0) {

    // Проверка урожайности
    if (initialYield < 0) {
        throw PlantException("Crop yield cannot be negative: " +
                             std::to_string(initialYield) + "kg");
    }
    if (initialYield > 10000.0) {
        throw PlantException("Crop yield unrealistically large: " +
                             std::to_string(initialYield) + "kg (max 10,000kg)");
    }
}

void Crop::applyFertilizer(double amount) {
    if (amount <= 0) {
        throw PlantException("Fertilizer amount must be positive: " +
                             std::to_string(amount));
    }
    if (amount > 100.0) {
        throw PlantException("Fertilizer amount too large: " +
                             std::to_string(amount) + " (max 100.0 units)");
    }

    fertilizerLevel += amount;

    // Проверка на передозировку удобрений
    if (fertilizerLevel > 200.0) {
        throw PlantDiseaseException("Fertilizer overdose", getName(), "Crop",
                                    "Chemical Burn", 8, {"roots", "leaves"});
        fertilizerLevel = 200.0;
    }

    health += 15.0;
    if (health > 100.0) health = 100.0;
    yield += amount * 0.5;

    std::cout << getName() << " fertilized with " << amount << " units." << std::endl;
}

void Crop::toggleIrrigation(bool status) {
    isIrrigated = status;
    if (status) {
        setWaterLevel(80.0);
        std::cout << getName() << " irrigation turned ON." << std::endl;
    } else {
        std::cout << getName() << " irrigation turned OFF." << std::endl;
    }
}

double Crop::calculateExpectedYield() const {
    double baseYield = yield;
    double multiplier = 1.0;

    if (isIrrigated) multiplier += 0.3;
    if (fertilizerLevel > 50.0) multiplier += 0.4;
    if (getWaterLevel() > 60.0) multiplier += 0.2;
    if (getHealth() > 80.0) multiplier += 0.1;

    double expected = baseYield * multiplier;

    // Проверка на аномально высокую урожайность
    if (expected > yield * 3.0) {
        throw HarvestException("Suspiciously high expected yield",
                               getName(), "Crop", yield, expected,
                               "Calculation error or unrealistic conditions");
    }

    return expected;
}

void Crop::displayInfo() const {
    Plant::displayInfo();
    std::cout << "  Type: Crop"
              << ", Yield: " << yield << "kg"
              << ", Irrigated: " << (isIrrigated ? "Yes" : "No")
              << ", Season: " << season
              << ", Fertilizer: " << fertilizerLevel << "%"
              << ", Expected yield: " << calculateExpectedYield() << "kg" << std::endl;
}

bool Crop::isReadyForHarvest() const {
    if (!Plant::isReadyForHarvest()) {
        throw HarvestException("Basic harvest conditions not met",
                               getName(), "Crop", yield, 0.0,
                               "Age/health/water insufficient");
    }

    if (getAge() <= 60) {
        throw HarvestException("Crop too young for harvest",
                               getName(), "Crop", yield, 0.0,
                               "Minimum age 60 days not reached");
    }

    if (yield <= 10.0) {
        throw HarvestException("Insufficient yield for harvest",
                               getName(), "Crop", 10.0, yield,
                               "Yield below minimum threshold");
    }

    return true;
}

double Crop::getYield() const { return yield; }
bool Crop::getIsIrrigated() const { return isIrrigated; }
std::string Crop::getSeason() const { return season; }
double Crop::getFertilizerLevel() const { return fertilizerLevel; }

void Crop::setYield(double y) {
    if (y < 0) {
        throw PlantException("Crop yield cannot be negative: " +
                             std::to_string(y) + "kg");
    }
    if (y > 50000.0) {
        throw PlantException("Crop yield unrealistically large: " +
                             std::to_string(y) + "kg (max 50,000kg)");
    }
    yield = y;
}

void Crop::setSeason(const std::string& s) {
    if (s != "spring" && s != "summer" && s != "autumn" && s != "winter") {
        throw PlantException("Invalid season: " + s +
                             " (must be spring/summer/autumn/winter)");
    }
    season = s;
}

void Crop::setFertilizerLevel(double level) {
    if (level < 0) {
        throw PlantException("Fertilizer level cannot be negative: " +
                             std::to_string(level));
    }
    if (level > 300.0) {
        throw PlantDiseaseException("Dangerous fertilizer level",
                                    getName(), "Crop", "Toxicity", 9,
                                    {"soil", "roots"});
    }
    fertilizerLevel = level;
}