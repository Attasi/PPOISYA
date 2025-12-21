#ifndef VEGETABLEPRODUCT_H
#define VEGETABLEPRODUCT_H

#include "Product.h"
#include <string>
#include <vector>

class VegetableProduct : public Product {
private:
    std::string vegetableType;      // морковь, картофель, помидоры и т.д.
    double freshnessLevel;          // уровень свежести (0-100%)
    bool isWashed;                  // вымыты ли овощи
    bool isCut;                     // нарезаны ли овощи
    std::string sizeCategory;       // размерная категория
    std::vector<std::string> defects; // дефекты продукции

public:
    VegetableProduct(const std::string& name, double quantity, double pricePerUnit,
                     const std::string& vegetableType);

    // Уникальные методы для овощной продукции
    void washVegetables();                                  // Мытье овощей
    void cutVegetables();                                   // Нарезка овощей
    void checkFreshness();                                  // Проверка свежести
    void addDefect(const std::string& defect);              // Добавление дефекта
    void removeDefects();                                   // Удаление дефектов
    double calculateVitaminContent() const;                 // Расчет содержания витаминов
    bool isReadyForCooking() const;                         // Готовы ли для готовки

    // Переопределенные методы
    void displayInfo() const override;
    void updateQuality() override;
    void package() override;
    bool meetsExportStandards() const override;
    void inspectQuality() override;

    // Геттеры и сеттеры
    std::string getVegetableType() const;
    double getFreshnessLevel() const;
    bool getIsWashed() const;
    bool getIsCut() const;
    std::string getSizeCategory() const;
    std::vector<std::string> getDefects() const;

    void setVegetableType(const std::string& type);
    void setFreshnessLevel(double freshness);
    void setIsWashed(bool washed);
    void setIsCut(bool cut);
    void setSizeCategory(const std::string& category);
};

#endif // VEGETABLEPRODUCT_H