#ifndef FARM_APPLETREE_H
#define FARM_APPLETREE_H

#include "Fruit.h"
#include <string>

class AppleTree : public Fruit {
private:
    double trunkDiameter;   // диаметр ствола в см
    int branchCount;        // количество ветвей
    std::string appleType;  // сорт яблок
    bool isDwarf;           // карликовое дерево или обычное

public:
    AppleTree(double height, const std::string& type = "Gala");

    // Уникальное поведение 28: обрезка ветвей
    void pruneBranches(int count);

    // Уникальное поведение 29: сбор яблок с дерева
    int pickApples(int count);

    // Уникальное поведение 30: проверка здоровья дерева
    std::string getTreeHealthStatus() const;

    // Переопределенные методы
    void displayInfo() const override;
    void grow() override;

    // Геттеры и сеттеры
    double getTrunkDiameter() const;
    int getBranchCount() const;
    std::string getAppleType() const;
    bool getIsDwarf() const;

    void setTrunkDiameter(double diameter);
    void setBranchCount(int count);
    void setAppleType(const std::string& type);
    void setIsDwarf(bool dwarf);
};

#endif //FARM_APPLETREE_H