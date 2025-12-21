#include "Tractor.h"
#include "EquipmentExceptions.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

Tractor::Tractor(const std::string& name, const std::string& manufacturer, int year,
                 double enginePower, bool hasFrontLoader)
        : Vehicle(name, manufacturer, year, "Diesel", 100.0),
          enginePower(enginePower), hasFrontLoader(hasFrontLoader),
          hasBackhoe(false), hydraulicSystemPressure(200) {

    // Проверка специфичных для трактора параметров
    if (enginePower <= 0) {
        throw EquipmentException("Tractor engine power must be positive: " +
                                 std::to_string(enginePower) + " HP for " + name);
    }

    if (enginePower > 500.0) {
        throw EquipmentException("Tractor engine power too high: " +
                                 std::to_string(enginePower) + " HP (max 500) for " + name);
    }

    // Проверка совместимости фронтального погрузчика с мощностью
    if (hasFrontLoader && enginePower < 50.0) {
        throw EquipmentException(std::string("Tractor ") + name +
                                 " has insufficient power (" + std::to_string(enginePower) +
                                 " HP) for front loader (minimum 50 HP)");
    }

    // Проверка года выпуска для мощных тракторов
    if (enginePower > 300.0 && year < 2005) {
        throw EquipmentException(std::string("High-power tractor (") + std::to_string(enginePower) +
                                 " HP) from " + std::to_string(year) +
                                 " may have reliability issues for " + name);
    }

    purchasePrice = 80000.0 + (enginePower * 100.0);
    currentValue = purchasePrice;
    fuelEfficiency = 15.0 + (enginePower / 50.0); // более мощный - больше расход
    licensePlate = "TR" + licensePlate;
}

void Tractor::attachImplement(const std::string& implement) {
    if (!isOperational) {
        throw EquipmentException("Cannot attach implement to non-operational tractor: " + name);
    }

    if (implement.empty()) {
        throw EquipmentException("Implement name cannot be empty for tractor " + name);
    }

    // Проверка на дублирование
    auto it = std::find(attachedImplements.begin(), attachedImplements.end(), implement);
    if (it != attachedImplements.end()) {
        throw EquipmentException(std::string("Implement ") + implement +
                                 " is already attached to tractor " + name);
    }

    if (!isImplementCompatible(implement)) {
        throw EquipmentException(std::string("Implement ") + implement +
                                 " is not compatible with tractor " + name);
    }

    // Проверка мощности для тяжелого оборудования
    if (implement.find("Heavy") != std::string::npos && enginePower < 100.0) {
        throw EquipmentException(std::string("Tractor ") + name +
                                 " has insufficient power (" + std::to_string(enginePower) +
                                 " HP) for heavy implement " + implement);
    }

    // Проверка давления в гидросистеме
    if (!checkHydraulicSystem() && implement.find("Hydraulic") != std::string::npos) {
        throw EquipmentException(std::string("Hydraulic system pressure issue (") +
                                 std::to_string(hydraulicSystemPressure) +
                                 " bar) - cannot attach hydraulic implement " +
                                 implement + " to tractor " + name);
    }

    // Проверка максимального количества навесного оборудования
    if (attachedImplements.size() >= 5) {
        throw EquipmentException("Tractor " + name +
                                 " cannot attach more than 5 implements");
    }

    attachedImplements.push_back(implement);
    std::cout << implement << " attached to " << name << std::endl;
}

void Tractor::detachImplement(const std::string& implement) {
    if (!isOperational) {
        throw EquipmentException("Cannot detach implement from non-operational tractor: " + name);
    }

    if (implement.empty()) {
        throw EquipmentException("Implement name cannot be empty for tractor " + name);
    }

    auto it = std::find(attachedImplements.begin(), attachedImplements.end(), implement);
    if (it == attachedImplements.end()) {
        throw EquipmentException(std::string("Implement ") + implement +
                                 " is not attached to tractor " + name);
    }

    // Проверка безопасности отцепления
    if (hydraulicSystemPressure > 150) {
        throw EquipmentException(std::string("Hydraulic pressure too high (") +
                                 std::to_string(hydraulicSystemPressure) +
                                 " bar) to safely detach implement " + implement +
                                 " from tractor " + name);
    }

    attachedImplements.erase(it);
    std::cout << implement << " detached from " << name << std::endl;
}

