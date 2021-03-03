#include "Person.h"

Person::Person(std::string newName) : name(newName) {
	id = counter++;
}

Person::~Person() {
	counter--;
}

Person::Person(const Person& other) {
	id = other.id;
	name = other.name;
}

Person::Person(const Person&& other) noexcept{
	id = other.id;
	name = other.name;
}

Person& Person::operator=(const Person& other) {
	id = other.id;
	name = other.name;
	return *this;
}

Person& Person::operator=(Person&& other) noexcept{
	id = other.id;
	name = other.name;
	return *this;
}

const std::string& Person::Name() const {
	return name;
}

std::string& Person::SetName(const std::string newName) {
	name = newName;
	return name;
}

const int Person::Size() {
	return counter;
}

const int Person::Id() const {
	return id;
}

int& Person::SetId(const int newId) {
	id = newId;
	return id;
}