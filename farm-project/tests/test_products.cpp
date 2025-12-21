// test_products.cpp
#include <gtest/gtest.h>
#include "Product.h"
#include "Egg.h"
#include "FruitProduct.h"
#include "GrainProduct.h"
#include "Meat.h"
#include "Milk.h"
#include "VegetableProduct.h"
#include "Wool.h"
#include "ProductExceptions.h"
#include <iostream>
#include <memory>

// ==================== Базовый класс Product ====================
TEST(ProductTest, ConstructorAndGetters) {
Product product("Test Product", 100.0, 10.0);

EXPECT_EQ(product.getName(), "Test Product");
EXPECT_EQ(product.getQuantity(), 100.0);
EXPECT_EQ(product.getPricePerUnit(), 10.0);
EXPECT_EQ(product.getQualityGrade(), "A");
EXPECT_FALSE(product.getIsOrganic());
}

TEST(ProductTest, InvalidConstructorParameters) {
EXPECT_THROW(Product("", 100.0, 10.0), ProductException);
EXPECT_THROW(Product("Test", -100.0, 10.0), ProductException);
EXPECT_THROW(Product("Test", 100.0, -10.0), ProductException);
EXPECT_THROW(Product("Test", 2000000.0, 10.0), ProductException);
EXPECT_THROW(Product("Test", 100.0, 20000.0), ProductException);
}

TEST(ProductTest, Setters) {
Product product("Test", 100.0, 10.0);

product.setName("New Name");
EXPECT_EQ(product.getName(), "New Name");

product.setQuantity(50.0);
EXPECT_EQ(product.getQuantity(), 50.0);

product.setPricePerUnit(20.0);
EXPECT_EQ(product.getPricePerUnit(), 20.0);

product.setQualityGrade("B");
EXPECT_EQ(product.getQualityGrade(), "B");

EXPECT_THROW(product.setQualityGrade("E"), QualityException);
EXPECT_THROW(product.setQuantity(-10.0), ProductException);
EXPECT_THROW(product.setPricePerUnit(-5.0), ProductException);
}

TEST(ProductTest, CalculateTotalValue) {
Product product("Test", 100.0, 10.0);
EXPECT_EQ(product.calculateTotalValue(), 1000.0);

product.setQuantity(50.0);
product.setPricePerUnit(20.0);
EXPECT_EQ(product.calculateTotalValue(), 1000.0);
}

TEST(ProductTest, ExpirationChecks) {
Product product("Test", 100.0, 10.0);

product.setProductionDate("2024-01-01");
product.setExpirationDate("2024-12-31");

EXPECT_THROW(product.isExpired(""), ProductException);
EXPECT_FALSE(product.isExpired("2024-06-01"));
EXPECT_THROW(product.isExpired("2025-01-01"), ExpirationException);
}

TEST(ProductTest, ApplyDiscount) {
Product product("Test", 100.0, 100.0);

product.applyDiscount(10.0);
EXPECT_EQ(product.getPricePerUnit(), 90.0);

product.setQualityGrade("A");
EXPECT_THROW(product.applyDiscount(60.0), ProductException);
EXPECT_THROW(product.applyDiscount(-10.0), ProductException);
EXPECT_THROW(product.applyDiscount(110.0), ProductException);
}

TEST(ProductTest, ExportStandards) {
Product product("Organic Test", 100.0, 10.0);
product.setQualityGrade("A");
product.setIsOrganic(true);

EXPECT_TRUE(product.meetsExportStandards());

product.setQualityGrade("B");
EXPECT_THROW(product.meetsExportStandards(), QualityException);
}

// ==================== Класс Egg ====================
TEST(EggTest, ConstructorAndBasicOperations) {
Egg egg(100, "Large", "Brown");

EXPECT_EQ(egg.getEggSize(), "Large");
EXPECT_EQ(egg.getShellColor(), "Brown");
EXPECT_EQ(egg.getYolkColorGrade(), 8.0);
EXPECT_EQ(egg.getQuantity(), 100);
EXPECT_FALSE(egg.getIsFertilized());
}

