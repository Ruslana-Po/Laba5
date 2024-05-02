#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <random>
using namespace std;
//структура
struct visitor {
    //компаненты структуры
    string ticket;
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int number;
    cout << "Введите кол-во окон\n";
    cin >> number;
    //queue адаптирует контейнер для предоставления очереди
    vector<queue<visitor>> windows(number);
    vector<int> Time(number,0);
    string command;
    //рандом для номера билета
    random_device ran;
    uniform_int_distribution<> dist(1, 1000);
    while (true) {
        cout << "Введите команду (ENQUEUE/DISTRIBUTE) и время: ";
        cin >> command;
        //Если продолжается ввод посетителей
        if (command == "ENQUEUE") {
            //вводим время посещения
            int time;
            cin >> time;
            //помещаем время и талон
            visitor person = { "T" + to_string(dist(ran)) };
            int minKol = 0;
            for (int i = 1; i < number; ++i) {
                //Распределяем в самое незанятое окно
                if (Time[i] < Time[minKol]) {
                    minKol = i;
                }
            }
            //Функция push() используется для вставки или «проталкивания» элемента наверх стека
            windows[minKol].push(person);
            Time[minKol] += time;
            cout << "Ваш талон: " << person.ticket << endl;
        }
        //Если заканчиваем 
        else if (command == "DISTRIBUTE") {
            for (int i = 0; i < number; ++i) {
                //front возвращает ссылку на первый элемент в контейнере
                cout << "Окно " << i + 1 << " ( "<<Time[i]<<" минут) : ";
                int generalTime = 0;
                //если контейнер не пуст empty() вернет false
                while (!windows[i].empty()) {
                    cout << windows[i].front().ticket;
                    //удаляем вверхний элемент
                    windows[i].pop();
                    if (!windows[i].empty()) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
            break;
        }
    }
}
