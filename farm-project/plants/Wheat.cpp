#include "Wheat.h"
#include "PlantExceptions.h"
#include <iostream>

Wheat::Wheat(double height, double yield, bool winterWheat)
        : Crop("Wheat", height, yield), grainQuality(80.0),
          isWinterWheat(winterWheat), glutenContent(12) {

    if (isWinterWheat) {
        setSeason("winter");
    } else {
        setSeason("spring");
    }

    // Дополнительные проверки для пшеницы
    if (height > 2.0) {
        throw GrowthException("Wheat height too tall",
                              getName(), "Wheat", height, 2.0);
    }

    if (height < 0.3) {
        throw GrowthException("Wheat height too short",
                              getName(), "Wheat", height, 0.3);
    }

    if (yield > 10000.0) {
        throw PlantException("Wheat yield unrealistically large: " +
                             std::to_string(yield) + "kg (max 10,000kg)");
    }
}

double Wheat::grindIntoFlour() const {
    if (!isReadyForHarvest()) {
        throw HarvestException("Wheat not ready for grinding",
                               getName(), "Wheat", getYield(), 0.0,
                               "Not harvest-ready");
    }

    if (grainQuality <= 70.0) {
        throw HarvestException("Wheat quality too low for flour",
                               getName(), "Wheat", 70.0, grainQuality,
                               "Poor grain quality");
    }

    double flourAmount = getYield() * 0.75;

    if (flourAmount <= 0) {
        throw HarvestException("No flour produced from wheat",
                               getName(), "Wheat", getYield(), 0.0,
                               "Zero or negative flour amount");
    }

    std::cout << "Ground " << getYield() << "kg of wheat into "
              << flourAmount << "kg of flour." << std::endl;

    return flourAmount;
}

std::string Wheat::getQualityGrade() const {
    if (grainQuality >= 90.0) return "Premium";
    if (grainQuality >= 75.0) return "First Grade";
    if (grainQuality >= 60.0) return "Second Grade";
    return "Feed Grade";
}

void Wheat::treatForPests() {
    if (getHealth() <= 20.0) {
        throw PlantDiseaseException("Wheat too weak for pest treatment",
                                    getName(), "Wheat", "Critical Condition", 9,
                                    {"all"});
    }

    if (getHealth() > 95.0) {
        throw PlantException(getName() + " is already healthy, no need for pest treatment");
    }

    setHealth(getHealth() + 20.0);
    if (getHealth() > 100.0) setHealth(100.0);

    grainQuality += 10.0;
    if (grainQuality > 100.0) grainQuality = 100.0;

    std::cout << getName() << " treated for pests. Quality improved." << std::endl;
}

void Wheat::displayInfo() const {
    Crop::displayInfo();
    std::cout << "  Variety: Wheat"
              << ", Type: " << (isWinterWheat ? "Winter" : "Spring")
              << ", Grain quality: " << grainQuality << "%"
              << ", Gluten: " << glutenContent << "%"
              << ", Quality grade: " << getQualityGrade() << std::endl;
}

double Wheat::calculateExpectedYield() const {
    double baseYield = Crop::calculateExpectedYield();

    if (isWinterWheat) baseYield *= 1.15;
    if (grainQuality > 80.0) baseYield *= 1.1;

    // Проверка на аномальную урожайность
    if (baseYield > getYield() * 5.0) {
        throw HarvestException("Suspiciously high expected yield",
                               getName(), "Wheat", getYield(), baseYield,
                               "Unrealistic growth factors");
    }

    if (baseYield <= 0) {
        throw HarvestException("Negative or zero expected yield",
                               getName(), "Wheat", getYield(), baseYield,
                               "Calculation error");
    }

    return baseYield;
}

double Wheat::getGrainQuality() const { return grainQuality; }
bool Wheat::getIsWinterWheat() const { return isWinterWheat; }
int Wheat::getGlutenContent() const { return glutenContent; }

void Wheat::setGrainQuality(double quality) {
    if (quality < 0 || quality > 100.0) {
        throw PlantException("Grain quality must be between 0-100%: " +
                             std::to_string(quality));
    }

    if (quality < 30.0) {
        throw PlantDiseaseException("Very poor grain quality set",
                                    getName(), "Wheat", "Low Quality", 7,
                                    {"grains"});
    }

    grainQuality = quality;
}

void Wheat::setGlutenContent(int gluten) {
    if (gluten < 0 || gluten > 50) {
        throw PlantException("Gluten content must be between 0-50%: " +
                             std::to_string(gluten));
    }

    if (gluten < 8 && isWinterWheat) {
        throw PlantException("Winter wheat gluten content too low: " +
                             std::to_string(gluten) + "% (min 8%)");
    }

    glutenContent = gluten;
}