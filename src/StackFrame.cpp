#include "../h/StackFrame.h"	  // Include header for StackFrame class
#include "../h/msclStringFuncs.h" // Include string utility functions
#include "../h/ErrorHandler.h"	  // Include error handling functionality

// Global pointers for stack frame management
void *globalFramePtr = nullptr;
void *stackPtr = nullptr;

// Function to add a member type to the stack frame
void StackFrame::addMember(Type in)
{
	// Check if the type is creatable; if not, throw an error
	if (!in->isCreatable())
	{
		throw DesiLangError("Stack frame mein uncreatable type " + in->getString() + " daalne ki koshish ki gayi", INTERNAL_ERROR);
	}

	// Add the member to the stack frame and update the frame size
	members.push_back(in);
	frameSize += in->getSize();
}

// Function to set the left and right input types in the stack frame
void StackFrame::setInput(Type left, Type right)
{
	// Ensure that setInput is only called once
	if (inputSet)
	{
		error.log("StackFrame::setInput ko baar-baar call kiya gaya", INTERNAL_ERROR);
	}
	else
	{
		// Handle left input type
		if (left->isCreatable())
		{
			leftInputOffset = frameSize;
			leftInputIndex = members.size();
			addMember(left); // Add the left input type to the stack frame
		}
		else if (left != Void)
		{
			throw DesiLangError("Stack frame mein left input " + left->getString() + " set kiya gaya hai, jo na to creatable hai aur na hi void", INTERNAL_ERROR);
		}

		// Handle right input type
		if (right->isCreatable())
		{
			rightInputOffset = frameSize;
			rightInputIndex = members.size();
			addMember(right); // Add the right input type to the stack frame
		}
		else if (right != Void)
		{
			throw DesiLangError("Stack frame mein right input " + right->getString() + " set kiya gaya hai, jo na to creatable hai aur na hi void", INTERNAL_ERROR);
		}

		inputSet = true; // Mark that the input has been set
	}
}

// Function to get the left input type from the stack frame
Type StackFrame::getLeftInType()
{
	if (leftInputIndex >= 0)
	{
		return members[leftInputIndex]; // Return the left input type
	}
	else
	{
		return Void; // Return Void if left input is not set
	}
}

// Function to get the right input type from the stack frame
Type StackFrame::getRightInType()
{
	if (rightInputIndex >= 0)
	{
		return members[rightInputIndex]; // Return the right input type
	}
	else
	{
		return Void; // Return Void if right input is not set
	}
}

// Function to get the offset of the left input in the stack frame
size_t StackFrame::getLeftOffset()
{
	if (leftInputIndex >= 0)
	{
		return leftInputOffset; // Return the left input offset
	}
	else
	{
		error.log("Stack frame mein left input offset lene ki koshish ki gayi, par left input nahi hai", INTERNAL_ERROR);
		return 0; // Return 0 if there is no left input
	}
}

// Function to get the offset of the right input in the stack frame
size_t StackFrame::getRightOffset()
{
	if (rightInputIndex >= 0)
	{
		return rightInputOffset; // Return the right input offset
	}
	else
	{
		throw DesiLangError("Stack frame mein right input offset lene ki koshish ki gayi, par right input nahi hai", INTERNAL_ERROR);
	}
}
