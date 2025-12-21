#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Building.h"
#include <string>
#include <vector>
#include <map>

class Warehouse : public Building {
private:
    double storageCapacity; // в кубических метрах
    std::map<std::string, double> storedItems; // предмет -> количество
    std::string climateControl; // None, Refrigerated, Humidity-controlled
    int numberOfRacks;
    bool hasLoadingDock;
    std::string inventorySystem;
    double currentOccupancy; // текущая заполненность в %
    std::string securitySystem;
    bool hasForklift;

public:
    Warehouse(const std::string& name, double area, int constructionYear,
              double storageCapacity = 1000.0);

    void displayInfo() const override;
    void storeItem(const std::string& item, double quantity);
    void retrieveItem(const std::string& item, double quantity);
    void conductInventory();
    void organizeShelves();

    // Геттеры
    double getStorageCapacity() const;
    std::map<std::string, double> getStoredItems() const;
    std::string getClimateControl() const;
    int getNumberOfRacks() const;
    bool getHasLoadingDock() const;
    std::string getInventorySystem() const;
    double getCurrentOccupancy() const;
    std::string getSecuritySystem() const;
    bool getHasForklift() const;

    // Сеттеры
    void setStorageCapacity(double capacity);
    void setStoredItems(const std::map<std::string, double>& items);
    void setClimateControl(const std::string& control);
    void setNumberOfRacks(int racks);
    void setHasLoadingDock(bool dock);
    void setInventorySystem(const std::string& system);
    void setCurrentOccupancy(double occupancy);
    void setSecuritySystem(const std::string& security);
    void setHasForklift(bool forklift);

    double calculateAvailableSpace() const;
    void optimizeStorage();
    void checkExpiryDates();
    void prepareForHarvestSeason();
};

#endif // WAREHOUSE_H