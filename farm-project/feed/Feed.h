#ifndef FEED_H
#define FEED_H

#include <string>
#include <iostream>

class Feed {
protected:
    std::string name;
    double quantity; // количество в кг
    double pricePerKg;
    std::string productionDate;
    std::string expirationDate;
    std::string storageLocation;
    double proteinContent; // содержание белка в %
    double fiberContent; // содержание клетчатки в %
    double moistureContent; // влажность в %
    std::string qualityGrade;
    bool isOrganic;

public:
    Feed(const std::string& name, double quantity, double pricePerKg);
    virtual ~Feed() = default;

    virtual void displayInfo() const;
    virtual double calculateTotalValue() const;
    virtual bool isExpired(const std::string& currentDate) const;
    virtual void checkQuality();
    virtual void store();

    // Геттеры
    std::string getName() const;
    double getQuantity() const;
    double getPricePerKg() const;
    std::string getProductionDate() const;
    std::string getExpirationDate() const;
    std::string getStorageLocation() const;
    double getProteinContent() const;
    double getFiberContent() const;
    double getMoistureContent() const;
    std::string getQualityGrade() const;
    bool getIsOrganic() const;

    // Сеттеры
    void setName(const std::string& name);
    void setQuantity(double quantity);
    void setPricePerKg(double price);
    void setProductionDate(const std::string& date);
    void setExpirationDate(const std::string& date);
    void setStorageLocation(const std::string& location);
    void setProteinContent(double protein);
    void setFiberContent(double fiber);
    void setMoistureContent(double moisture);
    void setQualityGrade(const std::string& grade);
    void setIsOrganic(bool organic);

    virtual double calculateNutritionalValue() const;
    virtual bool isSuitableForAnimal(const std::string& animalType) const;
    virtual void applyDiscount(double percentage);
    virtual void updateStock(double amount);
};

#endif // FEED_H