#include "Plow.h"
#include "EquipmentExceptions.h"
#include <iostream>
#include <string>

Plow::Plow(const std::string& name, const std::string& manufacturer, int year,
           int bladeCount, double workingWidth)
        : Equipment(name, manufacturer, year), bladeCount(bladeCount),
          workingWidth(workingWidth), maxWorkingDepth(0.3),
          plowType("Moldboard"), isReversible(true), wearLevel(0.0) {

    // Проверка специфичных для плуга параметров
    if (bladeCount <= 0) {
        throw EquipmentException("Plow blade count must be positive: " +
                                 std::to_string(bladeCount) + " for " + name);
    }

    if (bladeCount > 12) {
        throw EquipmentException("Plow blade count too high: " +
                                 std::to_string(bladeCount) + " (max 12) for " + name);
    }

    if (workingWidth <= 0) {
        throw EquipmentException("Plow working width must be positive: " +
                                 std::to_string(workingWidth) + " meters for " + name);
    }

    if (workingWidth > 10.0) {
        throw EquipmentException("Plow working width too large: " +
                                 std::to_string(workingWidth) + " meters (max 10) for " + name);
    }

    purchasePrice = 5000.0 + (bladeCount * 500.0);
    currentValue = purchasePrice;
    maintenanceInterval = 20; // более частое обслуживание
    serialNumber = "PL" + serialNumber;
}

void Plow::adjustDepth(double depth) {
    if (!isOperational) {
        throw EquipmentException("Cannot adjust depth on non-operational plow: " + name);
    }

    if (depth <= 0) {
        throw EquipmentException("Plow depth must be positive: " +
                                 std::to_string(depth) + " meters for " + name);
    }

    if (depth > maxWorkingDepth) {
        throw EquipmentException("Plow depth " + std::to_string(depth) +
                                 " meters exceeds maximum of " +
                                 std::to_string(maxWorkingDepth) + " meters for " + name);
    }

    std::cout << name << " depth adjusted to " << depth << " meters." << std::endl;

    // Изменение глубины увеличивает износ
    wearLevel += 1.0;

    // Проверка на чрезмерный износ после регулировки
    if (wearLevel > 80.0) {
        throw EquipmentException("Plow wear level too high (" +
                                 std::to_string(wearLevel) + "%) to safely adjust depth for " + name);
    }
}

void Plow::sharpenBlades() {
    if (!isOperational) {
        throw EquipmentException("Cannot sharpen blades on non-operational plow: " + name);
    }

    if (wearLevel > 90.0) {
        throw MissingPartsException(name, "Blade replacement set", 7);
    }

    if (wearLevel > 20.0) {
        wearLevel -= 20.0;
        if (wearLevel < 0) wearLevel = 0;
        std::cout << "Blades of " << name << " have been sharpened." << std::endl;
        std::cout << "Wear level reduced from " << (wearLevel + 20.0)
                  << "% to " << wearLevel << "%" << std::endl;
    } else {
        throw EquipmentException("Blades don't need sharpening yet. Wear level: " +
                                 std::to_string(wearLevel) + "% for " + name);
    }
}

double Plow::calculateAreaPerHour(double speed) const {
    if (speed <= 0) {
        throw EquipmentException("Plowing speed must be positive: " +
                                 std::to_string(speed) + " km/h for " + name);
    }

    if (speed > 15.0) {
        throw EquipmentException("Plowing speed too high: " +
                                 std::to_string(speed) + " km/h (max 15) for " + name);
    }

    // площадь в час = ширина * скорость
    return workingWidth * speed * 10000.0; // в квадратных метрах
}

bool Plow::checkBladeWear() const {
    return wearLevel > 50.0;
}

void Plow::replaceBlades() {
    if (!checkBladeWear()) {
        throw EquipmentException("Blades don't need replacement yet. Wear level: " +
                                 std::to_string(wearLevel) + "% for " + name);
    }

    if (!isOperational) {
        throw EquipmentException("Cannot replace blades on non-operational plow: " + name);
    }

    // Проверка наличия запчастей
    double missingPartChance = 0.2;
    if (missingPartChance > 0.15) {
        throw MissingPartsException(name, "Replacement blades", 10);
    }

    wearLevel = 0.0;
    currentValue *= 0.9; // замена лезвий немного уменьшает общую стоимость
    std::cout << "Blades replaced on " << name << ". Wear level reset to 0%." << std::endl;
}

