#include "gtest/gtest.h"
#include "Employee.h"
#include "Farmer.h"
#include "Milkmaid.h"
#include "Shepherd.h"
#include "EmployeeExceptions.h"
#include <vector>
#include <stdexcept>

// ==================== Тесты для базового класса Employee ====================

TEST(EmployeeTest, ConstructorValidParameters) {
EXPECT_NO_THROW({
Employee emp("John Doe", 30, "Manager", 5000.0);
EXPECT_EQ(emp.getName(), "John Doe");
EXPECT_EQ(emp.getAge(), 30);
EXPECT_EQ(emp.getPosition(), "Manager");
EXPECT_EQ(emp.getSalary(), 5000.0);
EXPECT_EQ(emp.getExperienceYears(), 1);
EXPECT_TRUE(emp.getIsFullTime());
});
}

TEST(EmployeeTest, ConstructorInvalidName) {
EXPECT_THROW(Employee("", 30, "Manager", 5000.0), EmployeeException);
}

TEST(EmployeeTest, ConstructorInvalidAgeTooYoung) {
EXPECT_THROW(Employee("John", 17, "Manager", 5000.0), EmployeeException);
}

TEST(EmployeeTest, ConstructorInvalidAgeTooOld) {
EXPECT_THROW(Employee("John", 71, "Manager", 5000.0), EmployeeException);
}

TEST(EmployeeTest, ConstructorInvalidPosition) {
EXPECT_THROW(Employee("John", 30, "", 5000.0), EmployeeException);
}

TEST(EmployeeTest, ConstructorInvalidSalaryTooLow) {
EXPECT_THROW(Employee("John", 30, "Manager", 999.0), EmployeeException);
}

TEST(EmployeeTest, ConstructorInvalidSalaryTooHigh) {
EXPECT_THROW(Employee("John", 30, "Manager", 10001.0), EmployeeException);
}

TEST(EmployeeTest, SetterGetterMethods) {
Employee emp("John", 30, "Manager", 5000.0);

// Проверяем сеттеры и геттеры
emp.setName("Jane");
EXPECT_EQ(emp.getName(), "Jane");

emp.setAge(35);
EXPECT_EQ(emp.getAge(), 35);

emp.setPosition("Senior Manager");
EXPECT_EQ(emp.getPosition(), "Senior Manager");

emp.setSalary(6000.0);
EXPECT_EQ(emp.getSalary(), 6000.0);

emp.setExperienceYears(5);
EXPECT_EQ(emp.getExperienceYears(), 5);

emp.setHireDate("2023-01-15");
EXPECT_EQ(emp.getHireDate(), "2023-01-15");

emp.setContactNumber("+12345678901");
EXPECT_EQ(emp.getContactNumber(), "+12345678901");

emp.setAddress("123 Farm St");
EXPECT_EQ(emp.getAddress(), "123 Farm St");

emp.setIsFullTime(false);
EXPECT_FALSE(emp.getIsFullTime());

emp.setVacationDays(15);
EXPECT_EQ(emp.getVacationDays(), 15);

emp.setSpecialization("Farm Management");
EXPECT_EQ(emp.getSpecialization(), "Farm Management");
}

TEST(EmployeeTest, SetterInvalidValues) {
Employee emp("John", 30, "Manager", 5000.0);

EXPECT_THROW(emp.setName(""), EmployeeException);
EXPECT_THROW(emp.setAge(17), EmployeeException);
EXPECT_THROW(emp.setAge(71), EmployeeException);
EXPECT_THROW(emp.setPosition(""), EmployeeException);
EXPECT_THROW(emp.setSalary(999.0), EmployeeException);
EXPECT_THROW(emp.setSalary(10001.0), EmployeeException);
EXPECT_THROW(emp.setExperienceYears(-1), EmployeeException);
EXPECT_THROW(emp.setExperienceYears(51), EmployeeException);
EXPECT_THROW(emp.setHireDate(""), EmployeeException);
EXPECT_THROW(emp.setContactNumber(""), EmployeeException);
EXPECT_THROW(emp.setAddress(""), EmployeeException);
EXPECT_THROW(emp.setEmployeeId(""), EmployeeException);
EXPECT_THROW(emp.setVacationDays(-1), EmployeeException);
EXPECT_THROW(emp.setVacationDays(366), EmployeeException);
EXPECT_THROW(emp.setSpecialization(""), EmployeeException);
}

