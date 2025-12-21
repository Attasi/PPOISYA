#include "Sheep.h"
#include "AnimalExceptions.h"
#include <iostream>

Sheep::Sheep(const std::string& name, int age, double weight, const std::string& breed)
        : Mammal(name, age, weight, breed, true, 32) {
    // Проверки для овец
    if (weight < 20 || weight > 150) {
        throw AnimalException("Sheep weight must be between 20-150 kg: " + std::to_string(weight));
    }

    setPrice(300.0);
    setFurColor("White");
    setHabitatType("Mountain");

    woolProduction = 4.5;
    woolQuality = "Fine";
    isSheared = false;
    flockNumber = "Flock-A";
    grazingRadius = 500;
    woolLength = 8.0;
    shepherdCall = "Baa-baa";
    hasLambs = false;
    lambCount = 0;
}

void Sheep::makeSound() const {
    std::cout << getName() << " says: Baa!" << std::endl;
}

void Sheep::produceWool() {
    if (isSheared) {
        throw AnimalException(getName() + " has been sheared recently, cannot produce wool yet");
    }
    if (woolLength >= 15.0) {
        throw AnimalException(getName() + " wool is already too long (" +
                              std::to_string(woolLength) + " cm), needs shearing");
    }

    // Оригинальный код
    if (!isSheared) {
        woolLength += 0.1;
        std::cout << getName() << "'s wool is growing. Current length: " << woolLength << " cm" << std::endl;
    }
}

void Sheep::graze() const {
    if (grazingRadius <= 0) {
        throw AnimalException(getName() + " grazing radius must be positive: " +
                              std::to_string(grazingRadius));
    }
    if (flockNumber.empty()) {
        throw AnimalException(getName() + " has no flock number assigned");
    }

    std::cout << getName() << " is grazing within " << grazingRadius << " meters radius." << std::endl;
}

void Sheep::followShepherd() {
    if (shepherdCall.empty()) {
        throw AnimalException(getName() + " has no shepherd call specified");
    }

    std::cout << getName() << " is following the shepherd's call: " << shepherdCall << std::endl;
    setHappinessLevel(getHappinessLevel() + 10);
}

void Sheep::bleat() {
    if (shepherdCall.empty()) {
        throw AnimalException(getName() + " has no shepherd call to bleat");
    }

    std::cout << getName() << " bleats: " << shepherdCall << "!" << std::endl;
}

double Sheep::getWoolProduction() const { return woolProduction; }
std::string Sheep::getWoolQuality() const { return woolQuality; }
bool Sheep::getIsSheared() const { return isSheared; }
std::string Sheep::getFlockNumber() const { return flockNumber; }
int Sheep::getGrazingRadius() const { return grazingRadius; }
double Sheep::getWoolLength() const { return woolLength; }
std::string Sheep::getShepherdCall() const { return shepherdCall; }
bool Sheep::getHasLambs() const { return hasLambs; }
int Sheep::getLambCount() const { return lambCount; }

void Sheep::setWoolProduction(double production) {
    if (production < 0 || production > 10) {
        throw AnimalException(getName() + " wool production must be between 0-10 kg/year: " +
                              std::to_string(production));
    }
    woolProduction = production;
}

void Sheep::setWoolQuality(const std::string& quality) {
    if (quality.empty()) {
        throw AnimalException("Wool quality cannot be empty");
    }
    woolQuality = quality;
}

void Sheep::setIsSheared(bool sheared) { isSheared = sheared; }

void Sheep::setFlockNumber(const std::string& flock) {
    if (flock.empty()) {
        throw AnimalException("Flock number cannot be empty");
    }
    flockNumber = flock;
}

void Sheep::setGrazingRadius(int radius) {
    if (radius < 0 || radius > 5000) {
        throw AnimalException(getName() + " grazing radius must be between 0-5000 meters: " +
                              std::to_string(radius));
    }
    grazingRadius = radius;
}

void Sheep::setWoolLength(double length) {
    if (length < 0 || length > 20) {
        throw AnimalException(getName() + " wool length must be between 0-20 cm: " +
                              std::to_string(length));
    }
    woolLength = length;
}

void Sheep::setShepherdCall(const std::string& call) {
    if (call.empty()) {
        throw AnimalException("Shepherd call cannot be empty");
    }
    shepherdCall = call;
}

void Sheep::setHasLambs(bool hasLambs) { this->hasLambs = hasLambs; }

void Sheep::setLambCount(int count) {
    if (count < 0 || count > 5) {
        throw AnimalException(getName() + " lamb count must be between 0-5: " +
                              std::to_string(count));
    }
    lambCount = count;
}

double Sheep::calculateDailyFood() const {
    double base = Mammal::calculateDailyFood();
    if (hasLambs) base *= 1.3;
    if (woolLength > 10.0) base *= 1.1;
    return base;
}

void Sheep::displayInfo() const {
    Mammal::displayInfo();
    std::cout << "--- Sheep Specific ---" << std::endl;
    std::cout << "Wool Production: " << woolProduction << " kg/year" << std::endl;
    std::cout << "Wool Quality: " << woolQuality << std::endl;
    std::cout << "Sheared: " << (isSheared ? "Yes" : "No") << std::endl;
    std::cout << "Flock Number: " << flockNumber << std::endl;
    std::cout << "Grazing Radius: " << grazingRadius << " meters" << std::endl;
    std::cout << "Wool Length: " << woolLength << " cm" << std::endl;
    std::cout << "Shepherd Call: " << shepherdCall << std::endl;
    std::cout << "Has Lambs: " << (hasLambs ? "Yes" : "No") << std::endl;
    if (hasLambs) {
        std::cout << "Lamb Count: " << lambCount << std::endl;
    }
}

void Sheep::shearWool() {
    if (isSheared) {
        throw AnimalException(getName() + " has already been sheared");
    }
    if (woolLength < 5.0) {
        throw AnimalException(getName() + " wool is too short for shearing (" +
                              std::to_string(woolLength) + " cm, need at least 5.0 cm)");
    }
    if (!getIsHealthy()) {
        throw AnimalHealthException(getName(), "Skin infection - cannot shear");
    }

    // Оригинальный код
    std::cout << "Shearing " << getName() << ". Wool collected: " << woolLength * 0.1 << " kg" << std::endl;
    isSheared = true;
    woolLength = 1.0;
    setHappinessLevel(getHappinessLevel() - 15);
}

double Sheep::calculateWoolValue() const {
    if (woolProduction <= 0) {
        throw AnimalException(getName() + " produces no wool");
    }
    if (woolQuality.empty()) {
        throw AnimalException(getName() + " wool quality not specified");
    }

    double value = 0;
    if (woolQuality == "Fine") value = 15.0;
    else if (woolQuality == "Medium") value = 10.0;
    else if (woolQuality == "Coarse") value = 5.0;
    else {
        throw AnimalException(getName() + " has unknown wool quality: " + woolQuality);
    }

    return woolProduction * value;
}

void Sheep::addLamb() {
    if (!getIsPregnant()) {
        throw AnimalException(getName() + " is not pregnant, cannot add lamb");
    }
    if (getPregnancyMonths() < 5) {
        throw AnimalException(getName() + " pregnancy is not advanced enough (only " +
                              std::to_string(getPregnancyMonths()) + " months)");
    }

    hasLambs = true;
    lambCount++;
    std::cout << getName() << " now has " << lambCount << " lamb(s)." << std::endl;
}