void Tractor::plowField(double area) {
    if (!isOperational) {
        throw EquipmentBreakdownException(name, "Not operational",
                                          "Unknown - tractor broken");
    }

    if (!hasInsurance) {
        throw EquipmentException("Cannot operate uninsured tractor: " + name);
    }

    if (area <= 0) {
        throw EquipmentException("Plowing area must be positive: " +
                                 std::to_string(area) + " sq.m. for tractor " + name);
    }

    if (area > 1000000.0) {
        throw EquipmentException("Plowing area too large: " +
                                 std::to_string(area) + " sq.m. (max 1,000,000) for tractor " + name);
    }

    if (!checkHydraulicSystem()) {
        throw EquipmentException(std::string("Hydraulic system not functioning properly (") +
                                 std::to_string(hydraulicSystemPressure) +
                                 " bar) - cannot plow with tractor " + name);
    }

    // Проверяем, прикреплен ли плуг
    bool hasPlow = false;
    std::string plowType;
    for (const auto& implement : attachedImplements) {
        if (implement.find("Plow") != std::string::npos) {
            hasPlow = true;
            plowType = implement;
            break;
        }
    }

    if (!hasPlow) {
        throw EquipmentException(std::string("No plow attached to tractor ") + name +
                                 ". Attach a plow first.");
    }

    // Проверка мощности для площади
    double requiredPower = area / 1000.0;
    if (enginePower < requiredPower) {
        throw EquipmentException(std::string("Tractor ") + name +
                                 " has insufficient power (" + std::to_string(enginePower) +
                                 " HP) for plowing " + std::to_string(area) +
                                 " sq.m. (needs at least " + std::to_string(requiredPower) + " HP)");
    }

    double fuelNeeded = (area / 10000.0) * 5.0; // 5 литров на гектар
    double timeNeeded = area / (enginePower * 0.1); // час на 0.1*мощность гектар

    if (currentFuelLevel < fuelNeeded) {
        double missingFuel = fuelNeeded - currentFuelLevel;
        throw EquipmentException(std::string("Not enough fuel to plow ") +
                                 std::to_string(area) + " sq.m. with tractor " + name +
                                 ". Need " + std::to_string(missingFuel) + "L more.");
    }

    if (needsMaintenance()) {
        std::cout << "Warning: " << name << " needs maintenance!" << std::endl;

        // Вспашка трактором, требующим обслуживания, может привести к поломке
        if (daysSinceMaintenance > maintenanceInterval * 2) {
            isOperational = false;
            throw EquipmentBreakdownException(name, "Overdue maintenance failure",
                                              "Unknown - maintenance overdue");
        }
    }

    if (needsOilChange()) {
        throw EquipmentException(std::string("Oil change required before plowing with tractor ") + name);
    }

    // Выполнение вспашки
    currentFuelLevel -= fuelNeeded;
    mileage += area * 0.01; // примерный пробег
    daysSinceMaintenance++;

    std::cout << name << " plowed " << area << " square meters with " << plowType << "." << std::endl;
    std::cout << "Fuel used: " << fuelNeeded << "L" << std::endl;
    std::cout << "Time required: " << timeNeeded << " hours" << std::endl;

    try {
        std::cout << "Productivity: " << calculateProductivity(timeNeeded)
                  << " units/hour" << std::endl;
    } catch (const EquipmentException& e) {
        std::cout << "Productivity calculation error: " << e.what() << std::endl;
    }

    // Износ из-за работы
    double wear = area * 0.000001;
    currentValue *= (1 - wear);
    hydraulicSystemPressure -= static_cast<int>(wear * 100.0);

    // Автоматическая проверка на перегрев
    if (timeNeeded > 4.0) {
        double overheatingChance = (timeNeeded - 4.0) / 2.0 * 0.1;
        if (overheatingChance > 0.05) {
            throw EquipmentException(std::string("Tractor ") + name +
                                     " may overheat during prolonged plowing (estimated time: " +
                                     std::to_string(timeNeeded) + " hours)");
        }
    }
}

