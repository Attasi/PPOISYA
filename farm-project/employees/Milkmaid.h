#ifndef MILKMAID_H
#define MILKMAID_H

#include "Employee.h"
#include <string>
#include <vector>

class Milkmaid : public Employee {
private:
    int cowsMilkedPerDay;
    double milkCollected; // литров в день
    std::string milkingEquipment;
    std::vector<std::string> cowNames;
    std::string milkingSchedule;
    double milkQualityScore; // 1-10
    bool isCertified;
    std::string hygieneProtocol;
    int milkingSessionsPerDay;

public:
    Milkmaid(const std::string& name, int age, double salary = 2200.0);

    void work() const override;
    void milkCow(const std::string& cowName);
    void checkMilkQuality();
    void cleanMilkingEquipment();
    void recordMilkProduction();

    // Геттеры
    int getCowsMilkedPerDay() const;
    double getMilkCollected() const;
    std::string getMilkingEquipment() const;
    std::vector<std::string> getCowNames() const;
    std::string getMilkingSchedule() const;
    double getMilkQualityScore() const;
    bool getIsCertified() const;
    std::string getHygieneProtocol() const;
    int getMilkingSessionsPerDay() const;

    // Сеттеры
    void setCowsMilkedPerDay(int cows);
    void setMilkCollected(double milk);
    void setMilkingEquipment(const std::string& equipment);
    void setCowNames(const std::vector<std::string>& names);
    void setMilkingSchedule(const std::string& schedule);
    void setMilkQualityScore(double score);
    void setIsCertified(bool certified);
    void setHygieneProtocol(const std::string& protocol);
    void setMilkingSessionsPerDay(int sessions);

    void calculateDailyYield() const;
    void pasteurizeMilk();
    void trainNewCow(const std::string& cowName);
    void maintainMilkingMachine();
};

#endif // MILKMAID_H