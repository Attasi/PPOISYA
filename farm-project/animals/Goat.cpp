#include "Goat.h"
#include "AnimalExceptions.h"
#include <iostream>

Goat::Goat(const std::string& name, int age, double weight, const std::string& breed)
        : Mammal(name, age, weight, breed, true, 32) {
    // Проверки для коз
    if (weight < 10 || weight > 100) {
        throw AnimalException("Goat weight must be between 10-100 kg: " + std::to_string(weight));
    }

    setPrice(400.0);
    setFurColor("Brown and White");
    setHabitatType("Mountainous");

    milkFatContent = 4.5;
    hornShape = "Curved";
    climbingAbility = 8;
    grazingTerrain = "Mountain";
    cheeseProduction = 2.5;
    beardType = "Long";
    agilityScore = 85;
    favoriteClimbingSpot = "Rocky Hill";
    isStubborn = true;
}

void Goat::makeSound() const {
    std::cout << getName() << " says: Maa!" << std::endl;
}

void Goat::climb() {
    if (climbingAbility <= 0) {
        throw AnimalException(getName() + " has no climbing ability (score: " +
                              std::to_string(climbingAbility) + ")");
    }
    if (favoriteClimbingSpot.empty()) {
        throw AnimalException(getName() + " has no favorite climbing spot");
    }

    // Оригинальный код
    std::cout << getName() << " is climbing with ability score " << climbingAbility << "/10." << std::endl;
    setHappinessLevel(getHappinessLevel() + 20);
    setHungerLevel(getHungerLevel() + 10);
}

void Goat::produceMilk() {
    if (getAge() < 1) {
        throw AnimalException(getName() + " is too young to produce milk (age: " +
                              std::to_string(getAge()) + ")");
    }
    if (milkFatContent <= 0) {
        throw AnimalException(getName() + " milk fat content must be positive: " +
                              std::to_string(milkFatContent));
    }

    // Оригинальный код
    if (getAge() > 1) {
        double milkAmount = 3.0; // liters per day
        std::cout << getName() << " produced " << milkAmount << " liters of milk with "
                  << milkFatContent << "% fat content." << std::endl;
        cheeseProduction = milkAmount * 0.1; // 10% becomes cheese
    }
}

void Goat::headButt() {
    if (hornShape.empty()) {
        throw AnimalException(getName() + " horn shape not specified");
    }

    std::cout << getName() << " does a head butt with its " << hornShape << " horns!" << std::endl;
    if (isStubborn) {
        std::cout << getName() << " is being stubborn!" << std::endl;
    }
}

void Goat::browse() {
    if (grazingTerrain.empty()) {
        throw AnimalException(getName() + " has no grazing terrain specified");
    }

    std::cout << getName() << " is browsing in " << grazingTerrain << " terrain." << std::endl;
    setHungerLevel(getHungerLevel() - 20);
}

double Goat::getMilkFatContent() const { return milkFatContent; }
std::string Goat::getHornShape() const { return hornShape; }
int Goat::getClimbingAbility() const { return climbingAbility; }
std::string Goat::getGrazingTerrain() const { return grazingTerrain; }
double Goat::getCheeseProduction() const { return cheeseProduction; }
std::string Goat::getBeardType() const { return beardType; }
int Goat::getAgilityScore() const { return agilityScore; }
std::string Goat::getFavoriteClimbingSpot() const { return favoriteClimbingSpot; }
bool Goat::getIsStubborn() const { return isStubborn; }

void Goat::setMilkFatContent(double fat) {
    if (fat < 0 || fat > 10) {
        throw AnimalException(getName() + " milk fat content must be between 0-10%: " +
                              std::to_string(fat));
    }
    milkFatContent = fat;
}

void Goat::setHornShape(const std::string& shape) {
    if (shape.empty()) {
        throw AnimalException("Horn shape cannot be empty");
    }
    hornShape = shape;
}

void Goat::setClimbingAbility(int ability) {
    if (ability < 0 || ability > 10) {
        throw AnimalException(getName() + " climbing ability must be between 0-10: " +
                              std::to_string(ability));
    }
    climbingAbility = ability;
}

void Goat::setGrazingTerrain(const std::string& terrain) {
    if (terrain.empty()) {
        throw AnimalException("Grazing terrain cannot be empty");
    }
    grazingTerrain = terrain;
}

void Goat::setCheeseProduction(double production) {
    if (production < 0 || production > 10) {
        throw AnimalException(getName() + " cheese production must be between 0-10 kg/month: " +
                              std::to_string(production));
    }
    cheeseProduction = production;
}

void Goat::setBeardType(const std::string& type) {
    if (type.empty()) {
        throw AnimalException("Beard type cannot be empty");
    }
    beardType = type;
}

void Goat::setAgilityScore(int score) {
    if (score < 0 || score > 100) {
        throw AnimalException(getName() + " agility score must be between 0-100: " +
                              std::to_string(score));
    }
    agilityScore = score;
}

void Goat::setFavoriteClimbingSpot(const std::string& spot) {
    if (spot.empty()) {
        throw AnimalException("Favorite climbing spot cannot be empty");
    }
    favoriteClimbingSpot = spot;
}

void Goat::setIsStubborn(bool stubborn) { isStubborn = stubborn; }

double Goat::calculateDailyFood() const {
    double base = Mammal::calculateDailyFood();
    if (climbingAbility > 5) base *= 1.2;
    if (isStubborn) base *= 1.1;
    return base;
}

void Goat::displayInfo() const {
    Mammal::displayInfo();
    std::cout << "--- Goat Specific ---" << std::endl;
    std::cout << "Milk Fat Content: " << milkFatContent << "%" << std::endl;
    std::cout << "Horn Shape: " << hornShape << std::endl;
    std::cout << "Climbing Ability: " << climbingAbility << "/10" << std::endl;
    std::cout << "Grazing Terrain: " << grazingTerrain << std::endl;
    std::cout << "Cheese Production: " << cheeseProduction << " kg/month" << std::endl;
    std::cout << "Beard Type: " << beardType << std::endl;
    std::cout << "Agility Score: " << agilityScore << "/100" << std::endl;
    std::cout << "Favorite Climbing Spot: " << favoriteClimbingSpot << std::endl;
    std::cout << "Stubborn: " << (isStubborn ? "Yes" : "No") << std::endl;
}

void Goat::makeCheese() {
    if (cheeseProduction <= 0) {
        throw AnimalException(getName() + " produces no milk for cheese");
    }
    if (milkFatContent < 2.0) {
        throw AnimalException(getName() + " milk fat content too low for cheese (" +
                              std::to_string(milkFatContent) + "%, need at least 2.0%)");
    }

    std::cout << "Making cheese from " << getName() << "'s milk. Expected yield: "
              << cheeseProduction << " kg" << std::endl;
}

double Goat::calculateMilkValue() const {
    if (milkFatContent <= 0) {
        throw AnimalException(getName() + " milk fat content must be positive: " +
                              std::to_string(milkFatContent));
    }

    return milkFatContent * 2.0; // $2 per % fat
}

void Goat::challengeToClimb() {
    if (favoriteClimbingSpot.empty()) {
        throw AnimalException(getName() + " has no favorite climbing spot");
    }

    std::cout << "Challenging " << getName() << " to climb " << favoriteClimbingSpot << std::endl;
    if (climbingAbility > 7) {
        std::cout << getName() << " accepted the challenge!" << std::endl;
    } else {
        std::cout << getName() << " is not confident enough." << std::endl;
    }
}