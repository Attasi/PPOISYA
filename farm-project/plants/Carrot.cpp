#include "Carrot.h"
#include "PlantExceptions.h"
#include <iostream>
#include <cmath>

Carrot::Carrot(double height)
        : Vegetable("Carrot", height, true), rootLength(10.0),
          sugarContent(5.0), isBabyCarrot(height < 0.3) {
    setColor("orange");

    if (height > 0.8) {
        throw GrowthException("Carrot plant height too tall",
                              getName(), "Carrot", height, 0.8);
    }
}

void Carrot::measureLength() {
    if (rootLength <= 0) {
        throw PlantException("Carrot root length invalid: " +
                             std::to_string(rootLength) + "cm");
    }

    std::cout << "Carrot root length: " << rootLength << "cm" << std::endl;

    if (rootLength > 30.0) {
        throw GrowthException("Carrot root abnormally long",
                              getName(), "Carrot", rootLength, 25.0);
    }

    if (rootLength < 2.0 && getAge() > 20) {
        throw GrowthException("Carrot root growth stunted",
                              getName(), "Carrot", rootLength, 5.0);
    }
}

bool Carrot::isSweetCarrot() const {
    return sugarContent > 7.0 && getHealth() > 75.0;
}

void Carrot::peelCarrot(int count) {
    if (getHarvestCount() <= 0) {
        throw HarvestException("No carrots harvested yet to peel",
                               getName(), "Carrot", count, 0.0,
                               "No harvests recorded");
    }

    if (count <= 0) {
        throw PlantException("Peeling count must be positive: " +
                             std::to_string(count));
    }

    if (!isSweetCarrot()) {
        throw HarvestException("Carrots not sweet enough for peeling",
                               getName(), "Carrot", 7.0, sugarContent,
                               "Low sugar content");
    }

    std::cout << "Peeled " << count << " carrots for consumption." << std::endl;
    sugarContent *= 0.95;
}

void Carrot::displayInfo() const {
    Vegetable::displayInfo();
    std::cout << "  Variety: Carrot"
              << ", Root length: " << rootLength << "cm"
              << ", Sugar content: " << sugarContent << "%"
              << ", Baby carrot: " << (isBabyCarrot ? "Yes" : "No")
              << ", Sweet carrot: " << (isSweetCarrot() ? "Yes" : "No") << std::endl;
}

void Carrot::grow() {
    Vegetable::grow();

    if (getIsPlanted() && getWaterLevel() > 30.0) {
        rootLength += 0.5;

        if (rootLength > 40.0) {
            throw GrowthException("Carrot root grew too long",
                                  getName(), "Carrot", rootLength, 35.0);
        }

        if (getAge() > 30) {
            sugarContent += 0.1;
            if (sugarContent > 15.0) {
                sugarContent = 15.0;
                throw PlantException(getName() + " reached maximum sugar content (15%)");
            }
        }

        if (isBabyCarrot && rootLength > 12.0) {
            isBabyCarrot = false;
            std::cout << getName() << " has matured from baby carrot to regular carrot." << std::endl;
        }
    }

    // Проверка на болезнь при неправильных условиях
    if (getWaterLevel() > 85.0 && sugarContent < 3.0) {
        throw PlantDiseaseException("Carrot developing root rot",
                                    getName(), "Carrot", "Root Rot", 7,
                                    {"root"});
    }
}

double Carrot::getRootLength() const { return rootLength; }
double Carrot::getSugarContent() const { return sugarContent; }
bool Carrot::getIsBabyCarrot() const { return isBabyCarrot; }

void Carrot::setRootLength(double length) {
    if (length <= 0) {
        throw PlantException("Root length must be positive: " +
                             std::to_string(length) + "cm");
    }

    if (length > 50.0) {
        throw GrowthException("Carrot root length unrealistically long",
                              getName(), "Carrot", length, 40.0);
    }

    rootLength = length;

    if (isBabyCarrot && length > 12.0) {
        isBabyCarrot = false;
    }
}

void Carrot::setSugarContent(double sugar) {
    if (sugar < 0) {
        throw PlantException("Sugar content cannot be negative: " +
                             std::to_string(sugar) + "%");
    }

    if (sugar > 20.0) {
        throw PlantException("Sugar content unrealistically high: " +
                             std::to_string(sugar) + "% (max 20%)");
    }

    sugarContent = sugar;
}

void Carrot::setIsBabyCarrot(bool baby) {
    if (!baby && rootLength < 8.0) {
        throw PlantException("Cannot set as regular carrot with root length < 8cm: " +
                             std::to_string(rootLength) + "cm");
    }
    isBabyCarrot = baby;
}