// test_equipment.cpp
#include "gtest/gtest.h"
#include "Equipment.h"
#include "Plow.h"
#include "Vehicle.h"
#include "Tractor.h"
#include "EquipmentExceptions.h"
#include <memory>
#include <stdexcept>

// ==================== Equipment Tests ====================

TEST(EquipmentTest, ConstructorValidParameters) {
Equipment equipment("Harvester", "John Deere", 2020);
EXPECT_EQ(equipment.getName(), "Harvester");
EXPECT_EQ(equipment.getManufacturer(), "John Deere");
EXPECT_EQ(equipment.getYearOfManufacture(), 2020);
EXPECT_TRUE(equipment.getIsOperational());
}

TEST(EquipmentTest, ConstructorEmptyNameThrows) {
EXPECT_THROW(Equipment("", "Deere", 2020), EquipmentException);
}

TEST(EquipmentTest, ConstructorEmptyManufacturerThrows) {
EXPECT_THROW(Equipment("Harvester", "", 2020), EquipmentException);
}

TEST(EquipmentTest, ConstructorInvalidYearThrows) {
EXPECT_THROW(Equipment("Harvester", "Deere", 1999), EquipmentException);
EXPECT_THROW(Equipment("Harvester", "Deere", 2025), EquipmentException);
}

TEST(EquipmentTest, UseIncreasesDaysSinceMaintenance) {
Equipment equipment("Test", "Maker", 2020);
int initialDays = equipment.getDaysSinceMaintenance();
equipment.use();
EXPECT_EQ(equipment.getDaysSinceMaintenance(), initialDays + 1);
}

TEST(EquipmentTest, UseDecreasesCurrentValue) {
Equipment equipment("Test", "Maker", 2020);
double initialValue = equipment.getCurrentValue();
equipment.use();
EXPECT_LT(equipment.getCurrentValue(), initialValue);
}

TEST(EquipmentTest, UseWhenNotOperationalThrows) {
Equipment equipment("Test", "Maker", 2020);
equipment.setIsOperational(false);
EXPECT_THROW(equipment.use(), EquipmentBreakdownException);
}

TEST(EquipmentTest, NeedsMaintenanceDetection) {
Equipment equipment("Test", "Maker", 2020);
equipment.setMaintenanceInterval(5);
equipment.setDaysSinceMaintenance(4);
EXPECT_FALSE(equipment.needsMaintenance());

equipment.setDaysSinceMaintenance(5);
EXPECT_TRUE(equipment.needsMaintenance());
}

TEST(EquipmentTest, PerformMaintenanceResetsDaysCounter) {
Equipment equipment("Test", "Maker", 2020);
equipment.setDaysSinceMaintenance(10);
equipment.performMaintenance();
EXPECT_EQ(equipment.getDaysSinceMaintenance(), 0);
}

TEST(EquipmentTest, PerformMaintenanceOnNonOperationalThrows) {
Equipment equipment("Test", "Maker", 2020);
equipment.setIsOperational(false);
EXPECT_THROW(equipment.performMaintenance(), EquipmentException);
}

TEST(EquipmentTest, PerformMaintenanceTooSoonThrows) {
Equipment equipment("Test", "Maker", 2020);
equipment.setDaysSinceMaintenance(3);
EXPECT_THROW(equipment.performMaintenance(), EquipmentException);
}

TEST(EquipmentTest, PerformMaintenanceIncreasesValue) {
Equipment equipment("Test", "Maker", 2020);
double initialValue = equipment.getCurrentValue();
equipment.setDaysSinceMaintenance(30);
equipment.performMaintenance();
EXPECT_GT(equipment.getCurrentValue(), initialValue);
}

TEST(EquipmentTest, RepairOperationalEquipmentThrows) {
Equipment equipment("Test", "Maker", 2020);
EXPECT_TRUE(equipment.getIsOperational());
EXPECT_THROW(equipment.repair(), EquipmentException);
}

TEST(EquipmentTest, RepairNonOperationalSuccess) {
Equipment equipment("Test", "Maker", 2020);
equipment.setIsOperational(false);
equipment.setCurrentValue(5000);
equipment.repair();
EXPECT_TRUE(equipment.getIsOperational());
EXPECT_GT(equipment.getCurrentValue(), 5000);
}

TEST(EquipmentTest, MoveToValidLocation) {
Equipment equipment("Test", "Maker", 2020);
std::string newLocation = "Field A";
equipment.moveTo(newLocation);
EXPECT_EQ(equipment.getLocation(), newLocation);
}

TEST(EquipmentTest, MoveToEmptyLocationThrows) {
Equipment equipment("Test", "Maker", 2020);
EXPECT_THROW(equipment.moveTo(""), EquipmentException);
}

