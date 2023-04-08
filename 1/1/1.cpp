#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>


using std::string;
using std::endl;
using std::cout;
using std::cin;

class adress {
	string city;
	string street;
	unsigned int house = 0;
	unsigned int flat = 0;
public:
	adress() {
		city = "";
		street = "";
		house = 0;
		flat = 0;
	};
	adress(string city, string street, unsigned int house, unsigned int flat)
	{
		this->city = city;
		this->street = street;
		this->house = house;
		this->flat = flat;
	}
	string getCity()
	{
		return city;
	}
	string getStreet()
	{
		return street;
	}
	unsigned int getHouse()
	{
		return house;
	}
	unsigned int getFlat()
	{
		return flat;
	}
	string GetOutputAddr()
	{
		string sSeparator = ", ";
		return city + sSeparator + street + sSeparator + std::to_string(house) + sSeparator + std::to_string(flat);
	}
};

int readCount(std::ifstream& f)
{
	int cnt;
	string sCnt;
//	if (f >> cnt) return cnt;
	std::getline(f, sCnt);
	cnt = stoi(sCnt);
    return cnt;
}

adress readStruct(std::ifstream& f)
{
	string line;
	string city;
	string street;
	unsigned int house;
	unsigned int flat;
	std::getline(f, city);
	std::getline(f, street);
	std::getline(f, line);
	house = stoi(line);
	std::getline(f, line);
	flat = stoi(line);
	{
		adress a(city, street, house, flat);
		return a;
	}
}

void fDeleteAddr(adress*& a)
{
	delete[] a;
	a = nullptr;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	// "Чтение из файла"
	string sing = "";
	std::ifstream in("\in.txt");
	const int cnt = readCount(in);
	adress* adr = new adress[cnt];
	for (int i = 0; i < cnt; i++)
	{
		adr[i] = readStruct(in);
	}
	// "Закрываем файл"
	in.close();

	std::ofstream out("\out.txt");
	out << cnt << endl;
	for (int i = cnt - 1; i >= 0; --i)
	{
		out << adr[i].GetOutputAddr() << endl;
	}
	fDeleteAddr(adr);
	out.close();
}