#include "../../h/Action.h"				 // Header file for action definitions
#include "../../h/ErrorHandler.h"		 // Header file for error handling
#include "../../h/utils/stringDrawing.h" // Header file for string drawing utilities

// Class for logical AND operation between two actions
class AndAction : public ActionData
{
public:
	// Constructor for AndAction, initializes the two actions
	AndAction(Action firstActionIn, Action secondActionIn)
		: ActionData(Bool, Void, Void) // Sets the return type to Bool, with Void input types
	{
		firstAction = firstActionIn;   // First operand action
		secondAction = secondActionIn; // Second operand action

		// Validate that both actions return a Bool type
		if (firstAction->getReturnType() != Bool)
		{
			throw DesiLangError("AndAction create hua jiska first action Bool nhi return krta", INTERNAL_ERROR);
		}

		if (secondAction->getReturnType() != Bool)
		{
			throw DesiLangError("AndAction create hua jiska second action Bool nhi return krta", INTERNAL_ERROR);
		}
	}

	// Returns a descriptive string for the AND action
	string getDescription()
	{
		// Creates a binary tree-like structure to represent the action
		return str::makeRootUpBinaryTree("&&",
										 firstAction->getReturnType()->getName(),
										 secondAction->getReturnType()->getName(),
										 firstAction->getDescription(),
										 secondAction->getDescription());
		// Alternative format (commented out):
		// return firstAction->getDescription() + " && " + firstAction->getDescription();
	}

	// Executes the logical AND operation
	void *execute(void *inLeft, void *inRight)
	{
		bool *out = (bool *)malloc(sizeof(bool)); // Allocate memory for the result
		*out = false;							  // Default result is false

		// Execute the first action
		void *firstVal = firstAction->execute(nullptr, nullptr);

		if (*((bool *)firstVal)) // If the first action evaluates to true
		{
			// Execute the second action
			void *secondVal = secondAction->execute(nullptr, nullptr);

			if (*((bool *)secondVal)) // If the second action evaluates to true
			{
				*out = true; // Both actions are true, set the result to true
			}

			free(secondVal); // Free memory allocated by the second action
		}

		free(firstVal); // Free memory allocated by the first action

		return out; // Return the result
	}

	// Adds the AND action to a C++ program
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		prog->pushExpr();									  // Start a new expression level
		firstAction->addToProg(voidAction, voidAction, prog); // Add the first action
		prog->popExpr();									  // End the expression level

		prog->code(" && "); // Add the AND operator to the program

		prog->pushExpr();									   // Start a new expression level
		secondAction->addToProg(voidAction, voidAction, prog); // Add the second action
		prog->popExpr();									   // End the expression level
	}

private:
	Action firstAction;	 // The first operand action
	Action secondAction; // The second operand action
};

// Class for logical OR operation between two actions
class OrAction : public ActionData
{
public:
	// Constructor for OrAction, initializes the two actions
	OrAction(Action firstActionIn, Action secondActionIn)
		: ActionData(Bool, Void, Void) // Sets the return type to Bool, with Void input types
	{
		firstAction = firstActionIn;   // First operand action
		secondAction = secondActionIn; // Second operand action

		// Validate that both actions return a Bool type
		if (firstAction->getReturnType() != Bool)
		{
			throw DesiLangError("OrAction create hua jiska first action Bool nhi return krta", INTERNAL_ERROR);
		}

		if (secondAction->getReturnType() != Bool)
		{
			throw DesiLangError("OrAction create hua jiska second action Bool nhi return krta", INTERNAL_ERROR);
		}
	}

	// Returns a descriptive string for the OR action
	string getDescription()
	{
		// Creates a binary tree-like structure to represent the action
		return str::makeRootUpBinaryTree("||",
										 firstAction->getReturnType()->getName(),
										 secondAction->getReturnType()->getName(),
										 firstAction->getDescription(),
										 secondAction->getDescription());
	}

	// Executes the logical OR operation
	void *execute(void *inLeft, void *inRight)
	{
		bool *out = (bool *)malloc(sizeof(bool)); // Allocate memory for the result
		*out = true;							  // Default result is true

		// Execute the first action
		void *firstVal = firstAction->execute(nullptr, nullptr);

		if (!*((bool *)firstVal)) // If the first action evaluates to false
		{
			// Execute the second action
			void *secondVal = secondAction->execute(nullptr, nullptr);

			if (!*((bool *)secondVal)) // If the second action also evaluates to false
			{
				*out = false; // Both actions are false, set the result to false
			}

			free(secondVal); // Free memory allocated by the second action
		}

		free(firstVal); // Free memory allocated by the first action

		return out; // Return the result
	}

	// Adds the OR action to a C++ program
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		prog->pushExpr();									  // Start a new expression level
		firstAction->addToProg(voidAction, voidAction, prog); // Add the first action
		prog->popExpr();									  // End the expression level

		prog->code(" || "); // Add the OR operator to the program

		prog->pushExpr();									   // Start a new expression level
		secondAction->addToProg(voidAction, voidAction, prog); // Add the second action
		prog->popExpr();									   // End the expression level
	}

private:
	Action firstAction;	 // The first operand action
	Action secondAction; // The second operand action
};

// Factory function to create an AndAction object
Action andAction(Action firstActionIn, Action secondActionIn)
{
	return Action(new AndAction(firstActionIn, secondActionIn));
}

// Factory function to create an OrAction object
Action orAction(Action firstActionIn, Action secondActionIn)
{
	return Action(new OrAction(firstActionIn, secondActionIn));
}
