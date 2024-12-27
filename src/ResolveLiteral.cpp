#include "../h/Action.h"	   // Include header for Action class
#include "../h/Token.h"		   // Include header for Token class
#include "../h/ErrorHandler.h" // Include header for error handling
#include "../h/Namespace.h"	   // Include header for Namespace class

extern Namespace globalNamespace; // Declare external global namespace

// Function to resolve an integer literal token
Action resolveIntLiteral(Token token, Type type)
{
	string in = token->getText(); // Get the text representation of the token

	int val = 0; // Initialize the integer value to 0

	// Loop through each character in the token text
	for (auto i = in.begin(); i != in.end(); ++i)
	{
		// Check if the character is a valid digit
		if (*i < '0' || *i > '9')
		{
			// Log an error if an invalid character is found in the integer
			error.log(string() + "bura character '" + *i + "' number '" + in + "' mein mila", SOURCE_ERROR, token);
			return nullptr; // Return nullptr on error
		}

		// Update the integer value by multiplying by 10 and adding the current digit
		val = val * 10 + (*i - '0');
	}

	// If the type is Bool, convert the integer value to a boolean (0 -> false, non-zero -> true)
	if (type == Bool)
	{
		bool out = (val != 0);
		return constGetAction(&out, type, token->getText(), globalNamespace); // Return the boolean literal as an action
	}
	else
	{
		// If the type is not Bool, return the integer literal as an action
		int out = val;
		return constGetAction(&out, type, token->getText(), globalNamespace);
	}
}

// Function to resolve a double literal token
Action resolveDubLiteral(Token token)
{
	string in = token->getText(); // Get the text representation of the token

	double val = 0;	  // Initialize the double value to 0
	int pointPos = 0; // Initialize position of decimal point

	// Loop through each character in the token text
	for (auto i = in.begin(); i != in.end(); ++i)
	{
		if (*i == '.' || *i == '_')
		{
			if (pointPos == 0)
			{
				pointPos = 10; // Mark the position of the decimal point
			}
			else
			{
				// Log an error if multiple decimal points are found in the number
				error.log(string() + "multiple decimal points number '" + in + "' mein hain", SOURCE_ERROR, token);
				return voidAction; // Return void action on error
			}
		}
		else if (*i >= '0' && *i <= '9')
		{
			if (pointPos)
			{
				// Update the double value after the decimal point
				val += (double)(*i - '0') / pointPos;
				pointPos *= 10; // Increase the precision for subsequent digits
			}
			else
			{
				val = val * 10 + (*i - '0'); // Update the integer part of the number
			}
		}
		else
		{
			// Log an error if an invalid character is found in the number
			error.log(string() + "bura character '" + *i + "' number '" + in + "' mein mila", SOURCE_ERROR, token);
			return voidAction; // Return void action on error
		}
	}

	double out = val;													 // Store the final value
	return constGetAction(&out, Dub, token->getText(), globalNamespace); // Return the double literal as an action
}

string dlcnStr2CppStr(void *obj);
void *cppStr2dlcnStr(string cpp);

// Function to resolve a string literal token
Action resolveStringLiteral(Token token)
{
	string text = token->getText(); // Get the text representation of the token

	// This nonsense is required because the lexer includes the first quote but not the last one
	// Instead of hardcoding, make it flexible so that things don't break when the lexer is fixed
	while (text.size() > 0 && text[0] == '"')
		text = text.substr(1, string::npos); // Remove leading quote

	while (text.size() > 0 && text[text.size() - 1] == '"')
		text = text.substr(0, text.size() - 1); // Remove trailing quote

	void *obj = cppStr2dlcnStr(text); // Convert C++ string to DesiLang string format

	return constGetAction(obj, String, "\"" + text + "\"", globalNamespace); // Return the string literal as an action
}

// Main function to resolve a literal token based on its type
Action resolveLiteral(Token token)
{
	if (token->getType() == TokenData::STRING_LITERAL)
	{
		return resolveStringLiteral(token); // If it's a string literal, resolve it
	}

	if (token->getType() != TokenData::LITERAL)
	{
		// Throw an error if the token is not a literal
		throw DesiLangError(FUNC + " ko token pe call kiya gaya jo literal nahi hai", INTERNAL_ERROR, token);
	}

	string in = token->getText(); // Get the text representation of the token

	if (in.empty())
		return nullptr; // Return nullptr if the token is empty

	Type type = Unknown; // Initialize the type as Unknown

	if (in.empty())
	{
		// Log an error if an empty string is passed as a literal
		error.log("literal banane ka try kiya, lekin string khali thi", INTERNAL_ERROR, token);
	}

	// Check if the literal starts with a number or a decimal point
	if ((in[0] >= '0' && in[0] <= '9') || in[0] == '.')
	{
		type = Int; // Initially assume it's an integer

		// Loop through the text to check if it contains a decimal point or underscore
		for (auto i = in.begin(); i != in.end(); ++i)
		{
			if (*i == '.' || *i == '_')
			{
				type = Dub; // If decimal point or underscore is found, treat it as a double
				break;
			}
		}

		// Check if the last character indicates a specific type (d/f for double, i for int, b for bool)
		if (in.back() == 'd' || in.back() == 'f')
		{
			type = Dub;	   // It's a double
			in.pop_back(); // Remove the last character (d/f)
		}
		else if (in.back() == 'i')
		{
			type = Int;	   // It's an integer
			in.pop_back(); // Remove the last character (i)
		}
		else if (in.back() == 'b')
		{
			type = Bool;   // It's a boolean
			in.pop_back(); // Remove the last character (b)
		}
	}

	// Resolve the literal based on its type
	if (type == Int)
	{
		return resolveIntLiteral(token, type); // Resolve as an integer
	}
	else if (type == Dub) // If it's a floating point number
	{
		return resolveDubLiteral(token); // Resolve as a double
	}
	else
	{
		// Throw an error if the literal type is invalid
		throw DesiLangError("literal banane ki kosis ki gayi galat type ke saath: " + type->getString(), INTERNAL_ERROR, token);
	}
}
