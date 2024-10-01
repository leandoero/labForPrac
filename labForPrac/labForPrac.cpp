#include "user.h";

#include <fstream>
#include <iostream>
#include "node.h"
#include "task.h"

ifstream inFileAdress("adress.txt"), inFileBalance("balance.txt"), inFileFio("fio.txt"), inFileNumbers("number.txt");
vector<string> fioFromAFile, adressFromAFile, balanceFromAFile, numbersFromAFile;

User::User() {
	FIO = funcForConstructor(fioFromAFile, FIO);
	adress = funcForConstructor(adressFromAFile, adress);
	balanceForPhone = funcForConstructor(balanceFromAFile, balanceForPhone);
	int indexForMas = (rand() % 3) + 1;
	for (int i = 0; i < indexForMas; i++)
	{
		int index = rand() % numbersFromAFile.size();
		numberPhone[i] = numbersFromAFile[index];
		if (index < numbersFromAFile.size()) {
			numbersFromAFile.erase(numbersFromAFile.begin() + index);
		}
	}
}

void User::PrintInfo()
{
	cout << "Информация по пользователю :\n" <<
		"ФИО : " << FIO << "\n" <<
		"Адрес : " << adress << "\n" <<
		"Баланс пользователя : " << balanceForPhone << "\n";
	for (int i = 0; i < sizeof(numberPhone) / sizeof(numberPhone[0]); i++)
	{
		if (numberPhone[i] != "") {
			cout << "Номера пользователя : " << numberPhone[i] << endl;
		}

	}
	cout << endl;

}

template<typename T>
string User::funcForConstructor(vector<T>& vec, T peremen) {
	unsigned short index = rand() % vec.size();
	peremen = vec[index];
	if (index < vec.size()) {
		vec.erase(vec.begin() + index);
	}
	return peremen;
}

void InitList(Node* node, User user) {
	node->user = user;
	node->prev = nullptr;
	node->next = nullptr;
}

void AddUser(Node*& head, User user) {
	if (head == nullptr) {
		 
		head = new Node;
		InitList(head, user);
		return;
	}
	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	Node* LastEl = new Node;
	LastEl->user = user;
	LastEl->next = nullptr;
	LastEl->prev = temp;
	temp->next = LastEl;
}


void addElBegin(Node*& head, User user) {
	Node* beginEl = new Node;
	beginEl->user = user;
	beginEl->next = head;
	beginEl->prev = nullptr;
	if (head)
	{
		head->prev = beginEl;
	}
	head = beginEl;
}

void removeLastEl(Node*& head) {
	if (head == nullptr) {
		cout << "Список пустой" << endl;
		return;
	}

	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	// Если список состоит из одного элемента
	if (temp->prev == nullptr)
	{
		removeHead(head);
		return;
	}
	temp->prev->next = nullptr;
	delete temp;
	temp = nullptr;
}

void removeHead(Node*& head) {
	if (head == nullptr) {
		cout << "Список пустой" << endl;
		return;
	}
	
	Node* list = head;
	head = head->next;
	delete list;
	list = nullptr;
	if (head)
	{
		head->prev = nullptr;
	}	
}


void removeList(Node*& head) {
	if (head == nullptr) {
		cout << "Список пустой" << endl;
		return;
	}
	while (head != nullptr) {
		removeHead(head);
	}
	
}

bool emptyList(Node* list) {
	if (list == nullptr) {
		return true;
	}
	else return false;
}

void printList(Node* head) {
	if (head == nullptr) {
		cout << "Список пустой!" << endl;
		return;
	}
	Node* temp = head;
	while (temp != nullptr) {

		temp->user.PrintInfo();
		temp = temp->next;
	}

}

void sortBySurname(Node* head) {
	if (!head) return; // Пустой список

	bool swapped;
	do {
		swapped = false;
		Node* current = head;

		while (current->next) {
			if (current->user.FIO > current->next->user.FIO) {
				// Меняем местами данные пользователей
				std::swap(current->user, current->next->user);
				swapped = true; // Установим флаг, что произошла замена
			}
			current = current->next; // Переходим к следующему элементу
		}
	} while (swapped); // Повторяем, пока есть замены
}

