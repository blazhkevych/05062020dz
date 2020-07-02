
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;
#define MENUTOP 0 
#define MENULEFT 0 
#define BACKGROUND 0                     
#define FOREGROUND 10                         
#define SELECTITEM 13
void gotorc(short r, short c) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { c,r });
}
void Color(unsigned short Back, unsigned short Forg) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short c = ((Back & 0x0F) << 4) + (Forg & 0x0F);
	SetConsoleTextAttribute(handle, c);
}
void paintmenu(const char** s, int sizem, int  pm, int left, int top) {
	system("cls");
	gotorc(top, left);
	Color(BACKGROUND, FOREGROUND);
	//cout << "";
	for (int i = 0; i < sizem; i++)
	{
		gotorc(top + i + 1, left);
		cout << (i == pm ? Color(BACKGROUND, SELECTITEM), "=>" : "  ");
		cout << s[i] << endl;
		Color(BACKGROUND, FOREGROUND);
	}
}
int menu(const char** s, int sizem, int  pm = 0, int left = MENULEFT, int top = MENUTOP) {
	char c = 80;
	while (true)
	{
		if (c == 72 || c == 80) paintmenu(s, sizem, pm, left, top);
		c = _getch();
		switch (c)
		{
		case 27: //код кнопки "esc" 27
			return -1;
		case 80: //down
			pm++;
			if (pm == sizem) pm = 0;
			break;
		case 72: //up
			if (pm == 0) pm = sizem;
			pm--;
			break;
		case 13: //enter
			return pm;
		}
	}
}
//******************************************************************************************************
/*
Создайте приложение "Телефонная книга".
Необходимо хранить данные об абоненте
(ФИО, домашний телефон, рабочий телефон, мобильный телефон, дополнительная информация о контакте)
внутри соответствующего класса.
Наполните класс переменными-членами, функциями-членами, конструкторами, inline-функциями-членами,
используйте инициализаторы, реализуйте деструктор.
Обязательно необходимо выделять динамически память под ФИО.
Предоставьте пользователю возможность добавлять новых абонентов, //
удалять абонентов,
искать абонентов по ФИО,
показывать всех абонентов,
сохранять информацию в файл
и загружать из файла.
*/
class Subscriber {
private:
	char* m_fio;
	char* m_home_phone;
	char* m_work_phone;
	char* m_mobile_phone;
	char* m_addit_cont_inf;
public:
	// КОНСТРУКТОРЫ
	//Конструктор с параметрами
	Subscriber(const char* f, const char* hp, const char* wp, const char* mf, const char* aci);
	//Конструктор без параметров
	Subscriber();
	// Деструктор
	~Subscriber();
	// Метод вывода на экран
	inline void Print();
	//ГЕТТЕРЫ
	inline const char* GetFio() { return m_fio; }
	inline const char* GetHome_phone() { return m_home_phone; }
	inline const char* GetWork_phone() { return m_work_phone; }
	inline const char* GetMobile_phone() { return m_mobile_phone; }
	inline const char* GetAddit_cont_inf() { return m_addit_cont_inf; }

};
Subscriber::Subscriber(const char* f, const char* hp, const char* wp, const char* mf, const char* aci) /*:
	m_fio(_strdup(f)), m_home_phone(_strdup(hp)), m_work_phone(_strdup(wp)), m_mobile_phone(_strdup(mf)),
	m_addit_cont_inf(_strdup(aci))*/ {
	if (f && strlen(f)) { m_fio = new char[strlen(f) + 1]; strcpy_s(m_fio, strlen(f) + 1, f); }
	else { m_fio = NULL; }
	if (hp && strlen(hp)) { m_home_phone = new char[strlen(hp) + 1]; strcpy_s(m_home_phone, strlen(hp) + 1, hp); }
	else { m_home_phone = NULL; }
	if (wp && strlen(wp)) { m_work_phone = new char[strlen(wp) + 1]; strcpy_s(m_work_phone, strlen(wp) + 1, wp); }
	else { m_work_phone = NULL; }
	if (mf && strlen(mf)) { m_mobile_phone = new char[strlen(mf) + 1]; strcpy_s(m_mobile_phone, strlen(mf) + 1, mf); }
	else { m_mobile_phone = NULL; }
	if (aci && strlen(aci)) { m_addit_cont_inf = new char[strlen(aci) + 1]; strcpy_s(m_addit_cont_inf, strlen(aci) + 1, aci); }
	else { m_addit_cont_inf = NULL; }
	cout << "Конструктор с параметрами для " << this << endl;
}
Subscriber::Subscriber() {
	m_fio = 0;
	m_home_phone = 0;
	m_work_phone = 0;
	m_mobile_phone = 0;
	m_addit_cont_inf = 0;
}
Subscriber::~Subscriber() {
	delete[]m_fio; //cout << "Деструктор для " << this << endl;
	delete[]m_home_phone; //cout << "Деструктор для " << this << endl;
	delete[]m_work_phone; //cout << "Деструктор для " << this << endl;
	delete[]m_mobile_phone; //cout << "Деструктор для " << this << endl;
	delete[]m_addit_cont_inf; //cout << "Деструктор для " << this << endl;
	cout << "Вызвался Subscriber деструктор для " << this << endl;
}
inline void Subscriber::Print() {
	cout << "Фамилия, имя, отчество: " << m_fio << endl;
	cout << "Домашний телефон: " << m_home_phone << endl;
	cout << "Рабочий телефон: " << m_work_phone << endl;
	cout << "Мобильный телефон: " << m_mobile_phone << endl;
	cout << "Дополнительная информация о контакте: " << m_addit_cont_inf << endl;
}
class PhoneBook {
private:
	int m_N; // кількість в масиві
	Subscriber* m_subscr; // 	Student* st;
	char* m_name;
public:
	inline PhoneBook(const char* n) : m_name(_strdup(n)), m_N(0), m_subscr(0) {}
	inline ~PhoneBook() { delete[]m_name; delete[]m_subscr; cout << "Вызвался PhoneBook деструктор для " << this << endl; }
	void Push(const Subscriber& s);
	void Push();
	void Print();
	void Delete(int a);
	void SaveToFile(const char* filename);
	void ReadFromFile(const char* filename);
};
void PhoneBook::Push(const Subscriber& d) {
	Subscriber* newm_subscr = new Subscriber[m_N + 1];
	for (size_t i = 0; i <= m_N; i++) // возможно проблема тут
		newm_subscr[i] = m_subscr[i];
	delete[]m_subscr;
	m_subscr = newm_subscr;
	m_subscr[m_N] = d;
	m_N++;
}
void PhoneBook::Push() {
	cout << "Введите данные:" << endl;
	cout << "Введите фамилию, имя, отчество: ";
	char buf_fio[50];
	cin.getline(buf_fio, 50);
	cout << "\nДомашний телефон: ";
	char buf_home_phone[50];
	cin.getline(buf_home_phone, 50);
	cout << "\nРабочий телефон: ";
	char buf_work_phone[50];
	cin.getline(buf_work_phone, 50);
	cout << "\nМобильный телефон: ";
	char buf_mobile_phone[50];
	cin.getline(buf_mobile_phone, 50);
	cout << "\nДополнительная информация о контакте: ";
	char buf_addit_cont_inf[50];
	cin >> buf_addit_cont_inf;
	Push(Subscriber(buf_fio, buf_home_phone, buf_work_phone, buf_mobile_phone, buf_addit_cont_inf));
}
void PhoneBook::Print() {
	cout << "Телефонная книга: " << m_name << endl;
	cout << "Кол-во абонентов в тел. книге: " << m_N << endl;
	for (size_t i = 0; i < m_N; i++) {
		m_subscr[i].Print();
	}
}
void PhoneBook::Delete(int a) {
	Subscriber* newm_subscr = new Subscriber[m_N - 1];
	for (size_t i = 0; i < a; i++)
		newm_subscr[i] = m_subscr[i];
	for (size_t i = a + 1; i < m_N; i++)
		newm_subscr[i - 1] = m_subscr[i];
	delete[]m_subscr;
	m_subscr = newm_subscr;
	m_N--;
}
void PhoneBook::SaveToFile(const char* filename) {
	FILE* fs;
	if (fopen_s(&fs, filename, "wb")) {
		cout << "Error";
		return;
	}
	int len = m_name ? strlen(m_name) : 0; // визначаємо довжину назви групи
	fwrite(&len, sizeof(len), 1, fs); // записуємо довжину імені
	fwrite(m_name, len, 1, fs); // пишемо назву группи
	fwrite(&m_N, sizeof(m_N), 1, fs);
	for (int i = 0; i < m_N; i++) {
		len = m_subscr[i].GetFio() ? strlen(m_subscr[i].GetFio()) : 0;
		fwrite(m_subscr[i].GetFio(), len, 1, fs);
		len = m_subscr[i].GetHome_phone() ? strlen(m_subscr[i].GetHome_phone()) : 0;
		fwrite(m_subscr[i].GetHome_phone(), len, 1, fs);
		len = m_subscr[i].GetWork_phone() ? strlen(m_subscr[i].GetWork_phone()) : 0;
		fwrite(m_subscr[i].GetWork_phone(), len, 1, fs);
		len = m_subscr[i].GetMobile_phone() ? strlen(m_subscr[i].GetMobile_phone()) : 0;
		fwrite(m_subscr[i].GetMobile_phone(), len, 1, fs);
		len = m_subscr[i].GetAddit_cont_inf() ? strlen(m_subscr[i].GetAddit_cont_inf()) : 0;
		fwrite(m_subscr[i].GetAddit_cont_inf(), len, 1, fs);
	}
	fclose(fs);
}
void PhoneBook::ReadFromFile(const char* filename) {
	FILE* fs;
	if (fopen_s(&fs, filename, "rb")) {
		cout << "Error";
		return;
	}
	int len = m_name ? strlen(m_name) : 0;
	fread(&len, sizeof(len), 1, fs);
	fread(m_name, len, 1, fs);
	fread(&m_N, sizeof(m_N), 1, fs);
	delete[] m_subscr;
	m_subscr = new Subscriber[m_N];
	for (int i = 0; i < m_N; i++) {
		char* buf_fio;
		fread(&len, sizeof(len), 1, fs); // прочитали довжину файлу
		buf_fio = new char[len + 1]{ 0 }; // для читання імені треба виділити память
		fread(buf_fio, len, 1, fs); // читаємо в буфер, читаємо розмір лен, 1, фс. Імя зчитано !

		char* buf_home_phone;
		fread(&len, sizeof(len), 1, fs); // прочитали довжину файлу
		buf_home_phone = new char[len + 1]{ 0 }; // для читання імені треба виділити память
		fread(buf_home_phone, len, 1, fs); // читаємо в буфер, читаємо розмір лен, 1, фс. Імя зчитано !

		char* buf_work_phone;
		fread(&len, sizeof(len), 1, fs); // прочитали довжину файлу
		buf_work_phone = new char[len + 1]{ 0 }; // для читання імені треба виділити память
		fread(buf_work_phone, len, 1, fs); // читаємо в буфер, читаємо розмір лен, 1, фс. Імя зчитано !

		char* buf_mobile_phone;
		fread(&len, sizeof(len), 1, fs); // прочитали довжину файлу
		buf_mobile_phone = new char[len + 1]{ 0 }; // для читання імені треба виділити память
		fread(buf_mobile_phone, len, 1, fs); // читаємо в буфер, читаємо розмір лен, 1, фс. Імя зчитано !

		char* buf_addit_cont_inf;
		fread(&len, sizeof(len), 1, fs); // прочитали довжину файлу
		buf_addit_cont_inf = new char[len + 1]{ 0 }; // для читання імені треба виділити память
		fread(buf_addit_cont_inf, len, 1, fs); // читаємо в буфер, читаємо розмір лен, 1, фс. Імя зчитано !		
		m_subscr[i] = Subscriber(buf_fio, buf_home_phone, buf_work_phone, buf_mobile_phone, buf_addit_cont_inf); //buf_fio, buf_home_phone, buf_work_phone, buf_mobile_phone, buf_addit_cont_inf
		delete[]buf_fio;
		delete[]buf_home_phone;
		delete[]buf_work_phone;
		delete[]buf_mobile_phone;
		delete[]buf_addit_cont_inf;
	}
	fclose(fs);
}

