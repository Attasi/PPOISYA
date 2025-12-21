#ifndef EMPLOYEE_EXCEPTIONS_H
#define EMPLOYEE_EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Базовое исключение для сотрудников
class EmployeeException : public std::runtime_error {
public:
    explicit EmployeeException(const std::string& message)
            : std::runtime_error("Employee Error: " + message) {}
};

// Исключение для отсутствия сотрудника
class EmployeeAbsenceException : public EmployeeException {
private:
    std::string employeeName;
    std::string position;
    std::string reason;
public:
    EmployeeAbsenceException(const std::string& employeeName, const std::string& position,
                             const std::string& reason)
            : EmployeeException(employeeName + " (" + position + ") is absent: " + reason),
              employeeName(employeeName), position(position), reason(reason) {}

    std::string getEmployeeName() const { return employeeName; }
    std::string getPosition() const { return position; }
    std::string getReason() const { return reason; }
};

// Исключение для недостаточной квалификации
class InsufficientQualificationException : public EmployeeException {
private:
    std::string employeeName;
    std::string requiredSkill;
    std::string actualSkillLevel;
public:
    InsufficientQualificationException(const std::string& employeeName,
                                       const std::string& requiredSkill,
                                       const std::string& actualSkillLevel)
            : EmployeeException(employeeName + " lacks qualification for " + requiredSkill +
                                " (has: " + actualSkillLevel + ")"),
              employeeName(employeeName), requiredSkill(requiredSkill),
              actualSkillLevel(actualSkillLevel) {}

    std::string getEmployeeName() const { return employeeName; }
    std::string getRequiredSkill() const { return requiredSkill; }
    std::string getActualSkillLevel() const { return actualSkillLevel; }
};

#endif // EMPLOYEE_EXCEPTIONS_H