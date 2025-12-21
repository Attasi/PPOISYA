#include "Product.h"
#include "ProductExceptions.h"
#include <iostream>


Product::Product(const std::string& name, double quantity, double pricePerUnit)
        : name(name), quantity(quantity), pricePerUnit(pricePerUnit),
          productionDate("2024-01-01"), expirationDate("2024-12-31"),
          qualityGrade("A"), storageConditions("Room temperature"),
          isOrganic(false), unitOfMeasure("kg"), producerId("FARM001") {

    // Проверка входных параметров
    if (name.empty()) {
        throw ProductException("Product name cannot be empty", "", "", 0.0);
    }

    if (quantity <= 0) {
        throw ProductException("Product quantity must be positive: " +
                               std::to_string(quantity), name, "Product", quantity);
    }

    if (quantity > 1000000.0) {
        throw ProductException("Product quantity unrealistically large: " +
                               std::to_string(quantity) + " (max 1,000,000)",
                               name, "Product", quantity);
    }

    if (pricePerUnit < 0) {
        throw ProductException("Price per unit cannot be negative: $" +
                               std::to_string(pricePerUnit), name, "Product", quantity);
    }

    if (pricePerUnit > 10000.0) {
        throw ProductException("Price per unit unrealistically high: $" +
                               std::to_string(pricePerUnit) + " (max $10,000)",
                               name, "Product", quantity);
    }
}

void Product::displayInfo() const {
    std::cout << "=== Product Information ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Quantity: " << quantity << " " << unitOfMeasure << std::endl;
    std::cout << "Price per unit: $" << pricePerUnit << std::endl;
    std::cout << "Total value: $" << calculateTotalValue() << std::endl;
    std::cout << "Production date: " << productionDate << std::endl;
    std::cout << "Expiration date: " << expirationDate << std::endl;
    std::cout << "Quality grade: " << qualityGrade << std::endl;
    std::cout << "Storage conditions: " << storageConditions << std::endl;
    std::cout << "Organic: " << (isOrganic ? "Yes" : "No") << std::endl;
    std::cout << "Producer ID: " << producerId << std::endl;
}

double Product::calculateTotalValue() const {
    double total = quantity * pricePerUnit;

    if (total < 0) {
        throw ProductException("Negative total value calculated: $" +
                               std::to_string(total), name, "Product", quantity);
    }

    if (total > 100000000.0) {
        throw ProductException("Total value unrealistically high: $" +
                               std::to_string(total) + " (max $100,000,000)",
                               name, "Product", quantity);
    }

    return total;
}

bool Product::isExpired(const std::string& currentDate) const {
    if (currentDate.empty()) {
        throw ProductException("Current date cannot be empty", name, "Product", quantity);
    }

    if (expirationDate.empty()) {
        throw ExpirationException("Expiration date not set", name, "Product",
                                  quantity, productionDate, expirationDate,
                                  currentDate, 0);
    }

    bool expired = currentDate > expirationDate;

    if (expired) {
        // Рассчитываем сколько дней просрочено (упрощенный расчет)
        int daysExpired = 30; // примерное значение

        throw ExpirationException("Product is expired", name, "Product",
                                  quantity, productionDate, expirationDate,
                                  currentDate, daysExpired);
    }

    return expired;
}

void Product::updateQuality() {
    std::cout << "Updating quality for " << name << std::endl;

    // Проверка на истекший срок годности
    std::string currentDate = "2024-06-01"; // примерная дата
    if (isExpired(currentDate)) {
        qualityGrade = "D";
        throw QualityException("Product quality degraded due to expiration",
                               name, "Product", quantity, qualityGrade,
                               "A", "Expired", 100.0);
    }

    // Проверка условий хранения
    if (storageConditions.find("cool") == std::string::npos &&
        name.find("Dairy") != std::string::npos) {
        qualityGrade = "C";
        throw StorageException("Dairy product stored at wrong temperature",
                               name, "Product", quantity,
                               "Cool place", storageConditions,
                               10.0, 20.0);
    }
}

void Product::package() {
    if (quantity <= 0) {
        throw ProductException("Cannot package zero or negative quantity: " +
                               std::to_string(quantity), name, "Product", quantity);
    }

    std::cout << "Packaging " << quantity << " " << unitOfMeasure
              << " of " << name << std::endl;

    // Проверка на соответствие упаковки
    if (unitOfMeasure == "kg" && quantity > 25.0) {
        throw PackagingException("Package too heavy for standard packaging",
                                 name, "Product", quantity,
                                 "Standard bag", "Heavy duty bag",
                                 unitOfMeasure, "Weight exceeds limit");
    }
}

std::string Product::getName() const { return name; }
double Product::getQuantity() const { return quantity; }
double Product::getPricePerUnit() const { return pricePerUnit; }
std::string Product::getProductionDate() const { return productionDate; }
std::string Product::getExpirationDate() const { return expirationDate; }
std::string Product::getQualityGrade() const { return qualityGrade; }
std::string Product::getStorageConditions() const { return storageConditions; }
bool Product::getIsOrganic() const { return isOrganic; }
std::string Product::getUnitOfMeasure() const { return unitOfMeasure; }
std::string Product::getProducerId() const { return producerId; }

