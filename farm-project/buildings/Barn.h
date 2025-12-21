#ifndef BARN_H
#define BARN_H

#include "Building.h"
#include <string>
#include <vector>

class Barn : public Building {
private:
    int animalCapacity;
    std::vector<std::string> housedAnimals;
    int numberOfStalls;
    bool hasHayloft;
    double hayStorageCapacity; // тонн
    std::string ventilationSystem;
    int milkingStations;
    bool hasInsulation;
    std::string manureManagement;

public:
    Barn(const std::string& name, double area, int constructionYear,
         int animalCapacity = 50);

    void displayInfo() const override;
    void houseAnimal(const std::string& animalType, int count);
    void storeHay(double amount);
    void cleanBarn();
    void checkVentilation();

    // Геттеры
    int getAnimalCapacity() const;
    std::vector<std::string> getHousedAnimals() const;
    int getNumberOfStalls() const;
    bool getHasHayloft() const;
    double getHayStorageCapacity() const;
    std::string getVentilationSystem() const;
    int getMilkingStations() const;
    bool getHasInsulation() const;
    std::string getManureManagement() const;

    // Сеттеры
    void setAnimalCapacity(int capacity);
    void setHousedAnimals(const std::vector<std::string>& animals);
    void setNumberOfStalls(int stalls);
    void setHasHayloft(bool hayloft);
    void setHayStorageCapacity(double capacity);
    void setVentilationSystem(const std::string& system);
    void setMilkingStations(int stations);
    void setHasInsulation(bool insulation);
    void setManureManagement(const std::string& management);

    double calculateAvailableSpace() const;
    void prepareForWinter();
    void installMilkingEquipment();
    void manageManure();
};

#endif // BARN_H