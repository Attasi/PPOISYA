#include "Shepherd.h"
#include "EmployeeExceptions.h"
#include <iostream>

Shepherd::Shepherd(const std::string& name, int age, double salary)
        : Employee(name, age, "Shepherd", salary) {
    // Проверки для пастуха
    if (salary < 1900) {
        throw EmployeeException("Shepherd salary too low: $" + std::to_string(salary) + " (min $1900)");
    }

    sheepInFlock = 150;
    dogBreed = "Border Collie";
    dogName = "Lassie";
    grazingArea = 20.0;
    shepherdStaffType = "Wooden crook";
    lambsBornThisSeason = 45;
    pastureLocation = "North Pasture";
    hasVetTraining = true;

    flockHealthIssues = {"Foot rot", "Parasites"};
    setSpecialization("Sheep Herding & Care");
    setAddress("Pasture Cabin");
}

void Shepherd::work() const {
    if (dogName.empty()) {
        throw EmployeeException(getName() + " has no sheepdog");
    }
    if (pastureLocation.empty()) {
        throw EmployeeException("Pasture location not specified");
    }

    std::cout << getName() << " is herding sheep with " << dogName
              << " the " << dogBreed << " in " << pastureLocation << std::endl;
}

void Shepherd::herdSheep() {
    if (sheepInFlock <= 0) {
        throw EmployeeException(getName() + " has no sheep in flock");
    }
    if (dogName.empty()) {
        throw EmployeeException(getName() + " cannot herd sheep without a sheepdog");
    }
    if (pastureLocation.empty()) {
        throw EmployeeException("Pasture location not specified for herding");
    }

    std::cout << getName() << " is herding " << sheepInFlock
              << " sheep to the grazing area." << std::endl;
    std::cout << "Using " << dogName << " to help with herding." << std::endl;
}

void Shepherd::countSheep() {
    if (sheepInFlock < 0) {
        throw EmployeeException("Sheep count cannot be negative: " + std::to_string(sheepInFlock));
    }
    if (grazingArea <= 0) {
        throw EmployeeException("Grazing area must be positive: " + std::to_string(grazingArea));
    }

    std::cout << getName() << " is counting the flock..." << std::endl;
    std::cout << "Total sheep: " << sheepInFlock << std::endl;
    std::cout << "Lambs born this season: " << lambsBornThisSeason << std::endl;
    std::cout << "Grazing area: " << grazingArea << " hectares" << std::endl;

    double sheepPerHectare = sheepInFlock / grazingArea;
    if (sheepPerHectare > 10) {
        throw EmployeeException("CRITICAL: Overgrazing risk! " +
                                std::to_string(sheepPerHectare) +
                                " sheep/hectare (max 10)");
    } else if (sheepPerHectare > 7) {
        std::cout << "Warning: High grazing density." << std::endl;
    } else {
        std::cout << "Grazing density is optimal." << std::endl;
    }
}

void Shepherd::tendToSickSheep(const std::string& sheepName, const std::string& issue) {
    if (sheepName.empty()) {
        throw EmployeeException("Sheep name cannot be empty");
    }
    if (issue.empty()) {
        throw EmployeeException("Health issue cannot be empty");
    }
    if (!hasVetTraining && (issue == "Broken leg" || issue == "Serious infection")) {
        throw InsufficientQualificationException(getName(), "Veterinary care",
                                                 "No vet training for serious issues");
    }

    flockHealthIssues.push_back(sheepName + ": " + issue);
    std::cout << getName() << " is tending to " << sheepName
              << " with health issue: " << issue << std::endl;

    if (hasVetTraining) {
        std::cout << "Applying veterinary treatment." << std::endl;
    } else {
        std::cout << "Providing basic care until vet arrives." << std::endl;
    }
}

void Shepherd::trainSheepdog() {
    if (dogName.empty()) {
        throw EmployeeException("No sheepdog to train");
    }
    if (dogBreed.empty()) {
        throw EmployeeException("Sheepdog breed not specified");
    }
    if (!hasVetTraining) {
        throw InsufficientQualificationException(getName(), "Dog training",
                                                 "No animal training certification");
    }

    std::cout << getName() << " is training " << dogName
              << " for better herding skills." << std::endl;
    std::cout << "Training commands: 'Come by', 'Away to me', 'Lie down', 'That'll do'" << std::endl;
}

int Shepherd::getSheepInFlock() const { return sheepInFlock; }
std::string Shepherd::getDogBreed() const { return dogBreed; }
std::string Shepherd::getDogName() const { return dogName; }
double Shepherd::getGrazingArea() const { return grazingArea; }
std::vector<std::string> Shepherd::getFlockHealthIssues() const { return flockHealthIssues; }
std::string Shepherd::getShepherdStaffType() const { return shepherdStaffType; }
int Shepherd::getLambsBornThisSeason() const { return lambsBornThisSeason; }
std::string Shepherd::getPastureLocation() const { return pastureLocation; }
bool Shepherd::getHasVetTraining() const { return hasVetTraining; }

