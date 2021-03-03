#pragma once
#include <string>

class Person
{
public:
	Person(std::string newName = "noname");
	Person(const Person& other);
	Person(const Person&& other) noexcept;
	Person& operator=(const Person& other);
	Person& operator=(Person&& other) noexcept;
	~Person();
	const std::string& Name() const;
	std::string& SetName(const std::string newName = "noname");
	static const int Size();
	int& SetId(const int id = 0);
	const int Id() const;
	static int counter;
private:
	int id;
	std::string name;
};





