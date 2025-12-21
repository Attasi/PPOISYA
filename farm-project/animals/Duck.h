#ifndef DUCK_H
#define DUCK_H

#include "Bird.h"
#include <string>

class Duck : public Bird {
private:
    bool canSwim;
    std::string pondPreference;
    int divingDepth;
    std::string billColor;
    bool isMigratory;
    std::string flockFormation;
    int preeningTime;
    std::string quackSound;
    bool hasWebbedFeet;

public:
    Duck(const std::string& name, int age, double weight, const std::string& breed = "Pekin");

    void makeSound() const override;
    void swim();
    void dive();
    void quack();
    void preenFeathers() override;

    // Геттеры
    bool getCanSwim() const;
    std::string getPondPreference() const;
    int getDivingDepth() const;
    std::string getBillColor() const;
    bool getIsMigratory() const;
    std::string getFlockFormation() const;
    int getPreeningTime() const;
    std::string getQuackSound() const;
    bool getHasWebbedFeet() const;

    // Сеттеры
    void setCanSwim(bool canSwim);
    void setPondPreference(const std::string& pond);
    void setDivingDepth(int depth);
    void setBillColor(const std::string& color);
    void setIsMigratory(bool migratory);
    void setFlockFormation(const std::string& formation);
    void setPreeningTime(int time);
    void setQuackSound(const std::string& sound);
    void setHasWebbedFeet(bool webbed);

    double calculateDailyFood() const override;
    void displayInfo() const override;
    void floatOnWater();
    void formFlock();
    void migrateIfNeeded();
};

#endif // DUCK_H