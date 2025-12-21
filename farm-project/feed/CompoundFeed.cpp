#include "CompoundFeed.h"
#include "FeedExceptions.h"
#include <iostream>
#include <algorithm>

CompoundFeed::CompoundFeed(double quantity, const std::string& targetAnimal,
                           const std::string& pelletSize)
        : Feed("Compound Feed", quantity, 1.8) {
    // Проверки для комбикорма
    if (quantity > 50000) {
        throw FeedException("Compound feed quantity too large (max 50,000 kg): " +
                            std::to_string(quantity));
    }
    if (targetAnimal.empty()) {
        throw FeedException("Target animal cannot be empty");
    }
    if (pelletSize.empty()) {
        throw FeedException("Pellet size cannot be empty");
    }

    this->targetAnimal = targetAnimal;
    this->pelletSize = pelletSize;
    this->pelletDurability = 95.0;
    this->additiveType = "Vitamins & Minerals";
    this->isMedicated = false;
    this->medicationType = "None";
    this->fatContent = 5.0;
    this->formulaCode = "CF-2024-001";

    // Базовые ингредиенты
    ingredients = {"Corn", "Soybean Meal", "Wheat Bran", "Calcium Carbonate"};

    // Настройка в зависимости от целевого животного
    if (targetAnimal == "Chicken") {
        setProteinContent(18.0);
        ingredients.push_back("Fish Meal");
    } else if (targetAnimal == "Pig") {
        setProteinContent(16.0);
        ingredients.push_back("Barley");
    } else if (targetAnimal == "Cow") {
        setProteinContent(14.0);
        ingredients.push_back("Cottonseed Meal");
    } else {
        throw FeedException("Unknown target animal for compound feed: " + targetAnimal);
    }

    setFiberContent(8.0);
    setStorageLocation("Feed Mill Storage");
    setName(targetAnimal + " Compound Feed");
}

