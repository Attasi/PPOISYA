#include "Egg.h"
#include "ProductExceptions.h"
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

Egg::Egg(int quantity, const std::string& eggSize,
         const std::string& shellColor)
        : Product("Egg", quantity, 0.3),
          eggSize(eggSize),
          shellColor(shellColor),
          yolkColorGrade(8.0),
          isFertilized(false),
          layingDate("2024-01-01"),
          chickenBreed("Rhode Island Red"),
          shellThickness(0.3),
          isFreeRange(false),
          cholesterolContent(185) {

    if (quantity <= 0) {
        throw ProductException("Egg quantity must be positive: " +
                               std::to_string(quantity),
                               getName(), "Egg", quantity);
    }

    if (quantity > 10000) {
        throw ProductException("Egg quantity unrealistically large: " +
                               std::to_string(quantity) + " (max 10,000)",
                               getName(), "Egg", quantity);
    }

    // Проверка размера яйца
    std::vector<std::string> validSizes = {"Small", "Medium", "Large", "X-Large"};
    bool validSize = false;
    for (const auto& size : validSizes) {
        if (eggSize == size) {
            validSize = true;
            break;
        }
    }

    if (!validSize) {
        throw ProductException("Invalid egg size: " + eggSize +
                               " (valid: Small, Medium, Large, X-Large)",
                               getName(), "Egg", quantity);
    }

    // Проверка цвета скорлупы
    if (shellColor != "White" && shellColor != "Brown") {
        throw ProductException("Invalid shell color: " + shellColor +
                               " (valid: White, Brown)",
                               getName(), "Egg", quantity);
    }

    setUnitOfMeasure("pieces");
    setStorageConditions("Refrigerated at 4°C");
    setExpirationDate("2024-02-15");
}

void Egg::displayInfo() const {
    Product::displayInfo();
    std::cout << "=== Egg Details ===" << std::endl;
    std::cout << "Size: " << eggSize << std::endl;
    std::cout << "Shell Color: " << shellColor << std::endl;
    std::cout << "Yolk Color Grade: " << yolkColorGrade << " (1-15 scale)" << std::endl;
    std::cout << "Fertilized: " << (isFertilized ? "Yes" : "No") << std::endl;
    std::cout << "Laying Date: " << layingDate << std::endl;
    std::cout << "Chicken Breed: " << chickenBreed << std::endl;
    std::cout << "Shell Thickness: " << shellThickness << " mm" << std::endl;
    std::cout << "Free Range: " << (isFreeRange ? "Yes" : "No") << std::endl;
    std::cout << "Cholesterol: " << cholesterolContent << " mg" << std::endl;
}

void Egg::candleEgg() {
    std::cout << "Candling egg..." << std::endl;

    // Проверка на наличие дефектов при просвете
    if (shellThickness < 0.2) {
        throw QualityException("Egg shell too thin for safe handling",
                               getName(), "Egg", getQuantity(),
                               std::to_string(yolkColorGrade),
                               "6-15", "Thin shell",
                               (0.2 - shellThickness) / 0.2 * 100.0);
    }

    if (shellThickness > 0.5) {
        throw QualityException("Egg shell abnormally thick",
                               getName(), "Egg", getQuantity(),
                               std::to_string(yolkColorGrade),
                               "6-15", "Thick shell",
                               (shellThickness - 0.5) / 0.5 * 100.0);
    }

    if (isFertilized) {
        std::cout << "Egg is fertilized - suitable for incubation" << std::endl;
    } else {
        std::cout << "Egg is not fertilized - suitable for consumption" << std::endl;
    }
}

