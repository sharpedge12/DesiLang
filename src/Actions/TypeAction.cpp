#include "../../h/Action.h"
#include "../../h/ErrorHandler.h"

class TypeGetAction : public ActionData
{
public:
	TypeGetAction(Type typeIn) : ActionData(typeIn->getMeta(), Void, Void)
	{
		setDescription(typeIn->getString() + " (type)");
	}

	string getCSource(string inLeft, string inRight)
	{
		return "/* C source for TypeGetAction not yet implemented */";
	}

	void *execute(void *inLeft, void *inRight)
	{
		// Error log in Hinglish: Function should not be called.
		error.log("TypeGetAction::execute ko call kiya gaya hai, jo nahi hona chahiye tha", RUNTIME_ERROR);

		return nullptr;
	}

	string getDescription()
	{
		return str::putStringInTreeNodeBox("{" + getReturnType()->getName() + "}");
	}

private:
};

Action typeGetAction(Type typeIn)
{
	return Action(new TypeGetAction(typeIn));
}
