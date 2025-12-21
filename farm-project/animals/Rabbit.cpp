#include "Rabbit.h"
#include "AnimalExceptions.h"
#include <iostream>

Rabbit::Rabbit(const std::string& name, int age, double weight, const std::string& breed)
        : Mammal(name, age, weight, breed, true, 28) {
    // Проверки для кроликов
    if (weight < 0.5 || weight > 10.0) {
        throw AnimalException("Rabbit weight must be between 0.5-10.0 kg: " + std::to_string(weight));
    }

    setPrice(50.0);
    setFurColor("White");
    setHabitatType("Hutch");

    earLength = 8;
    furType = "Angora";
    burrowingDepth = 2;
    hutchNumber = "Hutch-5";
    jumpHeight = 60;
    favoriteVegetable = "Carrot";
    breedingRate = 8;
    personalityType = "Curious";
    isNervous = true;
}

void Rabbit::makeSound() const {
    std::cout << getName() << " makes a soft thumping sound." << std::endl;
}

void Rabbit::hop() {
    if (jumpHeight <= 0) {
        throw AnimalException(getName() + " jump height must be positive: " +
                              std::to_string(jumpHeight));
    }
    if (!getIsHealthy()) {
        throw AnimalHealthException(getName(), "Leg injury - cannot hop");
    }

    // Оригинальный код
    std::cout << getName() << " hops " << jumpHeight << " cm high!" << std::endl;
    setHappinessLevel(getHappinessLevel() + 15);
    setHungerLevel(getHungerLevel() + 5);
}

void Rabbit::digBurrow() {
    if (burrowingDepth <= 0) {
        throw AnimalException(getName() + " burrowing depth must be positive: " +
                              std::to_string(burrowingDepth));
    }
    if (hutchNumber.empty()) {
        throw AnimalException(getName() + " has no hutch number assigned");
    }

    // Оригинальный код
    std::cout << getName() << " is digging a burrow " << burrowingDepth << " meters deep." << std::endl;
    setHappinessLevel(getHappinessLevel() + 20);
}

void Rabbit::twitchNose() {
    if (personalityType.empty()) {
        throw AnimalException(getName() + " personality type not specified");
    }

    std::cout << getName() << " is twitching its nose curiously." << std::endl;
    if (isNervous) {
        std::cout << getName() << " seems nervous!" << std::endl;
    }
}

void Rabbit::sleep() {
    if (getAge() < 0.1) {
        throw AnimalException(getName() + " is too young to sleep properly (age: " +
                              std::to_string(getAge()) + ")");
    }

    std::cout << getName() << " is sleeping lightly (rabbits are light sleepers)." << std::endl;
    Animal::sleep(6); // Rabbits sleep about 6 hours
    if (isNervous) {
        setHappinessLevel(getHappinessLevel() - 5); // Nervous rabbits don't sleep well
    }
}

int Rabbit::getEarLength() const { return earLength; }
std::string Rabbit::getFurType() const { return furType; }
int Rabbit::getBurrowingDepth() const { return burrowingDepth; }
std::string Rabbit::getHutchNumber() const { return hutchNumber; }
int Rabbit::getJumpHeight() const { return jumpHeight; }
std::string Rabbit::getFavoriteVegetable() const { return favoriteVegetable; }
int Rabbit::getBreedingRate() const { return breedingRate; }
std::string Rabbit::getPersonalityType() const { return personalityType; }
bool Rabbit::getIsNervous() const { return isNervous; }

void Rabbit::setEarLength(int length) {
    if (length < 0 || length > 20) {
        throw AnimalException(getName() + " ear length must be between 0-20 cm: " +
                              std::to_string(length));
    }
    earLength = length;
}

void Rabbit::setFurType(const std::string& type) {
    if (type.empty()) {
        throw AnimalException("Fur type cannot be empty");
    }
    furType = type;
}