TEST(EggTest, InvalidConstructorParameters) {
EXPECT_THROW(Egg(0, "Large", "Brown"), ProductException);
EXPECT_THROW(Egg(-100, "Large", "Brown"), ProductException);
EXPECT_THROW(Egg(20000, "Large", "Brown"), ProductException);
EXPECT_THROW(Egg(100, "Huge", "Brown"), ProductException);
EXPECT_THROW(Egg(100, "Large", "Blue"), ProductException);
}

TEST(EggTest, EggGettersAndSetters) {
Egg egg(100, "Medium", "White");

egg.setEggSize("X-Large");
EXPECT_EQ(egg.getEggSize(), "X-Large");
EXPECT_THROW(egg.setEggSize("Huge"), ProductException);

egg.setShellColor("Brown");
EXPECT_EQ(egg.getShellColor(), "Brown");
EXPECT_THROW(egg.setShellColor("Blue"), ProductException);

egg.setYolkColorGrade(10.0);
EXPECT_EQ(egg.getYolkColorGrade(), 10.0);
EXPECT_THROW(egg.setYolkColorGrade(20.0), ProductException);

egg.setShellThickness(0.4);
EXPECT_EQ(egg.getShellThickness(), 0.4);
EXPECT_THROW(egg.setShellThickness(-0.1), ProductException);
EXPECT_THROW(egg.setShellThickness(2.0), ProductException);
}

TEST(EggTest, EggOperations) {
Egg egg(100, "Large", "Brown");

// Тест просвечивания
egg.setShellThickness(0.25);
EXPECT_NO_THROW(egg.candleEgg());

egg.setShellThickness(0.1);
EXPECT_THROW(egg.candleEgg(), QualityException);

// Тест градации
egg.setYolkColorGrade(12.0);
EXPECT_NO_THROW(egg.gradeEgg());
EXPECT_EQ(egg.getQualityGrade(), "AA");

egg.setYolkColorGrade(2.0);
EXPECT_THROW(egg.gradeEgg(), QualityException);

// Тест мойки
egg.setQuantity(100);
egg.setShellThickness(0.3);
EXPECT_NO_THROW(egg.washEggs());

// Тест упаковки
egg.setQuantity(12);
EXPECT_NO_THROW(egg.packInCarton());

egg.setQuantity(13);
EXPECT_THROW(egg.packInCarton(), PackagingException);
}

TEST(EggTest, AdditionalMethods) {
Egg egg(100, "Large", "Brown");

EXPECT_TRUE(egg.checkFreshness());

egg.setShellThickness(0.1);
EXPECT_FALSE(egg.checkFreshness());

EXPECT_EQ(egg.calculateProteinContent(), 6.3);

egg.setEggSize("Small");
EXPECT_EQ(egg.calculateProteinContent(), 4.8);

EXPECT_NO_THROW(egg.sortBySize());
}

// ==================== Класс FruitProduct ====================
TEST(FruitProductTest, ConstructorAndBasicOperations) {
FruitProduct fruit("Apples", 50.0, 2.0, "Apples");

EXPECT_EQ(fruit.getFruitType(), "Apples");
EXPECT_EQ(fruit.getRipenessLevel(), 70.0);
EXPECT_EQ(fruit.getRipenessStage(), "Ripening");
EXPECT_FALSE(fruit.getIsPackagedInBaskets());
EXPECT_EQ(fruit.getBrixLevel(), 12);
}

TEST(FruitProductTest, InvalidConstructorParameters) {
EXPECT_THROW(FruitProduct("", 50.0, 2.0, "Apples"), ProductException);
EXPECT_THROW(FruitProduct("Apples", 50.0, 2.0, ""), ProductException);
EXPECT_THROW(FruitProduct("Apples", -50.0, 2.0, "Apples"), ProductException);
}

TEST(FruitProductTest, FruitSpecificOperations) {
FruitProduct fruit("Apples", 50.0, 2.0, "Apples");

// Тест созревания
EXPECT_NO_THROW(fruit.ripenFruit(10.0));
EXPECT_GT(fruit.getRipenessLevel(), 70.0);

fruit.setRipenessLevel(95.0);
EXPECT_THROW(fruit.ripenFruit(10.0), ProductException);

// Тест добавления повреждений
EXPECT_NO_THROW(fruit.addBruise("Side"));
EXPECT_FALSE(fruit.getBruises().empty());

// Тест удаления повреждений
EXPECT_NO_THROW(fruit.removeBruises());
EXPECT_TRUE(fruit.getBruises().empty());

// Тест упаковки в корзины
fruit.setRipenessLevel(80.0);
fruit.setQualityGrade("A");
EXPECT_NO_THROW(fruit.packageInBaskets());
EXPECT_TRUE(fruit.getIsPackagedInBaskets());
}

