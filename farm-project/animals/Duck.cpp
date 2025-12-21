#include "Duck.h"
#include "AnimalExceptions.h"
#include <iostream>

Duck::Duck(const std::string& name, int age, double weight, const std::string& breed)
        : Bird(name, age, weight, breed, 0.8, true) {
    // Проверки для уток
    if (weight < 0.5 || weight > 5.0) {
        throw AnimalException("Duck weight must be between 0.5-5.0 kg: " + std::to_string(weight));
    }

    setPrice(35.0);
    setFeatherColor("White");
    setMigrates(true);

    canSwim = true;
    pondPreference = "Large Pond";
    divingDepth = 1;
    billColor = "Yellow";
    isMigratory = true;
    flockFormation = "V-shape";
    preeningTime = 30;
    quackSound = "Quack-quack";
    hasWebbedFeet = true;
}

void Duck::makeSound() const {
    if (quackSound.empty()) {
        throw AnimalException(getName() + " has no quack sound specified");
    }

    std::cout << getName() << " says: " << quackSound << "!" << std::endl;
}

void Duck::swim() {
    if (!canSwim) {
        throw AnimalException(getName() + " cannot swim");
    }
    if (!hasWebbedFeet) {
        throw AnimalException(getName() + " has no webbed feet for swimming");
    }
    if (pondPreference.empty()) {
        throw AnimalException(getName() + " has no pond preference for swimming");
    }

    // Оригинальный код
    std::cout << getName() << " is swimming in " << pondPreference << "." << std::endl;
    setHappinessLevel(getHappinessLevel() + 25);
}

void Duck::dive() {
    if (!canSwim) {
        throw AnimalException(getName() + " cannot swim, therefore cannot dive");
    }
    if (divingDepth <= 0) {
        throw AnimalException(getName() + " diving depth must be positive: " +
                              std::to_string(divingDepth));
    }

    // Оригинальный код
    std::cout << getName() << " is diving to " << divingDepth << " meters depth." << std::endl;
    setHungerLevel(getHungerLevel() - 15);
}

void Duck::quack() {
    if (quackSound.empty()) {
        throw AnimalException(getName() + " has no quack sound to make");
    }

    std::cout << getName() << " quacks: " << quackSound << "!" << std::endl;
}

void Duck::preenFeathers() {
    if (preeningTime <= 0) {
        throw AnimalException(getName() + " preening time must be positive: " +
                              std::to_string(preeningTime));
    }
    if (getFeatherColor().empty()) {
        throw AnimalException(getName() + " feather color not specified");
    }

    // Оригинальный код
    std::cout << getName() << " is preening feathers for " << preeningTime << " minutes." << std::endl;
    Bird::preenFeathers();
    setHappinessLevel(getHappinessLevel() + 10); // Extra happiness for ducks
}

bool Duck::getCanSwim() const { return canSwim; }
std::string Duck::getPondPreference() const { return pondPreference; }
int Duck::getDivingDepth() const { return divingDepth; }
std::string Duck::getBillColor() const { return billColor; }
bool Duck::getIsMigratory() const { return isMigratory; }
std::string Duck::getFlockFormation() const { return flockFormation; }
int Duck::getPreeningTime() const { return preeningTime; }
std::string Duck::getQuackSound() const { return quackSound; }
bool Duck::getHasWebbedFeet() const { return hasWebbedFeet; }

void Duck::setCanSwim(bool canSwim) { this->canSwim = canSwim; }

void Duck::setPondPreference(const std::string& pond) {
    if (pond.empty()) {
        throw AnimalException("Pond preference cannot be empty");
    }
    pondPreference = pond;
}

void Duck::setDivingDepth(int depth) {
    if (depth < 0 || depth > 10) {
        throw AnimalException(getName() + " diving depth must be between 0-10 meters: " +
                              std::to_string(depth));
    }
    divingDepth = depth;
}

void Duck::setBillColor(const std::string& color) {
    if (color.empty()) {
        throw AnimalException("Bill color cannot be empty");
    }
    billColor = color;
}

void Duck::setIsMigratory(bool migratory) { isMigratory = migratory; }

void Duck::setFlockFormation(const std::string& formation) {
    if (formation.empty()) {
        throw AnimalException("Flock formation cannot be empty");
    }
    flockFormation = formation;
}

void Duck::setPreeningTime(int time) {
    if (time < 0 || time > 120) {
        throw AnimalException(getName() + " preening time must be between 0-120 minutes: " +
                              std::to_string(time));
    }
    preeningTime = time;
}

void Duck::setQuackSound(const std::string& sound) {
    if (sound.empty()) {
        throw AnimalException("Quack sound cannot be empty");
    }
    quackSound = sound;
}

void Duck::setHasWebbedFeet(bool webbed) { hasWebbedFeet = webbed; }

double Duck::calculateDailyFood() const {
    double base = Bird::calculateDailyFood();
    if (canSwim) base *= 1.2;
    if (isMigratory) base *= 1.3;
    return base;
}

void Duck::displayInfo() const {
    Bird::displayInfo();
    std::cout << "--- Duck Specific ---" << std::endl;
    std::cout << "Can Swim: " << (canSwim ? "Yes" : "No") << std::endl;
    std::cout << "Pond Preference: " << pondPreference << std::endl;
    std::cout << "Diving Depth: " << divingDepth << " meters" << std::endl;
    std::cout << "Bill Color: " << billColor << std::endl;
    std::cout << "Migratory: " << (isMigratory ? "Yes" : "No") << std::endl;
    std::cout << "Flock Formation: " << flockFormation << std::endl;
    std::cout << "Preening Time: " << preeningTime << " minutes/day" << std::endl;
    std::cout << "Quack Sound: " << quackSound << std::endl;
    std::cout << "Webbed Feet: " << (hasWebbedFeet ? "Yes" : "No") << std::endl;
}

void Duck::floatOnWater() {
    if (!canSwim) {
        throw AnimalException(getName() + " cannot swim, therefore cannot float");
    }

    std::cout << getName() << " is floating peacefully on water." << std::endl;
    setHappinessLevel(getHappinessLevel() + 15);
}

void Duck::formFlock() {
    if (flockFormation.empty()) {
        throw AnimalException(getName() + " has no flock formation specified");
    }

    std::cout << getName() << " is forming a " << flockFormation << " formation with other ducks." << std::endl;
}

void Duck::migrateIfNeeded() {
    if (isMigratory && canMigrateNow()) {
        if (getAge() < 1) {
            throw AnimalException(getName() + " is too young to migrate (age: " +
                                  std::to_string(getAge()) + ")");
        }
        if (!getIsHealthy()) {
            throw AnimalHealthException(getName(), "Injured wing - cannot migrate");
        }

        std::cout << getName() << " is ready to migrate." << std::endl;
    } else {
        std::cout << getName() << " is not migrating now." << std::endl;
    }
}