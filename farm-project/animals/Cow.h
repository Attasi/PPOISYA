#ifndef COW_H
#define COW_H

#include "Mammal.h"
#include <string>

class Cow : public Mammal {
private:
    double milkProduction; // литров в день
    std::string hornType;
    int milkQuality; // 1-10
    bool isMilking;
    std::string pastureArea;
    int grazingHours;
    double methaneProduction;
    std::string cowbellSound;
    bool hasBell;

public:
    Cow(const std::string& name, int age, double weight, const std::string& breed = "Holstein");

    void makeSound() const override;
    void produceMilk() override;
    void graze();
    void ringBell();
    void chewCud();

    // Геттеры
    double getMilkProduction() const;
    std::string getHornType() const;
    int getMilkQuality() const;
    bool getIsMilking() const;
    std::string getPastureArea() const;
    int getGrazingHours() const;
    double getMethaneProduction() const;
    std::string getCowbellSound() const;
    bool getHasBell() const;

    // Сеттеры
    void setMilkProduction(double production);
    void setHornType(const std::string& type);
    void setMilkQuality(int quality);
    void setIsMilking(bool milking);
    void setPastureArea(const std::string& area);
    void setGrazingHours(int hours);
    void setMethaneProduction(double methane);
    void setCowbellSound(const std::string& sound);
    void setHasBell(bool hasBell);

    double calculateDailyFood() const override;
    void displayInfo() const override;
    double calculateMilkValue() const;
    void startMilkingSession();
    void stopMilkingSession();
};

#endif // COW_H