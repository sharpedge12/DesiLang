#include "../h/SourceFile.h"      // Include header for SourceFile class
#include "../h/utils/fileUtils.h" // Include utility functions for file handling
#include "../h/msclStringFuncs.h" // Include string utility functions

// Constructor for SourceFile class
SourceFile::SourceFile(string filenameIn, bool printOutput)
{
    filename = filenameIn; // Set the filename to the provided input

    try
    {
        // Try to load the file content into the 'contents' variable
        loadFile(filenameIn, contents);
        contents += "\n"; // Append a newline at the end of the contents
    }
    catch (string err)
    {
        // If there's an error while loading the file, throw a custom DesiLangError
        throw DesiLangError(err, SOURCE_ERROR);
    }
}

// Function to get the directory path from the filename
string SourceFile::getDirPath()
{
    int i = filename.size();

    // This will break on Windows, as the directory separator is different
    while (i >= 0 && filename[i] != '/')
    {
        i--; // Traverse the filename string backwards to find the last '/'
    }

    return filename.substr(0, i); // Return the substring from the start to the found index, which is the directory path
}

// Function to get the content of the file in a boxed string format
string SourceFile::getBoxedString()
{
    return str::getBoxedString(contents, filename, true); // Return the content of the file in a boxed format using the utility function
}

// Function to get a specific line from the file contents
string SourceFile::getLine(int lineNum)
{
    return getTextOfLine(contents, lineNum); // Return the text of the specified line using the utility function
}
