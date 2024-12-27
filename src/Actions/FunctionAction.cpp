#include "../../h/Action.h"					   // Includes the header for the Action class and related definitions.
#include "../../h/ErrorHandler.h"			   // Includes the error handling mechanisms.
#include "../../h/StackFrame.h"				   // Includes the StackFrame class for stack management.
#include "../../h/AstNode.h"				   // Includes the AstNode class for abstract syntax tree operations.
#include "../../h/utils/stringNumConversion.h" // Includes utility functions for string and numeric conversions.
#include "../../h/utils/stringUtils.h"		   // Includes utility functions for string operations.

#include <cstring> //for memcpy          // Standard library header for memory operations like memcpy.
using std::memcpy; // Uses memcpy from the standard library.

class FunctionAction : public ActionData // The FunctionAction class extends ActionData to represent a function call.
{
public:
	// Constructor for wrapping an already resolved action with a stack frame
	FunctionAction(Action actionIn, shared_ptr<StackFrame> stackFameIn) : ActionData(actionIn->getReturnType(), stackFameIn->getLeftInType(), stackFameIn->getRightInType())
	{
		stackFame = stackFameIn; // Initialize stack frame.
		action = actionIn;		 // Set the action.
		node = nullptr;			 // No node is used in this case.

		// Set a description for the function based on input/output types.
		setDescription("function (" + getInLeftType()->getString() + "." + getInRightType()->getString() +
					   " > " + getReturnType()->getString() + ")");

		// Verify that the action has no inputs.
		if (action->getInLeftType() != Void || action->getInRightType() != Void)
		{
			throw DesiLangError(action->getDescription() + " function mai put ho gya but input void nhi hai", INTERNAL_ERROR);
		}
	}

	// Constructor for initializing a function from an AST node and stack frame
	FunctionAction(AstNode nodeIn, Type returnTypeIn, shared_ptr<StackFrame> stackFameIn) : ActionData(returnTypeIn, stackFameIn->getLeftInType(), stackFameIn->getRightInType())
	{
		stackFame = stackFameIn; // Initialize stack frame.
		node = move(nodeIn);	 // Set the AST node.
		action = nullptr;		 // Action is unresolved at this stage.

		// Set a description for the function based on input/output types.
		setDescription("function (" + getInLeftType()->getString() + "." + getInRightType()->getString() +
					   " > " + getReturnType()->getString() + ")");
	}

	// Resolves the action from the AST node when needed
	void resolveAction()
	{
		if (!node || action) // Ensure the function is in the correct state for resolution.
		{
			throw DesiLangError("FunctionAction::resolveAction call hua jaab action wrong state mai hai", INTERNAL_ERROR);
		}

		action = node->getAction(); // Resolve the action from the AST node.

		// Verify that the return type matches expectations.
		if (!returnType->isVoid() && !returnType->matches(action->getReturnType()))
		{
			throw DesiLangError("function body returns " + action->getReturnType()->getString() +
									" instead of " + returnType->getString() + "\n" + action->getDescription(),
								SOURCE_ERROR, node->getToken());
		}

		// Ensure the resolved action has no inputs.
		if (!action->getInLeftType()->isVoid() || !action->getInRightType()->isVoid())
		{
			throw DesiLangError(action->getDescription() + " function mai put ho gya but input void nhi hai", INTERNAL_ERROR);
		}
	}

	// Returns a description of the function for debugging or display
	string getDescription()
	{
		return str::putStringInTreeNodeBox("call func " + nameHint);
	}

	// Indicates that this action represents a function
	bool isFunction() { return true; }

	// Executes the function by managing the stack and calling the underlying action
	void *execute(void *inLeft, void *inRight)
	{
		if (!action) // Resolve the action if not already resolved.
			resolveAction();

		void *oldStackPtr = stackPtr; // Save the current stack pointer.

		// Allocate memory for the function's stack frame.
		stackPtr = malloc(stackFame->getSize());

		// Copy left input to the stack frame if it exists.
		if (inLeft)
			memcpy((char *)stackPtr + stackFame->getLeftOffset(), inLeft, getInLeftType()->getSize());

		// Copy right input to the stack frame if it exists.
		if (inRight)
			memcpy((char *)stackPtr + stackFame->getRightOffset(), inRight, getInRightType()->getSize());

		// Execute the action with no additional inputs (inputs are on the stack).
		void *out = action->execute(nullptr, nullptr);

		free(stackPtr);			// Free the stack frame.
		stackPtr = oldStackPtr; // Restore the previous stack pointer.

		return out; // Return the result of the function.
	}

	// Adds the function to a C++ program during code generation
	void addToProg(Action inLeft, Action inRight, CppProgram *prog)
	{
		if (!action) // Resolve the action if not already resolved.
			resolveAction();

		// Generate a unique name for the function in the C++ program.
		string name = "%";
		name += (nameHint.empty() ? "func" : nameHint);
		name += "_" + str::ptrToUniqueStr(&*action);

		// If the function hasn't been added to the program yet, define it.
		if (!prog->hasFunc(name))
		{
			prog->pushFunc(name, getInLeftType(), getInRightType(), getReturnType());
			if (getReturnType()->isCreatable() && action->getReturnType() != getReturnType())
			{
				cppTupleCastAction(action, getReturnType())->addToProg(prog);
			}
			else
			{
				action->addToProg(prog);
			}
			prog->endln();
			prog->popFunc();
		}

		prog->name(name); // Use the generated name for the function.

		prog->pushExpr(); // Begin the function call expression.

		// Add left input to the function call if it's creatable.
		if (getInLeftType()->isCreatable())
		{
			inLeft->addToProg(prog);
		}

		// Add right input to the function call if it's creatable.
		if (getInRightType()->isCreatable())
		{
			if (getInLeftType()->isCreatable())
				prog->code(", "); // Separate inputs with a comma.

			inRight->addToProg(prog);
		}

		prog->popExpr(); // End the function call expression.
	}

private:
	shared_ptr<StackFrame> stackFame; // The stack frame for the function.
	Action action = nullptr;		  // The resolved action representing the function's body.
	AstNode node = nullptr;			  // The AST node used to define the function (if unresolved).
};

// Wrapper for creating a function action from an action and stack frame
Action functionAction(Action actionIn, shared_ptr<StackFrame> stackFameIn)
{
	return Action(new FunctionAction(actionIn, stackFameIn));
}

// Wrapper for creating a function action from an AST node, return type, and stack frame
Action functionAction(AstNode nodeIn, Type returnTypeIn, shared_ptr<StackFrame> stackFameIn)
{
	return Action(new FunctionAction(move(nodeIn), returnTypeIn, stackFameIn));
}
