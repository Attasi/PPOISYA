#include "Equipment.h"
#include "EquipmentExceptions.h"
#include <iostream>
#include <cmath>
#include <string>

Equipment::Equipment(const std::string& name, const std::string& manufacturer, int year)
        : name(name), manufacturer(manufacturer), yearOfManufacture(year),
          purchasePrice(10000.0), currentValue(10000.0), isOperational(true),
          maintenanceInterval(30), daysSinceMaintenance(0),
          location("Storage"), serialNumber("EQ" + std::to_string(year) + "001") {

    // Проверка входных параметров
    if (name.empty()) {
        throw EquipmentException("Equipment name cannot be empty");
    }

    if (manufacturer.empty()) {
        throw EquipmentException("Manufacturer name cannot be empty for " + name);
    }

    if (year < 2000 || year > 2024) {
        throw EquipmentException("Invalid year of manufacture: " + std::to_string(year) +
                                 " for " + name);
    }
}

void Equipment::use() {
    if (!isOperational) {
        throw EquipmentBreakdownException(name, "Not operational",
                                          "Unknown - equipment broken");
    }

    if (needsMaintenance()) {
        std::cout << "Warning: " << name << " needs maintenance!" << std::endl;

        // Использование оборудования, требующего обслуживания, может привести к поломке
        if (daysSinceMaintenance > maintenanceInterval * 2) {
            isOperational = false;
            throw EquipmentBreakdownException(name, "Overdue maintenance failure",
                                              "Unknown - maintenance overdue");
        }
    }

    daysSinceMaintenance++;
    std::cout << name << " is being used." << std::endl;

    // Использование уменьшает стоимость
    currentValue *= 0.999;

    // Периодическая проверка на износ
    if (daysSinceMaintenance % 100 == 0) {
        double wearChance = (2024 - yearOfManufacture) * 0.05;
        if (wearChance > 0.5) {
            isOperational = false;
            throw EquipmentBreakdownException(name, "Normal wear and tear",
                                              "Regular maintenance");
        }
    }
}

void Equipment::performMaintenance() {
    if (!isOperational) {
        throw EquipmentException("Cannot perform maintenance on non-operational equipment: " + name);
    }

    if (daysSinceMaintenance < 7) {
        throw EquipmentException("Maintenance performed too recently on " + name +
                                 " (only " + std::to_string(daysSinceMaintenance) + " days ago)");
    }

    // Проверка наличия запчастей для старого оборудования
    if ((2024 - yearOfManufacture) > 10) {
        double missingPartChance = 0.3;
        if (missingPartChance > 0.2) {
            throw MissingPartsException(name, "OEM replacement part", 14);
        }
    }

    daysSinceMaintenance = 0;
    currentValue *= 1.01; // обслуживание немного увеличивает стоимость
    if (currentValue > purchasePrice) currentValue = purchasePrice;

    std::cout << "Performed maintenance on " << name << std::endl;
    std::cout << "Maintenance cost: $" << calculateMaintenanceCost() << std::endl;
}

void Equipment::repair() {
    if (isOperational) {
        throw EquipmentException("Cannot repair operational equipment: " + name);
    }

    // Проверка на дорогостоящий ремонт
    double repairToValueRatio = purchasePrice / currentValue;
    if (repairToValueRatio > 5.0) {
        throw EquipmentException("Repair cost exceeds equipment value for " + name);
    }

    // Проверка наличия запчастей
    if ((2024 - yearOfManufacture) > 15) {
        throw MissingPartsException(name, "Obsolete component", 30);
    }

    isOperational = true;
    currentValue *= 1.05; // ремонт восстанавливает стоимость
    std::cout << name << " has been repaired." << std::endl;
}

void Equipment::moveTo(const std::string& newLocation) {
    if (newLocation.empty()) {
        throw EquipmentException("Cannot move equipment to empty location");
    }

    if (!isOperational) {
        throw EquipmentException("Cannot move non-operational equipment: " + name);
    }

    // Проверка на безопасное перемещение оборудования, требующего обслуживания
    if (needsMaintenance()) {
        std::cout << "Warning: Moving " << name << " that needs maintenance!" << std::endl;

        if (daysSinceMaintenance > maintenanceInterval * 1.5) {
            isOperational = false;
            throw EquipmentBreakdownException(name, "Damage during transport",
                                              "Unknown - maintenance overdue");
        }
    }

    std::cout << "Moving " << name << " from " << location
              << " to " << newLocation << std::endl;
    location = newLocation;
}

double Equipment::calculateDepreciation() const {
    int age = 2024 - yearOfManufacture;
    if (age < 0) {
        throw EquipmentException("Invalid equipment age calculation for " + name);
    }

    double depreciationRate = 0.1; // 10% в год
    return purchasePrice * depreciationRate * age;
}

bool Equipment::needsMaintenance() const {
    return daysSinceMaintenance >= maintenanceInterval;
}

