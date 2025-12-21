#include "Farmer.h"
#include "EmployeeExceptions.h"
#include <iostream>

Farmer::Farmer(const std::string& name, int age, double salary)
        : Employee(name, age, "Farmer", salary) {
    // Дополнительные проверки для фермера
    if (salary < 2000) {
        throw EmployeeException("Farmer salary too low: $" + std::to_string(salary) + " (min $2000)");
    }

    farmEquipment = "Basic tools";
    landArea = 5.0;
    irrigationSystem = "Drip irrigation";
    animalsCaredFor = 0;
    plantingSeason = "Spring";
    hasTractorLicense = true;
    organicCertification = "Pending";
    cropYield = 3.5;

    cropsResponsible = {"Wheat", "Corn", "Potatoes"};
    setSpecialization("Crop Production");
    setAddress("Farm House #1");
}

void Farmer::work() const {
    std::cout << getName() << " is working in the fields, tending to crops." << std::endl;
}

void Farmer::plantCrops(const std::string& cropType, double area) {
    if (cropType.empty()) {
        throw EmployeeException("Crop type cannot be empty");
    }
    if (area <= 0) {
        throw EmployeeException("Planting area must be positive: " + std::to_string(area));
    }
    if (area > landArea) {
        throw EmployeeException(getName() + " cannot plant " + std::to_string(area) +
                                " hectares, only has " + std::to_string(landArea) + " hectares available");
    }
    if (!hasTractorLicense && area > 2) {
        throw InsufficientQualificationException(getName(), "Tractor operation",
                                                 "No license for large-scale planting");
    }
    if (plantingSeason.empty()) {
        throw EmployeeException("Planting season not specified");
    }

    cropsResponsible.push_back(cropType);
    std::cout << getName() << " planted " << area << " hectares of " << cropType << std::endl;
}

void Farmer::harvestCrops() {
    if (cropsResponsible.empty()) {
        throw EmployeeException(getName() + " has no crops to harvest");
    }
    if (landArea <= 0) {
        throw EmployeeException("Land area must be positive: " + std::to_string(landArea));
    }
    if (cropYield <= 0) {
        throw EmployeeException("Crop yield must be positive: " + std::to_string(cropYield));
    }

    std::cout << getName() << " is harvesting crops. Expected yield: "
              << cropYield * landArea << " tons." << std::endl;

    double totalValue = cropYield * landArea * 300; // $300 за тонну
    std::cout << "Estimated harvest value: $" << totalValue << std::endl;
}

void Farmer::maintainEquipment() {
    if (farmEquipment.empty()) {
        throw EmployeeException("Farm equipment not specified");
    }

    std::cout << getName() << " is maintaining farm equipment: " << farmEquipment << std::endl;
    if (hasTractorLicense) {
        std::cout << getName() << " is also servicing the tractor." << std::endl;
    }
}

