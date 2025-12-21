#include "Wool.h"
#include "ProductExceptions.h"
#include <iostream>
#include <algorithm>
#include <vector>

Wool::Wool(double quantity, const std::string& sheepBreed,
           const std::string& woolType)
        : Product(sheepBreed + " Wool", quantity, calculateBasePrice(sheepBreed, woolType)),
          sheepBreed(sheepBreed), woolType(woolType), fiberDiameter(20.0),
          color("Natural"), stapleLength(80), processingStage("Raw"),
          lanolinContent(10.0), isOrganic(true), spinningQuality("Medium") {

    setUnitOfMeasure("kg");
    setStorageConditions("Dry, ventilated area");
    setExpirationDate("2025-12-31");
    setQualityGrade("B");

    if (quantity <= 0) {
        throw ProductException("Wool quantity must be positive: " +
                               std::to_string(quantity) + " kg",
                               getName(), "Wool", quantity);
    }

    if (quantity > 1000.0) {
        throw ProductException("Wool quantity unrealistically large: " +
                               std::to_string(quantity) + " kg (max 1000 kg)",
                               getName(), "Wool", quantity);
    }

    // Проверка породы овец
    std::vector<std::string> validBreeds = {"Merino", "Shetland", "Romney", "Corriedale",
                                            "Border Leicester", "Bluefaced Leicester"};
    bool validBreed = false;
    for (const auto& breed : validBreeds) {
        if (sheepBreed == breed) {
            validBreed = true;
            break;
        }
    }

    if (!validBreed) {
        throw ProductException("Invalid sheep breed: " + sheepBreed +
                               " (valid: Merino, Shetland, Romney, Corriedale, Border Leicester, Bluefaced Leicester)",
                               getName(), "Wool", quantity);
    }

    // Проверка типа шерсти
    if (woolType != "Fine" && woolType != "Medium" && woolType != "Coarse") {
        throw ProductException("Invalid wool type: " + woolType +
                               " (valid: Fine, Medium, Coarse)",
                               getName(), "Wool", quantity);
    }

    // Установка диаметра волокна на основе типа
    if (woolType == "Fine") fiberDiameter = 18.0;
    else if (woolType == "Medium") fiberDiameter = 25.0;
    else fiberDiameter = 35.0;

    // Установка длины штапеля на основе породы
    if (sheepBreed == "Merino") stapleLength = 70;
    else if (sheepBreed == "Shetland") stapleLength = 90;
    else stapleLength = 100;
}

double Wool::calculateBasePrice(const std::string& breed, const std::string& type) {
    double basePrice = 15.0;

    // Цена в зависимости от породы
    if (breed == "Merino") basePrice = 25.0;
    else if (breed == "Shetland") basePrice = 20.0;
    else if (breed == "Bluefaced Leicester") basePrice = 22.0;

    // Премиум за тонкую шерсть
    if (type == "Fine") basePrice += 10.0;
    else if (type == "Medium") basePrice += 5.0;

    return basePrice;
}

void Wool::displayInfo() const {
    Product::displayInfo();
    std::cout << "=== Wool Details ===" << std::endl;
    std::cout << "Sheep Breed: " << sheepBreed << std::endl;
    std::cout << "Wool Type: " << woolType << std::endl;
    std::cout << "Fiber Diameter: " << fiberDiameter << " microns" << std::endl;
    std::cout << "Color: " << color << std::endl;
    std::cout << "Staple Length: " << stapleLength << " mm" << std::endl;
    std::cout << "Processing Stage: " << processingStage << std::endl;
    std::cout << "Lanolin Content: " << lanolinContent << "%" << std::endl;
    std::cout << "Organic: " << (isOrganic ? "Yes" : "No") << std::endl;
    std::cout << "Spinning Quality: " << spinningQuality << std::endl;
    std::cout << "Warmth Rating: " << calculateWarmthRating() << "/10" << std::endl;
    std::cout << "Suitable for Clothing: " << (isSuitableForClothing() ? "Yes" : "No") << std::endl;

    // Проверка условий хранения
    if (getStorageConditions().find("Dry") == std::string::npos) {
        throw StorageException("Wool not stored in dry conditions",
                               getName(), "Wool", getQuantity(),
                               "Dry, ventilated area", getStorageConditions(),
                               0.0, 30.0);
    }
}

