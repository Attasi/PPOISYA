#ifndef FARM_PLANT_H
#define FARM_PLANT_H

#include <string>
#include <iostream>

class Plant {
protected:
    std::string name;
    double height;          // высота в метрах
    int age;               // возраст в днях
    bool isPlanted;
    double waterLevel;     // уровень влажности
    double health;         // здоровье растения (0-100%)

public:
    Plant(const std::string& plantName, double plantHeight);
    virtual ~Plant() = default;

    // Методы для ухода за растениями
    virtual void water(double amount);
    virtual void grow();
    virtual void harvest();

    // Геттеры
    std::string getName() const;
    double getHeight() const;
    int getAge() const;
    bool getIsPlanted() const;
    double getWaterLevel() const;
    double getHealth() const;

    // Сеттеры
    void setHeight(double h);
    void setAge(int a);
    void setIsPlanted(bool planted);
    void setWaterLevel(double level);
    void setHealth(double h);

    // Виртуальный метод для отображения информации
    virtual void displayInfo() const;

    // Уникальное поведение 1: проверка готовности к сбору урожая
    virtual bool isReadyForHarvest() const;

    // Уникальное поведение 2: лечение растения
    void heal(double amount);

    // Уникальное поведение 3: проверка необходимости полива
    bool needsWatering() const;
};

#endif //FARM_PLANT_H