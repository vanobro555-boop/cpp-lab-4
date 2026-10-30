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

	// Новый метод для демонстрации вызова специфической логики после загрузки
	virtual string getSpecificFeature() const = 0;

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

	virtual string getSpecificFeature() const override {
		return "Специфика: Скорость бега = " + to_string(m_runningSpeed) + " км/ч";
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

	virtual string getSpecificFeature() const override {
		return "Специфика: Размер ушей = " + to_string(m_earSize) + " см";
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

	virtual string getSpecificFeature() const override {
		return "Специфика: Размер стаи = " + to_string(m_flockSize) + " особей";
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
	
	virtual string getSpecificFeature() const override {
		return "Специфика: Высота прыжка = " + to_string(m_jumpHeight) + " м";
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

//класс для сериализцаии иерархии
class HierarchyStorage {
public:
	// Сохранение вектора разнородных объектов в бинарный файл
	void saveHierarchy(const string& fileName, const vector<unique_ptr<Animal>>& animals) {
		auto outFile = make_unique<fstream>(fileName, ios::out | ios::binary | ios::trunc);
		if (!outFile->is_open()) {
			throw runtime_error("Не удалось открыть файл для записи: " + fileName);
		}

		//Записываем количество объектов
		size_t count = animals.size();
		outFile->write(reinterpret_cast<const char*>(&count), sizeof(count));

		//Последовательно записываем каждый объект
		for (const auto& animal : animals) {
			writeString(*outFile, animal->getType()); // Сначала тег типа
			animal->save(*outFile);             // Затем данные объекта
		}

		if (outFile->fail()) {
			throw runtime_error("Ошибка при записи данных в файл");
		}
		// unique_ptr автоматически закроет файл
	}

	// Загрузка вектора разнородных объектов из бинарного файла
	void loadHierarchy(const string& fileName, vector<unique_ptr<Animal>>& animals) {
		// Очищаем вектор перед загрузкой
		animals.clear();

		auto inFile = make_unique<fstream>(fileName, ios::in | ios::binary);
		if (!inFile->is_open()) {
			throw runtime_error("Не удалось открыть файл для чтения: " + fileName);
		}

		//Читаем количество объектов
		size_t count;
		inFile->read(reinterpret_cast<char*>(&count), sizeof(count));
		if (inFile->fail()) {
			throw runtime_error("Ошибка чтения количества объектов. Файл поврежден или пуст.");
		}

		//Последовательно читаем каждый объект
		for (size_t i = 0; i < count; ++i) {
			string type = readString(*inFile);

			// Создаем объект нужного типа через фабрику
			unique_ptr<Animal> animal = AnimalFactory::create(type);

			// Загружаем специфичные данные в созданный объект
			animal->load(*inFile);

			if (inFile->fail()) {
				throw runtime_error("Ошибка чтения данных объекта №" + to_string(i + 1));
			}

			// Добавляем в вектор
			animals.push_back(move(animal));
		}
		// unique_ptr автоматически закроет файл (RAII)
	}
};

int main() {
	setlocale(LC_ALL, "RU");
	HierarchyStorage storage;
	const string fileName = "zoo_hierarchy.dat";

	cout << "Создание и заполнение коллекции разнородных объектов" << endl;
	vector<unique_ptr<Animal>> zoo;
	zoo.push_back(make_unique<Lion>(10, 100.0, "Panthera leo", 30.0));
	zoo.push_back(make_unique<Elephant>(5, 3000.0, "Loxodonta", 50.0));
	zoo.push_back(make_unique<Penguin>(3, 20.0, "Aptenodytes", 300));
	zoo.push_back(make_unique<Dolphin>(5, 50.0, "Delphinidae", 2.3));

	cout << "В коллекции " << zoo.size() << " животных." << endl;

	cout << "\nСохранение иерархии в бинарный файл" << endl;
	try {
		storage.saveHierarchy(fileName, zoo);
		cout << "Успешно сохранено в " << fileName << endl;
	}
	catch (const exception& e) {
		cout << "Ошибка сохранения: " << e.what() << endl;
		return 1;
	}

	cout << "\nОчистка коллекции (имитация перезапуска программы)" << endl;
	zoo.clear();
	cout << "Размер коллекции после очистки: " << zoo.size() << endl;

	cout << "\nЗагрузка иерархии из файла с восстановлением типов" << endl;
	try {
		storage.loadHierarchy(fileName, zoo);
		cout << "Успешно загружено " << zoo.size() << " животных." << endl;
	}
	catch (const exception& e) {
		cout << "Ошибка загрузки: " << e.what() << endl;
		return 1;
	}

	cout << "\nДемонстрация полиморфизма и вызова специфических методов" << endl;
	for (size_t i = 0; i < zoo.size(); ++i) {
		cout << "Объект #" << (i + 1) << " (Тип: " << zoo[i]->getType() << "):" << endl;

		// Полиморфный вызов общих методов
		zoo[i]->toDescribe();
		zoo[i]->makeTheSound();

		// Вызов специфического метода, который доказывает, что тип восстановлен корректно
		// и работают специфичные для подкласса данные
		cout << "  -> " << zoo[i]->getSpecificFeature() << endl;
	}

	cout << "\nДемонстрация обработки ошибки (файл не существует)" << endl;
	vector<unique_ptr<Animal>> emptyZoo;
	try {
		storage.loadHierarchy("nonexistent_file.dat", emptyZoo);
	}
	catch (const exception& e) {
		cout << "Ожидаемая ошибка поймана: " << e.what() << endl;
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
	\
	string str(len, '\0'); //создаем строку str длины len и записывает в каждый элемент \0
	in.read(&str[0], len); //считываем из файла все данные в строку
	if (in.fail()) throw runtime_error("Ошибка чтения содержимого строки"); //проверка на успешное считывание
	return str; //возвращаем строку
}