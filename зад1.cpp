#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <map>
using namespace std;

int examination(map<string, vector<string>> product, string number, string s) {
	int k=0;
	for (pair<string, vector<string>> i : product) {
		if (i.first == number) {
			for (string j : i.second) {
				if (j == s) {
					k++;
				}
			}
		}
	}
	return k;
}

void out(map<string, vector<string>> product, string number) {
	for (pair<string, vector<string>> i : product) {
		if (i.first == number) {
			cout << i.first << " : ";
			for (string j : i.second) {
				cout << j << " ";
			}
			cout << endl;
		}
	}
	
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	map<string,vector<string>> product;
	for (int i = 0; i < 2; i++) {
		string zone;
		if (i == 0) {
			zone = "A";
		}
		else if (i == 1) {
			zone = "B";
		}
		for (int j = 0; j < 19; j++) {
			string rack = to_string(j + 1);
			if (j < 9) {
				rack = '0' + rack;
			}
			
			for (int z = 0; z < 4; z++) {
				string sections = to_string(z + 1);
				for (int y = 0; y < 8; y++) {
					string shelves = to_string(y + 1);
					string all = zone + rack + sections + shelves;
					for (int w = 0; w < 10; w++) {
						product[all].push_back("0");
					}
				}
			}
		}
	}
	string command;
	while (true) {
		cout << "Введите команду (ADD/REMOVE/INFO): ";
		cin >> command;
		string merchandise, number;
		int kol;
		if (command == "ADD") {
			cout << "Введите товар: ";
			cin >> merchandise;
			cout << "Введите кол-во: ";
			cin >> kol;
			cout << "Введите адрес: ";
			cin >> number;
			//Есть место?
			int there = examination(product, number,"0");
			//Если место есть, то добавляем
			if (kol <= 10 && kol <= there) {
				int k = 0;
				//Заполняем первые пустые ячейки
				for (int w = 0; w < 10; w++) {
					if (product[number][w] == "0" && k < kol) {
						product[number][w] = merchandise;
						k++;
					}
				}
			}else {
				cout << "Недостаточно места" << endl;
			}
		}else if (command == "REMOVE") {
			cout << "Введите товар: ";
			cin >> merchandise;
			cout << "Введите кол-во: ";
			cin >> kol;
			cout << "Введите адрес: ";
			cin >> number;
			//Есть столько товара?
			int there = examination(product, number, merchandise);
			if (kol <= 10 && kol <= there) {
				int k = 0;
				//Удаляем с конца
				for (int w = 9; w >= 0; w--) {
					if (product[number][w] == merchandise && k<kol) {
						product[number][w] = "0";
						k++;
					}
				}
			}else {
				cout << "Недостаточно товара" << endl;
			}
		}else if (command == "INFO") {
			vector<string> noEmpty;
			vector<string> empty;
			int kolNull = 0;
			int nullA = 0;
			int nullB = 0;
			for (pair<string, vector<string>> i : product) {
				int there = examination(product, i.first, "0");
				kolNull += there;
				if (!i.first.find('A')) {
					nullA += there;
				}else {
					nullB+= there;
				}
				if (there < 10) {
					noEmpty.push_back(i.first);
				}
				else{
					empty.push_back(i.first);
				}
			}
			cout << " Cодержание каждой ячейки: " << endl;
			for (int i = 0; i < noEmpty.size(); i++){
				out(product, noEmpty[i]);
			}
			cout << " Склад загружен на " << float(float(12160 -kolNull)/ 12160)*100 << " %" << endl;
			cout<<" Зона А загруженна на "<< float(float(6080 - nullA) / 6080) * 100 << " %" << endl;
			cout << " Зона B загруженна на " << float(float(6080 - nullB) / 6080) * 100 << " %" << endl;
			cout << " Пустые ячейки: " << endl;
			for (string i : empty) {
				cout << i << " ";
			}
			cout << endl;
		}
	}
}
