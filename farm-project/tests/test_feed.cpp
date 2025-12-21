#include <gtest/gtest.h>
#include "Feed.h"
#include "Grain.h"
#include "Hay.h"
#include "CompoundFeed.h"
#include "FeedExceptions.h"
#include <vector>

// Тесты для базового класса Feed
TEST(FeedTest, ConstructorValidInput) {
Feed feed("Test Feed", 100.0, 1.5);
EXPECT_EQ(feed.getName(), "Test Feed");
EXPECT_DOUBLE_EQ(feed.getQuantity(), 100.0);
EXPECT_DOUBLE_EQ(feed.getPricePerKg(), 1.5);
EXPECT_EQ(feed.getQualityGrade(), "Standard");
}

TEST(FeedTest, ConstructorInvalidInput) {
EXPECT_THROW(Feed("", 100.0, 1.5), FeedException);
EXPECT_THROW(Feed("Test", -10.0, 1.5), FeedException);
EXPECT_THROW(Feed("Test", 100.0, -1.5), FeedException);
EXPECT_THROW(Feed("Test", 200000.0, 1.5), FeedException);
EXPECT_THROW(Feed("Test", 100.0, 150.0), FeedException);
}

TEST(FeedTest, DisplayInfo) {
Feed feed("Test Feed", 100.0, 1.5);
feed.setProteinContent(15.0);
feed.setFiberContent(25.0);

testing::internal::CaptureStdout();
feed.displayInfo();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("Test Feed") != std::string::npos);
EXPECT_TRUE(output.find("100") != std::string::npos);
EXPECT_TRUE(output.find("1.5") != std::string::npos);
}

TEST(FeedTest, CalculateTotalValue) {
Feed feed("Test Feed", 100.0, 1.5);
EXPECT_DOUBLE_EQ(feed.calculateTotalValue(), 150.0);

feed.setQuantity(50.0);
feed.setPricePerKg(2.0);
EXPECT_DOUBLE_EQ(feed.calculateTotalValue(), 100.0);
}

TEST(FeedTest, IsExpired) {
Feed feed("Test Feed", 100.0, 1.5);
feed.setExpirationDate("2024-12-31");

EXPECT_FALSE(feed.isExpired("2024-01-01"));
EXPECT_THROW(feed.isExpired("2025-01-01"), SpoiledFeedException);
EXPECT_THROW(feed.isExpired(""), FeedException);
}

TEST(FeedTest, CheckQuality) {
Feed feed("Test Feed", 100.0, 1.5);

testing::internal::CaptureStdout();
feed.setMoistureContent(25.0);
EXPECT_THROW(feed.checkQuality(), FeedException);
std::string output = testing::internal::GetCapturedStdout();

testing::internal::CaptureStdout();
feed.setMoistureContent(10.0);
feed.setProteinContent(3.0);
feed.checkQuality();
output = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output.find("Protein content is below") != std::string::npos);
}

TEST(FeedTest, Store) {
Feed feed("Test Feed", 100.0, 1.5);
feed.setStorageLocation("Test Storage");

testing::internal::CaptureStdout();
feed.store();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("Test Storage") != std::string::npos);
EXPECT_THROW(feed.setStorageLocation(""), FeedException);
}

TEST(FeedTest, GettersAndSetters) {
Feed feed("Test Feed", 100.0, 1.5);

// Проверка сеттеров с валидацией
EXPECT_THROW(feed.setName(""), FeedException);
feed.setName("New Name");
EXPECT_EQ(feed.getName(), "New Name");

EXPECT_THROW(feed.setQuantity(-10), FeedException);
feed.setQuantity(200.0);
EXPECT_DOUBLE_EQ(feed.getQuantity(), 200.0);

EXPECT_THROW(feed.setPricePerKg(-1), FeedException);
feed.setPricePerKg(2.0);
EXPECT_DOUBLE_EQ(feed.getPricePerKg(), 2.0);

EXPECT_THROW(feed.setProductionDate(""), FeedException);
feed.setProductionDate("2024-01-01");
EXPECT_EQ(feed.getProductionDate(), "2024-01-01");

EXPECT_THROW(feed.setProteinContent(60), FeedException);
feed.setProteinContent(20.0);
EXPECT_DOUBLE_EQ(feed.getProteinContent(), 20.0);

feed.setIsOrganic(true);
EXPECT_TRUE(feed.getIsOrganic());
}

