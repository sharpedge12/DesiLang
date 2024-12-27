// Include necessary headers for the implementation
#include "../h/Token.h"		   // Header defining Token data structure
#include "../h/ErrorHandler.h" // Header for error handling utilities
#include "../h/Operator.h"	   // Header defining Operator class
#include "../h/AllOperators.h" // Header for managing all supported operators
#include "../h/SourceFile.h"   // Header defining the SourceFile abstraction

#include <vector> // Standard vector library for managing collections
using std::vector;

#include <unordered_map> // Standard unordered map library for efficient key-value lookups
using std::unordered_map;

// Class to classify characters into different types based on their role in the source code
class CharClassifier
{
public:
	// Enum representing character types
	enum Type
	{
		WHITESPACE,				  // Whitespace characters like space, tab
		LINE_BREAK,				  // Characters causing a line break (e.g., ';')
		NEWLINE,				  // Characters representing a new line (e.g., '\n')
		LETTER,					  // Alphabetic characters (A-Z, a-z)
		DIGIT,					  // Numeric characters (0-9)
		OPERATOR,				  // Operators like +, -, *, /
		STRING_QUOTE,			  // Characters used for strings (e.g., '"')
		SINGLE_LINE_COMMENT,	  // Start of a single-line comment (e.g., '//')
		MULTI_LINE_COMMENT_START, // Start of a multi-line comment (e.g., '/*')
		MULTI_LINE_COMMENT_END,	  // End of a multi-line comment (e.g., '*/')
		UNKNOWN,				  // Unclassified or unknown characters
	};

	// Static method to map character type to token type based on context
	static inline TokenData::Type getTokenType(CharClassifier::Type type, TokenData::Type previousType);

	// Determines the type of a character at a given index in the source file
	inline CharClassifier::Type get(std::shared_ptr<SourceFile> file, int i);

private:
	// Initializes character-type mappings
	void setUp();

private:
	std::unordered_map<char, CharClassifier::Type> hm; // Hashmap for character-to-type mappings
	bool hasSetUp = false;							   // Flag to ensure one-time setup
};

// Create a global instance of CharClassifier
CharClassifier charClassifier;

// Initializes the character-type mapping
void CharClassifier::setUp()
{
	// Map common characters to their respective types
	hm[' '] = WHITESPACE;
	hm['\t'] = WHITESPACE;
	hm['\r'] = WHITESPACE; // Ignore '\r' in Windows-style line endings
	hm['\n'] = NEWLINE;
	hm[';'] = LINE_BREAK;

	// Map alphabetic characters (lowercase and uppercase) to LETTER
	for (char c = 'a'; c <= 'z'; ++c)
		hm[c] = LETTER;
	for (char c = 'A'; c <= 'Z'; ++c)
		hm[c] = LETTER;

	hm['_'] = LETTER; // Underscore is treated as a letter (common in identifiers)

	// Map numeric characters to DIGIT
	for (char c = '0'; c <= '9'; ++c)
		hm[c] = DIGIT;

	hm['#'] = SINGLE_LINE_COMMENT; // Hash indicates the start of a single-line comment
	hm['"'] = STRING_QUOTE;		   // Double quote indicates a string literal

	// Add all operators to the map
	unordered_map<string, Operator> &opsMap = ops->getOpsMap();
	for (auto i = opsMap.begin(); i != opsMap.end(); ++i)
	{
		string str = (*i).first; // Get operator text like "=" or "||" or "=="
		for (unsigned j = 0; j < str.size(); j++)
		{
			hm[str[j]] = OPERATOR;
		}
	}

	hasSetUp = true; // Mark setup as complete
}

// Determines the type of a character at a specific index
inline CharClassifier::Type CharClassifier::get(std::shared_ptr<SourceFile> file, int index)
{
	if (!hasSetUp) // Perform setup if not already done
		setUp();

	// Handle multi-character tokens like comments specially
	switch ((*file)[index])
	{
	case '/':
		if (index < int(file->size()) - 1 && (*file)[index + 1] == '/')
			return MULTI_LINE_COMMENT_START; // Start of a multi-line comment
		break;
	case '\\':
		if (index > 0 && (*file)[index - 1] == '\\')
			return MULTI_LINE_COMMENT_END; // End of a multi-line comment
		break;
	case '.':
		// Handle '.' as part of a number if followed by a digit
		if (index < int(file->size()) - 1)
		{
			auto i = hm.find((*file)[index + 1]);
			if (i != hm.end() && i->second == DIGIT)
				return DIGIT;
		}
		break;
	}

	// Use the hashmap for other single-character cases
	char c = (*file)[index];
	auto i = hm.find(c);
	return (i == hm.end()) ? UNKNOWN : i->second;
}