TEST(FruitProductTest, QualityChecks) {
FruitProduct fruit("Apples", 50.0, 2.0, "Apples");
fruit.setRipenessLevel(80.0);
fruit.setQualityGrade("A");

EXPECT_TRUE(fruit.isReadyForSale());

fruit.addBruise("Top");
EXPECT_THROW(fruit.isReadyForSale(), QualityException);

EXPECT_GT(fruit.calculateSugarContent(), 0.0);
}

// ==================== Класс GrainProduct ====================
TEST(GrainProductTest, ConstructorAndBasicOperations) {
GrainProduct grain("Wheat", 1000.0, 0.5, "Wheat");

EXPECT_EQ(grain.getGrainType(), "Wheat");
EXPECT_EQ(grain.getMoistureContent(), 14.0);
EXPECT_EQ(grain.getProteinContent(), 12.0);
EXPECT_FALSE(grain.getIsCleaned());
EXPECT_EQ(grain.getMillingGrade(), "Standard");
}

TEST(GrainProductTest, GrainSpecificOperations) {
GrainProduct grain("Wheat", 1000.0, 0.5, "Wheat");

// Тест очистки
EXPECT_NO_THROW(grain.cleanGrain());
EXPECT_TRUE(grain.getIsCleaned());
EXPECT_LT(grain.getQuantity(), 1000.0);

// Тест добавления загрязнителей
EXPECT_NO_THROW(grain.addContaminant("Stone"));
EXPECT_FALSE(grain.getContaminants().empty());

// Тест удаления загрязнителей
EXPECT_NO_THROW(grain.removeContaminants());
EXPECT_TRUE(grain.getContaminants().empty());

// Тест проверки влажности
EXPECT_NO_THROW(grain.checkMoistureLevel());

grain.setMoistureContent(20.0);
EXPECT_THROW(grain.checkMoistureLevel(), QualityException);
}

TEST(GrainProductTest, CalculationsAndGrading) {
GrainProduct grain("Wheat", 1000.0, 0.5, "Wheat");

EXPECT_GT(grain.calculateNutritionalValue(), 0.0);
EXPECT_FALSE(grain.getGrainClass().empty());

grain.setMoistureContent(12.0);
grain.setProteinContent(16.0);
grain.cleanGrain();
EXPECT_EQ(grain.getGrainClass(), "Premium");
}

// ==================== Класс Meat ====================
TEST(MeatTest, ConstructorAndBasicOperations) {
Meat meat(50.0, "Beef", "Ribeye");

EXPECT_EQ(meat.getAnimalType(), "Beef");
EXPECT_EQ(meat.getCut(), "Ribeye");
EXPECT_EQ(meat.getFatPercentage(), 12.0);
EXPECT_EQ(meat.getGrade(), "Choice");
EXPECT_EQ(meat.getAgingMethod(), "Wet-aged");
EXPECT_EQ(meat.getAgingDays(), 0);
}

TEST(MeatTest, InvalidConstructorParameters) {
EXPECT_THROW(Meat(0, "Beef", "Ribeye"), ProductException);
EXPECT_THROW(Meat(-50.0, "Beef", "Ribeye"), ProductException);
EXPECT_THROW(Meat(600.0, "Beef", "Ribeye"), ProductException);
EXPECT_THROW(Meat(50.0, "Horse", "Ribeye"), ProductException);
}