TEST(FeedTest, CalculateNutritionalValue) {
Feed feed("Test Feed", 100.0, 1.5);
feed.setProteinContent(15.0);
feed.setFiberContent(25.0);

EXPECT_DOUBLE_EQ(feed.calculateNutritionalValue(), 15.0 * 10 + 25.0 * 5);
}

TEST(FeedTest, IsSuitableForAnimal) {
Feed feed("Test Feed", 100.0, 1.5);

EXPECT_THROW(feed.isSuitableForAnimal(""), FeedException);

testing::internal::CaptureStdout();
EXPECT_TRUE(feed.isSuitableForAnimal("Cow"));

feed.setMoistureContent(20.0);
EXPECT_THROW(feed.isSuitableForAnimal("Horse"), FeedException);
}

TEST(FeedTest, ApplyDiscount) {
Feed feed("Test Feed", 100.0, 2.0);

EXPECT_THROW(feed.applyDiscount(-10), FeedException);
EXPECT_THROW(feed.applyDiscount(110), FeedException);

testing::internal::CaptureStdout();
feed.applyDiscount(20.0);
std::string output = testing::internal::GetCapturedStdout();

EXPECT_DOUBLE_EQ(feed.getPricePerKg(), 1.6);
EXPECT_TRUE(output.find("Applied 20% discount") != std::string::npos);
}

TEST(FeedTest, UpdateStock) {
Feed feed("Test Feed", 100.0, 1.5);

EXPECT_THROW(feed.updateStock(-150), InsufficientFeedException);
EXPECT_THROW(feed.updateStock(2000), FeedException);

testing::internal::CaptureStdout();
feed.updateStock(50.0);
std::string output = testing::internal::GetCapturedStdout();

EXPECT_DOUBLE_EQ(feed.getQuantity(), 150.0);
EXPECT_TRUE(output.find("Updated stock") != std::string::npos);
}

// Тесты для класса Grain
TEST(GrainTest, Constructor) {
Grain grain(1000.0, "Corn", "Whole");
EXPECT_EQ(grain.getGrainType(), "Corn");
EXPECT_EQ(grain.getProcessingMethod(), "Whole");
EXPECT_DOUBLE_EQ(grain.getStarchContent(), 65.0);

EXPECT_THROW(Grain(200000.0, "Corn", "Whole"), FeedException);
EXPECT_THROW(Grain(1000.0, "", "Whole"), FeedException);
EXPECT_THROW(Grain(1000.0, "Corn", ""), FeedException);
EXPECT_THROW(Grain(1000.0, "Unknown", "Whole"), FeedException);
}

TEST(GrainTest, DisplayInfo) {
Grain grain(1000.0, "Wheat", "Ground");

testing::internal::CaptureStdout();
grain.displayInfo();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("Wheat") != std::string::npos);
EXPECT_TRUE(output.find("Ground") != std::string::npos);
EXPECT_TRUE(output.find("Starch content") != std::string::npos);
}

TEST(GrainTest, GrindGrain) {
Grain grain(1000.0, "Corn", "Whole");

grain.setMoistureContent(13.0);
testing::internal::CaptureStdout();
grain.grindGrain();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_EQ(grain.getProcessingMethod(), "Ground");
EXPECT_TRUE(output.find("has been ground") != std::string::npos);

EXPECT_THROW(grain.grindGrain(), FeedException);

Grain wetGrain(1000.0, "Corn", "Whole");
wetGrain.setMoistureContent(15.0);
EXPECT_THROW(wetGrain.grindGrain(), FeedException);
}

