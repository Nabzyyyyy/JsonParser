#ifndef PARSE_HPP
#define PARSE_HPP

class JsonParser {

private: 
	Value* Parse(std::string::iterator&, std::string::iterator&);
	Value* Parse_Null(std::string::iterator&, std::string::iterator&);
	Value* Parse_Number(std::string::iterator&, std::string::iterator&);
	Value* Parse_Bool(std::string::iterator&, std::string::iterator&);
	Value* Parse_String(std::string::iterator&, std::string::iterator&);
	Value* Parse_Array(std::string::iterator&, std::string::iterator&);
	Value* Parse_Object(std::string::iterator&, std::string::iterator&);
	void throwException(std::string err);
	int weight = 0; // weight for json document
	std::string err = ""; // error for throwing runtime errors
	std::vector<Value*> tree; // the vector for holding the tree of Value pointers
	std::string print(Value* val); // pretty printer to call from helper function 
	int indent = 0;

public:// (std::string::iterator&, std::string::iterator&)
	void Parse(std::string); // helper function for prase
	int getWeight() {return weight;} // getter for the weight
	void print(); // pretty printer helper function for outputting the json document in a readable format

};

#endif