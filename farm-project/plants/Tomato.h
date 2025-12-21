#ifndef FARM_TOMATO_H
#define FARM_TOMATO_H

#include "Vegetable.h"
#include <string>

class Tomato : public Vegetable {
private:
    int tomatoCount;        // количество помидоров
    double tomatoSize;      // размер помидора в см
    bool isCherryTomato;    // черри или обычный
    std::string ripeness;   // степень зрелости

public:
    Tomato(double height, bool cherryTomato = false);

    // Уникальное поведение 25: сбор помидоров
    int harvestTomatoes(int count);

    // Уникальное поведение 26: проверка зрелости
    void checkRipeness();

    // Уникальное поведение 27: приготовление томатного соуса
    void makeSauce(int tomatoesNeeded);

    // Переопределенные методы
    void displayInfo() const override;
    void grow() override;

    // Геттеры и сеттеры
    int getTomatoCount() const;
    double getTomatoSize() const;
    bool getIsCherryTomato() const;
    std::string getRipeness() const;

    void setTomatoCount(int count);
    void setTomatoSize(double size);
    void setIsCherryTomato(bool cherry);
    void setRipeness(const std::string& r);
};

#endif //FARM_TOMATO_H