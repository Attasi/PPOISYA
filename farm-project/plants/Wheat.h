#ifndef FARM_WHEAT_H
#define FARM_WHEAT_H

#include "Crop.h"
#include <string>

class Wheat : public Crop {
private:
    double grainQuality;    // качество зерна (0-100%)
    bool isWinterWheat;     // озимая или яровая пшеница
    int glutenContent;      // содержание глютена (%)

public:
    Wheat(double height, double yield, bool winterWheat = false);

    // Уникальное поведение 13: помол пшеницы в муку
    double grindIntoFlour() const;

    // Уникальное поведение 14: проверка качества зерна
    std::string getQualityGrade() const;

    // Уникальное поведение 15: обработка от вредителей
    void treatForPests();

    // Переопределенные методы
    void displayInfo() const override;
    double calculateExpectedYield() const override;

    // Геттеры и сеттеры
    double getGrainQuality() const;
    bool getIsWinterWheat() const;
    int getGlutenContent() const;

    void setGrainQuality(double quality);
    void setGlutenContent(int gluten);
};

#endif //FARM_WHEAT_H