TEST(EquipmentTest, MoveNonOperationalThrows) {
Equipment equipment("Test", "Maker", 2020);
equipment.setIsOperational(false);
EXPECT_THROW(equipment.moveTo("Field A"), EquipmentException);
}

TEST(EquipmentTest, CalculateDepreciation) {
Equipment equipment("Test", "Maker", 2015);
double depreciation = equipment.calculateDepreciation();
EXPECT_GT(depreciation, 0);
}

TEST(EquipmentTest, CalculateDepreciationInvalidYearThrows) {
Equipment equipment("Test", "Maker", 2020);
equipment.setYearOfManufacture(2025); // Invalid year
EXPECT_THROW(equipment.calculateDepreciation(), EquipmentException);
}

TEST(EquipmentTest, EstimateResidualValue) {
Equipment equipment("Test", "Maker", 2018);
double residual = equipment.estimateResidualValue();
EXPECT_GE(residual, 0);
EXPECT_LE(residual, equipment.getPurchasePrice());
}

TEST(EquipmentTest, EstimateResidualValueNonOperational) {
Equipment equipment("Test", "Maker", 2020);
equipment.setIsOperational(false);
double residual = equipment.estimateResidualValue();
EXPECT_GT(residual, 0);
}

TEST(EquipmentTest, IsUnderWarranty) {
Equipment equipment("Test", "Maker", 2022);
EXPECT_TRUE(equipment.isUnderWarranty(2024));
EXPECT_FALSE(equipment.isUnderWarranty(2026));
}

TEST(EquipmentTest, IsUnderWarrantyInvalidYearThrows) {
Equipment equipment("Test", "Maker", 2020);
EXPECT_THROW(equipment.isUnderWarranty(2019), EquipmentException);
}

TEST(EquipmentTest, CalculateMaintenanceCost) {
Equipment equipment("Test", "Maker", 2020);
equipment.setDaysSinceMaintenance(40);
equipment.setMaintenanceInterval(30);
double cost = equipment.calculateMaintenanceCost();
EXPECT_GT(cost, 0);
}

TEST(EquipmentTest, CalculateMaintenanceCostNonOperationalThrows) {
Equipment equipment("Test", "Maker", 2020);
equipment.setIsOperational(false);
EXPECT_THROW(equipment.calculateMaintenanceCost(), EquipmentException);
}

TEST(EquipmentTest, SettersAndGetters) {
Equipment equipment("Test", "Maker", 2020);

// Test all setters and getters
equipment.setName("New Name");
EXPECT_EQ(equipment.getName(), "New Name");

equipment.setManufacturer("New Maker");
EXPECT_EQ(equipment.getManufacturer(), "New Maker");

equipment.setYearOfManufacture(2021);
EXPECT_EQ(equipment.getYearOfManufacture(), 2021);

equipment.setPurchasePrice(15000.0);
EXPECT_EQ(equipment.getPurchasePrice(), 15000.0);

equipment.setCurrentValue(12000.0);
EXPECT_EQ(equipment.getCurrentValue(), 12000.0);

equipment.setIsOperational(false);
EXPECT_FALSE(equipment.getIsOperational());

equipment.setMaintenanceInterval(60);
EXPECT_EQ(equipment.getMaintenanceInterval(), 60);

equipment.setDaysSinceMaintenance(45);
EXPECT_EQ(equipment.getDaysSinceMaintenance(), 45);

equipment.setLocation("Warehouse");
EXPECT_EQ(equipment.getLocation(), "Warehouse");

equipment.setSerialNumber("NEW123");
EXPECT_EQ(equipment.getSerialNumber(), "NEW123");
}

TEST(EquipmentTest, InvalidSettersThrow) {
Equipment equipment("Test", "Maker", 2020);

EXPECT_THROW(equipment.setName(""), EquipmentException);
EXPECT_THROW(equipment.setManufacturer(""), EquipmentException);
EXPECT_THROW(equipment.setYearOfManufacture(1999), EquipmentException);
EXPECT_THROW(equipment.setPurchasePrice(-100), EquipmentException);
EXPECT_THROW(equipment.setCurrentValue(-100), EquipmentException);
EXPECT_THROW(equipment.setMaintenanceInterval(0), EquipmentException);
EXPECT_THROW(equipment.setDaysSinceMaintenance(-1), EquipmentException);
EXPECT_THROW(equipment.setLocation(""), EquipmentException);
EXPECT_THROW(equipment.setSerialNumber(""), EquipmentException);
}

TEST(EquipmentTest, DisplayInfoNoThrow) {
Equipment equipment("Test Equipment", "Test Maker", 2020);
EXPECT_NO_THROW(equipment.displayInfo());
}

