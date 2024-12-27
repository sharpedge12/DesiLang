#include "../../h/Action.h"					   // Include header for Action class.
#include "../../h/ErrorHandler.h"			   // Include header for ErrorHandler.
#include "../../h/StackFrame.h"				   // Include header for StackFrame.
#include "../../h/CppProgram.h"				   // Include header for CppProgram.
#include "../../h/utils/stringNumConversion.h" // Include for string and number conversion utilities.
#include "../../h/Namespace.h"				   // Include for Namespace handling.
#include "../../h/utils/stringDrawing.h"	   // Include for string drawing utilities.

class VarGetAction : public ActionData // VarGetAction class to handle variable retrieval actions.
{
public:
	// Constructor initializes with the stack offset, stack pointer, type, and variable name.
	VarGetAction(size_t in, void **stackPtrPtrIn, Type typeIn, string idIn) : ActionData(typeIn, Void, Void)
	{
		offset = in;				 // Set the offset for variable in stack.
		stackPtrPtr = stackPtrPtrIn; // Set the stack pointer.
		nameHint = idIn;			 // Set the name of the variable.

		setDescription("get " + typeIn->getString() + " '" + idIn + "'"); // Set description for the action.
	}

	// Execute method to retrieve the variable from the stack and return its value.
	void *execute(void *inLeft, void *inRight)
	{
		if (!(*stackPtrPtr)) // Check if the stack pointer is null.
		{
			throw DesiLangError("VarGetAction::execute call ho gya but stalk pointer null hai", RUNTIME_ERROR);
		}

		// Allocate memory for the result and copy the variable from the stack.
		void *out = malloc(returnType->getSize());
		memcpy(out, (char *)(*stackPtrPtr) + offset, returnType->getSize());
		return out; // Return the variable data.
	}

	// Method to add the variable retrieval code to the program.
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		/*
		if ((nameHint=="me" || nameHint=="in") && getReturnType()->getType()==TypeBase::TUPLE)
		{
			prog->code(prog->getTypeCode(getReturnType()));
			prog->pushExpr();
				bool isFirst=true;
				for (auto i: *getReturnType()->getAllSubTypes())
				{
					if (!isFirst)
						prog->code(", ");
					isFirst=false;
					prog->name(i.name);
				}
			prog->popExpr();
		}
		else
		*/
		{
			// Declare the variable in the program and use the variable name.
			prog->declareVar(nameHint, getReturnType());
			prog->name(nameHint);
		}
	}

	// Get the description of this action.
	string getDescription()
	{
		return str::putStringInTreeNodeBox("get " + nameHint);
	}

private:
	void **stackPtrPtr; // Pointer to the stack pointer.
	size_t offset;		// Offset in the stack for the variable.
};

class VarSetAction : public ActionData // VarSetAction class to handle variable set actions.
{
public:
	// Constructor initializes with the stack offset, stack pointer, type, and variable name.
	VarSetAction(size_t in, void **stackPtrPtrIn, Type typeIn, string idIn) : ActionData(Void, Void, typeIn)
	{
		offset = in;				 // Set the offset for variable in stack.
		stackPtrPtr = stackPtrPtrIn; // Set the stack pointer.
		nameHint = idIn;			 // Set the name of the variable.

		setDescription("set " + typeIn->getString() + " '" + idIn + "'"); // Set description for the action.
	}

	// Execute method to set the variable in the stack with the provided value.
	void *execute(void *left, void *right)
	{
		if (!(*stackPtrPtr)) // Check if the stack pointer is null.
		{
			throw DesiLangError("VarSetAction::execute execute call ho gya but stalk pointer null hai", RUNTIME_ERROR);
		}

		// Copy the provided value onto the variable's location in the stack.
		memcpy((char *)(*stackPtrPtr) + offset, right, inRightType->getSize());

		// Allocate memory and copy the value to return.
		void *out = malloc(returnType->getSize());
		memcpy(out, (char *)(*stackPtrPtr) + offset, inRightType->getSize());
		// Return null as no specific return is needed in this context.
		return nullptr;
	}