TEST(MeatTest, MeatProcessingOperations) {
Meat meat(50.0, "Beef", "Ribeye");

// Тест выдержки
EXPECT_NO_THROW(meat.ageMeat(14));
EXPECT_EQ(meat.getAgingDays(), 14);
EXPECT_EQ(meat.getAgingMethod(), "Dry-aged");

EXPECT_THROW(meat.ageMeat(50), ExpirationException);

// Тест маринования
Meat chicken(20.0, "Chicken", "Breast");
EXPECT_NO_THROW(chicken.marinate());
EXPECT_TRUE(chicken.getIsMarinated());

// Тест обрезки жира
EXPECT_NO_THROW(meat.trimFat());
EXPECT_LT(meat.getFatPercentage(), 12.0);
EXPECT_LT(meat.getQuantity(), 50.0);

// Тест вакуумной упаковки
EXPECT_NO_THROW(meat.vacuumPack());
}

TEST(MeatTest, MeatCalculations) {
Meat meat(50.0, "Beef", "Filet Mignon");

EXPECT_GT(meat.calculateTenderness(), 0.0);
EXPECT_TRUE(meat.isPremiumCut());

meat.setCut("Ribeye");
EXPECT_TRUE(meat.isPremiumCut());

meat.setCut("Shoulder");
EXPECT_FALSE(meat.isPremiumCut());

EXPECT_NO_THROW(meat.recommendCookingMethod());
EXPECT_FALSE(meat.getCookingRecommendation().empty());

EXPECT_NO_THROW(meat.sliceIntoPortions(1.0));
}

// ==================== Класс Milk ====================
TEST(MilkTest, ConstructorAndBasicOperations) {
Milk milk(100.0, 3.2, "Cow");

EXPECT_EQ(milk.getFatContent(), 3.2);
EXPECT_EQ(milk.getSourceAnimal(), "Cow");
EXPECT_TRUE(milk.getIsPasteurized());
EXPECT_EQ(milk.getPackagingType(), "Carton");
EXPECT_EQ(milk.getMilkType(), "Whole");
EXPECT_GT(milk.getBacterialCount(), 0);
}

TEST(MilkTest, InvalidConstructorParameters) {
EXPECT_THROW(Milk(0, 3.2, "Cow"), ProductException);
EXPECT_THROW(Milk(-100.0, 3.2, "Cow"), ProductException);
EXPECT_THROW(Milk(2000.0, 3.2, "Cow"), ProductException);
EXPECT_THROW(Milk(100.0, -1.0, "Cow"), ProductException);
EXPECT_THROW(Milk(100.0, 3.2, "Horse"), ProductException);
}

TEST(MilkTest, MilkProcessingOperations) {
Milk rawMilk(100.0, 3.2, "Cow");
rawMilk.setIsPasteurized(false);
rawMilk.setBacterialCount(100000);

// Тест пастеризации
EXPECT_NO_THROW(rawMilk.pasteurize());
EXPECT_TRUE(rawMilk.getIsPasteurized());
EXPECT_LT(rawMilk.getBacterialCount(), 100000);

// Тест гомогенизации
Milk milk(100.0, 3.2, "Cow");
EXPECT_NO_THROW(milk.homogenize());
EXPECT_EQ(milk.getHomogenizationLevel(), "Partial");

// Тест обогащения
EXPECT_NO_THROW(milk.fortify());
EXPECT_TRUE(milk.getIsFortified());
EXPECT_GT(milk.getPricePerUnit(), 1.5);

// Тест проверки свежести
EXPECT_NO_THROW(milk.checkFreshness());

milk.setBacterialCount(60000);
EXPECT_THROW(milk.checkFreshness(), QualityException);
}

TEST(MilkTest, MilkCalculationsAndChecks) {
Milk milk(100.0, 3.2, "Cow");

EXPECT_GT(milk.calculateNutritionalValue(), 0.0);
EXPECT_TRUE(milk.isSafeForConsumption());

EXPECT_NO_THROW(milk.adjustFatContent(2.0));
EXPECT_EQ(milk.getMilkType(), "2%");

EXPECT_NO_THROW(milk.makeCheese(5.0));
EXPECT_LT(milk.getQuantity(), 100.0);

milk.setFatContent(2.5);
EXPECT_EQ(milk.getMilkType(), "2%");
}

// ==================== Класс VegetableProduct ====================
TEST(VegetableProductTest, ConstructorAndBasicOperations) {
VegetableProduct veg("Carrots", 50.0, 1.5, "Carrot");

EXPECT_EQ(veg.getVegetableType(), "Carrot");
EXPECT_EQ(veg.getFreshnessLevel(), 100.0);
EXPECT_FALSE(veg.getIsWashed());
EXPECT_FALSE(veg.getIsCut());
EXPECT_EQ(veg.getSizeCategory(), "Medium");
}

