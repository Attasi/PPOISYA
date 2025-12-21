#ifndef SHEPHERD_H
#define SHEPHERD_H

#include "Employee.h"
#include <string>
#include <vector>

class Shepherd : public Employee {
private:
    int sheepInFlock;
    std::string dogBreed;
    std::string dogName;
    double grazingArea; // площадь пастбища в гектарах
    std::vector<std::string> flockHealthIssues;
    std::string shepherdStaffType;
    int lambsBornThisSeason;
    std::string pastureLocation;
    bool hasVetTraining;

public:
    Shepherd(const std::string& name, int age, double salary = 2300.0);

    void work() const override;
    void herdSheep();
    void countSheep();
    void tendToSickSheep(const std::string& sheepName, const std::string& issue);
    void trainSheepdog();

    // Геттеры
    int getSheepInFlock() const;
    std::string getDogBreed() const;
    std::string getDogName() const;
    double getGrazingArea() const;
    std::vector<std::string> getFlockHealthIssues() const;
    std::string getShepherdStaffType() const;
    int getLambsBornThisSeason() const;
    std::string getPastureLocation() const;
    bool getHasVetTraining() const;

    // Сеттеры
    void setSheepInFlock(int sheep);
    void setDogBreed(const std::string& breed);
    void setDogName(const std::string& name);
    void setGrazingArea(double area);
    void setFlockHealthIssues(const std::vector<std::string>& issues);
    void setShepherdStaffType(const std::string& staffType);
    void setLambsBornThisSeason(int lambs);
    void setPastureLocation(const std::string& location);
    void setHasVetTraining(bool training);

    void moveFlockToNewPasture(const std::string& newLocation);
    void shearSheep(int count);
    void protectFromPredators();
    void monitorFlockHealth();
};

#endif // SHEPHERD_H