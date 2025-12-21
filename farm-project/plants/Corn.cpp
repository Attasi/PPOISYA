#include "Corn.h"
#include "PlantExceptions.h"
#include <iostream>

Corn::Corn(double height, double yield, bool sweetCorn)
        : Crop("Corn", height, yield), earCount(0), cobSize(15.0),
          isSweetCorn(sweetCorn) {
    setSeason("summer");

    if (height > 4.0) {
        throw GrowthException("Corn height too tall",
                              getName(), "Corn", height, 4.0);
    }

    if (yield > 20000.0) {
        throw PlantException("Corn yield unrealistically large: " +
                             std::to_string(yield) + "kg (max 20,000kg)");
    }
}

int Corn::harvestEars(int count) {
    if (earCount == 0) {
        throw HarvestException("No corn ears available for harvest",
                               getName(), "Corn", count, 0.0,
                               "No ears produced");
    }

    if (count <= 0) {
        throw PlantException("Harvest count must be positive: " +
                             std::to_string(count));
    }

    if (count > earCount) {
        throw HarvestException("Trying to harvest more ears than available",
                               getName(), "Corn", count, earCount,
                               "Insufficient ear count");
    }

    if (!isReadyForHarvest()) {
        throw HarvestException("Corn not ready for harvest",
                               getName(), "Corn", getYield(), 0.0,
                               "Immature corn");
    }

    earCount -= count;
    double harvestedWeight = count * cobSize * 0.1;

    std::cout << "Harvested " << count << " corn ears ("
              << harvestedWeight << "kg). Remaining: " << earCount << std::endl;

    return count;
}

bool Corn::hasLargeCobs() const {
    return cobSize > 18.0 && getHealth() > 70.0 && getWaterLevel() > 60.0;
}

void Corn::canCorn(int amount) {
    if (!isSweetCorn) {
        throw PlantException(getName() + " is not sweet corn, cannot can it");
    }

    if (amount <= 0) {
        throw PlantException("Canning amount must be positive: " +
                             std::to_string(amount));
    }

    if (amount > earCount) {
        throw HarvestException("Not enough ears for canning",
                               getName(), "Corn", amount, earCount,
                               "Insufficient ear count");
    }

    if (!hasLargeCobs()) {
        throw HarvestException("Corn cobs too small for canning",
                               getName(), "Corn", 18.0, cobSize,
                               "Small cob size");
    }

    std::cout << "Canned " << amount << " ears of sweet corn." << std::endl;
    earCount -= amount;
}

void Corn::displayInfo() const {
    Crop::displayInfo();
    std::cout << "  Variety: Corn"
              << ", Type: " << (isSweetCorn ? "Sweet Corn" : "Field Corn")
              << ", Ear count: " << earCount
              << ", Cob size: " << cobSize << "cm"
              << ", Large cobs: " << (hasLargeCobs() ? "Yes" : "No") << std::endl;
}

void Corn::grow() {
    Crop::grow();

    if (getIsIrrigated() && getFertilizerLevel() > 30.0) {
        setHeight(getHeight() + 0.02);

        if (getHeight() > 4.0) {
            throw GrowthException("Corn grew too tall",
                                  getName(), "Corn", getHeight(), 4.0);
        }

        if (getAge() > 40 && earCount < 4) {
            earCount += 1;
            cobSize += 0.5;

            if (cobSize > 30.0) {
                throw GrowthException("Corn cob size abnormally large",
                                      getName(), "Corn", cobSize, 25.0);
            }
        }
    }

    // Проверка на болезнь при высокой влажности
    if (getWaterLevel() > 90.0 && getHealth() < 60.0) {
        throw PlantDiseaseException("Corn developing fungal disease",
                                    getName(), "Corn", "Fungal Infection", 6,
                                    {"leaves", "cobs"});
    }
}

int Corn::getEarCount() const { return earCount; }
double Corn::getCobSize() const { return cobSize; }
bool Corn::getIsSweetCorn() const { return isSweetCorn; }

void Corn::setEarCount(int count) {
    if (count < 0) {
        throw PlantException("Ear count cannot be negative: " +
                             std::to_string(count));
    }

    if (count > 100) {
        throw PlantException("Ear count unrealistically large: " +
                             std::to_string(count) + " (max 100)");
    }

    earCount = count;
}

void Corn::setCobSize(double size) {
    if (size <= 0) {
        throw PlantException("Cob size must be positive: " +
                             std::to_string(size) + "cm");
    }

    if (size > 40.0) {
        throw GrowthException("Cob size unrealistically large",
                              getName(), "Corn", size, 30.0);
    }

    cobSize = size;
}

void Corn::setIsSweetCorn(bool sweet) { isSweetCorn = sweet; }