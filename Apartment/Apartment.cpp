//Создайте программу, имитирующую многоквартирный дом.
//Необходимо иметь классы “Человек”, “Квартира”, “Дом”.
//Класс “Квартира” содержит динамический массив объектов класса “Человек”.
//Класс “Дом” содержит массив объектов класса “Квартира”.
//Каждый из классов содержит переменные - члены и функции - члены, которые необходимы для предметной области класса.
//Обращаем ваше внимание, что память под строковые значения выделяется динамически.
//Например, для ФИО в классе “Человек”.
//Не забывайте обеспечить классы различными конструкторами(конструктор копирования обязателен), деструкторами.
//В main протестировать работу полученного набора классов.

#include <iostream>
#include <Windows.h>

using namespace std;

class Human {
	char* name;
	char* patronym;
	char* surname;
public:
	Human(const char* name_p, const char* patronym_p, const char* surname_p)
	{
		if (name_p)
		{
			name = new char[strlen(name_p) + 1] {};
			strcpy_s(name, strlen(name_p) + 1, name_p);
		}
		if (patronym_p)
		{
			patronym = new char[strlen(patronym_p) + 1] {};
			strcpy_s(patronym, strlen(patronym_p) + 1, patronym_p);
		}
		if (surname_p)
		{
			surname = new char[strlen(surname_p) + 1] {};
			strcpy_s(surname, strlen(surname_p) + 1, surname_p);
		}
	}
	Human() :Human(nullptr, nullptr, nullptr) {}
	~Human()
	{
		delete[]surname;
		delete[]patronym;
		delete[]name;
	}
	Human(const Human& human)
	{
		if (human.name)
		{
			name = new char[strlen(human.name) + 1] {};
			strcpy_s(name, strlen(human.name) + 1, human.name);
		}
		if (human.patronym)
		{
			patronym = new char[strlen(human.patronym) + 1] {};
			strcpy_s(patronym, strlen(human.patronym) + 1, human.patronym);
		}
		if (human.surname)
		{
			surname = new char[strlen(human.surname) + 1] {};
			strcpy_s(surname, strlen(human.surname) + 1, human.surname);
		}
	}
	Human& operator=(const Human& human)
	{
		if (&human != this) {

			name = new char[strlen(human.name) + 1] {};
			strcpy_s(name, strlen(human.name) + 1, human.name);

			patronym = new char[strlen(human.patronym) + 1] {};
			strcpy_s(patronym, strlen(human.patronym) + 1, human.patronym);

			surname = new char[strlen(human.surname) + 1] {};
			strcpy_s(surname, strlen(human.surname) + 1, human.surname);

		}
		return *this;
	}
	Human& setName(char* name_p)
	{
		this->name = name_p;
		return *this;
	}
	Human& setPatronym(char* patronym_p)
	{
		this->patronym = patronym_p;
		return *this;
	}
	Human& setSurname(char* surname_p)
	{
		this->surname = surname_p;
		return *this;
	}
	char* getName()const
	{
		return this->name;
	}
	char* getPatronym()const
	{
		return this->patronym;
	}
	char* getSurname()const
	{
		return this->surname;
	}
	void show()const
	{
		cout << surname << ' ' << name << ' ' << patronym;
	}
};
ostream& operator<<(ostream& os, const Human& human)
{
	os << human.getSurname() << ' ' << human.getName() << ' ' << human.getPatronym();
	return os;
}
class Flat
{
	unsigned int number;
	unsigned int tenantQty;
	Human* tenants;
public:
	Flat(unsigned int number_p, unsigned int tenantQty_p, const Human* tenants_p) :number{ number_p }, tenantQty{ tenantQty_p }
	{
		if (tenantQty_p)
		{
			tenants = new Human[tenantQty_p]{};
			for (unsigned int i = 0; i < tenantQty; i++)
			{
				tenants[i] = tenants_p[i];
			}
		}
	}
	~Flat()
	{
		delete[]tenants;
	}

	Flat() :Flat(0, 0, nullptr) {}

	explicit Flat(unsigned int number_p) : Flat(number_p, 0, nullptr) {}

