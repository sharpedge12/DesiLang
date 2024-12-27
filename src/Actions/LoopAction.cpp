#include "../../h/Action.h"		  // Includes Action class and related functionality.
#include "../../h/ErrorHandler.h" // Includes error handling utilities.

class LoopAction : public ActionData // LoopAction class represents a loop action (like a "while" loop).
{
public:
	// Constructor for initializing LoopAction with condition, loop body, and optional end action.
	LoopAction(Action conditionIn, Action endActionIn, Action loopActionIn)
		: ActionData(Void, Void, Void) // No input or return types for this action.
	{
		condition = conditionIn;   // The condition to check for the loop.
		loopAction = loopActionIn; // The action to perform inside the loop.
		endAction = endActionIn;   // An optional action to execute after each loop iteration.

		// Check that the condition action returns a boolean value.
		if (condition->getReturnType() != Bool)
		{
			error.log("LoopAction banate waqt condition action Bool return nahi kar raha hai", INTERNAL_ERROR);
		}

		// Check that the condition action takes no inputs (Void).
		if (condition->getInLeftType() != Void || condition->getInRightType() != Void)
		{
			error.log("LoopAction banate waqt condition action kuch input le raha hai, jo Void nahi hai", INTERNAL_ERROR);
		}

		// Check that the loop action takes no inputs (Void).
		if (loopAction->getInLeftType() != Void || loopAction->getInRightType() != Void)
		{
			error.log("LoopAction banate waqt loop action kuch input le raha hai, jo Void nahi hai", INTERNAL_ERROR);
		}
	}

	// Returns a description of the loop action, including the condition and body.
	string getDescription()
	{
		string body = loopAction->getDescription(); // Get the description of the loop body.
		if (endAction != voidAction)				// If there's an end action, include it in the description.
		{
			vector<string> data = {body, endAction->getDescription()};
			body = str::makeList(data);
		}
		// Create a formatted description in the form of a binary tree structure.
		return str::makeRootUpBinaryTree("@", condition->getReturnType()->getName(), "", condition->getDescription(), body);
	}

	// Executes the loop action by checking the condition and performing the loop body.
	void *execute(void *inLeft, void *inRight)
	{
		void *conditionOut; // Variable to hold the result of the condition evaluation.

		while (true)
		{
			// Execute the condition to check if the loop should continue.
			conditionOut = condition->execute(nullptr, nullptr);
			if (!(*((bool *)conditionOut))) // If the condition is false, break the loop.
				break;
			free(conditionOut); // Free the memory allocated for condition result.

			// Execute the loop body and the optional end action.
			free(loopAction->execute(nullptr, nullptr));
			free(endAction->execute(nullptr, nullptr));
		}

		free(conditionOut); // Free the memory for the final condition check.

		return nullptr; // Return nothing.
	}

	/*
	// Method to generate C source code representation of the loop action (commented out).
	string getCSource(string inLeft, string inRight)
	{
		string out;

		out += "while (";
		out += condition->getCSource();  // Get C code for the condition.
		out += ")\n{";
		out += loopAction->getCSource();  // Get C code for the loop body.
		out += endAction->getCSource();  // Get C code for the end action.
		out += "\n}";

		return out;
	}
	*/

	// Adds the loop action to the program code.
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		prog->code("while "); // Start the while loop in C++ syntax.

		prog->pushExpr();
		condition->addToProg(prog); // Add the condition to the loop.
		prog->popExpr();

		prog->pushBlock();			 // Start a new block for the loop body.
		loopAction->addToProg(prog); // Add the loop action (body) to the block.
		prog->endln();
		if (endAction != voidAction) // If there is an end action, add it.
		{
			endAction->addToProg(prog);
			prog->endln();
		}
		prog->popBlock(); // End the loop block.
	}

private:
	Action condition;  // The condition for the loop (evaluates to Bool).
	Action loopAction; // The action to perform inside the loop.
	Action endAction;  // The optional action to execute after each iteration.
};

// Helper function to create a LoopAction with only a condition and loop body (no end action).
Action loopAction(Action conditionIn, Action loopActionIn)
{
	return Action(new LoopAction(conditionIn, voidAction, loopActionIn));
}

// Helper function to create a LoopAction with a condition, loop body, and end action.
Action loopAction(Action conditionIn, Action endActionIn, Action loopActionIn)
{
	return Action(new LoopAction(conditionIn, endActionIn, loopActionIn));
}