void Tractor::transportLoad(double weight, double distance) {
    if (!isOperational) {
        throw EquipmentBreakdownException(name, "Not operational",
                                          "Unknown - tractor broken");
    }

    if (!hasInsurance) {
        throw EquipmentException("Cannot transport with uninsured tractor: " + name);
    }

    if (weight <= 0) {
        throw EquipmentException("Transport weight must be positive: " +
                                 std::to_string(weight) + " kg for tractor " + name);
    }

    if (weight > 10000.0) {
        throw EquipmentException("Transport weight too high: " +
                                 std::to_string(weight) + " kg (max 10,000) for tractor " + name);
    }

    if (distance <= 0) {
        throw EquipmentException("Transport distance must be positive: " +
                                 std::to_string(distance) + " km for tractor " + name);
    }

    if (distance > 500.0) {
        throw EquipmentException("Transport distance too long: " +
                                 std::to_string(distance) + " km (max 500) for tractor " + name);
    }

    if (!checkHydraulicSystem() && hasFrontLoader) {
        throw EquipmentException(std::string("Front loader hydraulic system not functioning - ") +
                                 "cannot transport load with tractor " + name);
    }

    // Проверка грузоподъемности
    double maxLoad = enginePower * 20.0; // 20 кг на л.с.
    if (weight > maxLoad) {
        throw EquipmentException(std::string("Tractor ") + name +
                                 " cannot transport " + std::to_string(weight) +
                                 " kg (max load: " + std::to_string(maxLoad) + " kg)");
    }

    double fuelNeeded = (distance / 100.0) * fuelEfficiency * (1 + weight / 1000.0);

    if (currentFuelLevel < fuelNeeded) {
        double missingFuel = fuelNeeded - currentFuelLevel;
        throw EquipmentException(std::string("Not enough fuel to transport ") +
                                 std::to_string(weight) + " kg over " +
                                 std::to_string(distance) + " km with tractor " + name +
                                 ". Need " + std::to_string(missingFuel) + "L more.");
    }

    // Выполнение транспортировки
    currentFuelLevel -= fuelNeeded;
    mileage += distance;
    daysSinceMaintenance++;

    std::cout << name << " transported " << weight << " kg over "
              << distance << " km." << std::endl;
    std::cout << "Fuel used: " << fuelNeeded << "L" << std::endl;
    std::cout << "Tractive effort required: " << calculateTractiveEffort()
              << " (available: " << (calculateTractiveEffort() * 0.8) << ")" << std::endl;

    // Автоматическая проверка на перегруз
    if (weight > maxLoad * 0.8) {
        std::cout << "Warning: Heavy load may cause excessive wear on tractor " << name << std::endl;

        double damageChance = (weight / maxLoad - 0.8) * 10.0;
        if (damageChance > 0.3) {
            hydraulicSystemPressure -= 10;
            throw EquipmentException(std::string("Heavy load caused hydraulic system damage on tractor ") + name);
        }
    }
}

bool Tractor::checkHydraulicSystem() const {
    return hydraulicSystemPressure >= 180 && hydraulicSystemPressure <= 220;
}

double Tractor::calculateTractiveEffort() const {
    if (!isOperational) {
        throw EquipmentException("Cannot calculate tractive effort for non-operational tractor: " + name);
    }

    if (enginePower <= 0) {
        throw EquipmentException("Invalid engine power for tractive effort calculation: " +
                                 std::to_string(enginePower) + " HP for tractor " + name);
    }

    return enginePower * 30.0; // приблизительная формула
}

bool Tractor::isImplementCompatible(const std::string& implement) const {
    if (implement.empty()) {
        throw EquipmentException("Implement name cannot be empty for compatibility check");
    }

    // Проверка совместимости оборудования
    std::vector<std::string> compatibleImplements = {
            "Plow", "Seeder", "Harvester", "Trailer", "Sprayer", "Mower",
            "Cultivator", "Disc", "Balers", "Loader", "Forklift"
    };

    for (const auto& compatible : compatibleImplements) {
        if (implement.find(compatible) != std::string::npos) {
            return true;
        }
    }

    return false;
}

