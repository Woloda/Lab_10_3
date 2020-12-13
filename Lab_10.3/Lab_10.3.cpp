#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;

enum measurement { МГ, Г, ЦН, КГ, ТТ };

string t_measurement[] = { "Мг ",
						   "Гр",
						   "Цн",
						   "Кг",
						   "Тн" };

struct towar
{
	string n_towar;
	int vartіst;
	int kilkist;
	measurement units;
	int masa;
};

void Create_towar(towar* s, const int kil_towar, int i, const char* name, bool bol);
void Print_towar(towar* s, const int kil_towar, int i, const char* name);
void SortTXT(char* lname, char* fname, const int kil_towar, towar* s);
int BinSearch_towar(const int kil_towar, const string nazwa_towar, char* gname, towar* s);
void BinSearch_vartist(towar* s, const int kil_towar, const int vartisr1, const int vartisr2, int& l1, int& l2, char* gname);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int kil_towar;
	cout << "Введіть початкову кількість товарів: "; cin >> kil_towar;
	cout << endl;
	int soxr_towar = kil_towar;
	towar* s = new towar[kil_towar + 100];

	char fname[12] = "test.txt";
	char gname[12] = "test1.txt";
	char lname[12] = "test1.1.txt";

	int i, g, pos, zmina, found, index;
	int l1 = 0, l2 = 0;
	int vartisr1, vartisr2;
	string nazwa_towar;
	char filename[100];

	int menutowar;
	do {
		cout << "Виберіть дію:" << endl << endl;

		cout << " [1] - створення списку товарів" << endl;
		cout << " [2] - перегляд інформації про товари" << endl;
		cout << " [3] - поповнення списку товарів" << endl;
		cout << " [4] - сортування товару" << endl;
		cout << " [5] - пошук товару за назвою і вивід інформації про товар" << endl;
		cout << " [6] - вивід інформації про товари із заданого діапазону вартості" << endl;

		cout << " [0] - вихід та завершення роботи програми" << endl << endl;

		cout << "Введіть пункт меню: "; cin >> menutowar;
		switch (menutowar)
		{
		case 1:
			kil_towar = soxr_towar;
			Create_towar(s, kil_towar, 0, fname, false);
			break;
		case 2:
			cout << endl;
			Print_towar(s, kil_towar, 0, fname);
			break;
		case 3:
			cout << endl;
			cout << "Введіть певну кількість товарів які ви хочете добавити до списку: "; cin >> g;
			cout << endl;
			kil_towar += g;
			i = kil_towar - g;
			Create_towar(s, kil_towar, i, fname, true);
			break;
		case 4:
			SortTXT(lname, fname, kil_towar, s);
			Print_towar(s, kil_towar, 0, fname);
			break;
		case 5:
			cout << endl;
			cin.get();
			cin.sync();
			cout << "Введіть назву товару: ";getline(cin, nazwa_towar);
			cout << endl;
			found = BinSearch_towar(kil_towar, nazwa_towar, gname, s);
			if (found != -1)
			{
				cout << "Інформація про товар: " << endl << endl;
				Print_towar(s, found + 1, found, fname);
			}
			else
				cout << "Введеного вами товару в списку не знайшлося: " << endl << endl;
			break;
		case 6:
			cout << "Діапазон вартості: " << endl << endl;
			cout << "Введіть мінімальну вартість: ";
			cin >> vartisr1;
			cout << "Введіть максимальну вартість: ";
			cin >> vartisr2;
			l1 = -1;
			l2 = -2;
			BinSearch_vartist(s, kil_towar, vartisr1, vartisr2, l1, l2, gname);
			Print_towar(s, l2 + 1, l1, fname);
			break;
		case 0:
			cout << "завершення роботи програми" << endl << endl;
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
		cout << endl;
	} while (menutowar != 0);
	delete[] s;
}

void Create_towar(towar* s, const int kil_towar, int i, const char* name, bool bol)
{
	ofstream save_f;
	if (bol)
		save_f.open(name, ios::app);
	else
		save_f.open(name);

	if (!save_f)
	{
		cerr << "Error opening file '" << name << "'" << endl;
		return;
	}

	int towar;
	for (; i < kil_towar; i++)
	{
		cout << endl;
		cout << "товар № " << i + 1 << endl;

		cin.get();
		cin.sync();

		cout << "  назва: "; getline(cin, s[i].n_towar);
		save_f << s[i].n_towar;
		save_f << "  ";
		cout << "  вартість(в грн.): "; cin >> s[i].vartіst;
		save_f << s[i].vartіst;
		save_f << "  ";
		cout << "  кількість: "; cin >> s[i].kilkist;
		save_f << s[i].kilkist;
		save_f << "  ";
		cout << "  одиниці вимірювання(0 - Міліграм, 1 - Грам, 2 - Центнер, 3 - Кілограм, 4 - Тонна): "; cin >> towar;
		s[i].units = (measurement)towar;
		save_f << s[i].units;
		save_f << "  ";
		cout << "  упаковка по: "; cin >> s[i].masa;
		save_f << s[i].masa;
		save_f << "  ";
		save_f << "\n";
		cout << "  " << t_measurement[towar] << endl;
	}
	save_f.close();
}

