#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>


using std::string;
using std::endl;
using std::cout;
using std::cin;

class address {
	string city;
	string street;
	string house ;
	string flat;
	string outputAddr;

public:
	address() {
		city = "";
		street = "";
		house = "0";
		flat = "0";
	};
	address(string city, string street, string house,  string flat)
	{
		this->city = city;
		this->street = street;
		this->house = house;
		this->flat = flat;
	}
	string GetOutputAddr()
	{
		string sSeparator = ", ";
		return city + sSeparator + street + sSeparator + house + sSeparator + flat;
	}
	void SetOutputAddr(string s)
	{

		this->city = field(s);
		this -> street = field(s);
		this->house = field(s);
		this->flat = s;
	}
private:
	string field(string &s)
	{
		string delimiter = ", ";

		size_t pos = 0;
		string token;
			if ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());
			}
		return token;
	}
};

int readCount(std::ifstream& f)
{
	int cnt;
	string sCnt;
	std::getline(f, sCnt);
	cnt = stoi(sCnt);
	return cnt;
}

address readStruct(std::ifstream& f)
{
	string line;
	string city;
	string street;
	string house;
	string flat;
	std::getline(f, city);
	std::getline(f, street);
	std::getline(f, house);
	std::getline(f, flat);
	{
		address a(city, street, house, flat);
		return a;
	}
}

void fDeleteAddr(address*& a)
{
	delete[] a;
	a = nullptr;
}

void sort(address* addresses, int size)
{
	bool change = false;
	do {
		change = false;
		string c;
		for (int i = 1; i < size; ++i)
		{
			if (addresses[i - 1].GetOutputAddr() > addresses[i].GetOutputAddr())
			{
				c = addresses[i - 1].GetOutputAddr();
				addresses[i - 1].SetOutputAddr(addresses[i].GetOutputAddr());
				addresses[i].SetOutputAddr(c);
				change = true;
			}
		}
	} while (change);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	// "Чтение из файла"
	string sing = "";
	std::ifstream in("\in.txt");
	const int cnt = readCount(in);
	address* adr = new address[cnt];
	for (int i = 0; i < cnt; i++)
	{
		adr[i] = readStruct(in);
	}
	// "Закрываем файл"
	in.close();

	std::ofstream out("\out.txt");
	out << cnt << endl;
	sort(adr, cnt);
	for (int i = 0; i < cnt; ++i)
	{
		out << adr[i].GetOutputAddr() << endl;
	}
	fDeleteAddr(adr);
	out.close();
}