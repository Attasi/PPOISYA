#include "Meat.h"
#include "ProductExceptions.h"
#include <iostream>
#include <algorithm>

Meat::Meat(double quantity, const std::string& animalType,
           const std::string& cut)
        : Product(animalType + " Meat", quantity, calculateBasePrice(animalType)),
          animalType(animalType), cut(cut), fatPercentage(12.0),
          grade("Choice"), agingMethod("Wet-aged"), agingDays(0),
          isMarinated(false), cookingRecommendation("Grill or Pan-fry"),
          isHalalCertified(false) {

    if (quantity <= 0) {
        throw ProductException("Meat quantity must be positive: " +
                               std::to_string(quantity) + " kg",
                               getName(), "Meat", quantity);
    }

    if (quantity > 500.0) {
        throw ProductException("Meat quantity unrealistically large: " +
                               std::to_string(quantity) + " kg (max 500 kg)",
                               getName(), "Meat", quantity);
    }

    // Проверка типа животного
    std::vector<std::string> validTypes = {"Beef", "Pork", "Chicken", "Lamb", "Turkey", "Veal"};
    bool validType = false;
    for (const auto& type : validTypes) {
        if (animalType == type) {
            validType = true;
            break;
        }
    }

    if (!validType) {
        throw ProductException("Invalid animal type: " + animalType +
                               " (valid: Beef, Pork, Chicken, Lamb, Turkey, Veal)",
                               getName(), "Meat", quantity);
    }

    setUnitOfMeasure("kg");
    setStorageConditions("Refrigerated at 2°C");
    setExpirationDate("2024-01-10");
    setQualityGrade("B");
}

double Meat::calculateBasePrice(const std::string& type) {
    if (type == "Beef") return 15.0;
    if (type == "Pork") return 10.0;
    if (type == "Chicken") return 8.0;
    if (type == "Lamb") return 20.0;
    if (type == "Turkey") return 12.0;
    if (type == "Veal") return 25.0;
    return 5.0;
}

void Meat::displayInfo() const {
    Product::displayInfo();
    std::cout << "=== Meat Details ===" << std::endl;
    std::cout << "Animal Type: " << animalType << std::endl;
    std::cout << "Cut: " << cut << std::endl;
    std::cout << "Fat Percentage: " << fatPercentage << "%" << std::endl;
    std::cout << "Grade: " << grade << std::endl;
    std::cout << "Aging Method: " << agingMethod << std::endl;
    std::cout << "Aging Days: " << agingDays << std::endl;
    std::cout << "Marinated: " << (isMarinated ? "Yes" : "No") << std::endl;
    std::cout << "Cooking Recommendation: " << cookingRecommendation << std::endl;
    std::cout << "Halal Certified: " << (isHalalCertified ? "Yes" : "No") << std::endl;
    std::cout << "Tenderness Score: " << calculateTenderness() << "/10" << std::endl;
    std::cout << "Premium Cut: " << (isPremiumCut() ? "Yes" : "No") << std::endl;
}

void Meat::ageMeat(int additionalDays) {
    if (additionalDays <= 0) {
        throw ProductException("Aging days must be positive: " +
                               std::to_string(additionalDays),
                               getName(), "Meat", getQuantity());
    }

    if (animalType != "Beef" && animalType != "Lamb") {
        throw ProductException(animalType + " cannot be dry-aged",
                               getName(), "Meat", getQuantity());
    }

    if (isMarinated) {
        throw ProductException("Cannot age marinated meat",
                               getName(), "Meat", getQuantity());
    }

    agingDays += additionalDays;
    agingMethod = "Dry-aged";

    if (agingDays > 45) {
        throw ExpirationException("Meat aged too long",
                                  getName(), "Meat", getQuantity(),
                                  getProductionDate(), getExpirationDate(),
                                  "2024-01-15", agingDays - 30);
    }

    // Улучшение качества при выдержке
    if (agingDays >= 21) {
        grade = "Prime";
        setQualityGrade("A");
        std::cout << animalType << " aged to " << agingDays << " days. Upgraded to Prime grade." << std::endl;
    } else if (agingDays >= 14) {
        grade = "Choice";
        setQualityGrade("B");
        std::cout << animalType << " aged to " << agingDays << " days. Choice grade." << std::endl;
    } else {
        grade = "Select";
        setQualityGrade("C");
        std::cout << animalType << " aged to " << agingDays << " days. Select grade." << std::endl;
    }

    // Проверка на перезревание
    if (agingDays > 35 && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("Meat over-aged for Prime grade",
                               getName(), "Meat", getQuantity(), getQualityGrade(),
                               "A", "Over-aged", 25.0);
    }
}