TEST(GrainTest, CleanGrain) {
Grain grain(1000.0, "Corn", "Whole");
grain.setForeignMaterial(3.0);

testing::internal::CaptureStdout();
grain.cleanGrain();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_DOUBLE_EQ(grain.getForeignMaterial(), 0.5);
EXPECT_TRUE(output.find("Cleaned grain") != std::string::npos);

grain.setForeignMaterial(0.3);
EXPECT_THROW(grain.cleanGrain(), FeedException);

grain.setForeignMaterial(6.0);
EXPECT_THROW(grain.cleanGrain(), FeedException);
}

TEST(GrainTest, TestGermination) {
Grain grain(1000.0, "Corn", "Whole");

grain.setGerminationRate(60.0);
EXPECT_THROW(grain.testGermination(), FeedException);

grain.setGerminationRate(80.0);
testing::internal::CaptureStdout();
grain.testGermination();
std::string output = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output.find("Warning") != std::string::npos);

grain.setGerminationRate(95.0);
testing::internal::CaptureStdout();
grain.testGermination();
output = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output.find("Excellent") != std::string::npos);
}

TEST(GrainTest, MixWithOtherGrains) {
Grain grain(1000.0, "Corn", "Whole");

EXPECT_THROW(grain.mixWithOtherGrains("", 100), FeedException);
EXPECT_THROW(grain.mixWithOtherGrains("Wheat", -50), FeedException);
EXPECT_THROW(grain.mixWithOtherGrains("Wheat", 1500), InsufficientFeedException);

testing::internal::CaptureStdout();
grain.mixWithOtherGrains("Wheat", 500.0);
std::string output = testing::internal::GetCapturedStdout();

EXPECT_DOUBLE_EQ(grain.getQuantity(), 1500.0);
EXPECT_TRUE(output.find("Mixed with") != std::string::npos);
}

TEST(GrainTest, GrainGettersAndSetters) {
Grain grain(1000.0, "Corn", "Whole");

EXPECT_THROW(grain.setGrainType(""), FeedException);
grain.setGrainType("Wheat");
EXPECT_EQ(grain.getGrainType(), "Wheat");

EXPECT_THROW(grain.setStarchContent(110), FeedException);
grain.setStarchContent(70.0);
EXPECT_DOUBLE_EQ(grain.getStarchContent(), 70.0);

EXPECT_THROW(grain.setTestWeight(0), FeedException);
grain.setTestWeight(75.0);
EXPECT_DOUBLE_EQ(grain.getTestWeight(), 75.0);

grain.setIsGMO(true);
EXPECT_TRUE(grain.getIsGMO());
}

TEST(GrainTest, CalculateEnergyDensity) {
Grain grain(1000.0, "Corn", "Whole");
grain.setStarchContent(75.0);

double energy = grain.calculateEnergyDensity();
EXPECT_GT(energy, 3.0);

Grain wheat(1000.0, "Wheat", "Ground");
energy = wheat.calculateEnergyDensity();
EXPECT_GT(energy, 3.0);
}

TEST(GrainTest, IsSuitableForAnimal_Grain) {
Grain grain(1000.0, "Corn", "Ground");

EXPECT_TRUE(grain.isSuitableForAnimal("Chicken"));

Grain wholeGrain(1000.0, "Corn", "Whole");
EXPECT_THROW(wholeGrain.isSuitableForAnimal("Chicken"), FeedException);

Grain barley(1000.0, "Barley", "Ground");
EXPECT_THROW(barley.isSuitableForAnimal("Chicken"), FeedException);

Grain oats(1000.0, "Oats", "Whole");
EXPECT_TRUE(oats.isSuitableForAnimal("Horse"));

Grain wheat(1000.0, "Wheat", "Ground");
EXPECT_TRUE(wheat.isSuitableForAnimal("Pig"));
}

