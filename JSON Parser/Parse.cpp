#include "value.hpp"
#include <assert.h>
#include <string>

// create vector of Value pointers
// object or array should be a vector with key value pairs
// main that calls parse
	// object and array will call parse recursively 



void throwException(string err) {
	throw std::runtime_error(err);
}

int weight = 0;

Value * Parse_Null(char* f, char* l) {
	assert(*f=='N');

	
}

Value * Parse_Number(char* f, char* l) {
	assert(isdigit(*f));
	bool cont = true;
	std::string num = *f;

	while (cont && *f != *l) {
		
		switch(*f)
			case '-':
			case '+':
			case '.':
			case 'e':
			case 'E':
			case '0':
			case '1': 
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': {
				strcat(num, *f);
			}
			default: cont = false;
	}

	++weight;
}

Value * Parse_Bool(char* f, char* l) {
	assert(*f=='T' || *f=='F');
}

Value * Parse_String(char* f, char* l) {
	assert(*f == '"');
}

Value * Parse_Array (char* f, char* l) {
	assert(*f == '[');
}

Value * Parse_Object (char* f, char* l) {
	assert(*f == '{');
}

// ignore spaces
//case statement for each character?



// ignore spaces

/* 
things to parse:
[space] -> ignore
{} -> parse_object
[] -> parse_array
"string" -> parse_String
: -> ignore
True -> parse_Bool
False -> parse_Bool
Null -> parse_Null
numbers -> parse_Number
[space] -> ignore

*/