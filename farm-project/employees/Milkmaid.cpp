#include "Milkmaid.h"
#include "EmployeeExceptions.h"
#include <iostream>

Milkmaid::Milkmaid(const std::string& name, int age, double salary)
        : Employee(name, age, "Milkmaid", salary) {
    // Проверки для доярки
    if (salary < 1800) {
        throw EmployeeException("Milkmaid salary too low: $" + std::to_string(salary) + " (min $1800)");
    }

    cowsMilkedPerDay = 20;
    milkCollected = 400.0;
    milkingEquipment = "Automatic milking machine";
    milkingSchedule = "6:00 AM, 2:00 PM, 10:00 PM";
    milkQualityScore = 8.5;
    isCertified = true;
    hygieneProtocol = "FDA Standard";
    milkingSessionsPerDay = 3;

    cowNames = {"Bessie", "Daisy", "Molly", "Buttercup"};
    setSpecialization("Dairy Production");
    setAddress("Dairy Quarters");
}

void Milkmaid::work() const {
    std::cout << getName() << " is milking cows in the dairy barn." << std::endl;
}

void Milkmaid::milkCow(const std::string& cowName) {
    if (cowName.empty()) {
        throw EmployeeException("Cow name cannot be empty");
    }
    if (cowsMilkedPerDay >= 50) {
        throw EmployeeException(getName() + " cannot milk more than 50 cows per day");
    }

    // Проверка на дубликаты
    for (const auto& name : cowNames) {
        if (name == cowName) {
            throw EmployeeException("Cow " + cowName + " is already in the milking list");
        }
    }

    cowNames.push_back(cowName);
    cowsMilkedPerDay++;
    milkCollected += 20.0; // Примерное количество молока от одной коровы

    std::cout << getName() << " milked " << cowName << ". Collected 20 liters." << std::endl;
    std::cout << "Total cows milked today: " << cowsMilkedPerDay << std::endl;
    std::cout << "Total milk collected: " << milkCollected << " liters" << std::endl;
}

void Milkmaid::checkMilkQuality() {
    if (milkQualityScore < 5) {
        throw EmployeeException("CRITICAL: Milk quality dangerously low: " +
                                std::to_string(milkQualityScore) + "/10 (min 5)");
    }
    if (!isCertified) {
        throw InsufficientQualificationException(getName(), "Milk quality testing",
                                                 "Not certified");
    }

    std::cout << getName() << " is checking milk quality..." << std::endl;

    if (milkQualityScore >= 9.0) {
        std::cout << "Excellent quality milk!" << std::endl;
        setSalary(getSalary() * 1.05); // Бонус за качество
    } else if (milkQualityScore >= 7.0) {
        std::cout << "Good quality milk." << std::endl;
    } else {
        std::cout << "Quality needs improvement." << std::endl;
        milkQualityScore = 7.0; // Минимальный стандарт
    }
}

void Milkmaid::cleanMilkingEquipment() {
    if (milkingEquipment.empty()) {
        throw EmployeeException("Milking equipment not specified");
    }
    if (hygieneProtocol.empty()) {
        throw EmployeeException("Hygiene protocol not specified");
    }

    std::cout << getName() << " is cleaning the " << milkingEquipment << std::endl;
    milkQualityScore += 0.5; // Чистота улучшает качество
    std::cout << "Milk quality improved to: " << milkQualityScore << "/10" << std::endl;
}

void Milkmaid::recordMilkProduction() {
    if (cowsMilkedPerDay <= 0) {
        throw EmployeeException("No cows milked today to record production");
    }
    if (milkCollected <= 0) {
        throw EmployeeException("No milk collected to record");
    }

    std::cout << "=== Milk Production Record ===" << std::endl;
    std::cout << "Milkmaid: " << getName() << std::endl;
    std::cout << "Date: Today" << std::endl;
    std::cout << "Cows milked: " << cowsMilkedPerDay << std::endl;
    std::cout << "Milk collected: " << milkCollected << " liters" << std::endl;
    std::cout << "Quality score: " << milkQualityScore << "/10" << std::endl;
    std::cout << "Milking sessions: " << milkingSessionsPerDay << std::endl;

    double milkValue = milkCollected * 0.5; // $0.5 за литр
    std::cout << "Total milk value: $" << milkValue << std::endl;
}

