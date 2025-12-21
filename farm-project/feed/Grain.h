#ifndef GRAIN_H
#define GRAIN_H

#include "Feed.h"
#include <string>

class Grain : public Feed {
private:
    std::string grainType; // Corn, Wheat, Barley, Oats
    double starchContent; // содержание крахмала в %
    std::string processingMethod; // Whole, Cracked, Ground
    double testWeight; // вес теста в кг/гл
    std::string origin;
    bool isGMO;
    double germinationRate; // процент всхожести
    std::string kernelSize; // Small, Medium, Large
    double foreignMaterial; // содержание примесей в %

public:
    Grain(double quantity, const std::string& grainType = "Corn",
          const std::string& processingMethod = "Whole");

    void displayInfo() const override;
    void grindGrain();
    void cleanGrain();
    void testGermination();
    void mixWithOtherGrains(const std::string& otherGrain, double amount);

    // Геттеры
    std::string getGrainType() const;
    double getStarchContent() const;
    std::string getProcessingMethod() const;
    double getTestWeight() const;
    std::string getOrigin() const;
    bool getIsGMO() const;
    double getGerminationRate() const;
    std::string getKernelSize() const;
    double getForeignMaterial() const;

    // Сеттеры
    void setGrainType(const std::string& type);
    void setStarchContent(double starch);
    void setProcessingMethod(const std::string& method);
    void setTestWeight(double weight);
    void setOrigin(const std::string& origin);
    void setIsGMO(bool gmo);
    void setGerminationRate(double rate);
    void setKernelSize(const std::string& size);
    void setForeignMaterial(double material);

    double calculateEnergyDensity() const;
    bool isSuitableForAnimal(const std::string& animalType) const override;
    void processToMethod(const std::string& targetMethod);
    void checkForContaminants();
};

#endif // GRAIN_H