#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>

class Animal {
protected:
    std::string name;
    int age;
    double weight;
    bool isHealthy;
    std::string breed;
    int hungerLevel; // 0-100
    int happinessLevel; // 0-100
    std::string id;
    double price;
    std::string lastVetCheck;

public:
    Animal(const std::string& name, int age, double weight, const std::string& breed);
    virtual ~Animal() = default;

    virtual void makeSound() const = 0;
    virtual void eat(double amount);
    virtual void sleep(int hours);
    virtual void move();
    virtual void displayInfo() const;

    // Геттеры
    std::string getName() const;
    int getAge() const;
    double getWeight() const;
    bool getIsHealthy() const;
    std::string getBreed() const;
    int getHungerLevel() const;
    int getHappinessLevel() const;
    std::string getId() const;
    double getPrice() const;
    std::string getLastVetCheck() const;

    // Сеттеры
    void setName(const std::string& name);
    void setAge(int age);
    void setWeight(double weight);
    void setIsHealthy(bool healthy);
    void setBreed(const std::string& breed);
    void setHungerLevel(int level);
    void setHappinessLevel(int level);
    void setId(const std::string& id);
    void setPrice(double price);
    void setLastVetCheck(const std::string& date);

    virtual double calculateDailyFood() const;
    virtual bool needsVetCheck() const;
    virtual void getVaccinated();
};

#endif // ANIMAL_H