void Meat::marinate() {
    if (isMarinated) {
        throw ProductException(getName() + " is already marinated",
                               getName(), "Meat", getQuantity());
    }

    if (agingDays > 0 && agingMethod == "Dry-aged") {
        throw ProductException("Cannot marinate dry-aged meat",
                               getName(), "Meat", getQuantity());
    }

    std::cout << "Marinating " << getName() << "..." << std::endl;
    isMarinated = true;

    // Маринование уменьшает срок годности
    setExpirationDate("2024-01-05");
    cookingRecommendation = "Slow cook or Braise";

    std::cout << "Meat marinated. New expiration date: " << getExpirationDate() << std::endl;
}

void Meat::trimFat() {
    double trimAmount = fatPercentage * 0.3; // Убираем 30% жира

    if (trimAmount <= 0) {
        throw ProductException("No fat to trim from " + getName(),
                               getName(), "Meat", getQuantity());
    }

    fatPercentage -= trimAmount;
    if (fatPercentage < 0) fatPercentage = 0;

    // Потеря веса при обрезке жира
    double weightLoss = getQuantity() * (trimAmount / 100.0 * 0.8); // 80% от обрезанного жира - вес
    setQuantity(getQuantity() - weightLoss);

    std::cout << "Trimmed " << trimAmount << "% fat from " << getName()
              << ". New fat percentage: " << fatPercentage << "%" << std::endl;
    std::cout << "Weight reduced by " << weightLoss << " kg" << std::endl;

    // Улучшение качества после обрезки жира
    if (fatPercentage < 10.0 && grade == "Select") {
        grade = "Choice";
        throw QualityException("Fat trimming improved meat grade",
                               getName(), "Meat", getQuantity(), getQualityGrade(),
                               "Select", "Choice", 20.0);
    }
}

void Meat::vacuumPack() {
    std::cout << "Vacuum packing " << getQuantity() << " kg of " << getName() << "..." << std::endl;

    if (getQuantity() <= 0) {
        throw ProductException("Cannot vacuum pack zero or negative meat quantity",
                               getName(), "Meat", getQuantity());
    }

    if (getQuantity() > 100.0) {
        throw PackagingException("Meat quantity too large for vacuum packaging",
                                 getName(), "Meat", getQuantity(),
                                 "Vacuum bag", "Industrial packaging",
                                 getUnitOfMeasure(), "Weight exceeds 100 kg limit");
    }

    // Вакуумная упаковка увеличивает срок годности
    if (!isMarinated) {
        setExpirationDate("2024-02-01");
        std::cout << "Vacuum packed. New expiration date: " << getExpirationDate() << std::endl;
    } else {
        std::cout << "Vacuum packed marinated meat. Must be consumed quickly." << std::endl;
    }
}

// Геттеры
std::string Meat::getAnimalType() const { return animalType; }
std::string Meat::getCut() const { return cut; }
double Meat::getFatPercentage() const { return fatPercentage; }
std::string Meat::getGrade() const { return grade; }
std::string Meat::getAgingMethod() const { return agingMethod; }
int Meat::getAgingDays() const { return agingDays; }
bool Meat::getIsMarinated() const { return isMarinated; }
std::string Meat::getCookingRecommendation() const { return cookingRecommendation; }
bool Meat::getIsHalalCertified() const { return isHalalCertified; }

// Сеттеры
void Meat::setAnimalType(const std::string& type) {
    std::vector<std::string> validTypes = {"Beef", "Pork", "Chicken", "Lamb", "Turkey", "Veal"};
    bool validType = false;
    for (const auto& valid : validTypes) {
        if (type == valid) {
            validType = true;
            break;
        }
    }

    if (!validType) {
        throw ProductException("Invalid animal type: " + type,
                               getName(), "Meat", getQuantity());
    }

    // Изменение типа животного меняет цену
    animalType = type;
    setPricePerUnit(calculateBasePrice(type));
}

void Meat::setCut(const std::string& meatCut) {
    if (meatCut.empty()) {
        throw ProductException("Meat cut cannot be empty", getName(), "Meat", getQuantity());
    }
    cut = meatCut;
}

void Meat::setFatPercentage(double percentage) {
    if (percentage < 0 || percentage > 100.0) {
        throw ProductException("Fat percentage must be between 0-100%: " +
                               std::to_string(percentage),
                               getName(), "Meat", getQuantity());
    }

    if (animalType == "Chicken" && percentage > 15.0) {
        throw QualityException("Chicken fat percentage too high",
                               getName(), "Meat", getQuantity(), getQualityGrade(),
                               "≤15%", std::to_string(percentage) + "%",
                               (percentage - 15.0) / 15.0 * 100.0);
    }

    fatPercentage = percentage;
}

void Meat::setGrade(const std::string& meatGrade) {
    std::vector<std::string> validGrades = {"Prime", "Choice", "Select", "Standard"};
    bool validGrade = false;
    for (const auto& valid : validGrades) {
        if (meatGrade == valid) {
            validGrade = true;
            break;
        }
    }

    if (!validGrade) {
        throw ProductException("Invalid meat grade: " + meatGrade,
                               getName(), "Meat", getQuantity());
    }

    if (meatGrade == "Prime" && agingDays < 21) {
        throw QualityException("Prime grade requires at least 21 days aging",
                               getName(), "Meat", getQuantity(), getQualityGrade(),
                               "≥21 days", std::to_string(agingDays) + " days",
                               (21.0 - agingDays) / 21.0 * 100.0);
    }

    grade = meatGrade;
}

