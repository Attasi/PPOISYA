#include "VegetableProduct.h"
#include "ProductExceptions.h"
#include <iostream>
#include <algorithm>

VegetableProduct::VegetableProduct(const std::string& name, double quantity,
                                   double pricePerUnit, const std::string& vegetableType)
        : Product(name, quantity, pricePerUnit), vegetableType(vegetableType),
          freshnessLevel(100.0), isWashed(false), isCut(false), sizeCategory("Medium") {
    setUnitOfMeasure("kg");
    setStorageConditions("Cool, dark place");

    if (vegetableType.empty()) {
        throw ProductException("Vegetable type cannot be empty", name, "Vegetable Product", quantity);
    }

    // Установка срока годности в зависимости от типа овощей
    if (vegetableType == "Potato" || vegetableType == "Carrot") {
        setExpirationDate("2024-12-31");
    } else if (vegetableType == "Tomato" || vegetableType == "Cucumber") {
        setExpirationDate("2024-02-15");
    } else {
        setExpirationDate("2024-01-31");
    }

    // Проверка свежести
    if (freshnessLevel < 50.0) {
        throw QualityException("Vegetable freshness too low at creation",
                               name, "Vegetable Product", quantity,
                               "A", "High", "Low freshness",
                               (50.0 - freshnessLevel) / 50.0 * 100.0);
    }
}

void VegetableProduct::washVegetables() {
    if (isWashed) {
        throw ProductException(getName() + " is already washed",
                               getName(), "Vegetable Product", getQuantity());
    }

    if (getQuantity() <= 0) {
        throw ProductException("Cannot wash zero or negative vegetable quantity",
                               getName(), "Vegetable Product", getQuantity());
    }

    std::cout << "Washing " << getQuantity() << " kg of " << vegetableType << "..." << std::endl;
    isWashed = true;
    freshnessLevel += 5.0;
    if (freshnessLevel > 100.0) freshnessLevel = 100.0;

    // Удаление некоторых дефектов при мытье
    auto it = std::remove_if(defects.begin(), defects.end(),
                             [](const std::string& defect) {
                                 return defect == "Dirt" || defect == "Soil" || defect == "Mud";
                             });
    defects.erase(it, defects.end());

    // Мытье улучшает качество
    if (getQualityGrade() == "B" && freshnessLevel > 85.0) {
        setQualityGrade("A");
        throw QualityException("Washing improved vegetable quality to A grade",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "B", "Washed", 15.0);
    }

    std::cout << getName() << " has been washed. Freshness improved to "
              << freshnessLevel << "%." << std::endl;
}

void VegetableProduct::cutVegetables() {
    if (isCut) {
        throw ProductException(getName() + " is already cut",
                               getName(), "Vegetable Product", getQuantity());
    }

    if (!isWashed) {
        throw ProductException(getName() + " must be washed before cutting",
                               getName(), "Vegetable Product", getQuantity());
    }

    if (freshnessLevel < 70.0) {
        throw QualityException("Vegetables too old for cutting",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "Fresh", "Old",
                               (70.0 - freshnessLevel) / 70.0 * 100.0);
    }

    std::cout << "Cutting " << getQuantity() << " kg of " << vegetableType << "..." << std::endl;
    isCut = true;

    // Нарезка уменьшает срок годности
    if (getExpirationDate() > "2024-01-20") {
        setExpirationDate("2024-01-20");
    }

    // Нарезка немного уменьшает вес
    setQuantity(getQuantity() * 0.95);

    std::cout << getName() << " has been cut. Ready for cooking!" << std::endl;
    std::cout << "New quantity: " << getQuantity() << " kg" << std::endl;
}

