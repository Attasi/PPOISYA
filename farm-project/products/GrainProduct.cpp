#include "GrainProduct.h"
#include "ProductExceptions.h"
#include <iostream>
#include <algorithm>

GrainProduct::GrainProduct(const std::string& name, double quantity, double pricePerUnit,
                           const std::string& grainType)
        : Product(name, quantity, pricePerUnit), grainType(grainType),
          moistureContent(14.0), proteinContent(12.0), isCleaned(false),
          millingGrade("Standard") {
    setUnitOfMeasure("kg");
    setStorageConditions("Dry, cool place");

    if (grainType.empty()) {
        throw ProductException("Grain type cannot be empty", name, "Grain Product", quantity);
    }

    // Установка срока годности в зависимости от типа зерна
    if (grainType == "Wheat" || grainType == "Corn") {
        setExpirationDate("2025-06-30");
    } else {
        setExpirationDate("2024-12-31");
    }

    // Проверка параметров зерна
    if (moistureContent < 8.0 || moistureContent > 20.0) {
        throw ProductException("Grain moisture content out of range: " +
                               std::to_string(moistureContent) + "% (8-20% normal)",
                               name, "Grain Product", quantity);
    }

    if (proteinContent < 5.0 || proteinContent > 25.0) {
        throw ProductException("Grain protein content out of range: " +
                               std::to_string(proteinContent) + "% (5-25% normal)",
                               name, "Grain Product", quantity);
    }
}

void GrainProduct::cleanGrain() {
    if (isCleaned) {
        throw ProductException(getName() + " is already cleaned",
                               getName(), "Grain Product", getQuantity());
    }

    if (getQuantity() <= 0) {
        throw ProductException("Cannot clean zero or negative grain quantity",
                               getName(), "Grain Product", getQuantity());
    }

    std::cout << "Cleaning " << getQuantity() << " kg of " << grainType << "..." << std::endl;
    isCleaned = true;
    contaminants.clear();

    // Очистка немного уменьшает вес
    setQuantity(getQuantity() * 0.98);

    if (getQualityGrade() == "B") {
        setQualityGrade("A");
        throw QualityException("Grain cleaning improved quality to A grade",
                               getName(), "Grain Product", getQuantity(),
                               getQualityGrade(), "B", "Cleaned", 20.0);
    }

    std::cout << getName() << " has been cleaned. Quality improved to grade A." << std::endl;
}

double GrainProduct::calculateNutritionalValue() const {
    double baseValue = proteinContent * 4.0; // 4 ккал на грамм белка
    if (grainType == "Oats") baseValue += 150;
    if (grainType == "Quinoa") baseValue += 200;

    double totalValue = baseValue * getQuantity() / 100.0;

    if (totalValue > 1000000.0) {
        throw ProductException("Grain nutritional value suspiciously high: " +
                               std::to_string(totalValue) + " kcal",
                               getName(), "Grain Product", getQuantity());
    }

    return totalValue;
}

bool GrainProduct::checkMoistureLevel() const {
    // Идеальный уровень влажности для зерна: 12-14%
    bool optimal = moistureContent >= 12.0 && moistureContent <= 14.0;

    if (!optimal) {
        throw QualityException("Grain moisture level not optimal",
                               getName(), "Grain Product", getQuantity(),
                               getQualityGrade(), "12-14%",
                               std::to_string(moistureContent) + "%",
                               fabs(moistureContent - 13.0) / 13.0 * 100.0);
    }

    return optimal;
}

void GrainProduct::addContaminant(const std::string& contaminant) {
    if (contaminant.empty()) {
        throw ProductException("Contaminant name cannot be empty",
                               getName(), "Grain Product", getQuantity());
    }

    contaminants.push_back(contaminant);

    if (contaminants.size() > 3) {
        setQualityGrade("C");
        throw QualityException("Too many contaminants in grain",
                               getName(), "Grain Product", getQuantity(),
                               getQualityGrade(), "Clean", "Contaminated",
                               contaminants.size() * 20.0);
    } else if (contaminants.size() > 1) {
        if (getQualityGrade() == "A") {
            setQualityGrade("B");
            throw QualityException("Contaminants reduced grain quality",
                                   getName(), "Grain Product", getQuantity(),
                                   getQualityGrade(), "A", "Contaminated", 25.0);
        }
    }

    std::cout << "Contaminant added: " << contaminant << std::endl;
}

