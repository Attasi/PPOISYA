#ifndef EGG_H
#define EGG_H

#include "Product.h"
#include <string>

class Egg : public Product {
private:
    std::string eggSize; // Small, Medium, Large, X-Large
    std::string shellColor; // White, Brown
    double yolkColorGrade; // 1-15 (по шкале Рош)
    bool isFertilized;
    std::string layingDate;
    std::string chickenBreed;
    double shellThickness; // мм
    bool isFreeRange;
    int cholesterolContent; // мг на яйцо

public:
    Egg(int quantity, const std::string& eggSize = "Large",
        const std::string& shellColor = "Brown");

    void displayInfo() const override;
    void candleEgg(); // проверка на просвет
    void gradeEgg();
    void washEggs();
    void packInCarton();

    // Геттеры
    std::string getEggSize() const;
    std::string getShellColor() const;
    double getYolkColorGrade() const;
    bool getIsFertilized() const;
    std::string getLayingDate() const;
    std::string getChickenBreed() const;
    double getShellThickness() const;
    bool getIsFreeRange() const;
    int getCholesterolContent() const;

    // Сеттеры
    void setEggSize(const std::string& size);
    void setShellColor(const std::string& color);
    void setYolkColorGrade(double grade);
    void setIsFertilized(bool fertilized);
    void setLayingDate(const std::string& date);
    void setChickenBreed(const std::string& breed);
    void setShellThickness(double thickness);
    void setIsFreeRange(bool freeRange);
    void setCholesterolContent(int cholesterol);

    bool checkFreshness() const;
    void incubateIfFertilized();
    double calculateProteinContent() const;
    void sortBySize();
};

#endif // EGG_H