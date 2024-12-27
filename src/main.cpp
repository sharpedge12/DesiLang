// headers needed by the program
#include "../h/msclStringFuncs.h"
#include "../h/DesiLangProgram.h"
#include "../h/ErrorHandler.h"

// for taking input from the command line
#include <iostream>

// manually inputting std libraries to decrease the size and load
using std::cout;
using std::endl;
using std::string;
using std::vector;

// all cmd line arguments
vector<string> cmdLineArgs;

// all the possible flags that can be used
struct Flags
{
    string myPath;              // path to the DesiLang exeutable that is now running
    vector<string> inFiles;     // all the input files
    bool debug = false;         // if to show debugging info
    bool help = false;          // if to show help message
    bool version = false;       // if to show version message
    bool runInterpreted = true; // if to run the program in the interpreter
    string cppOutFile = "";     // output file for transpiled C++ code, empty if flag not set
    string binOutFile = "";     // binary executable output file, empty if flag not set
    bool runCompiled = false;   // if to run the program compiled
    bool flagError = false;     // if to quit immediately, this is set if there is an unrecognised flag
};

// gets all the flags from the command line
Flags getFlags(int argc, char **argv);

// main function of the program
int main(int argc, char **argv)
{
    Flags flags = getFlags(argc, argv);

    if (flags.flagError)
    {
        cout << "help ke liye 'desilang -h' use kren" << endl;
        return 0;
    }

    if (flags.help)
    {
        cout << "DesiLang v" << VERSION_X << "." << VERSION_Y << "." << VERSION_Z << endl;
        cout << "usage: desilang [options] [source file] [options]" << endl;
        cout << "options: " << endl;
        cout << "-v, -version      DesiLang ka version dekhne le liye" << endl;
        cout << "-d, -debug        program run krne ke baad deugging info dekhne le liye" << endl;
        cout << "-r, -run          program ko interpreter ke sath run krne ke liye" << endl;
        cout << "                    ye default mai active hota hai agar koi transpiling command present nhi hai" << endl;
        cout << "                    currently, -r ke baad saab ignored rahega" << endl;
        cout << "-cpp [file]       C++ mai transpile krne ke liye and file ko save krne ke liye" << endl;
        cout << "-bin [file]       transpile, GCC se compile and binary ko save krne ke liye" << endl;
        cout << "-e, -execute      binary ko transpile, compile and execute krne ke liye" << endl;
        cout << "                    -cpp, -bin and -e ka koi bhi combination use kr skte hai" << endl;
        cout << "                    -r ki tarah hi, -e ke baad saab ignore ho jata hai" << endl;
        cout << "-h, -help         help message dikha kr quit krne ke liye" << endl;
        cout << endl;
        cout << endl;

        return 0;
    }

    if (flags.version)
    {
        cout << "DesiLang version " << VERSION_X << "." << VERSION_Y << "." << VERSION_Z << endl;
        return 0;
    }

    DesiLangProgram program;

    if (flags.inFiles.empty())
    {
        cout << "koi source file specified nhi hai" << endl;
        cout << "help ke liye 'desilang -h' use kren" << endl;
        return 0;
    }
    else if (flags.inFiles.size() > 1)
    {
        cout << "multiple source files specified hai , please ek hi use kren" << endl;
        cout << "help ke liye 'desilang -h' use kren" << endl;
        return 0;
    }

    program.resolveProgram(flags.inFiles[0], flags.debug);

    if (flags.runInterpreted)
    {
        if (error.getIfErrorLogged())
        {
            if (flags.debug)
                cout << endl
                     << ">>>>>>    pichle error ke karan execution aborted  <<<<<<" << endl;
            else
                cout << "program execute nhi hue errors ke karan" << endl;
        }
        else
        {
            if (flags.debug)
                cout << endl
                     << "running program..." << endl
                     << endl;

            program.execute();
        }
    }

    if (!flags.cppOutFile.empty() || !flags.binOutFile.empty() || flags.runCompiled)
    {
        string cppCode = program.getCpp();

        if (error.getIfErrorLogged())
        {
            if (flags.debug)
                cout << endl
                     << ">>>>>>    transpiling failed    <<<<<<" << endl;
            else
                cout << "transpiling failed" << endl;
        }
        else
        {
            string cppFileName = flags.cppOutFile;

            if (cppFileName.empty())
                cppFileName = "temp_desilang_transpiled.cpp";

            if (flags.debug)
                cout << endl
                     << putStringInBox(cppCode, "C++ code", true, false, -1) << endl;

            writeFile(cppFileName, cppCode, flags.debug);

            if (!flags.binOutFile.empty() || flags.runCompiled)
            {
                string binFileName = flags.binOutFile;

                if (binFileName.empty())
                    binFileName = "temp_desilang_compiled";

                string cmd;
                cmd = "g++ -std=c++11 '" + cppFileName + "' -o '" + binFileName + "'";

                if (flags.debug)
                    cout << "running '" + cmd + "'" << endl;

                runCmd(cmd, true);

                if (flags.runCompiled)
                {
                    if (flags.debug)
                        cout << endl;

                    cmd = "./" + binFileName + " --running-from-desilang " + str::join(cmdLineArgs, " ", false);

                    if (flags.debug)
                        cout << "running '" + cmd + "'" << endl
                             << endl;

                    runCmd(cmd, true);
                }

                if (flags.binOutFile.empty())
                    remove(binFileName.c_str());
            }

            if (flags.cppOutFile.empty())
                remove(cppFileName.c_str());
        }
    }

    if (flags.debug)
        cout << endl
             << "all done" << endl;

    return 0;
}

// implementation of getFlags
Flags getFlags(int argc, char **argv)
{
    bool after = false;
    Flags flags;

    for (int i = 1; i < argc; i++)
    {
        string arg(argv[i]);
        if (!after)
        {
            if (arg.size() > 1 && arg[0] == '-')
            {
                string flag = arg.substr(1, string::npos);

                if (flag == "d" || flag == "debug")
                {
                    flags.debug = true;
                }
                else if (flag == "v" || flag == "version")
                {
                    flags.version = true;
                }
                else if (flag == "h" || flag == "help")
                {
                    flags.help = true;
                }
                else if (flag == "r" || flag == "run")
                {
                    flags.runCompiled = false;
                    flags.runInterpreted = true;
                    after = true;
                }
                else if (flag == "cpp")
                {
                    if (i + 1 >= argc)
                    {
                        cout << "output file mai '-cpp' flag hona chaiye";
                        flags.flagError = true;
                    }

                    flags.runInterpreted = false;

                    flags.cppOutFile = string(argv[i + 1]);

                    i++;
                }
                else if (flag == "bin")
                {
                    if (i + 1 >= argc)
                    {
                        cout << "output file mai '-bin' flag hona chaiye";
                        flags.flagError = true;
                    }

                    flags.runInterpreted = false;

                    flags.binOutFile = string(argv[i + 1]);

                    i++;
                }
                else if (flag == "e" || flag == "execute")
                {
                    flags.runCompiled = true;
                    flags.runInterpreted = false;
                    after = true;
                }
                else
                {
                    cout << "unknown flag '" + flag + "'" << endl;
                    flags.flagError = true;
                }
            }
            else
            {
                flags.inFiles.push_back(arg);
                cmdLineArgs.push_back(arg);
            }
        }
        else
        {
            cmdLineArgs.push_back(arg);
        }
    }

    return flags;
}
