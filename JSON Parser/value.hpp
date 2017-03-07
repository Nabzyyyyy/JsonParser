#ifndef VALUE_HPP
#define VALUE_HPP

#include <utility>
#include <string>
#include <cstring>
#include <vector>

enum valueKind { Literal_Kind, Array_Kind, Object_Kind };

struct Value {
	virtual ~Value() = default;
	virtual int kind() = 0;
};

struct Literal_Value : Value { 
	virtual std::string print() = 0; 
	int kind() {
		return Literal_Kind;
	}
};

struct Null_Val : Literal_Value {
	std::string print() {return "null"; }
};

struct Bool_Val : Literal_Value {
	bool value;
	std::string print() {return value ? "true" : "false"; }
};

struct Num_Val : Literal_Value {
	std::string numVal;
	std::string print() { return numVal; }
};

struct String_Val : Literal_Value {
	std::string strVal;
	std::string print() { return "\"" + strVal + "\"" ; }
};

struct Array_Val : Value, std::vector<Value*> {
	using std::vector<Value*>::vector;
	int kind() {
		return Array_Kind;
	}
};

struct Object_Val : Value, std::vector<std::pair<std::string, Value*>> {
	using std::vector<std::pair<std::string, Value*>>::vector;
	int kind() {
		return Object_Kind;
	}
};


#endif