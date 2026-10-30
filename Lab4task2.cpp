#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

//вспомогательные функции для бинарной сериализации
//функция сначала в файл записывает длину строки, потом саму строку
void writeString(ostream& out, const string& str);

//функция сначала считывает длину строки, затем считывает колв-во символов = длине строки
string readString(istream& in);

//функция вычисляет сумму байт записи в файл, для проверки на целостность данных
uint32_t calculateChecksum(const char* data, size_t size);

//абстрактный класс с общими полями и абстрактными методами
class Animal {
private:
	int m_age;
	double m_weight;
	string m_species;
public:
	//конструктор по умолчанию
	Animal() {}

	//конструктор с параметрами
	Animal(int age, double weight, string species) : m_age(age), m_weight(weight), m_species(species) {}

	//чистые виртуальные функции
	virtual void makeTheSound() = 0;
	virtual void toEat() = 0;
	virtual void toDescribe() = 0;
	virtual string getType() const = 0;

	//метод, который записывает родительские атрибуты в БИНАРНЫЙ файл 
	virtual void save(ostream& out) const {
		out.write(reinterpret_cast<const char*>(&m_age), sizeof(m_age));
		out.write(reinterpret_cast<const char*>(&m_weight), sizeof(m_weight));
		writeString(out, m_species);
	}

	//метод, который считывает родительские аттрибуты из БИНАРНОГО файла
	virtual void load(istream& in) {
		in.read(reinterpret_cast<char*>(&m_age), sizeof(m_age));
		in.read(reinterpret_cast<char*>(&m_weight), sizeof(m_weight));
		m_species = readString(in);
	}

	//геттеры
	int getAge() const {
		return m_age;
	}

	double getWeight() const {
		return m_weight;
	}

	string getSpecies() const {
		return m_species;
	}

	//обычный метод для демонстрации раннего полиморфизма
	void sleep() const {
		cout << m_species << " спит" << endl;
	}

	//виртуальные деструктор
	virtual ~Animal() {}
};

//подкласс лев
class Lion : public Animal {
private:
	double m_runningSpeed; //скорость бега
public:
	Lion() {}
	Lion(int age, double weight, string species, double runningSpeed) : Animal(age, weight, species), m_runningSpeed(runningSpeed) {}

	double getRunningSpeed() const {
		return m_runningSpeed;
	}

	//переопределение методов
	virtual void makeTheSound() override {
		cout << "Лев рычит" << endl;
	}

	virtual void toEat() override {
		cout << "Лев ест мясо" << endl;
	}

	virtual void toDescribe() override {
		cout << "Животное: Лев" << endl;
		cout << "age: " << getAge() << endl;
		cout << "weight: " << getWeight() << endl;
		cout << "species: " << getSpecies() << endl;
		cout << "runningSpeed: " << getRunningSpeed() << endl;
	}

	virtual string getType() const override { 
		return "LION";
	}

	//метод, записывает все атрибуты класса Lion в бинарный файл
	void save(ostream& out) const override {
		Animal::save(out);
		out.write(reinterpret_cast<const char*>(&m_runningSpeed), sizeof(m_runningSpeed));
	}

	//метод, считывает атрибуты класса Lion в бинарный файл
	void load(istream& in) override {
		Animal::load(in);
		in.read(reinterpret_cast<char*>(&m_runningSpeed), sizeof(m_runningSpeed));
	}
};

//подкласс слон
class Elephant : public Animal {
private:
	double m_earSize; //размер ушей
public:
	Elephant() {}
	Elephant(int age, double weight, string species, double earSize) : Animal(age, weight, species), m_earSize(earSize) {}

	double getEarSize() const {
		return m_earSize;
	}

	//переопределение методов
	virtual void makeTheSound() override {
		cout << "Слон трубит" << endl;
	}

	virtual void toEat() override {
		cout << "Слон ест листья" << endl;
	}

	virtual void toDescribe() override {
		cout << "Животное: Слон" << endl;
		cout << "age: " << getAge() << endl;
		cout << "weight: " << getWeight() << endl;
		cout << "species: " << getSpecies() << endl;
		cout << "earSize: " << getEarSize() << endl;
	}

	virtual string getType() const override {
		return "ELEPHANT";
	}

