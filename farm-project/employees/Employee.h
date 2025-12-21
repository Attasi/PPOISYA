#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>

class Employee {
protected:
    std::string name;
    int age;
    std::string position;
    double salary;
    int experienceYears;
    std::string hireDate;
    std::string contactNumber;
    std::string address;
    bool isFullTime;
    std::string employeeId;
    int vacationDays;
    std::string specialization;

public:
    Employee(const std::string& name, int age, const std::string& position, double salary);
    virtual ~Employee() = default;

    virtual void work() const;
    virtual void takeBreak() const;
    virtual void attendMeeting() const;
    virtual void displayInfo() const;

    // Геттеры
    std::string getName() const;
    int getAge() const;
    std::string getPosition() const;
    double getSalary() const;
    int getExperienceYears() const;
    std::string getHireDate() const;
    std::string getContactNumber() const;
    std::string getAddress() const;
    bool getIsFullTime() const;
    std::string getEmployeeId() const;
    int getVacationDays() const;
    std::string getSpecialization() const;

    // Сеттеры
    void setName(const std::string& name);
    void setAge(int age);
    void setPosition(const std::string& position);
    void setSalary(double salary);
    void setExperienceYears(int years);
    void setHireDate(const std::string& date);
    void setContactNumber(const std::string& number);
    void setAddress(const std::string& address);
    void setIsFullTime(bool fullTime);
    void setEmployeeId(const std::string& id);
    void setVacationDays(int days);
    void setSpecialization(const std::string& specialization);

    virtual void calculateAnnualSalary() const;
    virtual void requestVacation(int days);
    virtual void updateExperience();
    virtual void receiveTraining(const std::string& trainingTopic);
};

#endif // EMPLOYEE_H