void Print_towar(towar* s, const int kil_towar, int i, const char* name)
{
	ifstream load_f(name);

	if (!load_f)
	{
		cerr << "Error opening file '" << name << "'" << endl;
		return;
	}

	cout << "====================================================================="
		<< endl;
	cout << "| №  | Назва        | Вартість(в грн.) | Кількість | упаковка по    |"
		<< endl;
	cout << "---------------------------------------------------------------------" << endl;

	int t, k = 0;
	for (; i < kil_towar; i++)
	{
		while (k < i + 1)
		{
			load_f >> s[i].n_towar;
			load_f >> s[i].vartіst;
			load_f >> s[i].kilkist;
			load_f >> t;
			s[i].units = (measurement)t;
			load_f >> s[i].masa;
			k++;
		}
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s[i].n_towar
			<< "| " << setw(16) << left << s[i].vartіst << " "
			<< "| " << setw(5) << left << s[i].kilkist << "     "
			<< "| " << setw(2) << left << s[i].masa << setw(1) << left << " " << setw(11) << left << t_measurement[s[i].units] << " |" << endl;
	}
	cout << "=====================================================================" << endl;

	load_f.close();
}

void SortTXT(char* lname, char* fname, const int kil_towar, towar* s)
{
	ofstream l_n(lname);
	for (int i = 0; i < kil_towar; i++)
		l_n << s[i].vartіst << endl;
	l_n.close();


	ofstream f(fname);
	string str, mins, z = "";
	int str_i, mins_i, z_i;
	istringstream iss2(z, istringstream::in);
	iss2 >> z_i;
	int k, l;
	do
	{
		int kil = 0;
		int kil_l = 0;
		int kil_k = 0;
		k = 0;
		l = 0;
		ifstream g(lname);
		while (getline(g, str))
		{
			istringstream iss(str, istringstream::in);
			iss >> str_i;
			if (str_i <= z_i)
				continue;
			mins = str;
			k++;
			break;
		}
		while (getline(g, str))
		{
			istringstream iss(str, istringstream::in);
			istringstream iss1(mins, istringstream::in);
			iss >> str_i;
			iss1 >> mins_i;
			if (str_i <= z_i)
				continue;
			if (str_i < mins_i)
			{
				mins = str;
				k++;
			}
		}
		z = mins;
		istringstream iss1(mins, istringstream::in);
		iss1 >> mins_i;
		for (kil = 0; kil < kil_towar; kil++)
			if (mins_i == s[kil].vartіst)
				break;
		istringstream iss2(z, istringstream::in);
		iss2 >> z_i;
		if (k > 0)
		{
			f << s[kil].n_towar;
			f << "  ";
			f << z;
			f << "  ";
			f << s[kil].kilkist;
			f << "  ";
			f << s[kil].units;
			f << "  ";
			f << s[kil].masa;
			f << "  ";
			f << "\n";
		}
		g.close();
	} while (k > 0);
}

int BinSearch_towar(const int kil_towar, const string nazwa_towar, char* gname, towar* s)
{
	ofstream l_n(gname);
	for (int i = 0; i < kil_towar; i++)
		l_n << s[i].n_towar << endl;
	l_n.close();

	ifstream g_load(gname);
	string str;
	int k = 0, i = 0;

	while (i < kil_towar)
	{
		if (getline(g_load, str))
			if (str == nazwa_towar)
			{
				g_load.close();
				return k;
			}
			else
				k++;
		i++;
	}
	g_load.close();
	return -1;
}

void BinSearch_vartist(towar* s, const int kil_towar, const int vartisr1, const int vartisr2, int& l1, int& l2, char* gname)
{
	ofstream l_n(gname);
	for (int i = 0; i < kil_towar; i++)
		l_n << s[i].vartіst << endl;
	l_n.close();

	ifstream g_load(gname);
	string str;

	int g = 0, str_i;
	for (int i = 0; i < kil_towar; i++)
	{
		if (getline(g_load, str))
		{
			istringstream iss2(str, istringstream::in);
			iss2 >> str_i;
			if (str_i >= vartisr1 && str_i <= vartisr2)
			{
				l2 = i;
				g++;
			}
			if (g == 1)
				l1 = l2;
		}
	}
}