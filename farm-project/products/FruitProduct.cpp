#include "FruitProduct.h"
#include "ProductExceptions.h"
#include <iostream>
#include <algorithm>

FruitProduct::FruitProduct(const std::string& name, double quantity,
                           double pricePerUnit, const std::string& fruitType)
        : Product(name, quantity, pricePerUnit), fruitType(fruitType),
          ripenessLevel(70.0), ripenessStage("Ripening"),
          isPackagedInBaskets(false), brixLevel(12) {
    setUnitOfMeasure("kg");
    setStorageConditions("Cool, ventilated place");

    if (fruitType.empty()) {
        throw ProductException("Fruit type cannot be empty", name, "Fruit Product", quantity);
    }

    // Установка срока годности в зависимости от типа фруктов
    if (fruitType == "Apples" || fruitType == "Pears") {
        setExpirationDate("2024-03-31");
    } else if (fruitType == "Berries") {
        setExpirationDate("2024-01-10");
    } else if (fruitType == "Citrus") {
        setExpirationDate("2024-02-28");
    } else {
        setExpirationDate("2024-01-31");
    }

    // Определение стадии спелости
    updateRipenessStage();

    // Проверка уровня Брикса
    if (brixLevel < 5 || brixLevel > 25) {
        throw ProductException("Brix level out of normal range: " +
                               std::to_string(brixLevel) + " (5-25 normal)",
                               name, "Fruit Product", quantity);
    }
}

void FruitProduct::updateRipenessStage() {
    if (ripenessLevel < 30.0) {
        ripenessStage = "Green";
    } else if (ripenessLevel < 60.0) {
        ripenessStage = "Ripening";
    } else if (ripenessLevel < 85.0) {
        ripenessStage = "Ripe";
    } else if (ripenessLevel < 95.0) {
        ripenessStage = "Very Ripe";
    } else {
        ripenessStage = "Overripe";
    }
}

std::string FruitProduct::checkRipenessStage() const {
    return ripenessStage;
}

void FruitProduct::ripenFruit(double amount) {
    if (amount <= 0) {
        throw ProductException("Ripening amount must be positive: " +
                               std::to_string(amount), getName(), "Fruit Product", getQuantity());
    }

    if (ripenessLevel >= 100.0) {
        throw ProductException(getName() + " is already fully ripe (100%)",
                               getName(), "Fruit Product", getQuantity());
    }

    if (ripenessStage == "Overripe") {
        throw QualityException("Cannot ripen overripe fruit further",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "Ripe", "Overripe", 50.0);
    }

    ripenessLevel += amount;
    if (ripenessLevel > 100.0) {
        ripenessLevel = 100.0;
        throw ProductException(getName() + " reached maximum ripeness (100%)",
                               getName(), "Fruit Product", getQuantity());
    }

    updateRipenessStage();

    // Созревание улучшает качество до определенного предела
    if (ripenessStage == "Ripe" && getQualityGrade() == "B") {
        setQualityGrade("A");
        throw QualityException("Fruit ripening improved quality to A grade",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "B", "Ripe", 25.0);
    }

    std::cout << getName() << " ripened by " << amount
              << "%. Current ripeness: " << ripenessLevel << "% ("
              << ripenessStage << ")" << std::endl;
}

void FruitProduct::packageInBaskets() {
    if (isPackagedInBaskets) {
        throw ProductException(getName() + " is already packaged in baskets",
                               getName(), "Fruit Product", getQuantity());
    }

    if (getQuantity() <= 0) {
        throw ProductException("Cannot package zero or negative fruit quantity",
                               getName(), "Fruit Product", getQuantity());
    }

    if (ripenessStage != "Ripe" && ripenessStage != "Very Ripe") {
        throw QualityException("Fruit not ripe enough for basket packaging",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "Ripe", ripenessStage,
                               (80.0 - ripenessLevel) / 80.0 * 100.0);
    }

    if (bruises.size() > 2) {
        throw QualityException("Too many bruises for basket packaging",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "No bruises", "Bruised",
                               bruises.size() * 30.0);
    }

    std::cout << "Packaging " << getQuantity() << " kg of " << fruitType
              << " in decorative baskets..." << std::endl;
    isPackagedInBaskets = true;

    // Упаковка в корзины увеличивает стоимость
    setPricePerUnit(getPricePerUnit() * 1.2);

    std::cout << getName() << " packaged in decorative baskets. Price increased by 20%." << std::endl;
}