TEST(VegetableProductTest, VegetableProcessingOperations) {
VegetableProduct veg("Carrots", 50.0, 1.5, "Carrot");

// Тест мойки
EXPECT_NO_THROW(veg.washVegetables());
EXPECT_TRUE(veg.getIsWashed());
EXPECT_EQ(veg.getFreshnessLevel(), 100.0);

// Тест нарезки
EXPECT_NO_THROW(veg.cutVegetables());
EXPECT_TRUE(veg.getIsCut());
EXPECT_LT(veg.getQuantity(), 50.0);

// Тест проверки свежести
EXPECT_NO_THROW(veg.checkFreshness());

// Тест добавления дефектов
EXPECT_NO_THROW(veg.addDefect("Bruise"));
EXPECT_FALSE(veg.getDefects().empty());

// Тест удаления дефектов
EXPECT_NO_THROW(veg.removeDefects());
EXPECT_TRUE(veg.getDefects().empty());
}

TEST(VegetableProductTest, VegetableCalculations) {
VegetableProduct veg("Carrots", 50.0, 1.5, "Carrot");

EXPECT_GT(veg.calculateVitaminContent(), 0.0);

veg.washVegetables();
EXPECT_TRUE(veg.isReadyForCooking());

veg.addDefect("Bruise");
EXPECT_THROW(veg.isReadyForCooking(), QualityException);
}

// ==================== Класс Wool ====================
TEST(WoolTest, ConstructorAndBasicOperations) {
Wool wool(100.0, "Merino", "Fine");

EXPECT_EQ(wool.getSheepBreed(), "Merino");
EXPECT_EQ(wool.getWoolType(), "Fine");
EXPECT_EQ(wool.getFiberDiameter(), 18.0);
EXPECT_EQ(wool.getColor(), "Natural");
EXPECT_EQ(wool.getStapleLength(), 70);
EXPECT_EQ(wool.getProcessingStage(), "Raw");
EXPECT_EQ(wool.getLanolinContent(), 10.0);
EXPECT_TRUE(wool.getIsOrganic());
}

TEST(WoolTest, InvalidConstructorParameters) {
EXPECT_THROW(Wool(0, "Merino", "Fine"), ProductException);
EXPECT_THROW(Wool(-100.0, "Merino", "Fine"), ProductException);
EXPECT_THROW(Wool(2000.0, "Merino", "Fine"), ProductException);
EXPECT_THROW(Wool(100.0, "Horse", "Fine"), ProductException);
EXPECT_THROW(Wool(100.0, "Merino", "Extra Fine"), ProductException);
}

TEST(WoolTest, WoolProcessingOperations) {
Wool wool(100.0, "Merino", "Fine");

// Тест мойки
EXPECT_NO_THROW(wool.washWool());
EXPECT_EQ(wool.getProcessingStage(), "Washed");
EXPECT_LT(wool.getLanolinContent(), 10.0);
EXPECT_LT(wool.getQuantity(), 100.0);

// Тест кардования
EXPECT_NO_THROW(wool.cardWool());
EXPECT_EQ(wool.getProcessingStage(), "Carded");
EXPECT_EQ(wool.getSpinningQuality(), "Good");

// Тест прядения
wool.setStapleLength(80);
EXPECT_NO_THROW(wool.spinIntoYarn());
EXPECT_EQ(wool.getProcessingStage(), "Spun");

// Тест окрашивания
Wool whiteWool(50.0, "Shetland", "Medium");
EXPECT_NO_THROW(whiteWool.dyeWool("Blue"));
EXPECT_EQ(whiteWool.getColor(), "Blue");
EXPECT_FALSE(whiteWool.getIsOrganic());
}

TEST(WoolTest, WoolCalculationsAndGrading) {
Wool wool(100.0, "Merino", "Fine");

EXPECT_GT(wool.calculateWarmthRating(), 0.0);

EXPECT_NO_THROW(wool.gradeWool());

wool.setFiberDiameter(35.0);
wool.setStapleLength(40);
wool.setLanolinContent(25.0);
EXPECT_THROW(wool.isSuitableForClothing(), QualityException);

wool.setFiberDiameter(25.0);
wool.setStapleLength(80);
wool.setLanolinContent(15.0);
EXPECT_TRUE(wool.isSuitableForClothing());

EXPECT_NO_THROW(wool.processToStage("Washed"));
}

