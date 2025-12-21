#include "Fruit.h"
#include "PlantExceptions.h"
#include <iostream>

Fruit::Fruit(const std::string& fruitName, double height, double sweetLevel)
        : Plant(fruitName, height), sweetness(sweetLevel), fruitCount(0),
          isEdibleRaw(true), taste("sweet") {

    // Проверка сладости
    if (sweetLevel < 0 || sweetLevel > 100.0) {
        throw PlantException("Sweetness must be between 0-100%: " +
                             std::to_string(sweetLevel));
    }

    // Проверка высоты для фруктовых деревьев/кустов
    if (height > 20.0 && fruitName.find("Tree") == std::string::npos) {
        throw GrowthException("Fruit plant too tall for type",
                              fruitName, "Fruit", height, 10.0);
    }
}

int Fruit::harvestFruit(int amount) {
    if (fruitCount == 0) {
        throw HarvestException("No fruits available for harvest",
                               getName(), "Fruit", amount, 0.0,
                               "No fruits produced");
    }

    if (amount <= 0) {
        throw PlantException("Harvest amount must be positive: " +
                             std::to_string(amount));
    }

    if (amount > fruitCount) {
        throw HarvestException("Trying to harvest more fruits than available",
                               getName(), "Fruit", amount, fruitCount,
                               "Insufficient fruit count");
    }

    // Проверка спелости перед сбором
    if (!isSweetEnough()) {
        throw HarvestException("Fruits not sweet enough for harvest",
                               getName(), "Fruit", sweetness, 70.0,
                               "Low sugar content");
    }

    fruitCount -= amount;
    std::cout << "Harvested " << amount << " fruits from " << getName()
              << ". Remaining: " << fruitCount << std::endl;

    return amount;
}

bool Fruit::isSweetEnough() const {
    return sweetness > 70.0 && getAge() > 50 && getWaterLevel() > 40.0;
}

void Fruit::pollinate() {
    if (getHealth() <= 50.0) {
        throw PlantDiseaseException("Plant too weak for pollination",
                                    getName(), "Fruit", "Weakness", 5,
                                    {"flowers"});
    }

    if (getWaterLevel() <= 30.0) {
        throw WateringException("Insufficient water for pollination",
                                getName(), "Fruit", getWaterLevel(), 40.0,
                                "Need watering before pollination");
    }

    fruitCount += 10;
    sweetness += 5.0;

    if (sweetness > 100.0) {
        sweetness = 100.0;
        throw PlantException("Fruit reached maximum sweetness (100%) for " + getName());
    }

    std::cout << getName() << " has been pollinated. Fruit count increased!" << std::endl;
}

void Fruit::displayInfo() const {
    Plant::displayInfo();
    std::cout << "  Type: Fruit"
              << ", Sweetness: " << sweetness << "%"
              << ", Fruit count: " << fruitCount
              << ", Edible raw: " << (isEdibleRaw ? "Yes" : "No")
              << ", Taste: " << taste
              << ", Sweet enough: " << (isSweetEnough() ? "Yes" : "No") << std::endl;
}

bool Fruit::isReadyForHarvest() const {
    if (fruitCount <= 0) {
        throw HarvestException("No fruits to harvest",
                               getName(), "Fruit", 10.0, 0.0,
                               "No fruits produced");
    }

    if (!isSweetEnough()) {
        throw HarvestException("Fruits not sweet enough",
                               getName(), "Fruit", 70.0, sweetness,
                               "Insufficient sugar content");
    }

    if (getHealth() <= 60.0) {
        throw PlantDiseaseException("Fruit plant unhealthy for harvest",
                                    getName(), "Fruit", "Disease", 7,
                                    {"fruits", "leaves"});
    }

    return true;
}

double Fruit::getSweetness() const { return sweetness; }
int Fruit::getFruitCount() const { return fruitCount; }
bool Fruit::getIsEdibleRaw() const { return isEdibleRaw; }
std::string Fruit::getTaste() const { return taste; }

void Fruit::setSweetness(double sweet) {
    if (sweet < 0 || sweet > 100.0) {
        throw PlantException("Sweetness must be between 0-100%: " +
                             std::to_string(sweet));
    }
    sweetness = sweet;
}

void Fruit::setFruitCount(int count) {
    if (count < 0) {
        throw PlantException("Fruit count cannot be negative: " +
                             std::to_string(count));
    }
    if (count > 10000) {
        throw PlantException("Fruit count unrealistically large: " +
                             std::to_string(count) + " (max 10,000)");
    }
    fruitCount = count;
}

void Fruit::setIsEdibleRaw(bool edible) { isEdibleRaw = edible; }

void Fruit::setTaste(const std::string& t) {
    if (t.empty()) {
        throw PlantException("Taste description cannot be empty");
    }

    // Проверка на необычные вкусы
    if (t == "bitter" && isEdibleRaw) {
        throw PlantException("Edible raw fruit cannot have bitter taste: " +
                             getName());
    }

    taste = t;
}