void FruitProduct::addBruise(const std::string& bruiseLocation) {
    if (bruiseLocation.empty()) {
        throw ProductException("Bruise location cannot be empty",
                               getName(), "Fruit Product", getQuantity());
    }

    bruises.push_back(bruiseLocation);
    ripenessLevel -= 5.0;
    if (ripenessLevel < 0) ripenessLevel = 0;

    updateRipenessStage();

    if (bruises.size() > 3 && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("Too many bruises for A grade fruit",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "A", "Bruised",
                               bruises.size() * 20.0);
    } else if (bruises.size() > 5) {
        setQualityGrade("C");
        throw QualityException("Excessive bruising in fruit",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "A", "Heavily bruised",
                               bruises.size() * 25.0);
    }

    std::cout << "Bruise added at: " << bruiseLocation << std::endl;
}

void FruitProduct::removeBruises() {
    if (bruises.empty()) {
        throw ProductException("No bruises to remove from " + getName(),
                               getName(), "Fruit Product", getQuantity());
    }

    std::cout << "Removing bruised fruits from " << getName() << ". Bruises at: ";
    for (const auto& bruise : bruises) {
        std::cout << bruise << " ";
    }
    std::cout << std::endl;

    // Удаление поврежденных фруктов уменьшает количество
    double lossPercentage = bruises.size() * 0.05; // 5% потерь за каждый синяк
    if (lossPercentage > 0.3) lossPercentage = 0.3; // максимум 30% потерь

    setQuantity(getQuantity() * (1.0 - lossPercentage));
    bruises.clear();

    if (getQualityGrade() == "B" || getQualityGrade() == "C") {
        setQualityGrade("A");
        std::cout << "Fruit quality restored to grade A after bruise removal." << std::endl;
    }

    std::cout << "Bruised fruits removed. New quantity: " << getQuantity() << " kg" << std::endl;
}

double FruitProduct::calculateSugarContent() const {
    double sugarPercentage = brixLevel * 0.85; // приблизительное содержание сахара
    double ripenessMultiplier = ripenessLevel / 100.0;
    double totalSugar = sugarPercentage * ripenessMultiplier * getQuantity();

    if (totalSugar > 1000.0) {
        throw ProductException("Fruit sugar content suspiciously high: " +
                               std::to_string(totalSugar) + " kg",
                               getName(), "Fruit Product", getQuantity());
    }

    return totalSugar;
}

bool FruitProduct::isReadyForSale() const {
    if (ripenessStage != "Ripe" && ripenessStage != "Very Ripe") {
        throw QualityException("Fruit not ripe enough for sale",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "Ripe", ripenessStage,
                               (70.0 - ripenessLevel) / 70.0 * 100.0);
    }

    if (!bruises.empty()) {
        throw QualityException("Fruit has bruises, not suitable for sale",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "No bruises", "Bruised",
                               bruises.size() * 30.0);
    }

    if (getQualityGrade() == "C") {
        throw QualityException("Fruit quality grade C, not suitable for regular sale",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "A/B", "C", 50.0);
    }

    return (ripenessStage == "Ripe" || ripenessStage == "Very Ripe") &&
           bruises.empty() &&
           getQualityGrade() != "C";
}

