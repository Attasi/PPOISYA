#include "Warehouse.h"
#include "BuildingExceptions.h"
#include <iostream>

Warehouse::Warehouse(const std::string& name, double area, int constructionYear,
                     double storageCapacity)
        : Building(name, area, constructionYear) {
    // Дополнительные проверки для склада
    if (storageCapacity <= 0) {
        throw BuildingException("Storage capacity must be positive: " +
                                std::to_string(storageCapacity));
    }
    if (storageCapacity > 100000) {
        throw BuildingException("Storage capacity too large: " +
                                std::to_string(storageCapacity) + " cubic meters (max 100,000)");
    }
    if (area < storageCapacity / 10) {
        throw BuildingException("Warehouse area too small for storage capacity: " +
                                std::to_string(area) + " sq.m for " +
                                std::to_string(storageCapacity) + " cubic meters");
    }

    this->storageCapacity = storageCapacity;
    this->climateControl = "Humidity-controlled";
    this->numberOfRacks = 50;
    this->hasLoadingDock = true;
    this->inventorySystem = "Manual with barcodes";
    this->currentOccupancy = 65.0;
    this->securitySystem = "Alarm and cameras";
    this->hasForklift = true;

    setBuildingMaterial("Concrete and Steel");
    setRoofType("Flat");
    setLocationOnFarm("Northeast Corner");
    setName("Warehouse: " + name);

    // Начальные запасы
    storedItems = {
            {"Wheat", 500.0},
            {"Corn", 300.0},
            {"Fertilizer", 200.0},
            {"Animal Feed", 400.0}
    };
}

void Warehouse::displayInfo() const {
    Building::displayInfo();
    std::cout << "--- Warehouse Specific ---" << std::endl;
    std::cout << "Storage Capacity: " << storageCapacity << " cubic meters" << std::endl;
    std::cout << "Climate Control: " << climateControl << std::endl;
    std::cout << "Number of Racks: " << numberOfRacks << std::endl;
    std::cout << "Has Loading Dock: " << (hasLoadingDock ? "Yes" : "No") << std::endl;
    std::cout << "Inventory System: " << inventorySystem << std::endl;
    std::cout << "Current Occupancy: " << currentOccupancy << "%" << std::endl;
    std::cout << "Security System: " << securitySystem << std::endl;
    std::cout << "Has Forklift: " << (hasForklift ? "Yes" : "No") << std::endl;

    if (storedItems.empty()) {
        throw BuildingException(getName() + " has no stored items");
    }

    std::cout << "Stored Items (" << storedItems.size() << " types):" << std::endl;
    for (const auto& item : storedItems) {
        std::cout << "  - " << item.first << ": " << item.second << " units" << std::endl;
    }
}

void Warehouse::storeItem(const std::string& item, double quantity) {
    if (item.empty()) {
        throw BuildingException("Item name cannot be empty");
    }
    if (quantity <= 0) {
        throw BuildingException("Storage quantity must be positive: " + std::to_string(quantity));
    }

    double availableSpace = storageCapacity * (100 - currentOccupancy) / 100;

    if (quantity > availableSpace) {
        throw BuildingCapacityException(getName(), storageCapacity,
                                        currentOccupancy * storageCapacity / 100 + quantity);
    }
    if (quantity > 10000) {
        throw BuildingException("Cannot store " + std::to_string(quantity) +
                                " units at once (max 10,000 per transaction)");
    }

    // Проверка на опасные материалы
    if ((item == "Fertilizer" || item == "Pesticides") && climateControl != "Special hazardous") {
        throw BuildingSafetyException(getName(), "Storing hazardous materials without proper climate control", 8);
    }

    storedItems[item] += quantity;
    currentOccupancy = (currentOccupancy * storageCapacity / 100 + quantity) / storageCapacity * 100;

    std::cout << "Stored " << quantity << " units of " << item << std::endl;
    std::cout << "New occupancy: " << currentOccupancy << "%" << std::endl;
}

