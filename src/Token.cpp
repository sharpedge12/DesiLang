#include "../h/Token.h"				// Include header for Token class
#include "../h/msclStringFuncs.h"	// Include header for string utility functions
#include "../h/utils/stringUtils.h" // Include header for additional string utilities

// Function to create a Token with the provided text and additional properties
Token makeToken(string textIn, shared_ptr<SourceFile> fileIn, int lineIn, int charPosIn, TokenData::Type tokenTypeIn, Operator opIn)
{
	// If the input text starts with a double quote and does not end with one, append the ending quote
	if (str::hasPrefix(textIn, "\"") && !str::hasSuffix(textIn, "\""))
		textIn += "\""; // Ensure that the string literal is properly closed

	// Return a new Token object created with the given properties
	return Token(new TokenData(textIn, fileIn, lineIn, charPosIn, tokenTypeIn, opIn));
}

// Overloaded function to create a Token with just text (default values for other properties)
Token makeToken(string textIn)
{
	// Return a new Token with the given text, and default properties like no file, line number, or operator
	return Token(new TokenData(textIn, nullptr, 0, 0, TokenData::IDENTIFIER, Operator(nullptr)));
}

// Converts a TokenData Type to its corresponding string representation
string TokenData::typeToString(TokenData::Type in)
{
	// Switch based on the token type and return the corresponding string representation
	switch (in)
	{
	case WHITESPACE:
		return "whitespace";
	case LINE_END:
		return "newline";
	case IDENTIFIER:
		return "identifier";
	case LITERAL:
		return "literal";
	case STRING_LITERAL:
		return "string literal";
	case OPERATOR:
		return "operator";
	case LINE_COMMENT:
		return "single line comment";
	case BLOCK_COMMENT:
		return "block comment";
	case SCOPE:
		return "scope";
	case UNKNOWN:
		return "UNKNOWN";
	default:
		return "ERROR GETTING TOKEN TYPE"; // Default case for unknown types
	}
}

// Returns a description of the TokenData in the format "line:charPos (type 'text')"
string TokenData::getDescription()
{
	// Combine line number, character position, token type, and text into a descriptive string
	return to_string(getLine()) + ":" + to_string(getCharPos()) + " (" + TokenData::typeToString(tokenType) + " '" + getText() + "')";
}

// Returns a description of the Token's type, including operator information if applicable
string TokenData::getTypeDescription()
{
	string out;

	// If the token is an operator, add operator-specific information
	if (tokenType == TokenData::OPERATOR)
	{
		if (op) // If the operator is not null, add its text representation
		{
			out += op->getText() + " ";
		}
		else // If the operator is unknown, mention that
		{
			out += "unknown ";
		}
	}

	// Append the general type of the token
	out += TokenData::typeToString(tokenType);

	return out;
}

// Converts a vector of tokens into a formatted string representation in a table-like format
string tableStringFromTokens(const vector<Token> &tokens, string tableName)
{
	// Declare variables to hold different parts of the table
	vector<string> lines;			 // Stores individual lines of the table
	string abv = "", blw = "";		 // For alignment purposes (above and below the token)
	string str = "";				 // Holds the current string being processed
	const int maxWidth = 240;		 // Maximum width for each line (to prevent overflow)
	const string seporator = "    "; // Separator between columns

	// Loop through all tokens and format them into lines
	for (unsigned i = 0; i < tokens.size(); ++i)
	{
		// Check if the current token can fit within the remaining width of the line
		if (i > 0 && str.size() + seporator.size() + tokens[i]->getText().size() < maxWidth)
		{
			// Add space and separator before the token
			abv += seporator;
			str += seporator;
			blw += seporator;

			// Add spaces to the 'above' and 'below' sections for alignment
			for (unsigned j = 0; j < tokens[i]->getText().size(); j++)
			{
				abv += " ";
				blw += " ";
			}

			// Add the current token's text to the 'str' section
			str += tokens[i]->getText();
		}
		else
		{
			// If the current token cannot fit on the same line, finalize the previous line
			if (i > 0)
			{
				lines.push_back(abv);
				lines.push_back(str);
				lines.push_back(blw);
				lines.push_back(""); // Empty line for separation
				abv = "";			 // Reset for the next line
				blw = "";			 // Reset for the next line
			}

			// Add spaces for alignment
			for (unsigned j = 0; j < tokens[i]->getText().size(); j++)
			{
				abv += " ";
				blw += " ";
			}

			// Start a new line with the current token
			str = tokens[i]->getText();
		}
	}

	// Add the final set of lines
	lines.push_back(abv);
	lines.push_back(str);
	lines.push_back(blw);

	// Return the table formatted as a boxed string (in a readable format)
	return lineListToBoxedString(lines, tableName, -1, false, maxWidth + 4);
}

// Creates a string from a range of tokens (from 'left' to 'right') and joins them with spaces
string stringFromTokens(const vector<Token> &tokens, int left, int right)
{
	string out;

	// Loop through the specified range of tokens
	for (int i = left; i <= right; ++i)
	{
		// Append the text of the current token to the output string
		out += tokens[i]->getText();

		// Add a space between tokens unless it's the last one
		if (i < right)
			out += " ";
	}

	return out; // Return the combined string
}