	void save(ostream& out) const override {
		Animal::save(out);
		out.write(reinterpret_cast<const char*>(&m_earSize), sizeof(m_earSize));
	}
	void load(istream& in) override {
		Animal::load(in);
		in.read(reinterpret_cast<char*>(&m_earSize), sizeof(m_earSize));
	}
};

//подкласс пингвин
class Penguin : public Animal {
private:
	int m_flockSize; //размер стаи
public:
	Penguin() {}
	Penguin(int age, double weight, string species, int flockSize) : Animal(age, weight, species), m_flockSize(flockSize) {}

	int getFlockSize() const {
		return m_flockSize;
	}

	//переопределение методов
	virtual void makeTheSound() override {
		cout << "Пингвин пищит" << endl;
	}

	virtual void toEat() override {
		cout << "Пингвин ест рыбу" << endl;
	}

	virtual void toDescribe() override {
		cout << "Животное: Пингвин" << endl;
		cout << "age: " << getAge() << endl;
		cout << "weight: " << getWeight() << endl;
		cout << "species: " << getSpecies() << endl;
		cout << "flockSize: " << getFlockSize() << endl;
	}

	virtual string getType() const override {
		return "PENGUIN";
	}

	void save(ostream& out) const override {
		Animal::save(out);
		out.write(reinterpret_cast<const char*>(&m_flockSize), sizeof(m_flockSize));
	}
	void load(istream& in) override {
		Animal::load(in);
		in.read(reinterpret_cast<char*>(&m_flockSize), sizeof(m_flockSize));
	}
};

//подкласс дельфин
class Dolphin : public Animal {
private:
	double m_jumpHeight;
public:
	Dolphin() {}
	Dolphin(int age, double weight, string species, double jumpHeight) : Animal(age, weight, species), m_jumpHeight(jumpHeight) {}

	double getJumpHeight() const {
		return m_jumpHeight;
	}

	//переопределение методов
	virtual void makeTheSound() override {
		cout << "Дельфин издает какой-то звук" << endl;
	}

	virtual void toEat() override {
		cout << "Дельфин ест рыбу" << endl;
	}

	virtual void toDescribe() override {
		cout << "Животное: Дельфин" << endl;
		cout << "age: " << getAge() << endl;
		cout << "weight: " << getWeight() << endl;
		cout << "species: " << getSpecies() << endl;
		cout << "jumpHeight: " << getJumpHeight() << endl;
	}

	virtual string getType() const override {
		return "DOLPHIN";
	}

	void save(ostream& out) const override {
		Animal::save(out);
		out.write(reinterpret_cast<const char*>(&m_jumpHeight), sizeof(m_jumpHeight));
	}
	void load(istream& in) override {
		Animal::load(in);
		in.read(reinterpret_cast<char*>(&m_jumpHeight), sizeof(m_jumpHeight));
	}

};

//класс фабрика животных нужен для того, чтоб при чтении данных из файла мы понимали какие данные принадлежат обьекту какого класса
class AnimalFactory {
public:
	//статический метод который при обнарружении тега, создает обьект соответсвующего класса
	static unique_ptr<Animal> create(const string& type) {
		if (type == "LION") {
			return make_unique<Lion>();
		}
		if (type == "ELEPHANT") {
			return make_unique<Elephant>();
		}
		if (type == "PENGUIN") {
			return make_unique<Penguin>();
		}
		if (type == "DOLPHIN") {
			return make_unique<Dolphin>();
		}

		throw runtime_error("Ошибка! Неизвестный тег для считывания - " + type);
	}
};

//класс который записывает из потока информацию в БИНАРНЫЙ файл или наоборот + записывать/считывать данные в любом месте файла
class BinaryStorage {
private:
	//Использование unique_ptr для владения файловым потоком
	unique_ptr<fstream> fileStream; //умнйы указатель на файловый поток

public:
	//Открытие файла в бинарном режиме для чтения и записи
	void open(const string& fileName) {
		fileStream = make_unique<fstream>(fileName, ios::in | ios::out | ios::binary | ios::trunc);
		if (!fileStream->is_open()) {
			throw runtime_error("Ошибка открытия файла: " + fileName);
		}
	}

	//Если файл уже существует и мы хотим его только читать/дописывать без trunc:
	void openExisting(const string& fileName) {
		fileStream = make_unique<fstream>(fileName, ios::in | ios::out | ios::binary);
		if (!fileStream->is_open()) {
			throw runtime_error("Ошибка открытия файла: " + fileName);
		}
	}

