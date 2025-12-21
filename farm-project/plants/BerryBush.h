#ifndef FARM_BERRYBUSH_H
#define FARM_BERRYBUSH_H

#include "Fruit.h"
#include <string>
#include <vector>

class BerryBush : public Fruit {
private:
    std::string berryType;          // тип ягод (клубника, малина и т.д.)
    int bushAge;                    // возраст куста в годах
    bool isThorny;                  // колючий куст или нет
    std::vector<std::string> pests; // вредители на кусте

public:
    BerryBush(double height, const std::string& type = "Strawberry");

    // Уникальное поведение 31: сбор ягод
    int pickBerries(int count);

    // Уникальное поведение 32: добавление вредителя
    void addPest(const std::string& pest);

    // Уникальное поведение 33: обработка от вредителей
    void sprayForPests();

    // Уникальное поведение 34: размножение куста
    bool canPropagate() const;

    // Переопределенные методы
    void displayInfo() const override;
    void grow() override;

    // Геттеры и сеттеры
    std::string getBerryType() const;
    int getBushAge() const;
    bool getIsThorny() const;
    std::vector<std::string> getPests() const;

    void setBerryType(const std::string& type);
    void setBushAge(int age);
    void setIsThorny(bool thorny);
};

#endif //FARM_BERRYBUSH_H