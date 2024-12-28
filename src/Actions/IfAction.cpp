#include "../../h/Action.h"		  // Includes the header for Action class and related definitions.
#include "../../h/ErrorHandler.h" // Includes error handling utilities.

class IfAction : public ActionData // The IfAction class represents an 'if' conditional action.
{
public:
	// Constructor for initializing IfAction with condition and action to execute if condition is true
	IfAction(Action conditionIn, Action ifActionIn)
		: ActionData(Void, Void, Void) // The return type and input types are Void (no data passed in/out).
	{
		condition = conditionIn; // The condition that determines if the action should run.
		ifAction = ifActionIn;	 // The action to execute if the condition is true.

		// Check that the condition action returns a Bool.
		if (condition->getReturnType() != Bool)
		{
			error.log("IfAction banate waqt condition action Bool return nahi kar raha hai", INTERNAL_ERROR);
		}

		// Ensure that the condition action does not take any input.
		if (condition->getInLeftType() != Void || condition->getInRightType() != Void)
		{
			error.log("IfAction banate waqt condition action kuch input le raha hai, jo Void nahi hai", INTERNAL_ERROR);
		}

		// Ensure that the ifAction does not take any input.
		if (ifAction->getInLeftType() != Void || ifAction->getInRightType() != Void)
		{
			error.log("IfAction banate waqt action kuch input le raha hai, jo Void nahi hai", INTERNAL_ERROR);
		}
	}

	// Returns a description of the IfAction in a formatted way.
	string getDescription()
	{
		// Creates a tree-like structure for displaying the action and condition.
		return str::makeRootUpBinaryTree("?", condition->getReturnType()->getName(), "", condition->getDescription(), ifAction->getDescription());
	}

	// Executes the ifAction if the condition is true.
	void *execute(void *inLeft, void *inRight)
	{
		void *conditionOut = condition->execute(nullptr, nullptr); // Execute the condition action.
		if (*((bool *)conditionOut))							   // Check if the condition evaluates to true.
		{
			free(ifAction->execute(nullptr, nullptr)); // Execute the action if the condition is true.
		}
		free(conditionOut); // Free the condition result.
		return nullptr;		// Return nothing.
	}

	// Adds the if action to the program code (in C++ syntax).
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		prog->code("if "); // Start the 'if' statement.
		prog->pushExpr();
		condition->addToProg(voidAction, voidAction, prog); // Add the condition to the program.
		prog->popExpr();
		prog->pushBlock();								   // Begin the block for the 'if' statement.
		ifAction->addToProg(voidAction, voidAction, prog); // Add the action to be executed if condition is true.
		prog->endln();
		prog->popBlock(); // End the 'if' block.
	}

private:
	Action condition; // The condition action.
	Action ifAction;  // The action to be executed if the condition is true.
};

class IfElseAction : public ActionData // The IfElseAction class represents an 'if-else' conditional action.
{
public:
	// Constructor for initializing IfElseAction with condition, if-action, and else-action.
	IfElseAction(Action conditionIn, Action ifActionIn, Action elseActionIn)
		: ActionData([&]()
					 { return ifActionIn->getReturnType()->matches(elseActionIn->getReturnType()) ? ifActionIn->getReturnType() : Void; }(),
					 Void, Void)
	{
		returnVal = getReturnType() != Void; // Check if a return value is expected.
		condition = conditionIn;			 // The condition to evaluate.
		ifAction = ifActionIn;				 // Action to execute if the condition is true.
		elseAction = elseActionIn;			 // Action to execute if the condition is false.

		// Check that the condition action returns a Bool.
		if (condition->getReturnType() != Bool)
		{
			error.log("IfElseAction banate waqt condition action Bool return nahi kar raha hai", INTERNAL_ERROR);
		}

		// Ensure the condition action does not take any input.
		if (condition->getInLeftType() != Void || condition->getInRightType() != Void)
		{
			error.log("IfElseAction banate waqt condition action kuch input le raha hai, jo Void nahi hai", INTERNAL_ERROR);
		}

		// Ensure both the ifAction and elseAction do not take any input.
		if (ifAction->getInLeftType() != Void || ifAction->getInRightType() != Void)
		{
			error.log("IfElseAction banate waqt ifAction kuch input le raha hai, jo Void nahi hai", INTERNAL_ERROR);
		}

		if (elseAction->getInLeftType() != Void || elseAction->getInRightType() != Void)
		{
			error.log("IfElseAction banate waqt elseAction kuch input le raha hai, jo Void nahi hai", INTERNAL_ERROR);
		}
	}

