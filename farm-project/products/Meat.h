#ifndef MEAT_H
#define MEAT_H

#include "Product.h"
#include <string>

class Meat : public Product {
private:
    std::string animalType; // Beef, Pork, Chicken, Lamb
    std::string cut; // Tenderloin, Ribeye, Chuck, etc.
    double fatPercentage;
    std::string grade; // Prime, Choice, Select
    std::string agingMethod; // Dry-aged, Wet-aged
    int agingDays;
    bool isMarinated;
    std::string cookingRecommendation;
    bool isHalalCertified;

    // Вспомогательный метод для расчета базовой цены
    static double calculateBasePrice(const std::string& type);

public:
    Meat(double quantity, const std::string& animalType = "Beef",
         const std::string& cut = "Steak");

    void displayInfo() const override;
    void ageMeat(int additionalDays);
    void marinate();
    void trimFat();
    void vacuumPack();

    // Геттеры
    std::string getAnimalType() const;
    std::string getCut() const;
    double getFatPercentage() const;
    std::string getGrade() const;
    std::string getAgingMethod() const;
    int getAgingDays() const;
    bool getIsMarinated() const;
    std::string getCookingRecommendation() const;
    bool getIsHalalCertified() const;

    // Сеттеры
    void setAnimalType(const std::string& type);
    void setCut(const std::string& cut);
    void setFatPercentage(double percentage);
    void setGrade(const std::string& grade);
    void setAgingMethod(const std::string& method);
    void setAgingDays(int days);
    void setIsMarinated(bool marinated);
    void setCookingRecommendation(const std::string& recommendation);
    void setIsHalalCertified(bool halal);

    double calculateTenderness() const;
    void sliceIntoPortions(double portionSize);
    bool isPremiumCut() const;
    void recommendCookingMethod();
};

#endif // MEAT_H