double Tractor::calculateProductivity(double hours) const {
    if (hours <= 0) {
        throw EquipmentException("Productivity calculation hours must be positive: " +
                                 std::to_string(hours) + " hours for tractor " + name);
    }

    if (hours > 24.0) {
        throw EquipmentException("Productivity calculation hours unrealistic: " +
                                 std::to_string(hours) + " hours (max 24) for tractor " + name);
    }

    if (!isOperational) {
        throw EquipmentException("Cannot calculate productivity for non-operational tractor: " + name);
    }

    double baseProductivity = enginePower * 0.5; // 0.5 единиц на л.с.
    double implementBonus = attachedImplements.size() * 10.0;

    return (baseProductivity + implementBonus) * hours;
}

void Tractor::use() {
    if (!checkHydraulicSystem()) {
        throw EquipmentException(std::string("Hydraulic system not ready for use on tractor ") + name);
    }

    try {
        // Использование трактора - вспашка небольшого участка
        plowField(1000.0);
    } catch (const EquipmentException& e) {
        throw EquipmentException(std::string("Failed to use tractor ") + name + ": " + e.what());
    }
}

void Tractor::performMaintenance() {
    if (!hasInsurance) {
        throw EquipmentException("Tractor " + name +
                                 " requires valid insurance for maintenance");
    }

    if (hydraulicSystemPressure > 250) {
        throw EquipmentException(std::string("Dangerous hydraulic pressure (") +
                                 std::to_string(hydraulicSystemPressure) +
                                 " bar) - cannot perform maintenance on tractor " + name);
    }

    // Вызов базового метода обслуживания с обработкой исключений
    try {
        Vehicle::performMaintenance();
    } catch (const EquipmentException& e) {
        throw EquipmentException(std::string("Failed to perform base maintenance on tractor ") + name +
                                 ": " + e.what());
    }

    // Специфичное обслуживание трактора
    std::cout << "Performing tractor-specific maintenance:" << std::endl;

    try {
        std::cout << "1. Checking hydraulic system: "
                  << (checkHydraulicSystem() ? "OK" : "Needs adjustment") << std::endl;
    } catch (const EquipmentException& e) {
        std::cout << "1. Hydraulic system check failed: " << e.what() << std::endl;
    }

    std::cout << "2. Inspecting attached implements" << std::endl;

    // Проверка наличия запчастей для обслуживания навесного оборудования
    if (!attachedImplements.empty()) {
        double missingPartChance = 0.15;
        if (missingPartChance > 0.1) {
            throw MissingPartsException(name, "Implement maintenance kit", 7);
        }
    }

    std::cout << "3. Checking PTO shaft" << std::endl;

    // Проверка на наличие специфичных запчастей для старых тракторов
    if (yearOfManufacture < 2000 && enginePower > 150.0) {
        throw MissingPartsException(name, "Vintage tractor parts", 30);
    }

    if (!checkHydraulicSystem()) {
        // Проверка наличия гидравлического масла
        double missingOilChance = 0.1;
        if (missingOilChance > 0.05) {
            throw MissingPartsException(name, "Hydraulic oil", 2);
        }

        hydraulicSystemPressure = 200; // сброс до нормального давления
        std::cout << "Hydraulic system adjusted to 200 bar." << std::endl;
    }

    // Специальная проверка для фронтального погрузчика
    if (hasFrontLoader) {
        std::cout << "4. Servicing front loader" << std::endl;

        if (enginePower < 80.0) {
            throw EquipmentException(std::string("Tractor ") + name +
                                     " may not have adequate power for front loader maintenance");
        }
    }
}

