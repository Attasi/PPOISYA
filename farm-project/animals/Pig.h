#ifndef PIG_H
#define PIG_H

#include "Mammal.h"
#include <string>

class Pig : public Mammal {
private:
    double fatPercentage;
    std::string snoutType;
    int wallowFrequency;
    std::string penNumber;
    double feedConversionRate;
    std::string tailType;
    int mudBathEnjoyment;
    std::string feedingSchedule;
    bool isForaging;

public:
    Pig(const std::string& name, int age, double weight, const std::string& breed = "Yorkshire");

    void makeSound() const override;
    void wallowInMud();
    void forage();
    void root();
    void sleep() override;

    // Геттеры
    double getFatPercentage() const;
    std::string getSnoutType() const;
    int getWallowFrequency() const;
    std::string getPenNumber() const;
    double getFeedConversionRate() const;
    std::string getTailType() const;
    int getMudBathEnjoyment() const;
    std::string getFeedingSchedule() const;
    bool getIsForaging() const;

    // Сеттеры
    void setFatPercentage(double percentage);
    void setSnoutType(const std::string& type);
    void setWallowFrequency(int frequency);
    void setPenNumber(const std::string& pen);
    void setFeedConversionRate(double rate);
    void setTailType(const std::string& type);
    void setMudBathEnjoyment(int enjoyment);
    void setFeedingSchedule(const std::string& schedule);
    void setIsForaging(bool foraging);

    double calculateDailyFood() const override;
    void displayInfo() const override;
    void calculateWeightGain();
    void cleanPen();
    void scheduleFeeding();
};

#endif // PIG_H