void Meat::setAgingMethod(const std::string& method) {
    if (method != "Dry-aged" && method != "Wet-aged" && method != "Not aged") {
        throw ProductException("Invalid aging method: " + method,
                               getName(), "Meat", getQuantity());
    }
    agingMethod = method;
}

void Meat::setAgingDays(int days) {
    if (days < 0) {
        throw ProductException("Aging days cannot be negative: " +
                               std::to_string(days), getName(), "Meat", getQuantity());
    }

    if (days > 60) {
        throw ExpirationException("Meat aged too long",
                                  getName(), "Meat", getQuantity(),
                                  getProductionDate(), getExpirationDate(),
                                  "2024-01-15", days - 30);
    }

    agingDays = days;
}

void Meat::setIsMarinated(bool marinated) {
    if (marinated && agingDays > 0 && agingMethod == "Dry-aged") {
        throw ProductException("Cannot marinate dry-aged meat",
                               getName(), "Meat", getQuantity());
    }
    isMarinated = marinated;
}

void Meat::setCookingRecommendation(const std::string& recommendation) {
    if (recommendation.empty()) {
        throw ProductException("Cooking recommendation cannot be empty",
                               getName(), "Meat", getQuantity());
    }
    cookingRecommendation = recommendation;
}

void Meat::setIsHalalCertified(bool halal) {
    if (halal && animalType == "Pork") {
        throw ProductException("Pork cannot be Halal certified",
                               getName(), "Meat", getQuantity());
    }
    isHalalCertified = halal;
}

double Meat::calculateTenderness() const {
    double tenderness = 5.0; // базовый уровень

    // Влияние выдержки
    if (agingDays > 0 && agingMethod == "Dry-aged") {
        tenderness += agingDays * 0.1;
    }

    // Влияние отруба
    if (cut.find("Tenderloin") != std::string::npos ||
        cut.find("Filet") != std::string::npos) {
        tenderness += 3.0;
    } else if (cut.find("Ribeye") != std::string::npos ||
               cut.find("Sirloin") != std::string::npos) {
        tenderness += 2.0;
    }

    // Влияние мраморности (процента жирности)
    if (fatPercentage >= 10.0 && fatPercentage <= 20.0) {
        tenderness += 1.0;
    }

    // Ограничение от 1 до 10
    if (tenderness > 10.0) tenderness = 10.0;
    if (tenderness < 1.0) tenderness = 1.0;

    return tenderness;
}

void Meat::sliceIntoPortions(double portionSize) {
    if (portionSize <= 0) {
        throw ProductException("Portion size must be positive: " +
                               std::to_string(portionSize) + " kg",
                               getName(), "Meat", getQuantity());
    }

    if (portionSize > getQuantity()) {
        throw ProductException("Portion size cannot exceed total quantity: " +
                               std::to_string(portionSize) + " kg > " +
                               std::to_string(getQuantity()) + " kg",
                               getName(), "Meat", getQuantity());
    }

    int portions = static_cast<int>(getQuantity() / portionSize);
    double remainder = getQuantity() - (portions * portionSize);

    std::cout << "Slicing " << getName() << " into " << portions
              << " portions of " << portionSize << " kg each" << std::endl;

    if (remainder > 0) {
        std::cout << "Remainder: " << remainder << " kg (can be used for ground meat)" << std::endl;
    }

    // Уменьшение качества при нарезке
    if (portions > 10 && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("Excessive slicing reduces meat quality",
                               getName(), "Meat", getQuantity(), getQualityGrade(),
                               "A", "Sliced", 15.0);
    }
}

bool Meat::isPremiumCut() const {
    std::vector<std::string> premiumCuts = {
            "Tenderloin", "Filet Mignon", "Ribeye", "Sirloin",
            "Strip Steak", "Porterhouse", "T-Bone"
    };

    for (const auto& premiumCut : premiumCuts) {
        if (cut.find(premiumCut) != std::string::npos) {
            return true;
        }
    }
    return false;
}

void Meat::recommendCookingMethod() {
    std::string method;

    if (isPremiumCut()) {
        if (fatPercentage > 15.0) {
            method = "Grill to medium-rare";
        } else {
            method = "Pan-sear and finish in oven";
        }
    } else if (animalType == "Chicken" || animalType == "Turkey") {
        method = "Roast at 180°C until internal temperature 74°C";
    } else if (animalType == "Pork") {
        method = "Slow roast at 160°C until tender";
    } else {
        method = "Braise or stew for tenderness";
    }

    if (isMarinated) {
        method += " (already marinated)";
    }

    cookingRecommendation = method;
    std::cout << "Recommended cooking method for " << getName() << ": " << method << std::endl;
}