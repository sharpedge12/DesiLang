// Header files needed by the program
#include "../h/ErrorHandler.h"    // Error handling related functions and classes
#include "../h/msclStringFuncs.h" // String manipulation functions
#include "../h/SourceFile.h"      // Source file handling

// For taking input/output
#include <iostream>

// Manually inputting standard libraries to decrease the size and load
using std::cout;
using std::endl;

ErrorHandler error; // Global instance for error handling

// Convert error priority to string for easier display
string ErrorHandler::priorityToStr(ErrorPriority in)
{
    switch (in)
    {
    case SOURCE_ERROR:
        return "error"; // For source errors
        break;

    case SOURCE_WARNING:
        return "warning"; // For warnings
        break;

    case JSYK:
        return "jsyk"; // Just so you know (informational messages)
        break;

    case INTERNAL_ERROR:
        return "INTERNAL ERROR"; // For internal errors
        break;

    case RUNTIME_ERROR:
        return "runtime error"; // For runtime errors
        break;

    default:
        return "UNKNOWN PRIORITY LEVEL"; // Default case if priority is unknown
        break;
    }
}

// Log the error with relevant details
void ErrorHandler::log(string msg, ErrorPriority priority, Token token)
{
    // If the priority indicates an error, set errorHasBeenLogged flag
    if (priority == SOURCE_ERROR || priority == INTERNAL_ERROR || priority == RUNTIME_ERROR)
        errorHasBeenLogged = true;

    // Display the error priority (error, warning, etc.)
    cout << priorityToStr(priority);

    // If a token is provided, print the file, line, and position of the error
    if (token)
    {
        cout << token->getFile()->getFilename() << " mein " // "mein" is used in Hinglish for "in"
             << token->getLine() << " line par "            // "par" is used in Hinglish for "on"
             << ":" << endl;
        cout << indentString(msg, "    ") << endl; // Print the error message with indentation

        string line = token->getFile()->getLine(token->getLine()); // Get the line of code containing the error

        int wspace = 0;
        // Skip leading whitespace characters (spaces, tabs, or newlines)
        for (; wspace < int(line.size()) && (line[wspace] == ' ' || line[wspace] == '\t' || line[wspace] == '\n'); wspace++)
        {
        }

        // Create an arrow string pointing to the error position
        string arrows = "";
        for (int i = 0; i < token->getCharPos() - 1 - wspace; i++)
            arrows += " "; // Add spaces before the error
        for (int i = 0; i < int(token->getText().size()); i++)
            arrows += "^"; // Add "^" to indicate the error location

        // Print the line of code with arrows pointing to the error
        cout << indentString("" + line.substr(wspace, string::npos) + "\n" + arrows, "    ") << endl;
    }
    else
    {
        // If no token is provided, just print the message
        cout << ": " << msg << endl;
    }
}

// Simple function to print general messages
void ErrorHandler::msg(string in)
{
    cout << "message: " << in << endl; // Print the message
}

// Constructor for DesiLangError, stores the error details
DesiLangError::DesiLangError(string msgIn, ErrorPriority priorityIn, Token tokenIn)
{
    msg = msgIn;           // Store error message
    priority = priorityIn; // Store error priority
    token = tokenIn;       // Store associated token
}

// Log the error for DesiLangError
void DesiLangError::log()
{   
    error.log(msg, priority, token);
}
