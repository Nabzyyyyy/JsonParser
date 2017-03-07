#include "value.hpp"
#include <assert.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include "Parse.hpp"

std::string JsonParser::print(Value* val) { // print function called from the helper function

	if (val->kind() == Literal_Kind) { //determines the type of value as Literal
		Literal_Value* litValPtr = dynamic_cast<Literal_Value*>(val); // for string for key
		return litValPtr->print(); // returns what to print
	}

	else if (val->kind() == Array_Kind) { // determines type of value as Array
		Array_Val* arrPtr = dynamic_cast<Array_Val*>(val); // for string for key
		std::string arrStr = "[\n"; // creates a [ character to signify this is an array to be printed and creates a new line
		indent++; // increments indent for pretty printer
		for(std::vector<Value*>::iterator it = (*arrPtr).begin(); it != (*arrPtr).end(); ++it) { // iterates through array and calls print recursively
			for (int i = 0; i < indent; i++) {
				arrStr += "\t"; // indents as much as neccessary
			}
			arrStr += print(*it);
			arrStr += (*it != (*arrPtr).back() ? ",\n" : "\n");
		}
		indent--; // decriment indent after complete
		for (int i = 0; i < indent; i++) { // indents as much as necessary to add the ] to arrStr
				arrStr += "\t";
			}
		arrStr += "]";
		return arrStr; // returns the array to the vector to print later
	}

	else if (val->kind() == Object_Kind) { // determines typ eof value as Object
		Object_Val* objPtr = dynamic_cast<Object_Val*>(val); // for string for key
		std::string objStr = "{\n";
		indent++; // increments indents for pretty printer
		for(std::vector<std::pair<std::string, Value*>>::iterator it = (*objPtr).begin(); it != (*objPtr).end(); ++it) { // iterates through object and calls print recursively
			for (int i = 0; i < indent; i++) { // indents before adding objects to string
				objStr += "\t";
			}
			objStr += (*it).first; 	// creates format for displaying object
			objStr += ": ";
			objStr += print((*it).second);
			objStr += (*it != (*objPtr).back() ? ",\n" : "\n");
		}
		indent--; // decriments indent to display closing curly brace
		for (int i = 0; i < indent; i++) {
				objStr += "\t";
			}
		objStr += "}"; // adds curly brace to string
		return objStr; // returns the object string
	}

	else {
		err = "Error when defining kind in print."; // some kind of error happened -- debuggings
		throwException(err);
	}

}

void JsonParser::print() { // helper print function iterates through the entire json document and then outputs the entire document in pretty form
	std::string outputStr = "";
	for(std::vector<Value*>::iterator it = tree.begin(); it != tree.end(); ++it) {
		outputStr += print(*it);
		outputStr += "\n";
	}
	std::cout << outputStr << std::endl;
}

void JsonParser::throwException(std::string err) { // throws exception with string err assigned before exception is thrown
 	//std::cout << err << std::endl;
 	throw std::runtime_error(err); // throw runtime error with string of whatever error it is
}

void JsonParser::Parse(std::string str) { // helper function to assign string iterators and call the private Parse function
	std::string::iterator f = str.begin();
	std::string::iterator l = str.end();

	// loop until end. 
	// assigned parse to value or whatever

	while (f != l)
		tree.push_back(Parse(f, l));
}

Value *  JsonParser::Parse(std::string::iterator &f, std::string::iterator &l) { // the actual parse function that will be called by the helper function and by the Parse array/object functions
	

	while ((*f == ' ' || *f == ':' || *f == ',' || *f == '\n' || *f == '\t' || *f == '\v') && f != l) {
		f++;
	}

	if(f != l) { // calls correct Parse function
		switch(*f) {
			case '{': return Parse_Object(f, l); 
			case '[': return Parse_Array(f, l); 
			case '"': return Parse_String(f, l); 
			case 't': return Parse_Bool(f, l); 
			case 'f': return Parse_Bool(f, l); 
			case 'n': return Parse_Null(f, l); 
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '-': return Parse_Number(f, l);
			default: {
				err = "Issue with parsing. Who knows what it.";
				throwException(err);
				break;
			}
		}

	}

}