void Shepherd::setSheepInFlock(int sheep) {
    if (sheep < 0 || sheep > 1000) {
        throw EmployeeException("Sheep in flock must be between 0-1000: " + std::to_string(sheep));
    }
    sheepInFlock = sheep;
}

void Shepherd::setDogBreed(const std::string& breed) {
    if (breed.empty()) {
        throw EmployeeException("Dog breed cannot be empty");
    }
    dogBreed = breed;
}

void Shepherd::setDogName(const std::string& name) {
    if (name.empty()) {
        throw EmployeeException("Dog name cannot be empty");
    }
    dogName = name;
}

void Shepherd::setGrazingArea(double area) {
    if (area <= 0 || area > 1000) {
        throw EmployeeException("Grazing area must be between 0-1000 hectares: " + std::to_string(area));
    }
    grazingArea = area;
}

void Shepherd::setFlockHealthIssues(const std::vector<std::string>& issues) {
    flockHealthIssues = issues;
}

void Shepherd::setShepherdStaffType(const std::string& staffType) {
    if (staffType.empty()) {
        throw EmployeeException("Shepherd staff type cannot be empty");
    }
    shepherdStaffType = staffType;
}

void Shepherd::setLambsBornThisSeason(int lambs) {
    if (lambs < 0 || lambs > 200) {
        throw EmployeeException("Lambs born must be between 0-200: " + std::to_string(lambs));
    }
    lambsBornThisSeason = lambs;
}

void Shepherd::setPastureLocation(const std::string& location) {
    if (location.empty()) {
        throw EmployeeException("Pasture location cannot be empty");
    }
    pastureLocation = location;
}

void Shepherd::setHasVetTraining(bool training) { hasVetTraining = training; }

void Shepherd::moveFlockToNewPasture(const std::string& newLocation) {
    if (newLocation.empty()) {
        throw EmployeeException("New pasture location cannot be empty");
    }
    if (pastureLocation == newLocation) {
        throw EmployeeException("Flock is already in " + newLocation);
    }
    if (sheepInFlock <= 0) {
        throw EmployeeException("Cannot move empty flock");
    }

    std::cout << getName() << " is moving the flock from " << pastureLocation
              << " to " << newLocation << std::endl;
    pastureLocation = newLocation;
    std::cout << "Flock successfully moved. New grazing area available." << std::endl;
}

void Shepherd::shearSheep(int count) {
    if (count <= 0) {
        throw EmployeeException("Sheep count for shearing must be positive: " + std::to_string(count));
    }
    if (count > sheepInFlock) {
        throw EmployeeException("Cannot shear " + std::to_string(count) +
                                " sheep, only " + std::to_string(sheepInFlock) + " in flock");
    }
    if (!hasVetTraining && count > 20) {
        throw InsufficientQualificationException(getName(), "Large-scale shearing",
                                                 "No certification for mass shearing");
    }

    std::cout << getName() << " is shearing " << count << " sheep." << std::endl;
    double woolCollected = count * 4.5; // 4.5 кг шерсти с овцы
    std::cout << "Collected approximately " << woolCollected << " kg of wool." << std::endl;

    double woolValue = woolCollected * 15; // $15 за кг
    std::cout << "Wool value: $" << woolValue << std::endl;

    // Бонус за хорошую работу
    setSalary(getSalary() * 1.02);
}

void Shepherd::protectFromPredators() {
    if (sheepInFlock <= 0) {
        throw EmployeeException("No sheep to protect");
    }
    if (dogName.empty()) {
        throw EmployeeException("No sheepdog for predator protection");
    }

    std::cout << getName() << " is on predator watch with " << dogName << std::endl;
    std::cout << "Common predators in area: Wolves, Coyotes, Foxes" << std::endl;
    std::cout << "Protection measures: Guard dogs, fencing, night patrols" << std::endl;

    if (hasVetTraining) {
        std::cout << "Also trained in predator deterrent techniques." << std::endl;
    }
}

void Shepherd::monitorFlockHealth() {
    if (sheepInFlock <= 0) {
        throw EmployeeException("No sheep in flock to monitor");
    }

    std::cout << "=== Flock Health Monitoring ===" << std::endl;
    std::cout << "Shepherd: " << getName() << std::endl;
    std::cout << "Flock size: " << sheepInFlock << std::endl;
    std::cout << "Lambs born: " << lambsBornThisSeason << std::endl;

    if (!flockHealthIssues.empty()) {
        std::cout << "Current health issues:" << std::endl;
        for (const auto& issue : flockHealthIssues) {
            std::cout << "  - " << issue << std::endl;
        }

        if (flockHealthIssues.size() > sheepInFlock * 0.1) {
            throw EmployeeException("CRITICAL: More than 10% of flock has health issues!");
        }
    } else {
        std::cout << "No current health issues. Flock is healthy!" << std::endl;
    }

    double healthPercentage = 100.0 - (flockHealthIssues.size() * 100.0 / sheepInFlock);
    std::cout << "Overall flock health: " << healthPercentage << "%" << std::endl;
}