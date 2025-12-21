#ifndef FARM_POTATO_H
#define FARM_POTATO_H

#include "Vegetable.h"
#include <string>

class Potato : public Vegetable {
private:
    int tuberCount;         // количество клубней
    double tuberSize;       // средний размер клубня в см
    std::string variety;    // сорт картофеля

public:
    Potato(double height, const std::string& potatoVariety = "Russet");

    // Уникальное поведение 19: сбор картофеля
    int harvestPotatoes(int count);

    // Уникальное поведение 20: проверка на болезни
    bool hasBlight() const;

    // Уникальное поведение 21: сортировка картофеля по размеру
    std::string sortBySize() const;

    // Переопределенные методы
    void displayInfo() const override;
    void harvestVegetable() override;

    // Геттеры и сеттеры
    int getTuberCount() const;
    double getTuberSize() const;
    std::string getVariety() const;

    void setTuberCount(int count);
    void setTuberSize(double size);
    void setVariety(const std::string& v);
};

#endif //FARM_POTATO_H