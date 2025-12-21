#include "Milk.h"
#include "ProductExceptions.h"
#include <iostream>
#include <algorithm>
#include <vector>

Milk::Milk(double quantity, double fatContent, const std::string& sourceAnimal)
        : Product(sourceAnimal + " Milk", quantity, calculateBasePrice(sourceAnimal, fatContent)),
          fatContent(fatContent), sourceAnimal(sourceAnimal), isPasteurized(true),
          packagingType("Carton"), lactoseContent(48), // 4.8 г на 100мл * 10 для целых чисел
          homogenizationLevel("Full"), isFortified(false),
          milkType(fatContent >= 3.0 ? "Whole" : fatContent >= 1.5 ? "2%" : "Skim"),
          bacterialCount(10000) {

    if (quantity <= 0) {
        throw ProductException("Milk quantity must be positive: " +
                               std::to_string(quantity) + " liters",
                               getName(), "Milk", quantity);
    }

    if (quantity > 1000.0) {
        throw ProductException("Milk quantity unrealistically large: " +
                               std::to_string(quantity) + " liters (max 1000l)",
                               getName(), "Milk", quantity);
    }

    if (fatContent < 0 || fatContent > 10.0) {
        throw ProductException("Milk fat content must be between 0-10%: " +
                               std::to_string(fatContent), getName(), "Milk", quantity);
    }

    // Проверка типа животного
    if (sourceAnimal != "Cow" && sourceAnimal != "Goat" && sourceAnimal != "Sheep") {
        throw ProductException("Invalid source animal: " + sourceAnimal +
                               " (valid: Cow, Goat, Sheep)",
                               getName(), "Milk", quantity);
    }

    setUnitOfMeasure("liters");
    setStorageConditions("Refrigerated at 4°C");
    setExpirationDate("2024-01-07");
    setQualityGrade("A");
}

double Milk::calculateBasePrice(const std::string& source, double fat) {
    double basePrice = 1.5;

    if (source == "Goat") basePrice = 3.0;
    else if (source == "Sheep") basePrice = 4.0;

    // Премиум за более высокое содержание жира
    if (fat > 3.5) basePrice += 0.5;

    return basePrice;
}

void Milk::displayInfo() const {
    Product::displayInfo();
    std::cout << "=== Milk Details ===" << std::endl;
    std::cout << "Fat Content: " << fatContent << "%" << std::endl;
    std::cout << "Source Animal: " << sourceAnimal << std::endl;
    std::cout << "Pasteurized: " << (isPasteurized ? "Yes" : "No") << std::endl;
    std::cout << "Packaging Type: " << packagingType << std::endl;
    std::cout << "Lactose Content: " << lactoseContent / 10.0 << "g/100ml" << std::endl;
    std::cout << "Homogenization Level: " << homogenizationLevel << std::endl;
    std::cout << "Fortified: " << (isFortified ? "Yes" : "No") << std::endl;
    std::cout << "Milk Type: " << milkType << std::endl;
    std::cout << "Bacterial Count: " << bacterialCount << " CFU/ml" << std::endl;
    std::cout << "Nutritional Value: " << calculateNutritionalValue() << " kcal/100ml" << std::endl;
    std::cout << "Safe for Consumption: " << (isSafeForConsumption() ? "Yes" : "No") << std::endl;

    // Проверка условий хранения
    if (getStorageConditions().find("Refrigerated") == std::string::npos) {
        throw StorageException("Milk not stored at proper temperature",
                               getName(), "Milk", getQuantity(),
                               "Refrigerated at 4°C", getStorageConditions(),
                               10.0, 20.0);
    }
}

void Milk::pasteurize() {
    if (isPasteurized) {
        throw ProductException(getName() + " is already pasteurized",
                               getName(), "Milk", getQuantity());
    }

    std::cout << "Pasteurizing milk at 72°C for 15 seconds..." << std::endl;
    isPasteurized = true;
    bacterialCount = 1000; // Снижение бактериального счета

    if (homogenizationLevel == "None") {
        homogenizationLevel = "Partial";
    }

    // Увеличение срока годности после пастеризации
    setExpirationDate("2024-01-14");
    setQualityGrade("A");

    std::cout << "Milk pasteurized. Bacterial count reduced to " << bacterialCount
              << " CFU/ml" << std::endl;
    std::cout << "New expiration date: " << getExpirationDate() << std::endl;
}