void Wool::washWool() {
    if (processingStage != "Raw") {
        throw ProductException("Wool already washed or further processed",
                               getName(), "Wool", getQuantity());
    }

    std::cout << "Washing wool to remove dirt and lanolin..." << std::endl;
    processingStage = "Washed";
    lanolinContent *= 0.3; // Удаление 70% ланолина при мытье

    // Мытье уменьшает вес из-за удаления загрязнений
    double weightLoss = 0.2; // 20% потери веса
    setQuantity(getQuantity() * (1.0 - weightLoss));

    // Улучшение качества после мытья
    if (getQualityGrade() == "C") {
        setQualityGrade("B");
        throw QualityException("Washing improved wool quality",
                               getName(), "Wool", getQuantity(), getQualityGrade(),
                               "C", "B", 25.0);
    }

    std::cout << "Wool washed. Lanolin content reduced to " << lanolinContent
              << "%" << std::endl;
}

void Wool::cardWool() {
    if (processingStage != "Washed") {
        throw ProductException("Wool must be washed before carding",
                               getName(), "Wool", getQuantity());
    }

    if (fiberDiameter > 30.0) {
        throw QualityException("Coarse wool not suitable for carding",
                               getName(), "Wool", getQuantity(), getQualityGrade(),
                               "≤30 microns", std::to_string(fiberDiameter) + " microns",
                               (fiberDiameter - 30.0) / 30.0 * 100.0);
    }

    std::cout << "Carding wool to align fibers..." << std::endl;
    processingStage = "Carded";
    spinningQuality = "Good";

    // Кардование немного уменьшает вес
    setQuantity(getQuantity() * 0.97);

    // Улучшение качества после кардования
    if (getQualityGrade() == "B") {
        setQualityGrade("A");
        throw QualityException("Carding improved wool quality to A grade",
                               getName(), "Wool", getQuantity(), getQualityGrade(),
                               "B", "A", 15.0);
    }

    std::cout << "Wool carded. Ready for spinning." << std::endl;
}

void Wool::spinIntoYarn() {
    if (processingStage != "Carded") {
        throw ProductException("Wool must be carded before spinning",
                               getName(), "Wool", getQuantity());
    }

    if (stapleLength < 50) {
        throw QualityException("Short staple length not suitable for spinning",
                               getName(), "Wool", getQuantity(), getQualityGrade(),
                               "≥50 mm", std::to_string(stapleLength) + " mm",
                               (50.0 - stapleLength) / 50.0 * 100.0);
    }

    std::cout << "Spinning wool into yarn..." << std::endl;
    processingStage = "Spun";

    // Расчет длины пряжи (примерно 500 м/кг для средней толщины)
    double yarnLength = getQuantity() * 500.0;

    // Установка качества прядения
    if (fiberDiameter < 22.0) {
        spinningQuality = "Excellent";
    } else if (fiberDiameter < 28.0) {
        spinningQuality = "Good";
    } else {
        spinningQuality = "Fair";
    }

    std::cout << "Spun " << getQuantity() << " kg of wool into approximately "
              << yarnLength << " meters of yarn." << std::endl;
    std::cout << "Spinning quality: " << spinningQuality << std::endl;
}

void Wool::dyeWool(const std::string& newColor) {
    if (newColor.empty()) {
        throw ProductException("Color cannot be empty",
                               getName(), "Wool", getQuantity());
    }

    if (processingStage != "Washed" && processingStage != "Carded") {
        throw ProductException("Wool must be washed before dyeing",
                               getName(), "Wool", getQuantity());
    }

    std::cout << "Dyeing wool from " << color << " to " << newColor << "..." << std::endl;
    color = newColor;

    // Красители могут немного утяжелять шерсть
    setQuantity(getQuantity() * 1.05);

    // Дополнительная проверка для натуральной органической шерсти
    if (isOrganic && newColor != "Natural") {
        setIsOrganic(false);
        std::cout << "Note: Dyed wool is no longer considered organic." << std::endl;
    }

    std::cout << "Wool dyed to " << color << " color." << std::endl;
}

// Геттеры
std::string Wool::getSheepBreed() const { return sheepBreed; }
std::string Wool::getWoolType() const { return woolType; }
double Wool::getFiberDiameter() const { return fiberDiameter; }
std::string Wool::getColor() const { return color; }
int Wool::getStapleLength() const { return stapleLength; }
std::string Wool::getProcessingStage() const { return processingStage; }
double Wool::getLanolinContent() const { return lanolinContent; }
bool Wool::getIsOrganic() const { return isOrganic; }
std::string Wool::getSpinningQuality() const { return spinningQuality; }

