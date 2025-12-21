#ifndef WOOL_H
#define WOOL_H

#include "Product.h"
#include <string>

class Wool : public Product {
private:
    std::string sheepBreed;
    std::string woolType; // Fine, Medium, Coarse
    double fiberDiameter; // микрометры
    std::string color;
    int stapleLength; // мм
    std::string processingStage; // Raw, Washed, Carded, Spun
    double lanolinContent; // содержание ланолина в %
    bool isOrganic;
    std::string spinningQuality;

    // Вспомогательный метод для расчета базовой цены
    static double calculateBasePrice(const std::string& breed, const std::string& type);

public:
    Wool(double quantity, const std::string& sheepBreed = "Merino",
         const std::string& woolType = "Fine");

    void displayInfo() const override;
    void washWool();
    void cardWool();
    void spinIntoYarn();
    void dyeWool(const std::string& color);

    // Геттеры
    std::string getSheepBreed() const;
    std::string getWoolType() const;
    double getFiberDiameter() const;
    std::string getColor() const;
    int getStapleLength() const;
    std::string getProcessingStage() const;
    double getLanolinContent() const;
    bool getIsOrganic() const;
    std::string getSpinningQuality() const;

    // Сеттеры
    void setSheepBreed(const std::string& breed);
    void setWoolType(const std::string& type);
    void setFiberDiameter(double diameter);
    void setColor(const std::string& color);
    void setStapleLength(int length);
    void setProcessingStage(const std::string& stage);
    void setLanolinContent(double content);
    void setIsOrganic(bool organic);
    void setSpinningQuality(const std::string& quality);

    double calculateWarmthRating() const;
    void gradeWool();
    bool isSuitableForClothing() const;
    void processToStage(const std::string& targetStage);
};

#endif // WOOL_H