void Milk::homogenize() {
    if (homogenizationLevel == "Full") {
        throw ProductException(getName() + " is already fully homogenized",
                               getName(), "Milk", getQuantity());
    }

    std::cout << "Homogenizing milk..." << std::endl;

    if (homogenizationLevel == "None") {
        homogenizationLevel = "Partial";
    } else if (homogenizationLevel == "Partial") {
        homogenizationLevel = "Full";
    }

    // Гомогенизация улучшает качество
    if (getQualityGrade() == "B" && isPasteurized) {
        setQualityGrade("A");
        throw QualityException("Homogenization improved milk quality",
                               getName(), "Milk", getQuantity(), getQualityGrade(),
                               "B", "A", 15.0);
    }

    std::cout << "Milk homogenization level: " << homogenizationLevel << std::endl;
}

void Milk::fortify() {
    if (isFortified) {
        throw ProductException(getName() + " is already fortified",
                               getName(), "Milk", getQuantity());
    }

    if (!isPasteurized) {
        throw ProductException("Cannot fortify unpasteurized milk",
                               getName(), "Milk", getQuantity());
    }

    std::cout << "Fortifying milk with vitamins A and D..." << std::endl;
    isFortified = true;

    // Обогащение повышает цену
    setPricePerUnit(getPricePerUnit() * 1.2);

    std::cout << "Milk fortified. Price increased by 20%." << std::endl;
}

void Milk::checkFreshness() const {
    if (!isPasteurized) {
        throw QualityException("Unpasteurized milk may not be fresh",
                               getName(), "Milk", getQuantity(), getQualityGrade(),
                               "Pasteurized", "Raw", 50.0);
    }

    if (bacterialCount > 50000) {
        throw QualityException("Milk bacterial count too high",
                               getName(), "Milk", getQuantity(), getQualityGrade(),
                               "≤50,000 CFU/ml", std::to_string(bacterialCount) + " CFU/ml",
                               (bacterialCount - 50000) / 50000.0 * 100.0);
    }

    // Проверка по типу молока и содержанию жира
    if (milkType == "Whole" && fatContent < 3.0) {
        throw QualityException("Whole milk should have at least 3% fat",
                               getName(), "Milk", getQuantity(), getQualityGrade(),
                               "≥3%", std::to_string(fatContent) + "%",
                               (3.0 - fatContent) / 3.0 * 100.0);
    }

    std::cout << getName() << " is fresh and safe for consumption." << std::endl;
}

// Геттеры
double Milk::getFatContent() const { return fatContent; }
std::string Milk::getSourceAnimal() const { return sourceAnimal; }
bool Milk::getIsPasteurized() const { return isPasteurized; }
std::string Milk::getPackagingType() const { return packagingType; }
int Milk::getLactoseContent() const { return lactoseContent; }
std::string Milk::getHomogenizationLevel() const { return homogenizationLevel; }
bool Milk::getIsFortified() const { return isFortified; }
std::string Milk::getMilkType() const { return milkType; }
int Milk::getBacterialCount() const { return bacterialCount; }

// Сеттеры
void Milk::setFatContent(double fat) {
    if (fat < 0 || fat > 10.0) {
        throw ProductException("Milk fat content must be between 0-10%: " +
                               std::to_string(fat), getName(), "Milk", getQuantity());
    }

    // Обновление типа молока на основе содержания жира
    std::string oldType = milkType;
    if (fat >= 3.0) milkType = "Whole";
    else if (fat >= 1.5) milkType = "2%";
    else milkType = "Skim";

    if (oldType == "Whole" && milkType != "Whole") {
        throw QualityException("Cannot downgrade from Whole milk type",
                               getName(), "Milk", getQuantity(), getQualityGrade(),
                               "Whole", milkType, 40.0);
    }

    fatContent = fat;
}