	// Method to add the variable setting code to the program.
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		{
			// Declare the variable and assign it the provided value.
			prog->declareVar(nameHint, getInRightType());
			prog->name(nameHint);
			prog->code(" = ");
			prog->pushExpr();
			inRight->addToProg(prog);
			prog->popExpr();
			// if (prog->getExprLevel()==0)
			//    prog->endln();
		}
	}

	// Get the description of this action.
	string getDescription()
	{
		return str::putStringInTreeNodeBox("set " + nameHint);
	}

private:
	void **stackPtrPtr; // Pointer to the stack pointer.
	size_t offset;		// Offset in the stack for the variable.
};

class ConstGetAction : public ActionData // ConstGetAction class to handle constant retrieval actions.
{
public:
	// Constructor initializes with constant data, type, and description.
	ConstGetAction(const void *in, Type typeIn, string textIn) : ActionData(typeIn, Void, Void)
	{
		data = malloc(returnType->getSize());	 // Allocate memory for constant data.
		memcpy(data, in, returnType->getSize()); // Copy constant data into memory.

		setDescription(textIn); // Set the description for the action.
	}

	// Destructor to free the allocated memory for the constant.
	~ConstGetAction()
	{
		free(data);
	}

	// Execute method to return a copy of the constant data.
	void *execute(void *inLeft, void *inRight)
	{
		void *out = malloc(returnType->getSize());
		memcpy(out, data, returnType->getSize());
		return out; // Return a copy of the constant data.
	}

	// Method to add constant retrieval code to the program.
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		if (getReturnType() == String) // Check if the return type is String.
		{
			// Add string literal to the program.
			prog->code(prog->getTypeCode(String));
			prog->pushExpr();

			// Retrieve and handle string properties like size and data.
			auto sizeInfo = getReturnType()->getSubType("_size");
			auto dataInfo = getReturnType()->getSubType("_data");
			if (sizeInfo.type != Int || dataInfo.type != Byte->getPtr())
			{
				throw DesiLangError("ConstGetAction::addToProg fail ho gya to access string properties", INTERNAL_ERROR);
			}

			// Add size and data to the program code.
			prog->code(Int->getCppLiteral((char *)data + sizeInfo.offset, prog));
			prog->code(", ");
			prog->code("(unsigned char*)\"");
			int len = *(int *)((char *)data + sizeInfo.offset);
			for (int i = 0; i < len; i++)
			{
				char c = *((*(char **)((char *)data + dataInfo.offset)) + i);

				// Handle special characters in strings.
				if (c == '"')
				{
					prog->code("\\\"");
				}
				else if (c == '\\')
				{
					prog->code("\\\\");
				}
				else if (c >= 32 && c <= 126)
				{
					prog->code(string() + c);
				}
				else if (c == '\n')
				{
					prog->code("\\n");
				}
				else
				{
					prog->code(str::charToCppStringLiteralEscaped(c));
				}
			}
			prog->code("\"");

			prog->popExpr();
		}
		else
		{
			// Handle non-string constants.
			prog->code(getReturnType()->getCppLiteral(data, prog));
		}
	}

	// Get the description of this action.
	string getDescription()
	{
		return str::putStringInTreeNodeBox(description);
	}

private:
	void *data; // Pointer to the constant data.
};

// Functions to create actions for variable retrieval, setting, and constants.
Action varGetAction(size_t in, Type typeIn, string textIn)
{
	return Action(new VarGetAction(in, &stackPtr, typeIn, textIn)); // Create a VarGetAction.
}

Action varSetAction(size_t in, Type typeIn, string varNameIn)
{
	return Action(new VarSetAction(in, &stackPtr, typeIn, varNameIn)); // Create a VarSetAction.
}

Action globalGetAction(size_t in, Type typeIn, string textIn)
{
	return Action(new VarGetAction(in, &globalFramePtr, typeIn, textIn)); // Create a global VarGetAction.
}

Action globalSetAction(size_t in, Type typeIn, string textIn)
{
	return Action(new VarSetAction(in, &globalFramePtr, typeIn, textIn)); // Create a global VarSetAction.
}

Action constGetAction(const void *in, Type typeIn, string textIn, Namespace ns)
{
	Action action = Action(new ConstGetAction(in, typeIn, textIn)); // Create a ConstGetAction.
	if (ns)															// If a namespace is provided.
	{
		Action copier = ns->getCopier(typeIn); // Retrieve the copier for the type.
		if (copier)
			action = branchAction(voidAction, copier, action); // Apply the copier.
	}
	return action; // Return the action.
}
