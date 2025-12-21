#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

class Product {
protected:
    std::string name;
    double quantity; // количество (кг, литры, штуки)
    double pricePerUnit;
    std::string productionDate;
    std::string expirationDate;
    std::string qualityGrade; // A, B, C
    std::string storageConditions;
    bool isOrganic;
    std::string unitOfMeasure; // кг, л, шт
    std::string producerId;

public:
    Product(const std::string& name, double quantity, double pricePerUnit);
    virtual ~Product() = default;

    virtual void displayInfo() const;
    virtual double calculateTotalValue() const;
    virtual bool isExpired(const std::string& currentDate) const;
    virtual void updateQuality();
    virtual void package();

    // Геттеры
    std::string getName() const;
    double getQuantity() const;
    double getPricePerUnit() const;
    std::string getProductionDate() const;
    std::string getExpirationDate() const;
    std::string getQualityGrade() const;
    std::string getStorageConditions() const;
    bool getIsOrganic() const;
    std::string getUnitOfMeasure() const;
    std::string getProducerId() const;

    // Сеттеры
    void setName(const std::string& name);
    void setQuantity(double quantity);
    void setPricePerUnit(double price);
    void setProductionDate(const std::string& date);
    void setExpirationDate(const std::string& date);
    void setQualityGrade(const std::string& grade);
    void setStorageConditions(const std::string& conditions);
    void setIsOrganic(bool organic);
    void setUnitOfMeasure(const std::string& unit);
    void setProducerId(const std::string& id);

    virtual void applyDiscount(double percentage);
    virtual bool meetsExportStandards() const;
    virtual void inspectQuality();
};

#endif // PRODUCT_H