TEST(GrainTest, ProcessToMethod) {
Grain grain(1000.0, "Corn", "Whole");

EXPECT_THROW(grain.processToMethod(""), FeedException);
EXPECT_THROW(grain.processToMethod("Whole"), FeedException);

testing::internal::CaptureStdout();
grain.processToMethod("Cracked");
std::string output = testing::internal::GetCapturedStdout();

EXPECT_EQ(grain.getProcessingMethod(), "Cracked");
EXPECT_TRUE(output.find("processed to") != std::string::npos);
}

TEST(GrainTest, CheckForContaminants) {
Grain grain(1000.0, "Corn", "Whole");

grain.setForeignMaterial(6.0);
EXPECT_THROW(grain.checkForContaminants(), FeedException);

grain.setForeignMaterial(3.0);
testing::internal::CaptureStdout();
grain.checkForContaminants();
std::string output = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output.find("Warning") != std::string::npos);

grain.setForeignMaterial(1.0);
grain.setIsGMO(true);
testing::internal::CaptureStdout();
grain.checkForContaminants();
output = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output.find("GMO grain") != std::string::npos);
}

// Тесты для класса Hay
TEST(HayTest, Constructor) {
Hay hay(5000.0, "Timothy", "First");
EXPECT_EQ(hay.getGrassType(), "Timothy");
EXPECT_EQ(hay.getCut(), "First");
EXPECT_DOUBLE_EQ(hay.getLeafToStemRatio(), 0.6);

EXPECT_THROW(Hay(60000.0, "Timothy", "First"), FeedException);
EXPECT_THROW(Hay(5000.0, "", "First"), FeedException);
EXPECT_THROW(Hay(5000.0, "Timothy", ""), FeedException);
}

TEST(HayTest, DisplayInfo) {
Hay hay(5000.0, "Alfalfa", "Second");

testing::internal::CaptureStdout();
hay.displayInfo();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("Alfalfa") != std::string::npos);
EXPECT_TRUE(output.find("Second") != std::string::npos);
EXPECT_TRUE(output.find("Bale type") != std::string::npos);
}

TEST(HayTest, BaleHay) {
Hay hay(1000.0, "Timothy", "First");
hay.setBaleWeight(20.0);

testing::internal::CaptureStdout();
hay.baleHay();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("Baled") != std::string::npos);

Hay smallHay(10.0, "Timothy", "First");
smallHay.setBaleWeight(20.0);
EXPECT_THROW(smallHay.baleHay(), FeedException);

hay.setBaleWeight(0);
EXPECT_THROW(hay.baleHay(), FeedException);
}

TEST(HayTest, CureHay) {
Hay hay(1000.0, "Timothy", "First");
hay.setMoistureContent(30.0);
hay.setIsSunCured(false);

testing::internal::CaptureStdout();
hay.cureHay();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(hay.getIsSunCured());
EXPECT_LT(hay.getMoistureContent(), 30.0);
EXPECT_TRUE(output.find("sun cured") != std::string::npos);

EXPECT_THROW(hay.cureHay(), FeedException);

Hay dryHay(1000.0, "Timothy", "First");
dryHay.setMoistureContent(4.0);
EXPECT_THROW(dryHay.cureHay(), FeedException);
}

TEST(HayTest, TestMoisture) {
Hay hay(1000.0, "Timothy", "First");

hay.setMoistureContent(25.0);
EXPECT_THROW(hay.testMoisture(), FeedException);

hay.setMoistureContent(18.0);
testing::internal::CaptureStdout();
hay.testMoisture();
std::string output = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output.find("Warning") != std::string::npos);

hay.setMoistureContent(8.0);
testing::internal::CaptureStdout();
hay.testMoisture();
output = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output.find("too dry") != std::string::npos);
}

TEST(HayTest, StackBales) {
Hay hay(1000.0, "Timothy", "First");
hay.setStorageLocation("Barn");

testing::internal::CaptureStdout();
hay.stackBales();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("Stacking") != std::string::npos);

hay.setStorageLocation("");
EXPECT_THROW(hay.stackBales(), FeedException);
}