double Plow::calculateRequiredTraction() const {
    if (!isOperational) {
        throw EquipmentException("Cannot calculate traction for non-operational plow: " + name);
    }

    if (wearLevel > 70.0) {
        throw EquipmentException("Plow wear level too high (" +
                                 std::to_string(wearLevel) + "%) to calculate traction for " + name);
    }

    // Требуемое усилие тяги зависит от ширины, глубины и количества лемехов
    double baseTraction = workingWidth * maxWorkingDepth * 10000.0; // Н/м²
    return baseTraction * bladeCount * 1.5; // коэффициент безопасности
}

bool Plow::isProperlyAdjusted() const {
    return wearLevel < 70.0 && isOperational;
}

double Plow::calculateFuelConsumption(double area, double soilHardness) const {
    if (area <= 0) {
        throw EquipmentException("Plowing area must be positive: " +
                                 std::to_string(area) + " sq.m. for " + name);
    }

    if (soilHardness < 0 || soilHardness > 10.0) {
        throw EquipmentException("Soil hardness must be between 0-10: " +
                                 std::to_string(soilHardness) + " for " + name);
    }

    if (!isOperational) {
        throw EquipmentException("Cannot calculate fuel consumption for non-operational plow: " + name);
    }

    if (wearLevel > 60.0) {
        throw EquipmentException("Plow wear level too high (" +
                                 std::to_string(wearLevel) + "%) to calculate accurate fuel consumption for " + name);
    }

    // Базовый расход: 5 литров на гектар
    double baseConsumption = (area / 10000.0) * 5.0;

    // Поправки
    double bladeFactor = bladeCount * 0.1;
    double wearFactor = wearLevel * 0.01;
    double soilFactor = soilHardness * 0.5;

    return baseConsumption * (1 + bladeFactor + wearFactor + soilFactor);
}

void Plow::use() {
    if (!isOperational) {
        throw EquipmentBreakdownException(name, "Not operational",
                                          "Unknown - equipment broken");
    }

    if (wearLevel > 85.0) {
        throw EquipmentBreakdownException(name, "Excessive blade wear",
                                          "Regular maintenance");
    }

    if (needsMaintenance()) {
        std::cout << "Warning: " << name << " needs maintenance!" << std::endl;

        // Использование плуга, требующего обслуживания, может привести к поломке
        if (daysSinceMaintenance > maintenanceInterval * 2) {
            isOperational = false;
            wearLevel += 10.0; // дополнительный износ при поломке
            throw EquipmentBreakdownException(name, "Overdue maintenance failure",
                                              "Unknown - maintenance overdue");
        }
    }

    // Использование плуга - вспашка
    wearLevel += 5.0; // использование увеличивает износ

    // Проверка на ускоренный износ при высоком уровне износа
    if (wearLevel > 60.0) {
        wearLevel += 2.0; // дополнительный износ
    }

    daysSinceMaintenance++;

    std::cout << name << " used for plowing." << std::endl;
    std::cout << "Wear level increased to " << wearLevel << "%" << std::endl;

    try {
        std::cout << "Area per hour at 5 km/h: "
                  << calculateAreaPerHour(5.0) << " sq.m." << std::endl;
    } catch (const EquipmentException& e) {
        std::cout << "Area calculation error: " << e.what() << std::endl;
    }

    if (checkBladeWear()) {
        std::cout << "Warning: Blades need sharpening or replacement!" << std::endl;

        if (wearLevel > 75.0) {
            throw EquipmentException("Critical blade wear (" +
                                     std::to_string(wearLevel) + "%) detected on " + name);
        }
    }

    // Уменьшение стоимости из-за износа
    currentValue *= (1 - wearLevel * 0.001);

    // Автоматическая поломка при критическом износе
    if (wearLevel > 95.0) {
        isOperational = false;
        throw EquipmentBreakdownException(name, "Critical blade wear failure",
                                          "Recent maintenance");
    }
}

void Plow::performMaintenance() {
    // Вызов базового метода обслуживания с обработкой исключений
    try {
        Equipment::performMaintenance();
    } catch (const EquipmentException& e) {
        throw EquipmentException("Failed to perform base maintenance on plow " + name +
                                 ": " + e.what());
    }

    // Специфичное обслуживание плуга
    std::cout << "Performing plow-specific maintenance:" << std::endl;

    try {
        if (wearLevel > 30.0) {
            sharpenBlades();
        } else {
            std::cout << "Blades are in good condition. No sharpening needed." << std::endl;
        }
    } catch (const MissingPartsException& e) {
        throw e; // Пробрасываем исключение выше
    } catch (const EquipmentException& e) {
        std::cout << "Blade sharpening skipped: " << e.what() << std::endl;
    }

    std::cout << "Checking all bolts and connections..." << std::endl;
    std::cout << "Lubricating moving parts..." << std::endl;

    // После обслуживания износ немного уменьшается
    wearLevel *= 0.9;

    // Проверка на необходимость замены лезвий после обслуживания
    if (wearLevel > 65.0 && isOperational) {
        throw EquipmentException("Plow " + name + " still has high wear level (" +
                                 std::to_string(wearLevel) + "%) after maintenance - consider blade replacement");
    }
}