TEST(EmployeeTest, WorkMethods) {
Employee emp("John", 30, "Manager", 5000.0);

// Проверяем, что методы не выбрасывают исключений
EXPECT_NO_THROW(emp.work());
EXPECT_NO_THROW(emp.takeBreak());
EXPECT_NO_THROW(emp.attendMeeting());
EXPECT_NO_THROW(emp.displayInfo());
EXPECT_NO_THROW(emp.calculateAnnualSalary());
}

TEST(EmployeeTest, RequestVacationValid) {
Employee emp("John", 30, "Manager", 5000.0);
emp.setVacationDays(20);

EXPECT_NO_THROW(emp.requestVacation(5));
EXPECT_EQ(emp.getVacationDays(), 15);
}

TEST(EmployeeTest, RequestVacationInvalidDays) {
Employee emp("John", 30, "Manager", 5000.0);

EXPECT_THROW(emp.requestVacation(0), EmployeeException);
EXPECT_THROW(emp.requestVacation(-5), EmployeeException);
EXPECT_THROW(emp.requestVacation(61), EmployeeException);
}

TEST(EmployeeTest, RequestVacationInsufficientDays) {
Employee emp("John", 30, "Manager", 5000.0);
emp.setVacationDays(5);

EXPECT_THROW(emp.requestVacation(10), EmployeeAbsenceException);
EXPECT_EQ(emp.getVacationDays(), 5); // Не должно измениться
}

TEST(EmployeeTest, UpdateExperience) {
Employee emp("John", 30, "Manager", 5000.0);
emp.setExperienceYears(5);

EXPECT_NO_THROW(emp.updateExperience());
EXPECT_EQ(emp.getExperienceYears(), 6);
EXPECT_GT(emp.getSalary(), 5000.0); // ЗП должна увеличиться на 5%
}

TEST(EmployeeTest, UpdateExperienceMaxYears) {
Employee emp("John", 30, "Manager", 5000.0);
emp.setExperienceYears(50);

EXPECT_THROW(emp.updateExperience(), EmployeeException);
EXPECT_EQ(emp.getExperienceYears(), 50); // Не должно измениться
}

TEST(EmployeeTest, ReceiveTraining) {
Employee emp("John", 30, "Manager", 5000.0);

EXPECT_NO_THROW(emp.receiveTraining("Advanced Farm Management"));
EXPECT_EQ(emp.getSpecialization(), "Advanced Farm Management");
}

TEST(EmployeeTest, ReceiveTrainingInvalidTopic) {
Employee emp("John", 30, "Manager", 5000.0);

EXPECT_THROW(emp.receiveTraining(""), EmployeeException);
}

// ==================== Тесты для класса Farmer ====================

TEST(FarmerTest, ConstructorValidParameters) {
EXPECT_NO_THROW({
Farmer farmer("Bob", 35, 2500.0);
EXPECT_EQ(farmer.getName(), "Bob");
EXPECT_EQ(farmer.getAge(), 35);
EXPECT_EQ(farmer.getPosition(), "Farmer");
EXPECT_EQ(farmer.getSalary(), 2500.0);
EXPECT_EQ(farmer.getLandArea(), 5.0);
EXPECT_TRUE(farmer.getHasTractorLicense());
});
}

TEST(FarmerTest, ConstructorInvalidSalary) {
EXPECT_THROW(Farmer("Bob", 35, 1999.0), EmployeeException);
}

TEST(FarmerTest, FarmerWorkMethod) {
Farmer farmer("Bob", 35, 2500.0);
EXPECT_NO_THROW(farmer.work());
}

TEST(FarmerTest, PlantCropsValid) {
Farmer farmer("Bob", 35, 2500.0);
farmer.setLandArea(10.0);

EXPECT_NO_THROW(farmer.plantCrops("Wheat", 2.0));
auto crops = farmer.getCropsResponsible();
EXPECT_FALSE(crops.empty());
}

TEST(FarmerTest, PlantCropsInvalid) {
Farmer farmer("Bob", 35, 2500.0);

EXPECT_THROW(farmer.plantCrops("", 2.0), EmployeeException);
EXPECT_THROW(farmer.plantCrops("Wheat", -1.0), EmployeeException);
EXPECT_THROW(farmer.plantCrops("Wheat", 100.0), EmployeeException);
}