void Product::setName(const std::string& name) {
    if (name.empty()) {
        throw ProductException("Product name cannot be empty", "", "", 0.0);
    }
    this->name = name;
}

void Product::setQuantity(double quantity) {
    if (quantity <= 0) {
        throw ProductException("Product quantity must be positive: " +
                               std::to_string(quantity), name, "Product", quantity);
    }

    if (quantity > 1000000.0) {
        throw ProductException("Product quantity unrealistically large: " +
                               std::to_string(quantity) + " (max 1,000,000)",
                               name, "Product", quantity);
    }

    this->quantity = quantity;
}

void Product::setPricePerUnit(double price) {
    if (price < 0) {
        throw ProductException("Price per unit cannot be negative: $" +
                               std::to_string(price), name, "Product", quantity);
    }

    if (price > 10000.0) {
        throw ProductException("Price per unit unrealistically high: $" +
                               std::to_string(price) + " (max $10,000)",
                               name, "Product", quantity);
    }

    pricePerUnit = price;
}

void Product::setProductionDate(const std::string& date) {
    if (date.empty()) {
        throw ProductException("Production date cannot be empty", name, "Product", quantity);
    }

    // Простая проверка формата даты (YYYY-MM-DD)
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        throw ProductException("Invalid production date format: " + date +
                               " (expected YYYY-MM-DD)", name, "Product", quantity);
    }

    productionDate = date;
}

void Product::setExpirationDate(const std::string& date) {
    if (date.empty()) {
        throw ProductException("Expiration date cannot be empty", name, "Product", quantity);
    }

    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        throw ProductException("Invalid expiration date format: " + date +
                               " (expected YYYY-MM-DD)", name, "Product", quantity);
    }

    if (!productionDate.empty() && date < productionDate) {
        throw ProductException("Expiration date cannot be before production date: " +
                               date + " < " + productionDate, name, "Product", quantity);
    }

    expirationDate = date;
}

void Product::setQualityGrade(const std::string& grade) {
    if (grade.empty()) {
        throw ProductException("Quality grade cannot be empty", name, "Product", quantity);
    }

    if (grade != "A" && grade != "B" && grade != "C" && grade != "D") {
        throw QualityException("Invalid quality grade: " + grade,
                               name, "Product", quantity, grade,
                               "A/B/C/D", "Invalid grade", 0.0);
    }

    qualityGrade = grade;
}

void Product::setStorageConditions(const std::string& conditions) {
    if (conditions.empty()) {
        throw ProductException("Storage conditions cannot be empty", name, "Product", quantity);
    }

    storageConditions = conditions;
}

void Product::setIsOrganic(bool organic) { isOrganic = organic; }

void Product::setUnitOfMeasure(const std::string& unit) {
    if (unit.empty()) {
        throw ProductException("Unit of measure cannot be empty", name, "Product", quantity);
    }

    // Проверка допустимых единиц измерения
    std::vector<std::string> validUnits = {"kg", "g", "l", "ml", "pieces", "boxes"};
    bool valid = false;
    for (const auto& validUnit : validUnits) {
        if (unit == validUnit) {
            valid = true;
            break;
        }
    }

    if (!valid) {
        throw ProductException("Invalid unit of measure: " + unit +
                               " (valid: kg, g, l, ml, pieces, boxes)",
                               name, "Product", quantity);
    }

    unitOfMeasure = unit;
}

void Product::setProducerId(const std::string& id) {
    if (id.empty()) {
        throw ProductException("Producer ID cannot be empty", name, "Product", quantity);
    }
    producerId = id;
}

void Product::applyDiscount(double percentage) {
    if (percentage < 0 || percentage > 100) {
        throw ProductException("Discount percentage must be between 0-100: " +
                               std::to_string(percentage), name, "Product", quantity);
    }

    if (percentage > 50 && qualityGrade == "A") {
        throw ProductException("Cannot apply >50% discount to A grade product",
                               name, "Product", quantity);
    }

    pricePerUnit *= (1 - percentage / 100);
    std::cout << "Applied " << percentage << "% discount to " << name << std::endl;
}

bool Product::meetsExportStandards() const {
    if (qualityGrade != "A") {
        throw QualityException("Product does not meet export quality standard",
                               name, "Product", quantity, qualityGrade,
                               "A", "Low quality", 0.0);
    }

    if (!isOrganic && name.find("Organic") != std::string::npos) {
        throw ProductException("Product labeled as organic but isOrganic flag is false",
                               name, "Product", quantity);
    }

    return qualityGrade == "A" && isOrganic;
}

void Product::inspectQuality() {
    std::cout << "Inspecting quality of " << name << std::endl;

    if (qualityGrade == "D") {
        throw QualityException("Product quality grade is D - Reject",
                               name, "Product", quantity, qualityGrade,
                               "A", "Rejected", 100.0);
    }

    if (quantity <= 0.1) {
        throw ProductException("Product quantity too low for inspection: " +
                               std::to_string(quantity), name, "Product", quantity);
    }
}