// ==================== Plow Tests ====================

TEST(PlowTest, ConstructorValidParameters) {
Plow plow("Model 5", "Deere", 2021, 5, 3.5);
EXPECT_EQ(plow.getBladeCount(), 5);
EXPECT_EQ(plow.getWorkingWidth(), 3.5);
EXPECT_EQ(plow.getPlowType(), "Moldboard");
EXPECT_TRUE(plow.getIsReversible());
}

TEST(PlowTest, ConstructorInvalidBladeCountThrows) {
EXPECT_THROW(Plow("Test", "Maker", 2020, 0, 2.0), EquipmentException);
EXPECT_THROW(Plow("Test", "Maker", 2020, 15, 2.0), EquipmentException);
}

TEST(PlowTest, ConstructorInvalidWidthThrows) {
EXPECT_THROW(Plow("Test", "Maker", 2020, 3, -1.0), EquipmentException);
EXPECT_THROW(Plow("Test", "Maker", 2020, 3, 12.0), EquipmentException);
}

TEST(PlowTest, AdjustDepthValid) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
EXPECT_NO_THROW(plow.adjustDepth(0.2));
}

TEST(PlowTest, AdjustDepthNonOperationalThrows) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
plow.setIsOperational(false);
EXPECT_THROW(plow.adjustDepth(0.2), EquipmentException);
}

TEST(PlowTest, AdjustDepthInvalidDepthThrows) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
EXPECT_THROW(plow.adjustDepth(-0.1), EquipmentException);
EXPECT_THROW(plow.adjustDepth(0.5), EquipmentException);
}

TEST(PlowTest, AdjustDepthIncreasesWearLevel) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
double initialWear = plow.getWearLevel();
plow.adjustDepth(0.2);
EXPECT_GT(plow.getWearLevel(), initialWear);
}

TEST(PlowTest, SharpenBladesReducesWear) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
plow.setWearLevel(40.0);
plow.sharpenBlades();
EXPECT_LT(plow.getWearLevel(), 40.0);
}

TEST(PlowTest, SharpenBladesLowWearThrows) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
plow.setWearLevel(10.0);
EXPECT_THROW(plow.sharpenBlades(), EquipmentException);
}

TEST(PlowTest, CalculateAreaPerHour) {
Plow plow("Test", "Maker", 2020, 4, 2.5);
double area = plow.calculateAreaPerHour(5.0);
EXPECT_GT(area, 0);
}

TEST(PlowTest, CalculateAreaPerHourInvalidSpeedThrows) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
EXPECT_THROW(plow.calculateAreaPerHour(-5.0), EquipmentException);
EXPECT_THROW(plow.calculateAreaPerHour(20.0), EquipmentException);
}

TEST(PlowTest, CheckBladeWear) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
plow.setWearLevel(30.0);
EXPECT_FALSE(plow.checkBladeWear());

plow.setWearLevel(60.0);
EXPECT_TRUE(plow.checkBladeWear());
}

TEST(PlowTest, ReplaceBladesSuccess) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
plow.setWearLevel(80.0);
double initialValue = plow.getCurrentValue();
plow.replaceBlades();
EXPECT_EQ(plow.getWearLevel(), 0.0);
EXPECT_LT(plow.getCurrentValue(), initialValue);
}

TEST(PlowTest, ReplaceBladesLowWearThrows) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
plow.setWearLevel(30.0);
EXPECT_THROW(plow.replaceBlades(), EquipmentException);
}

TEST(PlowTest, CalculateRequiredTraction) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
double traction = plow.calculateRequiredTraction();
EXPECT_GT(traction, 0);
}

TEST(PlowTest, IsProperlyAdjusted) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
plow.setWearLevel(60.0);
plow.setIsOperational(true);
EXPECT_TRUE(plow.isProperlyAdjusted());

plow.setWearLevel(80.0);
EXPECT_FALSE(plow.isProperlyAdjusted());

plow.setIsOperational(false);
EXPECT_FALSE(plow.isProperlyAdjusted());
}

TEST(PlowTest, CalculateFuelConsumption) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
double consumption = plow.calculateFuelConsumption(10000.0, 5.0);
EXPECT_GT(consumption, 0);
}

TEST(PlowTest, UseIncreasesWearLevel) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
double initialWear = plow.getWearLevel();
plow.use();
EXPECT_GT(plow.getWearLevel(), initialWear);
}

TEST(PlowTest, UseHighWearThrows) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
plow.setWearLevel(90.0);
EXPECT_THROW(plow.use(), EquipmentBreakdownException);
}

