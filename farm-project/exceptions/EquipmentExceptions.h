#ifndef EQUIPMENT_EXCEPTIONS_H
#define EQUIPMENT_EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Базовое исключение для оборудования
class EquipmentException : public std::runtime_error {
public:
    explicit EquipmentException(const std::string& message)
            : std::runtime_error("Equipment Error: " + message) {}
};

// Исключение для поломки оборудования
class EquipmentBreakdownException : public EquipmentException {
private:
    std::string equipmentName;
    std::string failureType;
    std::string lastMaintenanceDate;
public:
    EquipmentBreakdownException(const std::string& equipmentName, const std::string& failureType,
                                const std::string& lastMaintenanceDate)
            : EquipmentException(equipmentName + " has broken down: " + failureType +
                                 " (last maintenance: " + lastMaintenanceDate + ")"),
              equipmentName(equipmentName), failureType(failureType),
              lastMaintenanceDate(lastMaintenanceDate) {}

    std::string getEquipmentName() const { return equipmentName; }
    std::string getFailureType() const { return failureType; }
    std::string getLastMaintenanceDate() const { return lastMaintenanceDate; }
};

// Исключение для отсутствия запчастей
class MissingPartsException : public EquipmentException {
private:
    std::string equipmentName;
    std::string missingPart;
    int daysWaiting;
public:
    MissingPartsException(const std::string& equipmentName, const std::string& missingPart,
                          int daysWaiting)
            : EquipmentException(equipmentName + " needs part: " + missingPart +
                                 " (waiting: " + std::to_string(daysWaiting) + " days)"),
              equipmentName(equipmentName), missingPart(missingPart), daysWaiting(daysWaiting) {}

    std::string getEquipmentName() const { return equipmentName; }
    std::string getMissingPart() const { return missingPart; }
    int getDaysWaiting() const { return daysWaiting; }
};

#endif // EQUIPMENT_EXCEPTIONS_H