void GrainProduct::removeContaminants() {
    if (contaminants.empty()) {
        throw ProductException("No contaminants to remove from " + getName(),
                               getName(), "Grain Product", getQuantity());
    }

    std::cout << "Removing contaminants from " << getName() << ": ";
    for (const auto& contaminant : contaminants) {
        std::cout << contaminant << " ";
    }
    std::cout << std::endl;

    contaminants.clear();

    if (getQualityGrade() == "B" || getQualityGrade() == "C") {
        setQualityGrade("A");
        std::cout << "Grain quality restored to grade A after contaminant removal." << std::endl;
    }
}

std::string GrainProduct::getGrainClass() const {
    if (proteinContent > 15.0 && moistureContent < 13.0 && isCleaned) {
        return "Premium";
    } else if (proteinContent > 12.0 && moistureContent < 14.0) {
        return "First Class";
    } else if (proteinContent > 10.0) {
        return "Second Class";
    } else {
        return "Feed Grade";
    }
}

void GrainProduct::displayInfo() const {
    Product::displayInfo();
    std::cout << "=== Grain Product Details ===" << std::endl;
    std::cout << "Grain type: " << grainType << std::endl;
    std::cout << "Moisture content: " << moistureContent << "%" << std::endl;
    std::cout << "Protein content: " << proteinContent << "%" << std::endl;
    std::cout << "Cleaned: " << (isCleaned ? "Yes" : "No") << std::endl;
    std::cout << "Milling grade: " << millingGrade << std::endl;
    std::cout << "Grain class: " << getGrainClass() << std::endl;

    if (!contaminants.empty()) {
        std::cout << "Contaminants: ";
        for (size_t i = 0; i < contaminants.size(); ++i) {
            std::cout << contaminants[i];
            if (i < contaminants.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }

    std::cout << "Optimal moisture: " << (checkMoistureLevel() ? "Yes" : "No") << std::endl;
    std::cout << "Nutritional value per 100g: "
              << calculateNutritionalValue() / (getQuantity() * 10) << " kcal" << std::endl;

    // Проверка условий хранения для зерна
    if (getStorageConditions().find("Dry") == std::string::npos) {
        throw StorageException("Grain not stored in dry conditions",
                               getName(), "Grain Product", getQuantity(),
                               "Dry, cool place", getStorageConditions(),
                               0.0, 25.0); // высокая влажность опасна
    }
}

void GrainProduct::updateQuality() {
    Product::updateQuality();

    // Проверка влажности
    if (moistureContent > 15.0) {
        if (getQualityGrade() == "A") {
            setQualityGrade("B");
            throw QualityException("Grain moisture too high for A grade",
                                   getName(), "Grain Product", getQuantity(),
                                   getQualityGrade(), "A", "High moisture",
                                   (moistureContent - 15.0) / 15.0 * 100.0);
        } else if (moistureContent > 18.0) {
            setQualityGrade("C");
            throw QualityException("Grain moisture dangerously high",
                                   getName(), "Grain Product", getQuantity(),
                                   getQualityGrade(), "A", "Very high moisture",
                                   (moistureContent - 15.0) / 15.0 * 100.0);
        }
    }

    // Проверка загрязнителей
    if (!contaminants.empty()) {
        if (getQualityGrade() == "A") {
            setQualityGrade("B");
            throw QualityException("Contaminants present in A grade grain",
                                   getName(), "Grain Product", getQuantity(),
                                   getQualityGrade(), "A", "Contaminated", 20.0);
        }
    }

    // Автоматическая очистка если много загрязнителей
    if (contaminants.size() > 3 && !isCleaned) {
        std::cout << "Auto-cleaning grain due to high contaminant count..." << std::endl;
        cleanGrain();
    }
}

void GrainProduct::package() {
    if (getQuantity() <= 0) {
        throw ProductException("Cannot package zero or negative grain quantity",
                               getName(), "Grain Product", getQuantity());
    }

    std::cout << "Packaging grain product: " << getName() << std::endl;
    std::cout << "Using special grain bags for " << getQuantity() << " kg" << std::endl;

    if (!isCleaned) {
        std::cout << "Warning: Packaging uncleaned grain!" << std::endl;
        throw PackagingException("Uncleaned grain requires special packaging",
                                 getName(), "Grain Product", getQuantity(),
                                 "Clean grain bag", "Uncleaned grain bag",
                                 getUnitOfMeasure(), "Contains contaminants");
    }

    if (moistureContent > 14.0) {
        throw PackagingException("High moisture grain requires special packaging",
                                 getName(), "Grain Product", getQuantity(),
                                 "Standard bag", "Ventilated bag",
                                 getUnitOfMeasure(), "High moisture content");
    }
}

bool GrainProduct::meetsExportStandards() const {
    bool baseStandards = Product::meetsExportStandards();

    if (!isCleaned) {
        throw QualityException("Grain not cleaned for export",
                               getName(), "Grain Product", getQuantity(),
                               getQualityGrade(), "Cleaned", "Uncleaned", 100.0);
    }

    if (moistureContent > 14.0) {
        throw QualityException("Grain moisture too high for export",
                               getName(), "Grain Product", getQuantity(),
                               getQualityGrade(), "≤14%",
                               std::to_string(moistureContent) + "%",
                               (moistureContent - 14.0) / 14.0 * 100.0);
    }

    if (!contaminants.empty()) {
        throw QualityException("Grain has contaminants, not suitable for export",
                               getName(), "Grain Product", getQuantity(),
                               getQualityGrade(), "Clean", "Contaminated", 100.0);
    }

    bool grainStandards = isCleaned &&
                          moistureContent <= 14.0 &&
                          contaminants.empty() &&
                          getGrainClass() == "Premium";

    return baseStandards && grainStandards;
}

void GrainProduct::inspectQuality() {
    Product::inspectQuality();
    std::cout << "Grain-specific inspection:" << std::endl;
    std::cout << "1. Checking moisture: " << moistureContent << "%"
              << (checkMoistureLevel() ? " (OK)" : " (Not optimal)") << std::endl;
    std::cout << "2. Checking cleanliness: " << (isCleaned ? "Clean" : "Needs cleaning") << std::endl;
    std::cout << "3. Grain class: " << getGrainClass() << std::endl;

    if (!contaminants.empty()) {
        throw QualityException("Grain inspection failed - contaminants found",
                               getName(), "Grain Product", getQuantity(),
                               getQualityGrade(), "Clean", "Contaminated",
                               contaminants.size() * 25.0);
    }
}

std::string GrainProduct::getGrainType() const { return grainType; }
double GrainProduct::getMoistureContent() const { return moistureContent; }
double GrainProduct::getProteinContent() const { return proteinContent; }
bool GrainProduct::getIsCleaned() const { return isCleaned; }
std::string GrainProduct::getMillingGrade() const { return millingGrade; }
std::vector<std::string> GrainProduct::getContaminants() const { return contaminants; }

void GrainProduct::setGrainType(const std::string& type) {
    if (type.empty()) {
        throw ProductException("Grain type cannot be empty", getName(), "Grain Product", getQuantity());
    }
    grainType = type;
}

void GrainProduct::setMoistureContent(double moisture) {
    if (moisture < 0 || moisture > 30.0) {
        throw ProductException("Moisture content must be between 0-30%: " +
                               std::to_string(moisture), getName(), "Grain Product", getQuantity());
    }

    if (moisture > 20.0 && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("High moisture content reduces grain quality",
                               getName(), "Grain Product", getQuantity(),
                               getQualityGrade(), "A", "High moisture",
                               (moisture - 15.0) / 15.0 * 100.0);
    }

    moistureContent = moisture;
}

void GrainProduct::setProteinContent(double protein) {
    if (protein < 0 || protein > 40.0) {
        throw ProductException("Protein content must be between 0-40%: " +
                               std::to_string(protein), getName(), "Grain Product", getQuantity());
    }

    if (grainType == "Wheat" && protein < 10.0 && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("Wheat protein content too low for A grade",
                               getName(), "Grain Product", getQuantity(),
                               getQualityGrade(), "A", "Low protein",
                               (10.0 - protein) / 10.0 * 100.0);
    }

    proteinContent = protein;
}

void GrainProduct::setMillingGrade(const std::string& grade) {
    if (grade.empty()) {
        throw ProductException("Milling grade cannot be empty", getName(), "Grain Product", getQuantity());
    }

    std::vector<std::string> validGrades = {"Fine", "Standard", "Coarse", "Whole"};
    bool validGrade = false;
    for (const auto& valid : validGrades) {
        if (grade == valid) {
            validGrade = true;
            break;
        }
    }

    if (!validGrade) {
        throw ProductException("Invalid milling grade: " + grade +
                               " (valid: Fine, Standard, Coarse, Whole)",
                               getName(), "Grain Product", getQuantity());
    }

    millingGrade = grade;
}