void Egg::gradeEgg() {
    std::cout << "Grading egg..." << std::endl;

    // Градация на основе цвета желтка
    if (yolkColorGrade < 1.0 || yolkColorGrade > 15.0) {
        throw QualityException("Invalid yolk color grade",
                               getName(), "Egg", getQuantity(),
                               std::to_string(yolkColorGrade),
                               "1-15", "Invalid grade",
                               100.0);
    }

    // Установка класса качества на основе цвета желтка
    if (yolkColorGrade >= 10.0) {
        setQualityGrade("AA");
        std::cout << "Grade AA: Premium quality (yolk grade: " << yolkColorGrade << ")" << std::endl;
    } else if (yolkColorGrade >= 7.0) {
        setQualityGrade("A");
        std::cout << "Grade A: Good quality (yolk grade: " << yolkColorGrade << ")" << std::endl;
    } else if (yolkColorGrade >= 4.0) {
        setQualityGrade("B");
        std::cout << "Grade B: Standard quality (yolk grade: " << yolkColorGrade << ")" << std::endl;
    } else {
        setQualityGrade("C");
        throw QualityException("Egg yolk color too pale",
                               getName(), "Egg", getQuantity(),
                               std::to_string(yolkColorGrade),
                               "7-15", "Pale yolk",
                               (7.0 - yolkColorGrade) / 7.0 * 100.0);
    }

    // Дополнительная проверка для органических яиц
    if (isFreeRange && yolkColorGrade < 10.0) {
        setQualityGrade("B");
        throw QualityException("Free-range eggs should have darker yolk",
                               getName(), "Egg", getQuantity(),
                               std::to_string(yolkColorGrade),
                               "10-15", "Pale for free-range",
                               (10.0 - yolkColorGrade) / 10.0 * 100.0);
    }
}

void Egg::washEggs() {
    int eggCount = static_cast<int>(getQuantity());

    if (eggCount <= 0) {
        throw ProductException("Cannot wash zero or negative egg count",
                               getName(), "Egg", getQuantity());
    }

    std::cout << "Washing " << eggCount << " eggs..." << std::endl;

    // Проверка на треснутые яйца после мытья
    if (shellThickness < 0.25 && getQuantity() > 50) {
        double crackProbability = 5.0; // 5% вероятность трещин
        if (crackProbability > 3.0) {
            throw QualityException("High risk of cracks during washing",
                                   getName(), "Egg", getQuantity(),
                                   std::to_string(yolkColorGrade),
                                   "Standard", "Thin shell risk",
                                   (0.25 - shellThickness) / 0.25 * 100.0);
        }
    }

    std::cout << "Eggs washed successfully" << std::endl;
}

void Egg::packInCarton() {
    int eggCount = static_cast<int>(getQuantity());

    if (eggCount <= 0) {
        throw ProductException("Cannot pack zero or negative egg count",
                               getName(), "Egg", getQuantity());
    }

    // Стандартные размеры упаковок
    std::vector<int> standardSizes = {6, 10, 12, 18, 30};
    bool standardPack = false;

    for (int size : standardSizes) {
        if (eggCount % size == 0) {
            standardPack = true;
            break;
        }
    }

    if (!standardPack) {
        throw PackagingException("Egg count not suitable for standard cartons",
                                 getName(), "Egg", getQuantity(),
                                 "Standard carton", "Custom packaging",
                                 getUnitOfMeasure(),
                                 "Count not divisible by 6, 10, 12, 18, or 30");
    }

    std::cout << "Packing " << eggCount << " eggs..." << std::endl;

    // Выбор оптимального размера упаковки
    if (eggCount % 30 == 0 && eggSize == "X-Large") {
        int trays = eggCount / 30;
        std::cout << "Using 30-egg trays for X-Large eggs: " << trays << " trays" << std::endl;
    } else if (eggCount % 12 == 0) {
        int dozens = eggCount / 12;
        std::cout << "Using dozen cartons: " << dozens << " cartons" << std::endl;
    } else if (eggCount % 10 == 0) {
        int packs = eggCount / 10;
        std::cout << "Using 10-egg packs: " << packs << " packs" << std::endl;
    } else if (eggCount % 6 == 0) {
        int halfDozens = eggCount / 6;
        std::cout << "Using half-dozen cartons: " << halfDozens << " cartons" << std::endl;
    } else {
        int packs = eggCount / 18;
        std::cout << "Using 18-egg flats: " << packs << " flats" << std::endl;
    }
}

// Геттеры
std::string Egg::getEggSize() const { return eggSize; }
std::string Egg::getShellColor() const { return shellColor; }
double Egg::getYolkColorGrade() const { return yolkColorGrade; }
bool Egg::getIsFertilized() const { return isFertilized; }
std::string Egg::getLayingDate() const { return layingDate; }
std::string Egg::getChickenBreed() const { return chickenBreed; }
double Egg::getShellThickness() const { return shellThickness; }
bool Egg::getIsFreeRange() const { return isFreeRange; }
int Egg::getCholesterolContent() const { return cholesterolContent; }

