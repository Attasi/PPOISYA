#ifndef BIRD_H
#define BIRD_H

#include "Animal.h"
#include <string>

class Bird : public Animal {
protected:
    double wingspan;
    bool canFly;
    std::string featherColor;
    int eggsLaid;
    int incubationPeriod; // дней
    bool migrates;
    std::string beakType;
    double flightSpeed;
    std::string nestingMaterial;

public:
    Bird(const std::string& name, int age, double weight, const std::string& breed,
         double wingspan = 1.0, bool canFly = true);

    void makeSound() const override;
    void fly();
    void layEgg();
    void buildNest();
    void preenFeathers();

    // Геттеры
    double getWingspan() const;
    bool getCanFly() const;
    std::string getFeatherColor() const;
    int getEggsLaid() const;
    int getIncubationPeriod() const;
    bool getMigrates() const;
    std::string getBeakType() const;
    double getFlightSpeed() const;
    std::string getNestingMaterial() const;

    // Сеттеры
    void setWingspan(double span);
    void setCanFly(bool canFly);
    void setFeatherColor(const std::string& color);
    void setEggsLaid(int eggs);
    void setIncubationPeriod(int days);
    void setMigrates(bool migrates);
    void setBeakType(const std::string& type);
    void setFlightSpeed(double speed);
    void setNestingMaterial(const std::string& material);

    double calculateDailyFood() const override;
    void displayInfo() const override;
    bool canMigrateNow() const;
    void startIncubation();
};

#endif // BIRD_H