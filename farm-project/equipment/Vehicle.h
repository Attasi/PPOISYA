#ifndef VEHICLE_H
#define VEHICLE_H

#include "Equipment.h"
#include <string>

class Vehicle : public Equipment {
protected:
    std::string fuelType;           // бензин, дизель, электричество
    double fuelCapacity;            // емкость бака в литрах
    double currentFuelLevel;        // текущий уровень топлива
    double fuelEfficiency;          // расход топлива (л/100км)
    double mileage;                 // пробег в км
    std::string licensePlate;
    bool hasInsurance;

public:
    Vehicle(const std::string& name, const std::string& manufacturer, int year,
            const std::string& fuelType, double fuelCapacity);

    // Уникальные методы для транспортных средств
    void refuel(double amount);
    void drive(double distance);
    bool checkFuelLevel() const;
    void renewInsurance();
    double calculateFuelCost(double distance, double fuelPrice) const;

    // Уникальное поведение 6: расчет остатка хода
    double calculateRange() const;

    // Уникальное поведение 7: проверка необходимости замены масла
    bool needsOilChange() const;

    // Переопределенные методы
    void use() override;
    void performMaintenance() override;
    void displayInfo() const override;
    double calculateMaintenanceCost() const override;

    // Геттеры и сеттеры
    std::string getFuelType() const;
    double getFuelCapacity() const;
    double getCurrentFuelLevel() const;
    double getFuelEfficiency() const;
    double getMileage() const;
    std::string getLicensePlate() const;
    bool getHasInsurance() const;

    void setFuelType(const std::string& type);
    void setFuelCapacity(double capacity);
    void setCurrentFuelLevel(double level);
    void setFuelEfficiency(double efficiency);
    void setMileage(double km);
    void setLicensePlate(const std::string& plate);
    void setHasInsurance(bool insured);
};

#endif // VEHICLE_H