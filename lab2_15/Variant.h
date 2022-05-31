#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

enum Types
{
	string = 1, charr, intt, floatt, doublee, booll
};



class Variant
{
	Types var;
	std::string str;

	void FindType(std::string str);
	template <typename T>
	std::string toString(T val);
	template<typename T>
	T fromString(const std::string& s);

public:
	Variant();
	Variant(std::string str);
	Variant(char ch);
	Variant(int num);
	Variant(float num);
	Variant(double num);
	Variant(bool bo);
	void PrintType();
	std::string ToString();
	char ToChar();
	int ToInt();
	float ToFloat();
	double ToDouble();
	bool ToBool();
	void Converse(Types type);

	friend std::istream& operator>>(std::istream& is, Variant& var);
	friend std::ostream& operator<<(std::ostream& os, Variant& var);
	Variant& operator=(Variant& rim);
	bool operator==(Variant rim);
	bool operator!=(Variant rim);
	operator std::string();
	operator char();
	operator int();
	operator float();
	operator double();
	operator bool();

};