TEST(FarmerTest, HarvestCrops) {
Farmer farmer("Bob", 35, 2500.0);
farmer.setCropsResponsible({"Wheat", "Corn"});
farmer.setLandArea(10.0);
farmer.setCropYield(3.5);

EXPECT_NO_THROW(farmer.harvestCrops());
}

TEST(FarmerTest, HarvestCropsNoCrops) {
Farmer farmer("Bob", 35, 2500.0);
farmer.setCropsResponsible({});

EXPECT_THROW(farmer.harvestCrops(), EmployeeException);
}

TEST(FarmerTest, MaintainEquipment) {
Farmer farmer("Bob", 35, 2500.0);
farmer.setFarmEquipment("Tractor and plow");

EXPECT_NO_THROW(farmer.maintainEquipment());
}

TEST(FarmerTest, PlanPlantingSchedule) {
Farmer farmer("Bob", 35, 2500.0);
farmer.setCropsResponsible({"Wheat", "Corn"});
farmer.setPlantingSeason("Spring");

EXPECT_NO_THROW(farmer.planPlantingSchedule());
}

TEST(FarmerTest, SetterGetterFarmerSpecific) {
Farmer farmer("Bob", 35, 2500.0);

std::vector<std::string> crops = {"Wheat", "Barley", "Corn"};
EXPECT_NO_THROW(farmer.setCropsResponsible(crops));
EXPECT_EQ(farmer.getCropsResponsible().size(), 3);

EXPECT_NO_THROW(farmer.setFarmEquipment("Advanced Tractor"));
EXPECT_EQ(farmer.getFarmEquipment(), "Advanced Tractor");

EXPECT_NO_THROW(farmer.setLandArea(20.0));
EXPECT_EQ(farmer.getLandArea(), 20.0);

EXPECT_NO_THROW(farmer.setIrrigationSystem("Sprinkler"));
EXPECT_EQ(farmer.getIrrigationSystem(), "Sprinkler");

EXPECT_NO_THROW(farmer.setAnimalsCaredFor(50));
EXPECT_EQ(farmer.getAnimalsCaredFor(), 50);

EXPECT_NO_THROW(farmer.setPlantingSeason("Fall"));
EXPECT_EQ(farmer.getPlantingSeason(), "Fall");

EXPECT_NO_THROW(farmer.setOrganicCertification("Certified"));
EXPECT_EQ(farmer.getOrganicCertification(), "Certified");

EXPECT_NO_THROW(farmer.setCropYield(4.5));
EXPECT_EQ(farmer.getCropYield(), 4.5);
}

TEST(FarmerTest, SetterInvalidValues) {
Farmer farmer("Bob", 35, 2500.0);

EXPECT_THROW(farmer.setCropsResponsible({}), EmployeeException);
EXPECT_THROW(farmer.setFarmEquipment(""), EmployeeException);
EXPECT_THROW(farmer.setLandArea(0.0), EmployeeException);
EXPECT_THROW(farmer.setLandArea(1001.0), EmployeeException);
EXPECT_THROW(farmer.setIrrigationSystem(""), EmployeeException);
EXPECT_THROW(farmer.setAnimalsCaredFor(-1), EmployeeException);
EXPECT_THROW(farmer.setAnimalsCaredFor(1001), EmployeeException);
EXPECT_THROW(farmer.setPlantingSeason(""), EmployeeException);
EXPECT_THROW(farmer.setOrganicCertification(""), EmployeeException);
EXPECT_THROW(farmer.setCropYield(0.0), EmployeeException);
EXPECT_THROW(farmer.setCropYield(51.0), EmployeeException);
}

TEST(FarmerTest, CalculateHarvestForecast) {
Farmer farmer("Bob", 35, 2500.0);
farmer.setLandArea(10.0);
farmer.setCropYield(3.5);

EXPECT_NO_THROW(farmer.calculateHarvestForecast());
}

TEST(FarmerTest, ApplyFertilizer) {
Farmer farmer("Bob", 35, 2500.0);
farmer.setLandArea(10.0);
farmer.setCropYield(3.5);

EXPECT_NO_THROW(farmer.applyFertilizer("Organic compost"));
EXPECT_GT(farmer.getCropYield(), 3.5);
}

TEST(FarmerTest, InspectCrops) {
Farmer farmer("Bob", 35, 2500.0);
farmer.setCropsResponsible({"Wheat", "Corn"});

EXPECT_NO_THROW(farmer.inspectCrops());
}

