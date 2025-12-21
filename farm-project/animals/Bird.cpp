#include "Bird.h"
#include "AnimalExceptions.h"
#include <iostream>

Bird::Bird(const std::string& name, int age, double weight, const std::string& breed,
           double wingspan, bool canFly)
        : Animal(name, age, weight, breed) {
    // Проверки для птиц
    if (wingspan < 0 || wingspan > 5.0) {
        throw AnimalException(getName() + " wingspan must be between 0-5.0 meters: " +
                              std::to_string(wingspan));
    }

    this->wingspan = wingspan;
    this->canFly = canFly;
    this->featherColor = "Brown";
    this->eggsLaid = 0;
    this->incubationPeriod = 21;
    this->migrates = false;
    this->beakType = "Short";
    this->flightSpeed = 20.0;
    this->nestingMaterial = "Twigs";
}

void Bird::makeSound() const {
    std::cout << getName() << " chirps!" << std::endl;
}

void Bird::fly() {
    if (!canFly) {
        throw AnimalException(getName() + " cannot fly");
    }
    if (!getIsHealthy()) {
        throw AnimalHealthException(getName(), "Wing injury - cannot fly");
    }
    if (wingspan <= 0) {
        throw AnimalException(getName() + " has invalid wingspan: " + std::to_string(wingspan));
    }

    // Оригинальный код
    std::cout << getName() << " is flying with wingspan of " << wingspan << " meters." << std::endl;
    setHungerLevel(getHungerLevel() + 15);
}

void Bird::layEgg() {
    if (getAge() < 1) {
        throw AnimalException(getName() + " is too young to lay eggs (age: " +
                              std::to_string(getAge()) + ")");
    }
    if (!getIsHealthy()) {
        throw AnimalHealthException(getName(), "Reproductive issues - cannot lay eggs");
    }

    // Оригинальный код
    eggsLaid++;
    std::cout << getName() << " laid an egg! Total eggs: " << eggsLaid << std::endl;
    setHappinessLevel(getHappinessLevel() - 10);
}

void Bird::buildNest() {
    if (nestingMaterial.empty()) {
        throw AnimalException(getName() + " has no nesting material");
    }

    std::cout << getName() << " is building a nest with " << nestingMaterial << "." << std::endl;
    setHappinessLevel(getHappinessLevel() + 20);
}

void Bird::preenFeathers() {
    if (featherColor.empty()) {
        throw AnimalException(getName() + " feather color not specified");
    }

    std::cout << getName() << " is preening its " << featherColor << " feathers." << std::endl;
    setHappinessLevel(getHappinessLevel() + 5);
}

double Bird::getWingspan() const { return wingspan; }
bool Bird::getCanFly() const { return canFly; }
std::string Bird::getFeatherColor() const { return featherColor; }
int Bird::getEggsLaid() const { return eggsLaid; }
int Bird::getIncubationPeriod() const { return incubationPeriod; }
bool Bird::getMigrates() const { return migrates; }
std::string Bird::getBeakType() const { return beakType; }
double Bird::getFlightSpeed() const { return flightSpeed; }
std::string Bird::getNestingMaterial() const { return nestingMaterial; }

void Bird::setWingspan(double span) {
    if (span < 0 || span > 5.0) {
        throw AnimalException(getName() + " wingspan must be between 0-5.0 meters: " +
                              std::to_string(span));
    }
    wingspan = span;
}

void Bird::setCanFly(bool canFly) { this->canFly = canFly; }

void Bird::setFeatherColor(const std::string& color) {
    if (color.empty()) {
        throw AnimalException("Feather color cannot be empty");
    }
    featherColor = color;
}

void Bird::setEggsLaid(int eggs) {
    if (eggs < 0 || eggs > 1000) {
        throw AnimalException(getName() + " eggs laid must be between 0-1000: " +
                              std::to_string(eggs));
    }
    eggsLaid = eggs;
}

void Bird::setIncubationPeriod(int days) {
    if (days < 0 || days > 100) {
        throw AnimalException(getName() + " incubation period must be between 0-100 days: " +
                              std::to_string(days));
    }
    incubationPeriod = days;
}

void Bird::setMigrates(bool migrates) { this->migrates = migrates; }

void Bird::setBeakType(const std::string& type) {
    if (type.empty()) {
        throw AnimalException("Beak type cannot be empty");
    }
    beakType = type;
}

void Bird::setFlightSpeed(double speed) {
    if (speed < 0 || speed > 200) {
        throw AnimalException(getName() + " flight speed must be between 0-200 km/h: " +
                              std::to_string(speed));
    }
    flightSpeed = speed;
}

void Bird::setNestingMaterial(const std::string& material) {
    if (material.empty()) {
        throw AnimalException("Nesting material cannot be empty");
    }
    nestingMaterial = material;
}

double Bird::calculateDailyFood() const {
    double base = Animal::calculateDailyFood();
    if (canFly) base *= 1.3;
    if (eggsLaid > 0) base *= 1.2;
    return base;
}

void Bird::displayInfo() const {
    Animal::displayInfo();
    std::cout << "--- Bird Specific ---" << std::endl;
    std::cout << "Wingspan: " << wingspan << " meters" << std::endl;
    std::cout << "Can Fly: " << (canFly ? "Yes" : "No") << std::endl;
    std::cout << "Feather Color: " << featherColor << std::endl;
    std::cout << "Eggs Laid: " << eggsLaid << std::endl;
    std::cout << "Incubation Period: " << incubationPeriod << " days" << std::endl;
    std::cout << "Migrates: " << (migrates ? "Yes" : "No") << std::endl;
    std::cout << "Beak Type: " << beakType << std::endl;
    std::cout << "Flight Speed: " << flightSpeed << " km/h" << std::endl;
    std::cout << "Nesting Material: " << nestingMaterial << std::endl;
}

bool Bird::canMigrateNow() const {
    return migrates && getAge() > 1 && getIsHealthy();
}

void Bird::startIncubation() {
    if (eggsLaid <= 0) {
        throw AnimalException(getName() + " has no eggs to incubate");
    }
    if (incubationPeriod <= 0) {
        throw AnimalException(getName() + " incubation period must be positive: " +
                              std::to_string(incubationPeriod));
    }

    std::cout << getName() << " started incubating eggs for " << incubationPeriod << " days." << std::endl;
}