void Rabbit::setBurrowingDepth(int depth) {
    if (depth < 0 || depth > 5) {
        throw AnimalException(getName() + " burrowing depth must be between 0-5 meters: " +
                              std::to_string(depth));
    }
    burrowingDepth = depth;
}

void Rabbit::setHutchNumber(const std::string& hutch) {
    if (hutch.empty()) {
        throw AnimalException("Hutch number cannot be empty");
    }
    hutchNumber = hutch;
}

void Rabbit::setJumpHeight(int height) {
    if (height < 0 || height > 100) {
        throw AnimalException(getName() + " jump height must be between 0-100 cm: " +
                              std::to_string(height));
    }
    jumpHeight = height;
}

void Rabbit::setFavoriteVegetable(const std::string& vegetable) {
    if (vegetable.empty()) {
        throw AnimalException("Favorite vegetable cannot be empty");
    }
    favoriteVegetable = vegetable;
}

void Rabbit::setBreedingRate(int rate) {
    if (rate < 0 || rate > 10) {
        throw AnimalException(getName() + " breeding rate must be between 0-10: " +
                              std::to_string(rate));
    }
    breedingRate = rate;
}

void Rabbit::setPersonalityType(const std::string& personality) {
    if (personality.empty()) {
        throw AnimalException("Personality type cannot be empty");
    }
    personalityType = personality;
}

void Rabbit::setIsNervous(bool nervous) { isNervous = nervous; }

double Rabbit::calculateDailyFood() const {
    double base = Mammal::calculateDailyFood();
    if (getIsPregnant()) base *= 1.5;
    if (isNervous) base *= 0.8; // Nervous rabbits eat less
    return base;
}

void Rabbit::displayInfo() const {
    Mammal::displayInfo();
    std::cout << "--- Rabbit Specific ---" << std::endl;
    std::cout << "Ear Length: " << earLength << " cm" << std::endl;
    std::cout << "Fur Type: " << furType << std::endl;
    std::cout << "Burrowing Depth: " << burrowingDepth << " meters" << std::endl;
    std::cout << "Hutch Number: " << hutchNumber << std::endl;
    std::cout << "Jump Height: " << jumpHeight << " cm" << std::endl;
    std::cout << "Favorite Vegetable: " << favoriteVegetable << std::endl;
    std::cout << "Breeding Rate: " << breedingRate << "/10" << std::endl;
    std::cout << "Personality: " << personalityType << std::endl;
    std::cout << "Nervous: " << (isNervous ? "Yes" : "No") << std::endl;
}

void Rabbit::breed() {
    if (getAge() < 6) {
        throw AnimalBreedingException(getName(), getAge(), 6);
    }
    if (breedingRate <= 5) {
        throw AnimalException(getName() + " breeding rate too low: " +
                              std::to_string(breedingRate) + "/10 (need at least 6)");
    }
    if (!getIsHealthy()) {
        throw AnimalHealthException(getName(), "Reproductive issues - cannot breed");
    }

    // Оригинальный код
    std::cout << getName() << " is ready to breed. Breeding rate: " << breedingRate << "/10" << std::endl;
    if (!getIsPregnant()) {
        setIsPregnant(true);
        setPregnancyMonths(1);
        std::cout << getName() << " is now pregnant!" << std::endl;
    }
}

void Rabbit::cleanHutch() {
    if (hutchNumber.empty()) {
        throw AnimalException(getName() + " has no hutch number to clean");
    }

    std::cout << "Cleaning hutch " << hutchNumber << " for " << getName() << std::endl;
    setHappinessLevel(getHappinessLevel() + 25);
    setIsHealthy(true);
}

void Rabbit::calmDown() {
    if (!isNervous) {
        throw AnimalException(getName() + " is not nervous");
    }

    std::cout << "Calming down " << getName() << std::endl;
    isNervous = false;
    setHappinessLevel(getHappinessLevel() + 20);
}