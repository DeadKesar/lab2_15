#include "Variant.h"


Variant::Variant()
{
	this->str = "";
	this->var = string;
}
Variant::Variant(std::string str) : str(str)
{
	FindType(str);
}
Variant::Variant(char ch)
{
	this->str = ch;
	this->var = charr;
}
Variant::Variant(int num)
{
	this->str = std::to_string(num);
	this->var = intt;
}
Variant::Variant(float num)
{
	this->str = std::to_string(num);
	this->str += 'f';
	this->var = floatt;
}
Variant::Variant(double num)
{
	this->str = std::to_string(num);
	this->var = doublee;
}
Variant::Variant(bool bo)
{
	if (bo)
		this->str = "true";
	else
		this->str = "false";
	this->var = booll;
}
void Variant::FindType(std::string str)
{
	bool dot = false, isNumber = true;
	//1 - строка, 2 - символ, 3 - int, 4 - fload, 5 - double, 6 - bool
	int n = str.length();
	if (n == 0) // пустая строка
	{
		this->var = string;
		return;
	}
	if (n == 1)
	{
		if (str[0] >= '0' && str[0] <= '9')
		{
			this->var = intt;
			return; // цифра
		}
		this->var = charr;
		return; // символ
	}
	if (str == "false" || str == "true")
	{
		this->var = booll;
		return;
	}
	for (int i = 0; i < n; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			continue;
		}
		else if (str[i] == '.' && !dot)
		{
			dot = true;
			continue;
		}
		else if (str[i] == '.' && dot)
		{
			this->var = string;
			return; // если 2 точки
		}
		else if (i + 1 == n && tolower(str[i]) == 'f')
		{
			this->var = floatt;
			return; // float так как f на конце
		}
		else
		{
			this->var = string;
			return;
		}
	}
	if (dot)
	{
		this->var = doublee;
		return; // double по умолчанию
	}
	this->var = intt;
	return;
}
template <typename T>
std::string Variant::toString(T val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}
template<typename T>
T Variant::fromString(const std::string& s)
{
	std::istringstream iss(s);
	T res;
	iss >> res;
	return res;
}
void Variant::PrintType()
{
	switch (this->var)
	{
	case string:
		std::cout << "строка" << std::endl;
		break;
	case charr:
		std::cout << "символ" << std::endl;
		break;
	case intt:
		std::cout << "целое чило" << std::endl;
		break;
	case floatt:
		std::cout << "число с плавающей точкой" << std::endl;
		break;
	case doublee:
		std::cout << "число с плавающей точкой двойной точности" << std::endl;
		break;
	case booll:
		std::cout << "булево значение" << std::endl;
		break;
	}
}
std::string Variant::ToString()
{
	return this->str;
}
char Variant::ToChar()
{
	if (this->str.length() == 1)
	{
		return this->str[0];
	}
	else if (this->var == booll)
	{
		if (this->str == "true")
			return '1';
		else
			return '0';
	}
	throw std::logic_error("приведение не возможно");
}
int Variant::ToInt()
{
	Types temp = this->var;
	this->FindType(this->str);
	if (this->var == string)
	{
		this->var = temp;
		throw std::logic_error("приведение не возможно");
	}
	if (this->var == charr)
	{
		return (int)this->str[0];
	}
	if (this->var == intt)
	{
		return fromString<int>(this->str);
	}
	if (this->var == floatt)
	{
		this->str.pop_back();
		return (int)fromString<float>(this->str);
	}
	if (this->var == doublee)
	{
		return (int)fromString<double>(this->str);
	}
	if (this->var == booll)
	{
		{
			if (this->str == "true")
				return 1;
			else
				return 0;
		}
	}
}
float Variant::ToFloat()
{
	Types temp = this->var;
	this->FindType(this->str);
	if (this->var == string)
	{
		this->var = temp;
		throw std::logic_error("приведение не возможно");
	}
	if (this->var == charr)
	{
		return (float)this->str[0];
	}
	if (this->var == intt)
	{
		return (float)fromString<int>(this->str);
	}
	if (this->var == floatt)
	{
		this->str.pop_back();
		return fromString<float>(this->str);
	}
	if (this->var == doublee)
	{
		return (float)fromString<double>(this->str);
	}
	if (this->var == booll)
	{
		{
			if (this->str == "true")
				return 1.0f;
			else
				return 0.0f;
		}
	}
}
double Variant::ToDouble()
{
	Types temp = this->var;
	this->FindType(this->str);
	if (this->var == string)
	{
		this->var = temp;
		throw std::logic_error("приведение не возможно");
	}
	if (this->var == charr)
	{
		return (double)this->str[0];
	}
	if (this->var == intt)
	{
		return (double)fromString<int>(this->str);
	}
	if (this->var == floatt)
	{
		this->str.pop_back();
		return (double)fromString<float>(this->str);
	}
	if (this->var == doublee)
	{
		return fromString<double>(this->str);
	}
	if (this->var == booll)
	{
		{
			if (this->str == "true")
				return 1.0;
			else
				return 0.0;
		}
	}
}
bool Variant::ToBool()
{
	Types temp = this->var;
	this->FindType(this->str);
	if (this->var == string)
	{
		this->var = temp;
		throw std::logic_error("приведение не возможно");
	}
	if (this->var == charr)
	{
		return (bool)this->str[0];
	}
	if (this->var == intt)
	{
		return (bool)fromString<int>(this->str);
	}
	if (this->var == floatt)
	{
		this->str.pop_back();
		return (bool)fromString<float>(this->str);
	}
	if (this->var == doublee)
	{
		return (bool)fromString<double>(this->str);
	}
	if (this->var == booll)
	{
		if (this->str == "true")
			return true;
		return false;
	}
}
void Variant::Converse(Types type)
{
	try {
		switch (type)
		{
		case string:
			this->str = (std::string)*this;
			this->var = string;
			break;
		case charr:
			this->str = (char)*this;
			this->var = charr;
			break;
		case intt:
			this->str = std::to_string((int)*this);
			this->var = intt;
			break;
		case floatt:
			this->str = std::to_string((float)*this);
			this->var = floatt;
			break;
		case doublee:
			this->str = std::to_string((double)*this);
			this->var = doublee;
			break;
		case booll:
			this->str = std::to_string((bool)*this);
			if (this->str == "1")
			{
				this->str = "true";
			}
			else
			{
				this->str = "false";
			}
			this->var = booll;
			break;
		default:
			break;
		}
	}
	catch (std::logic_error mes) {
		std::cout << mes.what();
	}
}

Variant& Variant::operator=(Variant& var)
{
	this->str = var.str;
	this->var = var.var;
	return *this;
}
bool Variant::operator==(Variant var)
{
	if (this->str == var.str)
		return true;
	return false;
}
bool Variant::operator!=(Variant var)
{
	if (this->str != var.str)
		return true;
	return false;
}
Variant::operator std::string()
{
	return this->ToString();
}
Variant::operator char()
{
	return this->ToChar();
}
Variant::operator int()
{
	return this->ToInt();
}
Variant::operator float()
{
	return this->ToFloat();
}
Variant::operator double()
{
	return this->ToDouble();
}
Variant::operator bool()
{
	return this->ToBool();
}
std::ostream& operator<<(std::ostream& os, Variant& var)
{
	os << var.str;
	return os;
}
std::istream& operator>>(std::istream& is, Variant& var)
{
	std::getline(is, var.str);
	var.FindType(var.str);
	return is;
}