	Flat(const Flat& flat)
	{
		this->number = flat.number;
		this->tenantQty = flat.tenantQty;

		if (flat.tenants)
		{
			tenants = new Human[flat.tenantQty]{};
			for (unsigned int i = 0; i < tenantQty; i++)
			{
				tenants[i] = flat.tenants[i];
			}
		}
	}
	Flat& operator=(const Flat& flat)
	{
		if (&flat != this)
		{
			this->tenants = flat.tenants;
			this->number = flat.number;
			this->tenantQty = flat.tenantQty;
		}
		return *this;
	}
	Flat& setNumber(unsigned int number_p)
	{
		this->number = number_p;
		return *this;
	}
	Flat& setTenantsQty(unsigned int tenantsQty_p)
	{
		this->tenantQty = tenantsQty_p;
		return *this;
	}
	Flat& setTenants(Human* tenants_p)
	{
		this->tenants = tenants_p;
		return *this;
	}
	unsigned int getNumber()const
	{
		return number;
	}
	unsigned int getTenantsQty()const
	{
		return tenantQty;
	}
	Human* getTenants()const
	{
		return tenants;
	}
	void show() const
	{
		cout << "Квартира № " << this->getNumber() << ":\n";
		cout << "Количество жильцов: " << this->getTenantsQty() << '\n';
		cout << "Список проживающих:\n";
		for (unsigned int i = 0; i < this->getTenantsQty(); i++)
		{
			cout << this->tenants[i] << '\n';
		}

	}
};

class Building
{
	char* address;
	unsigned int flatsQty;
	Flat* flats;
public:
	Building(const char* address_p, const unsigned int flatsQty_p, const Flat* flats_p)
	{
		if (address_p)
		{
			address = new char[strlen(address_p) + 1];
			strcpy_s(address, strlen(address_p) + 1, address_p);
		}
		flatsQty = flatsQty_p;
		if (flats_p)
		{
			flats = new Flat[flatsQty];
			for (unsigned int i = 0; i < flatsQty; i++)
			{
				flats[i] = flats_p[i];
			}
		}

	}
	Building() :Building(nullptr, 0, nullptr) {}
	~Building()
	{
		delete[]flats;
		delete[]address;
	}
	Building(const Building& building)
	{
		if (building.address)
		{
			address = new char[strlen(building.address) + 1];
			strcpy_s(address, strlen(building.address) + 1, building.address);
		}
		flatsQty = building.flatsQty;
		if (building.flats)
		{
			flats = new Flat[flatsQty];
			for (unsigned int i = 0; i < flatsQty; i++)
			{
				flats[i] = building.flats[i];
			}
		}
	}
	Building& operator=(const Building& building)
	{
		if (&building != this) {
			if (building.address)
			{
				this->address = new char[strlen(building.address) + 1];
				strcpy_s(this->address, strlen(building.address) + 1, building.address);
			}
			this->flatsQty = building.flatsQty;
			if (building.flats)
			{
				this->flats = new Flat[flatsQty];
				for (unsigned int i = 0; i < this->flatsQty; i++)
				{
					this->flats[i] = building.flats[i];
				}
			}
		}
		return *this;
	}
	Building& setAddress(char* address_p)
	{
		this->address = address_p;
		return *this;
	}
	Building& setFlatsQty(unsigned int flatsQty_p)
	{
		this->flatsQty = flatsQty_p;
		return *this;
	}
	Building& setFlats(Flat* flats_p)
	{
		this->flats = flats_p;
		return *this;
	}
	char* getAddress()const
	{
		return this->address;
	}
	unsigned int getFlatsQty()const
	{
		return this->flatsQty;
	}
	Flat* getFlats()const
	{
		return this->flats;
	}
	void show()
	{
		cout << "Адрес дома: " << address << '\n';
		cout << "Поквартирный список:\n";
		for(unsigned int i = 0; i < flatsQty; i++)
		{
			flats[i].show();
			cout << '\n';
		}
	}

};
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char* n1 = new char[] {"Петр"};
	char* p1 = new char[] {"Сергеевич"};
	char* s1 = new char[] {"Иванов"};
	char* n2 = new char[] {"Дмитрий"};
	char* p2 = new char[] {"Евгеньевич"};
	char* s2 = new char[] {"Морозов"};
	char* n3 = new char[] {"Ольга"};
	char* p3 = new char[] {"Александровна"};
	char* s3 = new char[] {"Виденович"};

	Human h2{ n2,p2,s2 };
	Human h1;
	h1.setName(n1).setSurname(s1).setPatronym(p1);
	Human h3{ n3,p3,s3 };
	cout << h1 << '\n' << h2 << '\n';
	cout << '\n';
	Human* tenants1 = new Human[]{ h1,h2,h3 };
	Flat flat1{ 1,3,tenants1 };
	flat1.show();
	cout << '\n';
	Human h4{ "Семен","Макарович","Петров" };
	Human h5{ "Маргарита","Егоровна","Петрова" };
	Human h6{ "Василий","Семенович","Петров" };
	Human h7{ "Макар","Семенович","Петров" };
	Human* tenants2 = new Human[]{ h4,h5,h6,h7 };
	Flat flat2{ 2,4, tenants2 };
	Flat* building1 = new Flat[]{ flat1,flat2 };
	Building b1{ "3 улица Строителей, 2",2,building1 };
	b1.show();


}

