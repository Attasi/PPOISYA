#include "Hay.h"
#include "FeedExceptions.h"
#include <iostream>

Hay::Hay(double quantity, const std::string& grassType, const std::string& cut)
        : Feed("Hay", quantity, 0.8) {
    // Дополнительные проверки для сена
    if (quantity > 50000) {
        throw FeedException("Hay quantity too large (max 50,000 kg): " + std::to_string(quantity));
    }
    if (grassType.empty()) {
        throw FeedException("Grass type cannot be empty");
    }
    if (cut.empty()) {
        throw FeedException("Cut type cannot be empty");
    }

    this->grassType = grassType;
    this->cut = cut;
    this->leafToStemRatio = 0.6;
    this->baleType = "Square";
    this->baleWeight = 20.0;
    this->harvestSeason = "Summer";
    this->isSunCured = true;
    this->color = "Green";
    this->dustContent = 2.5;

    setProteinContent(8.5);
    setFiberContent(30.0);
    setStorageLocation("Barn");
    setExpirationDate("2025-06-30"); // Сено хранится долго
}

void Hay::displayInfo() const {
    Feed::displayInfo();
    std::cout << "--- Hay Specific ---" << std::endl;
    std::cout << "Grass type: " << grassType << std::endl;
    std::cout << "Cut: " << cut << std::endl;
    std::cout << "Leaf to stem ratio: " << leafToStemRatio << std::endl;
    std::cout << "Bale type: " << baleType << std::endl;
    std::cout << "Bale weight: " << baleWeight << " kg" << std::endl;
    std::cout << "Harvest season: " << harvestSeason << std::endl;
    std::cout << "Sun cured: " << (isSunCured ? "Yes" : "No") << std::endl;
    std::cout << "Color: " << color << std::endl;
    std::cout << "Dust content: " << dustContent << "%" << std::endl;
}

void Hay::baleHay() {
    if (baleWeight <= 0) {
        throw FeedException("Bale weight must be positive: " + std::to_string(baleWeight));
    }

    int bales = static_cast<int>(getQuantity() / baleWeight);
    if (bales == 0) {
        throw FeedException("Not enough hay to make bales. Need at least " +
                            std::to_string(baleWeight) + " kg");
    }

    std::cout << "Baled " << getQuantity() << " kg of hay into "
              << bales << " " << baleType << " bales." << std::endl;
}

void Hay::cureHay() {
    if (getMoistureContent() < 5) {
        throw FeedException("Hay is already too dry for curing: " +
                            std::to_string(getMoistureContent()) + "% moisture");
    }

    if (!isSunCured) {
        isSunCured = true;
        setMoistureContent(getMoistureContent() * 0.5); // Уменьшаем влажность
        std::cout << "Hay has been sun cured." << std::endl;
    } else {
        throw FeedException("Hay is already sun cured");
    }
}

void Hay::testMoisture() {
    double moisture = getMoistureContent();
    if (moisture > 20) {
        throw FeedException("DANGER: Hay moisture content critically high: " +
                            std::to_string(moisture) + "% (risk of spontaneous combustion!)");
    } else if (moisture > 15) {
        std::cout << "Warning: Moisture content too high! Risk of mold." << std::endl;
    } else if (moisture < 10) {
        std::cout << "Moisture content very low. May be too dry." << std::endl;
    } else {
        std::cout << "Moisture content is optimal." << std::endl;
    }
}

void Hay::stackBales() {
    if (getStorageLocation().empty()) {
        throw FeedException("Storage location not specified for stacking bales");
    }

    std::cout << "Stacking hay bales in " << getStorageLocation() << std::endl;
}

std::string Hay::getGrassType() const { return grassType; }
std::string Hay::getCut() const { return cut; }
double Hay::getLeafToStemRatio() const { return leafToStemRatio; }
std::string Hay::getBaleType() const { return baleType; }
double Hay::getBaleWeight() const { return baleWeight; }
std::string Hay::getHarvestSeason() const { return harvestSeason; }
bool Hay::getIsSunCured() const { return isSunCured; }
std::string Hay::getColor() const { return color; }
double Hay::getDustContent() const { return dustContent; }

