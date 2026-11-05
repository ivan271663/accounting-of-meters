#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Тарифы на коммунальные услуги
double Waterprice = 40.0;        // за 1 куб.м
double Electricityprice = 4.25;  // за 1 кВт·ч
double Heatingprice = 1200.0;    // за 1 Гкал

// Нормы потребления (при отсутствии счётчиков)
double Waternorm = 0.5;          //  куб. м на человека
double Electricitynorm = 150.0;  // кВт·ч на человека
double Heatingnorm = 0.035;      // Гкал на  кв. м площади

// Структура для хранения показаний счётчиков
struct MeterReadings {
    double Water = 0.0;        // вода, куб. м 
    double Electricity = 0.0;  // электроэнергия, кВт·ч
    double Heating = 0.0;      // отопление, Гкал
};

// Структура для хранения информации о квартире
struct Apartment {
    int Number = 0;            // номер квартиры
    double Area = 0.0;         // площадь, кв. м 
    int People = 0;            // количество проживающих
    MeterReadings meters;      // показания счётчиков
    bool Watermeter = false;   // наличие счётчика воды
    bool Electricitymeter = false; // наличие счётчика электроэнергии
    bool Heatingmeter = false; // наличие счётчика отопления
    bool Benefits = false;     // наличие льготы
    double Benefitpercent = 0.0; // процент льготы (0-1)
};

// Функция для ввода данных о квартире
void inputApartment(Apartment& apt) {
    cout << "Номер квартиры: ";
    cin >> apt.Number;
    cout << "Площадь (кв. м): ";
    cin >> apt.Area;
    cout << "Число проживающих: ";
    cin >> apt.People;

    // Ввод информации о наличии счётчиков и льгот
    cout << "Есть счётчик воды? (1/0): ";
    cin >> apt.Watermeter;
    cout << "Есть счётчик электричества? (1/0): ";
    cin >> apt.Electricitymeter;
    cout << "Есть счётчик отопления? (1/0): ";
    cin >> apt.Heatingmeter;
    cout << "Есть льгота? (1/0): ";
    cin >> apt.Benefits;

    // Ввод процента льготы
    if (apt.Benefits) {
        cout << "Размер льготы (0–100%): ";
        cin >> apt.Benefitpercent;
        apt.Benefitpercent /= 100.0; // преобразование процентов в дробь
    }

    // Ввод показаний 
    if (apt.Watermeter) {
        cout << "Показания воды (куб.м): ";
        cin >> apt.meters.Water;
    }
    if (apt.Electricitymeter) {
        cout << "Показания электричества (кВт·ч): ";
        cin >> apt.meters.Electricity;
    }
    if (apt.Heatingmeter) {
        cout << "Показания отопления (Гкал): ";
        cin >> apt.meters.Heating;
    }
}

// Функция для вывода результата расчёта 
void printResult(const Apartment& apt, double total) {
    cout << "\n  РАСЧЁТ КВАРТПЛАТЫ " << endl;
    cout << "Квартира №" << apt.Number << endl;
    cout << "Площадь: " << apt.Area << " кв. м" << endl;
    cout << "Проживающих: " << apt.People << endl;

    // Вывод информации о льготе
    if (apt.Benefits) {
        cout << "Льгота: " << (apt.Benefitpercent * 100) << "%" << endl;
    }
    else {
        cout << "Льгота: нет" << endl;
    }

    // Округление итоговой суммы
    double totalRounded = round(total * 100) / 100.0;
    cout << "Итого к оплате: " << totalRounded << " руб." << endl;
}

int main() {
    setlocale(LC_ALL, "Russian"); 

    vector<Apartment> building; // вектор для хранения квартир 
    int choice; // переменная для выбора пункта в меню

    // Осн. цикл программы
    do {
        cout << "  МЕНЮ УПРАВЛЕНИЯ ДОМОМ  " <<endl;
        cout << "1. Добавить квартиру "<< endl;
        cout << "2. Показать номера всех квартир "<< endl;
        cout << "3. Поиск по номеру и расчёт квартплаты "<<endl;
        cout << "4. Выход " << endl;;
        cout << "Выберите действие: " << endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            // Доб. новой квартиры
            Apartment apt;
            inputApartment(apt);
            building.push_back(apt);
            cout << "Квартира " << apt.Number << " добавлена.\n";
            break;
        }
        case 2: {
            // Вывод списка всех квартир
            if (building.empty()) {
                cout << " нет квартир.\n";
                break;
            }

            cout << "\n ВСЕ КВАРТИРЫ ДОМА \n";
            for (const auto& apt : building) {
                cout << "Квартира " << apt.Number << endl;
            }
            break;
        }
        case 3: {
            // Поиск квартиры по номеру и расчёт квартплаты
            int num;
            cout << "Введите номер квартиры: ";
            cin >> num;

            bool found = false; // переменная  для отслеживания найденной квартиры

            // Поиск квартиры
            for (const auto& apt : building) {
                if (apt.Number == num) {
                    found = true;

                    // Расчёт платы за воду
                    double waterCharge = 0.0;
                    if (apt.Watermeter) {
                        // По счётчику
                        waterCharge = apt.meters.Water * Waterprice;
                    }
                    else {
                        // По норме
                        waterCharge = apt.People * Waternorm * Waterprice;
                    }

                    // Расчёт платы за электричество
                    double electricityCharge = 0.0;
                    if (apt.Electricitymeter) {
                        // По счётчику
                        electricityCharge = apt.meters.Electricity * Electricityprice;
                    }
                    else {
                        // По норме
                        electricityCharge = apt.People * Electricitynorm * Electricityprice;
                    }

                    // Расчёт платы за отопление
                    double heatingCharge = 0.0;
                    if (apt.Heatingmeter) {
                        // По счётчику
                        heatingCharge = apt.meters.Heating * Heatingprice;
                    }
                    else {
                        // По норме
                        heatingCharge = apt.Area * Heatingnorm * Heatingprice;
                    }

                    // Общая сумма до применения льгот
                    double total = waterCharge + electricityCharge + heatingCharge;

                    // Применение льготы (если она есть)
                    if (apt.Benefits) {
                        total *= (1.0 - apt.Benefitpercent);
                    }

                    // Округление итоговой суммы
                    total = round(total * 100) / 100.0;

                    // Вывод результата
                    printResult(apt, total);
                    break;
                }
            }

            // вывод , если квартира не найдена
            if (!found) {
                cout << "Квартира не найдена.\n";
            }
            break;
        }
        case 4: {
            // Выход из программы

            break;
        }
        default: {
            // Обработка некорректного выбора
            cout << "Ошибка\n";
            break;
        }
        }
        
    } 
    while (choice != 4); // Программа работает пока не выбран пункт 4 

    return 0;
} 