TEST(HayTest, HayGettersAndSetters) {
Hay hay(1000.0, "Timothy", "First");

EXPECT_THROW(hay.setGrassType(""), FeedException);
hay.setGrassType("Alfalfa");
EXPECT_EQ(hay.getGrassType(), "Alfalfa");

EXPECT_THROW(hay.setLeafToStemRatio(1.5), FeedException);
hay.setLeafToStemRatio(0.8);
EXPECT_DOUBLE_EQ(hay.getLeafToStemRatio(), 0.8);

EXPECT_THROW(hay.setBaleWeight(0), FeedException);
hay.setBaleWeight(25.0);
EXPECT_DOUBLE_EQ(hay.getBaleWeight(), 25.0);

hay.setIsSunCured(true);
EXPECT_TRUE(hay.getIsSunCured());
}

TEST(HayTest, CalculateEnergyValue) {
Hay hay(1000.0, "Alfalfa", "Second");
hay.setLeafToStemRatio(0.8);

double energy = hay.calculateEnergyValue();
EXPECT_GT(energy, 1.5);

Hay timothy(1000.0, "Timothy", "First");
energy = timothy.calculateEnergyValue();
EXPECT_GE(energy, 1.5);
}

TEST(HayTest, IsSuitableForAnimal_Hay) {
Hay hay(1000.0, "Timothy", "First");
hay.setDustContent(2.0);

EXPECT_TRUE(hay.isSuitableForAnimal("Horse"));

hay.setDustContent(5.0);
EXPECT_THROW(hay.isSuitableForAnimal("Horse"), FeedException);

Hay alfalfa(1000.0, "Alfalfa", "First");
EXPECT_THROW(alfalfa.isSuitableForAnimal("Horse"), FeedException);

Hay rabbitHay(1000.0, "Timothy", "First");
rabbitHay.setFiberContent(30.0);
EXPECT_TRUE(rabbitHay.isSuitableForAnimal("Rabbit"));

rabbitHay.setFiberContent(20.0);
EXPECT_THROW(rabbitHay.isSuitableForAnimal("Rabbit"), FeedException);
}

TEST(HayTest, CompressBales) {
Hay hay(1000.0, "Timothy", "First");
hay.setBaleType("Square");
hay.setBaleWeight(20.0);

testing::internal::CaptureStdout();
hay.compressBales();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_DOUBLE_EQ(hay.getBaleWeight(), 30.0);
EXPECT_TRUE(output.find("compressed") != std::string::npos);

hay.setBaleType("Round");
EXPECT_THROW(hay.compressBales(), FeedException);

hay.setBaleType("Square");
hay.setBaleWeight(30.0);
EXPECT_THROW(hay.compressBales(), FeedException);
}

TEST(HayTest, GradeHay) {
Hay hay(1000.0, "Alfalfa", "Second");
hay.setProteinContent(12.0);
hay.setLeafToStemRatio(0.8);
hay.setColor("Green");

testing::internal::CaptureStdout();
hay.gradeHay();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_EQ(hay.getQualityGrade(), "Premium");
EXPECT_GT(hay.getPricePerKg(), 0.8);
EXPECT_TRUE(output.find("Premium") != std::string::npos);
}

// Тесты для класса CompoundFeed
TEST(CompoundFeedTest, Constructor) {
CompoundFeed feed(1000.0, "Chicken", "Medium");
EXPECT_EQ(feed.getTargetAnimal(), "Chicken");
EXPECT_EQ(feed.getPelletSize(), "Medium");
EXPECT_DOUBLE_EQ(feed.getPelletDurability(), 95.0);
EXPECT_FALSE(feed.getIsMedicated());

EXPECT_THROW(CompoundFeed(60000.0, "Chicken", "Medium"), FeedException);
EXPECT_THROW(CompoundFeed(1000.0, "", "Medium"), FeedException);
EXPECT_THROW(CompoundFeed(1000.0, "Chicken", ""), FeedException);
EXPECT_THROW(CompoundFeed(1000.0, "Unknown", "Medium"), FeedException);
}