void Tractor::displayInfo() const {
    Vehicle::displayInfo();
    std::cout << "=== Tractor Details ===" << std::endl;
    std::cout << "Engine power: " << enginePower << " HP" << std::endl;
    std::cout << "Front loader: " << (hasFrontLoader ? "Yes" : "No") << std::endl;
    std::cout << "Backhoe: " << (hasBackhoe ? "Yes" : "No") << std::endl;
    std::cout << "Hydraulic pressure: " << hydraulicSystemPressure << " bar" << std::endl;

    try {
        std::cout << "Tractive effort: " << calculateTractiveEffort() << " kg" << std::endl;
    } catch (const EquipmentException& e) {
        std::cout << "Tractive effort: Cannot calculate - " << e.what() << std::endl;
    }

    std::cout << "Hydraulic system OK: " << (checkHydraulicSystem() ? "Yes" : "No") << std::endl;

    if (!attachedImplements.empty()) {
        std::cout << "Attached implements: ";
        for (size_t i = 0; i < attachedImplements.size(); ++i) {
            std::cout << attachedImplements[i];
            if (i < attachedImplements.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }

    // Дополнительные предупреждения
    if (enginePower > 300.0 && yearOfManufacture > 2010) {
        std::cout << "Note: High-power modern tractor - may require specialized service." << std::endl;
    }

    if (hasFrontLoader && !checkHydraulicSystem()) {
        std::cout << "Warning: Front loader operation may be unsafe with current hydraulic pressure." << std::endl;
    }
}

double Tractor::calculateMaintenanceCost() const {
    if (!isOperational) {
        throw EquipmentException("Cannot calculate maintenance cost for non-operational tractor: " + name);
    }

    if (!hasInsurance) {
        throw EquipmentException("Uninsured tractor " + name +
                                 " has higher maintenance costs");
    }

    try {
        double vehicleCost = Vehicle::calculateMaintenanceCost();
        double tractorPremium = enginePower * 2.0; // 2 рубля за л.с.
        double implementCost = attachedImplements.size() * 50.0;

        // Дополнительная стоимость для гидравлической системы
        double hydraulicCost = 0.0;
        if (!checkHydraulicSystem()) {
            hydraulicCost = 500.0;
        }

        // Дополнительная стоимость для фронтального погрузчика
        double loaderCost = hasFrontLoader ? 300.0 : 0.0;

        // Дополнительная стоимость для старых тракторов
        if ((2024 - yearOfManufacture) > 15) {
            tractorPremium *= 1.5;
        }

        return vehicleCost + tractorPremium + implementCost + hydraulicCost + loaderCost;
    } catch (const EquipmentException& e) {
        throw EquipmentException(std::string("Failed to calculate tractor maintenance cost: ") +
                                 e.what());
    }
}

double Tractor::getEnginePower() const { return enginePower; }
bool Tractor::getHasFrontLoader() const { return hasFrontLoader; }
bool Tractor::getHasBackhoe() const { return hasBackhoe; }
int Tractor::getHydraulicSystemPressure() const { return hydraulicSystemPressure; }
std::vector<std::string> Tractor::getAttachedImplements() const { return attachedImplements; }

void Tractor::setEnginePower(double power) {
    if (power <= 0) {
        throw EquipmentException("Tractor engine power must be positive: " +
                                 std::to_string(power) + " HP");
    }

    if (power > 500.0) {
        throw EquipmentException("Tractor engine power too high: " +
                                 std::to_string(power) + " HP (max 500)");
    }

    // Проверка совместимости с фронтальным погрузчиком
    if (hasFrontLoader && power < 50.0) {
        throw EquipmentException(std::string("Tractor has insufficient power (") +
                                 std::to_string(power) + " HP) for front loader (minimum 50 HP)");
    }

    enginePower = power;
}

void Tractor::setHasFrontLoader(bool hasLoader) {
    if (hasLoader && enginePower < 50.0) {
        throw EquipmentException(std::string("Cannot add front loader to tractor with insufficient power (") +
                                 std::to_string(enginePower) + " HP, minimum 50 HP)");
    }

    hasFrontLoader = hasLoader;
}

void Tractor::setHasBackhoe(bool hasBackhoe) {
    if (hasBackhoe && enginePower < 70.0) {
        throw EquipmentException(std::string("Cannot add backhoe to tractor with insufficient power (") +
                                 std::to_string(enginePower) + " HP, minimum 70 HP)");
    }

    this->hasBackhoe = hasBackhoe;
}

void Tractor::setHydraulicSystemPressure(int pressure) {
    if (pressure < 0) {
        throw EquipmentException("Hydraulic system pressure cannot be negative: " +
                                 std::to_string(pressure) + " bar");
    }

    if (pressure > 300) {
        throw EquipmentException("Hydraulic system pressure dangerously high: " +
                                 std::to_string(pressure) + " bar (max 300)");
    }

    hydraulicSystemPressure = pressure;
}