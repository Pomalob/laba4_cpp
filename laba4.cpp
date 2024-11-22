/* Задание 1
    Класс - Time
    Поля - byte hours, byte minutes
    Методы - Добавление произвольного количества
             минут (unsigned int) к объекту типа Time.
             Результат должен быть типа Time



   Задание 2 
    Добавить к реализованному в первом задании классу указанные в варианте
    перегруженные операции
    Операции - Унарные операции:
                ++ добавление минуты к объекту типа Time
                -- вычитание минуты из объекта типа Time
               Операции приведения типа:
                short int (явная) – результатом является количество часов (минуты
                отбрасываются);
                bool (неявная) – результатом является true, если часы и минуты не равны
                нулю, и falseв противном случае.
               Бинарные операции:
                + Time t, беззнаковое целое число (минуты). Результат должен быть типа
                Time.
                – Time t, беззнаковое целое число (минуты). Результат должен быть типа
                Time    
*/

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class Time
{
private:
    unsigned int hours;
    unsigned int minutes;

public:
    Time() : hours(0), minutes(0) {}

    Time(unsigned int hours, unsigned int minutes)
    {
        if (minutes > 59 || hours > 23) 
        {
            throw std::out_of_range("Wrong time!");
        }
        this->hours = hours;
        this->minutes = minutes;
    }

    unsigned int GetHours() const
    {
        return hours;
    }

    unsigned int GetMinutes() const
    {
        return minutes;       
    }

    void AddMinutes(unsigned int new_min)
    {
        minutes += new_min;
        hours += minutes / 60;  // добавляем часы
        minutes = minutes % 60; // оставляем минуты в пределах 0-59

        // Приводим часы к формату 24
        hours = hours % 24;
    }

    // Унарный оператор ++ (добавить 1 минуту)
    Time& operator++()
    {
        minutes++;
        if (minutes == 60) {
            minutes = 0;
            hours++;
            if (hours == 24) {
                hours = 0;
            }
        }
        return *this;
    }

    // Унарный оператор -- (вычесть 1 минуту)
    Time& operator--()
    {
        if (minutes == 0) {
            minutes = 59;
            if (hours == 0) {
                hours = 23;
            } else {
                hours--;
            }
        } else {
            minutes--;
        }
        return *this;
    }

    // Приведение типа Time к short int (количество полных часов)
    operator short int() const
    {
        return static_cast<short int>(hours);
    }

    // Приведение типа Time к bool (если время не 00:00)
    operator bool() const
    {
        return hours != 0 || minutes != 0;
    }

     // Бинарный оператор + (прибавить минуты)
    Time operator+(unsigned int min) const
    {
        unsigned int total_minutes = hours * 60 + minutes + min; 
        Time new_time(total_minutes / 60 % 24, total_minutes % 60);

        return new_time;
    }

    // Бинарный оператор - (вычесть минуты)
    Time operator-(unsigned int min) const
    {
        int total_minutes = hours * 60 + minutes - min;
        if (total_minutes < 0) {
            total_minutes = 0;
        }

        Time new_time(total_minutes / 60 % 24, total_minutes % 60); 

        return new_time;
    }

    void PrintTime() const
    {
        cout << hours << " : " << minutes << "\n";
    }
};

int main()
{
    // Задание 1
    cout << "Task 1\n";
    unsigned int hours, minutes, new_min;
    cout << "Write time\n";
    cout << "Hours: ";
    cin >> hours;
    cout << "Minuts: ";
    cin >> minutes;
    Time t1(hours, minutes);  
    t1.PrintTime();
    cout << "Write added minuts: ";
    cin >> new_min;
    t1.AddMinutes(new_min);    
    t1.PrintTime();
    
    // Задание 2
    cout << "\nTask 2\n";

    // Унарные операции
    int operation;
    cout << "Which operation to apply (1 - increase, 2 - decrease): ";
    cin >> operation;
    if (operation == 1) {
        ++t1;  
        cout << "After increase: ";
        t1.PrintTime();
        cout << "\n";
    } else if (operation == 2) {
        --t1;
        cout << "After decrease: ";
        t1.PrintTime();
        cout << "\n";
    }

    // Операции приведения типа
    short int hours_only = static_cast<short int>(t1);
    cout << "Number of hours: " << hours_only << "\n";
    
    bool is_non_zero = static_cast<bool>(t1);
    cout << "Time not 00:00? " << (is_non_zero ? "Yes" : "No") << "\n";

    // Бинарные операции
    unsigned int add_minutes;
    cout << "\nEnter the number of minutes to be added: ";
    cin >> add_minutes;
    Time t2 = t1 + add_minutes;
    cout << "Time after added: ";
    t2.PrintTime();

    unsigned int sub_minutes;
    cout << "\nEnter the number of minutes to subtract: ";
    cin >> sub_minutes;
    Time t3 = t2 - sub_minutes;
    cout << "Time after subtract: ";
    t3.PrintTime();
    return 0;
}