TEST(CompoundFeedTest, DisplayInfo) {
CompoundFeed feed(1000.0, "Pig", "Large");

testing::internal::CaptureStdout();
feed.displayInfo();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("Pig") != std::string::npos);
EXPECT_TRUE(output.find("Large") != std::string::npos);
EXPECT_TRUE(output.find("Ingredients") != std::string::npos);

CompoundFeed emptyFeed(1000.0, "Cow", "Medium");
emptyFeed.setIngredients({});
EXPECT_THROW(emptyFeed.displayInfo(), FeedException);
}

TEST(CompoundFeedTest, Pelletize) {
CompoundFeed feed(1000.0, "Chicken", "Medium");

feed.setMoistureContent(14.0);
testing::internal::CaptureStdout();
feed.pelletize();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_DOUBLE_EQ(feed.getPelletDurability(), 98.0);
EXPECT_TRUE(output.find("pelletized") != std::string::npos);

feed.setMoistureContent(10.0);
EXPECT_THROW(feed.pelletize(), FeedException);

feed.setMoistureContent(18.0);
EXPECT_THROW(feed.pelletize(), FeedException);
}

TEST(CompoundFeedTest, AddIngredient) {
CompoundFeed feed(1000.0, "Chicken", "Medium");
auto ingredients = feed.getIngredients();
size_t initialSize = ingredients.size();

testing::internal::CaptureStdout();
feed.addIngredient("Molasses");
std::string output = testing::internal::GetCapturedStdout();

ingredients = feed.getIngredients();
EXPECT_EQ(ingredients.size(), initialSize + 1);
EXPECT_TRUE(output.find("Added") != std::string::npos);

EXPECT_THROW(feed.addIngredient(""), FeedException);
EXPECT_THROW(feed.addIngredient("Molasses"), FeedException);

// Проверка обновления питательной ценности
double initialProtein = feed.getProteinContent();
feed.addIngredient("Soybean Meal");
EXPECT_GT(feed.getProteinContent(), initialProtein);
}

TEST(CompoundFeedTest, AddMedication) {
CompoundFeed feed(1000.0, "Pig", "Medium");
double initialPrice = feed.getPricePerKg();

testing::internal::CaptureStdout();
feed.addMedication("Antibiotic");
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(feed.getIsMedicated());
EXPECT_EQ(feed.getMedicationType(), "Antibiotic");
EXPECT_GT(feed.getPricePerKg(), initialPrice);
EXPECT_TRUE(output.find("Added medication") != std::string::npos);

EXPECT_THROW(feed.addMedication("Another"), FeedException);

CompoundFeed chickenFeed(1000.0, "Chicken", "Medium");
EXPECT_THROW(chickenFeed.addMedication("Antibiotic"), FeedException);
}

TEST(CompoundFeedTest, MixFeed) {
CompoundFeed feed(1000.0, "Cow", "Medium");

testing::internal::CaptureStdout();
feed.mixFeed();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("Mixing") != std::string::npos);

feed.setIngredients({});
EXPECT_THROW(feed.mixFeed(), FeedException);

feed.setIngredients({"Corn"});
feed.setQuantity(0);
EXPECT_THROW(feed.mixFeed(), FeedException);
}

TEST(CompoundFeedTest, CompoundFeedGettersAndSetters) {
CompoundFeed feed(1000.0, "Chicken", "Medium");

EXPECT_THROW(feed.setTargetAnimal(""), FeedException);
feed.setTargetAnimal("Pig");
EXPECT_EQ(feed.getTargetAnimal(), "Pig");

EXPECT_THROW(feed.setPelletSize(""), FeedException);
feed.setPelletSize("Small");
EXPECT_EQ(feed.getPelletSize(), "Small");

EXPECT_THROW(feed.setPelletDurability(110), FeedException);
feed.setPelletDurability(90.0);
EXPECT_DOUBLE_EQ(feed.getPelletDurability(), 90.0);

EXPECT_THROW(feed.setIngredients({}), FeedException);
feed.setIngredients({"Corn", "Soy"});
EXPECT_EQ(feed.getIngredients().size(), 2);

feed.setFatContent(10.0);
EXPECT_DOUBLE_EQ(feed.getFatContent(), 10.0);
}