// Сеттеры
void Wool::setSheepBreed(const std::string& breed) {
    std::vector<std::string> validBreeds = {"Merino", "Shetland", "Romney", "Corriedale",
                                            "Border Leicester", "Bluefaced Leicester"};
    bool validBreed = false;
    for (const auto& valid : validBreeds) {
        if (breed == valid) {
            validBreed = true;
            break;
        }
    }

    if (!validBreed) {
        throw ProductException("Invalid sheep breed: " + breed,
                               getName(), "Wool", getQuantity());
    }

    // Изменение породы меняет цену
    sheepBreed = breed;
    setPricePerUnit(calculateBasePrice(breed, woolType));
}

void Wool::setWoolType(const std::string& type) {
    if (type != "Fine" && type != "Medium" && type != "Coarse") {
        throw ProductException("Invalid wool type: " + type +
                               " (valid: Fine, Medium, Coarse)",
                               getName(), "Wool", getQuantity());
    }

    // Обновление диаметра волокна
    if (type == "Fine") fiberDiameter = 18.0;
    else if (type == "Medium") fiberDiameter = 25.0;
    else fiberDiameter = 35.0;

    woolType = type;
}

void Wool::setFiberDiameter(double diameter) {
    if (diameter <= 0) {
        throw ProductException("Fiber diameter must be positive: " +
                               std::to_string(diameter) + " microns",
                               getName(), "Wool", getQuantity());
    }

    if (diameter > 50.0) {
        throw ProductException("Fiber diameter too large for wool: " +
                               std::to_string(diameter) + " microns (max 50)",
                               getName(), "Wool", getQuantity());
    }

    // Обновление типа на основе диаметра
    if (diameter < 22.0) woolType = "Fine";
    else if (diameter < 32.0) woolType = "Medium";
    else woolType = "Coarse";

    fiberDiameter = diameter;
}

void Wool::setColor(const std::string& woolColor) {
    if (woolColor.empty()) {
        throw ProductException("Color cannot be empty",
                               getName(), "Wool", getQuantity());
    }

    // Если меняем с натурального цвета на другой - теряем органический статус
    if (color == "Natural" && woolColor != "Natural" && isOrganic) {
        setIsOrganic(false);
        std::cout << "Note: Changing from natural color - wool is no longer organic." << std::endl;
    }

    color = woolColor;
}

void Wool::setStapleLength(int length) {
    if (length <= 0) {
        throw ProductException("Staple length must be positive: " +
                               std::to_string(length) + " mm",
                               getName(), "Wool", getQuantity());
    }

    if (length > 200) {
        throw ProductException("Staple length unrealistically long: " +
                               std::to_string(length) + " mm (max 200)",
                               getName(), "Wool", getQuantity());
    }

    stapleLength = length;
}

void Wool::setProcessingStage(const std::string& stage) {
    std::vector<std::string> validStages = {"Raw", "Washed", "Carded", "Spun"};
    bool validStage = false;
    for (const auto& valid : validStages) {
        if (stage == valid) {
            validStage = true;
            break;
        }
    }

    if (!validStage) {
        throw ProductException("Invalid processing stage: " + stage +
                               " (valid: Raw, Washed, Carded, Spun)",
                               getName(), "Wool", getQuantity());
    }

    processingStage = stage;
}

void Wool::setLanolinContent(double content) {
    if (content < 0 || content > 100.0) {
        throw ProductException("Lanolin content must be between 0-100%: " +
                               std::to_string(content),
                               getName(), "Wool", getQuantity());
    }

    // Содержание ланолина влияет на качество
    if (content > 15.0 && getQualityGrade() == "A") {
        setQualityGrade("B");
        throw QualityException("High lanolin content reduces wool quality",
                               getName(), "Wool", getQuantity(), getQualityGrade(),
                               "A", "High lanolin", (content - 15.0) / 15.0 * 100.0);
    }

    lanolinContent = content;
}

void Wool::setIsOrganic(bool organic) {
    if (!organic && color != "Natural") {
        throw ProductException("Dyed wool cannot be certified organic",
                               getName(), "Wool", getQuantity());
    }
    isOrganic = organic;
}

void Wool::setSpinningQuality(const std::string& quality) {
    std::vector<std::string> validQualities = {"Poor", "Fair", "Good", "Excellent"};
    bool valid = false;
    for (const auto& validQuality : validQualities) {
        if (quality == validQuality) {
            valid = true;
            break;
        }
    }

    if (!valid) {
        throw ProductException("Invalid spinning quality: " + quality,
                               getName(), "Wool", getQuantity());
    }

    spinningQuality = quality;
}