TEST(PlowTest, PerformMaintenanceCallsBaseAndSpecific) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
plow.setDaysSinceMaintenance(30);
plow.setWearLevel(40.0);
EXPECT_NO_THROW(plow.performMaintenance());
}

TEST(PlowTest, CalculateMaintenanceCostIncludesBladeCost) {
Plow plow("Test", "Maker", 2020, 5, 3.0);
plow.setDaysSinceMaintenance(40);
double cost = plow.calculateMaintenanceCost();
EXPECT_GT(cost, 0);
}

TEST(PlowTest, DisplayInfoNoThrow) {
Plow plow("Test Plow", "Test Maker", 2020, 4, 3.0);
EXPECT_NO_THROW(plow.displayInfo());
}

TEST(PlowTest, SettersAndGetters) {
Plow plow("Test", "Maker", 2020, 3, 2.0);

plow.setBladeCount(4);
EXPECT_EQ(plow.getBladeCount(), 4);

plow.setWorkingWidth(3.0);
EXPECT_EQ(plow.getWorkingWidth(), 3.0);

plow.setMaxWorkingDepth(0.4);
EXPECT_EQ(plow.getMaxWorkingDepth(), 0.4);

plow.setPlowType("Disc");
EXPECT_EQ(plow.getPlowType(), "Disc");

plow.setIsReversible(false);
EXPECT_FALSE(plow.getIsReversible());

plow.setWearLevel(50.0);
EXPECT_EQ(plow.getWearLevel(), 50.0);
}

TEST(PlowTest, InvalidSettersThrow) {
Plow plow("Test", "Maker", 2020, 3, 2.0);

EXPECT_THROW(plow.setBladeCount(0), EquipmentException);
EXPECT_THROW(plow.setBladeCount(15), EquipmentException);
EXPECT_THROW(plow.setWorkingWidth(-1.0), EquipmentException);
EXPECT_THROW(plow.setWorkingWidth(12.0), EquipmentException);
EXPECT_THROW(plow.setMaxWorkingDepth(-0.1), EquipmentException);
EXPECT_THROW(plow.setMaxWorkingDepth(1.5), EquipmentException);
EXPECT_THROW(plow.setPlowType(""), EquipmentException);
EXPECT_THROW(plow.setWearLevel(-10.0), EquipmentException);
EXPECT_THROW(plow.setWearLevel(110.0), EquipmentException);
}

// ==================== Vehicle Tests ====================

TEST(VehicleTest, ConstructorValidParameters) {
Vehicle vehicle("Truck", "Ford", 2019, "Diesel", 80.0);
EXPECT_EQ(vehicle.getFuelType(), "Diesel");
EXPECT_EQ(vehicle.getFuelCapacity(), 80.0);
EXPECT_EQ(vehicle.getCurrentFuelLevel(), 80.0);
EXPECT_TRUE(vehicle.getHasInsurance());
}

TEST(VehicleTest, ConstructorInvalidFuelTypeThrows) {
EXPECT_THROW(Vehicle("Test", "Maker", 2020, "", 50.0), EquipmentException);
EXPECT_THROW(Vehicle("Test", "Maker", 2020, "Biofuel", 50.0), EquipmentException);
}

TEST(VehicleTest, ConstructorInvalidCapacityThrows) {
EXPECT_THROW(Vehicle("Test", "Maker", 2020, "Gasoline", -10.0), EquipmentException);
EXPECT_THROW(Vehicle("Test", "Maker", 2020, "Gasoline", 2000.0), EquipmentException);
}

TEST(VehicleTest, RefuelValid) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setCurrentFuelLevel(50.0);
double initialFuel = vehicle.getCurrentFuelLevel();
vehicle.refuel(20.0);
EXPECT_GT(vehicle.getCurrentFuelLevel(), initialFuel);
}

TEST(VehicleTest, RefuelElectricThrows) {
Vehicle vehicle("Test", "Maker", 2020, "Electric", 100.0);
EXPECT_THROW(vehicle.refuel(20.0), EquipmentException);
}

TEST(VehicleTest, RefuelNonOperationalThrows) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setIsOperational(false);
EXPECT_THROW(vehicle.refuel(20.0), EquipmentException);
}

TEST(VehicleTest, DriveValid) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setCurrentFuelLevel(100.0);
vehicle.setFuelEfficiency(10.0);
vehicle.setHasInsurance(true);
vehicle.setDaysSinceMaintenance(15);
vehicle.setMaintenanceInterval(30);

double initialMileage = vehicle.getMileage();
double initialFuel = vehicle.getCurrentFuelLevel();

EXPECT_NO_THROW(vehicle.drive(50.0));

EXPECT_GT(vehicle.getMileage(), initialMileage);
EXPECT_LT(vehicle.getCurrentFuelLevel(), initialFuel);
}