TEST(CompoundFeedTest, CalculateCompleteNutrition) {
CompoundFeed feed(1000.0, "Chicken", "Medium");
feed.setProteinContent(15.0);
feed.setFiberContent(10.0);
feed.setFatContent(5.0);

double nutrition = feed.calculateCompleteNutrition();
EXPECT_GT(nutrition, 0);

feed.setProteinContent(5.0);
EXPECT_THROW(feed.calculateCompleteNutrition(), FeedException);
}

TEST(CompoundFeedTest, IsSuitableForAnimal_CompoundFeed) {
CompoundFeed feed(1000.0, "Chicken", "Medium");

EXPECT_TRUE(feed.isSuitableForAnimal("Chicken"));
EXPECT_THROW(feed.isSuitableForAnimal("Cow"), FeedException);
EXPECT_THROW(feed.isSuitableForAnimal(""), FeedException);
}

TEST(CompoundFeedTest, CreateCustomFormula) {
CompoundFeed feed(1000.0, "Pig", "Medium");

std::vector<std::string> newIngredients = {"Corn", "Barley", "Wheat"};
testing::internal::CaptureStdout();
feed.createCustomFormula(newIngredients);
std::string output = testing::internal::GetCapturedStdout();

EXPECT_EQ(feed.getIngredients().size(), 3);
EXPECT_TRUE(output.find("custom formula") != std::string::npos);
EXPECT_TRUE(feed.getFormulaCode().find("CUSTOM") != std::string::npos);

EXPECT_THROW(feed.createCustomFormula({}), FeedException);

std::vector<std::string> toxicIngredients = {"Urea"};
CompoundFeed chickenFeed(1000.0, "Chicken", "Medium");
EXPECT_THROW(chickenFeed.createCustomFormula(toxicIngredients), FeedException);
}

TEST(CompoundFeedTest, TestPelletQuality) {
CompoundFeed feed(1000.0, "Cow", "Medium");

feed.setPelletDurability(80.0);
EXPECT_THROW(feed.testPelletQuality(), FeedException);

feed.setPelletDurability(88.0);
testing::internal::CaptureStdout();
feed.testPelletQuality();
std::string output = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output.find("Warning") != std::string::npos);
EXPECT_EQ(feed.getQualityGrade(), "Low");

feed.setPelletDurability(92.0);
testing::internal::CaptureStdout();
feed.testPelletQuality();
output = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output.find("acceptable") != std::string::npos);
EXPECT_EQ(feed.getQualityGrade(), "Medium");

feed.setPelletDurability(97.0);
testing::internal::CaptureStdout();
feed.testPelletQuality();
output = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output.find("Excellent") != std::string::npos);
EXPECT_EQ(feed.getQualityGrade(), "High");
}

// Тесты для иерархии и полиморфизма
TEST(PolymorphismTest, VirtualFunctions) {
Feed* feed1 = new Grain(1000.0, "Corn", "Whole");
Feed* feed2 = new Hay(5000.0, "Timothy", "First");
Feed* feed3 = new CompoundFeed(2000.0, "Chicken", "Medium");

// Проверка displayInfo()
testing::internal::CaptureStdout();
feed1->displayInfo();
std::string output1 = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output1.find("Grain") != std::string::npos);

testing::internal::CaptureStdout();
feed2->displayInfo();
std::string output2 = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output2.find("Hay") != std::string::npos);

testing::internal::CaptureStdout();
feed3->displayInfo();
std::string output3 = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output3.find("Compound Feed") != std::string::npos);

