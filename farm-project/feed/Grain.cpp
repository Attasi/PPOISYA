#include "Grain.h"
#include "FeedExceptions.h"
#include <iostream>

Grain::Grain(double quantity, const std::string& grainType, const std::string& processingMethod)
        : Feed("Grain", quantity, 1.2) {
    // Проверки для зерна
    if (quantity > 100000) {
        throw FeedException("Grain quantity too large (max 100,000 kg): " + std::to_string(quantity));
    }
    if (grainType.empty()) {
        throw FeedException("Grain type cannot be empty");
    }
    if (processingMethod.empty()) {
        throw FeedException("Processing method cannot be empty");
    }

    this->grainType = grainType;
    this->processingMethod = processingMethod;
    this->starchContent = 65.0;
    this->testWeight = 72.0;
    this->origin = "Local farm";
    this->isGMO = false;
    this->germinationRate = 95.0;
    this->kernelSize = "Medium";
    this->foreignMaterial = 1.5;

    if (grainType == "Corn") {
        setProteinContent(8.5);
        setName("Corn Grain");
    } else if (grainType == "Wheat") {
        setProteinContent(12.0);
        setName("Wheat Grain");
    } else if (grainType == "Barley") {
        setProteinContent(11.0);
        setName("Barley Grain");
    } else if (grainType == "Oats") {
        setProteinContent(13.0);
        setName("Oats Grain");
    } else {
        throw FeedException("Unknown grain type: " + grainType);
    }

    setFiberContent(10.0);
    setStorageLocation("Grain Silo");
}

void Grain::displayInfo() const {
    Feed::displayInfo();
    std::cout << "--- Grain Specific ---" << std::endl;
    std::cout << "Grain type: " << grainType << std::endl;
    std::cout << "Starch content: " << starchContent << "%" << std::endl;
    std::cout << "Processing method: " << processingMethod << std::endl;
    std::cout << "Test weight: " << testWeight << " kg/hl" << std::endl;
    std::cout << "Origin: " << origin << std::endl;
    std::cout << "GMO: " << (isGMO ? "Yes" : "No") << std::endl;
    std::cout << "Germination rate: " << germinationRate << "%" << std::endl;
    std::cout << "Kernel size: " << kernelSize << std::endl;
    std::cout << "Foreign material: " << foreignMaterial << "%" << std::endl;
}

void Grain::grindGrain() {
    if (processingMethod == "Ground") {
        throw FeedException("Grain is already ground");
    }

    if (getMoistureContent() > 14) {
        throw FeedException("Grain too moist for grinding: " +
                            std::to_string(getMoistureContent()) + "% (max 14%)");
    }

    processingMethod = "Ground";
    std::cout << grainType << " has been ground." << std::endl;
}

void Grain::cleanGrain() {
    if (foreignMaterial <= 0.5) {
        throw FeedException("Grain is already clean enough: " +
                            std::to_string(foreignMaterial) + "% foreign material");
    }

    if (foreignMaterial > 5) {
        throw FeedException("Grain has dangerously high foreign material: " +
                            std::to_string(foreignMaterial) + "% (max 5%)");
    }

    double removed = getQuantity() * (foreignMaterial - 0.5) / 100;
    foreignMaterial = 0.5;
    setQuantity(getQuantity() - removed);
    std::cout << "Cleaned grain. Removed " << removed << " kg of foreign material." << std::endl;
}

void Grain::testGermination() {
    if (germinationRate < 70) {
        throw FeedException("Grain germination rate critically low: " +
                            std::to_string(germinationRate) + "% (min 70% for feed)");
    } else if (germinationRate < 85) {
        std::cout << "Warning: Low germination rate! Not suitable for planting." << std::endl;
    } else if (germinationRate < 90) {
        std::cout << "Germination rate acceptable for feed." << std::endl;
    } else {
        std::cout << "Excellent germination rate." << std::endl;
    }
}

void Grain::mixWithOtherGrains(const std::string& otherGrain, double amount) {
    if (otherGrain.empty()) {
        throw FeedException("Other grain type cannot be empty");
    }
    if (amount <= 0) {
        throw FeedException("Mixing amount must be positive: " + std::to_string(amount));
    }
    if (amount > getQuantity()) {
        throw InsufficientFeedException("Grain for mixing", amount, getQuantity());
    }

    setName(getName() + "/" + otherGrain + " Mix");
    setQuantity(getQuantity() + amount);
    std::cout << "Mixed with " << amount << " kg of " << otherGrain << std::endl;
}

