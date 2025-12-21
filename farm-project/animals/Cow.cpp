#include "Cow.h"
#include "AnimalExceptions.h"
#include <iostream>

Cow::Cow(const std::string& name, int age, double weight, const std::string& breed)
        : Mammal(name, age, weight, breed, true, 32) {
    // Проверки для коров
    if (weight < 100 || weight > 1200) {
        throw AnimalException("Cow weight must be between 100-1200 kg: " + std::to_string(weight));
    }

    setPrice(1500.0);
    setHabitatType("Pasture");

    milkProduction = 20.0;
    hornType = "Curved";
    milkQuality = 8;
    isMilking = false;
    pastureArea = "North Pasture";
    grazingHours = 6;
    methaneProduction = 250.0;
    cowbellSound = "Ding-dong";
    hasBell = true;
}

void Cow::makeSound() const {
    std::cout << getName() << " says: Moooo!" << std::endl;
}

void Cow::produceMilk() {
    if (getAge() < 2) {
        throw AnimalException(getName() + " is too young to produce milk (age: " + std::to_string(getAge()) + ")");
    }
    if (!getIsHealthy()) {
        throw AnimalHealthException(getName(), "Mastitis - cannot produce milk");
    }
    if (!getIsPregnant() && getAge() < 3) {
        throw AnimalException(getName() + " must be pregnant or older than 3 years to produce milk");
    }

    // Оригинальный код
    if (getIsPregnant() || getAge() > 2) {
        std::cout << getName() << " produced " << milkProduction << " liters of milk." << std::endl;
        if (isMilking) {
            setHappinessLevel(getHappinessLevel() - 5);
        } else {
            setHappinessLevel(getHappinessLevel() - 2);
        }
    } else {
        std::cout << getName() << " is too young to produce milk." << std::endl;
    }
}

void Cow::graze() {
    if (grazingHours <= 0) {
        throw AnimalException(getName() + " cannot graze for non-positive hours: " + std::to_string(grazingHours));
    }
    if (pastureArea.empty()) {
        throw AnimalException(getName() + " has no pasture area assigned");
    }

    // Оригинальный код
    std::cout << getName() << " is grazing in " << pastureArea << " for " << grazingHours << " hours." << std::endl;
    setHungerLevel(getHungerLevel() - 30);
    setHappinessLevel(getHappinessLevel() + 15);
    setWeight(getWeight() + 0.5);
}

void Cow::ringBell() {
    if (!hasBell) {
        throw AnimalException(getName() + " doesn't have a bell to ring");
    }

    // Оригинальный код
    if (hasBell) {
        std::cout << getName() << "'s bell sounds: " << cowbellSound << std::endl;
    }
}

void Cow::chewCud() {
    if (!getIsHealthy()) {
        throw AnimalHealthException(getName(), "Digestive problems - cannot chew cud");
    }

    std::cout << getName() << " is chewing cud." << std::endl;
    setHappinessLevel(getHappinessLevel() + 10);
}

double Cow::getMilkProduction() const { return milkProduction; }
std::string Cow::getHornType() const { return hornType; }
int Cow::getMilkQuality() const { return milkQuality; }
bool Cow::getIsMilking() const { return isMilking; }
std::string Cow::getPastureArea() const { return pastureArea; }
int Cow::getGrazingHours() const { return grazingHours; }
double Cow::getMethaneProduction() const { return methaneProduction; }
std::string Cow::getCowbellSound() const { return cowbellSound; }
bool Cow::getHasBell() const { return hasBell; }

void Cow::setMilkProduction(double production) {
    if (production < 0 || production > 50) {
        throw AnimalException(getName() + " milk production must be between 0-50 liters: " + std::to_string(production));
    }
    milkProduction = production;
}

void Cow::setHornType(const std::string& type) {
    if (type.empty()) {
        throw AnimalException("Horn type cannot be empty");
    }
    hornType = type;
}

void Cow::setMilkQuality(int quality) {
    if (quality < 1 || quality > 10) {
        throw AnimalException(getName() + " milk quality must be between 1-10: " + std::to_string(quality));
    }
    milkQuality = quality;
}

void Cow::setIsMilking(bool milking) { isMilking = milking; }

void Cow::setPastureArea(const std::string& area) {
    if (area.empty()) {
        throw AnimalException("Pasture area cannot be empty");
    }
    pastureArea = area;
}

void Cow::setGrazingHours(int hours) {
    if (hours < 0 || hours > 24) {
        throw AnimalException(getName() + " grazing hours must be between 0-24: " + std::to_string(hours));
    }
    grazingHours = hours;
}

void Cow::setMethaneProduction(double methane) {
    if (methane < 0 || methane > 1000) {
        throw AnimalException(getName() + " methane production must be between 0-1000 liters: " + std::to_string(methane));
    }
    methaneProduction = methane;
}

void Cow::setCowbellSound(const std::string& sound) {
    if (sound.empty()) {
        throw AnimalException("Cowbell sound cannot be empty");
    }
    cowbellSound = sound;
}

void Cow::setHasBell(bool hasBell) { this->hasBell = hasBell; }

double Cow::calculateDailyFood() const {
    double base = Mammal::calculateDailyFood();
    if (isMilking) base *= 1.4;
    if (getIsPregnant()) base *= 1.3;
    return base;
}

void Cow::displayInfo() const {
    Mammal::displayInfo();
    std::cout << "--- Cow Specific ---" << std::endl;
    std::cout << "Milk Production: " << milkProduction << " liters/day" << std::endl;
    std::cout << "Horn Type: " << hornType << std::endl;
    std::cout << "Milk Quality: " << milkQuality << "/10" << std::endl;
    std::cout << "Currently Milking: " << (isMilking ? "Yes" : "No") << std::endl;
    std::cout << "Pasture Area: " << pastureArea << std::endl;
    std::cout << "Grazing Hours: " << grazingHours << " hours/day" << std::endl;
    std::cout << "Methane Production: " << methaneProduction << " liters/day" << std::endl;
    std::cout << "Has Bell: " << (hasBell ? "Yes" : "No") << std::endl;
    if (hasBell) {
        std::cout << "Cowbell Sound: " << cowbellSound << std::endl;
    }
}

double Cow::calculateMilkValue() const {
    if (milkProduction <= 0) {
        throw AnimalException(getName() + " produces no milk");
    }
    if (milkQuality < 1) {
        throw AnimalException(getName() + " milk quality is invalid: " + std::to_string(milkQuality));
    }

    return milkProduction * milkQuality * 0.5; // $0.5 per quality liter
}

void Cow::startMilkingSession() {
    if (!getIsHealthy()) {
        throw AnimalHealthException(getName(), "Health issue - cannot start milking");
    }
    if (isMilking) {
        throw AnimalException(getName() + " is already being milked");
    }

    isMilking = true;
    std::cout << "Started milking session for " << getName() << std::endl;
}

void Cow::stopMilkingSession() {
    if (!isMilking) {
        throw AnimalException(getName() + " is not being milked");
    }

    isMilking = false;
    std::cout << "Stopped milking session for " << getName() << std::endl;
}