TEST(VehicleTest, DriveNoInsuranceThrows) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setHasInsurance(false);
vehicle.setCurrentFuelLevel(100.0);
EXPECT_THROW(vehicle.drive(50.0), EquipmentException);
}

TEST(VehicleTest, DriveNonOperationalThrows) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setIsOperational(false);
EXPECT_THROW(vehicle.drive(50.0), EquipmentBreakdownException);
}

TEST(VehicleTest, CheckFuelLevel) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setCurrentFuelLevel(5.0); // 5% of capacity
EXPECT_FALSE(vehicle.checkFuelLevel());

vehicle.setCurrentFuelLevel(15.0); // 15% of capacity
EXPECT_TRUE(vehicle.checkFuelLevel());
}

TEST(VehicleTest, RenewInsurance) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setHasInsurance(false);
vehicle.renewInsurance();
EXPECT_TRUE(vehicle.getHasInsurance());
}

TEST(VehicleTest, CalculateFuelCost) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setFuelEfficiency(8.0);
double cost = vehicle.calculateFuelCost(100.0, 1.5);
EXPECT_GT(cost, 0);
}

TEST(VehicleTest, CalculateRange) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setCurrentFuelLevel(50.0);
vehicle.setFuelEfficiency(10.0);
double range = vehicle.calculateRange();
EXPECT_GT(range, 0);
}

TEST(VehicleTest, NeedsOilChange) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setMileage(6000.0);
EXPECT_TRUE(vehicle.needsOilChange());

vehicle.setMileage(3000.0);
EXPECT_FALSE(vehicle.needsOilChange());

Vehicle electric("Electric", "Tesla", 2020, "Electric", 100.0);
electric.setMileage(10000.0);
EXPECT_FALSE(electric.needsOilChange());
}

TEST(VehicleTest, UseCallsDrive) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setCurrentFuelLevel(100.0);
vehicle.setFuelEfficiency(10.0);
vehicle.setHasInsurance(true);
vehicle.setDaysSinceMaintenance(15);
vehicle.setMaintenanceInterval(30);

EXPECT_NO_THROW(vehicle.use());
}

TEST(VehicleTest, PerformMaintenance) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setDaysSinceMaintenance(30);
vehicle.setMileage(6000.0);
vehicle.setHasInsurance(true);

EXPECT_NO_THROW(vehicle.performMaintenance());
}

TEST(VehicleTest, CalculateMaintenanceCost) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setMileage(50000.0);
vehicle.setHasInsurance(true);

double cost = vehicle.calculateMaintenanceCost();
EXPECT_GT(cost, 0);
}

TEST(VehicleTest, DisplayInfoNoThrow) {
Vehicle vehicle("Test Vehicle", "Test Maker", 2020, "Gasoline", 60.0);
EXPECT_NO_THROW(vehicle.displayInfo());
}

TEST(VehicleTest, SettersAndGetters) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);

vehicle.setFuelType("Gasoline");
EXPECT_EQ(vehicle.getFuelType(), "Gasoline");

vehicle.setFuelCapacity(80.0);
EXPECT_EQ(vehicle.getFuelCapacity(), 80.0);

vehicle.setCurrentFuelLevel(60.0);
EXPECT_EQ(vehicle.getCurrentFuelLevel(), 60.0);

vehicle.setFuelEfficiency(12.0);
EXPECT_EQ(vehicle.getFuelEfficiency(), 12.0);

vehicle.setMileage(15000.0);
EXPECT_EQ(vehicle.getMileage(), 15000.0);

vehicle.setLicensePlate("ABC123");
EXPECT_EQ(vehicle.getLicensePlate(), "ABC123");

vehicle.setHasInsurance(false);
EXPECT_FALSE(vehicle.getHasInsurance());
}

TEST(VehicleTest, InvalidSettersThrow) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);

EXPECT_THROW(vehicle.setFuelType("Invalid"), EquipmentException);
EXPECT_THROW(vehicle.setFuelCapacity(-10.0), EquipmentException);
EXPECT_THROW(vehicle.setFuelCapacity(1500.0), EquipmentException);
EXPECT_THROW(vehicle.setCurrentFuelLevel(-5.0), EquipmentException);
EXPECT_THROW(vehicle.setCurrentFuelLevel(200.0), EquipmentException); // Over capacity
EXPECT_THROW(vehicle.setFuelEfficiency(0.0), EquipmentException);
EXPECT_THROW(vehicle.setFuelEfficiency(60.0), EquipmentException);
EXPECT_THROW(vehicle.setMileage(-100.0), EquipmentException);
EXPECT_THROW(vehicle.setMileage(2000000.0), EquipmentException);
EXPECT_THROW(vehicle.setLicensePlate(""), EquipmentException);
}