TEST(FarmerTest, ManageWaterSupply) {
Farmer farmer("Bob", 35, 2500.0);
farmer.setIrrigationSystem("Drip irrigation");

EXPECT_NO_THROW(farmer.manageWaterSupply());
}

// ==================== Тесты для класса Milkmaid ====================

TEST(MilkmaidTest, ConstructorValidParameters) {
EXPECT_NO_THROW({
Milkmaid milkmaid("Alice", 28, 2200.0);
EXPECT_EQ(milkmaid.getName(), "Alice");
EXPECT_EQ(milkmaid.getPosition(), "Milkmaid");
EXPECT_EQ(milkmaid.getCowsMilkedPerDay(), 20);
EXPECT_EQ(milkmaid.getMilkCollected(), 400.0);
EXPECT_TRUE(milkmaid.getIsCertified());
});
}

TEST(MilkmaidTest, ConstructorInvalidSalary) {
EXPECT_THROW(Milkmaid("Alice", 28, 1799.0), EmployeeException);
}

TEST(MilkmaidTest, MilkCowValid) {
Milkmaid milkmaid("Alice", 28, 2200.0);

EXPECT_NO_THROW(milkmaid.milkCow("Buttercup"));
EXPECT_GT(milkmaid.getCowsMilkedPerDay(), 20);
EXPECT_GT(milkmaid.getMilkCollected(), 400.0);
}

TEST(MilkmaidTest, MilkCowInvalid) {
Milkmaid milkmaid("Alice", 28, 2200.0);

EXPECT_THROW(milkmaid.milkCow(""), EmployeeException);
}

TEST(MilkmaidTest, CheckMilkQuality) {
Milkmaid milkmaid("Alice", 28, 2200.0);
milkmaid.setMilkQualityScore(8.5);
milkmaid.setIsCertified(true);

EXPECT_NO_THROW(milkmaid.checkMilkQuality());
}

TEST(MilkmaidTest, CheckMilkQualityLowScore) {
Milkmaid milkmaid("Alice", 28, 2200.0);
milkmaid.setMilkQualityScore(4.5);

EXPECT_THROW(milkmaid.checkMilkQuality(), EmployeeException);
}

TEST(MilkmaidTest, CleanMilkingEquipment) {
Milkmaid milkmaid("Alice", 28, 2200.0);
milkmaid.setMilkingEquipment("Automatic milker");
milkmaid.setHygieneProtocol("Standard");

EXPECT_NO_THROW(milkmaid.cleanMilkingEquipment());
EXPECT_GT(milkmaid.getMilkQualityScore(), 0);
}

TEST(MilkmaidTest, RecordMilkProduction) {
Milkmaid milkmaid("Alice", 28, 2200.0);
milkmaid.setCowsMilkedPerDay(15);
milkmaid.setMilkCollected(300.0);

EXPECT_NO_THROW(milkmaid.recordMilkProduction());
}

TEST(MilkmaidTest, SetterGetterMilkmaidSpecific) {
Milkmaid milkmaid("Alice", 28, 2200.0);

EXPECT_NO_THROW(milkmaid.setCowsMilkedPerDay(30));
EXPECT_EQ(milkmaid.getCowsMilkedPerDay(), 30);

EXPECT_NO_THROW(milkmaid.setMilkCollected(500.0));
EXPECT_EQ(milkmaid.getMilkCollected(), 500.0);

EXPECT_NO_THROW(milkmaid.setMilkingEquipment("Manual milker"));
EXPECT_EQ(milkmaid.getMilkingEquipment(), "Manual milker");

std::vector<std::string> cows = {"Bessie", "Daisy"};
EXPECT_NO_THROW(milkmaid.setCowNames(cows));
EXPECT_EQ(milkmaid.getCowNames().size(), 2);

EXPECT_NO_THROW(milkmaid.setMilkingSchedule("5:00 AM, 1:00 PM, 9:00 PM"));
EXPECT_FALSE(milkmaid.getMilkingSchedule().empty());

EXPECT_NO_THROW(milkmaid.setMilkQualityScore(9.0));
EXPECT_EQ(milkmaid.getMilkQualityScore(), 9.0);

EXPECT_NO_THROW(milkmaid.setHygieneProtocol("Strict protocol"));
EXPECT_EQ(milkmaid.getHygieneProtocol(), "Strict protocol");

EXPECT_NO_THROW(milkmaid.setMilkingSessionsPerDay(3));
EXPECT_EQ(milkmaid.getMilkingSessionsPerDay(), 3);
}