void Warehouse::retrieveItem(const std::string& item, double quantity) {
    if (item.empty()) {
        throw BuildingException("Item name cannot be empty");
    }
    if (quantity <= 0) {
        throw BuildingException("Retrieval quantity must be positive: " + std::to_string(quantity));
    }

    if (storedItems.find(item) == storedItems.end()) {
        throw BuildingException("Item " + item + " not found in warehouse");
    }

    if (storedItems[item] < quantity) {
        throw BuildingException("Insufficient quantity of " + item +
                                ": available " + std::to_string(storedItems[item]) +
                                ", requested " + std::to_string(quantity));
    }

    if (!hasForklift && quantity > 1000) {
        throw BuildingException("Cannot retrieve " + std::to_string(quantity) +
                                " units without forklift (max 1000 manually)");
    }

    storedItems[item] -= quantity;
    currentOccupancy = (currentOccupancy * storageCapacity / 100 - quantity) / storageCapacity * 100;

    std::cout << "Retrieved " << quantity << " units of " << item << std::endl;
    std::cout << "Remaining " << item << ": " << storedItems[item] << " units" << std::endl;
    std::cout << "New occupancy: " << currentOccupancy << "%" << std::endl;

    // Удаляем запись если количество = 0
    if (storedItems[item] == 0) {
        storedItems.erase(item);
    }
}

void Warehouse::conductInventory() {
    if (storedItems.empty()) {
        throw BuildingException("Warehouse is empty, no inventory to conduct");
    }
    if (inventorySystem.empty()) {
        throw BuildingException("Inventory system not specified");
    }

    std::cout << "=== Warehouse Inventory ===" << std::endl;
    std::cout << "Warehouse: " << getName() << std::endl;
    std::cout << "Date: Today" << std::endl;
    std::cout << "Total items: " << storedItems.size() << std::endl;

    double totalValue = 0;
    for (const auto& item : storedItems) {
        double itemValue = item.second * 10; // $10 за единицу (примерно)
        std::cout << "  - " << item.first << ": " << item.second
                  << " units ($" << itemValue << ")" << std::endl;
        totalValue += itemValue;
    }

    std::cout << "Total inventory value: $" << totalValue << std::endl;
    std::cout << "Storage occupancy: " << currentOccupancy << "%" << std::endl;

    if (currentOccupancy > 95) {
        throw BuildingCapacityException(getName(), storageCapacity,
                                        currentOccupancy * storageCapacity / 100);
    }
}

void Warehouse::organizeShelves() {
    if (numberOfRacks <= 0) {
        throw BuildingException("No racks to organize");
    }
    if (currentOccupancy > 90) {
        throw BuildingException("Cannot organize shelves when occupancy > 90%");
    }

    std::cout << "Organizing warehouse shelves..." << std::endl;
    std::cout << "Reorganizing " << numberOfRacks << " racks for better space utilization." << std::endl;
    std::cout << "Grouping similar items together." << std::endl;

    // Оптимизация увеличивает эффективность
    double efficiencyImprovement = 1.1; // 10% улучшение
    storageCapacity *= efficiencyImprovement;
    std::cout << "Storage capacity increased to " << storageCapacity << " cubic meters" << std::endl;
}

double Warehouse::getStorageCapacity() const { return storageCapacity; }
std::map<std::string, double> Warehouse::getStoredItems() const { return storedItems; }
std::string Warehouse::getClimateControl() const { return climateControl; }
int Warehouse::getNumberOfRacks() const { return numberOfRacks; }
bool Warehouse::getHasLoadingDock() const { return hasLoadingDock; }
std::string Warehouse::getInventorySystem() const { return inventorySystem; }
double Warehouse::getCurrentOccupancy() const { return currentOccupancy; }
std::string Warehouse::getSecuritySystem() const { return securitySystem; }
bool Warehouse::getHasForklift() const { return hasForklift; }

void Warehouse::setStorageCapacity(double capacity) {
    if (capacity <= 0 || capacity > 100000) {
        throw BuildingException("Storage capacity must be between 0-100000 cubic meters: " +
                                std::to_string(capacity));
    }
    storageCapacity = capacity;
}

void Warehouse::setStoredItems(const std::map<std::string, double>& items) {
    storedItems = items;
    // Пересчитываем занятость
    double totalStored = 0;
    for (const auto& item : items) {
        totalStored += item.second;
    }
    currentOccupancy = (totalStored / storageCapacity) * 100;
}

void Warehouse::setClimateControl(const std::string& control) {
    if (control.empty()) {
        throw BuildingException("Climate control cannot be empty");
    }
    climateControl = control;
}