// ==================== Тесты исключений ====================
TEST(ExceptionTest, ProductExceptions) {
// Тест ProductException
try {
throw ProductException("Test message", "Test Product", "Egg", 100.0);
FAIL() << "Expected ProductException";
} catch (const ProductException& e) {
EXPECT_STREQ(e.what(), "Test message");
EXPECT_EQ(e.getProductName(), "Test Product");
EXPECT_EQ(e.getProductType(), "Egg");
EXPECT_EQ(e.getQuantity(), 100.0);
}
}

TEST(ExceptionTest, QualityException) {
try {
throw QualityException("Quality issue", "Apple", "Fruit", 50.0,
"B", "A", "Bruises", 25.0);
FAIL() << "Expected QualityException";
} catch (const QualityException& e) {
EXPECT_EQ(e.getActualGrade(), "B");
EXPECT_EQ(e.getExpectedGrade(), "A");
EXPECT_EQ(e.getIssueDescription(), "Bruises");
EXPECT_EQ(e.getDeviation(), 25.0);
}
}

TEST(ExceptionTest, StorageException) {
try {
throw StorageException("Storage issue", "Milk", "Dairy", 100.0,
"Refrigerated", "Room temp", 15.0, 30.0);
FAIL() << "Expected StorageException";
} catch (const StorageException& e) {
EXPECT_EQ(e.getRequiredConditions(), "Refrigerated");
EXPECT_EQ(e.getActualConditions(), "Room temp");
EXPECT_EQ(e.getTemperatureDeviation(), 15.0);
EXPECT_EQ(e.getHumidityDeviation(), 30.0);
}
}

TEST(ExceptionTest, PackagingException) {
try {
throw PackagingException("Packaging issue", "Eggs", "Poultry", 100.0,
"Carton", "Plastic", "pieces", "Not secure");
FAIL() << "Expected PackagingException";
} catch (const PackagingException& e) {
EXPECT_EQ(e.getRequiredPackaging(), "Carton");
EXPECT_EQ(e.getActualPackaging(), "Plastic");
EXPECT_EQ(e.getUnit(), "pieces");
EXPECT_EQ(e.getPackagingIssue(), "Not secure");
}
}

// ==================== Интеграционные тесты ====================
TEST(IntegrationTest, ProductPolymorphism) {
std::vector<std::unique_ptr<Product>> products;

products.push_back(std::make_unique<Egg>(100, "Large", "Brown"));
products.push_back(std::make_unique<FruitProduct>("Apples", 50.0, 2.0, "Apples"));
products.push_back(std::make_unique<GrainProduct>("Wheat", 1000.0, 0.5, "Wheat"));
products.push_back(std::make_unique<Meat>(50.0, "Beef", "Ribeye"));
products.push_back(std::make_unique<Milk>(100.0, 3.2, "Cow"));
products.push_back(std::make_unique<VegetableProduct>("Carrots", 50.0, 1.5, "Carrot"));
products.push_back(std::make_unique<Wool>(100.0, "Merino", "Fine"));

for (const auto& product : products) {
EXPECT_NO_THROW(product->displayInfo());
EXPECT_GT(product->calculateTotalValue(), 0.0);
EXPECT_NO_THROW(product->updateQuality());
EXPECT_NO_THROW(product->inspectQuality());
}
}

TEST(IntegrationTest, ProductDisplayChain) {
Egg egg(12, "Large", "Brown");
egg.setYolkColorGrade(12.0);
egg.setShellThickness(0.3);

// Проверяем, что displayInfo() вызывает базовый и производный методы
testing::internal::CaptureStdout();
egg.displayInfo();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("=== Product Information ===") != std::string::npos);
EXPECT_TRUE(output.find("=== Egg Details ===") != std::string::npos);
EXPECT_TRUE(output.find("Size: Large") != std::string::npos);
}

