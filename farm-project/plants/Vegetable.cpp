#include "Vegetable.h"
#include "PlantExceptions.h"
#include <iostream>

Vegetable::Vegetable(const std::string& vegName, double height, bool rootVeg)
        : Plant(vegName, height), isRootVegetable(rootVeg), vitaminContent(50.0),
          harvestCount(0), color("green") {

    // Дополнительные проверки для овощей
    if (height > 3.0 && !rootVeg) {
        throw GrowthException("Vegetable height suspiciously large",
                              vegName, "Vegetable", height, 3.0);
    }
}

void Vegetable::harvestVegetable() {
    if (!isReadyForHarvest()) {
        double readinessScore = (getAge() * getHealth() * getWaterLevel()) / 10000.0;
        throw HarvestException("Vegetable not ready for harvest",
                               getName(), "Vegetable", 100.0, readinessScore,
                               "Immature vegetable");
    }

    harvestCount++;
    std::cout << getName() << " harvested! Total harvests: " << harvestCount << std::endl;

    if (isRootVegetable) {
        // Корнеплоды собираются один раз
        setIsPlanted(false);
        std::cout << "This root vegetable has been fully harvested." << std::endl;

        // Проверка на маленький урожай корнеплодов
        if (harvestCount == 1 && vitaminContent < 30.0) {
            throw HarvestException("Poor quality root vegetable",
                                   getName(), "Vegetable", 50.0, vitaminContent,
                                   "Low nutritional value");
        }
    } else {
        // Другие овощи могут давать урожай несколько раз
        setHealth(getHealth() - 30.0);
        setAge(0);

        // Проверка на истощение растения
        if (getHealth() < 20.0) {
            throw PlantDiseaseException("Vegetable exhausted after harvest",
                                        getName(), "Vegetable", "Exhaustion", 6,
                                        {"stems", "leaves"});
        }
    }
}

bool Vegetable::isRipe() const {
    return getAge() > 45 && getHealth() > 75.0 && getWaterLevel() > 50.0;
}

double Vegetable::getNutritionalValue() const {
    double baseValue = vitaminContent;
    if (getHealth() > 80.0) baseValue *= 1.2;
    if (getWaterLevel() > 60.0) baseValue *= 1.1;

    // Проверка на аномальную питательную ценность
    if (baseValue > 200.0) {
        throw PlantException("Suspiciously high nutritional value: " +
                             std::to_string(baseValue) +
                             " (max 200.0) for " + getName());
    }

    return baseValue;
}

void Vegetable::displayInfo() const {
    Plant::displayInfo();
    std::cout << "  Type: Vegetable"
              << ", Root vegetable: " << (isRootVegetable ? "Yes" : "No")
              << ", Color: " << color
              << ", Vitamin content: " << vitaminContent << "mg"
              << ", Harvest count: " << harvestCount
              << ", Nutritional value: " << getNutritionalValue()
              << ", Ripe: " << (isRipe() ? "Yes" : "No") << std::endl;
}

bool Vegetable::getIsRootVegetable() const { return isRootVegetable; }
double Vegetable::getVitaminContent() const { return vitaminContent; }
int Vegetable::getHarvestCount() const { return harvestCount; }
std::string Vegetable::getColor() const { return color; }

void Vegetable::setIsRootVegetable(bool root) { isRootVegetable = root; }

void Vegetable::setVitaminContent(double vitamins) {
    if (vitamins < 0) {
        throw PlantException("Vitamin content cannot be negative: " +
                             std::to_string(vitamins) + "mg");
    }
    if (vitamins > 500.0) {
        throw PlantException("Vitamin content unrealistically high: " +
                             std::to_string(vitamins) + "mg (max 500mg)");
    }
    vitaminContent = vitamins;
}

void Vegetable::setColor(const std::string& c) {
    if (c.empty()) {
        throw PlantException("Color cannot be empty");
    }

    // Проверка на необычные цвета для овощей
    if (c == "blue" || c == "purple") {
        throw PlantDiseaseException("Unusual vegetable color",
                                    getName(), "Vegetable", "Color Mutation", 3,
                                    {"pigmentation"});
    }

    color = c;
}