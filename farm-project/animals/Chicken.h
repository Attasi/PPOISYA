#ifndef CHICKEN_H
#define CHICKEN_H

#include "Bird.h"
#include <string>

class Chicken : public Bird {
private:
    int eggsPerWeek;
    std::string combType;
    bool isBroody;
    std::string roostingPerch;
    int featherLoss;
    std::string chickenRun;
    bool freeRange;
    std::string favoriteFeed;
    int dustBathingFrequency;

public:
    Chicken(const std::string& name, int age, double weight, const std::string& breed = "Rhode Island Red");

    void makeSound() const override;
    void layEgg() override;
    void peckFood();
    void dustBathe();
    void roost();

    // Геттеры
    int getEggsPerWeek() const;
    std::string getCombType() const;
    bool getIsBroody() const;
    std::string getRoostingPerch() const;
    int getFeatherLoss() const;
    std::string getChickenRun() const;
    bool getFreeRange() const;
    std::string getFavoriteFeed() const;
    int getDustBathingFrequency() const;

    // Сеттеры
    void setEggsPerWeek(int eggs);
    void setCombType(const std::string& type);
    void setIsBroody(bool broody);
    void setRoostingPerch(const std::string& perch);
    void setFeatherLoss(int loss);
    void setChickenRun(const std::string& run);
    void setFreeRange(bool freeRange);
    void setFavoriteFeed(const std::string& feed);
    void setDustBathingFrequency(int frequency);

    double calculateDailyFood() const override;
    void displayInfo() const override;
    bool isLayingWell() const;
    void collectEggs();
    void breakBroodiness();
};

#endif // CHICKEN_H