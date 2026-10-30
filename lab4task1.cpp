#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <stdexcept>

using namespace std;

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

	//метод, который возвращает в поток тег который показывает какой обект какого класса записан в файл
	virtual string getType() const = 0;

	//метод, который записывает поля класса родителя в поток
	virtual void save(ostream& out) const {
		out << m_age << " " << m_weight << " " << m_species << " ";
	}

	//метод, который считывает поля класса родителя из потока
	virtual void load(istream& in) {
		in >> m_age >> m_weight >> m_species;
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

	//записываем тег LION в поток
	virtual string getType() const override {
		return "LION";
	}

	//записывает данные атрибутов клсса Animal + спец. атрибут класса Lion в поток
	virtual void save(ostream& out) const override {
		Animal::save(out);
		out << m_runningSpeed << endl;
	}

	//читает данные атрибутов класса Aniaml + спец. атрибут класса Lion из потока
	virtual void load(istream& in) override {
		Animal::load(in);
		in >> m_runningSpeed;
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

	//записываем тег ELEPHANT в поток
	virtual string getType() const override {
		return "ELEPHANT";
	}

	//записывает данные атрибутов клсса Animal + спец. атрибут класса Elephant в поток
	virtual void save(ostream& out) const override {
		Animal::save(out);
		out << m_earSize << endl;
	}

	//читает данные атрибутов класса Aniaml + спец. атрибут класса Elephant из потока
	virtual void load(istream& in) override {
		Animal::load(in);
		in >> m_earSize;
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

	//записываем тег PENGUIN в поток
	virtual string getType() const override {
		return "PENGUIN";
	}

	//записывает данные атрибутов клсса Animal + спец. атрибут класса Penguin в поток
	virtual void save(ostream& out) const override {
		Animal::save(out);
		out << m_flockSize << endl;
	}

	//читает данные атрибутов класса Aniaml + спец. атрибут класса Penguin из потока
	virtual void load(istream& in) override {
		Animal::load(in);
		in >> m_flockSize;
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

	//записываем тег DOLPHIN в поток
	virtual string getType() const override {
		return "DOLPHIN";
	}

	//записывает данные атрибутов клсса Animal + спец. атрибут класса Dolphin в поток
	virtual void save(ostream& out) const override {
		Animal::save(out);
		out << m_jumpHeight << endl;
	}

	//читает данные атрибутов класса Aniaml + спец. атрибут класса Dolphin из потока
	virtual void load(istream& in) override {
		Animal::load(in);
		in >> m_jumpHeight;
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

//класс который записывает из потока информацию в файл или наоборот + обрабатывает все ошибки
class DataStorage {
public:

	//метод, который сохраняет информацию в файл
	void saveToFile(const string& fileName, const unique_ptr<Animal>* animals, int count) {
		//создаем указатель на поток ввода
		auto outFile = make_unique<ofstream>(fileName);

		//проверка на открытие файла
		if (!outFile->is_open()) {
			throw runtime_error("ошибка открытия файла - " + fileName);
		}

		*outFile << count << "\n"; //записываем в файл количество обьектов

		//основной цикл записи в файл
		for (int i = 0; i < count; i++) {
			*outFile << animals[i]->getType() << " "; //сначала записываем тег
			animals[i]->save(*outFile); //затем остальную информацию
		}

		//если по какой-то причине записи в файл не произойдет
		if (outFile->fail()) {
			throw runtime_error("Ошибка при записи в файл" + fileName);
		}
	}

	//метод который читает информацию из файла в поток
	void loadFromFile(const string& fileName, unique_ptr<Animal>* animals, int& count) {
		//создаем указатель на поток вывода
		auto inFile = make_unique<ifstream>(fileName);

		if (!inFile->is_open()) {
			throw runtime_error("ошибка открытия файла - " + fileName);
		}

		int loadedCount;
		*inFile >> loadedCount;

		//если файл поврежден или он вообще пустой
		if (inFile->fail() || loadedCount <= 0) {
			throw runtime_error("Ошибка: файл поврежден или он пуст " + fileName);
		}

		//основной цикл чтения из файла в поток
		for (int i = 0; i < loadedCount; i++) {
			string type;
			//считываем тег
			*inFile >> type;

			if (inFile->fail()) {
				throw runtime_error("Ошибка: файл поврежден или не удалось прочитать тег обьекта " + to_string(i + 1));
			}

			//создаем обьект по тегу
			animals[i] = AnimalFactory::create(type);

			//загружаем данные в обьект из файла
			animals[i]->load(*inFile);

			if (inFile->fail()) {
				throw runtime_error("Ошибка: не удалось прочитать данные объекта " + to_string(i + 1));
			}
		}
		count = loadedCount;
	}
};

int main() {
	setlocale(LC_ALL, "RU");

	DataStorage storage;
	const int MAX_ANIMALS = 4;

	//массив умных указателей на обьекты
	unique_ptr<Animal> zoo[MAX_ANIMALS];

	zoo[0] = make_unique<Lion>(10, 100.0, "лев", 30.0);
	zoo[1] = make_unique<Elephant>(5, 3000.0, "слон", 50.0);
	zoo[2] = make_unique<Penguin>(3, 20.0, "пингвин", 300);
	zoo[3] = make_unique<Dolphin>(5, 50.0, "дельфин", 2.3);

	//полиморфные вызовы
	for (int i = 0; i < MAX_ANIMALS; i++) {
		zoo[i]->toDescribe();
		zoo[i]->makeTheSound();
		cout << endl;
	}

	//опасная зона
	try {
		storage.saveToFile("zoo.txt", zoo, MAX_ANIMALS);
		cout << "Зоопарк успешно сохранён в файл zoo.txt!" << endl << endl;
	}
	//разбираемся с ошибками
	catch (const exception& e) {
		cout << "Ошибка сохранения: " << e.what() << endl << endl;
	}

	unique_ptr<Animal> loadedZoo[MAX_ANIMALS];
	int loadedCount = 0; // Будет обновлен методом loadFromFile

	try {
		storage.loadFromFile("zoo.txt", loadedZoo, loadedCount);
		cout << "Зоопарк успешно загружен! Животных: " << loadedCount << endl << endl;

		for (int i = 0; i < loadedCount; i++) {
			loadedZoo[i]->toDescribe();
			loadedZoo[i]->makeTheSound();
			cout << endl;
		}
	}
	catch (const exception& e) {
		cout << "Ошибка загрузки: " << e.what() << endl << endl;
	}

	//демонстрация, когда файл не существует
	try {
		unique_ptr<Animal> empty[MAX_ANIMALS];
		int dummyCount = 0;
		storage.loadFromFile("nonexistent_file.txt", empty, dummyCount);
	}
	catch (const exception& e) {
		cout << "Ожидаемая ошибка поймана: " << e.what() << endl << endl;
	}

	//демонстрация, когда файл поврежден
	{
		ofstream badFile("bad_zoo.txt");
		badFile << "это не число, а мусор";
		badFile.close();
	}

	try {
		unique_ptr<Animal> empty[MAX_ANIMALS];
		int dummyCount = 0;
		storage.loadFromFile("bad_zoo.txt", empty, dummyCount);
	}
	catch (const exception& e) {
		cout << "Ожидаемая ошибка поймана: " << e.what() << endl << endl;
	}

	return 0;
}