void Warehouse::setNumberOfRacks(int racks) {
    if (racks < 0 || racks > 1000) {
        throw BuildingException("Number of racks must be between 0-1000: " + std::to_string(racks));
    }
    numberOfRacks = racks;
}

void Warehouse::setHasLoadingDock(bool dock) { hasLoadingDock = dock; }

void Warehouse::setInventorySystem(const std::string& system) {
    if (system.empty()) {
        throw BuildingException("Inventory system cannot be empty");
    }
    inventorySystem = system;
}

void Warehouse::setCurrentOccupancy(double occupancy) {
    if (occupancy < 0 || occupancy > 100) {
        throw BuildingException("Current occupancy must be between 0-100%: " + std::to_string(occupancy));
    }
    currentOccupancy = occupancy;
}

void Warehouse::setSecuritySystem(const std::string& security) {
    if (security.empty()) {
        throw BuildingException("Security system cannot be empty");
    }
    securitySystem = security;
}

void Warehouse::setHasForklift(bool forklift) { hasForklift = forklift; }

double Warehouse::calculateAvailableSpace() const {
    double available = storageCapacity * (100 - currentOccupancy) / 100;
    if (available < 0) {
        throw BuildingCapacityException(getName(), storageCapacity,
                                        currentOccupancy * storageCapacity / 100);
    }
    return available;
}

void Warehouse::optimizeStorage() {
    if (currentOccupancy > 95) {
        throw BuildingCapacityException(getName(), storageCapacity,
                                        currentOccupancy * storageCapacity / 100);
    }

    std::cout << "Optimizing warehouse storage..." << std::endl;

    if (currentOccupancy > 80) {
        std::cout << "High occupancy detected. Adding more racks..." << std::endl;
        numberOfRacks += 20;
        storageCapacity *= 1.2;
        std::cout << "Added 20 racks. New capacity: " << storageCapacity << " cubic meters" << std::endl;
    }

    if (!hasForklift && currentOccupancy > 50) {
        std::cout << "Installing forklift for better material handling." << std::endl;
        hasForklift = true;
        setMaintenanceCost(getMaintenanceCost() + 300);
    }

    std::cout << "Storage optimization complete." << std::endl;
}

void Warehouse::checkExpiryDates() {
    if (storedItems.empty()) {
        throw BuildingException("No items to check expiry dates");
    }

    std::cout << "Checking expiry dates of stored items..." << std::endl;

    // Проверяем типичные сроки годности
    for (const auto& item : storedItems) {
        if (item.first == "Fertilizer" || item.first == "Animal Feed") {
            if (climateControl != "Humidity-controlled" && climateControl != "Refrigerated") {
                throw BuildingException(item.first + " stored without proper climate control - may expire early");
            }
            std::cout << "  - " << item.first << ": Check manufacturing date, typically 6-12 months shelf life." << std::endl;
        } else if (item.first.find("Grain") != std::string::npos) {
            if (climateControl != "Humidity-controlled") {
                throw BuildingSafetyException(getName(), "Grain stored without humidity control - mold risk", 7);
            }
            std::cout << "  - " << item.first << ": Store in dry conditions, shelf life 1-2 years." << std::endl;
        }
    }

    std::cout << "Expiry date check completed." << std::endl;
}

void Warehouse::prepareForHarvestSeason() {
    if (currentOccupancy > 90) {
        throw BuildingCapacityException(getName(), storageCapacity,
                                        currentOccupancy * storageCapacity / 100);
    }

    std::cout << "Preparing warehouse for harvest season..." << std::endl;

    // Освобождаем место для нового урожая
    double spaceNeeded = storageCapacity * 0.4; // 40% для нового урожая
    if (currentOccupancy > 60) {
        std::cout << "Clearing space for new harvest..." << std::endl;
        // Здесь можно добавить логику перемещения или продажи старых запасов
    }

    // Подготавливаем оборудование
    if (hasForklift) {
        std::cout << "Servicing forklift for heavy use during harvest." << std::endl;
    } else {
        throw BuildingException("Cannot handle harvest without forklift");
    }

    // Проверяем климат-контроль
    if (climateControl == "Humidity-controlled") {
        std::cout << "Setting humidity control for grain storage (optimal: 12-14%)." << std::endl;
    } else {
        throw BuildingException("Warehouse needs humidity control for harvest storage");
    }

    std::cout << "Warehouse ready for harvest season!" << std::endl;
}