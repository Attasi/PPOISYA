#ifndef FARM_FRUIT_H
#define FARM_FRUIT_H

#include "Plant.h"
#include <string>

class Fruit : public Plant {
protected:
    double sweetness;       // сладость (0-100%)
    int fruitCount;         // количество плодов
    bool isEdibleRaw;       // можно есть сырым
    std::string taste;      // вкус

public:
    Fruit(const std::string& fruitName, double height, double sweetLevel);

    // Уникальное поведение 10: сбор плодов
    virtual int harvestFruit(int amount);

    // Уникальное поведение 11: проверка спелости по сладости
    bool isSweetEnough() const;

    // Уникальное поведение 12: опыление растения
    void pollinate();

    // Переопределенные методы
    void displayInfo() const override;
    bool isReadyForHarvest() const override;

    // Геттеры и сеттеры
    double getSweetness() const;
    int getFruitCount() const;
    bool getIsEdibleRaw() const;
    std::string getTaste() const;

    void setSweetness(double sweet);
    void setFruitCount(int count);
    void setIsEdibleRaw(bool edible);
    void setTaste(const std::string& t);
};

#endif //FARM_FRUIT_H