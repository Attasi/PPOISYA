#ifndef ANIMAL_EXCEPTIONS_H
#define ANIMAL_EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Базовое исключение для животных
class AnimalException : public std::runtime_error {
public:
    explicit AnimalException(const std::string& message)
            : std::runtime_error("Animal Error: " + message) {}
};

// Исключение для проблем со здоровьем животных
class AnimalHealthException : public AnimalException {
private:
    std::string animalName;
    std::string disease;
public:
    AnimalHealthException(const std::string& animalName, const std::string& disease)
            : AnimalException(animalName + " has health issue: " + disease),
              animalName(animalName), disease(disease) {}

    std::string getAnimalName() const { return animalName; }
    std::string getDisease() const { return disease; }
};

// Исключение для проблем с кормлением
class AnimalFeedingException : public AnimalException {
private:
    std::string animalName;
    double requiredFood;
    double providedFood;
public:
    AnimalFeedingException(const std::string& animalName, double required, double provided)
            : AnimalException(animalName + " feeding error: required " +
                              std::to_string(required) + ", provided " +
                              std::to_string(provided)),
              animalName(animalName), requiredFood(required), providedFood(provided) {}

    std::string getAnimalName() const { return animalName; }
    double getRequiredFood() const { return requiredFood; }
    double getProvidedFood() const { return providedFood; }
};

// Исключение для проблем с размножением
class AnimalBreedingException : public AnimalException {
private:
    std::string animalName;
    int age;
    int requiredAge;
public:
    AnimalBreedingException(const std::string& animalName, int age, int requiredAge)
            : AnimalException(animalName + " breeding error: age " +
                              std::to_string(age) + " < required " +
                              std::to_string(requiredAge)),
              animalName(animalName), age(age), requiredAge(requiredAge) {}

    std::string getAnimalName() const { return animalName; }
    int getAge() const { return age; }
    int getRequiredAge() const { return requiredAge; }
};

#endif // ANIMAL_EXCEPTIONS_H