#include "../../h/Action.h"
#include "../../h/ErrorHandler.h"
#include "../../h/CppProgram.h"
#include "../../h/utils/stringDrawing.h"

// The `BranchAction` class represents a binary action that combines two input actions
// (left and right) and processes them through a main action.
class BranchAction : public ActionData
{
public:
	// Constructor initializes the BranchAction and validates inputs
	BranchAction(Action leftInputIn, Action actionIn, Action rightInputIn)
		: ActionData(actionIn->getReturnType(), Void, Void)
	{
		if (!actionIn)
			throw DesiLangError(string() + "branch action create hua or usne null action sent kra", INTERNAL_ERROR);

		if (!leftInputIn)
			throw DesiLangError(string() + "branch action create hua or usne null leftInput sent kra ", INTERNAL_ERROR);

		if (!rightInputIn)
			throw DesiLangError(string() + "branch action create hua or usne null rightInput sent kra", INTERNAL_ERROR);

		action = actionIn;
		leftInput = leftInputIn;
		rightInput = rightInputIn;

		// Ensure left input matches expectations
		if (!leftInput->getInLeftType()->matches(Void) || !leftInput->getInRightType()->matches(Void))
		{
			throw DesiLangError(leftInput->getDescription() + " branch mai put ho gya but uska input void nhi hai", INTERNAL_ERROR);
		}

		// Ensure right input matches expectations
		if (!rightInput->getInLeftType()->matches(Void) || !rightInput->getInRightType()->matches(Void))
		{
			throw DesiLangError(leftInput->getDescription() + " branch mai put ho gya but uska input void nhi hai", INTERNAL_ERROR);
		}

		// Ensure return types align with action inputs
		if (!leftInput->getReturnType()->matches(action->getInLeftType()))
		{
			throw DesiLangError(leftInput->getDescription() + " return type left input se alag hai  " + action->getDescription(), INTERNAL_ERROR);
		}

		if (!rightInput->getReturnType()->matches(action->getInRightType()))
		{
			throw DesiLangError(rightInput->getDescription() + " return type right input se alag hai " + action->getDescription(), INTERNAL_ERROR);
		}
	}

	// Returns a textual description of the branch action
	string getDescription()
	{
		if (leftInput && action && rightInput)
		{
			// Generate a description using a binary tree format
			return str::makeRootUpBinaryTree(action->getDescription(), leftInput->getReturnType()->getName(), rightInput->getReturnType()->getName(), leftInput->getDescription(), rightInput->getDescription());
		}
		else
			return "[branch with null element]";
	}

	// Executes the branch action by processing the left and right inputs through the main action
	void *execute(void *inLeft, void *inRight)
	{
		void *leftData = leftInput->execute(nullptr, nullptr);
		void *rightData = rightInput->execute(nullptr, nullptr);
		void *outData = action->execute(leftData, rightData);
		free(leftData);	 // Free allocated memory for left data
		free(rightData); // Free allocated memory for right data
		return outData;
	}

	// Adds the action to the C++ program representation
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		Action leftInTmp = leftInput;
		Action rightInTmp = rightInput;

		// Adjust types if needed to match the main action's input types
		if (leftInTmp->getReturnType() != action->getInLeftType())
			leftInTmp = cppTupleCastAction(leftInTmp, action->getInLeftType());

		if (rightInTmp->getReturnType() != action->getInRightType())
			rightInTmp = cppTupleCastAction(rightInTmp, action->getInRightType());

		action->addToProg(leftInTmp, rightInTmp, prog);
	}

private:
	Action action;	   // The main action that processes inputs
	Action leftInput;  // Left input action
	Action rightInput; // Right input action
};

// The `RightBranchAction` class represents a branch where only the right input
// and the main action are processed.
class RightBranchAction : public ActionData
{
public:
	RightBranchAction(Action actionIn, Action rightInputIn)
		: ActionData(actionIn->getReturnType(), Void, Void)
	{
		if (!actionIn)
			throw DesiLangError(string() + "branch action create hua or usne null action sent kra", INTERNAL_ERROR);

		if (!rightInputIn)
			throw DesiLangError(string() + "branch action create hua or usne null rightInput sent kra", INTERNAL_ERROR);

		action = actionIn;
		rightInput = rightInputIn;

		// Ensure the right input matches expectations
		if (!rightInput->getInLeftType()->matches(Void) || !rightInput->getInRightType()->matches(Void))
		{
			throw DesiLangError(rightInput->getDescription() + " branch mai put ho gya but uska input void nhi hai", INTERNAL_ERROR);
		}

		if (!rightInput->getReturnType()->matches(action->getInRightType()))
		{
			throw DesiLangError(rightInput->getDescription() + " return type right input se alag hai " + action->getDescription(), INTERNAL_ERROR);
		}
	}