// Проверка isSuitableForAnimal()
EXPECT_NO_THROW(feed1->isSuitableForAnimal("Pig"));
EXPECT_NO_THROW(feed2->isSuitableForAnimal("Horse"));
EXPECT_NO_THROW(feed3->isSuitableForAnimal("Chicken"));

delete feed1;
delete feed2;
delete feed3;
}

// Тесты для исключений
TEST(ExceptionTest, FeedExceptions) {
try {
throw FeedException("Test error");
FAIL() << "Expected FeedException";
} catch (const FeedException& e) {
EXPECT_TRUE(std::string(e.what()).find("Test error") != std::string::npos);
}

try {
throw SpoiledFeedException("Test Feed", "2024-01-01", "2024-02-01");
FAIL() << "Expected SpoiledFeedException";
} catch (const SpoiledFeedException& e) {
EXPECT_EQ(e.getFeedType(), "Test Feed");
EXPECT_EQ(e.getExpirationDate(), "2024-01-01");
EXPECT_TRUE(std::string(e.what()).find("spoiled") != std::string::npos);
}

try {
throw InsufficientFeedException("Cows", 100.0, 50.0);
FAIL() << "Expected InsufficientFeedException";
} catch (const InsufficientFeedException& e) {
EXPECT_EQ(e.getAnimalType(), "Cows");
EXPECT_DOUBLE_EQ(e.getRequiredAmount(), 100.0);
EXPECT_DOUBLE_EQ(e.getAvailableAmount(), 50.0);
}
}

// Интеграционные тесты
TEST(IntegrationTest, FeedManagementSystem) {
// Создаем различные типы кормов
Grain corn(5000.0, "Corn", "Ground");
Hay alfalfa(3000.0, "Alfalfa", "Second");
CompoundFeed chickenFeed(2000.0, "Chicken", "Small");

// Устанавливаем цены
corn.setPricePerKg(1.2);
alfalfa.setPricePerKg(0.9);
chickenFeed.setPricePerKg(1.8);

// Проверяем общую стоимость
double totalValue = corn.calculateTotalValue() +
                    alfalfa.calculateTotalValue() +
                    chickenFeed.calculateTotalValue();
EXPECT_GT(totalValue, 0);

// Проверяем питательную ценность
EXPECT_GT(corn.calculateNutritionalValue(), 0);
EXPECT_GT(alfalfa.calculateEnergyValue(), 0);
EXPECT_GT(chickenFeed.calculateCompleteNutrition(), 0);

// Проверяем пригодность для животных
EXPECT_NO_THROW(corn.isSuitableForAnimal("Pig"));
EXPECT_NO_THROW(alfalfa.isSuitableForAnimal("Cow"));
EXPECT_NO_THROW(chickenFeed.isSuitableForAnimal("Chicken"));

// Обновляем запасы
corn.updateStock(1000.0);
EXPECT_DOUBLE_EQ(corn.getQuantity(), 6000.0);

// Применяем скидку
double originalPrice = alfalfa.getPricePerKg();
alfalfa.applyDiscount(10.0);
EXPECT_LT(alfalfa.getPricePerKg(), originalPrice);

// Добавляем ингредиенты в комбикорм
chickenFeed.addIngredient("Fish Meal");
auto ingredients = chickenFeed.getIngredients();
EXPECT_GT(ingredients.size(), 0);
}

TEST(IntegrationTest, FeedQualitySystem) {
// Тестируем систему контроля качества
CompoundFeed feed(1000.0, "Pig", "Medium");

// Устанавливаем параметры качества
feed.setMoistureContent(13.0);
feed.setProteinContent(18.0);

// Проверяем качество
EXPECT_NO_THROW(feed.checkQuality());

// Гранулируем
feed.pelletize();
EXPECT_DOUBLE_EQ(feed.getPelletDurability(), 98.0);

// Тестируем качество гранул
feed.testPelletQuality();
EXPECT_EQ(feed.getQualityGrade(), "High");

// Добавляем лекарство
feed.addMedication("Vitamin Supplement");
EXPECT_TRUE(feed.getIsMedicated());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}