TEST(MilkmaidTest, SetterInvalidValuesMilkmaid) {
Milkmaid milkmaid("Alice", 28, 2200.0);

EXPECT_THROW(milkmaid.setCowsMilkedPerDay(-1), EmployeeException);
EXPECT_THROW(milkmaid.setCowsMilkedPerDay(51), EmployeeException);
EXPECT_THROW(milkmaid.setMilkCollected(-1.0), EmployeeException);
EXPECT_THROW(milkmaid.setMilkCollected(2001.0), EmployeeException);
EXPECT_THROW(milkmaid.setMilkingEquipment(""), EmployeeException);
EXPECT_THROW(milkmaid.setCowNames({}), EmployeeException);
EXPECT_THROW(milkmaid.setMilkingSchedule(""), EmployeeException);
EXPECT_THROW(milkmaid.setMilkQualityScore(-0.1), EmployeeException);
EXPECT_THROW(milkmaid.setMilkQualityScore(10.1), EmployeeException);
EXPECT_THROW(milkmaid.setHygieneProtocol(""), EmployeeException);
EXPECT_THROW(milkmaid.setMilkingSessionsPerDay(-1), EmployeeException);
EXPECT_THROW(milkmaid.setMilkingSessionsPerDay(6), EmployeeException);
}

TEST(MilkmaidTest, CalculateDailyYield) {
Milkmaid milkmaid("Alice", 28, 2200.0);
milkmaid.setCowsMilkedPerDay(20);
milkmaid.setMilkCollected(400.0);

EXPECT_NO_THROW(milkmaid.calculateDailyYield());
}

TEST(MilkmaidTest, PasteurizeMilk) {
Milkmaid milkmaid("Alice", 28, 2200.0);
milkmaid.setMilkCollected(300.0);
milkmaid.setIsCertified(true);

EXPECT_NO_THROW(milkmaid.pasteurizeMilk());
EXPECT_EQ(milkmaid.getMilkQualityScore(), 9.5);
}

TEST(MilkmaidTest, PasteurizeMilkNotCertified) {
Milkmaid milkmaid("Alice", 28, 2200.0);
milkmaid.setMilkCollected(300.0);
milkmaid.setIsCertified(false);

EXPECT_THROW(milkmaid.pasteurizeMilk(), InsufficientQualificationException);
}

TEST(MilkmaidTest, TrainNewCow) {
Milkmaid milkmaid("Alice", 28, 2200.0);
milkmaid.setIsCertified(true);

EXPECT_NO_THROW(milkmaid.trainNewCow("Molly"));
}

TEST(MilkmaidTest, MaintainMilkingMachine) {
Milkmaid milkmaid("Alice", 28, 2200.0);
milkmaid.setMilkingEquipment("Automatic milking machine");

EXPECT_NO_THROW(milkmaid.maintainMilkingMachine());
EXPECT_GT(milkmaid.getMilkQualityScore(), 0);
}

// ==================== Тесты для класса Shepherd ====================

TEST(ShepherdTest, ConstructorValidParameters) {
EXPECT_NO_THROW({
Shepherd shepherd("Charlie", 40, 2300.0);
EXPECT_EQ(shepherd.getName(), "Charlie");
EXPECT_EQ(shepherd.getPosition(), "Shepherd");
EXPECT_EQ(shepherd.getSheepInFlock(), 150);
EXPECT_EQ(shepherd.getDogName(), "Lassie");
EXPECT_TRUE(shepherd.getHasVetTraining());
});
}

TEST(ShepherdTest, ConstructorInvalidSalary) {
EXPECT_THROW(Shepherd("Charlie", 40, 1899.0), EmployeeException);
}

TEST(ShepherdTest, ShepherdWorkMethod) {
Shepherd shepherd("Charlie", 40, 2300.0);
EXPECT_NO_THROW(shepherd.work());
}

TEST(ShepherdTest, HerdSheep) {
Shepherd shepherd("Charlie", 40, 2300.0);
shepherd.setSheepInFlock(100);
shepherd.setDogName("Rex");
shepherd.setPastureLocation("East Pasture");

EXPECT_NO_THROW(shepherd.herdSheep());
}

TEST(ShepherdTest, HerdSheepNoSheep) {
Shepherd shepherd("Charlie", 40, 2300.0);
shepherd.setSheepInFlock(0);

EXPECT_THROW(shepherd.herdSheep(), EmployeeException);
}

