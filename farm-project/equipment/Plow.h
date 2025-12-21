#ifndef PLOW_H
#define PLOW_H

#include "Equipment.h"
#include <string>

class Plow : public Equipment {
private:
    int bladeCount;                 // количество лемехов
    double workingWidth;            // рабочая ширина в метрах
    double maxWorkingDepth;         // максимальная глубина вспашки
    std::string plowType;           // тип плуга
    bool isReversible;              // оборотный плуг или нет
    double wearLevel;               // уровень износа (0-100%)

public:
    Plow(const std::string& name, const std::string& manufacturer, int year,
         int bladeCount, double workingWidth);

    // Уникальные методы для плуга
    void adjustDepth(double depth);
    void sharpenBlades();
    double calculateAreaPerHour(double speed) const;
    bool checkBladeWear() const;
    void replaceBlades();

    // Уникальное поведение 11: расчет усилия тяги
    double calculateRequiredTraction() const;

    // Уникальное поведение 12: проверка настройки
    bool isProperlyAdjusted() const;

    // Уникальное поведение 13: расчет расхода топлива
    double calculateFuelConsumption(double area, double soilHardness) const;

    // Переопределенные методы
    void use() override;
    void performMaintenance() override;
    void displayInfo() const override;
    double calculateMaintenanceCost() const override;

    // Геттеры и сеттеры
    int getBladeCount() const;
    double getWorkingWidth() const;
    double getMaxWorkingDepth() const;
    std::string getPlowType() const;
    bool getIsReversible() const;
    double getWearLevel() const;

    void setBladeCount(int count);
    void setWorkingWidth(double width);
    void setMaxWorkingDepth(double depth);
    void setPlowType(const std::string& type);
    void setIsReversible(bool reversible);
    void setWearLevel(double wear);
};

#endif // PLOW_H