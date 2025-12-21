#ifndef GOAT_H
#define GOAT_H

#include "Mammal.h"
#include <string>

class Goat : public Mammal {
private:
    double milkFatContent;
    std::string hornShape;
    int climbingAbility;
    std::string grazingTerrain;
    double cheeseProduction;
    std::string beardType;
    int agilityScore;
    std::string favoriteClimbingSpot;
    bool isStubborn;

public:
    Goat(const std::string& name, int age, double weight, const std::string& breed = "Alpine");

    void makeSound() const override;
    void climb();
    void produceMilk() override;
    void headButt();
    void browse();

    // Геттеры
    double getMilkFatContent() const;
    std::string getHornShape() const;
    int getClimbingAbility() const;
    std::string getGrazingTerrain() const;
    double getCheeseProduction() const;
    std::string getBeardType() const;
    int getAgilityScore() const;
    std::string getFavoriteClimbingSpot() const;
    bool getIsStubborn() const;

    // Сеттеры
    void setMilkFatContent(double fat);
    void setHornShape(const std::string& shape);
    void setClimbingAbility(int ability);
    void setGrazingTerrain(const std::string& terrain);
    void setCheeseProduction(double production);
    void setBeardType(const std::string& type);
    void setAgilityScore(int score);
    void setFavoriteClimbingSpot(const std::string& spot);
    void setIsStubborn(bool stubborn);

    double calculateDailyFood() const override;
    void displayInfo() const override;
    void makeCheese();
    double calculateMilkValue() const;
    void challengeToClimb();
};

#endif // GOAT_H