#include "Vehicle.h"
#include "EquipmentExceptions.h"
#include <iostream>
#include <string>
#include <cmath>

Vehicle::Vehicle(const std::string& name, const std::string& manufacturer, int year,
                 const std::string& fuelType, double fuelCapacity)
        : Equipment(name, manufacturer, year), fuelType(fuelType),
          fuelCapacity(fuelCapacity), currentFuelLevel(fuelCapacity),
          fuelEfficiency(10.0), mileage(0.0), licensePlate("AGRI" + std::to_string(year)),
          hasInsurance(true) {

    // Проверка специфичных для транспортных средств параметров
    if (fuelType.empty()) {
        throw EquipmentException("Vehicle fuel type cannot be empty for " + name);
    }

    std::vector<std::string> validFuelTypes = {"Gasoline", "Diesel", "Electric", "Hybrid", "LPG"};
    bool validFuel = false;
    for (const auto& type : validFuelTypes) {
        if (fuelType == type) {
            validFuel = true;
            break;
        }
    }

    if (!validFuel) {
        throw EquipmentException("Invalid fuel type: " + fuelType +
                                 " (valid: Gasoline, Diesel, Electric, Hybrid, LPG) for " + name);
    }

    if (fuelCapacity <= 0) {
        throw EquipmentException("Vehicle fuel capacity must be positive: " +
                                 std::to_string(fuelCapacity) + "L for " + name);
    }

    if (fuelCapacity > 1000.0) {
        throw EquipmentException("Vehicle fuel capacity too large: " +
                                 std::to_string(fuelCapacity) + "L (max 1000) for " + name);
    }

    // Проверка совместимости топлива для старых транспортных средств
    if (year < 2010 && fuelType == "Electric") {
        throw EquipmentException("Electric vehicles not supported before 2010 for " + name);
    }

    purchasePrice = 50000.0;
    currentValue = 50000.0;
}

void Vehicle::refuel(double amount) {
    if (!isOperational) {
        throw EquipmentException("Cannot refuel non-operational vehicle: " + name);
    }

    if (amount <= 0) {
        throw EquipmentException("Refuel amount must be positive: " +
                                 std::to_string(amount) + "L for " + name);
    }

    if (amount > fuelCapacity * 2) {
        throw EquipmentException("Refuel amount suspiciously large: " +
                                 std::to_string(amount) + "L for capacity " +
                                 std::to_string(fuelCapacity) + "L for " + name);
    }

    // Проверка на наличие нужного типа топлива
    if (fuelType == "Electric") {
        throw EquipmentException("Electric vehicle " + name +
                                 " requires charging, not refueling");
    }

    double oldLevel = currentFuelLevel;
    currentFuelLevel += amount;

    if (currentFuelLevel > fuelCapacity) {
        currentFuelLevel = fuelCapacity;
        std::cout << "Warning: Fuel overflow! Fuel level capped at capacity." << std::endl;
    }

    std::cout << "Refueled " << name << " with " << amount
              << " liters. Current level: " << currentFuelLevel
              << "/" << fuelCapacity << "L" << std::endl;
}

