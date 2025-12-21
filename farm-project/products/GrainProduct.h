#ifndef GRAINPRODUCT_H
#define GRAINPRODUCT_H

#include "Product.h"
#include <string>
#include <vector>

class GrainProduct : public Product {
private:
    std::string grainType;          // пшеница, кукуруза, ячмень и т.д.
    double moistureContent;         // влажность зерна (%)
    double proteinContent;          // содержание белка (%)
    bool isCleaned;                 // очищено ли зерно
    std::string millingGrade;       // сорт помола
    std::vector<std::string> contaminants; // возможные загрязнители

public:
    GrainProduct(const std::string& name, double quantity, double pricePerUnit,
                 const std::string& grainType);

    // Уникальные методы для зерновой продукции
    void cleanGrain();                                   // Очистка зерна
    double calculateNutritionalValue() const;            // Расчет питательной ценности
    bool checkMoistureLevel() const;                     // Проверка уровня влажности
    void addContaminant(const std::string& contaminant); // Добавление загрязнителя
    void removeContaminants();                           // Удаление загрязнителей
    std::string getGrainClass() const;                   // Получение класса зерна

    // Переопределенные методы
    void displayInfo() const override;
    void updateQuality() override;
    void package() override;
    bool meetsExportStandards() const override;
    void inspectQuality() override;

    // Геттеры и сеттеры
    std::string getGrainType() const;
    double getMoistureContent() const;
    double getProteinContent() const;
    bool getIsCleaned() const;
    std::string getMillingGrade() const;
    std::vector<std::string> getContaminants() const;

    void setGrainType(const std::string& type);
    void setMoistureContent(double moisture);
    void setProteinContent(double protein);
    void setMillingGrade(const std::string& grade);
};

#endif // GRAINPRODUCT_H