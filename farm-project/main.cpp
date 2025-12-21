#include <iostream>
#include "farm/Farm.h"
#include "animals/Cow.h"
#include "animals/Chicken.h"
#include "animals/Sheep.h"
#include "plants/Wheat.h"
#include "employees/Farmer.h"
#include "feed/Hay.h"
#include "equipment/Tractor.h"
#include "buildings/Barn.h"
#include "fields/Field.h"
#include "products/Milk.h"
#include "products/Egg.h"
#include "seasons/Spring.h"

int main() {
    std::cout << "=== Фермерское хозяйство ===\n" << std::endl;

    try {
        // 1. СОЗДАЕМ ФЕРМУ
        Farm myFarm("Солнечная долина", "Краснодарский край", 100.0, 2010);
        std::cout << "Создана ферма: " << myFarm.getName() << std::endl;

        // 2. СОЗДАЕМ ЖИВОТНЫХ
        Cow* cow1 = new Cow("Буренка", 36, 550.0, "Голштинская");
        Cow* cow2 = new Cow("Зорька", 24, 500.0, "Ярославская");
        Chicken* chicken1 = new Chicken("Ряба", 12, 2.5, "Белая");
        Chicken* chicken2 = new Chicken("Пеструшка", 8, 2.2, "Рыжая");
        Sheep* sheep1 = new Sheep("Барашек", 24, 60.0, "Меринос");

        // 3. ДОБАВЛЯЕМ ЖИВОТНЫХ НА ФЕРМУ
        myFarm.addAnimal(cow1);
        myFarm.addAnimal(cow2);
        myFarm.addAnimal(chicken1);
        myFarm.addAnimal(chicken2);
        myFarm.addAnimal(sheep1);

        // 4. СОЗДАЕМ РАСТЕНИЯ
        Wheat* wheat1 = new Wheat("Озимая пшеница", 50.0, "Озимая");
        Wheat* wheat2 = new Wheat("Яровая пшеница", 30.0, "Яровая");

        // 5. СОЗДАЕМ ПОЛЕ И САЖАЕМ РАСТЕНИЯ
        Field* field1 = new Field("Большое поле", 50.0, "Пшеничное");
        myFarm.addField(field1);
        myFarm.plantCropInField(wheat1, field1);

        // 6. СОЗДАЕМ СОТРУДНИКОВ
        Farmer* farmer1 = new Farmer("Иван Петров", 35, 50000.0, 10);
        myFarm.hireEmployee(farmer1);

        // 7. СОЗДАЕМ ОБОРУДОВАНИЕ
        Tractor* tractor1 = new Tractor("John Deere 6250R", "JD12345", 250);
        myFarm.addEquipment(tractor1);
        myFarm.assignEquipmentToWorker(tractor1, farmer1);

        // 8. СОЗДАЕМ ПОСТРОЙКИ
        Barn* barn1 = new Barn("Основной сарай", 200.0, "Деревянный");
        myFarm.addBuilding(barn1);
        myFarm.setMainBarn(barn1);

        // 9. СОЗДАЕМ КОРМ
        Hay* hay1 = new Hay("Луговое сено", 1000.0, 10.0, "Тимофеевка", 2023);

        // 10. СОЗДАЕМ ПРОДУКЦИЮ
        Milk* milk1 = new Milk("Свежее молоко", 50.0, "Высший сорт");
        Egg* egg1 = new Egg("Деревенские яйца", 100, "Коричневые");

        // 11. СОЗДАЕМ СЕЗОН
        Spring* spring = new Spring("Весна 2024", 15.0, 60.0);

        // 12. СИМУЛЯЦИЯ РАБОТЫ ФЕРМЫ
        std::cout << "\n=== Начало симуляции ===" << std::endl;

        // День 1
        myFarm.startNewDay();
        cow1->startMilking();
        double milkAmount = cow1->milk();
        milk1->addQuantity(milkAmount);

        chicken1->startLaying();
        int eggs = chicken1->layEggs();
        egg1->addQuantity(eggs);

        // День 2
        myFarm.startNewDay();
        tractor1->plowField(10.0);

        // День 3
        myFarm.startNewDay();
        sheep1->shear();

        // 13. ВЫВОД ОТЧЕТА
        std::cout << "\n=== Итоговый отчет ===" << std::endl;
        std::cout << "Ферма: " << myFarm.getName() << std::endl;
        std::cout << "Животных: " << myFarm.getAnimalCount() << std::endl;
        std::cout << "Сотрудников: " << myFarm.getEmployeeCount() << std::endl;
        std::cout << "Оборудования: " << myFarm.getEquipmentCount() << std::endl;
        std::cout << "Молока собрано: " << milk1->getQuantity() << " л" << std::endl;
        std::cout << "Яиц собрано: " << egg1->getQuantity() << " шт" << std::endl;

        // 14. ПРОВЕРКА РАЗНЫХ ПОВЕДЕНИЙ
        std::cout << "\n=== Проверка различных поведений ===" << std::endl;

        // Проверка пароля (имитация)
        std::string enteredPassword = "farm123";
        bool isPasswordCorrect = (enteredPassword == "farm123");
        std::cout << "Проверка пароля: " << (isPasswordCorrect ? "верно" : "неверно") << std::endl;

        // Перевод корма (имитация)
        double feedToTransfer = 100.0;
        std::cout << "Переведено корма: " << feedToTransfer << " кг" << std::endl;

        // Расчет стоимости
        double cowPrice = cow1->calculatePrice();
        std::cout << "Стоимость коровы " << cow1->getName() << ": " << cowPrice << " руб" << std::endl;

        // Проверка здоровья
        if (cow1->needsVet()) {
            std::cout << cow1->getName() << " нуждается в ветеринаре!" << std::endl;
        } else {
            std::cout << cow1->getName() << " здорова" << std::endl;
        }

        // Производство продуктов из молока
        double cheese = cow1->produceCheese(milkAmount);
        double yogurt = cow1->produceYogurt(milkAmount);
        double butter = cow1->produceButter(milkAmount);

        std::cout << "\nИз " << milkAmount << " л молока произведено:" << std::endl;
        std::cout << "Сыр: " << cheese << " кг" << std::endl;
        std::cout << "Йогурт: " << yogurt << " л" << std::endl;
        std::cout << "Масло: " << butter << " кг" << std::endl;

        // 15. ОЧИСТКА ПАМЯТИ
        delete cow1;
        delete cow2;
        delete chicken1;
        delete chicken2;
        delete sheep1;
        delete wheat1;
        delete wheat2;
        delete field1;
        delete farmer1;
        delete tractor1;
        delete barn1;
        delete hay1;
        delete milk1;
        delete egg1;
        delete spring;

        std::cout << "\n=== Симуляция завершена успешно! ===" << std::endl;

    } catch (const AnimalNotFound& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    } catch (const NotEnoughFood& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cout << "Неизвестная ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}