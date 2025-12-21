#include "AppleTree.h"
#include "PlantExceptions.h"
#include <iostream>

AppleTree::AppleTree(double height, const std::string& type)
        : Fruit("Apple Tree", height, 60.0), trunkDiameter(15.0),
          branchCount(10), appleType(type), isDwarf(height < 2.0) {
    setTaste("sweet");

    if (height > 15.0 && !isDwarf) {
        throw GrowthException("Apple tree height too tall",
                              getName(), "Apple Tree", height, 12.0);
    }

    if (height < 0.5) {
        throw GrowthException("Apple tree height too short",
                              getName(), "Apple Tree", height, 1.0);
    }

    if (type.empty()) {
        throw PlantException("Apple type cannot be empty");
    }
}

void AppleTree::pruneBranches(int count) {
    if (count <= 0) {
        throw PlantException("Pruning count must be positive: " +
                             std::to_string(count));
    }

    if (count > branchCount) {
        throw PlantException("Trying to prune more branches than available: " +
                             std::to_string(count) + "/" +
                             std::to_string(branchCount));
    }

    if (getHealth() < 40.0) {
        throw PlantDiseaseException("Tree too weak for pruning",
                                    getName(), "Apple Tree", "Weakness", 6,
                                    {"branches"});
    }

    branchCount -= count;
    setHealth(getHealth() + 10.0 * count);
    if (getHealth() > 100.0) setHealth(100.0);

    std::cout << "Pruned " << count << " branches. Remaining: " << branchCount << std::endl;
}

int AppleTree::pickApples(int count) {
    int picked = harvestFruit(count);
    if (picked > 0) {
        if (appleType == "Crab" && getSweetness() < 40.0) {
            throw HarvestException("Crab apples not sweet enough for picking",
                                   getName(), "Apple Tree", 40.0, getSweetness(),
                                   "Low sugar content");
        }

        std::cout << "Picked " << picked << " " << appleType << " apples from the tree." << std::endl;
    }
    return picked;
}

std::string AppleTree::getTreeHealthStatus() const {
    if (getHealth() >= 80.0) return "Excellent";
    if (getHealth() >= 60.0) return "Good";
    if (getHealth() >= 40.0) return "Fair";
    if (getHealth() >= 20.0) return "Poor";
    return "Critical";
}

void AppleTree::displayInfo() const {
    Fruit::displayInfo();
    std::cout << "  Variety: Apple Tree (" << appleType << ")"
              << ", Trunk diameter: " << trunkDiameter << "cm"
              << ", Branch count: " << branchCount
              << ", Tree type: " << (isDwarf ? "Dwarf" : "Standard")
              << ", Health status: " << getTreeHealthStatus() << std::endl;
}

void AppleTree::grow() {
    Fruit::grow();

    if (getIsPlanted() && getHealth() > 30.0) {
        if (!isDwarf) {
            setHeight(getHeight() + 0.005);
            trunkDiameter += 0.01;

            if (getHeight() > 20.0) {
                throw GrowthException("Apple tree grew too tall",
                                      getName(), "Apple Tree", getHeight(), 15.0);
            }

            if (trunkDiameter > 100.0) {
                throw GrowthException("Apple tree trunk too thick",
                                      getName(), "Apple Tree", trunkDiameter, 80.0);
            }
        }

        if (getAge() % 100 == 0 && branchCount < 50) {
            branchCount += 2;

            if (branchCount > 100) {
                branchCount = 100;
                throw PlantException(getName() + " reached maximum branch count (100)");
            }
        }

        if ((getAge() % 365 > 100 && getAge() % 365 < 250) && getFruitCount() < 200) {
            setFruitCount(getFruitCount() + 5);

            int maxFruit = isDwarf ? 100 : 200;
            if (getFruitCount() > maxFruit) {
                setFruitCount(maxFruit);
                throw PlantException(getName() + " reached maximum fruit count (" +
                                     std::to_string(maxFruit) + ")");
            }
        }

        if (getFruitCount() > 0 && getAge() % 365 > 200) {
            setSweetness(getSweetness() + 0.5);
            if (getSweetness() > 100.0) setSweetness(100.0);
        }
    }

    // Проверка на болезнь при плохих условиях
    if (getHealth() < 50.0 && branchCount > 30) {
        throw PlantDiseaseException("Apple tree has fungal disease",
                                    getName(), "Apple Tree", "Apple Scab", 7,
                                    {"leaves", "fruits", "branches"});
    }
}

double AppleTree::getTrunkDiameter() const { return trunkDiameter; }
int AppleTree::getBranchCount() const { return branchCount; }
std::string AppleTree::getAppleType() const { return appleType; }
bool AppleTree::getIsDwarf() const { return isDwarf; }

void AppleTree::setTrunkDiameter(double diameter) {
    if (diameter <= 0) {
        throw PlantException("Trunk diameter must be positive: " +
                             std::to_string(diameter) + "cm");
    }

    if (diameter > 150.0) {
        throw GrowthException("Apple tree trunk diameter unrealistically large",
                              getName(), "Apple Tree", diameter, 120.0);
    }

    trunkDiameter = diameter;
}

void AppleTree::setBranchCount(int count) {
    if (count < 0) {
        throw PlantException("Branch count cannot be negative: " +
                             std::to_string(count));
    }

    if (count > 150) {
        throw PlantException("Branch count unrealistically large: " +
                             std::to_string(count) + " (max 150)");
    }

    branchCount = count;
}

void AppleTree::setAppleType(const std::string& type) {
    if (type.empty()) {
        throw PlantException("Apple type cannot be empty");
    }
    appleType = type;
}

void AppleTree::setIsDwarf(bool dwarf) {
    if (!dwarf && getHeight() < 1.0) {
        throw PlantException("Cannot set as standard tree with height < 1.0m: " +
                             std::to_string(getHeight()) + "m");
    }
    isDwarf = dwarf;
}