void sortByBalance(Node* head) {
	if (!head) return;

	bool swapped;
	do {
		swapped = false;
		Node* temp = head;

		while (temp->next) {
			if (stoi(temp->user.balanceForPhone) > stoi(temp->next->user.balanceForPhone)) {
				std::swap(temp->user, temp->next->user);
				swapped = true;
			}
			temp = temp->next;
		}
	} while (swapped);
}

void removeNegativeBalance(Node*& head)
{
	if (head == nullptr) return;

	sortBySurname(head);
	Node* ptr = head;
	while (ptr != nullptr)
	{
		if (stoi(ptr->user.balanceForPhone) < 0)
		{
			// Если голова - отрицательный элемент
			if (ptr->prev == nullptr)
			{
				removeHead(ptr);
			}
			// Если последний элемент отрицательный
			if (ptr->next == nullptr)
			{
				removeLastEl(ptr);
				return;
			}

			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			Node* nextNode = ptr->next;
			delete ptr;
			ptr = nextNode;
		}
		else
		{
			ptr = ptr->next;
		}
		
	}
}

void usersWithMoreNumbers(Node* head) {

	Node* temp = head;
	sortBySurname(temp);

	while (temp != nullptr) {
		int count = 0;
		for (size_t i = 0; i < 3; i++)
		{
			if (temp->user.numberPhone[i] != "") {
				++count;
			}
		}
		if (count > 1) {
			temp->user.PrintInfo();
		}
		temp = temp->next;
	}
}

void balanceLessSpecified(Node* head, int balance) {
	sortByBalance(head);
	Node* temp = head;
	while (temp) {
		if (stoi(temp->user.balanceForPhone) < balance) {
			temp->user.PrintInfo();
		}
		temp = temp->next;
	}
}

void usersWithSameCompany(Node* head) {
	sortBySurname(head);
	Node* temp = head;
	while (temp) {
		vector<string>mas(3);
		vector<int>masForInt(3, 0);
		for (size_t i = 0; i < 3; i++)
		{
			if (temp->user.numberPhone[i] != "") {
				mas[i] = temp->user.numberPhone[i];
				int num = stoi(mas[i].substr(1, 3));
				masForInt[i] = num;
			}
		}
		int count = 0;
		for (size_t i = 0; i < masForInt.size(); i++)
		{
			if (masForInt[i] > 0) {
				++count;
			}
		}
		if (count > 1) {
			if ((masForInt[0] == masForInt[1]) != 0 || (masForInt[1] == masForInt[2]) != 0 || (masForInt[0] == masForInt[2]) != 0) {
				temp->user.PrintInfo();
			}
		}
		temp = temp->next;
	}

}

string networkWithLargeNumberUsers(Node* head) {
	Node* temp = head;
	vector<string>tel;
	string num;
	int ans = -1;
	int count = 0;
	while (temp) {
		for (size_t i = 0; i < 3; i++)
		{
			if (temp->user.numberPhone[i] != "") {
				string str = temp->user.numberPhone[i];
				str = str.substr(1, 3);
				tel.push_back(str);
			}
		}
		temp = temp->next;
	}

	for (size_t i = 0; i < tel.size(); i++)
	{
		for (size_t j = 0; j < tel.size(); j++) {
			if (tel[i] == tel[j] && (i != j)) {
				++count;
			}
		}
		if (count > ans) {
			ans = count;
			num = tel[i];
		}
		count = 0;
	}
	return num;
}

void caseFirst(Node*& list) {
	int choice = 0;


	cout << "1. Добавление в начало\n" <<
		"2. Добавление в конец\n" <<
		"3. Удаление всего списка\n" <<
		"4. Удаление головы\n" <<
		"5. Удаление последнего элемента\n" <<
		"6. Вернуться в меню\n" << endl;
	while (true) {
		cout << "Ввод : ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			break;
		}
	}
	switch (choice) {
	case 1: {

		User user;
		addElBegin(list, user);
		cout << "Элемент добавлен!" << endl;
		system("pause");
		break;
	}
	case 2: {

		User user;
		AddUser(list, user);
		cout << "Элемент добавлен!" << endl;
		system("pause");
		break;
	}
	case 3: {

		removeList(list);
		cout << "Список удален!" << endl;
		system("pause");
		break;
	}
	case 4: {

		removeHead(list);
		cout << "Голова списка удалена!" << endl;
		system("pause");
		break;
	}
	case 5: {

		removeLastEl(list);
		cout << "Список удален!" << endl;
		system("pause");
		break;
	}
	case 6: {

		start(list);
		break;
	}
	}

}

