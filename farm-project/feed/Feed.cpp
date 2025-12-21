#include "Feed.h"
#include "FeedExceptions.h"
#include <iostream>

Feed::Feed(const std::string& name, double quantity, double pricePerKg) {
    // Проверка входных параметров
    if (name.empty()) {
        throw FeedException("Feed name cannot be empty");
    }
    if (quantity <= 0) {
        throw FeedException("Feed quantity must be positive: " + std::to_string(quantity));
    }
    if (quantity > 100000) {
        throw FeedException("Feed quantity too large (max 100,000 kg): " + std::to_string(quantity));
    }
    if (pricePerKg < 0) {
        throw FeedException("Feed price cannot be negative: $" + std::to_string(pricePerKg));
    }
    if (pricePerKg > 100) {
        throw FeedException("Feed price unrealistically high (max $100/kg): $" + std::to_string(pricePerKg));
    }

    this->name = name;
    this->quantity = quantity;
    this->pricePerKg = pricePerKg;
    this->productionDate = "2024-01-01";
    this->expirationDate = "2024-12-31";
    this->storageLocation = "Warehouse A";
    this->proteinContent = 10.0;
    this->fiberContent = 20.0;
    this->moistureContent = 12.0;
    this->qualityGrade = "Standard";
    this->isOrganic = false;
}

void Feed::displayInfo() const {
    std::cout << "=== Feed Information ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Quantity: " << quantity << " kg" << std::endl;
    std::cout << "Price per kg: $" << pricePerKg << std::endl;
    std::cout << "Total value: $" << calculateTotalValue() << std::endl;
    std::cout << "Production date: " << productionDate << std::endl;
    std::cout << "Expiration date: " << expirationDate << std::endl;
    std::cout << "Storage location: " << storageLocation << std::endl;
    std::cout << "Protein content: " << proteinContent << "%" << std::endl;
    std::cout << "Fiber content: " << fiberContent << "%" << std::endl;
    std::cout << "Moisture content: " << moistureContent << "%" << std::endl;
    std::cout << "Quality grade: " << qualityGrade << std::endl;
    std::cout << "Organic: " << (isOrganic ? "Yes" : "No") << std::endl;
}

double Feed::calculateTotalValue() const {
    return quantity * pricePerKg;
}

bool Feed::isExpired(const std::string& currentDate) const {
    if (currentDate.empty() || expirationDate.empty()) {
        throw FeedException("Date strings cannot be empty");
    }
    if (currentDate > expirationDate) {
        throw SpoiledFeedException(name, expirationDate, currentDate);
    }
    return false;
}

void Feed::checkQuality() {
    if (moistureContent > 20) {
        qualityGrade = "Low";
        throw FeedException(name + " has dangerously high moisture content: " +
                            std::to_string(moistureContent) + "% (max 20%)");
    } else if (proteinContent < 5) {
        qualityGrade = "Medium";
        std::cout << "Protein content is below optimal level." << std::endl;
    } else {
        qualityGrade = "High";
        std::cout << "Feed quality is good." << std::endl;
    }
}

void Feed::store() {
    if (storageLocation.empty()) {
        throw FeedException("Storage location cannot be empty");
    }

    std::cout << "Storing " << quantity << " kg of " << name
              << " in " << storageLocation << std::endl;
}

std::string Feed::getName() const { return name; }
double Feed::getQuantity() const { return quantity; }
double Feed::getPricePerKg() const { return pricePerKg; }
std::string Feed::getProductionDate() const { return productionDate; }
std::string Feed::getExpirationDate() const { return expirationDate; }
std::string Feed::getStorageLocation() const { return storageLocation; }
double Feed::getProteinContent() const { return proteinContent; }
double Feed::getFiberContent() const { return fiberContent; }
double Feed::getMoistureContent() const { return moistureContent; }
std::string Feed::getQualityGrade() const { return qualityGrade; }
bool Feed::getIsOrganic() const { return isOrganic; }

void Feed::setName(const std::string& name) {
    if (name.empty()) {
        throw FeedException("Feed name cannot be empty");
    }
    this->name = name;
}

void Feed::setQuantity(double quantity) {
    if (quantity < 0) {
        throw FeedException("Feed quantity cannot be negative: " + std::to_string(quantity));
    }
    if (quantity > 100000) {
        throw FeedException("Feed quantity too large (max 100,000 kg): " + std::to_string(quantity));
    }
    this->quantity = quantity;
}

void Feed::setPricePerKg(double price) {
    if (price < 0) {
        throw FeedException("Feed price cannot be negative: $" + std::to_string(price));
    }
    if (price > 100) {
        throw FeedException("Feed price unrealistically high (max $100/kg): $" + std::to_string(price));
    }
    pricePerKg = price;
}

void Feed::setProductionDate(const std::string& date) {
    if (date.empty()) {
        throw FeedException("Production date cannot be empty");
    }
    productionDate = date;
}

void Feed::setExpirationDate(const std::string& date) {
    if (date.empty()) {
        throw FeedException("Expiration date cannot be empty");
    }
    expirationDate = date;
}

void Feed::setStorageLocation(const std::string& location) {
    if (location.empty()) {
        throw FeedException("Storage location cannot be empty");
    }
    storageLocation = location;
}

void Feed::setProteinContent(double protein) {
    if (protein < 0 || protein > 50) {
        throw FeedException("Protein content must be between 0-50%: " + std::to_string(protein));
    }
    proteinContent = protein;
}

void Feed::setFiberContent(double fiber) {
    if (fiber < 0 || fiber > 50) {
        throw FeedException("Fiber content must be between 0-50%: " + std::to_string(fiber));
    }
    fiberContent = fiber;
}

void Feed::setMoistureContent(double moisture) {
    if (moisture < 0 || moisture > 100) {
        throw FeedException("Moisture content must be between 0-100%: " + std::to_string(moisture));
    }
    moistureContent = moisture;
}

void Feed::setQualityGrade(const std::string& grade) {
    if (grade.empty()) {
        throw FeedException("Quality grade cannot be empty");
    }
    qualityGrade = grade;
}

void Feed::setIsOrganic(bool organic) { isOrganic = organic; }

double Feed::calculateNutritionalValue() const {
    return proteinContent * 10 + fiberContent * 5;
}

bool Feed::isSuitableForAnimal(const std::string& animalType) const {
    if (animalType.empty()) {
        throw FeedException("Animal type cannot be empty");
    }

    // Базовая реализация
    if (moistureContent > 15 && animalType == "Horse") {
        throw FeedException(name + " too moist for horses: " +
                            std::to_string(moistureContent) + "% (max 15%)");
    }
    return true;
}

void Feed::applyDiscount(double percentage) {
    if (percentage < 0 || percentage > 100) {
        throw FeedException("Discount percentage must be between 0-100: " +
                            std::to_string(percentage));
    }

    pricePerKg *= (1 - percentage / 100);
    std::cout << "Applied " << percentage << "% discount to " << name << std::endl;
}

void Feed::updateStock(double amount) {
    if (quantity + amount < 0) {
        throw InsufficientFeedException("Various animals", -amount, quantity);
    }
    if (amount < -1000 || amount > 1000) {
        throw FeedException("Stock update amount unrealistic: " + std::to_string(amount) +
                            " kg (max ±1000 kg per transaction)");
    }

    quantity += amount;
    std::cout << "Updated stock of " << name << " by " << amount
              << " kg. New quantity: " << quantity << " kg" << std::endl;
}