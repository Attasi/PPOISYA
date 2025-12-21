#include "BerryBush.h"
#include "PlantExceptions.h"
#include <iostream>


BerryBush::BerryBush(double height, const std::string& type)
        : Fruit("Berry Bush", height, 70.0), berryType(type),
          bushAge(0), isThorny(type == "Raspberry" || type == "Blackberry") {
    setTaste("sweet-tart");

    if (height > 3.0) {
        throw GrowthException("Berry bush height too tall",
                              getName(), "Berry Bush", height, 2.5);
    }

    if (type.empty()) {
        throw PlantException("Berry type cannot be empty");
    }

    // Инициализация в зависимости от типа ягод
    if (berryType == "Strawberry") {
        setIsEdibleRaw(true);
        fruitCount = 20;  // Используем прямое присваивание, так как нет setFruitCount()
    } else if (berryType == "Blueberry") {
        setIsEdibleRaw(true);
        fruitCount = 15;
    } else {
        fruitCount = 10;
    }
}

int BerryBush::pickBerries(int count) {
    if (fruitCount == 0) {
        throw HarvestException("No berries available for picking",
                               getName(), "Berry Bush", count, 0.0,
                               "No berries produced");
    }

    if (count <= 0) {
        throw PlantException("Picking count must be positive: " +
                             std::to_string(count));
    }

    if (count > fruitCount) {
        throw HarvestException("Trying to pick more berries than available",
                               getName(), "Berry Bush", count, fruitCount,
                               "Insufficient berry count");
    }

    if (!getIsEdibleRaw() && berryType != "Gooseberry") {
        throw PlantException(getName() + " berries are not edible raw");
    }

    fruitCount -= count;
    std::cout << "Picked " << count << " " << berryType
              << " berries. Remaining: " << fruitCount << std::endl;

    // Увеличиваем счетчик сборов урожая через метод родительского класса
    // (если такой метод есть) или просто выводим сообщение
    std::cout << "Harvest successful!" << std::endl;

    return count;
}

void BerryBush::addPest(const std::string& pest) {
    if (pest.empty()) {
        throw PlantException("Pest name cannot be empty");
    }

    pests.push_back(pest);
    setHealth(getHealth() - 10.0);
    if (getHealth() < 0) setHealth(0);

    if (pests.size() > 5) {
        throw PlantDiseaseException("Severe pest infestation",
                                    getName(), "Berry Bush", "Pest Infestation", 8,
                                    {"leaves", "berries", "stems"});
    }

    std::cout << pest << " infestation detected on " << getName() << "!" << std::endl;
}

void BerryBush::sprayForPests() {
    if (pests.empty()) {
        throw PlantException("No pests detected on " + getName());
    }

    if (getHealth() < 20.0) {
        throw PlantDiseaseException("Bush too weak for pesticide treatment",
                                    getName(), "Berry Bush", "Critical Condition", 9,
                                    {"all"});
    }

    std::cout << "Spraying " << getName() << " for pests: ";
    for (const auto& pest : pests) {
        std::cout << pest << " ";
    }
    std::cout << std::endl;

    pests.clear();
    setHealth(getHealth() + 20.0);
    if (getHealth() > 100.0) setHealth(100.0);

    std::cout << "Pests eliminated!" << std::endl;
}

bool BerryBush::canPropagate() const {
    return bushAge >= 2 && getHealth() > 70.0 && fruitCount > 5;
}

void BerryBush::displayInfo() const {
    Fruit::displayInfo();
    std::cout << "  Variety: " << berryType << " Bush"
              << ", Bush age: " << bushAge << " years"
              << ", Thorny: " << (isThorny ? "Yes" : "No")
              << ", Can propagate: " << (canPropagate() ? "Yes" : "No");

    if (!pests.empty()) {
        std::cout << std::endl << "  Pests: ";
        for (size_t i = 0; i < pests.size(); ++i) {
            std::cout << pests[i];
            if (i < pests.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void BerryBush::grow() {
    Fruit::grow();

    bushAge = getAge() / 365;

    if (bushAge > 20) {
        throw PlantException(getName() + " is too old (max 20 years)");
    }

    if (getIsPlanted() && getHealth() > 40.0) {
        if (getAge() % 30 == 0 && fruitCount < 50) {
            int newBerries = 5 + (bushAge * 2);
            fruitCount += newBerries;

            int maxFruit = 0;
            if (berryType == "Strawberry") maxFruit = 100;
            else if (berryType == "Blueberry") maxFruit = 80;
            else if (berryType == "Raspberry") maxFruit = 60;
            else maxFruit = 50;

            if (fruitCount > maxFruit) {
                fruitCount = maxFruit;
                throw PlantException(getName() + " reached maximum berry count (" +
                                     std::to_string(maxFruit) + ")");
            }
        }

        if (bushAge > 1) {
            setSweetness(getSweetness() + 0.2);
            if (getSweetness() > 100.0) setSweetness(100.0);
        }

        if (getAge() % 100 == 0 && getHealth() < 80.0) {
            if (berryType == "Strawberry") addPest("Aphids");
            else if (berryType == "Blueberry") addPest("Birds");
            else if (berryType == "Raspberry") addPest("Beetles");
        }
    }

    // Проверка на болезнь при плохих условиях
    if (getHealth() < 30.0 && bushAge > 3) {
        throw PlantDiseaseException("Berry bush has fungal disease",
                                    getName(), "Berry Bush", "Powdery Mildew", 6,
                                    {"leaves", "berries"});
    }
}

std::string BerryBush::getBerryType() const { return berryType; }
int BerryBush::getBushAge() const { return bushAge; }
bool BerryBush::getIsThorny() const { return isThorny; }
std::vector<std::string> BerryBush::getPests() const { return pests; }

void BerryBush::setBerryType(const std::string& type) {
    if (type.empty()) {
        throw PlantException("Berry type cannot be empty");
    }
    berryType = type;
    // Не можем изменить имя через setName, так как его нет
    // Вместо этого обновим отображение при выводе
}

void BerryBush::setBushAge(int age) {
    if (age < 0) {
        throw PlantException("Bush age cannot be negative: " +
                             std::to_string(age) + " years");
    }

    if (age > 30) {
        throw PlantException("Bush age unrealistically large: " +
                             std::to_string(age) + " years (max 30)");
    }

    bushAge = age;
}

void BerryBush::setIsThorny(bool thorny) { isThorny = thorny; }