#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
using namespace std;
int main() {
	//Вектор студентов
	vector<string> student{ "Мокрушин","Потапова","Юдина","Полевой","Тарасенко" };
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string command;
	//на отчисление
	vector<string> deduction;
	//неприкас
	vector<string> inviolable;
	while (true) {
		cout << "Введите команду (NEW_STUDENTS/SUSPICIOUS/IMMORTAL/TOP-LIST/SCOUNT): ";
		cin >> command;
		int number, numberStudent;
		//добавление или удаленние студентов
		if (command=="NEW_STUDENTS") {
			cin >> number;
			//добавление
			if (number > 0) {
				for (int i = 0; i < number; i++) {
					string s;
					cout << "Введите фамилию: ";
					cin >> s;
					student.push_back(s);
				}
				cout << "Welcome " << number << " clever students!" << endl;
			}
			//удаленние
			else if (number < 0) {
				//если просят удалить больше чем есть
				if (abs(number) > student.size()) {
					cout << "Incorrect" << endl;
				}
				else {
					for (int i = 0; i > number; i--) {
						student.pop_back();
					}
					cout << "GoodBye " << abs(number) << " clever students!" << endl;
				}
			}
			//добавление в лист на отчисленние
		}else if (command == "SUSPICIOUS") {
			cin >> numberStudent;
			//Проверка  что не введенно отрицательное число и что не больше кол-ва
			if (numberStudent > 0 && numberStudent <= student.size()) {
				int k = 0;
				//проверка нет ли его в списке неприкосновенных
				if (inviolable.size() > 0) {
					for (int i = 0; i < inviolable.size(); i++) {
						if (inviolable[i] == student[numberStudent - 1]) {
							k++;
							break;
						}
					}
				}
				if (k == 0) {
					deduction.push_back(student[numberStudent - 1]);
					cout << "The suspected student " << numberStudent << endl;
				}else {
					cout << "Неприкасаемый " << endl;
				}
				
			}
			//удаленние из списка или просто что этого студента нельзя отчислить
		}else if (command == "IMMORTAL") {
			cin >> numberStudent;
			//Проверка  что не введенно отрицательное число и что не больше кол-ва
			if (numberStudent > 0 && numberStudent <= student.size()) {
				//если есть в списке на отчисленние удаляем
				if (deduction.size() > 0) {
					for (int i = 0; i < deduction.size(); i++) {
						if (deduction[i] == student[numberStudent - 1]) {
							deduction.erase(deduction.begin() + i);
							break;
						}
					}
				}
				inviolable.push_back(student[numberStudent - 1]);
				cout << "Student "<< numberStudent<< " is immortal!" << endl;
			}
			//вывод отсортированного списка, по фамилиям и рядом его порядковый номер
		}else if (command == "TOP-LIST") {
			cout << "List of students for expulsion: " << endl;
			sort(begin(deduction), end(deduction));
			int k = 1;
			for (string i : deduction) {
				for (int j = 0; j < student.size(); j++) {
					if (i==student[j]) {
						cout << "Student " << k << " : " << i <<" "<< j+1 << endl;
						k++;
						break;
					}
				}
				
			}
			//кол-во человек на отчисление
		}else if (command == "SCOUNT") {
			cout << "List of students for expulsion consists of " << deduction.size() << " students" << endl;
		}
	}
}
