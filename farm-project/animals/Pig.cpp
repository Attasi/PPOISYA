#include "Pig.h"
#include "AnimalExceptions.h"
#include <iostream>

Pig::Pig(const std::string& name, int age, double weight, const std::string& breed)
        : Mammal(name, age, weight, breed, false, 44) {
    // Проверки для свиней
    if (weight < 10 || weight > 400) {
        throw AnimalException("Pig weight must be between 10-400 kg: " + std::to_string(weight));
    }

    setPrice(450.0);
    setFurColor("Pink");
    setCanSwim(true);
    setHabitatType("Pen");

    fatPercentage = 15.0;
    snoutType = "Round";
    wallowFrequency = 2;
    penNumber = "Pen-3";
    feedConversionRate = 3.5;
    tailType = "Curly";
    mudBathEnjoyment = 90;
    feedingSchedule = "8am, 1pm, 6pm";
    isForaging = false;
}

void Pig::makeSound() const {
    std::cout << getName() << " says: Oink oink!" << std::endl;
}

void Pig::wallowInMud() {
    if (mudBathEnjoyment <= 0) {
        throw AnimalException(getName() + " does not enjoy mud baths (enjoyment: " +
                              std::to_string(mudBathEnjoyment) + "%)");
    }
    if (!getCanSwim()) {
        throw AnimalException(getName() + " cannot swim, may drown in mud");
    }

    // Оригинальный код
    std::cout << getName() << " is wallowing in mud. Enjoyment level: " << mudBathEnjoyment << "%" << std::endl;
    setHappinessLevel(getHappinessLevel() + 30);
    setIsHealthy(true); // Mud helps with parasites
}

void Pig::forage() {
    if (penNumber.empty()) {
        throw AnimalException(getName() + " has no pen number assigned");
    }

    isForaging = true;
    std::cout << getName() << " is foraging for food." << std::endl;
    setHungerLevel(getHungerLevel() - 25);
    setWeight(getWeight() + 0.3);
}

void Pig::root() {
    if (snoutType.empty()) {
        throw AnimalException(getName() + " snout type not specified");
    }

    std::cout << getName() << " is rooting with its " << snoutType << " snout." << std::endl;
    setHappinessLevel(getHappinessLevel() + 15);
}

void Pig::sleep() {
    if (getAge() < 0.5) {
        throw AnimalException(getName() + " is too young to sleep deeply (age: " +
                              std::to_string(getAge()) + ")");
    }

    std::cout << getName() << " is sleeping soundly (pigs sleep deeply)." << std::endl;
    Animal::sleep(8); // Pigs sleep about 8 hours
    setWeight(getWeight() + 0.1); // Pigs gain weight while sleeping
}

double Pig::getFatPercentage() const { return fatPercentage; }
std::string Pig::getSnoutType() const { return snoutType; }
int Pig::getWallowFrequency() const { return wallowFrequency; }
std::string Pig::getPenNumber() const { return penNumber; }
double Pig::getFeedConversionRate() const { return feedConversionRate; }
std::string Pig::getTailType() const { return tailType; }
int Pig::getMudBathEnjoyment() const { return mudBathEnjoyment; }
std::string Pig::getFeedingSchedule() const { return feedingSchedule; }
bool Pig::getIsForaging() const { return isForaging; }

void Pig::setFatPercentage(double percentage) {
    if (percentage < 5 || percentage > 50) {
        throw AnimalException(getName() + " fat percentage must be between 5-50%: " +
                              std::to_string(percentage));
    }
    fatPercentage = percentage;
}

void Pig::setSnoutType(const std::string& type) {
    if (type.empty()) {
        throw AnimalException("Snout type cannot be empty");
    }
    snoutType = type;
}

void Pig::setWallowFrequency(int frequency) {
    if (frequency < 0 || frequency > 10) {
        throw AnimalException(getName() + " wallow frequency must be between 0-10 times/week: " +
                              std::to_string(frequency));
    }
    wallowFrequency = frequency;
}

void Pig::setPenNumber(const std::string& pen) {
    if (pen.empty()) {
        throw AnimalException("Pen number cannot be empty");
    }
    penNumber = pen;
}

void Pig::setFeedConversionRate(double rate) {
    if (rate < 2.0 || rate > 5.0) {
        throw AnimalException(getName() + " feed conversion rate must be between 2.0-5.0: " +
                              std::to_string(rate));
    }
    feedConversionRate = rate;
}

void Pig::setTailType(const std::string& type) {
    if (type.empty()) {
        throw AnimalException("Tail type cannot be empty");
    }
    tailType = type;
}

void Pig::setMudBathEnjoyment(int enjoyment) {
    if (enjoyment < 0 || enjoyment > 100) {
        throw AnimalException(getName() + " mud bath enjoyment must be between 0-100%: " +
                              std::to_string(enjoyment));
    }
    mudBathEnjoyment = enjoyment;
}

void Pig::setFeedingSchedule(const std::string& schedule) {
    if (schedule.empty()) {
        throw AnimalException("Feeding schedule cannot be empty");
    }
    feedingSchedule = schedule;
}

void Pig::setIsForaging(bool foraging) { isForaging = foraging; }

double Pig::calculateDailyFood() const {
    double base = Mammal::calculateDailyFood();
    base *= feedConversionRate;
    if (getIsPregnant()) base *= 1.4;
    return base;
}

void Pig::displayInfo() const {
    Mammal::displayInfo();
    std::cout << "--- Pig Specific ---" << std::endl;
    std::cout << "Fat Percentage: " << fatPercentage << "%" << std::endl;
    std::cout << "Snout Type: " << snoutType << std::endl;
    std::cout << "Wallow Frequency: " << wallowFrequency << " times/week" << std::endl;
    std::cout << "Pen Number: " << penNumber << std::endl;
    std::cout << "Feed Conversion Rate: " << feedConversionRate << " kg feed/kg weight" << std::endl;
    std::cout << "Tail Type: " << tailType << std::endl;
    std::cout << "Mud Bath Enjoyment: " << mudBathEnjoyment << "%" << std::endl;
    std::cout << "Feeding Schedule: " << feedingSchedule << std::endl;
    std::cout << "Currently Foraging: " << (isForaging ? "Yes" : "No") << std::endl;
}

void Pig::calculateWeightGain() {
    if (feedConversionRate <= 0) {
        throw AnimalException(getName() + " feed conversion rate must be positive: " +
                              std::to_string(feedConversionRate));
    }

    double dailyGain = calculateDailyFood() / feedConversionRate;
    std::cout << getName() << " gains approximately " << dailyGain << " kg per day." << std::endl;
}

void Pig::cleanPen() {
    if (penNumber.empty()) {
        throw AnimalException(getName() + " has no pen number to clean");
    }

    std::cout << "Cleaning pen " << penNumber << " for " << getName() << std::endl;
    setHappinessLevel(getHappinessLevel() + 20);
    setIsHealthy(true);
}

void Pig::scheduleFeeding() {
    if (feedingSchedule.empty()) {
        throw AnimalException(getName() + " has no feeding schedule");
    }

    std::cout << getName() << "'s feeding schedule: " << feedingSchedule << std::endl;
}