double Equipment::estimateResidualValue() const {
    int age = 2024 - yearOfManufacture;
    if (age < 0) {
        throw EquipmentException("Invalid equipment age for residual value calculation: " + name);
    }

    double annualDepreciation = 0.15; // 15% в год
    double residual = purchasePrice * pow(1 - annualDepreciation, age);

    if (residual < 0) {
        residual = 0;
    }

    // Если оборудование не работает, остаточная стоимость уменьшается
    if (!isOperational) {
        residual *= 0.5;
    }

    return residual;
}

std::string Equipment::getName() const { return name; }
std::string Equipment::getManufacturer() const { return manufacturer; }
int Equipment::getYearOfManufacture() const { return yearOfManufacture; }
double Equipment::getPurchasePrice() const { return purchasePrice; }
double Equipment::getCurrentValue() const { return currentValue; }
bool Equipment::getIsOperational() const { return isOperational; }
int Equipment::getMaintenanceInterval() const { return maintenanceInterval; }
int Equipment::getDaysSinceMaintenance() const { return daysSinceMaintenance; }
std::string Equipment::getLocation() const { return location; }
std::string Equipment::getSerialNumber() const { return serialNumber; }

void Equipment::setName(const std::string& name) {
    if (name.empty()) {
        throw EquipmentException("Equipment name cannot be empty");
    }
    this->name = name;
}

void Equipment::setManufacturer(const std::string& manufacturer) {
    if (manufacturer.empty()) {
        throw EquipmentException("Manufacturer name cannot be empty");
    }
    this->manufacturer = manufacturer;
}

void Equipment::setYearOfManufacture(int year) {
    if (year < 2000 || year > 2024) {
        throw EquipmentException("Invalid year of manufacture: " + std::to_string(year));
    }
    yearOfManufacture = year;
}

void Equipment::setPurchasePrice(double price) {
    if (price <= 0) {
        throw EquipmentException("Purchase price must be positive: $" + std::to_string(price));
    }
    purchasePrice = price;
}

void Equipment::setCurrentValue(double value) {
    if (value < 0) {
        throw EquipmentException("Current value cannot be negative: $" + std::to_string(value));
    }
    currentValue = value;
}

void Equipment::setIsOperational(bool operational) { isOperational = operational; }

void Equipment::setMaintenanceInterval(int interval) {
    if (interval <= 0) {
        throw EquipmentException("Maintenance interval must be positive: " + std::to_string(interval));
    }
    maintenanceInterval = interval;
}

void Equipment::setDaysSinceMaintenance(int days) {
    if (days < 0) {
        throw EquipmentException("Days since maintenance cannot be negative: " + std::to_string(days));
    }
    daysSinceMaintenance = days;
}

void Equipment::setLocation(const std::string& location) {
    if (location.empty()) {
        throw EquipmentException("Location cannot be empty");
    }
    this->location = location;
}

void Equipment::setSerialNumber(const std::string& serial) {
    if (serial.empty()) {
        throw EquipmentException("Serial number cannot be empty");
    }
    serialNumber = serial;
}

void Equipment::displayInfo() const {
    std::cout << "=== Equipment Information ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Manufacturer: " << manufacturer << std::endl;
    std::cout << "Year: " << yearOfManufacture << std::endl;
    std::cout << "Purchase Price: $" << purchasePrice << std::endl;
    std::cout << "Current Value: $" << currentValue << std::endl;
    std::cout << "Operational: " << (isOperational ? "Yes" : "No") << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Serial Number: " << serialNumber << std::endl;
    std::cout << "Days since maintenance: " << daysSinceMaintenance
              << " (Interval: " << maintenanceInterval << " days)" << std::endl;
    std::cout << "Needs maintenance: " << (needsMaintenance() ? "Yes" : "No") << std::endl;

    try {
        std::cout << "Depreciation: $" << calculateDepreciation() << std::endl;
        std::cout << "Estimated residual value: $" << estimateResidualValue() << std::endl;
    } catch (const EquipmentException& e) {
        std::cout << "Depreciation calculation error: " << e.what() << std::endl;
    }
}

bool Equipment::isUnderWarranty(int currentYear) const {
    if (currentYear < yearOfManufacture) {
        throw EquipmentException("Current year cannot be before manufacture year for " + name);
    }

    return (currentYear - yearOfManufacture) <= 3; // 3 года гарантии
}

double Equipment::calculateMaintenanceCost() const {
    if (!isOperational) {
        throw EquipmentException("Cannot calculate maintenance cost for non-operational equipment: " + name);
    }

    double baseCost = 100.0;
    int age = 2024 - yearOfManufacture;

    if (age < 0) {
        throw EquipmentException("Invalid equipment age for maintenance cost calculation: " + name);
    }

    double ageFactor = age * 10.0;

    // Дополнительная стоимость, если обслуживание просрочено
    if (needsMaintenance()) {
        double overdueFactor = (daysSinceMaintenance - maintenanceInterval) * 2.0;
        baseCost += overdueFactor;
    }

    return baseCost + ageFactor;
}