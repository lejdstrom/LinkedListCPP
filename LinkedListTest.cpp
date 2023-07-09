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
	List_ToArray(list, &actual, &actual_size);

	bool isOK = actual_size == 10;
	if (isOK)
	{
		for (int i = 0; i < actual_size; i++)
		{
			isOK = isOK && (actual[i] == 9 - i);
		}
	}
	free(actual);
	List_Free(list);
	return isOK ? 0 : 1;
}

int List_Find__WhenValueIsNotPreset_ThenReturnsErrorCode()
{
	// Arrange
	Link* list = List_Create();
	for (int i = 0; i < 10; i++)
		List_Insert(list, i);
	
	// Act
	Link* link = NULL;
	List_ErrorCodes res = List_Find(list, 20, &link);
	
	// Assert
	List_Free(list);
	return res == NO_SUCH_ELEMENT ? 0 : 1;
}


int List_Find__WhenValuePresetMultipleTimes_ThenReturnsFirstLinkThatFit()
{
	// Arrange
	Link* list = List_Create();
	for (int i = 0; i < 10; i++)
		List_Insert(list, i % 3);
	
	// now list is 0,2,1,0,2,1,0,2,1,0

	// Act
	Link* link = NULL;
	List_ErrorCodes res = List_Find(list, 2, &link);

	// Assert
	bool isOK = (res == SUCCESS)
		&& (link->value == 2)
		&& (link == list->next->next);

	List_Free(list);
	return isOK ? 0 : 1;
}

int List_FindPrev__WhenValuePresent()
{
	// Arrange
	Link * anchor = List_Create();
	for (int i = 0; i < 10; i++)
		List_Insert(anchor, i % 3);
	// now list should be 0,2,1,0,2,1,0,2,1,0
	if (List_Length(anchor) != 10)
	{
		List_Free(anchor); 
		return 1;
	}

	// Act
	Link* prev = NULL;
	List_ErrorCodes res = List_FindPrev(anchor, anchor->next->next, &prev);

	// Assert
	bool isOK = (res == SUCCESS)
		&& (prev == anchor->next);
	
	List_Free(anchor);

	return isOK ? 0 : 1;
}

int List_Length__Sanity()
{
	// Arrange, Act:
	Link * anchor = List_Create();
	for (int i = 0; i < 10; i++)
		List_Insert(anchor, (int)List_Length(anchor));

	// Assert
	int* actual = NULL;
	size_t actual_size = 0;
	List_ToArray(anchor, &actual, &actual_size);

	bool isOK = actual_size == 10;
	if (isOK)
	{
		for (int i = 0; i < actual_size; i++)
		{
			isOK = isOK && (actual[i] == 9-i);
		}
	}
	free(actual);
	List_Free(anchor);
	return isOK ? 0 : 1;
}

int List_LastLink__WhenListIsNotEmpty()
{
	// Arrange
	Link * anchor = List_Create();
	for (int i = 0; i < 3; i++)
		List_Insert(anchor, i);

	// Act
	Link* lastLink = NULL;
	List_ErrorCodes res = List_LastLink(anchor, &lastLink);

	// Assert
	bool isOK = res == SUCCESS &&
		lastLink != NULL &&
		lastLink->value == 0 &&
		lastLink->next == NULL &&
		anchor->next->next->next == lastLink;

	List_Free(anchor);
	return isOK ? 0 : 1;
}

int List_LastLink__WhenListIsEmpty()
{
	// Arrange
	Link * anchor = List_Create();

	// Act
	Link* lastLink = NULL;
	List_ErrorCodes res = List_LastLink(anchor, &lastLink);

	// Assert
	bool isOK = res == NO_SUCH_ELEMENT;

	List_Free(anchor);
	return isOK ? 0 : 1;
}

int List_Remove__WhenLinkToRemoveIsNull()
{
	// Arrange
	Link * anchor = List_Create();

	// Act
	List_ErrorCodes res = List_Remove(anchor, NULL, true);

	// Assert
	bool isOK = res == INVALID_PARAM;

	List_Free(anchor);
	return isOK ? 0 : 1;
}


int List_Remove__WhenNoSuchElement()
{
	// Arrange
	Link * anchor = List_Create();

	// Act
	List_ErrorCodes res = List_Remove(anchor, (Link*)0xFF, true);

	// Assert
	bool isOK = res == NO_SUCH_ELEMENT;

	List_Free(anchor);
	return isOK ? 0 : 1;
}

int List_Remove__WhenInputIsValid()
{
	// Arrange
	Link * anchor = List_Create();
	for (int i = 0; i < 3; i++)
		List_Insert(anchor, i);
	if (List_Length(anchor) != 3)
	{
		List_Free(anchor);
		return 1;
	}
	// Act
	List_ErrorCodes res = List_Remove(anchor, anchor->next->next, true);

	// Assert
	bool isOK = res == SUCCESS &&
		List_Length(anchor) == 2 &&
		anchor->next->value == 2 &&
		anchor->next->next->value == 0;

	List_Free(anchor);
	return isOK ? 0 : 1;
}

int List_Sort__Sanity()
{
	// Arrange
	Link * anchor = List_Create();
	for (int i = 0; i < 10; i++)
		List_Insert(anchor, i);
	
	// Act
	List_Sort(anchor);

	// Assert
	int* actual = NULL;
	size_t actual_size = 0;
	List_ToArray(anchor, &actual, &actual_size);

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
	List_Free(anchor);
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