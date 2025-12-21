#ifndef HAY_H
#define HAY_H

#include "Feed.h"
#include <string>

class Hay : public Feed {
private:
    std::string grassType; // Timothy, Alfalfa, Orchard, etc.
    std::string cut; // First cut, Second cut
    double leafToStemRatio; // соотношение листьев к стеблям
    std::string baleType; // Square, Round
    double baleWeight; // вес тюка в кг
    std::string harvestSeason;
    bool isSunCured;
    std::string color;
    double dustContent; // содержание пыли в %

public:
    Hay(double quantity, const std::string& grassType = "Timothy",
        const std::string& cut = "First");

    void displayInfo() const override;
    void baleHay();
    void cureHay();
    void testMoisture();
    void stackBales();

    // Геттеры
    std::string getGrassType() const;
    std::string getCut() const;
    double getLeafToStemRatio() const;
    std::string getBaleType() const;
    double getBaleWeight() const;
    std::string getHarvestSeason() const;
    bool getIsSunCured() const;
    std::string getColor() const;
    double getDustContent() const;

    // Сеттеры
    void setGrassType(const std::string& type);
    void setCut(const std::string& cut);
    void setLeafToStemRatio(double ratio);
    void setBaleType(const std::string& type);
    void setBaleWeight(double weight);
    void setHarvestSeason(const std::string& season);
    void setIsSunCured(bool cured);
    void setColor(const std::string& color);
    void setDustContent(double dust);

    double calculateEnergyValue() const;
    bool isSuitableForAnimal(const std::string& animalType) const override;
    void compressBales();
    void gradeHay();
};

#endif // HAY_H