void Milk::setSourceAnimal(const std::string& animal) {
    if (animal != "Cow" && animal != "Goat" && animal != "Sheep") {
        throw ProductException("Invalid source animal: " + animal +
                               " (valid: Cow, Goat, Sheep)",
                               getName(), "Milk", getQuantity());
    }

    std::string oldName = getName();
    sourceAnimal = animal;
    setName(animal + " Milk");

    // Обновление цены при изменении источника
    setPricePerUnit(calculateBasePrice(animal, fatContent));

    std::cout << "Source animal changed from " << oldName << " to " << getName() << std::endl;
}

void Milk::setIsPasteurized(bool pasteurized) {
    if (!pasteurized && getQuantity() > 10.0) {
        throw ProductException("Large quantity of milk must be pasteurized: " +
                               std::to_string(getQuantity()) + " liters",
                               getName(), "Milk", getQuantity());
    }

    if (!pasteurized && bacterialCount < 10000) {
        bacterialCount = 50000; // Сырое молоко имеет более высокий бактериальный счет
    }

    isPasteurized = pasteurized;
}

void Milk::setPackagingType(const std::string& packaging) {
    std::vector<std::string> validPackaging = {"Bottle", "Carton", "Bag", "Can"};
    bool valid = false;
    for (const auto& validType : validPackaging) {
        if (packaging == validType) {
            valid = true;
            break;
        }
    }

    if (!valid) {
        throw ProductException("Invalid packaging type: " + packaging,
                               getName(), "Milk", getQuantity());
    }

    if (packaging == "Bag" && getQuantity() > 1.0) {
        throw PackagingException("Bags not suitable for large quantities",
                                 getName(), "Milk", getQuantity(),
                                 "Carton/Bottle", "Bag",
                                 getUnitOfMeasure(), "Volume exceeds 1 liter");
    }

    packagingType = packaging;
}

void Milk::setLactoseContent(int lactose) {
    if (lactose < 0 || lactose > 100) { // 0-10g/100ml в целых числах * 10
        throw ProductException("Lactose content must be between 0-10g/100ml: " +
                               std::to_string(lactose/10.0), getName(), "Milk", getQuantity());
    }

    if (sourceAnimal == "Goat" && lactose > 42) { // 4.2г/100мл
        throw QualityException("Goat milk lactose content too high",
                               getName(), "Milk", getQuantity(), getQualityGrade(),
                               "≤4.2g/100ml", std::to_string(lactose/10.0) + "g/100ml",
                               (lactose - 42) / 42.0 * 100.0);
    }

    lactoseContent = lactose;
}

void Milk::setHomogenizationLevel(const std::string& level) {
    if (level != "None" && level != "Partial" && level != "Full") {
        throw ProductException("Invalid homogenization level: " + level +
                               " (valid: None, Partial, Full)",
                               getName(), "Milk", getQuantity());
    }

    if (level == "Full" && !isPasteurized) {
        throw ProductException("Cannot fully homogenize unpasteurized milk",
                               getName(), "Milk", getQuantity());
    }

    homogenizationLevel = level;
}

void Milk::setIsFortified(bool fortified) {
    if (fortified && !isPasteurized) {
        throw ProductException("Cannot fortify unpasteurized milk",
                               getName(), "Milk", getQuantity());
    }
    isFortified = fortified;
}

void Milk::setMilkType(const std::string& type) {
    std::vector<std::string> validTypes = {"Whole", "2%", "Skim", "Raw"};
    bool valid = false;
    for (const auto& validType : validTypes) {
        if (type == validType) {
            valid = true;
            break;
        }
    }

    if (!valid) {
        throw ProductException("Invalid milk type: " + type,
                               getName(), "Milk", getQuantity());
    }

    // Обновление содержания жира на основе типа
    if (type == "Whole" && fatContent < 3.0) {
        fatContent = 3.2;
    } else if (type == "2%" && (fatContent < 1.5 || fatContent > 2.5)) {
        fatContent = 2.0;
    } else if (type == "Skim" && fatContent > 0.5) {
        fatContent = 0.2;
    }

    milkType = type;
}