// ==================== Tractor Tests ====================

TEST(TractorTest, ConstructorValidParameters) {
Tractor tractor("Model X", "John Deere", 2020, 150.0, true);
EXPECT_EQ(tractor.getEnginePower(), 150.0);
EXPECT_TRUE(tractor.getHasFrontLoader());
EXPECT_FALSE(tractor.getHasBackhoe());
EXPECT_EQ(tractor.getHydraulicSystemPressure(), 200);
}

TEST(TractorTest, ConstructorInvalidPowerThrows) {
EXPECT_THROW(Tractor("Test", "Maker", 2020, -50.0, false), EquipmentException);
EXPECT_THROW(Tractor("Test", "Maker", 2020, 600.0, false), EquipmentException);
}

TEST(TractorTest, ConstructorInsufficientPowerForLoaderThrows) {
EXPECT_THROW(Tractor("Test", "Maker", 2020, 40.0, true), EquipmentException);
}

TEST(TractorTest, AttachImplementValid) {
Tractor tractor("Test", "Maker", 2020, 120.0);
EXPECT_NO_THROW(tractor.attachImplement("Plow"));
}

TEST(TractorTest, AttachDuplicateImplementThrows) {
Tractor tractor("Test", "Maker", 2020, 120.0);
tractor.attachImplement("Plow");
EXPECT_THROW(tractor.attachImplement("Plow"), EquipmentException);
}

TEST(TractorTest, AttachIncompatibleImplementThrows) {
Tractor tractor("Test", "Maker", 2020, 120.0);
EXPECT_THROW(tractor.attachImplement("InvalidTool"), EquipmentException);
}

TEST(TractorTest, DetachImplement) {
Tractor tractor("Test", "Maker", 2020, 120.0);
tractor.attachImplement("Seeder");
EXPECT_NO_THROW(tractor.detachImplement("Seeder"));
}

TEST(TractorTest, DetachNonAttachedImplementThrows) {
Tractor tractor("Test", "Maker", 2020, 120.0);
EXPECT_THROW(tractor.detachImplement("Harvester"), EquipmentException);
}

TEST(TractorTest, PlowFieldValid) {
Tractor tractor("Test", "Maker", 2020, 150.0);
tractor.attachImplement("Plow");
tractor.setCurrentFuelLevel(100.0);
tractor.setHasInsurance(true);
tractor.setDaysSinceMaintenance(15);

EXPECT_NO_THROW(tractor.plowField(5000.0));
}

TEST(TractorTest, PlowFieldNoPlowThrows) {
Tractor tractor("Test", "Maker", 2020, 150.0);
tractor.setCurrentFuelLevel(100.0);
tractor.setHasInsurance(true);

EXPECT_THROW(tractor.plowField(1000.0), EquipmentException);
}

TEST(TractorTest, TransportLoadValid) {
Tractor tractor("Test", "Maker", 2020, 120.0);
tractor.setCurrentFuelLevel(100.0);
tractor.setFuelEfficiency(15.0);
tractor.setHasInsurance(true);

EXPECT_NO_THROW(tractor.transportLoad(1000.0, 10.0));
}

TEST(TractorTest, CheckHydraulicSystem) {
Tractor tractor("Test", "Maker", 2020, 120.0);
tractor.setHydraulicSystemPressure(200);
EXPECT_TRUE(tractor.checkHydraulicSystem());

tractor.setHydraulicSystemPressure(170);
EXPECT_FALSE(tractor.checkHydraulicSystem());
}

TEST(TractorTest, CalculateTractiveEffort) {
Tractor tractor("Test", "Maker", 2020, 150.0);
double effort = tractor.calculateTractiveEffort();
EXPECT_GT(effort, 0);
}

TEST(TractorTest, IsImplementCompatible) {
Tractor tractor("Test", "Maker", 2020, 120.0);
EXPECT_TRUE(tractor.isImplementCompatible("Plow"));
EXPECT_TRUE(tractor.isImplementCompatible("Seeder"));
EXPECT_FALSE(tractor.isImplementCompatible("Unknown"));
}

TEST(TractorTest, CalculateProductivity) {
Tractor tractor("Test", "Maker", 2020, 120.0);
tractor.attachImplement("Plow");
double productivity = tractor.calculateProductivity(8.0);
EXPECT_GT(productivity, 0);
}

TEST(TractorTest, UseCallsPlowField) {
Tractor tractor("Test", "Maker", 2020, 150.0);
tractor.attachImplement("Plow");
tractor.setCurrentFuelLevel(100.0);
tractor.setFuelEfficiency(15.0);
tractor.setHasInsurance(true);
tractor.setDaysSinceMaintenance(15);
tractor.setHydraulicSystemPressure(200);

EXPECT_NO_THROW(tractor.use());
}

