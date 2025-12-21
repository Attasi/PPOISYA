#ifndef RABBIT_H
#define RABBIT_H

#include "Mammal.h"
#include <string>

class Rabbit : public Mammal {
private:
    int earLength;
    std::string furType;
    int burrowingDepth;
    std::string hutchNumber;
    int jumpHeight;
    std::string favoriteVegetable;
    int breedingRate;
    std::string personalityType;
    bool isNervous;

public:
    Rabbit(const std::string& name, int age, double weight, const std::string& breed = "New Zealand White");

    void makeSound() const override;
    void hop();
    void digBurrow();
    void twitchNose();
    void sleep() override;

    // Геттеры
    int getEarLength() const;
    std::string getFurType() const;
    int getBurrowingDepth() const;
    std::string getHutchNumber() const;
    int getJumpHeight() const;
    std::string getFavoriteVegetable() const;
    int getBreedingRate() const;
    std::string getPersonalityType() const;
    bool getIsNervous() const;

    // Сеттеры
    void setEarLength(int length);
    void setFurType(const std::string& type);
    void setBurrowingDepth(int depth);
    void setHutchNumber(const std::string& hutch);
    void setJumpHeight(int height);
    void setFavoriteVegetable(const std::string& vegetable);
    void setBreedingRate(int rate);
    void setPersonalityType(const std::string& personality);
    void setIsNervous(bool nervous);

    double calculateDailyFood() const override;
    void displayInfo() const override;
    void breed();
    void cleanHutch();
    void calmDown();
};

#endif // RABBIT_H