void Plow::displayInfo() const {
    Equipment::displayInfo();
    std::cout << "=== Plow Details ===" << std::endl;
    std::cout << "Blade count: " << bladeCount << std::endl;
    std::cout << "Working width: " << workingWidth << " meters" << std::endl;
    std::cout << "Max working depth: " << maxWorkingDepth << " meters" << std::endl;
    std::cout << "Plow type: " << plowType << std::endl;
    std::cout << "Reversible: " << (isReversible ? "Yes" : "No") << std::endl;
    std::cout << "Wear level: " << wearLevel << "%" << std::endl;
    std::cout << "Blades need attention: " << (checkBladeWear() ? "Yes" : "No") << std::endl;
    std::cout << "Properly adjusted: " << (isProperlyAdjusted() ? "Yes" : "No") << std::endl;

    try {
        std::cout << "Required traction: " << calculateRequiredTraction() << " N" << std::endl;
    } catch (const EquipmentException& e) {
        std::cout << "Required traction: Cannot calculate - " << e.what() << std::endl;
    }

    try {
        std::cout << "Area per hour (5 km/h): " << calculateAreaPerHour(5.0)
                  << " sq.m." << std::endl;
    } catch (const EquipmentException& e) {
        std::cout << "Area per hour: Cannot calculate - " << e.what() << std::endl;
    }
}

double Plow::calculateMaintenanceCost() const {
    if (!isOperational) {
        throw EquipmentException("Cannot calculate maintenance cost for non-operational plow: " + name);
    }

    try {
        double baseCost = Equipment::calculateMaintenanceCost();
        double bladeCost = bladeCount * 25.0;
        double wearCost = wearLevel * 2.0;

        return baseCost + bladeCost + wearCost;
    } catch (const EquipmentException& e) {
        throw EquipmentException("Failed to calculate plow maintenance cost: " +
                                 std::string(e.what()));
    }
}

int Plow::getBladeCount() const { return bladeCount; }
double Plow::getWorkingWidth() const { return workingWidth; }
double Plow::getMaxWorkingDepth() const { return maxWorkingDepth; }
std::string Plow::getPlowType() const { return plowType; }
bool Plow::getIsReversible() const { return isReversible; }
double Plow::getWearLevel() const { return wearLevel; }

void Plow::setBladeCount(int count) {
    if (count <= 0) {
        throw EquipmentException("Plow blade count must be positive: " +
                                 std::to_string(count));
    }

    if (count > 12) {
        throw EquipmentException("Plow blade count too high: " +
                                 std::to_string(count) + " (max 12)");
    }

    bladeCount = count;
}

void Plow::setWorkingWidth(double width) {
    if (width <= 0) {
        throw EquipmentException("Plow working width must be positive: " +
                                 std::to_string(width) + " meters");
    }

    if (width > 10.0) {
        throw EquipmentException("Plow working width too large: " +
                                 std::to_string(width) + " meters (max 10)");
    }

    workingWidth = width;
}

void Plow::setMaxWorkingDepth(double depth) {
    if (depth <= 0) {
        throw EquipmentException("Plow max working depth must be positive: " +
                                 std::to_string(depth) + " meters");
    }

    if (depth > 1.0) {
        throw EquipmentException("Plow max working depth too deep: " +
                                 std::to_string(depth) + " meters (max 1.0)");
    }

    maxWorkingDepth = depth;
}

void Plow::setPlowType(const std::string& type) {
    if (type.empty()) {
        throw EquipmentException("Plow type cannot be empty");
    }

    plowType = type;
}

void Plow::setIsReversible(bool reversible) { isReversible = reversible; }

void Plow::setWearLevel(double wear) {
    if (wear < 0 || wear > 100.0) {
        throw EquipmentException("Plow wear level must be between 0-100%: " +
                                 std::to_string(wear) + "%");
    }

    wearLevel = wear;
}