void FruitProduct::displayInfo() const {
    Product::displayInfo();
    std::cout << "=== Fruit Product Details ===" << std::endl;
    std::cout << "Fruit type: " << fruitType << std::endl;
    std::cout << "Ripeness level: " << ripenessLevel << "%" << std::endl;
    std::cout << "Ripeness stage: " << ripenessStage << std::endl;
    std::cout << "Packaged in baskets: " << (isPackagedInBaskets ? "Yes" : "No") << std::endl;
    std::cout << "Brix level: " << brixLevel << "°Bx" << std::endl;

    try {
        double sugar = calculateSugarContent();
        std::cout << "Sugar content: " << sugar << " kg total" << std::endl;
    } catch (const ProductException& e) {
        std::cout << "Sugar content: calculation error" << std::endl;
    }

    try {
        bool ready = isReadyForSale();
        std::cout << "Ready for sale: " << (ready ? "Yes" : "No") << std::endl;
    } catch (const ProductException& e) {
        std::cout << "Ready for sale: No (quality issue)" << std::endl;
    }

    if (!bruises.empty()) {
        std::cout << "Bruises at: ";
        for (size_t i = 0; i < bruises.size(); ++i) {
            std::cout << bruises[i];
            if (i < bruises.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }

    // Проверка условий хранения
    if (getStorageConditions().find("Cool") == std::string::npos) {
        throw StorageException("Fruit not stored at cool temperature",
                               getName(), "Fruit Product", getQuantity(),
                               "Cool, ventilated place", getStorageConditions(),
                               5.0, 10.0);
    }
}

void FruitProduct::updateQuality() {
    Product::updateQuality();

    // Фрукты продолжают созревать
    ripenessLevel += 2.0;
    if (ripenessLevel > 100.0) ripenessLevel = 100.0;

    updateRipenessStage();

    // Обновление категории качества на основе спелости и повреждений
    if (ripenessStage == "Ripe" && bruises.empty()) {
        if (getQualityGrade() != "A") {
            setQualityGrade("A");
        }
    } else if ((ripenessStage == "Ripe" || ripenessStage == "Very Ripe") && bruises.size() <= 2) {
        if (getQualityGrade() == "A") {
            setQualityGrade("B");
            throw QualityException("Bruises reduced fruit quality to B grade",
                                   getName(), "Fruit Product", getQuantity(),
                                   getQualityGrade(), "A", "Bruised",
                                   bruises.size() * 25.0);
        }
    } else if (ripenessStage == "Overripe" || bruises.size() > 2) {
        setQualityGrade("C");
        throw QualityException("Fruit quality degraded to C grade",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "A", "Overripe/Bruised",
                               bruises.size() > 2 ? 60.0 : 50.0);
    }

    // Автоматическая упаковка в корзины для спелых фруктов высшего сорта
    if (ripenessStage == "Ripe" && getQualityGrade() == "A" && !isPackagedInBaskets && bruises.empty()) {
        try {
            std::cout << "Auto-packaging ripe A grade fruit in baskets..." << std::endl;
            packageInBaskets();
        } catch (const ProductException& e) {
            std::cout << "Auto-packaging failed: " << e.what() << std::endl;
        }
    }

    // Проверка уровня Брикса
    if (fruitType == "Apples" && brixLevel < 10 && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("Apple Brix level too low for A grade",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "≥10°Bx",
                               std::to_string(brixLevel) + "°Bx",
                               (10.0 - brixLevel) / 10.0 * 100.0);
    }
}

void FruitProduct::package() {
    if (getQuantity() <= 0) {
        throw ProductException("Cannot package zero or negative fruit quantity",
                               getName(), "Fruit Product", getQuantity());
    }

    std::cout << "Packaging fruit product: " << getName() << std::endl;

    if (isPackagedInBaskets) {
        std::cout << "Using decorative baskets for " << getQuantity() << " kg" << std::endl;
        std::cout << "Adding protective padding to prevent bruising" << std::endl;

        if (bruises.size() > 0) {
            throw PackagingException("Bruised fruit cannot be packaged in decorative baskets",
                                     getName(), "Fruit Product", getQuantity(),
                                     "Perfect fruit basket", "Bruised fruit",
                                     getUnitOfMeasure(), "Bruises present");
        }
    } else {
        std::cout << "Using plastic crates for " << getQuantity() << " kg" << std::endl;
        std::cout << "Arranging fruits carefully to minimize damage" << std::endl;

        if (ripenessStage == "Very Ripe" || ripenessStage == "Overripe") {
            throw PackagingException("Very ripe fruit requires special packaging",
                                     getName(), "Fruit Product", getQuantity(),
                                     "Standard crate", "Soft packaging",
                                     getUnitOfMeasure(), "Very ripe - handle with care");
        }
    }

    if (ripenessStage == "Very Ripe" || ripenessStage == "Overripe") {
        std::cout << "Warning: Fruits are very ripe - handle with care!" << std::endl;
    }

    if (bruises.size() > 1) {
        throw PackagingException("Bruised fruit requires discount packaging",
                                 getName(), "Fruit Product", getQuantity(),
                                 "Regular packaging", "Discount packaging",
                                 getUnitOfMeasure(), "Multiple bruises");
    }
}

bool FruitProduct::meetsExportStandards() const {
    bool baseStandards = Product::meetsExportStandards();

    if (ripenessStage != "Ripe") {
        throw QualityException("Fruit not at perfect ripeness for export",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "Ripe", ripenessStage,
                               (80.0 - ripenessLevel) / 80.0 * 100.0);
    }

    if (!bruises.empty()) {
        throw QualityException("Fruit has bruises, not suitable for export",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "No bruises", "Bruised", 100.0);
    }

    if (brixLevel < 12) {
        throw QualityException("Fruit Brix level too low for export",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "≥12°Bx",
                               std::to_string(brixLevel) + "°Bx",
                               (12.0 - brixLevel) / 12.0 * 100.0);
    }

    if (!isPackagedInBaskets) {
        throw PackagingException("Export fruit must be packaged in baskets",
                                 getName(), "Fruit Product", getQuantity(),
                                 "Decorative basket", "Standard packaging",
                                 getUnitOfMeasure(), "Presentation requirements");
    }

    bool fruitStandards = ripenessStage == "Ripe" &&
                          bruises.empty() &&
                          brixLevel >= 12 &&
                          isPackagedInBaskets;

    return baseStandards && fruitStandards;
}

void FruitProduct::inspectQuality() {
    Product::inspectQuality();
    std::cout << "Fruit-specific inspection:" << std::endl;
    std::cout << "1. Ripeness stage: " << ripenessStage
              << " (" << ripenessLevel << "%)" << std::endl;
    std::cout << "2. Brix level: " << brixLevel << "°Bx"
              << (brixLevel >= 12 ? " (Good)" : " (Low)") << std::endl;
    std::cout << "3. Bruises count: " << bruises.size()
              << (bruises.empty() ? " (Good)" : " (Needs attention)") << std::endl;

    try {
        bool ready = isReadyForSale();
        std::cout << "4. Ready for sale: " << (ready ? "Yes" : "No") << std::endl;
    } catch (const ProductException& e) {
        std::cout << "4. Ready for sale: No (" << e.what() << ")" << std::endl;
    }

    if (!bruises.empty()) {
        throw QualityException("Fruit inspection failed - bruises found",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "No bruises", "Bruised",
                               bruises.size() * 30.0);
    }

    if (ripenessStage == "Green" || ripenessStage == "Overripe") {
        throw QualityException("Fruit inspection failed - improper ripeness",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "Ripe", ripenessStage,
                               ripenessStage == "Green" ? 60.0 : 40.0);
    }

    if (brixLevel < 8) {
        throw QualityException("Fruit inspection failed - low sugar content",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "≥8°Bx",
                               std::to_string(brixLevel) + "°Bx",
                               (8.0 - brixLevel) / 8.0 * 100.0);
    }
}

std::string FruitProduct::getFruitType() const { return fruitType; }
double FruitProduct::getRipenessLevel() const { return ripenessLevel; }
std::string FruitProduct::getRipenessStage() const { return ripenessStage; }
bool FruitProduct::getIsPackagedInBaskets() const { return isPackagedInBaskets; }
int FruitProduct::getBrixLevel() const { return brixLevel; }
std::vector<std::string> FruitProduct::getBruises() const { return bruises; }

void FruitProduct::setFruitType(const std::string& type) {
    if (type.empty()) {
        throw ProductException("Fruit type cannot be empty", getName(), "Fruit Product", getQuantity());
    }
    fruitType = type;
}

void FruitProduct::setRipenessLevel(double ripeness) {
    if (ripeness < 0 || ripeness > 100.0) {
        throw ProductException("Ripeness level must be between 0-100%: " +
                               std::to_string(ripeness), getName(), "Fruit Product", getQuantity());
    }

    ripenessLevel = ripeness;
    updateRipenessStage();

    if (ripenessStage == "Overripe" && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("Fruit overripe for A grade",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "A", "Overripe", 30.0);
    }
}

void FruitProduct::setBrixLevel(int brix) {
    if (brix < 5 || brix > 25) {
        throw ProductException("Brix level must be between 5-25°Bx: " +
                               std::to_string(brix), getName(), "Fruit Product", getQuantity());
    }

    if (fruitType == "Grapes" && brix < 18 && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("Grape Brix level too low for A grade",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "A", "Low sugar",
                               (18.0 - brix) / 18.0 * 100.0);
    }

    brixLevel = brix;
}

void FruitProduct::setIsPackagedInBaskets(bool packaged) {
    if (packaged && bruises.size() > 1) {
        throw QualityException("Bruised fruit cannot be packaged in baskets",
                               getName(), "Fruit Product", getQuantity(),
                               getQualityGrade(), "No bruises", "Bruised",
                               bruises.size() * 30.0);
    }
    isPackagedInBaskets = packaged;
}