void caseFourth(Node*& list) {
	int choice = 0;

	cout << "1. Удалить всех абонентов, имеющих отрицательный баланс\n" <<
		"2. Напечатайте информацию об абонентах, имеющих два и более телефонных номера\n" <<
		"3. Найти телефонную сеть, имеющую наибольшее количество абонентов\n" <<
		"4. Напечатайте информацию об абонентах, имеющих баланс, меньше заданного\n" <<
		"5. Напечатайте информацию об абонентах, имеющих два и более телефонных номера одной и той же сотовой компании\n" <<
		"6. Вернуться в меню\n" << endl;
	while (true) {
		cout << "Ввод : ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			break;
		}
	}
	switch (choice) {
	case 1: {
		system("cls");
		removeNegativeBalance(list);
		cout << "Абоненты с отрицательным балансом удалены! " << endl;
		system("pause");
		break;
	}
	case 2: {
		system("cls");
		usersWithMoreNumbers(list);
		system("pause");
		break;
	}
	case 3: {
		system("cls");
		cout << networkWithLargeNumberUsers(list) << endl;
		system("pause");
		break;
	}
	case 4: {
		system("cls");
		cout << "Введите значения баланса : ";
		int balance = 0;
		cin >> balance;
		balanceLessSpecified(list, balance);
		system("pause");
		break;
	}
	case 5: {
		system("cls");
		usersWithSameCompany(list);
		system("pause");
		break;
	}
	case 6: {

		break;
	}
	}
}

void start(Node* list) {
	unsigned int choiceForSwitch = 0;
	do {
		system("cls");

		cout << "Выберите операцию:\n\n" <<
			"1. Добавления и удаления\n" <<
			"2. Вывод на экран\n" <<
			"3. Проверка на пустоту\n" <<
			"4. Индивидуальные функции\n" <<
			"5. Выйти из программы\n" << endl;
		while (true) {
			cout << "Ввод : ";
			cin >> choiceForSwitch;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else {
				break;
			}
		}
		switch (choiceForSwitch) {
		case 1: {
			system("cls");
			caseFirst(list);
			break;
		}
		case 2: {
			system("cls");
			printList(list);
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			if (emptyList(list) == 1) {
				cout << "Список пустой" << endl;
			}
			else {
				cout << "Список не пустой" << endl;
			}
			system("pause");
			break;
		}
		case 4: {
			system("cls");
			caseFourth(list);
			break;

		}
		case 5: {
			system("cls");
			break;
		}
		}

	} while (choiceForSwitch != 5);
}


void openingAndFillingFiles() {
	if (!inFileAdress || !inFileBalance || !inFileFio || !inFileNumbers) {
		cout << "Проблема открытия файлов...";
	}
	string line;
	while (getline(inFileFio, line)) {
		fioFromAFile.push_back(line);
	}
	while (getline(inFileAdress, line)) {
		adressFromAFile.push_back(line);
	}
	while (getline(inFileBalance, line)) {
		balanceFromAFile.push_back(line);
	}
	while (getline(inFileNumbers, line)) {
		numbersFromAFile.push_back(line);
	}
}

void program() {
	std::srand(std::time(0));

	openingAndFillingFiles();

	string input;
	do {
		cout << "Создать список? y/n  :  ";
		cin >> input;
	} while (input != "Y" && input != "N" && input != "y" && input != "n");

	if (input == "y" || input == "Y") {
		Node* list = new Node;
		User user;
		InitList(list, user);
		start(list);
	}
	else if (input == "n" || input == "N") {
		cout << "Выход...";
	}
}

