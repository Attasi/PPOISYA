#include "Tomato.h"
#include "PlantExceptions.h"
#include <iostream>

Tomato::Tomato(double height, bool cherryTomato)
        : Vegetable("Tomato", height, false), tomatoCount(0),
          tomatoSize(6.0), isCherryTomato(cherryTomato), ripeness("green") {
    setColor("red");

    if (isCherryTomato) {
        // Не можем изменить имя через setName, создаем новый объект с другим именем
        // Просто запомним, что это черри-томаты
        tomatoSize = 2.0;

        if (height > 2.0) {
            throw GrowthException("Cherry tomato plant too tall",
                                  getName(), "Tomato", height, 2.0);
        }
    } else {
        if (height > 3.0) {
            throw GrowthException("Tomato plant too tall",
                                  getName(), "Tomato", height, 3.0);
        }
    }
}

int Tomato::harvestTomatoes(int count) {
    if (tomatoCount == 0) {
        throw HarvestException("No tomatoes available for harvest",
                               getName(), "Tomato", count, 0.0,
                               "No tomatoes produced");
    }

    if (count <= 0) {
        throw PlantException("Harvest count must be positive: " +
                             std::to_string(count));
    }

    if (count > tomatoCount) {
        throw HarvestException("Trying to harvest more tomatoes than available",
                               getName(), "Tomato", count, tomatoCount,
                               "Insufficient tomato count");
    }

    if (ripeness != "red") {
        throw HarvestException("Tomatoes are not ripe yet",
                               getName(), "Tomato", 100.0, 0.0,
                               "Ripeness: " + ripeness);
    }

    tomatoCount -= count;
    std::cout << "Harvested " << count << " tomatoes. Remaining: " << tomatoCount << std::endl;

    return count;
}

void Tomato::checkRipeness() {
    if (getAge() < 30) {
        ripeness = "green";
    } else if (getAge() < 50) {
        ripeness = "yellow";
    } else if (getAge() < 70) {
        ripeness = "orange";
    } else {
        ripeness = "red";
    }

    if (ripeness == "red" && tomatoCount == 0) {
        throw HarvestException("Tomatoes ripe but none produced",
                               getName(), "Tomato", 10.0, 0.0,
                               "No fruit development");
    }

    std::cout << "Tomatoes are " << ripeness << "." << std::endl;
}

void Tomato::makeSauce(int tomatoesNeeded) {
    if (tomatoCount < tomatoesNeeded) {
        throw HarvestException("Not enough tomatoes for sauce",
                               getName(), "Tomato", tomatoesNeeded, tomatoCount,
                               "Insufficient tomatoes");
    }

    if (ripeness != "red") {
        throw HarvestException("Tomatoes not ripe enough for sauce",
                               getName(), "Tomato", 100.0, 0.0,
                               "Ripeness: " + ripeness);
    }

    if (tomatoesNeeded <= 0) {
        throw PlantException("Sauce requires positive number of tomatoes: " +
                             std::to_string(tomatoesNeeded));
    }

    std::cout << "Making tomato sauce from " << tomatoesNeeded << " tomatoes." << std::endl;
    tomatoCount -= tomatoesNeeded;
    // Увеличиваем счетчик сборов через доступ к полю родительского класса
    // Если в Vegetable есть поле harvestCount
    // В данном случае просто выводим сообщение
    std::cout << "Sauce made successfully!" << std::endl;
}

void Tomato::displayInfo() const {
    Vegetable::displayInfo();
    std::string displayName = isCherryTomato ? "Cherry Tomato" : "Tomato";
    std::cout << "  Variety: " << displayName
              << ", Tomato count: " << tomatoCount
              << ", Tomato size: " << tomatoSize << "cm"
              << ", Ripeness: " << ripeness << std::endl;
}

void Tomato::grow() {
    Vegetable::grow();

    if (getIsPlanted() && getHealth() > 40.0) {
        if (getAge() > 40 && tomatoCount < 20) {
            tomatoCount += 2;

            if (isCherryTomato && tomatoCount > 100) {
                tomatoCount = 100;
                throw PlantException(getName() + " reached maximum tomato count (100)");
            }

            if (!isCherryTomato && tomatoCount > 30) {
                tomatoCount = 30;
                throw PlantException(getName() + " reached maximum tomato count (30)");
            }
        }

        if (tomatoCount > 0 && getWaterLevel() > 50.0) {
            tomatoSize += 0.1;

            if (isCherryTomato && tomatoSize > 4.0) {
                tomatoSize = 4.0;
                throw GrowthException("Cherry tomato size too large",
                                      getName(), "Tomato", tomatoSize, 3.0);
            }

            if (!isCherryTomato && tomatoSize > 12.0) {
                tomatoSize = 12.0;
                throw GrowthException("Tomato size too large",
                                      getName(), "Tomato", tomatoSize, 10.0);
            }
        }

        checkRipeness();
    }

    // Проверка на болезнь при высокой влажности
    if (getWaterLevel() > 90.0 && tomatoCount > 10) {
        throw PlantDiseaseException("Tomatoes developing blight",
                                    getName(), "Tomato", "Blight", 8,
                                    {"fruits", "leaves"});
    }
}

int Tomato::getTomatoCount() const { return tomatoCount; }
double Tomato::getTomatoSize() const { return tomatoSize; }
bool Tomato::getIsCherryTomato() const { return isCherryTomato; }
std::string Tomato::getRipeness() const { return ripeness; }

void Tomato::setTomatoCount(int count) {
    if (count < 0) {
        throw PlantException("Tomato count cannot be negative: " +
                             std::to_string(count));
    }

    int maxCount = isCherryTomato ? 100 : 30;
    if (count > maxCount) {
        throw PlantException("Tomato count too large: " +
                             std::to_string(count) + " (max " +
                             std::to_string(maxCount) + ")");
    }

    tomatoCount = count;
}

void Tomato::setTomatoSize(double size) {
    if (size <= 0) {
        throw PlantException("Tomato size must be positive: " +
                             std::to_string(size) + "cm");
    }

    double maxSize = isCherryTomato ? 4.0 : 12.0;
    if (size > maxSize) {
        throw GrowthException("Tomato size too large",
                              getName(), "Tomato", size, maxSize);
    }

    tomatoSize = size;
}

void Tomato::setIsCherryTomato(bool cherry) { isCherryTomato = cherry; }
void Tomato::setRipeness(const std::string& r) {
    if (r != "green" && r != "yellow" && r != "orange" && r != "red") {
        throw PlantException("Invalid ripeness: " + r +
                             " (must be green/yellow/orange/red)");
    }
    ripeness = r;
}