void VegetableProduct::checkFreshness() {
    if (freshnessLevel <= 0) {
        throw QualityException("Vegetables have spoiled completely",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "Fresh", "Spoiled", 100.0);
    }

    std::cout << "Freshness check for " << getName() << ": "
              << freshnessLevel << "%" << std::endl;

    if (freshnessLevel > 80.0) {
        std::cout << "Very fresh!" << std::endl;
    } else if (freshnessLevel > 60.0) {
        std::cout << "Acceptable freshness" << std::endl;
    } else if (freshnessLevel > 40.0) {
        std::cout << "Starting to lose freshness" << std::endl;
        if (getQualityGrade() == "A") {
            setQualityGrade("B");
            throw QualityException("Vegetable freshness declining",
                                   getName(), "Vegetable Product", getQuantity(),
                                   getQualityGrade(), "A", "Aging",
                                   (80.0 - freshnessLevel) / 80.0 * 100.0);
        }
    } else {
        std::cout << "Not fresh - consider discounting" << std::endl;
        setQualityGrade("C");
        throw QualityException("Vegetables not fresh",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "A", "Old",
                               (60.0 - freshnessLevel) / 60.0 * 100.0);
    }
}

void VegetableProduct::addDefect(const std::string& defect) {
    if (defect.empty()) {
        throw ProductException("Defect description cannot be empty",
                               getName(), "Vegetable Product", getQuantity());
    }

    defects.push_back(defect);
    freshnessLevel -= 10.0;
    if (freshnessLevel < 0) freshnessLevel = 0;

    if (defects.size() > 2 && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("Too many defects for A grade vegetables",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "A", "Defective",
                               defects.size() * 20.0);
    } else if (defects.size() > 4) {
        setQualityGrade("C");
        throw QualityException("Excessive defects in vegetables",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "A", "Many defects",
                               defects.size() * 25.0);
    }

    std::cout << "Defect added: " << defect << std::endl;
}

void VegetableProduct::removeDefects() {
    if (defects.empty()) {
        throw ProductException("No defects to remove from " + getName(),
                               getName(), "Vegetable Product", getQuantity());
    }

    std::cout << "Removing defects from " << getName() << ": ";
    for (const auto& defect : defects) {
        std::cout << defect << " ";
    }
    std::cout << std::endl;

    defects.clear();
    freshnessLevel += 20.0;
    if (freshnessLevel > 100.0) freshnessLevel = 100.0;

    if (getQualityGrade() == "B" || getQualityGrade() == "C") {
        setQualityGrade("A");
        std::cout << "Vegetable quality restored to grade A after defect removal." << std::endl;
    }
}

double VegetableProduct::calculateVitaminContent() const {
    double baseVitamins = 50.0;

    if (vegetableType == "Carrot") baseVitamins = 80.0;
    else if (vegetableType == "Tomato") baseVitamins = 70.0;
    else if (vegetableType == "Broccoli") baseVitamins = 100.0;
    else if (vegetableType == "Spinach") baseVitamins = 120.0;

    double freshnessMultiplier = freshnessLevel / 100.0;
    double totalVitamins = baseVitamins * freshnessMultiplier * getQuantity() / 10.0;

    if (totalVitamins > 10000.0) {
        throw ProductException("Vegetable vitamin content suspiciously high: " +
                               std::to_string(totalVitamins) + " mg",
                               getName(), "Vegetable Product", getQuantity());
    }

    return totalVitamins;
}

bool VegetableProduct::isReadyForCooking() const {
    if (!isWashed) {
        throw ProductException(getName() + " must be washed before cooking",
                               getName(), "Vegetable Product", getQuantity());
    }

    if (freshnessLevel <= 50.0) {
        throw QualityException("Vegetables too old for cooking",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "Fresh", "Old",
                               (70.0 - freshnessLevel) / 70.0 * 100.0);
    }

    if (!defects.empty()) {
        throw QualityException("Vegetables have defects, not suitable for cooking",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "No defects", "Defective",
                               defects.size() * 30.0);
    }

    return isWashed && freshnessLevel > 70.0 && defects.empty();
}