	void close() {
		if (fileStream && fileStream->is_open()) { //если файл открыт и указатель не null то закрываемф
			fileStream->close();
		}
	}

	//Запись объекта в произвольную позицию с контролем целостности
	void writeAt(size_t position, const Animal& animal) {
		if (!fileStream || !fileStream->is_open()) {
			throw runtime_error("Файл не открыт");
		}

		//Сериализуем объект во временный буфер в памяти, чтобы узнать его точный размер и посчитать checksum
		ostringstream tempBuffer(ios::binary);
		string type = animal.getType();
		writeString(tempBuffer, type); // Сначала записываем тип, чтобы при чтении знать, кого создавать
		animal.save(tempBuffer);       // Затем данные объекта

		string data = tempBuffer.str();
		size_t dataSize = data.size();
		uint32_t checksum = calculateChecksum(data.c_str(), dataSize);

		//Перемещаем указатель записи в нужную позицию (произвольный доступ)
		fileStream->seekp(position);
		if (fileStream->fail()) {
			throw runtime_error("Ошибка позиционирования при записи (seekp)");
		}

		//Записываем структуру: [Длина строки (8 байт)] + [Сами данные] + [Контрольная сумма байт (4 байта)]
		fileStream->write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize)); //длина строки
		fileStream->write(data.c_str(), dataSize); //данные
		fileStream->write(reinterpret_cast<const char*>(&checksum), sizeof(checksum)); //сумма байт

		if (fileStream->fail()) {
			throw runtime_error("Ошибка физической записи в файл");
		}
	}

	//Чтение объекта из произвольной позиции с проверкой целостности
	unique_ptr<Animal> readAt(size_t position) {
		if (!fileStream || !fileStream->is_open()) {
			throw runtime_error("Файл не открыт");
		}

		//Проверка на выход за границы файла
		fileStream->seekg(0, ios::end); //переносит указатель в конец файла
		size_t fileSize = fileStream->tellg(); //узнаем размер файла

		//Минимальный размер записи: 8 байт (lkbyf) + 0 байт (данные) + 4 байта (checksum) = 12 байт
		if (position >= fileSize || position + 12 > fileSize) {
			throw out_of_range("Ошибка: позиция выходит за границы файла или файл слишком мал для чтения");
		}

		//Перемещаем указатель чтения в нужную позицию
		fileStream->seekg(position);

		//Читаем размер блока данных
		uint64_t dataSize;
		fileStream->read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
		if (fileStream->fail()) {
			throw runtime_error("Ошибка чтения размера блока данных");
		}

		//Выделяем буфер и читаем сами данные
		vector<char> buffer(dataSize);
		fileStream->read(buffer.data(), dataSize);
		if (fileStream->fail()) {
			throw runtime_error("Ошибка чтения данных объекта");
		}

		//Читаем контрольную сумму из файла
		uint32_t fileChecksum;
		fileStream->read(reinterpret_cast<char*>(&fileChecksum), sizeof(fileChecksum));
		if (fileStream->fail()) {
			throw runtime_error("Ошибка чтения контрольной суммы");
		}

		//Проверяем целостность данных
		uint32_t calculatedChecksum = calculateChecksum(buffer.data(), dataSize);
		if (fileChecksum != calculatedChecksum) {
			throw runtime_error("Ошибка целостности данных: контрольная сумма не совпадает! Файл поврежден.");
		}

		//Десериализация: помещаем буфер в поток для чтения
		istringstream inBuffer(string(buffer.data(), dataSize), ios::binary);

		//Читаем тип объекта
		string type = readString(inBuffer);

		//Создаем объект нужного класса через фабрику
		unique_ptr<Animal> animal = AnimalFactory::create(type);

		//Загружаем специфичные данные в объект
		animal->load(inBuffer);

		return animal;
	}
};

