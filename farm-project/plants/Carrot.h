#ifndef FARM_CARROT_H
#define FARM_CARROT_H

#include "Vegetable.h"
#include <string>

class Carrot : public Vegetable {
private:
    double rootLength;      // длина корнеплода в см
    double sugarContent;    // содержание сахара (%)
    bool isBabyCarrot;      // молодая морковь

public:
    Carrot(double height);

    // Уникальное поведение 22: измерение длины моркови
    void measureLength();

    // Уникальное поведение 23: проверка сладости
    bool isSweetCarrot() const;

    // Уникальное поведение 24: очистка моркови
    void peelCarrot(int count);

    // Переопределенные методы
    void displayInfo() const override;
    void grow() override;

    // Геттеры и сеттеры
    double getRootLength() const;
    double getSugarContent() const;
    bool getIsBabyCarrot() const;

    void setRootLength(double length);
    void setSugarContent(double sugar);
    void setIsBabyCarrot(bool baby);
};

#endif //FARM_CARROT_H