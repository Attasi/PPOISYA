#ifndef COMPOUND_FEED_H
#define COMPOUND_FEED_H

#include "Feed.h"
#include <string>
#include <vector>

class CompoundFeed : public Feed {
private:
    std::vector<std::string> ingredients;
    std::string targetAnimal;
    std::string pelletSize; // Small, Medium, Large
    double pelletDurability; // прочность гранул в %
    std::string additiveType; // Vitamins, Minerals, Probiotics
    bool isMedicated;
    std::string medicationType;
    double fatContent; // содержание жира в %
    std::string formulaCode;

public:
    CompoundFeed(double quantity, const std::string& targetAnimal = "Chicken",
                 const std::string& pelletSize = "Medium");

    void displayInfo() const override;
    void pelletize();
    void addIngredient(const std::string& ingredient);
    void addMedication(const std::string& medication);
    void mixFeed();

    // Геттеры
    std::vector<std::string> getIngredients() const;
    std::string getTargetAnimal() const;
    std::string getPelletSize() const;
    double getPelletDurability() const;
    std::string getAdditiveType() const;
    bool getIsMedicated() const;
    std::string getMedicationType() const;
    double getFatContent() const;
    std::string getFormulaCode() const;

    // Сеттеры
    void setIngredients(const std::vector<std::string>& ingredients);
    void setTargetAnimal(const std::string& animal);
    void setPelletSize(const std::string& size);
    void setPelletDurability(double durability);
    void setAdditiveType(const std::string& additive);
    void setIsMedicated(bool medicated);
    void setMedicationType(const std::string& medication);
    void setFatContent(double fat);
    void setFormulaCode(const std::string& code);

    double calculateCompleteNutrition() const;
    bool isSuitableForAnimal(const std::string& animalType) const override;
    void createCustomFormula(const std::vector<std::string>& newIngredients);
    void testPelletQuality();
};

#endif // COMPOUND_FEED_H