void VegetableProduct::displayInfo() const {
    Product::displayInfo();
    std::cout << "=== Vegetable Product Details ===" << std::endl;
    std::cout << "Vegetable type: " << vegetableType << std::endl;
    std::cout << "Freshness level: " << freshnessLevel << "%" << std::endl;
    std::cout << "Washed: " << (isWashed ? "Yes" : "No") << std::endl;
    std::cout << "Cut: " << (isCut ? "Yes" : "No") << std::endl;
    std::cout << "Size category: " << sizeCategory << std::endl;
    std::cout << "Ready for cooking: " << (isReadyForCooking() ? "Yes" : "No") << std::endl;
    std::cout << "Vitamin content: " << calculateVitaminContent() << " mg total" << std::endl;

    if (!defects.empty()) {
        std::cout << "Defects: ";
        for (size_t i = 0; i < defects.size(); ++i) {
            std::cout << defects[i];
            if (i < defects.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }

    // Проверка условий хранения
    if (getStorageConditions().find("Cool") == std::string::npos) {
        throw StorageException("Vegetables not stored at cool temperature",
                               getName(), "Vegetable Product", getQuantity(),
                               "Cool, dark place", getStorageConditions(),
                               10.0, 15.0);
    }
}

void VegetableProduct::updateQuality() {
    Product::updateQuality();

    // Овощи теряют свежесть со временем
    freshnessLevel -= 5.0;
    if (freshnessLevel < 0) freshnessLevel = 0;

    // Обновление категории качества на основе свежести
    if (freshnessLevel > 80.0) {
        if (getQualityGrade() != "A") {
            setQualityGrade("A");
        }
    } else if (freshnessLevel > 60.0) {
        if (getQualityGrade() == "A") {
            setQualityGrade("B");
            throw QualityException("Vegetable freshness declined to B grade",
                                   getName(), "Vegetable Product", getQuantity(),
                                   getQualityGrade(), "A", "Aging",
                                   (80.0 - freshnessLevel) / 80.0 * 100.0);
        }
    } else if (freshnessLevel > 40.0) {
        if (getQualityGrade() == "B") {
            setQualityGrade("C");
            throw QualityException("Vegetable freshness declined to C grade",
                                   getName(), "Vegetable Product", getQuantity(),
                                   getQualityGrade(), "B", "Old",
                                   (60.0 - freshnessLevel) / 60.0 * 100.0);
        }
    } else {
        setQualityGrade("D");
        throw QualityException("Vegetables have spoiled",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "A", "Spoiled", 100.0);
    }

    // Автоматическое мытье если много дефектов и не вымыто
    if (!defects.empty() && !isWashed) {
        std::cout << "Auto-washing vegetables due to defects..." << std::endl;
        washVegetables();
    }
}

void VegetableProduct::package() {
    if (getQuantity() <= 0) {
        throw ProductException("Cannot package zero or negative vegetable quantity",
                               getName(), "Vegetable Product", getQuantity());
    }

    std::cout << "Packaging vegetable product: " << getName() << std::endl;

    if (isCut) {
        std::cout << "Using vacuum packaging for cut vegetables" << std::endl;
        std::cout << "Packaging " << getQuantity() << " kg into portion packs" << std::endl;

        if (!isWashed) {
            throw PackagingException("Cut vegetables must be washed before vacuum packaging",
                                     getName(), "Vegetable Product", getQuantity(),
                                     "Washed & vacuum packed", "Unwashed cut",
                                     getUnitOfMeasure(), "Sanitation issue");
        }
    } else {
        std::cout << "Using mesh bags for whole vegetables" << std::endl;
        std::cout << "Packaging " << getQuantity() << " kg" << std::endl;

        if (freshnessLevel < 70.0) {
            throw PackagingException("Low freshness vegetables require special packaging",
                                     getName(), "Vegetable Product", getQuantity(),
                                     "Standard bag", "Quick sale bag",
                                     getUnitOfMeasure(), "Low freshness");
        }
    }

    if (!isWashed) {
        std::cout << "Note: Vegetables are not washed" << std::endl;
        throw PackagingException("Unwashed vegetables require special labeling",
                                 getName(), "Vegetable Product", getQuantity(),
                                 "Washed vegetables", "Unwashed vegetables",
                                 getUnitOfMeasure(), "Consumer information");
    }
}

bool VegetableProduct::meetsExportStandards() const {
    bool baseStandards = Product::meetsExportStandards();

    if (!isWashed) {
        throw QualityException("Vegetables not washed for export",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "Washed", "Unwashed", 100.0);
    }

    if (freshnessLevel <= 85.0) {
        throw QualityException("Vegetable freshness too low for export",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "≥85%",
                               std::to_string(freshnessLevel) + "%",
                               (85.0 - freshnessLevel) / 85.0 * 100.0);
    }

    if (!defects.empty()) {
        throw QualityException("Vegetables have defects, not suitable for export",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "No defects", "Defective", 100.0);
    }

    if (isCut) {
        throw ProductException("Cut vegetables cannot be exported",
                               getName(), "Vegetable Product", getQuantity());
    }

    bool vegetableStandards = isWashed &&
                              freshnessLevel > 85.0 &&
                              defects.empty() &&
                              !isCut;

    return baseStandards && vegetableStandards;
}

void VegetableProduct::inspectQuality() {
    Product::inspectQuality();
    std::cout << "Vegetable-specific inspection:" << std::endl;
    std::cout << "1. Freshness: " << freshnessLevel << "%"
              << (freshnessLevel > 70.0 ? " (Good)" : " (Needs attention)") << std::endl;
    std::cout << "2. Cleanliness: " << (isWashed ? "Washed" : "Needs washing") << std::endl;
    std::cout << "3. Defects count: " << defects.size() << std::endl;
    std::cout << "4. Ready for cooking: " << (isReadyForCooking() ? "Yes" : "No") << std::endl;

    if (!defects.empty()) {
        throw QualityException("Vegetable inspection failed - defects found",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "No defects", "Defective",
                               defects.size() * 30.0);
    }

    if (freshnessLevel < 60.0) {
        throw QualityException("Vegetable inspection failed - low freshness",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "≥60%",
                               std::to_string(freshnessLevel) + "%",
                               (60.0 - freshnessLevel) / 60.0 * 100.0);
    }
}

std::string VegetableProduct::getVegetableType() const { return vegetableType; }
double VegetableProduct::getFreshnessLevel() const { return freshnessLevel; }
bool VegetableProduct::getIsWashed() const { return isWashed; }
bool VegetableProduct::getIsCut() const { return isCut; }
std::string VegetableProduct::getSizeCategory() const { return sizeCategory; }
std::vector<std::string> VegetableProduct::getDefects() const { return defects; }

void VegetableProduct::setVegetableType(const std::string& type) {
    if (type.empty()) {
        throw ProductException("Vegetable type cannot be empty", getName(), "Vegetable Product", getQuantity());
    }
    vegetableType = type;
}

void VegetableProduct::setFreshnessLevel(double freshness) {
    if (freshness < 0 || freshness > 100.0) {
        throw ProductException("Freshness level must be between 0-100%: " +
                               std::to_string(freshness), getName(), "Vegetable Product", getQuantity());
    }

    if (freshness < 50.0 && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("Freshness too low for A grade vegetables",
                               getName(), "Vegetable Product", getQuantity(),
                               getQualityGrade(), "A", "Low freshness",
                               (50.0 - freshness) / 50.0 * 100.0);
    }

    freshnessLevel = freshness;
}

void VegetableProduct::setIsWashed(bool washed) {
    if (!washed && isCut) {
        throw ProductException("Cut vegetables must be washed", getName(), "Vegetable Product", getQuantity());
    }
    isWashed = washed;
}

void VegetableProduct::setIsCut(bool cut) {
    if (cut && !isWashed) {
        throw ProductException("Vegetables must be washed before cutting", getName(), "Vegetable Product", getQuantity());
    }
    isCut = cut;
}

void VegetableProduct::setSizeCategory(const std::string& category) {
    if (category.empty()) {
        throw ProductException("Size category cannot be empty", getName(), "Vegetable Product", getQuantity());
    }

    std::vector<std::string> validCategories = {"Small", "Medium", "Large", "Extra Large"};
    bool validCategory = false;
    for (const auto& valid : validCategories) {
        if (category == valid) {
            validCategory = true;
            break;
        }
    }

    if (!validCategory) {
        throw ProductException("Invalid size category: " + category +
                               " (valid: Small, Medium, Large, Extra Large)",
                               getName(), "Vegetable Product", getQuantity());
    }

    sizeCategory = category;
}