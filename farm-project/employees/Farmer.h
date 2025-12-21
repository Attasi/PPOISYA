#ifndef FARMER_H
#define FARMER_H

#include "Employee.h"
#include <string>
#include <vector>

class Farmer : public Employee {
private:
    std::vector<std::string> cropsResponsible;
    std::string farmEquipment;
    double landArea; // площадь земли в гектарах
    std::string irrigationSystem;
    int animalsCaredFor;
    std::string plantingSeason;
    bool hasTractorLicense;
    std::string organicCertification;
    double cropYield; // урожайность в тоннах/гектар

public:
    Farmer(const std::string& name, int age, double salary = 2500.0);

    void work() const override;
    void plantCrops(const std::string& cropType, double area);
    void harvestCrops();
    void maintainEquipment();
    void planPlantingSchedule();

    // Геттеры
    std::vector<std::string> getCropsResponsible() const;
    std::string getFarmEquipment() const;
    double getLandArea() const;
    std::string getIrrigationSystem() const;
    int getAnimalsCaredFor() const;
    std::string getPlantingSeason() const;
    bool getHasTractorLicense() const;
    std::string getOrganicCertification() const;
    double getCropYield() const;

    // Сеттеры
    void setCropsResponsible(const std::vector<std::string>& crops);
    void setFarmEquipment(const std::string& equipment);
    void setLandArea(double area);
    void setIrrigationSystem(const std::string& system);
    void setAnimalsCaredFor(int animals);
    void setPlantingSeason(const std::string& season);
    void setHasTractorLicense(bool license);
    void setOrganicCertification(const std::string& certification);
    void setCropYield(double yield);

    void calculateHarvestForecast() const;
    void applyFertilizer(const std::string& fertilizerType);
    void inspectCrops();
    void manageWaterSupply();
};

#endif // FARMER_H