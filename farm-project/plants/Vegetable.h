#ifndef FARM_VEGETABLE_H
#define FARM_VEGETABLE_H

#include "Plant.h"
#include <string>

class Vegetable : public Plant {
protected:
    bool isRootVegetable;   // корнеплод или нет
    double vitaminContent;  // содержание витаминов
    int harvestCount;       // количество сборов урожая
    std::string color;      // цвет овоща

public:
    Vegetable(const std::string& vegName, double height, bool rootVeg);

    // Уникальное поведение 7: сбор урожая с возможностью повторного сбора
    virtual void harvestVegetable();

    // Уникальное поведение 8: проверка, является ли овощ спелым
    bool isRipe() const;

    // Уникальное поведение 9: получение информации о питательной ценности
    virtual double getNutritionalValue() const;

    // Переопределенные методы
    void displayInfo() const override;

    // Геттеры и сеттеры
    bool getIsRootVegetable() const;
    double getVitaminContent() const;
    int getHarvestCount() const;
    std::string getColor() const;

    void setIsRootVegetable(bool root);
    void setVitaminContent(double vitamins);
    void setColor(const std::string& c);
};

#endif //FARM_VEGETABLE_H