// ==================== Тесты граничных значений ====================
TEST(BoundaryTest, ExtremeValues) {
// Максимальные значения
EXPECT_NO_THROW(Product("Test", 1000000.0, 10000.0));
EXPECT_NO_THROW(Egg(10000, "X-Large", "White"));
EXPECT_NO_THROW(Meat(500.0, "Beef", "Steak"));
EXPECT_NO_THROW(Milk(1000.0, 10.0, "Cow"));

// Минимальные допустимые значения
EXPECT_NO_THROW(Product("Test", 0.1, 0.01));
EXPECT_NO_THROW(Egg(1, "Small", "Brown"));
EXPECT_NO_THROW(Meat(0.1, "Chicken", "Breast"));

// Граничные значения для сеттеров
Egg egg(100, "Large", "Brown");
EXPECT_NO_THROW(egg.setYolkColorGrade(1.0));
EXPECT_NO_THROW(egg.setYolkColorGrade(15.0));

Milk milk(100.0, 3.2, "Cow");
EXPECT_NO_THROW(milk.setFatContent(0.0));
EXPECT_NO_THROW(milk.setFatContent(10.0));
}

// ==================== Тесты ошибок времени выполнения ====================
TEST(RuntimeErrorTest, InvalidOperationsSequence) {
// Попытка нарезать немытые овощи
VegetableProduct veg("Carrots", 50.0, 1.5, "Carrot");
EXPECT_THROW(veg.cutVegetables(), ProductException);

// Попытка кардовать немытую шерсть
Wool wool(100.0, "Merino", "Fine");
EXPECT_THROW(wool.cardWool(), ProductException);

// Попытка обогатить непастеризованное молоко
Milk rawMilk(100.0, 3.2, "Cow");
rawMilk.setIsPasteurized(false);
EXPECT_THROW(rawMilk.fortify(), ProductException);

// Попытка замариновать выдержанное мясо
Meat agedMeat(50.0, "Beef", "Ribeye");
agedMeat.ageMeat(21);
EXPECT_THROW(agedMeat.marinate(), ProductException);
}

// ==================== Тесты сеттеров с валидацией ====================
TEST(SetterValidationTest, ParameterValidation) {
Egg egg(100, "Large", "Brown");

// Неправильный размер яйца
EXPECT_THROW(egg.setEggSize("Huge"), ProductException);

// Неправильный цвет скорлупы
EXPECT_THROW(egg.setShellColor("Blue"), ProductException);

// Неправильная оценка желтка
EXPECT_THROW(egg.setYolkColorGrade(20.0), ProductException);
EXPECT_THROW(egg.setYolkColorGrade(0.0), ProductException);

// Неправильная толщина скорлупы
EXPECT_THROW(egg.setShellThickness(-0.1), ProductException);
EXPECT_THROW(egg.setShellThickness(2.0), ProductException);

// Тесты для мяса
Meat meat(50.0, "Beef", "Ribeye");
EXPECT_THROW(meat.setAnimalType("Horse"), ProductException);
EXPECT_THROW(meat.setFatPercentage(-10.0), ProductException);
EXPECT_THROW(meat.setFatPercentage(110.0), ProductException);
EXPECT_THROW(meat.setGrade("Super"), ProductException);

// Тесты для молока
Milk milk(100.0, 3.2, "Cow");
EXPECT_THROW(milk.setFatContent(-1.0), ProductException);
EXPECT_THROW(milk.setFatContent(11.0), ProductException);
EXPECT_THROW(milk.setSourceAnimal("Horse"), ProductException);
EXPECT_THROW(milk.setPackagingType("Box"), ProductException);

// Тесты для шерсти
Wool wool(100.0, "Merino", "Fine");
EXPECT_THROW(wool.setSheepBreed("Horse"), ProductException);
EXPECT_THROW(wool.setWoolType("Super Fine"), ProductException);
EXPECT_THROW(wool.setFiberDiameter(-10.0), ProductException);
EXPECT_THROW(wool.setFiberDiameter(60.0), ProductException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    std::cout << "Running agricultural products tests..." << std::endl;
    std::cout << "=====================================" << std::endl;

    int result = RUN_ALL_TESTS();

    std::cout << "=====================================" << std::endl;
    std::cout << "Tests completed!" << std::endl;

    return result;
}