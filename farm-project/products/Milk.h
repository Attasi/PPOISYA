#ifndef MILK_H
#define MILK_H

#include "Product.h"
#include <string>

class Milk : public Product {
private:
    double fatContent; // содержание жира в %
    std::string sourceAnimal; // Cow, Goat
    bool isPasteurized;
    std::string packagingType; // Bottle, Carton, Bag
    int lactoseContent; // содержание лактозы
    std::string homogenizationLevel;
    bool isFortified;
    std::string milkType; // Whole, Skim, 2%
    int bacterialCount;

    // Вспомогательный метод для расчета базовой цены
    static double calculateBasePrice(const std::string& source, double fat);

public:
    Milk(double quantity, double fatContent = 3.2,
         const std::string& sourceAnimal = "Cow");

    void displayInfo() const override;
    void pasteurize();
    void homogenize();
    void fortify();
    void checkFreshness() const;

    // Геттеры
    double getFatContent() const;
    std::string getSourceAnimal() const;
    bool getIsPasteurized() const;
    std::string getPackagingType() const;
    int getLactoseContent() const;
    std::string getHomogenizationLevel() const;
    bool getIsFortified() const;
    std::string getMilkType() const;
    int getBacterialCount() const;

    // Сеттеры
    void setFatContent(double fat);
    void setSourceAnimal(const std::string& animal);
    void setIsPasteurized(bool pasteurized);
    void setPackagingType(const std::string& packaging);
    void setLactoseContent(int lactose);
    void setHomogenizationLevel(const std::string& level);
    void setIsFortified(bool fortified);
    void setMilkType(const std::string& type);
    void setBacterialCount(int count);

    double calculateNutritionalValue() const;
    void makeCheese(double amount);
    bool isSafeForConsumption() const;
    void adjustFatContent(double targetFat);
};

#endif // MILK_H