#ifndef CHICKEN_COOP_H
#define CHICKEN_COOP_H

#include "Building.h"
#include <string>
#include <vector>

class ChickenCoop : public Building {
private:
    int chickenCapacity;
    int numberOfNestingBoxes;
    int numberOfRoosts;
    bool hasRun;
    double runArea; // площадь выгула в кв.м
    std::string predatorProtection;
    int eggsCollectedDaily;
    std::string beddingMaterial;
    bool hasAutomaticFeeder;

public:
    ChickenCoop(const std::string& name, double area, int constructionYear,
                int chickenCapacity = 100);

    void displayInfo() const override;
    void addChickens(int count);
    void collectEggs();
    void cleanCoop();
    void checkForPredators();

    // Геттеры
    int getChickenCapacity() const;
    int getNumberOfNestingBoxes() const;
    int getNumberOfRoosts() const;
    bool getHasRun() const;
    double getRunArea() const;
    std::string getPredatorProtection() const;
    int getEggsCollectedDaily() const;
    std::string getBeddingMaterial() const;
    bool getHasAutomaticFeeder() const;

    // Сеттеры
    void setChickenCapacity(int capacity);
    void setNumberOfNestingBoxes(int boxes);
    void setNumberOfRoosts(int roosts);
    void setHasRun(bool run);
    void setRunArea(double area);
    void setPredatorProtection(const std::string& protection);
    void setEggsCollectedDaily(int eggs);
    void setBeddingMaterial(const std::string& material);
    void setHasAutomaticFeeder(bool feeder);

    double calculateEggProductionValue() const;
    void installAutomaticSystems();
    void maintainRoosts();
    void ventilateCoop();
};

#endif // CHICKEN_COOP_H