	~RightBranchAction()
	{ /* Destructor */
	}

	// Returns a textual description of the right branch action
	string getDescription()
	{
		if (action && rightInput)
		{
			return str::makeRootUpBinaryTree(action->getDescription(), "", rightInput->getReturnType()->getName(), "", rightInput->getDescription());
		}
		else
			return "[branch with null element]";
	}

	// Executes the branch action with only the right input
	void *execute(void *inLeft, void *inRight)
	{
		void *rightData = rightInput->execute(nullptr, nullptr);
		void *outData = action->execute(nullptr, rightData);
		free(rightData); // Free allocated memory for right data
		return outData;
	}

	// Adds the action to the C++ program representation
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		Action rightInTmp = rightInput;

		// Adjust types if needed to match the main action's right input type
		if (rightInTmp->getReturnType() != action->getInRightType())
			rightInTmp = cppTupleCastAction(rightInTmp, action->getInRightType());

		action->addToProg(voidAction, rightInTmp, prog);
	}

private:
	Action action = nullptr;	 // The main action that processes inputs
	Action rightInput = nullptr; // Right input action
};

// The `LeftBranchAction` class represents a branch where only the left input
// and the main action are processed.
class LeftBranchAction : public ActionData
{
public:
	LeftBranchAction(Action leftInputIn, Action actionIn)
		: ActionData(actionIn->getReturnType(), Void, Void)
	{
		if (!actionIn)
			throw DesiLangError(string() + "branch action create hua or usne null action sent kra", INTERNAL_ERROR);

		if (!leftInputIn)
			throw DesiLangError(string() + "branch action create hua or usne null leftInput sent kra", INTERNAL_ERROR);

		action = actionIn;
		leftInput = leftInputIn;

		// Ensure the left input matches expectations
		if (!leftInput->getInLeftType()->matches(Void) || !leftInput->getInRightType()->matches(Void))
		{
			throw DesiLangError(leftInput->getDescription() + " branch mai put ho gya but uska input void nhi hai", INTERNAL_ERROR);
		}

		if (!leftInput->getReturnType()->matches(action->getInLeftType()))
		{
			throw DesiLangError(leftInput->getDescription() + " return type left input se alag hai " + action->getDescription(), INTERNAL_ERROR);
		}
	}

	// Returns a textual description of the left branch action
	string getDescription()
	{
		if (leftInput && action)
		{
			return str::makeRootUpBinaryTree(action->getDescription(), leftInput->getReturnType()->getName(), "", leftInput->getDescription(), "");
		}
		else
			return "[branch with null element]";
	}

	// Executes the branch action with only the left input
	void *execute(void *inLeft, void *inRight)
	{
		void *leftData = leftInput->execute(nullptr, nullptr);
		void *outData = action->execute(leftData, nullptr);
		free(leftData); // Free allocated memory for left data
		return outData;
	}

	// Adds the action to the C++ program representation
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		Action leftInTmp = leftInput;

		// Adjust types if needed to match the main action's left input type
		if (leftInTmp->getReturnType() != action->getInLeftType())
			leftInTmp = cppTupleCastAction(leftInTmp, action->getInLeftType());

		action->addToProg(leftInTmp, voidAction, prog);
	}

private:
	Action leftInput; // Left input action
	Action action;	  // The main action that processes inputs
};

// Factory function to create appropriate branch actions based on input types
Action branchAction(Action leftInputIn, Action actionIn, Action rightInputIn)
{
	if (leftInputIn->getReturnType()->isVoid())
	{
		if (rightInputIn->getReturnType()->isVoid())
		{
			return actionIn;
		}
		else
		{
			return Action(new RightBranchAction(actionIn, rightInputIn));
		}
	}
	else
	{
		if (rightInputIn->getReturnType()->isVoid())
		{
			return Action(new LeftBranchAction(leftInputIn, actionIn));
		}
		else
		{
			return Action(new BranchAction(leftInputIn, actionIn, rightInputIn));
		}
	}
}
