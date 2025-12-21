#ifndef TRACTOR_H
#define TRACTOR_H

#include "Vehicle.h"
#include <string>
#include <vector>

class Tractor : public Vehicle {
private:
    double enginePower;             // мощность двигателя в л.с.
    bool hasFrontLoader;            // есть ли фронтальный погрузчик
    bool hasBackhoe;                // есть ли обратная лопата
    int hydraulicSystemPressure;    // давление гидросистемы (бар)
    std::vector<std::string> attachedImplements; // навесное оборудование

public:
    Tractor(const std::string& name, const std::string& manufacturer, int year,
            double enginePower, bool hasFrontLoader = false);

    // Уникальные методы для трактора
    void attachImplement(const std::string& implement);
    void detachImplement(const std::string& implement);
    void plowField(double area);
    void transportLoad(double weight, double distance);
    bool checkHydraulicSystem() const;

    // Уникальное поведение 8: расчет тягового усилия
    double calculateTractiveEffort() const;

    // Уникальное поведение 9: проверка совместимости оборудования
    bool isImplementCompatible(const std::string& implement) const;

    // Уникальное поведение 10: расчет производительности
    double calculateProductivity(double hours) const;

    // Переопределенные методы
    void use() override;
    void performMaintenance() override;
    void displayInfo() const override;
    double calculateMaintenanceCost() const override;

    // Геттеры и сеттеры
    double getEnginePower() const;
    bool getHasFrontLoader() const;
    bool getHasBackhoe() const;
    int getHydraulicSystemPressure() const;
    std::vector<std::string> getAttachedImplements() const;

    void setEnginePower(double power);
    void setHasFrontLoader(bool hasLoader);
    void setHasBackhoe(bool hasBackhoe);
    void setHydraulicSystemPressure(int pressure);
};

#endif // TRACTOR_H