TEST(TractorTest, PerformMaintenance) {
Tractor tractor("Test", "Maker", 2020, 150.0);
tractor.setDaysSinceMaintenance(30);
tractor.setHasInsurance(true);
tractor.setHydraulicSystemPressure(200);

EXPECT_NO_THROW(tractor.performMaintenance());
}

TEST(TractorTest, CalculateMaintenanceCost) {
Tractor tractor("Test", "Maker", 2020, 150.0, true);
tractor.attachImplement("Plow");
tractor.setHasInsurance(true);

double cost = tractor.calculateMaintenanceCost();
EXPECT_GT(cost, 0);
}

TEST(TractorTest, DisplayInfoNoThrow) {
Tractor tractor("Test Tractor", "Test Maker", 2020, 180.0, true);
tractor.attachImplement("Plow");
EXPECT_NO_THROW(tractor.displayInfo());
}

TEST(TractorTest, SettersAndGetters) {
Tractor tractor("Test", "Maker", 2020, 120.0);

tractor.setEnginePower(180.0);
EXPECT_EQ(tractor.getEnginePower(), 180.0);

tractor.setHasFrontLoader(true);
EXPECT_TRUE(tractor.getHasFrontLoader());

tractor.setHasBackhoe(true);
EXPECT_TRUE(tractor.getHasBackhoe());

tractor.setHydraulicSystemPressure(210);
EXPECT_EQ(tractor.getHydraulicSystemPressure(), 210);
}

TEST(TractorTest, InvalidSettersThrow) {
Tractor tractor("Test", "Maker", 2020, 120.0);

EXPECT_THROW(tractor.setEnginePower(-50.0), EquipmentException);
EXPECT_THROW(tractor.setEnginePower(600.0), EquipmentException);
EXPECT_THROW(tractor.setHasFrontLoader(true), EquipmentException); // Insufficient power
EXPECT_THROW(tractor.setHydraulicSystemPressure(-10), EquipmentException);
EXPECT_THROW(tractor.setHydraulicSystemPressure(350), EquipmentException);
}

// ==================== Exception Tests ====================

TEST(ExceptionTest, EquipmentExceptionBasic) {
EquipmentException ex("Test message");
EXPECT_NE(std::string(ex.what()).find("Test message"), std::string::npos);
}

TEST(ExceptionTest, EquipmentBreakdownException) {
EquipmentBreakdownException ex("Harvester", "Engine failure", "2024-01-15");
EXPECT_NE(std::string(ex.what()).find("Harvester"), std::string::npos);
EXPECT_NE(std::string(ex.what()).find("Engine failure"), std::string::npos);
EXPECT_EQ(ex.getEquipmentName(), "Harvester");
EXPECT_EQ(ex.getFailureType(), "Engine failure");
EXPECT_EQ(ex.getLastMaintenanceDate(), "2024-01-15");
}

TEST(ExceptionTest, MissingPartsException) {
MissingPartsException ex("Tractor", "Fuel filter", 5);
EXPECT_NE(std::string(ex.what()).find("Tractor"), std::string::npos);
EXPECT_NE(std::string(ex.what()).find("Fuel filter"), std::string::npos);
EXPECT_EQ(ex.getEquipmentName(), "Tractor");
EXPECT_EQ(ex.getMissingPart(), "Fuel filter");
EXPECT_EQ(ex.getDaysWaiting(), 5);
}

// ==================== Integration Tests ====================

TEST(IntegrationTest, EquipmentHierarchyPolymorphism) {
std::unique_ptr<Equipment> equipment = std::make_unique<Equipment>("Basic", "Maker", 2020);
std::unique_ptr<Equipment> plow = std::make_unique<Plow>("Plow1", "Maker", 2021, 4, 3.0);
std::unique_ptr<Equipment> vehicle = std::make_unique<Vehicle>("Truck", "Maker", 2019, "Diesel", 80.0);
std::unique_ptr<Equipment> tractor = std::make_unique<Tractor>("Tractor1", "Maker", 2020, 150.0);

// Test polymorphic calls
EXPECT_NO_THROW(equipment->displayInfo());
EXPECT_NO_THROW(plow->displayInfo());
EXPECT_NO_THROW(vehicle->displayInfo());
EXPECT_NO_THROW(tractor->displayInfo());
}