Value * JsonParser::Parse_Null(std::string::iterator &f, std::string::iterator &l) { // Parses a null value pointer
	if (*f=='n') f++; // ensures each character is "null"
	else {
		err = "Receieved unexpected char. Expected char was 'n' in null value.";
		throwException(err); 
	}

	if (*f=='u') f++;
	else {
		err = "Receieved unexpected char. Expected char was 'u' in null value.";
		throwException(err); 
	}

	if (*f=='l') f++;
	else {
		err = "Receieved unexpected char. Expected char was 'l' in null value.";
		throwException(err); 
	}

	if (*f=='l') f++;
	else {
		err = "Receieved unexpected char. Expected char was 'l' in null value.";
		throwException(err); 
	}

	//std::string str = "null";

	Null_Val * ptr = new Null_Val();

	++weight; // increment weight 

	return ptr; // return the null value pointer
}


Value * JsonParser::Parse_Number(std::string::iterator &f, std::string::iterator &l) {
	bool cont = true;
	//std::string num = *f;
	
	Num_Val * ptr = new Num_Val();

	while (cont && f != l) { // while not end of file and there are still digits to parse
		
		switch(*f) {
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
				ptr->numVal += *f;
				f++;
				continue;
			}
			default: cont = false;
		}
	}

	++weight; // increment weight

	return ptr; // return the parsed number
}

Value * JsonParser::Parse_Bool(std::string::iterator &f, std::string::iterator &l) { 
	assert(*f=='t' || *f=='f'); // assert that it's a true or false
	//std::string b = *f;
	Bool_Val * ptr = new Bool_Val();

	//consume the character
	if (*f == 't') { // if true, skip the four characters 'true'
		ptr->value = true;
		f++;
		f++;
		f++;
		f++;
	}
	else if (*f == 'f') { // if false, skip the 5 characters 'false'
		ptr->value = false;
		f++;
		f++;
		f++;
		f++;
		f++;
	}

	++weight; // increment weight

	return ptr; // return the parsed bool value
}

Value * JsonParser::Parse_String(std::string::iterator &f, std::string::iterator &l) { // parse string function
	assert(*f == '"'); // ensure string's beginning quote
	String_Val * ptr = new String_Val(); // create the string value pointer
	//consume the " and go to next
	f++; // increment the pointer

	ptr->strVal = ""; // initialize the string

	while(f != l && *f != '"') { // if it's not the end of file and we're not at the end of the quote
		if (*f == '\\') // increment and add the character to the string
			f++;
		ptr->strVal += *f; //strcat(str, *f);
		f++; 
	}

	f++; // incremement past the last quote

	++weight; // increment weight

	return ptr; // return the parsed string Value pointer
}

Value * JsonParser::Parse_Array (std::string::iterator &f, std::string::iterator &l) { // parse array value pointer
	
	assert(*f == '['); // ensure beginning of array
	Array_Val * arr = new Array_Val(); 
	f++;
	Value * val;
	
	//loop until ] or eof
	while (f != l && *f != ']') { // if not end of array and not at eof
		val = Parse(f, l); // for value pair

		(*arr).push_back(val); 
	}

	f++;
	++weight; // increment weight

	return arr; // return the array 
}

Value * JsonParser::Parse_Object (std::string::iterator &f, std::string::iterator &l) { // Parse object value pointer
	assert(*f == '{'); // ensure beginning of object
	Object_Val * obj = new Object_Val(); 
	f++;
	String_Val * strValue; // string value pointer for key 
	Value * val; // Value pointer

	//loop until } or eof
	while (f != l && *f != '}') { // while not end of file and not at end of object, do the things
		strValue = dynamic_cast<String_Val*>(Parse(f, l)); // for string for key
		--weight; // decriment weight because Parsing a string for key value pair will add 1 extra to weight for every object
		val = Parse(f, l); // for value pair

		(*obj).push_back(std::make_pair(strValue->strVal, val));
	}

	f++;
	++weight;

	return obj;
}

int main() {
// std::stringstream
	// parse helper
std::string strIn; // 
std::stringstream strStream; // Json

while(std::getline(std::cin, strIn)) { 	// while there's standard input
	strStream << strIn; // append the string to the stream
}

JsonParser j; // creates object of type JsonParser

j.Parse(strStream.str()); // adds strings to the string stream 

std::cout << "Weight of Json document: " << j.getWeight() << std::endl; // otputs the weight of the json document

j.print(); // pretty print the json doc

return 0;
}