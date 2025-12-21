#include "Potato.h"
#include "PlantExceptions.h"
#include <iostream>

Potato::Potato(double height, const std::string& potatoVariety)
        : Vegetable("Potato", height, true), tuberCount(0),
          tuberSize(5.0), variety(potatoVariety) {
    setColor("brown");

    if (height > 1.5) {
        throw GrowthException("Potato plant height too tall",
                              getName(), "Potato", height, 1.5);
    }

    if (potatoVariety.empty()) {
        throw PlantException("Potato variety cannot be empty");
    }
}

int Potato::harvestPotatoes(int count) {
    if (tuberCount == 0 || !isReadyForHarvest()) {
        throw HarvestException("No potatoes ready for harvest",
                               getName(), "Potato", count, 0.0,
                               "No tubers or not harvest-ready");
    }

    if (count <= 0) {
        throw PlantException("Harvest count must be positive: " +
                             std::to_string(count));
    }

    if (count > tuberCount) {
        throw HarvestException("Trying to harvest more potatoes than available",
                               getName(), "Potato", count, tuberCount,
                               "Insufficient tuber count");
    }

    if (hasBlight()) {
        throw PlantDiseaseException("Potatoes have blight, cannot harvest",
                                    getName(), "Potato", "Blight", 9,
                                    {"tubers", "leaves"});
    }

    tuberCount -= count;
    double totalWeight = count * tuberSize * 0.2;

    std::cout << "Harvested " << count << " potatoes ("
              << totalWeight << "kg). Remaining: " << tuberCount << std::endl;

    if (tuberCount == 0) {
        setIsPlanted(false);
    }

    return count;
}

bool Potato::hasBlight() const {
    return getHealth() < 40.0 && getWaterLevel() > 80.0;
}

std::string Potato::sortBySize() const {
    if (tuberSize > 7.0) return "Large";
    if (tuberSize > 4.0) return "Medium";
    return "Small";
}

void Potato::displayInfo() const {
    Vegetable::displayInfo();
    std::cout << "  Variety: Potato (" << variety << ")"
              << ", Tuber count: " << tuberCount
              << ", Tuber size: " << tuberSize << "cm"
              << ", Size category: " << sortBySize()
              << ", Has blight: " << (hasBlight() ? "Yes" : "No") << std::endl;
}

void Potato::harvestVegetable() {
    if (isReadyForHarvest() && tuberCount > 0) {
        if (hasBlight()) {
            throw PlantDiseaseException("Cannot harvest potatoes with blight",
                                        getName(), "Potato", "Blight", 9,
                                        {"tubers"});
        }

        std::cout << "Harvesting all potatoes from " << getName() << std::endl;
        // Используем методы родительского класса Vegetable
        // Если в Vegetable нет harvestCount, просто выводим сообщение
        std::cout << "Harvest successful!" << std::endl;
        tuberCount = 0;
        setIsPlanted(false);
    } else {
        throw HarvestException("Potatoes not ready for harvest",
                               getName(), "Potato", 10.0, tuberCount,
                               "Insufficient tubers or not mature");
    }
}

int Potato::getTuberCount() const { return tuberCount; }
double Potato::getTuberSize() const { return tuberSize; }
std::string Potato::getVariety() const { return variety; }

void Potato::setTuberCount(int count) {
    if (count < 0) {
        throw PlantException("Tuber count cannot be negative: " +
                             std::to_string(count));
    }

    if (count > 100) {
        throw PlantException("Tuber count unrealistically large: " +
                             std::to_string(count) + " (max 100)");
    }

    tuberCount = count;
}

void Potato::setTuberSize(double size) {
    if (size <= 0) {
        throw PlantException("Tuber size must be positive: " +
                             std::to_string(size) + "cm");
    }

    if (size > 15.0) {
        throw GrowthException("Potato tuber size abnormally large",
                              getName(), "Potato", size, 10.0);
    }

    tuberSize = size;
}

void Potato::setVariety(const std::string& v) {
    if (v.empty()) {
        throw PlantException("Potato variety cannot be empty");
    }
    variety = v;
}