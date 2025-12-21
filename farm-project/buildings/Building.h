#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <iostream>

class Building {
protected:
    std::string name;
    double area; // площадь в квадратных метрах
    int constructionYear;
    std::string buildingMaterial;
    std::string condition; // Excellent, Good, Fair, Poor
    std::string locationOnFarm;
    bool hasElectricity;
    bool hasWaterSupply;
    std::string roofType;
    double maintenanceCost;
    std::string buildingId;

public:
    Building(const std::string& name, double area, int constructionYear);
    virtual ~Building() = default;

    virtual void displayInfo() const;
    virtual double calculateValue() const;
    virtual void performMaintenance();
    virtual void inspectBuilding();

    // Геттеры
    std::string getName() const;
    double getArea() const;
    int getConstructionYear() const;
    std::string getBuildingMaterial() const;
    std::string getCondition() const;
    std::string getLocationOnFarm() const;
    bool getHasElectricity() const;
    bool getHasWaterSupply() const;
    std::string getRoofType() const;
    double getMaintenanceCost() const;
    std::string getBuildingId() const;

    // Сеттеры
    void setName(const std::string& name);
    void setArea(double area);
    void setConstructionYear(int year);
    void setBuildingMaterial(const std::string& material);
    void setCondition(const std::string& condition);
    void setLocationOnFarm(const std::string& location);
    void setHasElectricity(bool electricity);
    void setHasWaterSupply(bool water);
    void setRoofType(const std::string& roofType);
    void setMaintenanceCost(double cost);
    void setBuildingId(const std::string& id);

    virtual int calculateAge(int currentYear) const;
    virtual void upgradeFacilities();
    virtual bool needsRenovation() const;
    virtual void calculateInsuranceCost() const;
};

#endif // BUILDING_H