void Hay::setGrassType(const std::string& type) {
    if (type.empty()) {
        throw FeedException("Grass type cannot be empty");
    }
    grassType = type;
}

void Hay::setCut(const std::string& cut) {
    if (cut.empty()) {
        throw FeedException("Cut type cannot be empty");
    }
    this->cut = cut;
}

void Hay::setLeafToStemRatio(double ratio) {
    if (ratio < 0 || ratio > 1) {
        throw FeedException("Leaf to stem ratio must be between 0-1: " + std::to_string(ratio));
    }
    leafToStemRatio = ratio;
}

void Hay::setBaleType(const std::string& type) {
    if (type.empty()) {
        throw FeedException("Bale type cannot be empty");
    }
    baleType = type;
}

void Hay::setBaleWeight(double weight) {
    if (weight <= 0 || weight > 1000) {
        throw FeedException("Bale weight must be between 0-1000 kg: " + std::to_string(weight));
    }
    baleWeight = weight;
}

void Hay::setHarvestSeason(const std::string& season) {
    if (season.empty()) {
        throw FeedException("Harvest season cannot be empty");
    }
    harvestSeason = season;
}

void Hay::setIsSunCured(bool cured) { isSunCured = cured; }

void Hay::setColor(const std::string& color) {
    if (color.empty()) {
        throw FeedException("Color cannot be empty");
    }
    this->color = color;
}

void Hay::setDustContent(double dust) {
    if (dust < 0 || dust > 10) {
        throw FeedException("Dust content must be between 0-10%: " + std::to_string(dust));
    }
    dustContent = dust;
}

double Hay::calculateEnergyValue() const {
    double energy = 1.5; // Mcal/kg базовое значение
    if (grassType == "Alfalfa") energy += 0.3;
    if (cut == "Second") energy += 0.2;
    if (leafToStemRatio > 0.7) energy += 0.1;
    return energy;
}

bool Hay::isSuitableForAnimal(const std::string& animalType) const {
    if (animalType.empty()) {
        throw FeedException("Animal type cannot be empty");
    }

    if (animalType == "Horse") {
        if (dustContent > 3) {
            throw FeedException("Hay dust content too high for horses: " +
                                std::to_string(dustContent) + "% (max 3%)");
        }
        if (grassType != "Timothy" && grassType != "Orchard") {
            throw FeedException("Horses require Timothy or Orchard grass, not " + grassType);
        }
        return true;
    } else if (animalType == "Cow") {
        if (getProteinContent() < 7) {
            throw InsufficientFeedException(animalType, 7.0, getProteinContent());
        }
        return true;
    } else if (animalType == "Rabbit") {
        if (grassType != "Timothy") {
            throw FeedException("Rabbits require Timothy grass, not " + grassType);
        }
        if (getFiberContent() < 25) {
            throw FeedException("Hay fiber content too low for rabbits: " +
                                std::to_string(getFiberContent()) + "% (min 25%)");
        }
        return true;
    }

    return false;
}

void Hay::compressBales() {
    if (baleType != "Square") {
        throw FeedException("Only square bales can be compressed");
    }
    if (baleWeight > 25) {
        throw FeedException("Bales already too heavy for compression: " +
                            std::to_string(baleWeight) + " kg (max 25 kg before compression)");
    }

    baleWeight *= 1.5;
    std::cout << "Bales compressed. New bale weight: " << baleWeight << " kg" << std::endl;
}

void Hay::gradeHay() {
    if (getProteinContent() > 10 && leafToStemRatio > 0.7 && color == "Green") {
        setQualityGrade("Premium");
        setPricePerKg(getPricePerKg() * 1.3);
    } else if (getProteinContent() > 8 && leafToStemRatio > 0.5) {
        setQualityGrade("Good");
    } else {
        setQualityGrade("Standard");
    }
    std::cout << "Hay graded as: " << getQualityGrade() << std::endl;
}