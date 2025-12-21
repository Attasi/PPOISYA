#include "Chicken.h"

Chicken::Chicken(const std::string& name, int age, double weight, const std::string& breed)
        : Bird(name, age, weight, breed, 0.6, false),
          eggsPerWeek(5), combType("Single"),
          isBroody(false), roostingPerch("Wooden"),
          featherLoss(0), chickenRun("Main Run"),
          freeRange(true), favoriteFeed("Grain"),
          dustBathingFrequency(3) {
    setPrice(25.0);
    setFeatherColor("Brown");
    setCanFly(false);
}

void Chicken::makeSound() const {
    if (age < 1) {
        std::cout << name << " says: Peep peep!" << std::endl;
    } else {
        std::cout << name << " says: Cluck cluck!" << std::endl;
    }
}

void Chicken::layEgg() {
    if (age > 5 && !isBroody) {
        Bird::layEgg();
        std::cout << name << " laid a fresh egg! Eggs this week: " << (eggsLaid % eggsPerWeek) + 1 << std::endl;
    } else if (isBroody) {
        std::cout << name << " is broody and won't lay eggs." << std::endl;
    } else {
        std::cout << name << " is too young to lay eggs." << std::endl;
    }
}

void Chicken::peckFood() {
    std::cout << name << " is pecking at " << favoriteFeed << "." << std::endl;
    hungerLevel -= 20;
    if (hungerLevel < 0) hungerLevel = 0;
    happinessLevel += 10;
    if (happinessLevel > 100) happinessLevel = 100;
}

void Chicken::dustBathe() {
    std::cout << name << " is taking a dust bath." << std::endl;
    happinessLevel += 25;
    if (happinessLevel > 100) happinessLevel = 100;
    featherLoss += 1;
    if (featherLoss > 10) featherLoss = 10;
}

void Chicken::roost() {
    std::cout << name << " is roosting on " << roostingPerch << " perch." << std::endl;
    happinessLevel += 15;
    if (happinessLevel > 100) happinessLevel = 100;
}

int Chicken::getEggsPerWeek() const { return eggsPerWeek; }
std::string Chicken::getCombType() const { return combType; }
bool Chicken::getIsBroody() const { return isBroody; }
std::string Chicken::getRoostingPerch() const { return roostingPerch; }
int Chicken::getFeatherLoss() const { return featherLoss; }
std::string Chicken::getChickenRun() const { return chickenRun; }
bool Chicken::getFreeRange() const { return freeRange; }
std::string Chicken::getFavoriteFeed() const { return favoriteFeed; }
int Chicken::getDustBathingFrequency() const { return dustBathingFrequency; }

void Chicken::setEggsPerWeek(int eggs) { eggsPerWeek = eggs; }
void Chicken::setCombType(const std::string& type) { combType = type; }
void Chicken::setIsBroody(bool broody) { isBroody = broody; }
void Chicken::setRoostingPerch(const std::string& perch) { roostingPerch = perch; }
void Chicken::setFeatherLoss(int loss) { featherLoss = loss; }
void Chicken::setChickenRun(const std::string& run) { chickenRun = run; }
void Chicken::setFreeRange(bool freeRange) { this->freeRange = freeRange; }
void Chicken::setFavoriteFeed(const std::string& feed) { favoriteFeed = feed; }
void Chicken::setDustBathingFrequency(int frequency) { dustBathingFrequency = frequency; }

double Chicken::calculateDailyFood() const {
    double base = Bird::calculateDailyFood();
    if (isBroody) base *= 0.8;
    if (freeRange) base *= 0.7;
    return base;
}

void Chicken::displayInfo() const {
    Bird::displayInfo();
    std::cout << "--- Chicken Specific ---" << std::endl;
    std::cout << "Eggs Per Week: " << eggsPerWeek << std::endl;
    std::cout << "Comb Type: " << combType << std::endl;
    std::cout << "Broody: " << (isBroody ? "Yes" : "No") << std::endl;
    std::cout << "Roosting Perch: " << roostingPerch << std::endl;
    std::cout << "Feather Loss: " << featherLoss << "/10" << std::endl;
    std::cout << "Chicken Run: " << chickenRun << std::endl;
    std::cout << "Free Range: " << (freeRange ? "Yes" : "No") << std::endl;
    std::cout << "Favorite Feed: " << favoriteFeed << std::endl;
    std::cout << "Dust Baths Per Week: " << dustBathingFrequency << std::endl;
}

bool Chicken::isLayingWell() const {
    return age > 5 && !isBroody && eggsLaid >= (eggsPerWeek * 0.8);
}

void Chicken::collectEggs() {
    std::cout << "Collecting eggs from " << name << std::endl;
    if (eggsLaid > 0) {
        std::cout << "Collected " << eggsLaid << " eggs." << std::endl;
        eggsLaid = 0;
    }
}

void Chicken::breakBroodiness() {
    if (isBroody) {
        std::cout << "Breaking broodiness for " << name << std::endl;
        isBroody = false;
        happinessLevel -= 20;
        if (happinessLevel < 0) happinessLevel = 0;
    }
}