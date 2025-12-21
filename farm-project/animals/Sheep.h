#ifndef SHEEP_H
#define SHEEP_H

#include "Mammal.h"
#include <string>

class Sheep : public Mammal {
private:
    double woolProduction; // кг в год
    std::string woolQuality;
    bool isSheared;
    std::string flockNumber;
    int grazingRadius;
    double woolLength;
    std::string shepherdCall;
    bool hasLambs;
    int lambCount;

public:
    Sheep(const std::string& name, int age, double weight, const std::string& breed = "Merino");

    void makeSound() const override;
    void produceWool();
    void graze() const;
    void followShepherd();
    void bleat();

    // Геттеры
    double getWoolProduction() const;
    std::string getWoolQuality() const;
    bool getIsSheared() const;
    std::string getFlockNumber() const;
    int getGrazingRadius() const;
    double getWoolLength() const;
    std::string getShepherdCall() const;
    bool getHasLambs() const;
    int getLambCount() const;

    // Сеттеры
    void setWoolProduction(double production);
    void setWoolQuality(const std::string& quality);
    void setIsSheared(bool sheared);
    void setFlockNumber(const std::string& flock);
    void setGrazingRadius(int radius);
    void setWoolLength(double length);
    void setShepherdCall(const std::string& call);
    void setHasLambs(bool hasLambs);
    void setLambCount(int count);

    double calculateDailyFood() const override;
    void displayInfo() const override;
    void shearWool();
    double calculateWoolValue() const;
    void addLamb();
};

#endif // SHEEP_H