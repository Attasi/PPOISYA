#ifndef FARM_CORN_H
#define FARM_CORN_H

#include "Crop.h"
#include <string>

class Corn : public Crop {
private:
    int earCount;           // количество початков
    double cobSize;         // размер початка в см
    bool isSweetCorn;       // сладкая кукуруза или кормовая

public:
    Corn(double height, double yield, bool sweetCorn = true);

    // Уникальное поведение 16: сбор початков
    int harvestEars(int count);

    // Уникальное поведение 17: проверка размера початков
    bool hasLargeCobs() const;

    // Уникальное поведение 18: консервация кукурузы
    void canCorn(int amount);

    // Переопределенные методы
    void displayInfo() const override;
    void grow() override;

    // Геттеры и сеттеры
    int getEarCount() const;
    double getCobSize() const;
    bool getIsSweetCorn() const;

    void setEarCount(int count);
    void setCobSize(double size);
    void setIsSweetCorn(bool sweet);
};

#endif //FARM_CORN_H