int main() {
	setlocale(LC_ALL, ""); //працює тільки з потоком виведення
	SetConsoleCP(1251); //встановлює потрібну кодову таблицю, на потік введення
	SetConsoleOutputCP(1251); //встановлює потрібну кодову таблицю, на потік виводу.		
	PhoneBook PE911("PE911");
	Color(BACKGROUND, FOREGROUND);
	system("cls");
	const char* Main_menu[]{
		"1. Добавить нового абонемента",
		"2. Удалить абонементов",
		"3. Искать абонента по ФИО",
		"4. Показывать всех абонентов",
		"5. Сохранять информацию в файл",
		"6. Загрузить информацию из файла",
	};
	int size_of_Main_menu = sizeof(Main_menu) / 4;
	bool bo = true;
	int pm = 0;
	while (true)
	{
		pm = menu(Main_menu, size_of_Main_menu, pm);
		system("cls");
		switch (pm) // Main_menu
		{
		case -1:
			return 0;
		case 0: // "1. Добавить нового абонемента",
			PE911.Push();
			break;
		case 1: // "2. Удалить абонементов",
			int num_of_the_deleted_subscriber;
			cout << "Введите номер удаляемого абонента: ";
			cin >> num_of_the_deleted_subscriber;
			PE911.Delete(num_of_the_deleted_subscriber);
			break;
		case 2: // "3. Искать абонента по ФИО",

			break;
		case 3: // "4. Показывать всех абонентов",
			PE911.Print();
			break;
		case 4: // "5. Сохранять информацию в файл",
			PE911.SaveToFile("PE911.bin");
			break;
		case 5: // "6. Загрузить информацию из файла",
			PE911.ReadFromFile("PE911.bin");
			break;
		}
		Color(BACKGROUND, 2);
		cout << "\n\nОперацію виконано успішно !\n";
		_getch();
	}
}