TEST(ShepherdTest, CountSheep) {
Shepherd shepherd("Charlie", 40, 2300.0);
shepherd.setSheepInFlock(100);
shepherd.setGrazingArea(15.0);

EXPECT_NO_THROW(shepherd.countSheep());
}

TEST(ShepherdTest, TendToSickSheep) {
Shepherd shepherd("Charlie", 40, 2300.0);
shepherd.setHasVetTraining(true);

EXPECT_NO_THROW(shepherd.tendToSickSheep("Wooly", "Foot rot"));
auto issues = shepherd.getFlockHealthIssues();
EXPECT_FALSE(issues.empty());
}

TEST(ShepherdTest, TrainSheepdog) {
Shepherd shepherd("Charlie", 40, 2300.0);
shepherd.setDogName("Rex");
shepherd.setDogBreed("Border Collie");
shepherd.setHasVetTraining(true);

EXPECT_NO_THROW(shepherd.trainSheepdog());
}

TEST(ShepherdTest, SetterGetterShepherdSpecific) {
Shepherd shepherd("Charlie", 40, 2300.0);

EXPECT_NO_THROW(shepherd.setSheepInFlock(200));
EXPECT_EQ(shepherd.getSheepInFlock(), 200);

EXPECT_NO_THROW(shepherd.setDogBreed("German Shepherd"));
EXPECT_EQ(shepherd.getDogBreed(), "German Shepherd");

EXPECT_NO_THROW(shepherd.setDogName("Max"));
EXPECT_EQ(shepherd.getDogName(), "Max");

EXPECT_NO_THROW(shepherd.setGrazingArea(25.0));
EXPECT_EQ(shepherd.getGrazingArea(), 25.0);

EXPECT_NO_THROW(shepherd.setShepherdStaffType("Metal crook"));
EXPECT_EQ(shepherd.getShepherdStaffType(), "Metal crook");

EXPECT_NO_THROW(shepherd.setLambsBornThisSeason(60));
EXPECT_EQ(shepherd.getLambsBornThisSeason(), 60);

EXPECT_NO_THROW(shepherd.setPastureLocation("West Pasture"));
EXPECT_EQ(shepherd.getPastureLocation(), "West Pasture");
}

TEST(ShepherdTest, SetterInvalidValuesShepherd) {
Shepherd shepherd("Charlie", 40, 2300.0);

EXPECT_THROW(shepherd.setSheepInFlock(-1), EmployeeException);
EXPECT_THROW(shepherd.setSheepInFlock(1001), EmployeeException);
EXPECT_THROW(shepherd.setDogBreed(""), EmployeeException);
EXPECT_THROW(shepherd.setDogName(""), EmployeeException);
EXPECT_THROW(shepherd.setGrazingArea(0.0), EmployeeException);
EXPECT_THROW(shepherd.setGrazingArea(1001.0), EmployeeException);
EXPECT_THROW(shepherd.setShepherdStaffType(""), EmployeeException);
EXPECT_THROW(shepherd.setLambsBornThisSeason(-1), EmployeeException);
EXPECT_THROW(shepherd.setLambsBornThisSeason(201), EmployeeException);
EXPECT_THROW(shepherd.setPastureLocation(""), EmployeeException);
}

TEST(ShepherdTest, MoveFlockToNewPasture) {
Shepherd shepherd("Charlie", 40, 2300.0);
shepherd.setSheepInFlock(100);
shepherd.setPastureLocation("North Pasture");

EXPECT_NO_THROW(shepherd.moveFlockToNewPasture("South Pasture"));
EXPECT_EQ(shepherd.getPastureLocation(), "South Pasture");
}

TEST(ShepherdTest, ShearSheepValid) {
Shepherd shepherd("Charlie", 40, 2300.0);
shepherd.setSheepInFlock(100);
shepherd.setHasVetTraining(true);

EXPECT_NO_THROW(shepherd.shearSheep(10));
EXPECT_GT(shepherd.getSalary(), 2300.0); // ЗП должна увеличиться
}

TEST(ShepherdTest, ShearSheepTooMany) {
Shepherd shepherd("Charlie", 40, 2300.0);
shepherd.setSheepInFlock(10);

EXPECT_THROW(shepherd.shearSheep(15), EmployeeException);
}

