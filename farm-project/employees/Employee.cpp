#include "Employee.h"
#include "EmployeeExceptions.h"
#include <iostream>

Employee::Employee(const std::string& name, int age, const std::string& position, double salary) {
    // Проверка входных параметров
    if (name.empty()) {
        throw EmployeeException("Employee name cannot be empty");
    }
    if (age < 18) {
        throw EmployeeException("Employee must be at least 18 years old: " + std::to_string(age));
    }
    if (age > 70) {
        throw EmployeeException("Employee age too high for farm work: " + std::to_string(age) + " (max 70)");
    }
    if (position.empty()) {
        throw EmployeeException("Employee position cannot be empty");
    }
    if (salary < 1000) {
        throw EmployeeException("Employee salary too low: $" + std::to_string(salary) + " (min $1000)");
    }
    if (salary > 10000) {
        throw EmployeeException("Employee salary unrealistically high: $" + std::to_string(salary) + " (max $10000)");
    }

    this->name = name;
    this->age = age;
    this->position = position;
    this->salary = salary;
    this->experienceYears = 1;
    this->hireDate = "2024-01-01";
    this->contactNumber = "+1234567890";
    this->address = "Farm Housing";
    this->isFullTime = true;
    this->vacationDays = 20;
    this->specialization = "General Farm Work";

    static int counter = 1;
    this->employeeId = "EMP" + std::to_string(counter++);
}

void Employee::work() const {
    std::cout << name << " is working as a " << position << std::endl;
}

void Employee::takeBreak() const {
    std::cout << name << " is taking a break." << std::endl;
}

void Employee::attendMeeting() const {
    std::cout << name << " is attending a farm management meeting." << std::endl;
}

void Employee::displayInfo() const {
    std::cout << "=== Employee Information ===" << std::endl;
    std::cout << "Employee ID: " << employeeId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Position: " << position << std::endl;
    std::cout << "Salary: $" << salary << " per month" << std::endl;
    std::cout << "Experience: " << experienceYears << " years" << std::endl;
    std::cout << "Hire Date: " << hireDate << std::endl;
    std::cout << "Contact: " << contactNumber << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Full Time: " << (isFullTime ? "Yes" : "No") << std::endl;
    std::cout << "Vacation Days: " << vacationDays << std::endl;
    std::cout << "Specialization: " << specialization << std::endl;
}

std::string Employee::getName() const { return name; }
int Employee::getAge() const { return age; }
std::string Employee::getPosition() const { return position; }
double Employee::getSalary() const { return salary; }
int Employee::getExperienceYears() const { return experienceYears; }
std::string Employee::getHireDate() const { return hireDate; }
std::string Employee::getContactNumber() const { return contactNumber; }
std::string Employee::getAddress() const { return address; }
bool Employee::getIsFullTime() const { return isFullTime; }
std::string Employee::getEmployeeId() const { return employeeId; }
int Employee::getVacationDays() const { return vacationDays; }
std::string Employee::getSpecialization() const { return specialization; }

void Employee::setName(const std::string& name) {
    if (name.empty()) {
        throw EmployeeException("Employee name cannot be empty");
    }
    this->name = name;
}

void Employee::setAge(int age) {
    if (age < 18) {
        throw EmployeeException("Employee must be at least 18 years old: " + std::to_string(age));
    }
    if (age > 70) {
        throw EmployeeException("Employee age too high for farm work: " + std::to_string(age) + " (max 70)");
    }
    this->age = age;
}

void Employee::setPosition(const std::string& position) {
    if (position.empty()) {
        throw EmployeeException("Employee position cannot be empty");
    }
    this->position = position;
}

void Employee::setSalary(double salary) {
    if (salary < 1000) {
        throw EmployeeException("Employee salary too low: $" + std::to_string(salary) + " (min $1000)");
    }
    if (salary > 10000) {
        throw EmployeeException("Employee salary unrealistically high: $" + std::to_string(salary) + " (max $10000)");
    }
    this->salary = salary;
}

void Employee::setExperienceYears(int years) {
    if (years < 0 || years > 50) {
        throw EmployeeException("Experience years must be between 0-50: " + std::to_string(years));
    }
    experienceYears = years;
}

void Employee::setHireDate(const std::string& date) {
    if (date.empty()) {
        throw EmployeeException("Hire date cannot be empty");
    }
    hireDate = date;
}

void Employee::setContactNumber(const std::string& number) {
    if (number.empty()) {
        throw EmployeeException("Contact number cannot be empty");
    }
    contactNumber = number;
}

void Employee::setAddress(const std::string& address) {
    if (address.empty()) {
        throw EmployeeException("Address cannot be empty");
    }
    this->address = address;
}

void Employee::setIsFullTime(bool fullTime) { isFullTime = fullTime; }

void Employee::setEmployeeId(const std::string& id) {
    if (id.empty()) {
        throw EmployeeException("Employee ID cannot be empty");
    }
    employeeId = id;
}

void Employee::setVacationDays(int days) {
    if (days < 0 || days > 365) {
        throw EmployeeException("Vacation days must be between 0-365: " + std::to_string(days));
    }
    vacationDays = days;
}

void Employee::setSpecialization(const std::string& specialization) {
    if (specialization.empty()) {
        throw EmployeeException("Specialization cannot be empty");
    }
    this->specialization = specialization;
}

void Employee::calculateAnnualSalary() const {
    double annualSalary = salary * 12;
    if (isFullTime) {
        annualSalary += salary * 0.1; // Бонус за полную занятость
    }
    std::cout << name << "'s annual salary: $" << annualSalary << std::endl;
}

void Employee::requestVacation(int days) {
    if (days <= 0) {
        throw EmployeeException("Vacation days must be positive: " + std::to_string(days));
    }
    if (days > 60) {
        throw EmployeeException("Vacation request too long: " + std::to_string(days) + " days (max 60)");
    }
    if (days > vacationDays) {
        throw EmployeeAbsenceException(name, position,
                                       "Requested " + std::to_string(days) +
                                       " days but only has " + std::to_string(vacationDays));
    }

    vacationDays -= days;
    std::cout << name << " requested " << days << " days of vacation. Remaining: "
              << vacationDays << " days." << std::endl;
}

void Employee::updateExperience() {
    if (experienceYears >= 50) {
        throw EmployeeException(name + " has maximum experience (50 years)");
    }

    experienceYears++;
    salary *= 1.05; // 5% повышение за год опыта
    std::cout << name << " gained another year of experience. New salary: $"
              << salary << std::endl;
}

void Employee::receiveTraining(const std::string& trainingTopic) {
    if (trainingTopic.empty()) {
        throw EmployeeException("Training topic cannot be empty");
    }

    specialization = trainingTopic;
    std::cout << name << " received training in: " << trainingTopic << std::endl;
}