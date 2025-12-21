#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <iostream>
#include <vector>

class Equipment {
protected:
    std::string name;
    std::string manufacturer;
    int yearOfManufacture;
    double purchasePrice;
    double currentValue;
    bool isOperational;
    int maintenanceInterval; // дни между обслуживанием
    int daysSinceMaintenance;
    std::string location;
    std::string serialNumber;

public:
    Equipment(const std::string& name, const std::string& manufacturer, int year);
    virtual ~Equipment() = default;

    // Основные методы
    virtual void use();
    virtual void performMaintenance();
    virtual void repair();
    virtual void moveTo(const std::string& newLocation);

    // Уникальное поведение 1: расчет амортизации
    virtual double calculateDepreciation() const;

    // Уникальное поведение 2: проверка необходимости обслуживания
    bool needsMaintenance() const;

    // Уникальное поведение 3: оценка остаточной стоимости
    double estimateResidualValue() const;

    // Геттеры
    std::string getName() const;
    std::string getManufacturer() const;
    int getYearOfManufacture() const;
    double getPurchasePrice() const;
    double getCurrentValue() const;
    bool getIsOperational() const;
    int getMaintenanceInterval() const;
    int getDaysSinceMaintenance() const;
    std::string getLocation() const;
    std::string getSerialNumber() const;

    // Сеттеры
    void setName(const std::string& name);
    void setManufacturer(const std::string& manufacturer);
    void setYearOfManufacture(int year);
    void setPurchasePrice(double price);
    void setCurrentValue(double value);
    void setIsOperational(bool operational);
    void setMaintenanceInterval(int interval);
    void setDaysSinceMaintenance(int days);
    void setLocation(const std::string& location);
    void setSerialNumber(const std::string& serial);

    // Виртуальный метод для отображения информации
    virtual void displayInfo() const;

    // Уникальное поведение 4: проверка гарантии
    bool isUnderWarranty(int currentYear) const;

    // Уникальное поведение 5: расчет стоимости обслуживания
    virtual double calculateMaintenanceCost() const;
};

#endif // EQUIPMENT_H