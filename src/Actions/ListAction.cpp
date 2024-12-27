#include "../../h/Action.h"		  // Includes the header for Action class and related definitions.
#include "../../h/ErrorHandler.h" // Includes error handling utilities.

class ListAction : public ActionData // ListAction class represents a sequence of actions to be executed in order.
{
public:
	// Constructor for initializing ListAction with a list of actions and optional destroyers.
	ListAction(const vector<Action> &actionsIn, const vector<Action> &destroyersIn) : ActionData(
																						  (actionsIn.size() > 0 ? actionsIn.back()->getReturnType() : Void), // Determine return type based on last action
																						  Void,																 // No input type for this action
																						  Void																 // No input type for this action
																					  )
	{
		actions = actionsIn;	   // The list of actions to be executed.
		destroyers = destroyersIn; // The list of actions to clean up (destroyers).

		// Ensure all actions take no input (Void).
		for (auto i = actions.begin(); i != actions.end(); ++i)
		{
			if (!(*i)->getInLeftType()->matches(Void) || !(*i)->getInRightType()->matches(Void))
			{
				error.log((*i)->getDescription() + " put into action list even though its inputs are not void", INTERNAL_ERROR);
			}
		}
	}

	// Destructor for ListAction (currently does nothing).
	~ListAction()
	{
	}

	// Returns a description of the ListAction in a formatted way.
	string getDescription()
	{
		vector<string> data;

		// Gather descriptions of each action in the list.
		for (auto i = actions.begin(); i != actions.end(); ++i)
		{
			if (*i)
				data.push_back((*i)->getDescription()); // Add description if the action is valid.
			else
				data.push_back(str::putStringInTreeNodeBox("[null action]")); // Handle null actions.
		}

		// Return the list of descriptions in a formatted string.
		return str::makeList(data);
	}

	// Executes the list of actions, one by one, and then executes any destroyers.
	void *execute(void *inLeft, void *inRight)
	{
		auto i = actions.begin();

		// Execute all actions except the last one (free their results).
		for (; i != std::prev(actions.end()); ++i)
		{
			free((*i)->execute(nullptr, nullptr));
		}

		// Execute the last action and keep the result.
		void *returnVal = (*i)->execute(nullptr, nullptr);

		// Execute any destroyers (actions meant for cleanup).
		for (auto j : destroyers)
		{
			free(j->execute(nullptr, nullptr));
		}

		// Return the result of the last action.
		return returnVal;
	}

	// Adds the list of actions to the program code (in C++ syntax).
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		addToProg(prog, getReturnType()); // Delegate to the overloaded version of addToProg.
	}

	// Overloaded version of addToProg to add the ListAction to the program code.
	void addToProg(CppProgram *prog, Type returnType)
	{
		bool shouldReturn = (prog->getBlockLevel() == 0 && prog->getIfReturnsVal()) && !prog->isMain();

		prog->pushBlock(); // Start a new block for the actions.

		// Add each action to the program.
		for (auto i : actions)
		{
			if (shouldReturn && i == actions.back()) // If the last action should return a value.
			{
				prog->declareVar("-out", returnType); // Declare a temporary variable for the result.
				prog->name("-out");
				prog->code(" = "); // Assign the result of the action to the variable.

				// If the action's return type doesn't match, cast it to the expected type.
				if (i->getReturnType() != returnType)
				{
					cppTupleCastAction(i, returnType)->addToProg(prog);
				}
				else
				{
					i->addToProg(prog); // Otherwise, directly add the action to the program.
				}
			}
			else
			{
				i->addToProg(prog); // Add other actions to the program without handling return.
			}
			prog->endln(); // End the line of code for the current action.
		}

		// Add any destroyers to the program (actions for cleanup).
		for (auto i : destroyers)
		{
			i->addToProg(prog);
			prog->endln();
		}

		// If we need to return a value, return the result of the last action.
		if (shouldReturn)
		{
			prog->code("return ");
			prog->name("-out");
			prog->endln();
		}

		prog->popBlock(); // End the block of code.
	}

private:
	vector<Action> actions;	   // List of actions to be executed.
	vector<Action> destroyers; // List of actions to clean up (destroyers).
};

// Helper function to add a ListAction to the program with the appropriate return type.
void addListToProgWithCppCasting(ListAction *list, Type returnType, CppProgram *prog)
{
	list->addToProg(prog, returnType); // Delegate to the ListAction's addToProg method.
}

// Helper function to create a ListAction from a list of actions and destroyers.
Action listAction(const vector<Action> &actionsIn, const vector<Action> &destroyersIn)
{
	// Handle the case where there are no actions or destroyers.
	if (actionsIn.size() == 0 && destroyersIn.size() == 0)
	{
		return voidAction; // Return a void action.
	}
	else if (actionsIn.size() == 1 && destroyersIn.size() == 0)
	{
		return actionsIn[0]; // Return the single action.
	}
	else
	{
		return Action(new ListAction(actionsIn, destroyersIn)); // Return a new ListAction if there are multiple actions.
	}
}