// Maps a character type to a token type based on context
inline TokenData::Type CharClassifier::getTokenType(CharClassifier::Type type, TokenData::Type previousType)
{
	if (previousType == TokenData::LINE_COMMENT)
	{
		if (type == NEWLINE)
			return TokenData::WHITESPACE;
		return TokenData::LINE_COMMENT;
	}
	else if (previousType == TokenData::BLOCK_COMMENT)
	{
		if (type == MULTI_LINE_COMMENT_END)
			return TokenData::WHITESPACE;
		return TokenData::BLOCK_COMMENT;
	}
	else if (previousType == TokenData::STRING_LITERAL)
	{
		if (type == STRING_QUOTE)
			return TokenData::WHITESPACE;
		return TokenData::STRING_LITERAL;
	}

	switch (type)
	{
	case SINGLE_LINE_COMMENT:
		return TokenData::LINE_COMMENT;
	case MULTI_LINE_COMMENT_START:
		return TokenData::BLOCK_COMMENT;
	case MULTI_LINE_COMMENT_END:
		error.log("block comment end without start", SOURCE_ERROR);
		return TokenData::UNKNOWN;
	case WHITESPACE:
		return TokenData::WHITESPACE;
	case LINE_BREAK:
	case NEWLINE:
		return TokenData::LINE_END;
	case OPERATOR:
		return TokenData::OPERATOR;
	case LETTER:
	case DIGIT:
		if (previousType == TokenData::IDENTIFIER || previousType == TokenData::LITERAL)
			return previousType;
		else if (type == DIGIT)
			return TokenData::LITERAL;
		else
			return TokenData::IDENTIFIER;
	case STRING_QUOTE:
		return TokenData::STRING_LITERAL;
	default:
		return TokenData::UNKNOWN;
	}
}

// Function to tokenize a source file
void lexString(std::shared_ptr<SourceFile> file, vector<Token> &tokens)
{
	string tokenTxt; // Stores the current token text
	int line = 1;	 // Tracks line numbers
	int charPos = 1; // Tracks character positions within a line

	TokenData::Type type = TokenData::WHITESPACE; // Initialize with whitespace type

	for (int i = 0; i < file->size(); i++)
	{
		CharClassifier::Type charType = charClassifier.get(file, i);
		TokenData::Type newType = CharClassifier::getTokenType(charType, type);

		if (newType != type)
		{
			if (!tokenTxt.empty())
			{
				if (type == TokenData::OPERATOR) // operator = , == , - , + , / , * etc
				{
					vector<Operator> opMatches;
					ops->get(tokenTxt, opMatches);
					for (auto op : opMatches)
					{
						tokens.push_back(makeToken(op->getText(), file, line, charPos - tokenTxt.size(), type, op));
					}
				}
				else if (type != TokenData::LINE_COMMENT && type != TokenData::BLOCK_COMMENT)
				{
					Token token = makeToken(tokenTxt, file, line, charPos - tokenTxt.size(), type);
					if (type == TokenData::UNKNOWN)
					{
						DesiLangError("invalid token '" + tokenTxt + "'", SOURCE_ERROR, token).log();
					}
					else
					{
						tokens.push_back(token);
					}
				}
			}
			tokenTxt = "";
		}

		if (newType != TokenData::WHITESPACE && newType != TokenData::LINE_END)
		{
			if (newType == TokenData::STRING_LITERAL && (*file)[i] == '\\')
			{
				i++;
				if ((*file)[i] == 'n')
					tokenTxt += '\n';
				else if ((*file)[i] == '"')
					tokenTxt += '"';
				else if ((*file)[i] == 't')
					tokenTxt += '\t';
				else if ((*file)[i] == '\\')
					tokenTxt += '\\';
				else
					throw DesiLangError(string() + "invalid escape character '\\" + (*file)[i] + "'", SOURCE_ERROR, makeToken(tokenTxt + (*file)[i], file, line, charPos - tokenTxt.size(), type));
			}
			else
			{
				tokenTxt += (*file)[i];
			}
		}

		type = newType;

		if ((*file)[i] == '\n')
		{
			line++;
			charPos = 1;
		}
		else
		{
			charPos++;
		}
	}
}