std::string Grain::getGrainType() const { return grainType; }
double Grain::getStarchContent() const { return starchContent; }
std::string Grain::getProcessingMethod() const { return processingMethod; }
double Grain::getTestWeight() const { return testWeight; }
std::string Grain::getOrigin() const { return origin; }
bool Grain::getIsGMO() const { return isGMO; }
double Grain::getGerminationRate() const { return germinationRate; }
std::string Grain::getKernelSize() const { return kernelSize; }
double Grain::getForeignMaterial() const { return foreignMaterial; }

void Grain::setGrainType(const std::string& type) {
    if (type.empty()) {
        throw FeedException("Grain type cannot be empty");
    }
    grainType = type;
    setName(grainType + " Grain");
}

void Grain::setStarchContent(double starch) {
    if (starch < 0 || starch > 100) {
        throw FeedException("Starch content must be between 0-100%: " + std::to_string(starch));
    }
    starchContent = starch;
}

void Grain::setProcessingMethod(const std::string& method) {
    if (method.empty()) {
        throw FeedException("Processing method cannot be empty");
    }
    processingMethod = method;
}

void Grain::setTestWeight(double weight) {
    if (weight <= 0 || weight > 100) {
        throw FeedException("Test weight must be between 0-100 kg/hl: " + std::to_string(weight));
    }
    testWeight = weight;
}

void Grain::setOrigin(const std::string& origin) {
    if (origin.empty()) {
        throw FeedException("Origin cannot be empty");
    }
    this->origin = origin;
}

void Grain::setIsGMO(bool gmo) { isGMO = gmo; }

void Grain::setGerminationRate(double rate) {
    if (rate < 0 || rate > 100) {
        throw FeedException("Germination rate must be between 0-100%: " + std::to_string(rate));
    }
    germinationRate = rate;
}

void Grain::setKernelSize(const std::string& size) {
    if (size.empty()) {
        throw FeedException("Kernel size cannot be empty");
    }
    kernelSize = size;
}

void Grain::setForeignMaterial(double material) {
    if (material < 0 || material > 10) {
        throw FeedException("Foreign material must be between 0-10%: " + std::to_string(material));
    }
    foreignMaterial = material;
}

double Grain::calculateEnergyDensity() const {
    double energy = 3.0; // Mcal/kg базовое значение
    if (grainType == "Corn") energy += 0.5;
    if (starchContent > 70) energy += 0.3;
    if (processingMethod == "Ground") energy += 0.1;
    return energy;
}

bool Grain::isSuitableForAnimal(const std::string& animalType) const {
    if (animalType.empty()) {
        throw FeedException("Animal type cannot be empty");
    }

    if (animalType == "Chicken") {
        if (processingMethod == "Whole") {
            throw FeedException("Chickens cannot digest whole grain");
        }
        if (grainType == "Barley") {
            throw FeedException("Chickens should not be fed barley (digestibility issues)");
        }
        return true;
    } else if (animalType == "Pig") {
        if (grainType != "Corn" && grainType != "Wheat") {
            throw FeedException("Pigs prefer corn or wheat, not " + grainType);
        }
        return true;
    } else if (animalType == "Horse") {
        if (grainType != "Oats") {
            throw FeedException("Horses should primarily eat oats, not " + grainType);
        }
        if (processingMethod != "Whole") {
            throw FeedException("Horses need whole grains for dental health");
        }
        return true;
    }

    return false;
}

void Grain::processToMethod(const std::string& targetMethod) {
    if (targetMethod.empty()) {
        throw FeedException("Target processing method cannot be empty");
    }
    if (processingMethod == targetMethod) {
        throw FeedException("Grain is already processed to " + targetMethod + " method");
    }

    processingMethod = targetMethod;
    std::cout << grainType << " processed to " << targetMethod << " method." << std::endl;
    if (targetMethod == "Ground") {
        setPricePerKg(getPricePerKg() * 1.1); // Молотое зерно дороже
    }
}

void Grain::checkForContaminants() {
    if (foreignMaterial > 5) {
        throw FeedException("CRITICAL: Grain has dangerous level of foreign material: " +
                            std::to_string(foreignMaterial) + "% (max 5%)");
    } else if (foreignMaterial > 2.0) {
        std::cout << "Warning: High level of foreign material detected!" << std::endl;
        setQualityGrade("Low");
    } else if (isGMO && !getIsOrganic()) {
        std::cout << "GMO grain detected (not organic)." << std::endl;
    } else {
        std::cout << "Grain quality check passed." << std::endl;
    }
}