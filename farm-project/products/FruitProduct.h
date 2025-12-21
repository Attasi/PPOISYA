#ifndef FRUITPRODUCT_H
#define FRUITPRODUCT_H

#include "Product.h"
#include <string>
#include <vector>

class FruitProduct : public Product {
private:
    void updateRipenessStage();     // Вспомогательный метод для обновления стадии спелости
    std::string fruitType;          // яблоки, груши, ягоды и т.д.
    double ripenessLevel;           // уровень спелости (0-100%)
    std::string ripenessStage;      // зеленый, созревающий, спелый, переспелый
    bool isPackagedInBaskets;       // упаковано в корзины
    int brixLevel;                  // уровень Брикса (содержание сахара)
    std::vector<std::string> bruises; // синяки/повреждения

public:
    FruitProduct(const std::string& name, double quantity, double pricePerUnit,
                 const std::string& fruitType);

    // Уникальные методы для фруктовой продукции
    void ripenFruit(double amount);                       // Дозревание фруктов
    std::string checkRipenessStage() const;               // Проверка стадии спелости
    void packageInBaskets();                              // Упаковка в корзины
    void addBruise(const std::string& bruiseLocation);    // Добавление синяка
    void removeBruises();                                 // Удаление синяков
    double calculateSugarContent() const;                  // Расчет содержания сахара
    bool isReadyForSale() const;                          // Готовы ли для продажи

    // Переопределенные методы
    void displayInfo() const override;
    void updateQuality() override;
    void package() override;
    bool meetsExportStandards() const override;
    void inspectQuality() override;

    // Геттеры и сеттеры
    std::string getFruitType() const;
    double getRipenessLevel() const;
    std::string getRipenessStage() const;
    bool getIsPackagedInBaskets() const;
    int getBrixLevel() const;
    std::vector<std::string> getBruises() const;

    void setFruitType(const std::string& type);
    void setRipenessLevel(double ripeness);
    void setBrixLevel(int brix);
    void setIsPackagedInBaskets(bool packaged);
};

#endif // FRUITPRODUCT_H