// Сеттеры
void Egg::setEggSize(const std::string& size) {
    std::vector<std::string> validSizes = {"Small", "Medium", "Large", "X-Large"};
    bool validSize = false;
    for (const auto& valid : validSizes) {
        if (size == valid) {
            validSize = true;
            break;
        }
    }

    if (!validSize) {
        throw ProductException("Invalid egg size: " + size,
                               getName(), "Egg", getQuantity());
    }
    eggSize = size;
}

void Egg::setShellColor(const std::string& color) {
    if (color != "White" && color != "Brown") {
        throw ProductException("Invalid shell color: " + color +
                               " (valid: White, Brown)",
                               getName(), "Egg", getQuantity());
    }
    shellColor = color;
}

void Egg::setYolkColorGrade(double grade) {
    if (grade < 1.0 || grade > 15.0) {
        throw ProductException("Yolk color grade must be between 1.0 and 15.0: " +
                               std::to_string(grade),
                               getName(), "Egg", getQuantity());
    }
    yolkColorGrade = grade;
}

void Egg::setIsFertilized(bool fertilized) {
    isFertilized = fertilized;
}

void Egg::setLayingDate(const std::string& date) {
    if (date.empty()) {
        throw ProductException("Laying date cannot be empty",
                               getName(), "Egg", getQuantity());
    }
    layingDate = date;
}

void Egg::setChickenBreed(const std::string& breed) {
    if (breed.empty()) {
        throw ProductException("Chicken breed cannot be empty",
                               getName(), "Egg", getQuantity());
    }
    chickenBreed = breed;
}

void Egg::setShellThickness(double thickness) {
    if (thickness <= 0) {
        throw ProductException("Shell thickness must be positive: " +
                               std::to_string(thickness) + " mm",
                               getName(), "Egg", getQuantity());
    }

    if (thickness > 1.0) {
        throw ProductException("Shell thickness unrealistically large: " +
                               std::to_string(thickness) + " mm (max 1.0 mm)",
                               getName(), "Egg", getQuantity());
    }
    shellThickness = thickness;
}

void Egg::setIsFreeRange(bool freeRange) {
    isFreeRange = freeRange;
}

void Egg::setCholesterolContent(int cholesterol) {
    if (cholesterol <= 0) {
        throw ProductException("Cholesterol content must be positive: " +
                               std::to_string(cholesterol) + " mg",
                               getName(), "Egg", getQuantity());
    }

    if (cholesterol > 300) {
        throw ProductException("Cholesterol content too high: " +
                               std::to_string(cholesterol) + " mg (max 300 mg)",
                               getName(), "Egg", getQuantity());
    }
    cholesterolContent = cholesterol;
}

bool Egg::checkFreshness() const {
    // Проверка свежести на основе толщины скорлупы и времени
    if (shellThickness < 0.2) {
        return false; // Скорлупа слишком тонкая - яйцо старое
    }

    // Здесь можно добавить логику проверки по дате
    // Для простоты всегда возвращаем true, если скорлупа в норме
    return true;
}

void Egg::incubateIfFertilized() {
    if (isFertilized) {
        std::cout << "Egg is fertilized - starting incubation process" << std::endl;
        // Логика инкубации
    } else {
        std::cout << "Egg is not fertilized - cannot incubate" << std::endl;
    }
}

double Egg::calculateProteinContent() const {
    // Приблизительное содержание белка в яйце (граммы)
    double protein = 0.0;

    if (eggSize == "Small") protein = 4.8;
    else if (eggSize == "Medium") protein = 5.5;
    else if (eggSize == "Large") protein = 6.3;
    else if (eggSize == "X-Large") protein = 7.0;

    return protein;
}

void Egg::sortBySize() {
    std::cout << "Sorting eggs by size..." << std::endl;
    // В реальной реализации здесь была бы логика сортировки
    // Для примера просто выводим информацию
    std::cout << "Eggs sorted as " << eggSize << " size" << std::endl;
}