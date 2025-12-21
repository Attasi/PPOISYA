#include "Mammal.h"
#include "AnimalExceptions.h"
#include <iostream>

Mammal::Mammal(const std::string& name, int age, double weight, const std::string& breed,
               bool hasFur, int numberOfTeeth)
        : Animal(name, age, weight, breed) {
    // Дополнительные проверки для млекопитающих
    if (numberOfTeeth < 0 || numberOfTeeth > 100) {
        throw AnimalException(getName() + " tooth count must be between 0-100: " + std::to_string(numberOfTeeth));
    }

    this->hasFur = hasFur;
    this->numberOfTeeth = numberOfTeeth;
    this->bodyTemperature = 37.0;
    this->isPregnant = false;
    this->pregnancyMonths = 0;
    this->furColor = "Brown";
    this->lactationPeriod = 180;
    this->canSwim = false;
    this->habitatType = "Land";
}

void Mammal::makeSound() const {
    std::cout << getName() << " makes a mammalian sound." << std::endl;
}

void Mammal::giveBirth() {
    if (!isPregnant) {
        throw AnimalException(getName() + " is not pregnant");
    }
    if (pregnancyMonths < 9) {
        throw AnimalException(getName() + " is not ready to give birth yet (only " +
                              std::to_string(pregnancyMonths) + " months pregnant)");
    }
    if (age < 2) {
        throw AnimalBreedingException(getName(), age, 2);
    }

    // Оригинальный код
    std::cout << getName() << " gave birth!" << std::endl;
    isPregnant = false;
    pregnancyMonths = 0;
}

void Mammal::produceMilk() {
    if (!isPregnant && pregnancyMonths <= 0) {
        throw AnimalException(getName() + " cannot produce milk (not pregnant or recently pregnant)");
    }
    if (age < 1) {
        throw AnimalException(getName() + " is too young to produce milk (age: " + std::to_string(age) + ")");
    }

    // Оригинальный код
    if (isPregnant || pregnancyMonths > 0) {
        std::cout << getName() << " is producing milk." << std::endl;
    } else {
        std::cout << getName() << " is not producing milk." << std::endl;
    }
}

void Mammal::regulateTemperature() {
    if (bodyTemperature > 42.0 || bodyTemperature < 35.0) {
        throw AnimalHealthException(getName(), "Critical body temperature: " + std::to_string(bodyTemperature));
    }

    std::cout << getName() << " is regulating body temperature." << std::endl;
    bodyTemperature = 37.0;
}

void Mammal::groomFur() {
    if (!hasFur) {
        throw AnimalException(getName() + " has no fur to groom");
    }

    // Оригинальный код
    if (hasFur) {
        setHappinessLevel(getHappinessLevel() + 10);
        std::cout << getName() << "'s fur has been groomed." << std::endl;
    }
}

bool Mammal::getHasFur() const { return hasFur; }
int Mammal::getNumberOfTeeth() const { return numberOfTeeth; }
double Mammal::getBodyTemperature() const { return bodyTemperature; }
bool Mammal::getIsPregnant() const { return isPregnant; }
int Mammal::getPregnancyMonths() const { return pregnancyMonths; }
std::string Mammal::getFurColor() const { return furColor; }
int Mammal::getLactationPeriod() const { return lactationPeriod; }
bool Mammal::getCanSwim() const { return canSwim; }
std::string Mammal::getHabitatType() const { return habitatType; }

void Mammal::setHasFur(bool hasFur) { this->hasFur = hasFur; }

void Mammal::setNumberOfTeeth(int number) {
    if (number < 0 || number > 100) {
        throw AnimalException(getName() + " tooth count must be between 0-100: " + std::to_string(number));
    }
    numberOfTeeth = number;
}

void Mammal::setBodyTemperature(double temp) {
    if (temp < 35.0 || temp > 42.0) {
        throw AnimalHealthException(getName(), "Body temperature out of range: " + std::to_string(temp));
    }
    bodyTemperature = temp;
}

void Mammal::setIsPregnant(bool pregnant) { isPregnant = pregnant; }

void Mammal::setPregnancyMonths(int months) {
    if (months < 0 || months > 12) {
        throw AnimalException(getName() + " pregnancy months must be between 0-12: " + std::to_string(months));
    }
    pregnancyMonths = months;
}

void Mammal::setFurColor(const std::string& color) {
    if (color.empty()) {
        throw AnimalException("Fur color cannot be empty");
    }
    furColor = color;
}

void Mammal::setLactationPeriod(int days) {
    if (days < 0 || days > 365) {
        throw AnimalException(getName() + " lactation period must be between 0-365 days: " + std::to_string(days));
    }
    lactationPeriod = days;
}

void Mammal::setCanSwim(bool canSwim) { this->canSwim = canSwim; }

void Mammal::setHabitatType(const std::string& habitat) {
    if (habitat.empty()) {
        throw AnimalException("Habitat type cannot be empty");
    }
    habitatType = habitat;
}

double Mammal::calculateDailyFood() const {
    double base = Animal::calculateDailyFood();
    if (isPregnant) base *= 1.5;
    if (bodyTemperature > 38.0) base *= 1.2;
    return base;
}

void Mammal::displayInfo() const {
    Animal::displayInfo();
    std::cout << "--- Mammal Specific ---" << std::endl;
    std::cout << "Has Fur: " << (hasFur ? "Yes" : "No") << std::endl;
    std::cout << "Number of Teeth: " << numberOfTeeth << std::endl;
    std::cout << "Body Temperature: " << bodyTemperature << "°C" << std::endl;
    std::cout << "Pregnant: " << (isPregnant ? "Yes" : "No") << std::endl;
    if (isPregnant) {
        std::cout << "Pregnancy Months: " << pregnancyMonths << std::endl;
    }
    std::cout << "Fur Color: " << furColor << std::endl;
    std::cout << "Lactation Period: " << lactationPeriod << " days" << std::endl;
    std::cout << "Can Swim: " << (canSwim ? "Yes" : "No") << std::endl;
    std::cout << "Habitat Type: " << habitatType << std::endl;
}

void Mammal::checkPregnancyProgress() const {
    if (!isPregnant) {
        throw AnimalException(getName() + " is not pregnant");
    }

    // Оригинальный код
    std::cout << getName() << " is " << pregnancyMonths << " months pregnant." << std::endl;
    int remaining = 9 - pregnancyMonths;
    if (remaining > 0) {
        std::cout << remaining << " months until birth." << std::endl;
    } else {
        std::cout << "Ready to give birth!" << std::endl;
    }
}

void Mammal::weanOffspring() {
    if (lactationPeriod <= 0) {
        throw AnimalException(getName() + " is not currently lactating");
    }

    std::cout << getName() << " is weaning offspring." << std::endl;
    lactationPeriod = 0;
}