int main() {
	setlocale(LC_ALL, "RU");

	const string fileName = "zoo_binary.dat";

	cout << "Бинарне хранение с произвольным доступом\n\n";

	// Создаем тестовые объекты
	auto lion = make_unique<Lion>(10, 100.0, "лев", 30.0);
	auto elephant = make_unique<Elephant>(5, 3000.0, "слон", 50.0);
	auto penguin = make_unique<Penguin>(3, 20.0, "пингвин", 300);

	BinaryStorage storage;

	try {
		//Открываем файл (trunc очистит его, если он существовал)
		storage.open(fileName);
		cout << "Файл открыт в бинарном режиме.\n";

		//Демонстрация записи в ПРОИЗВОЛЬНЫЕ позиции
		//Мы намеренно выбираем далекие позиции, чтобы показать работу seekp
		cout << "\nЗапись объектов в произвольные позици\n";

		storage.writeAt(0, *lion); // Записываем льва в начало файла (позиция 0)
		cout << "Лев записан в позицию 0\n";

		storage.writeAt(500, *elephant); // Записываем слона в позицию 500
		cout << "[OK] Слон записан в позицию 500\n";

		storage.writeAt(1000, *penguin); // Записываем пингвина в позицию 1000
		cout << "Пингвин записан в позицию 1000\n";

		storage.close();
		cout << "Файл корректно закрыт\n";

		//Демонстрация чтения из произвольных позиций
		cout << "\nЧтение объектов из произвольных позиций\n";
		storage.openExisting(fileName); // Открываем существующий файл без очистки

		cout << "\nЧтение из позиции 500 (должен быть Слон):\n";
		auto loadedElephant = storage.readAt(500);
		loadedElephant->toDescribe();
		loadedElephant->makeTheSound();

		cout << "\nЧтение из позиции 0 (должен быть Лев):\n";
		auto loadedLion = storage.readAt(0);
		loadedLion->toDescribe();

		cout << "\nЧтение из позиции 1000 (должен быть Пингвин):\n";
		auto loadedPenguin = storage.readAt(1000);
		loadedPenguin->toDescribe();

		storage.close();

		//Демонстрация обработки ошибки: позиция выходит за границы файла
		cout << "\nДемонстрация ошибки: выход за границы файла\n";
		storage.openExisting(fileName);
		try {
			cout << "Попытка чтения из позиции 99999\n";
			auto badAnimal = storage.readAt(99999);
		}
		catch (const out_of_range& e) {
			cout << "Ожидаемая ошибка поймана: " << e.what() << "\n";
		}
		storage.close();

		//Демонстрация обработки ошибки: повреждение данных (нарушение целостности)
		cout << "\nДемонстрация ошибки: повреждение данных (несовпадение checksum)\n";
		{
			//Намеренно портим файл, перезаписывая байты в середине записи Пингвина
			fstream corruptFile(fileName, ios::in | ios::out | ios::binary);
			corruptFile.seekp(1010); // Сдвигаемся немного внутрь данных пингвина
			char garbage[] = "XXXX";
			corruptFile.write(garbage, 4); // Затираем оригинальные данные
			corruptFile.close();
			cout << "Файл намеренно поврежден на байтовом уровне.\n";
		}

		storage.openExisting(fileName);
		try {
			cout << "Попытка чтения поврежденного объекта из позиции 1000\n";
			auto corruptedAnimal = storage.readAt(1000);
		}
		catch (const runtime_error& e) {
			cout << "Ожидаемая ошибка поймана: " << e.what() << "\n";
		}
		storage.close();

	}
	catch (const exception& e) {
		cerr << "Критическая ошибка: " << e.what() << "\n";
	}

	return 0;
}

//реализация функций

void writeString(ostream& out, const string& str) {
	uint64_t len = str.length(); //вычисляет длину строки
	out.write(reinterpret_cast<const char*>(&len), sizeof(len)); //записывает длину строки в файл
	out.write(str.c_str(), len); //записывает саму строку в файл
}

string readString(istream& in) {
	uint64_t len;//переменая для длины строки
	in.read(reinterpret_cast<char*>(&len), sizeof(len));//считываем в len длину строки
	if (in.fail()) throw runtime_error("Ошибка чтения длины строки"); //проверка на успешное проведение операции считывания

	string str(len, '\0'); //создаем строку str длины len и записывает в каждый элемент \0
	in.read(&str[0], len); //считываем из файла все данные в строку
	if (in.fail()) throw runtime_error("Ошибка чтения содержимого строки"); //проверка на успешное считывание
	return str; //возвращаем строку
}

uint32_t calculateChecksum(const char* data, size_t size) {
	uint32_t sum = 0; //переменная для суммы данных
	for (size_t i = 0; i < size; ++i) { //цикл проходится по каждому байту
		sum += static_cast<unsigned char>(data[i]); //прибавляет байт этой итерации к общей сумме
	}
	return sum; //возвращает сумму
}