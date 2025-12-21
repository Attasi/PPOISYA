#ifndef MAMMAL_H
#define MAMMAL_H

#include "Animal.h"
#include <string>

class Mammal : public Animal {
protected:
    bool hasFur;
    int numberOfTeeth;
    double bodyTemperature;
    bool isPregnant;
    int pregnancyMonths;
    std::string furColor;
    int lactationPeriod; // дней
    bool canSwim;
    std::string habitatType;

public:
    Mammal(const std::string& name, int age, double weight, const std::string& breed,
           bool hasFur = true, int numberOfTeeth = 32);

    void makeSound() const override;
    void giveBirth();
    void produceMilk();
    void regulateTemperature();
    void groomFur();

    // Геттеры
    bool getHasFur() const;
    int getNumberOfTeeth() const;
    double getBodyTemperature() const;
    bool getIsPregnant() const;
    int getPregnancyMonths() const;
    std::string getFurColor() const;
    int getLactationPeriod() const;
    bool getCanSwim() const;
    std::string getHabitatType() const;

    // Сеттеры
    void setHasFur(bool hasFur);
    void setNumberOfTeeth(int number);
    void setBodyTemperature(double temp);
    void setIsPregnant(bool pregnant);
    void setPregnancyMonths(int months);
    void setFurColor(const std::string& color);
    void setLactationPeriod(int days);
    void setCanSwim(bool canSwim);
    void setHabitatType(const std::string& habitat);

    double calculateDailyFood() const override;
    void displayInfo() const override;
    void checkPregnancyProgress() const;
    void weanOffspring();
};

#endif // MAMMAL_H