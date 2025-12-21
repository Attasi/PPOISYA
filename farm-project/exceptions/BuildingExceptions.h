#ifndef BUILDING_EXCEPTIONS_H
#define BUILDING_EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Базовое исключение для построек
class BuildingException : public std::runtime_error {
public:
    explicit BuildingException(const std::string& message)
            : std::runtime_error("Building Error: " + message) {}
};

// Исключение для аварийного состояния постройки
class BuildingSafetyException : public BuildingException {
private:
    std::string buildingName;
    std::string safetyIssue;
    int dangerLevel; // 1-10
public:
    BuildingSafetyException(const std::string& buildingName, const std::string& safetyIssue,
                            int dangerLevel)
            : BuildingException(buildingName + " safety issue: " + safetyIssue +
                                " (danger level: " + std::to_string(dangerLevel) + "/10)"),
              buildingName(buildingName), safetyIssue(safetyIssue), dangerLevel(dangerLevel) {}

    std::string getBuildingName() const { return buildingName; }
    std::string getSafetyIssue() const { return safetyIssue; }
    int getDangerLevel() const { return dangerLevel; }
};

// Исключение для переполнения постройки
class BuildingCapacityException : public BuildingException {
private:
    std::string buildingName;
    double capacity;
    double currentOccupancy;
public:
    BuildingCapacityException(const std::string& buildingName, double capacity, double currentOccupancy)
            : BuildingException(buildingName + " is over capacity: " +
                                std::to_string(currentOccupancy) + "/" +
                                std::to_string(capacity)),
              buildingName(buildingName), capacity(capacity), currentOccupancy(currentOccupancy) {}

    std::string getBuildingName() const { return buildingName; }
    double getCapacity() const { return capacity; }
    double getCurrentOccupancy() const { return currentOccupancy; }
};

#endif // BUILDING_EXCEPTIONS_H