#include "Animal.h"
#include "AnimalExceptions.h"
#include <iostream>

Animal::Animal(const std::string& name, int age, double weight, const std::string& breed) {
    // Проверка входных параметров
    if (name.empty()) {
        throw AnimalException("Animal name cannot be empty");
    }
    if (age < 0 || age > 50) {
        throw AnimalException("Animal age must be between 0-50: " + std::to_string(age));
    }
    if (weight <= 0 || weight > 5000) {
        throw AnimalException("Animal weight must be between 0-5000 kg: " + std::to_string(weight));
    }
    if (breed.empty()) {
        throw AnimalException("Animal breed cannot be empty");
    }

    this->name = name;
    this->age = age;
    this->weight = weight;
    this->breed = breed;
    this->isHealthy = true;
    this->hungerLevel = 50;
    this->happinessLevel = 50;
    this->price = 0.0;
    this->lastVetCheck = "Never";

    static int counter = 1;
    this->id = "ANIMAL_" + std::to_string(counter++);
}

void Animal::eat(double amount) {
    if (amount <= 0) {
        throw AnimalException(getName() + " cannot eat non-positive amount of food: " + std::to_string(amount));
    }
    if (amount > calculateDailyFood() * 3) {
        throw AnimalFeedingException(getName(), calculateDailyFood(), amount);
    }
    if (!isHealthy) {
        throw AnimalHealthException(getName(), "Unknown disease - animal is too sick to eat");
    }

    // Оригинальный код
    hungerLevel -= static_cast<int>(amount * 10);
    if (hungerLevel < 0) hungerLevel = 0;
    happinessLevel += 5;
    if (happinessLevel > 100) happinessLevel = 100;
    weight += amount * 0.1;
    std::cout << name << " ate " << amount << " kg of food." << std::endl;
}

void Animal::sleep(int hours) {
    if (hours <= 0) {
        throw AnimalException(getName() + " cannot sleep non-positive hours: " + std::to_string(hours));
    }
    if (hours > 24) {
        throw AnimalException(getName() + " cannot sleep more than 24 hours: " + std::to_string(hours));
    }

    // Оригинальный код
    if (hours > 0) {
        happinessLevel += hours * 2;
        if (happinessLevel > 100) happinessLevel = 100;
        std::cout << name << " slept for " << hours << " hours." << std::endl;
    }
}

void Animal::move() {
    if (!isHealthy) {
        throw AnimalHealthException(getName(), "Injury - cannot move");
    }

    // Оригинальный код
    hungerLevel += 5;
    if (hungerLevel > 100) hungerLevel = 100;
    weight -= 0.01;
    if (weight < 0.5) weight = 0.5;
    std::cout << name << " is moving around." << std::endl;
}

void Animal::displayInfo() const {
    std::cout << "=== Animal Info ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << " years" << std::endl;
    std::cout << "Weight: " << weight << " kg" << std::endl;
    std::cout << "Breed: " << breed << std::endl;
    std::cout << "Health: " << (isHealthy ? "Healthy" : "Sick") << std::endl;
    std::cout << "Hunger: " << hungerLevel << "/100" << std::endl;
    std::cout << "Happiness: " << happinessLevel << "/100" << std::endl;
    std::cout << "Price: $" << price << std::endl;
    std::cout << "Last Vet Check: " << lastVetCheck << std::endl;
}

std::string Animal::getName() const { return name; }
int Animal::getAge() const { return age; }
double Animal::getWeight() const { return weight; }
bool Animal::getIsHealthy() const { return isHealthy; }
std::string Animal::getBreed() const { return breed; }
int Animal::getHungerLevel() const { return hungerLevel; }
int Animal::getHappinessLevel() const { return happinessLevel; }
std::string Animal::getId() const { return id; }
double Animal::getPrice() const { return price; }
std::string Animal::getLastVetCheck() const { return lastVetCheck; }

void Animal::setName(const std::string& name) {
    if (name.empty()) {
        throw AnimalException("Animal name cannot be empty");
    }
    this->name = name;
}

void Animal::setAge(int age) {
    if (age < 0 || age > 50) {
        throw AnimalException("Animal age must be between 0-50: " + std::to_string(age));
    }
    this->age = age;
}

void Animal::setWeight(double weight) {
    if (weight <= 0 || weight > 5000) {
        throw AnimalException("Animal weight must be between 0-5000 kg: " + std::to_string(weight));
    }
    this->weight = weight;
}

void Animal::setIsHealthy(bool healthy) { isHealthy = healthy; }

void Animal::setBreed(const std::string& breed) {
    if (breed.empty()) {
        throw AnimalException("Animal breed cannot be empty");
    }
    this->breed = breed;
}

void Animal::setHungerLevel(int level) {
    if (level < 0 || level > 100) {
        throw AnimalException(getName() + " hunger level must be between 0-100: " + std::to_string(level));
    }
    hungerLevel = level;
}

void Animal::setHappinessLevel(int level) {
    if (level < 0 || level > 100) {
        throw AnimalException(getName() + " happiness level must be between 0-100: " + std::to_string(level));
    }
    happinessLevel = level;
}

void Animal::setId(const std::string& id) {
    if (id.empty()) {
        throw AnimalException("Animal ID cannot be empty");
    }
    this->id = id;
}

void Animal::setPrice(double price) {
    if (price < 0) {
        throw AnimalException(getName() + " price cannot be negative: " + std::to_string(price));
    }
    this->price = price;
}

void Animal::setLastVetCheck(const std::string& date) {
    if (date.empty()) {
        throw AnimalException("Vet check date cannot be empty");
    }
    lastVetCheck = date;
}

double Animal::calculateDailyFood() const {
    return weight * 0.02; // 2% от веса
}

bool Animal::needsVetCheck() const {
    return !isHealthy || age > 5 || lastVetCheck == "Never";
}

void Animal::getVaccinated() {
    if (age < 0.5) {
        throw AnimalException(getName() + " is too young for vaccination (age: " + std::to_string(age) + ")");
    }

    isHealthy = true;
    lastVetCheck = "Today";
    std::cout << name << " has been vaccinated." << std::endl;
}