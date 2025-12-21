#ifndef PLANTEXCEPTIONS_H
#define PLANTEXCEPTIONS_H

#include <stdexcept>
#include <string>
#include <vector>

// Базовый класс для исключений растений
class PlantException : public std::runtime_error {
public:
    explicit PlantException(const std::string& message)
            : std::runtime_error(message) {}
};

// Исключение для проблем с ростом растений
class GrowthException : public PlantException {
private:
    std::string plantName;
    std::string plantType;
    double currentHeight;
    double expectedHeight;

public:
    GrowthException(const std::string& message,
                    const std::string& plantName,
                    const std::string& plantType,
                    double currentHeight,
                    double expectedHeight)
            : PlantException(message), plantName(plantName), plantType(plantType),
              currentHeight(currentHeight), expectedHeight(expectedHeight) {}

    std::string getPlantName() const { return plantName; }
    std::string getPlantType() const { return plantType; }
    double getCurrentHeight() const { return currentHeight; }
    double getExpectedHeight() const { return expectedHeight; }
    double getGrowthDeficit() const { return expectedHeight - currentHeight; }

    virtual std::string getFullMessage() const {
        return "Growth Exception [" + plantType + " - " + plantName +
               "]: Expected height: " + std::to_string(expectedHeight) +
               "m, Actual: " + std::to_string(currentHeight) + "m - " + what();
    }
};

// Исключение для проблем с поливом
class WateringException : public PlantException {
private:
    std::string plantName;
    std::string plantType;
    double currentWaterLevel;
    double requiredWaterLevel;
    std::string wateringIssue;

public:
    WateringException(const std::string& message,
                      const std::string& plantName,
                      const std::string& plantType,
                      double currentWaterLevel,
                      double requiredWaterLevel,
                      const std::string& wateringIssue)
            : PlantException(message), plantName(plantName), plantType(plantType),
              currentWaterLevel(currentWaterLevel), requiredWaterLevel(requiredWaterLevel),
              wateringIssue(wateringIssue) {}

    std::string getPlantName() const { return plantName; }
    std::string getPlantType() const { return plantType; }
    double getCurrentWaterLevel() const { return currentWaterLevel; }
    double getRequiredWaterLevel() const { return requiredWaterLevel; }
    std::string getWateringIssue() const { return wateringIssue; }
    double getWaterDeficit() const { return requiredWaterLevel - currentWaterLevel; }

    virtual std::string getFullMessage() const {
        return "Watering Exception [" + plantType + " - " + plantName +
               "]: Required: " + std::to_string(requiredWaterLevel) +
               "%, Actual: " + std::to_string(currentWaterLevel) +
               "%. Issue: " + wateringIssue + " - " + what();
    }
};

// Исключение для проблем со сбором урожая
class HarvestException : public PlantException {
private:
    std::string plantName;
    std::string plantType;
    double expectedYield;
    double actualYield;
    std::string harvestIssue;

public:
    HarvestException(const std::string& message,
                     const std::string& plantName,
                     const std::string& plantType,
                     double expectedYield,
                     double actualYield,
                     const std::string& harvestIssue)
            : PlantException(message), plantName(plantName), plantType(plantType),
              expectedYield(expectedYield), actualYield(actualYield),
              harvestIssue(harvestIssue) {}

    std::string getPlantName() const { return plantName; }
    std::string getPlantType() const { return plantType; }
    double getExpectedYield() const { return expectedYield; }
    double getActualYield() const { return actualYield; }
    std::string getHarvestIssue() const { return harvestIssue; }
    double getYieldLoss() const { return expectedYield - actualYield; }
    double getYieldLossPercentage() const {
        return expectedYield > 0 ? (getYieldLoss() / expectedYield) * 100.0 : 0.0;
    }

    virtual std::string getFullMessage() const {
        return "Harvest Exception [" + plantType + " - " + plantName +
               "]: Expected: " + std::to_string(expectedYield) +
               "kg, Actual: " + std::to_string(actualYield) +
               "kg, Loss: " + std::to_string(getYieldLossPercentage()) +
               "%. Issue: " + harvestIssue + " - " + what();
    }
};

// Исключение для болезней растений
class PlantDiseaseException : public PlantException {
private:
    std::string plantName;
    std::string plantType;
    std::string diseaseName;
    int severity; // 1-10
    std::vector<std::string> affectedParts;

public:
    PlantDiseaseException(const std::string& message,
                          const std::string& plantName,
                          const std::string& plantType,
                          const std::string& diseaseName,
                          int severity,
                          const std::vector<std::string>& affectedParts = {})
            : PlantException(message), plantName(plantName), plantType(plantType),
              diseaseName(diseaseName), severity(severity), affectedParts(affectedParts) {}

    std::string getPlantName() const { return plantName; }
    std::string getPlantType() const { return plantType; }
    std::string getDiseaseName() const { return diseaseName; }
    int getSeverity() const { return severity; }
    std::vector<std::string> getAffectedParts() const { return affectedParts; }

    virtual std::string getFullMessage() const {
        std::string message = "Plant Disease Exception [" + plantType + " - " + plantName +
                              "]: Disease: " + diseaseName + ", Severity: " +
                              std::to_string(severity);

        if (!affectedParts.empty()) {
            message += ", Affected parts: ";
            for (size_t i = 0; i < affectedParts.size(); ++i) {
                message += affectedParts[i];
                if (i < affectedParts.size() - 1) message += ", ";
            }
        }

        return message + " - " + what();
    }
};

#endif // PLANTEXCEPTIONS_H