void CompoundFeed::displayInfo() const {
    Feed::displayInfo();
    std::cout << "--- Compound Feed Specific ---" << std::endl;
    std::cout << "Target animal: " << targetAnimal << std::endl;
    std::cout << "Pellet size: " << pelletSize << std::endl;
    std::cout << "Pellet durability: " << pelletDurability << "%" << std::endl;
    std::cout << "Additive type: " << additiveType << std::endl;
    std::cout << "Medicated: " << (isMedicated ? "Yes" : "No") << std::endl;
    if (isMedicated) {
        std::cout << "Medication type: " << medicationType << std::endl;
    }
    std::cout << "Fat content: " << fatContent << "%" << std::endl;
    std::cout << "Formula code: " << formulaCode << std::endl;

    if (ingredients.empty()) {
        throw FeedException("Compound feed has no ingredients specified");
    }

    std::cout << "Ingredients (" << ingredients.size() << "): ";
    for (size_t i = 0; i < ingredients.size(); ++i) {
        std::cout << ingredients[i];
        if (i < ingredients.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void CompoundFeed::pelletize() {
    if (getMoistureContent() < 12 || getMoistureContent() > 16) {
        throw FeedException("Moisture content must be 12-16% for pelleting, currently: " +
                            std::to_string(getMoistureContent()) + "%");
    }

    pelletDurability = 98.0;
    std::cout << "Feed has been pelletized. Pellet durability: "
              << pelletDurability << "%" << std::endl;
}

void CompoundFeed::addIngredient(const std::string& ingredient) {
    if (ingredient.empty()) {
        throw FeedException("Ingredient name cannot be empty");
    }

    // Проверка на дубликаты
    if (std::find(ingredients.begin(), ingredients.end(), ingredient) != ingredients.end()) {
        throw FeedException("Ingredient " + ingredient + " already in the formula");
    }

    ingredients.push_back(ingredient);
    std::cout << "Added " << ingredient << " to the feed formula." << std::endl;

    // Обновляем питательную ценность
    if (ingredient == "Soybean Meal") {
        setProteinContent(getProteinContent() + 3.0);
    } else if (ingredient == "Fish Meal") {
        setProteinContent(getProteinContent() + 5.0);
    } else if (ingredient == "Molasses") {
        setPricePerKg(getPricePerKg() + 0.1);
    }
}

void CompoundFeed::addMedication(const std::string& medication) {
    if (medication.empty()) {
        throw FeedException("Medication name cannot be empty");
    }
    if (isMedicated) {
        throw FeedException("Feed is already medicated with: " + medicationType);
    }

    isMedicated = true;
    medicationType = medication;
    setPricePerKg(getPricePerKg() * 1.25); // Лечебный корм дороже

    // Проверка совместимости медикаментов
    if (medication.find("Antibiotic") != std::string::npos && targetAnimal == "Chicken") {
        throw FeedException("Antibiotics not allowed in chicken feed (withdrawal period issues)");
    }

    std::cout << "Added medication: " << medication << std::endl;
}

void CompoundFeed::mixFeed() {
    if (ingredients.empty()) {
        throw FeedException("No ingredients to mix");
    }
    if (getQuantity() <= 0) {
        throw FeedException("Cannot mix zero or negative quantity of feed");
    }

    std::cout << "Mixing " << ingredients.size() << " ingredients for "
              << getQuantity() << " kg of compound feed." << std::endl;
}

std::vector<std::string> CompoundFeed::getIngredients() const { return ingredients; }
std::string CompoundFeed::getTargetAnimal() const { return targetAnimal; }
std::string CompoundFeed::getPelletSize() const { return pelletSize; }
double CompoundFeed::getPelletDurability() const { return pelletDurability; }
std::string CompoundFeed::getAdditiveType() const { return additiveType; }
bool CompoundFeed::getIsMedicated() const { return isMedicated; }
std::string CompoundFeed::getMedicationType() const { return medicationType; }
double CompoundFeed::getFatContent() const { return fatContent; }
std::string CompoundFeed::getFormulaCode() const { return formulaCode; }

void CompoundFeed::setIngredients(const std::vector<std::string>& ingredients) {
    if (ingredients.empty()) {
        throw FeedException("Ingredients list cannot be empty");
    }
    this->ingredients = ingredients;
}

void CompoundFeed::setTargetAnimal(const std::string& animal) {
    if (animal.empty()) {
        throw FeedException("Target animal cannot be empty");
    }
    targetAnimal = animal;
    setName(targetAnimal + " Compound Feed");
}

void CompoundFeed::setPelletSize(const std::string& size) {
    if (size.empty()) {
        throw FeedException("Pellet size cannot be empty");
    }
    pelletSize = size;
}

void CompoundFeed::setPelletDurability(double durability) {
    if (durability < 0 || durability > 100) {
        throw FeedException("Pellet durability must be between 0-100%: " + std::to_string(durability));
    }
    pelletDurability = durability;
}

void CompoundFeed::setAdditiveType(const std::string& additive) {
    if (additive.empty()) {
        throw FeedException("Additive type cannot be empty");
    }
    additiveType = additive;
}

void CompoundFeed::setIsMedicated(bool medicated) { isMedicated = medicated; }

void CompoundFeed::setMedicationType(const std::string& medication) {
    if (medication.empty()) {
        throw FeedException("Medication type cannot be empty");
    }
    medicationType = medication;
}

void CompoundFeed::setFatContent(double fat) {
    if (fat < 0 || fat > 20) {
        throw FeedException("Fat content must be between 0-20%: " + std::to_string(fat));
    }
    fatContent = fat;
}

void CompoundFeed::setFormulaCode(const std::string& code) {
    if (code.empty()) {
        throw FeedException("Formula code cannot be empty");
    }
    formulaCode = code;
}

double CompoundFeed::calculateCompleteNutrition() const {
    if (getProteinContent() < 10) {
        throw FeedException("Compound feed protein content too low: " +
                            std::to_string(getProteinContent()) + "% (min 10%)");
    }

    double nutrition = getProteinContent() * 2 + getFiberContent() * 1.5 + fatContent * 3;
    if (isMedicated) nutrition += 10; // Лечебный корм более питательный
    return nutrition;
}

bool CompoundFeed::isSuitableForAnimal(const std::string& animalType) const {
    if (animalType.empty()) {
        throw FeedException("Animal type cannot be empty");
    }

    // Комбикорм обычно предназначен для конкретного вида животных
    if (animalType != targetAnimal) {
        throw FeedException("This compound feed is formulated for " + targetAnimal +
                            ", not for " + animalType);
    }
    return true;
}

void CompoundFeed::createCustomFormula(const std::vector<std::string>& newIngredients) {
    if (newIngredients.empty()) {
        throw FeedException("New ingredients list cannot be empty");
    }

    // Проверка на опасные ингредиенты
    for (const auto& ingredient : newIngredients) {
        if (ingredient == "Urea" && targetAnimal == "Chicken") {
            throw FeedException("Urea is toxic to chickens!");
        }
    }

    ingredients = newIngredients;
    std::cout << "Created custom formula with " << newIngredients.size()
              << " ingredients." << std::endl;

    // Генерируем новый код формулы
    formulaCode = "CF-CUSTOM-" + std::to_string(newIngredients.size());
}

void CompoundFeed::testPelletQuality() {
    if (pelletDurability < 85) {
        throw FeedException("CRITICAL: Pellet durability too low: " +
                            std::to_string(pelletDurability) + "% (min 85% for transport)");
    } else if (pelletDurability < 90) {
        std::cout << "Warning: Low pellet durability! May crumble during handling." << std::endl;
        setQualityGrade("Low");
    } else if (pelletDurability < 95) {
        std::cout << "Pellet quality acceptable." << std::endl;
        setQualityGrade("Medium");
    } else {
        std::cout << "Excellent pellet quality." << std::endl;
        setQualityGrade("High");
    }
}