void Vehicle::drive(double distance) {
    if (!isOperational) {
        throw EquipmentBreakdownException(name, "Not operational",
                                          "Unknown - vehicle broken");
    }

    if (!hasInsurance) {
        throw EquipmentException("Cannot drive uninsured vehicle: " + name);
    }

    if (distance <= 0) {
        throw EquipmentException("Drive distance must be positive: " +
                                 std::to_string(distance) + " km for " + name);
    }

    if (distance > 1000.0) {
        throw EquipmentException("Drive distance too long: " +
                                 std::to_string(distance) + " km (max 1000) for " + name);
    }

    if (!checkFuelLevel()) {
        throw EquipmentException("Insufficient fuel for " + name +
                                 " (current level: " + std::to_string(currentFuelLevel) + "L)");
    }

    double fuelNeeded = (distance / 100.0) * fuelEfficiency;

    if (currentFuelLevel < fuelNeeded) {
        double missingFuel = fuelNeeded - currentFuelLevel;
        throw EquipmentException("Not enough fuel to drive " +
                                 std::to_string(distance) + " km for " + name +
                                 ". Need " + std::to_string(missingFuel) + "L more.");
    }

    if (needsMaintenance()) {
        std::cout << "Warning: " << name << " needs maintenance!" << std::endl;

        // Вождение транспортного средства, требующего обслуживания, может привести к поломке
        if (daysSinceMaintenance > maintenanceInterval * 2) {
            isOperational = false;
            throw EquipmentBreakdownException(name, "Overdue maintenance failure",
                                              "Unknown - maintenance overdue");
        }
    }

    if (needsOilChange()) {
        throw EquipmentException("Oil change required before driving " + name);
    }

    // Выполнение поездки
    currentFuelLevel -= fuelNeeded;
    mileage += distance;
    daysSinceMaintenance++;

    std::cout << name << " drove " << distance << " km." << std::endl;
    std::cout << "Fuel used: " << fuelNeeded << "L. Remaining: "
              << currentFuelLevel << "L" << std::endl;
    std::cout << "Total mileage: " << mileage << " km" << std::endl;

    // Уменьшение стоимости из-за износа
    double depreciation = distance * 0.00001;
    currentValue *= (1 - depreciation);

    // Проверка на критический пробег
    if (mileage > 300000.0) {
        double failureChance = (mileage - 300000.0) / 100000.0 * 0.1;
        if (failureChance > 0.05) {
            isOperational = false;
            throw EquipmentBreakdownException(name, "High mileage failure",
                                              "Regular maintenance - high mileage");
        }
    }

    // Автоматическая проверка уровня масла после длительной поездки
    if (distance > 200.0 && fuelType != "Electric") {
        if (mileage > 10000.0 && (static_cast<int>(mileage) % 10000) < 500) {
            throw EquipmentException("Oil level low detected after long drive for " + name);
        }
    }
}

bool Vehicle::checkFuelLevel() const {
    return currentFuelLevel > (fuelCapacity * 0.1); // больше 10%
}

void Vehicle::renewInsurance() {
    if (!isOperational) {
        throw EquipmentException("Cannot renew insurance for non-operational vehicle: " + name);
    }

    // Проверка на наличие обязательного техосмотра для страховки
    if (daysSinceMaintenance > maintenanceInterval * 3) {
        throw EquipmentException("Vehicle " + name +
                                 " requires maintenance before insurance renewal");
    }

    if (mileage > 200000.0 && !hasInsurance) {
        throw EquipmentException("High mileage vehicle " + name +
                                 " may have limited insurance options");
    }

    hasInsurance = true;
    std::cout << "Insurance renewed for " << name << std::endl;
}

double Vehicle::calculateFuelCost(double distance, double fuelPrice) const {
    if (distance <= 0) {
        throw EquipmentException("Distance must be positive: " +
                                 std::to_string(distance) + " km for " + name);
    }

    if (fuelPrice <= 0) {
        throw EquipmentException("Fuel price must be positive: $" +
                                 std::to_string(fuelPrice) + " for " + name);
    }

    if (!isOperational) {
        throw EquipmentException("Cannot calculate fuel cost for non-operational vehicle: " + name);
    }

    if (fuelType == "Electric") {
        throw EquipmentException("Electric vehicle " + name +
                                 " uses electricity, not fuel");
    }

    double fuelNeeded = (distance / 100.0) * fuelEfficiency;
    return fuelNeeded * fuelPrice;
}

double Vehicle::calculateRange() const {
    if (!isOperational) {
        throw EquipmentException("Cannot calculate range for non-operational vehicle: " + name);
    }

    if (currentFuelLevel <= 0) {
        throw EquipmentException("Cannot calculate range with empty fuel tank for " + name);
    }

    if (fuelEfficiency <= 0) {
        throw EquipmentException("Invalid fuel efficiency: " +
                                 std::to_string(fuelEfficiency) + " L/100km for " + name);
    }

    double range = (currentFuelLevel / fuelEfficiency) * 100.0;

    // Корректировка диапазона на основе износа
    if (mileage > 150000.0) {
        range *= 0.9; // снижение дальности на 10% для старых транспортных средств
    }

    return range;
}

