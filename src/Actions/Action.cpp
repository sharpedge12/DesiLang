#include "../../h/Action.h"			 // Header file for action definitions
#include "../../h/ErrorHandler.h"	 // Header file for error handling
#include "../../h/msclStringFuncs.h" // Header file for string manipulation utilities

// Constructor for ActionData, initializes the types for an action and validates them
ActionData::ActionData(Type returnTypeIn, Type inLeftTypeIn, Type inRightTypeIn)
{
	returnType = returnTypeIn;	 // Return type of the action
	inLeftType = inLeftTypeIn;	 // Input type for the left operand
	inRightType = inRightTypeIn; // Input type for the right operand

	// Ensure all types are valid; throw an internal error if any type is null
	if (!returnType || !inLeftType || !inRightType)
	{
		throw DesiLangError("ActionData ko null type se bnaya", INTERNAL_ERROR);
	}
}

// Converts the action's description into a string representation
string ActionData::toString()
{
	return description; // Returns the description of the action

	// Placeholder for a more detailed string representation
	// return returnType->getName() + " <- " + inLeftType->getName() + " " + text + " " + inRightType->getName();
}

// Returns a string showing the types involved in the action
string ActionData::getTypesString()
{
	// Format: returnType <- inLeftType.inRightType
	return returnType->getString() + " <- " + inLeftType->getString() + "." + inRightType->getString();
}

// Class representing a "Void Action", an action that effectively does nothing
class VoidAction : public ActionData
{
public:
	// Constructor for VoidAction, initializing it with Void types
	VoidAction() : ActionData(Void, Void, Void)
	{
		setDescription("Void Action"); // Set a description for the void action
	}

	// Executes the void action (does nothing and returns nullptr)
	void *execute(void *inLeft, void *inRight)
	{
		return nullptr;
	}

	// Adds the void action to a C++ program (comments out "void" in the program)
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		if (prog->getExprLevel() > 0) // Add a comment if the expression level is above zero
			prog->comment("void");
	}

	// Returns a description of the void action
	string getDescription()
	{
		return str::putStringInTreeNodeBox("void");
	}
};

// Class representing a LambdaAction, an action defined with lambda functions
class LambdaAction : public ActionData
{
public:
	// Constructor for LambdaAction, initializes with types, lambdas, and description
	LambdaAction(Type inLeftTypeIn, Type inRightTypeIn, Type returnTypeIn,
				 function<void *(void *, void *)> lambdaIn,
				 function<void(Action inLeft, Action inRight, CppProgram *prog)> cppWriterIn,
				 string textIn)
		: ActionData(returnTypeIn, inLeftTypeIn, inRightTypeIn)
	{
		// Set the C++ writer lambda or provide a default implementation
		if (cppWriterIn == nullptr)
		{
			cppWriter = [=](Action inLeft, Action inRight, CppProgram *prog)
			{
				prog->comment("lambda action '" + textIn + "' has not yet been implemented for C++");
			};
		}
		else
		{
			cppWriter = cppWriterIn;
		}

		// Set the execution lambda or provide a default implementation
		if (lambdaIn == nullptr)
		{
			lambda = [=](void *inLeft, void *inRight) -> void *
			{
				throw DesiLangError("action '" + textIn + "' implement nhi hua hai for interpreter", RUNTIME_ERROR);
			};
		}
		else
		{
			lambda = lambdaIn;
		}

		setDescription(textIn); // Set the description for the lambda action
	}

	// Executes the lambda action with given left and right inputs
	void *execute(void *inLeft, void *inRight)
	{
		return lambda(inLeft, inRight);
	}

	// Adds the lambda action to a C++ program using the provided C++ writer lambda
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		cppWriter(inLeft, inRight, prog);
	}

	// Returns a description of the lambda action
	string getDescription()
	{
		return str::putStringInTreeNodeBox(description);
	}

private:
	function<void *(void *, void *)> lambda;								   // Lambda function for executing the action
	function<void(Action inLeft, Action inRight, CppProgram *prog)> cppWriter; // Lambda function for generating C++ code
	string cppCode;															   // Placeholder for generated C++ code
};

// Factory function to create a new LambdaAction object
Action lambdaAction(Type inLeftTypeIn, Type inRightTypeIn, Type returnTypeIn,
					function<void *(void *, void *)> lambdaIn,
					function<void(Action inLeft, Action inRight, CppProgram *prog)> cppWriter,
					string textIn)
{
	return Action(new LambdaAction(inLeftTypeIn, inRightTypeIn, returnTypeIn, lambdaIn, cppWriter, textIn));
}

// Factory function to create a new VoidAction object
Action createNewVoidAction()
{
	return Action(new VoidAction());
}