void Milk::setBacterialCount(int count) {
    if (count < 0 || count > 1000000) {
        throw ProductException("Bacterial count must be between 0-1,000,000 CFU/ml: " +
                               std::to_string(count), getName(), "Milk", getQuantity());
    }

    if (isPasteurized && count > 50000) {
        throw QualityException("Pasteurized milk bacterial count too high",
                               getName(), "Milk", getQuantity(), getQualityGrade(),
                               "≤50,000 CFU/ml", std::to_string(count) + " CFU/ml",
                               (count - 50000) / 50000.0 * 100.0);
    }

    bacterialCount = count;
}

double Milk::calculateNutritionalValue() const {
    // Расчет пищевой ценности на 100мл
    double calories = (fatContent * 9) +
                      (lactoseContent / 10.0 * 4) + // лактоза в граммах
                      (3.5 * 4); // приблизительное содержание белка 3.5г

    if (isFortified) {
        calories += 5; // дополнительные калории от витаминов
    }

    return calories;
}

void Milk::makeCheese(double amount) {
    if (amount <= 0) {
        throw ProductException("Cheese amount must be positive: " +
                               std::to_string(amount) + " kg",
                               getName(), "Milk", getQuantity());
    }

    if (amount > getQuantity() * 0.1) { // ~10% выхода сыра
        throw ProductException("Cheese yield too high: " + std::to_string(amount) +
                               " kg from " + std::to_string(getQuantity()) + " liters",
                               getName(), "Milk", getQuantity());
    }

    if (fatContent < 3.0) {
        throw QualityException("Low-fat milk not suitable for cheese making",
                               getName(), "Milk", getQuantity(), getQualityGrade(),
                               "≥3% fat", std::to_string(fatContent) + "%",
                               (3.0 - fatContent) / 3.0 * 100.0);
    }

    double milkUsed = amount * 10; // Примерно 10 литров молока на 1 кг сыра
    if (milkUsed > getQuantity()) {
        milkUsed = getQuantity();
    }

    setQuantity(getQuantity() - milkUsed);

    std::cout << "Made " << amount << " kg of cheese from " << milkUsed
              << " liters of milk" << std::endl;
    std::cout << "Remaining milk: " << getQuantity() << " liters" << std::endl;
}

bool Milk::isSafeForConsumption() const {
    if (!isPasteurized && bacterialCount > 100000) {
        return false;
    }

    if (lactoseContent > 50 && sourceAnimal == "Goat") { // 5.0г/100мл
        throw QualityException("Goat milk lactose content unusually high",
                               getName(), "Milk", getQuantity(), getQualityGrade(),
                               "≤5.0g/100ml", std::to_string(lactoseContent/10.0) + "g/100ml",
                               (lactoseContent - 50) / 50.0 * 100.0);
    }

    return isPasteurized || bacterialCount <= 50000;
}

void Milk::adjustFatContent(double targetFat) {
    if (targetFat < 0 || targetFat > 10.0) {
        throw ProductException("Target fat content must be between 0-10%: " +
                               std::to_string(targetFat), getName(), "Milk", getQuantity());
    }

    if (targetFat == fatContent) {
        std::cout << "Milk already at " << targetFat << "% fat" << std::endl;
        return;
    }

    std::cout << "Adjusting fat content from " << fatContent << "% to "
              << targetFat << "%" << std::endl;

    double oldFat = fatContent;
    fatContent = targetFat;

    // Обновление типа молока
    if (targetFat >= 3.0) milkType = "Whole";
    else if (targetFat >= 1.5) milkType = "2%";
    else milkType = "Skim";

    // Проверка качества
    if (oldFat >= 3.0 && targetFat < 3.0 && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("Fat reduction lowered milk quality",
                               getName(), "Milk", getQuantity(), getQualityGrade(),
                               "A", "B", 15.0);
    }

    std::cout << "Fat content adjusted. New milk type: " << milkType << std::endl;
}