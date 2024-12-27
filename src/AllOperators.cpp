// Header files needed by the program
#include "../h/AllOperators.h" // Defines the AllOperators class and related methods
#include "../h/ErrorHandler.h" // Handles errors in the program

// Pointer to hold a global instance of AllOperators
AllOperators *ops = nullptr;

// Function to create a new operator object
// Takes the operator's text representation, left and right precedences, and a flag for overloadability
Operator opCreate(string textIn, int leftPrecedenceIn, int rightPrecedenceIn, bool overloadableIn);

// Constructor method to initialize the global AllOperators instance
void AllOperators::init()
{
	// Allocate memory for a new AllOperators instance and assign it to the global pointer
	ops = new AllOperators();
}

// Constructor for the AllOperators class
// Responsible for populating the operators map with all predefined operators
AllOperators::AllOperators()
{
// Undefine the macro DECLARE_OP to avoid any conflicts with existing definitions
#undef DECLARE_OP

// Define the macro DECLARE_OP to call the putOpInMap method for adding operators to the map
#define DECLARE_OP(name, text, prece, input, overload) putOpInMap(name);

	// Call the ALL_OPS macro, which presumably expands to a list of DECLARE_OP calls
	ALL_OPS;
}

// Adds an operator to the operators map
// Maps the operator's text representation to the operator object
void AllOperators::putOpInMap(Operator op)
{
	opsMap[op->getText()] = op; // Use the text of the operator as the key in the map
}

// Retrieves all matching operators from a given text string and stores them in the output vector
void AllOperators::get(string text, vector<Operator> &out)
{
	int start = 0;		   // Starting index of the current substring
	int end = text.size(); // Ending index of the substring (initially the entire string)

	// Loop through the entire text string
	while (start < int(text.size()))
	{
		// Find the longest matching operator from the text
		while (true)
		{
			// If no match is found for the current substring
			if (end <= start)
			{
				// Log an error and exit the loop
				error.log("unknown operator '" + text + "'", SOURCE_ERROR);
			}

			// Try to find the current substring in the operators map
			auto i = opsMap.find(text.substr(start, end - start));

			if (i == opsMap.end()) // If the substring is not in the map
			{
				end--; // Reduce the substring length and try again
			}
			else // If a match is found
			{
				out.push_back(i->second); // Add the matching operator to the output vector
				start = end;			  // Move the start pointer to the end of the matched substring
				end = text.size();		  // Reset the end pointer to the full remaining text
				break;					  // Exit the inner loop
			}
		}
	}
}

// Checks if the given operator is an opening bracket
bool AllOperators::isOpenBrac(Operator op)
{
	return op == openPeren || op == openSqBrac || op == openCrBrac; // Returns true for parentheses, square, or curly braces
}

// Checks if the given operator is a closing bracket
bool AllOperators::isCloseBrac(Operator op)
{
	return op == closePeren || op == closeSqBrac || op == closeCrBrac; // Returns true for parentheses, square, or curly braces
}