double Wool::calculateWarmthRating() const {
    double rating = 5.0; // базовый рейтинг

    // Влияние диаметра волокна (чем тоньше - теплее)
    if (fiberDiameter < 20.0) rating += 3.0;
    else if (fiberDiameter < 25.0) rating += 2.0;
    else if (fiberDiameter < 30.0) rating += 1.0;

    // Влияние содержания ланолина
    rating += lanolinContent * 0.1;

    // Влияние обработки
    if (processingStage == "Carded" || processingStage == "Spun") rating += 1.0;

    // Ограничение от 1 до 10
    if (rating > 10.0) rating = 10.0;
    if (rating < 1.0) rating = 1.0;

    return rating;
}

void Wool::gradeWool() {
    std::cout << "Grading wool..." << std::endl;

    // Градация на основе диаметра волокна
    if (fiberDiameter < 20.0) {
        setQualityGrade("A");
        std::cout << "Grade A: Superfine wool (" << fiberDiameter << " microns)" << std::endl;
    } else if (fiberDiameter < 25.0) {
        setQualityGrade("B");
        std::cout << "Grade B: Fine wool (" << fiberDiameter << " microns)" << std::endl;
    } else if (fiberDiameter < 30.0) {
        setQualityGrade("C");
        std::cout << "Grade C: Medium wool (" << fiberDiameter << " microns)" << std::endl;
    } else {
        setQualityGrade("D");
        std::cout << "Grade D: Coarse wool (" << fiberDiameter << " microns)" << std::endl;
    }

    // Дополнительная проверка для органической шерсти
    if (isOrganic && getQualityGrade() == "C") {
        setQualityGrade("B");
        throw QualityException("Organic certification improves wool grade",
                               getName(), "Wool", getQuantity(), getQualityGrade(),
                               "C", "B", 20.0);
    }
}

bool Wool::isSuitableForClothing() const {
    if (fiberDiameter > 28.0) {
        throw QualityException("Wool too coarse for clothing",
                               getName(), "Wool", getQuantity(), getQualityGrade(),
                               "≤28 microns", std::to_string(fiberDiameter) + " microns",
                               (fiberDiameter - 28.0) / 28.0 * 100.0);
    }

    if (stapleLength < 50) {
        throw QualityException("Staple length too short for clothing",
                               getName(), "Wool", getQuantity(), getQualityGrade(),
                               "≥50 mm", std::to_string(stapleLength) + " mm",
                               (50.0 - stapleLength) / 50.0 * 100.0);
    }

    if (lanolinContent > 20.0) {
        throw QualityException("High lanolin content makes wool unsuitable for clothing",
                               getName(), "Wool", getQuantity(), getQualityGrade(),
                               "≤20%", std::to_string(lanolinContent) + "%",
                               (lanolinContent - 20.0) / 20.0 * 100.0);
    }

    return fiberDiameter <= 28.0 && stapleLength >= 50 && lanolinContent <= 20.0;
}

void Wool::processToStage(const std::string& targetStage) {
    std::vector<std::string> stages = {"Raw", "Washed", "Carded", "Spun"};

    // Находим текущую и целевую позиции
    int currentPos = -1, targetPos = -1;
    for (size_t i = 0; i < stages.size(); ++i) {
        if (processingStage == stages[i]) currentPos = i;
        if (targetStage == stages[i]) targetPos = i;
    }

    if (targetPos == -1) {
        throw ProductException("Invalid target processing stage: " + targetStage,
                               getName(), "Wool", getQuantity());
    }

    if (currentPos == targetPos) {
        throw ProductException("Wool already at " + targetStage + " stage",
                               getName(), "Wool", getQuantity());
    }

    if (currentPos > targetPos) {
        throw ProductException("Cannot go back to earlier processing stage",
                               getName(), "Wool", getQuantity());
    }

    // Последовательная обработка до целевой стадии
    while (currentPos < targetPos) {
        if (stages[currentPos + 1] == "Washed") {
            washWool();
        } else if (stages[currentPos + 1] == "Carded") {
            cardWool();
        } else if (stages[currentPos + 1] == "Spun") {
            spinIntoYarn();
        }
        currentPos++;
    }

    std::cout << "Wool successfully processed to " << targetStage << " stage." << std::endl;
}