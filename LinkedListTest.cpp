#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>


int List_Insert__WhenMultipleValues()
{
	// Arrange
	LinkedList list{};
	
	// Act
	for (int i = 0; i < 10; i++)
		list.Insert(i);
	// Assert
	int* actual = NULL;
	size_t actual_size = 0;
	list.ToArray(&actual, &actual_size);

	bool isOK = actual_size == 10;
	if (isOK)
	{
		for (int i = 0; i < actual_size; i++)
		{
			isOK = isOK && (actual[i] == 9 - i);
		}
	}
	free(actual);
	return isOK ? 0 : 1;
}

int List_Find__WhenValueIsNotPreset_ThenReturnsErrorCode()
{
	// Arrange
	LinkedList list{};
	
	// Act
	for (int i = 0; i < 10; i++)
		list.Insert(i);
	// Act
	Link const * link = NULL;
	ErrorCodes res = list.Find(20, &link);
	
	// Assert
	return res == NO_SUCH_ELEMENT ? 0 : 1;
}


int List_Find__WhenValuePresetMultipleTimes_ThenReturnsFirstLinkThatFit()
{
	// Arrange
	LinkedList list{};
	for (int i = 0; i < 10; i++)
		list.Insert(i % 3);
	
	// now list is 0,2,1,0,2,1,0,2,1,0

	// Act
	Link const* link = NULL;
	ErrorCodes res = list.Find(2, &link);

	// Assert
	bool isOK = (res == SUCCESS)
		&& (link->value == 2)
		&& (link == list.head->next->next);

	return isOK ? 0 : 1;
}

int List_FindPrev__WhenValuePresent()
{
	// Arrange
	LinkedList list{};
	for (int i = 0; i < 10; i++)
		list.Insert(i % 3);
	// now list should be 0,2,1,0,2,1,0,2,1,0
	if (list.Length() != 10)
	{ 
		return 1;
	}

	// Act
	Link const* prev = NULL;
	ErrorCodes res = list.FindPrev(list.head->next->next, &prev);

	// Assert
	bool isOK = (res == SUCCESS)
		&& (prev == list.head->next);
	
	return isOK ? 0 : 1;
}

int List_Length__Sanity()
{
	// Arrange, Act:
	LinkedList list{};
	for (int i = 0; i < 10; i++)
		list.Insert((int)list.Length());

	// Assert
	int* actual = NULL;
	size_t actual_size = 0;
	list.ToArray(&actual, &actual_size);

	bool isOK = actual_size == 10;
	if (isOK)
	{
		for (int i = 0; i < actual_size; i++)
		{
			isOK = isOK && (actual[i] == 9-i);
		}
	}
	free(actual);
	return isOK ? 0 : 1;
}

int List_LastLink__WhenListIsNotEmpty()
{
	// Arrange
	LinkedList list{};
	// Act
	for (int i = 0; i < 3; i++)
		list.Insert(i);
	// Act
	Link const* lastLink = nullptr;
	ErrorCodes res = list.LastLink(&lastLink);

	// Assert
	bool isOK = res == SUCCESS &&
		lastLink != nullptr &&
		lastLink->value == 0 &&
		lastLink->next == nullptr &&
		list.head->next->next->next == lastLink;

	return isOK ? 0 : 1;
}

int List_LastLink__WhenListIsEmpty()
{
	// Arrange
	LinkedList list{};

	// Act
	Link const * lastLink = NULL;
	ErrorCodes res = list.LastLink(&lastLink);

	// Assert
	bool isOK = res == NO_SUCH_ELEMENT;

	return isOK ? 0 : 1;
}

int List_Remove__WhenLinkToRemoveIsNull()
{
	// Arrange
	LinkedList list{};

	// Act
	ErrorCodes res = list.Remove(nullptr, true);

	// Assert
	bool isOK = res == INVALID_PARAM;

	return isOK ? 0 : 1;
}


int List_Remove__WhenNoSuchElement()
{
	// Arrange
	LinkedList list{};
	// Act
	ErrorCodes res = list.Remove((Link*)0xFF, true);

	// Assert
	bool isOK = res == NO_SUCH_ELEMENT;

	return isOK ? 0 : 1;
}

int List_Remove__WhenInputIsValid()
{
	// Arrange
	LinkedList list{};
	for (int i = 0; i < 3; i++)
		list.Insert(i);

	if (list.Length() != 3)
	{
		return 1;
	}
	// Act
	ErrorCodes res = list.Remove(list.head->next->next, true);

	// Assert
	bool isOK = res == SUCCESS &&
		list.Length() == 2 &&
		list.head->next->value == 2 &&
		list.head->next->next->value == 0;

	return isOK ? 0 : 1;
}

int List_Sort__Sanity()
{
	// Arrange
	LinkedList list{};

	for (int i = 0; i < 10; i++)
		list.Insert(i);
	
	// Act
	list.Sort();

	// Assert
	int* actual = NULL;
	size_t actual_size = 0;
	list.ToArray(&actual, &actual_size);

	bool isOK = actual_size == 10;
	if (isOK)
	{
		for (int i = 0; i < actual_size; i++)
		{
			isOK = isOK && (actual[i] == i);
		}
	}
	if (actual)
		free(actual);

	return isOK ? 0 : 1;
}


#define RUN_TEST(T) printf("%s -->", #T); printf(T()==0?"PASS":"FAIL");printf("\n");

int main()
{
	
		RUN_TEST(List_Insert__WhenMultipleValues);
		RUN_TEST(List_Find__WhenValueIsNotPreset_ThenReturnsErrorCode);
		RUN_TEST(List_Find__WhenValuePresetMultipleTimes_ThenReturnsFirstLinkThatFit);
		RUN_TEST(List_FindPrev__WhenValuePresent);
		RUN_TEST(List_Length__Sanity);
		RUN_TEST(List_LastLink__WhenListIsNotEmpty);
		RUN_TEST(List_LastLink__WhenListIsEmpty);
		RUN_TEST(List_Remove__WhenLinkToRemoveIsNull);
		RUN_TEST(List_Remove__WhenNoSuchElement);
		RUN_TEST(List_Remove__WhenInputIsValid);
		RUN_TEST(List_Sort__Sanity);
	
	return 0;
}