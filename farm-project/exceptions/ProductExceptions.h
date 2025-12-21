#ifndef PRODUCTEXCEPTIONS_H
#define PRODUCTEXCEPTIONS_H

#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

// Базовый класс для исключений продукции
class ProductException : public std::runtime_error {
private:
    std::string productName;
    std::string productType;
    double quantity;

public:
    ProductException(const std::string& message,
                     const std::string& productName,
                     const std::string& productType,
                     double quantity)
            : std::runtime_error(message),
              productName(productName),
              productType(productType),
              quantity(quantity) {}

    std::string getProductName() const { return productName; }
    std::string getProductType() const { return productType; }
    double getQuantity() const { return quantity; }

    virtual std::string getFullMessage() const {
        return "Product Exception [" + productType + " - " + productName +
               "]: " + std::to_string(quantity) + " units - " + what();
    }
};

// Исключение для проблем с качеством продукции
class QualityException : public ProductException {
private:
    std::string expectedGrade;
    std::string actualGrade;
    std::string issueDescription;
    double deviation; // отклонение от стандарта в %
    std::vector<std::string> qualityIssues;

public:
    QualityException(const std::string& message,
                     const std::string& productName,
                     const std::string& productType,
                     double quantity,
                     const std::string& actualGrade,
                     const std::string& expectedGrade,
                     const std::string& issueDescription,
                     double deviation,
                     const std::vector<std::string>& qualityIssues = {})
            : ProductException(message, productName, productType, quantity),
              expectedGrade(expectedGrade),
              actualGrade(actualGrade),
              issueDescription(issueDescription),
              deviation(deviation),
              qualityIssues(qualityIssues) {}

    std::string getExpectedGrade() const { return expectedGrade; }
    std::string getActualGrade() const { return actualGrade; }
    std::string getIssueDescription() const { return issueDescription; }
    double getDeviation() const { return deviation; }
    std::vector<std::string> getQualityIssues() const { return qualityIssues; }

    std::string getFullMessage() const override {
        std::string message = "Quality Exception [" + getProductType() + " - " + getProductName() +
                              "]: Expected: " + expectedGrade +
                              ", Actual: " + actualGrade +
                              ", Issue: " + issueDescription +
                              ", Deviation: " + std::to_string(deviation) + "%";

        if (!qualityIssues.empty()) {
            message += ", Issues: ";
            for (size_t i = 0; i < qualityIssues.size(); ++i) {
                message += qualityIssues[i];
                if (i < qualityIssues.size() - 1) message += ", ";
            }
        }

        return message + " - " + what();
    }
};

// Исключение для проблем со сроком годности
class ExpirationException : public ProductException {
private:
    std::string productionDate;
    std::string expirationDate;
    std::string currentDate;
    int daysExpired;

public:
    ExpirationException(const std::string& message,
                        const std::string& productName,
                        const std::string& productType,
                        double quantity,
                        const std::string& productionDate,
                        const std::string& expirationDate,
                        const std::string& currentDate,
                        int daysExpired)
            : ProductException(message, productName, productType, quantity),
              productionDate(productionDate),
              expirationDate(expirationDate),
              currentDate(currentDate),
              daysExpired(daysExpired) {}

    std::string getProductionDate() const { return productionDate; }
    std::string getExpirationDate() const { return expirationDate; }
    std::string getCurrentDate() const { return currentDate; }
    int getDaysExpired() const { return daysExpired; }

    std::string getFullMessage() const override {
        return "Expiration Exception [" + getProductType() + " - " + getProductName() +
               "]: Produced: " + productionDate +
               ", Expires: " + expirationDate +
               ", Current: " + currentDate +
               ", Expired for " + std::to_string(daysExpired) + " days - " + what();
    }
};

// Исключение для проблем с хранением
class StorageException : public ProductException {
private:
    std::string requiredConditions;
    std::string actualConditions;
    double temperatureDeviation;
    double humidityDeviation;

public:
    StorageException(const std::string& message,
                     const std::string& productName,
                     const std::string& productType,
                     double quantity,
                     const std::string& requiredConditions,
                     const std::string& actualConditions,
                     double temperatureDeviation,
                     double humidityDeviation)
            : ProductException(message, productName, productType, quantity),
              requiredConditions(requiredConditions),
              actualConditions(actualConditions),
              temperatureDeviation(temperatureDeviation),
              humidityDeviation(humidityDeviation) {}

    std::string getRequiredConditions() const { return requiredConditions; }
    std::string getActualConditions() const { return actualConditions; }
    double getTemperatureDeviation() const { return temperatureDeviation; }
    double getHumidityDeviation() const { return humidityDeviation; }

    std::string getFullMessage() const override {
        return "Storage Exception [" + getProductType() + " - " + getProductName() +
               "]: Required: " + requiredConditions +
               ", Actual: " + actualConditions +
               ", Temp deviation: " + std::to_string(temperatureDeviation) + "°C" +
               ", Humidity deviation: " + std::to_string(humidityDeviation) + "% - " + what();
    }
};

// Исключение для проблем с упаковкой
class PackagingException : public ProductException {
private:
    std::string requiredPackaging;
    std::string actualPackaging;
    std::string unit;
    std::string packagingIssue;

public:
    PackagingException(const std::string& message,
                       const std::string& productName,
                       const std::string& productType,
                       double quantity,
                       const std::string& requiredPackaging,
                       const std::string& actualPackaging,
                       const std::string& unit,
                       const std::string& packagingIssue)
            : ProductException(message, productName, productType, quantity),
              requiredPackaging(requiredPackaging),
              actualPackaging(actualPackaging),
              unit(unit),
              packagingIssue(packagingIssue) {}

    std::string getRequiredPackaging() const { return requiredPackaging; }
    std::string getActualPackaging() const { return actualPackaging; }
    std::string getUnit() const { return unit; }
    std::string getPackagingIssue() const { return packagingIssue; }

    std::string getFullMessage() const override {
        return "Packaging Exception [" + getProductType() + " - " + getProductName() +
               "]: Required: " + requiredPackaging +
               ", Actual: " + actualPackaging +
               ", Quantity: " + std::to_string(getQuantity()) + " " + unit +
               ", Issue: " + packagingIssue + " - " + what();
    }
};

#endif // PRODUCTEXCEPTIONS_H