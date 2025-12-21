#ifndef FARM_CROP_H
#define FARM_CROP_H

#include "Plant.h"
#include <string>

class Crop : public Plant {
protected:
    double yield;           // урожайность в кг
    bool isIrrigated;       // есть ли ирригация
    std::string season;     // сезон выращивания
    double fertilizerLevel; // уровень удобрений

public:
    Crop(const std::string& cropName, double height, double initialYield);

    // Уникальное поведение 4: применение удобрений
    void applyFertilizer(double amount);

    // Уникальное поведение 5: включение/выключение ирригации
    void toggleIrrigation(bool status);

    // Уникальное поведение 6: расчет ожидаемого урожая
    virtual double calculateExpectedYield() const;

    // Переопределенные методы
    void displayInfo() const override;
    bool isReadyForHarvest() const override;

    // Геттеры и сеттеры
    double getYield() const;
    bool getIsIrrigated() const;
    std::string getSeason() const;
    double getFertilizerLevel() const;

    void setYield(double y);
    void setSeason(const std::string& s);
    void setFertilizerLevel(double level);
};

#endif //FARM_CROP_H