bool Vehicle::needsOilChange() const {
    if (fuelType == "Electric") {
        return false; // электромобили не требуют замены масла
    }

    return mileage >= 5000.0 && (static_cast<int>(mileage) % 5000) < 100;
}

void Vehicle::use() {
    if (!checkFuelLevel()) {
        throw EquipmentException("Insufficient fuel for using vehicle: " + name);
    }

    try {
        // Для транспортных средств использование - это поездка на 50 км
        drive(50.0);
    } catch (const EquipmentException& e) {
        throw EquipmentException("Failed to use vehicle " + name + ": " + e.what());
    }
}

void Vehicle::performMaintenance() {
    if (!hasInsurance && fuelType != "Electric") {
        throw EquipmentException("Vehicle " + name +
                                 " requires valid insurance for maintenance");
    }

    // Вызов базового метода обслуживания с обработкой исключений
    try {
        Equipment::performMaintenance();
    } catch (const EquipmentException& e) {
        throw EquipmentException("Failed to perform base maintenance on vehicle " + name +
                                 ": " + e.what());
    }

    // Дополнительные действия для ТС
    if (needsOilChange()) {
        std::cout << "Changing oil for " << name << std::endl;

        // Проверка наличия масла правильного типа
        if (fuelType == "Diesel") {
            double missingPartChance = 0.1;
            if (missingPartChance > 0.05) {
                throw MissingPartsException(name, "Diesel engine oil", 3);
            }
        }

        // После замены масла сбрасываем счетчик для следующей замены
        mileage = static_cast<int>(mileage / 5000) * 5000;
    }

    // Проверка и замена фильтров
    std::cout << "Checking and replacing filters if necessary." << std::endl;

    // Проверка наличия топливного фильтра
    if (mileage > 30000.0 && fuelType != "Electric") {
        double filterChance = 0.2;
        if (filterChance > 0.15) {
            throw MissingPartsException(name, "Fuel filter", 5);
        }
    }

    // Специальная проверка для электромобилей
    if (fuelType == "Electric") {
        std::cout << "Checking battery health for electric vehicle " << name << std::endl;

        if (mileage > 100000.0) {
            throw EquipmentException("Electric vehicle " + name +
                                     " battery may need replacement soon (high mileage)");
        }
    }
}

void Vehicle::displayInfo() const {
    Equipment::displayInfo();
    std::cout << "=== Vehicle Details ===" << std::endl;
    std::cout << "Fuel type: " << fuelType << std::endl;
    std::cout << "Fuel capacity: " << fuelCapacity << "L" << std::endl;
    std::cout << "Current fuel: " << currentFuelLevel << "L" << std::endl;
    std::cout << "Fuel efficiency: " << fuelEfficiency << "L/100km" << std::endl;
    std::cout << "Mileage: " << mileage << " km" << std::endl;
    std::cout << "License plate: " << licensePlate << std::endl;
    std::cout << "Insurance: " << (hasInsurance ? "Valid" : "Expired") << std::endl;

    try {
        std::cout << "Current range: " << calculateRange() << " km" << std::endl;
    } catch (const EquipmentException& e) {
        std::cout << "Current range: Cannot calculate - " << e.what() << std::endl;
    }

    std::cout << "Needs oil change: " << (needsOilChange() ? "Yes" : "No") << std::endl;
    std::cout << "Fuel level OK: " << (checkFuelLevel() ? "Yes" : "No") << std::endl;

    // Дополнительная информация о необходимости обслуживания
    if (mileage > 200000.0) {
        std::cout << "Warning: High mileage vehicle - may require major service soon." << std::endl;
    }

    if (fuelType == "Electric" && mileage > 80000.0) {
        std::cout << "Note: Electric vehicle battery warranty may expire soon." << std::endl;
    }
}