	// Returns a description of the IfElseAction in a formatted way.
	string getDescription()
	{
		// Creates a tree-like structure for displaying the action, condition, and both branches (if and else).
		string branch = str::makeRootUpBinaryTree("╭┴╮\n│ │", "jhut", "sach", elseAction->getDescription(), ifAction->getDescription());
		return str::makeRootUpBinaryTree("?", condition->getReturnType()->getName(), "", condition->getDescription(), branch);
	}

	// Executes either the ifAction or elseAction based on the evaluation of the condition.
	void *execute(void *inLeft, void *inRight)
	{
		void *out;
		void *conditionOut = condition->execute(nullptr, nullptr); // Execute the condition action.
		if (*((bool *)conditionOut))							   // Check if the condition evaluates to true.
		{
			out = ifAction->execute(nullptr, nullptr); // Execute the ifAction if true.
		}
		else
		{
			out = elseAction->execute(nullptr, nullptr); // Execute the elseAction if false.
		}
		free(conditionOut); // Free the condition result.

		if (returnVal) // If the action has a return value, return the result.
		{
			return out;
		}
		else // If no return value is expected, free the result and return nullptr.
		{
			free(out);
			return nullptr;
		}
	}

	// Adds the if-else action to the program code (in C++ syntax).
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		if (returnVal && prog->getExprLevel() > 0) // If there is a return value, add the ternary operator format.
		{
			prog->pushExpr();
			condition->addToProg(voidAction, voidAction, prog); // Add the condition to the program.
			prog->popExpr();
			prog->code(" ? "); // Ternary 'if' operator.
			prog->pushExpr();
			ifAction->addToProg(voidAction, voidAction, prog); // Add the 'true' branch action.
			prog->popExpr();
			prog->code(" : "); // Ternary 'else' operator.
			prog->pushExpr();
			elseAction->addToProg(voidAction, voidAction, prog); // Add the 'false' branch action.
			prog->popExpr();
		}
		else // If no return value, use standard 'if-else' blocks.
		{
			prog->code("if ");
			prog->pushExpr();
			condition->addToProg(voidAction, voidAction, prog); // Add the condition to the program.
			prog->popExpr();
			prog->pushBlock();								   // Begin the block for the 'if' statement.
			ifAction->addToProg(voidAction, voidAction, prog); // Add the action for the 'if' branch.
			prog->endln();
			prog->popBlock(); // End the 'if' block.

			prog->code("else");									 // Add the 'else' keyword.
			prog->pushBlock();									 // Begin the block for the 'else' statement.
			elseAction->addToProg(voidAction, voidAction, prog); // Add the action for the 'else' branch.
			prog->endln();
			prog->popBlock(); // End the 'else' block.
		}
	}

private:
	Action condition;		// The condition to evaluate.
	Action ifAction;		// The action to execute if the condition is true.
	Action elseAction;		// The action to execute if the condition is false.
	bool returnVal = false; // Indicates if a return value is expected.
};

// Function to create an IfAction from a condition and a corresponding action.
Action ifAction(Action conditionIn, Action ifActionIn)
{
	return Action(new IfAction(conditionIn, ifActionIn));
}

// Function to create an IfElseAction from a condition, ifAction, and elseAction.
Action ifElseAction(Action conditionIn, Action ifActionIn, Action elseAction)
{
	return Action(new IfElseAction(conditionIn, ifActionIn, elseAction));
}