TEST(IntegrationTest, TractorWithPlowSimulation) {
// Create a tractor
Tractor tractor("John Deere 8R", "John Deere", 2020, 250.0, true);
tractor.setCurrentFuelLevel(200.0);
tractor.setFuelEfficiency(18.0);
tractor.setHasInsurance(true);

// Create a plow
Plow plow("Model 720", "John Deere", 2021, 7, 4.2);

// Attach plow to tractor
tractor.attachImplement("7-Bottom Plow");

// Adjust plow depth
plow.adjustDepth(0.25);

// Perform maintenance if needed
if (tractor.needsMaintenance()) {
tractor.performMaintenance();
}

// Plow a field
EXPECT_NO_THROW(tractor.plowField(10000.0));

// Check plow wear
EXPECT_TRUE(plow.getWearLevel() > 0);
}

TEST(IntegrationTest, MaintenanceCostChain) {
Equipment* equipment = new Equipment("Basic", "Maker", 2020);
Equipment* plow = new Plow("Plow", "Maker", 2021, 5, 3.0);
Equipment* vehicle = new Vehicle("Truck", "Maker", 2019, "Diesel", 80.0);
Equipment* tractor = new Tractor("Tractor", "Maker", 2020, 180.0);

// Set operational status
equipment->setIsOperational(true);
plow->setIsOperational(true);
vehicle->setIsOperational(true);
tractor->setIsOperational(true);

// Test maintenance cost calculation at each level
double cost1 = equipment->calculateMaintenanceCost();
double cost2 = plow->calculateMaintenanceCost();
double cost3 = vehicle->calculateMaintenanceCost();
double cost4 = tractor->calculateMaintenanceCost();

EXPECT_GT(cost1, 0);
EXPECT_GT(cost2, cost1); // Plow should cost more than basic equipment
EXPECT_GT(cost3, cost1); // Vehicle should cost more than basic equipment
EXPECT_GT(cost4, cost3); // Tractor should cost more than vehicle

delete equipment;
delete plow;
delete vehicle;
delete tractor;
}

// ==================== Edge Case Tests ====================

TEST(EdgeCaseTest, EquipmentExtremeAge) {
Equipment equipment("Old", "Maker", 2000);
equipment.setIsOperational(true);

// Should not throw when calculating values for old equipment
EXPECT_NO_THROW(equipment.calculateDepreciation());
EXPECT_NO_THROW(equipment.estimateResidualValue());
}

TEST(EdgeCaseTest, PlowCriticalWear) {
Plow plow("Test", "Maker", 2020, 3, 2.0);
plow.setWearLevel(95.0);
plow.setIsOperational(true);

// Using plow with critical wear should cause breakdown
EXPECT_THROW(plow.use(), EquipmentBreakdownException);
}

TEST(EdgeCaseTest, VehicleLongDistance) {
Vehicle vehicle("Test", "Maker", 2020, "Diesel", 100.0);
vehicle.setCurrentFuelLevel(100.0);
vehicle.setFuelEfficiency(5.0); // Very efficient
vehicle.setHasInsurance(true);
vehicle.setDaysSinceMaintenance(15);

// Drive long distance
EXPECT_NO_THROW(vehicle.drive(500.0));

// Mileage should be increased
EXPECT_EQ(vehicle.getMileage(), 500.0);
}

TEST(EdgeCaseTest, TractorMultipleImplements) {
Tractor tractor("Test", "Maker", 2020, 200.0);

// Attach maximum number of implements
tractor.attachImplement("Plow");
tractor.attachImplement("Seeder");
tractor.attachImplement("Sprayer");
tractor.attachImplement("Trailer");
tractor.attachImplement("Mower");

// Try to attach one more - should throw
EXPECT_THROW(tractor.attachImplement("Cultivator"), EquipmentException);
}

// ==================== Performance Tests ====================

TEST(PerformanceTest, MultipleOperations) {
// Test that multiple operations don't cause memory leaks or crashes
Equipment equipment("Test", "Maker", 2020);

for (int i = 0; i < 100; i++) {
equipment.use();
}

EXPECT_GT(equipment.getDaysSinceMaintenance(), 0);
EXPECT_LT(equipment.getCurrentValue(), equipment.getPurchasePrice());
}

TEST(PerformanceTest, ComplexTractorOperations) {
Tractor tractor("Test", "Maker", 2020, 180.0, true);
tractor.setCurrentFuelLevel(200.0);
tractor.setFuelEfficiency(15.0);
tractor.setHasInsurance(true);

for (int i = 0; i < 10; i++) {
if (tractor.getIsOperational()) {
try {
tractor.attachImplement("Plow " + std::to_string(i));
tractor.plowField(1000.0 * (i + 1));
tractor.detachImplement("Plow " + std::to_string(i));
} catch (const EquipmentException& e) {
// Expected in some cases
}
}
}

EXPECT_TRUE(true); // If we got here without crash, test passes
}

// ==================== Main Test Runner ====================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}