void Farmer::planPlantingSchedule() {
    if (plantingSeason.empty()) {
        throw EmployeeException("Planting season not specified");
    }
    if (cropsResponsible.empty()) {
        throw EmployeeException(getName() + " has no crops to plan schedule for");
    }

    std::cout << getName() << " is planning the planting schedule for " << plantingSeason << std::endl;
    std::cout << "Crops to plant: ";
    for (size_t i = 0; i < cropsResponsible.size(); ++i) {
        std::cout << cropsResponsible[i];
        if (i < cropsResponsible.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

std::vector<std::string> Farmer::getCropsResponsible() const { return cropsResponsible; }
std::string Farmer::getFarmEquipment() const { return farmEquipment; }
double Farmer::getLandArea() const { return landArea; }
std::string Farmer::getIrrigationSystem() const { return irrigationSystem; }
int Farmer::getAnimalsCaredFor() const { return animalsCaredFor; }
std::string Farmer::getPlantingSeason() const { return plantingSeason; }
bool Farmer::getHasTractorLicense() const { return hasTractorLicense; }
std::string Farmer::getOrganicCertification() const { return organicCertification; }
double Farmer::getCropYield() const { return cropYield; }

void Farmer::setCropsResponsible(const std::vector<std::string>& crops) {
    if (crops.empty()) {
        throw EmployeeException("Crops list cannot be empty");
    }
    cropsResponsible = crops;
}

void Farmer::setFarmEquipment(const std::string& equipment) {
    if (equipment.empty()) {
        throw EmployeeException("Farm equipment cannot be empty");
    }
    farmEquipment = equipment;
}

void Farmer::setLandArea(double area) {
    if (area <= 0 || area > 1000) {
        throw EmployeeException("Land area must be between 0-1000 hectares: " + std::to_string(area));
    }
    landArea = area;
}

void Farmer::setIrrigationSystem(const std::string& system) {
    if (system.empty()) {
        throw EmployeeException("Irrigation system cannot be empty");
    }
    irrigationSystem = system;
}

void Farmer::setAnimalsCaredFor(int animals) {
    if (animals < 0 || animals > 1000) {
        throw EmployeeException("Animals cared for must be between 0-1000: " + std::to_string(animals));
    }
    animalsCaredFor = animals;
}

void Farmer::setPlantingSeason(const std::string& season) {
    if (season.empty()) {
        throw EmployeeException("Planting season cannot be empty");
    }
    plantingSeason = season;
}

void Farmer::setHasTractorLicense(bool license) { hasTractorLicense = license; }

void Farmer::setOrganicCertification(const std::string& certification) {
    if (certification.empty()) {
        throw EmployeeException("Organic certification cannot be empty");
    }
    organicCertification = certification;
}

void Farmer::setCropYield(double yield) {
    if (yield <= 0 || yield > 50) {
        throw EmployeeException("Crop yield must be between 0-50 tons/hectare: " + std::to_string(yield));
    }
    cropYield = yield;
}

void Farmer::calculateHarvestForecast() const {
    if (landArea <= 0) {
        throw EmployeeException("Land area must be positive for harvest forecast");
    }
    if (cropYield <= 0) {
        throw EmployeeException("Crop yield must be positive for harvest forecast");
    }

    double forecast = landArea * cropYield;
    std::cout << "Harvest forecast for " << getName() << ": " << forecast << " tons" << std::endl;

    if (organicCertification == "Certified") {
        std::cout << "Organic premium applies: +20% value" << std::endl;
        forecast *= 1.2;
    } else if (organicCertification == "Pending") {
        std::cout << "Warning: Organic certification pending - no premium applied" << std::endl;
    }
    std::cout << "Expected revenue: $" << forecast * 300 << std::endl;
}

void Farmer::applyFertilizer(const std::string& fertilizerType) {
    if (fertilizerType.empty()) {
        throw EmployeeException("Fertilizer type cannot be empty");
    }
    if (landArea <= 0) {
        throw EmployeeException("Cannot apply fertilizer to zero or negative land area");
    }

    std::cout << getName() << " is applying " << fertilizerType << " fertilizer to the crops." << std::endl;
    cropYield *= 1.15; // Увеличение урожайности на 15%
    std::cout << "Crop yield increased to: " << cropYield << " tons/hectare" << std::endl;
}

void Farmer::inspectCrops() {
    if (cropsResponsible.empty()) {
        throw EmployeeException(getName() + " has no crops to inspect");
    }

    std::cout << getName() << " is inspecting crops for pests and diseases." << std::endl;
    if (cropYield < 3.0) {
        std::cout << "Warning: Low crop yield detected. May need intervention." << std::endl;
    } else {
        std::cout << "Crops are healthy and growing well." << std::endl;
    }
}

void Farmer::manageWaterSupply() {
    if (irrigationSystem.empty()) {
        throw EmployeeException("Irrigation system not specified");
    }

    std::cout << getName() << " is managing the " << irrigationSystem << " system." << std::endl;
    if (irrigationSystem == "Drip irrigation") {
        std::cout << "Using efficient water-saving irrigation." << std::endl;
    } else if (irrigationSystem == "Sprinkler") {
        std::cout << "Activating sprinkler system for uniform watering." << std::endl;
    } else {
        throw EmployeeException("Unknown irrigation system: " + irrigationSystem);
    }
}