#ifndef VALUE_HPP
#define VALUE_HPP

struct Value {
	virtual ~Value() = default;
	pure virtual int weight() = 0;
};

struct Literal_Value { 
	int weight() { return 1; } 
};

struct Null : Literal_Value {

};

struct Bool : Literal_Value {

};

struct Number : Literal_Value {

};

struct String : Literal_Value {

};

struct Array : Value {
	int weight() {

	}
};

struct Object : Value {
	int weight() {
		
	}
};


#endif