double Vehicle::calculateMaintenanceCost() const {
    if (!isOperational) {
        throw EquipmentException("Cannot calculate maintenance cost for non-operational vehicle: " + name);
    }

    if (!hasInsurance && fuelType != "Electric") {
        throw EquipmentException("Uninsured vehicle " + name +
                                 " has higher maintenance costs");
    }

    try {
        double baseCost = Equipment::calculateMaintenanceCost();
        double mileageCost = mileage * 0.01; // 1 цент за км
        double fuelTypeCost = (fuelType == "Diesel") ? 200.0 : 100.0;

        // Дополнительная стоимость для старых транспортных средств
        if ((2024 - yearOfManufacture) > 10) {
            baseCost *= 1.5;
        }

        // Дополнительная стоимость для электромобилей
        if (fuelType == "Electric") {
            if (mileage > 50000.0) {
                baseCost += 500.0; // возможная замена батареи
            }
        }

        return baseCost + mileageCost + fuelTypeCost;
    } catch (const EquipmentException& e) {
        throw EquipmentException("Failed to calculate vehicle maintenance cost: " +
                                 std::string(e.what()));
    }
}

std::string Vehicle::getFuelType() const { return fuelType; }
double Vehicle::getFuelCapacity() const { return fuelCapacity; }
double Vehicle::getCurrentFuelLevel() const { return currentFuelLevel; }
double Vehicle::getFuelEfficiency() const { return fuelEfficiency; }
double Vehicle::getMileage() const { return mileage; }
std::string Vehicle::getLicensePlate() const { return licensePlate; }
bool Vehicle::getHasInsurance() const { return hasInsurance; }

void Vehicle::setFuelType(const std::string& type) {
    std::vector<std::string> validFuelTypes = {"Gasoline", "Diesel", "Electric", "Hybrid", "LPG"};
    bool validFuel = false;
    for (const auto& validType : validFuelTypes) {
        if (type == validType) {
            validFuel = true;
            break;
        }
    }

    if (!validFuel) {
        throw EquipmentException("Invalid fuel type: " + type);
    }

    // Проверка совместимости для изменения типа топлива
    if (type == "Electric" && yearOfManufacture < 2010) {
        throw EquipmentException("Cannot change to electric for pre-2010 vehicle");
    }

    fuelType = type;
}

void Vehicle::setFuelCapacity(double capacity) {
    if (capacity <= 0) {
        throw EquipmentException("Fuel capacity must be positive: " +
                                 std::to_string(capacity) + "L");
    }

    if (capacity > 1000.0) {
        throw EquipmentException("Fuel capacity too large: " +
                                 std::to_string(capacity) + "L (max 1000)");
    }

    fuelCapacity = capacity;
}

void Vehicle::setCurrentFuelLevel(double level) {
    if (level < 0) {
        throw EquipmentException("Fuel level cannot be negative: " +
                                 std::to_string(level) + "L");
    }

    if (level > fuelCapacity * 1.1) { // допускаем 10% переполнение
        throw EquipmentException("Fuel level exceeds capacity: " +
                                 std::to_string(level) + "L > " +
                                 std::to_string(fuelCapacity) + "L");
    }

    currentFuelLevel = level;
}

void Vehicle::setFuelEfficiency(double efficiency) {
    if (efficiency <= 0) {
        throw EquipmentException("Fuel efficiency must be positive: " +
                                 std::to_string(efficiency) + " L/100km");
    }

    if (efficiency > 50.0) {
        throw EquipmentException("Fuel efficiency unrealistic: " +
                                 std::to_string(efficiency) + " L/100km (max 50)");
    }

    fuelEfficiency = efficiency;
}

void Vehicle::setMileage(double km) {
    if (km < 0) {
        throw EquipmentException("Mileage cannot be negative: " + std::to_string(km) + " km");
    }

    if (km > 1000000.0) {
        throw EquipmentException("Mileage unrealistic: " +
                                 std::to_string(km) + " km (max 1,000,000)");
    }

    mileage = km;
}

void Vehicle::setLicensePlate(const std::string& plate) {
    if (plate.empty()) {
        throw EquipmentException("License plate cannot be empty");
    }

    licensePlate = plate;
}

void Vehicle::setHasInsurance(bool insured) {
    if (!insured && mileage > 0) {
        throw EquipmentException("Cannot remove insurance from vehicle with mileage");
    }

    hasInsurance = insured;
}