int Milkmaid::getCowsMilkedPerDay() const { return cowsMilkedPerDay; }
double Milkmaid::getMilkCollected() const { return milkCollected; }
std::string Milkmaid::getMilkingEquipment() const { return milkingEquipment; }
std::vector<std::string> Milkmaid::getCowNames() const { return cowNames; }
std::string Milkmaid::getMilkingSchedule() const { return milkingSchedule; }
double Milkmaid::getMilkQualityScore() const { return milkQualityScore; }
bool Milkmaid::getIsCertified() const { return isCertified; }
std::string Milkmaid::getHygieneProtocol() const { return hygieneProtocol; }
int Milkmaid::getMilkingSessionsPerDay() const { return milkingSessionsPerDay; }

void Milkmaid::setCowsMilkedPerDay(int cows) {
    if (cows < 0 || cows > 50) {
        throw EmployeeException("Cows milked per day must be between 0-50: " + std::to_string(cows));
    }
    cowsMilkedPerDay = cows;
}

void Milkmaid::setMilkCollected(double milk) {
    if (milk < 0 || milk > 2000) {
        throw EmployeeException("Milk collected must be between 0-2000 liters: " + std::to_string(milk));
    }
    milkCollected = milk;
}

void Milkmaid::setMilkingEquipment(const std::string& equipment) {
    if (equipment.empty()) {
        throw EmployeeException("Milking equipment cannot be empty");
    }
    milkingEquipment = equipment;
}

void Milkmaid::setCowNames(const std::vector<std::string>& names) {
    if (names.empty()) {
        throw EmployeeException("Cow names list cannot be empty");
    }
    cowNames = names;
}

void Milkmaid::setMilkingSchedule(const std::string& schedule) {
    if (schedule.empty()) {
        throw EmployeeException("Milking schedule cannot be empty");
    }
    milkingSchedule = schedule;
}

void Milkmaid::setMilkQualityScore(double score) {
    if (score < 0 || score > 10) {
        throw EmployeeException("Milk quality score must be between 0-10: " + std::to_string(score));
    }
    milkQualityScore = score;
}

void Milkmaid::setIsCertified(bool certified) { isCertified = certified; }

void Milkmaid::setHygieneProtocol(const std::string& protocol) {
    if (protocol.empty()) {
        throw EmployeeException("Hygiene protocol cannot be empty");
    }
    hygieneProtocol = protocol;
}

void Milkmaid::setMilkingSessionsPerDay(int sessions) {
    if (sessions < 0 || sessions > 5) {
        throw EmployeeException("Milking sessions must be between 0-5 per day: " + std::to_string(sessions));
    }
    milkingSessionsPerDay = sessions;
}

void Milkmaid::calculateDailyYield() const {
    if (cowsMilkedPerDay <= 0) {
        throw EmployeeException("No cows milked to calculate yield");
    }
    if (milkCollected <= 0) {
        throw EmployeeException("No milk collected to calculate yield");
    }

    double averagePerCow = milkCollected / cowsMilkedPerDay;
    std::cout << "Daily milk yield analysis:" << std::endl;
    std::cout << "Average per cow: " << averagePerCow << " liters" << std::endl;

    if (averagePerCow > 25) {
        std::cout << "Excellent yield!" << std::endl;
    } else if (averagePerCow > 18) {
        std::cout << "Good yield." << std::endl;
    } else {
        std::cout << "Yield needs improvement." << std::endl;
    }
}

void Milkmaid::pasteurizeMilk() {
    if (milkCollected <= 0) {
        throw EmployeeException("No milk to pasteurize");
    }
    if (!isCertified) {
        throw InsufficientQualificationException(getName(), "Pasteurization",
                                                 "Not certified for milk processing");
    }

    std::cout << getName() << " is pasteurizing " << milkCollected << " liters of milk." << std::endl;
    milkQualityScore = 9.5; // Пастеризация улучшает качество
    std::cout << "Milk quality after pasteurization: " << milkQualityScore << "/10" << std::endl;
}

void Milkmaid::trainNewCow(const std::string& cowName) {
    if (cowName.empty()) {
        throw EmployeeException("Cow name cannot be empty");
    }
    if (!isCertified) {
        throw InsufficientQualificationException(getName(), "Cow training",
                                                 "Not certified for animal training");
    }

    std::cout << getName() << " is training " << cowName << " for milking." << std::endl;
    std::cout << "Using certified training methods." << std::endl;
    std::cout << "Training successful. " << cowName << " added to milking roster." << std::endl;
}

void Milkmaid::maintainMilkingMachine() {
    if (milkingEquipment.empty()) {
        throw EmployeeException("Milking equipment not specified");
    }

    std::cout << getName() << " is performing maintenance on the " << milkingEquipment << std::endl;
    std::cout << "Checking vacuum levels, pulsation rates, and sanitizing components." << std::endl;
    milkQualityScore += 0.2; // Техническое обслуживание улучшает качество
}