TEST(ShepherdTest, ProtectFromPredators) {
Shepherd shepherd("Charlie", 40, 2300.0);
shepherd.setSheepInFlock(100);
shepherd.setDogName("Rex");

EXPECT_NO_THROW(shepherd.protectFromPredators());
}

TEST(ShepherdTest, MonitorFlockHealth) {
Shepherd shepherd("Charlie", 40, 2300.0);
shepherd.setSheepInFlock(100);

EXPECT_NO_THROW(shepherd.monitorFlockHealth());
}

// ==================== Тесты для исключений ====================

TEST(ExceptionsTest, EmployeeException) {
try {
throw EmployeeException("Test error");
FAIL() << "Expected EmployeeException";
} catch (const EmployeeException& e) {
EXPECT_STREQ(e.what(), "Employee Error: Test error");
}
}

TEST(ExceptionsTest, EmployeeAbsenceException) {
try {
throw EmployeeAbsenceException("John", "Manager", "Sick leave");
FAIL() << "Expected EmployeeAbsenceException";
} catch (const EmployeeAbsenceException& e) {
EXPECT_EQ(e.getEmployeeName(), "John");
EXPECT_EQ(e.getPosition(), "Manager");
EXPECT_EQ(e.getReason(), "Sick leave");
}
}

TEST(ExceptionsTest, InsufficientQualificationException) {
try {
throw InsufficientQualificationException("Alice", "Tractor Operation", "No license");
FAIL() << "Expected InsufficientQualificationException";
} catch (const InsufficientQualificationException& e) {
EXPECT_EQ(e.getEmployeeName(), "Alice");
EXPECT_EQ(e.getRequiredSkill(), "Tractor Operation");
EXPECT_EQ(e.getActualSkillLevel(), "No license");
}
}

// ==================== Интеграционные тесты ====================

TEST(IntegrationTest, EmployeePolymorphism) {
Employee* emp1 = new Farmer("Bob", 35, 2500.0);
Employee* emp2 = new Milkmaid("Alice", 28, 2200.0);
Employee* emp3 = new Shepherd("Charlie", 40, 2300.0);

EXPECT_NO_THROW(emp1->work());
EXPECT_NO_THROW(emp2->work());
EXPECT_NO_THROW(emp3->work());

EXPECT_NO_THROW(emp1->displayInfo());
EXPECT_NO_THROW(emp2->displayInfo());
EXPECT_NO_THROW(emp3->displayInfo());

delete emp1;
delete emp2;
delete emp3;
}

TEST(IntegrationTest, EmployeeCollection) {
std::vector<Employee*> employees;

employees.push_back(new Farmer("Bob", 35, 2500.0));
employees.push_back(new Milkmaid("Alice", 28, 2200.0));
employees.push_back(new Shepherd("Charlie", 40, 2300.0));

for (auto emp : employees) {
EXPECT_NO_THROW(emp->work());
EXPECT_NO_THROW(emp->calculateAnnualSalary());
}

for (auto emp : employees) {
delete emp;
}
}

// ==================== Граничные значения ====================

TEST(BoundaryTest, AgeBoundaries) {
// Минимальный возраст
EXPECT_NO_THROW(Employee("John", 18, "Manager", 5000.0));
EXPECT_THROW(Employee("John", 17, "Manager", 5000.0), EmployeeException);

// Максимальный возраст
EXPECT_NO_THROW(Employee("John", 70, "Manager", 5000.0));
EXPECT_THROW(Employee("John", 71, "Manager", 5000.0), EmployeeException);
}

TEST(BoundaryTest, SalaryBoundaries) {
// Минимальная зарплата
EXPECT_NO_THROW(Employee("John", 30, "Manager", 1000.0));
EXPECT_THROW(Employee("John", 30, "Manager", 999.0), EmployeeException);

// Максимальная зарплата
EXPECT_NO_THROW(Employee("John", 30, "Manager", 10000.0));
EXPECT_THROW(Employee("John", 30, "Manager", 10001.0), EmployeeException);
}

TEST(BoundaryTest, VacationBoundaries) {
Employee emp("John", 30, "Manager", 5000.0);

// Минимальное количество дней
EXPECT_THROW(emp.setVacationDays(-1), EmployeeException);
EXPECT_NO_THROW(emp.setVacationDays(0));

// Максимальное количество дней
EXPECT_NO_THROW(emp.setVacationDays(365));
EXPECT_THROW(emp.setVacationDays(366), EmployeeException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}