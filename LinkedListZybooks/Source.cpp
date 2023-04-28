/********************************************************************************
 *		TITLE LinkedList Program
 *		author(s): Lennart Richter
 *		adapted from:
 *		other citations:
 *
 *		goal:
 *		overview:
 *
 *
 *
 ********************************************************************************/


#include <iostream> 
#include <vector>
#include <fstream>
#include <string>

#define FILE_ONE "short_dict1.txt"
#define FILE_TWO "short_dict2.txt"
#define FILE_THREE "short_dict3.txt"

#define NEW_DICT_FILE "Updated Dictionary.txt"
#define NEW_DICT_FILE_TWO "Updated Dictionary2.txt"
#define NEW_DICT_FILE_THREE "Updated Dictionary3.txt"

#define FILE_SUFFIX ".txt"

#define FILE_NAME "dictionary"
#define MAX_DICTIONARY_NUM "\"9\""


using namespace std;


/* function returns a vector of dictionary words - possible inputs are 1, 2, & 3 *
 * representing three different word lists. Function will return word list #3 if *
 * any integer besides 1 or 2 is passed in.                                      *
 */
vector<string> fillVector(string fileName);


//Basic structs that represents a LinkedList Node, supports only strings
//Constructor called upon by other functions and this one
struct LinkedListNode
{
	string val;
	LinkedListNode* next;
	LinkedListNode* prev;

	LinkedListNode(string val, LinkedListNode* prev, LinkedListNode* next) {
		this->val = val;
		this->prev = prev;
		this->next = next;
	}
};

//Function called to add a Node after creating a Head node
//Optional parameter of tail can be given, if one is ommited, it's assumed to be a new list.
LinkedListNode* AddNode(string val, LinkedListNode* listEnd = nullptr) {
	//This loop checks for whether there is an end and if not it's a new list
	if (!listEnd) {
		return new LinkedListNode(val, listEnd, nullptr);
	}
	else {
		LinkedListNode* current = new LinkedListNode(val, listEnd, nullptr);
		listEnd->next = current;
		return current;
	}
}

LinkedListNode* FindTail(LinkedListNode* head) {
	//Function similar to finding a middle where we find where the tail is
	LinkedListNode* iterator = head;

	if (head == nullptr) {
		return nullptr;
	}
	else if (head->next == nullptr) {
		return head;
	}
	else {
		while (iterator->next) {
			iterator = iterator->next;
		}
		return iterator;
	}
}

//Linear search algorithm that takes the head, and string being searched for in the list.
//Returns the position of null depending if the words is present.
LinkedListNode* LinearSearch(LinkedListNode* head, string toSearch) {
	//Runs through the list until it finds the toSearch string, if it doesn't returns a null pointer
	LinkedListNode* iterator = head;
	while (iterator != nullptr) {
		if (iterator->val == toSearch) {
			return iterator;
		}
		else {
			iterator = iterator->next;
		}
	}
	return nullptr;
}


//FindInsertionPoint is used to Insert Nodes and for other algorithms
//Returns the node previous to which our word needs to be inserted
//Or if the word is present in the list returns that position
LinkedListNode* FindInsertionPoint(LinkedListNode* head, string word) {
	//Find the alphabetical insertion point
	LinkedListNode* iterator = head;
	if (head->val > word) {
		return head;
	}
	//Loops until the list is either finished, or you find the position where the word can be wedged into
	while (iterator != nullptr && iterator->next) {
		if (iterator->val == word) {
			return iterator;
		}
		if (iterator->val < word && iterator->next->val > word) {
			return iterator;
		}
		iterator = iterator->next;
	}
	return iterator;
}

//Inserts a new node in the correct alphabetical position, and returns the position of the newNode
LinkedListNode* InsertNewNode(LinkedListNode* head, string word) {
	//First finds the point where the node needs to be inserted using the above function
	LinkedListNode* nodeBeforeInsert = FindInsertionPoint(head, word);
	//Then depending on whether the insertion point is head or not makes a new node and inserts it
	if (nodeBeforeInsert == head) {
		LinkedListNode* newNode = new LinkedListNode(word, nullptr, nodeBeforeInsert);
		nodeBeforeInsert->prev = newNode;
		head = newNode;
		return newNode;
	}
	LinkedListNode* newNode = new LinkedListNode(word, nodeBeforeInsert, nodeBeforeInsert->next);
	if (nodeBeforeInsert->next) {
		nodeBeforeInsert->next->prev = newNode;
	}
	nodeBeforeInsert->next = newNode;
	return newNode;
}

//Uses LinearSearch to determine the position of a node, and whether it exists
//If the word exists uses delete to delete the node from the list, and adjusts the words surrounding it
LinkedListNode* DeleteNode(LinkedListNode* head, string word) {
	//First have to make sure that the word is even present in the list
	LinkedListNode* DeletionNode = LinearSearch(head, word);
	//Whether it is present have to check whether it's the head or the tail
	if (DeletionNode) {
		if (DeletionNode->prev == nullptr) {
			cout << "Your word was '" << word << "'. The word '" << word << "' has been deleted." << endl;
			cout << "The next word would be '" << DeletionNode->next->val << "' " << endl;
			cout << "There is no word before '" << word << "' " << endl;
			DeletionNode->next->prev = nullptr;
			LinkedListNode* tempNode = DeletionNode->next;
			delete DeletionNode;
			return tempNode;
		}
		else if (DeletionNode->next == nullptr) {
			cout << "Your word was '" << word << "'. The word '" << word << "' has been deleted." << endl;
			cout << "There is no word following '" << word << "' " << endl;
			cout << "The previous word would be '" << DeletionNode->prev->val << "' " << endl;
			DeletionNode->prev->next = nullptr;
			delete DeletionNode;
			return head;
		}
		else {
			cout << "Your word was '" << word << "'. The word '" << word << "' has been deleted." << endl;
			cout << "The next word would be '" << DeletionNode->next->val << "' " << endl;
			cout << "The previous word would be '" << DeletionNode->prev->val << "' " << endl;
			DeletionNode->next->prev = DeletionNode->prev;
			DeletionNode->prev->next = DeletionNode->next;
			delete DeletionNode;
			return head;
		}
	}
	else {
		cout << "Your word was '" << word << "'. we did not find your word." << endl;
		return head;
	}
}

//Prints the Linked Lists starting with the node passed into the function
void PrintLinked(LinkedListNode* list) {
	while (list != nullptr) {
		cout << list->val << endl;
		list = list->next;
	}
}

//Helper function to print the current node, and the next and previous word
void PrintNodeWithNextAndPrev(LinkedListNode* node) {
	cout << "Your word was '" << node->val << "'. ";
	if (node->next) {
		cout << "The next word would be '" << node->next->val << "'" << endl;
	}
	else {
		cout << "There is no word following '" << node->val << "'" << endl;
	}
	if (node->prev) {
		cout << "The previous word would be '" << node->prev->val << "'" << endl;
	}
	else {
		cout << "There is no word before '" << node->val << "'" << endl;
	}
}

//Swaps the position of the two nodes passed in and adjusts the nodes with references to them as well
LinkedListNode* SwapNodes(LinkedListNode* node1, LinkedListNode* node2) {
	//Adapted from https://www.geeksforgeeks.org/swap-given-nodes-in-a-doubly-linked-list-without-modifying-data/#
	LinkedListNode* tempNode = nullptr;
	tempNode = node1->next;
	node1->next = node2->next;
	node2->next = tempNode;

	if (node1->next != nullptr) {
		node1->next->prev = node1;
	}
	if (node2->next != nullptr) {
		node2->next->prev = node2;
	}

	tempNode = node1->prev;
	node1->prev = node2->prev;
	node2->prev = tempNode;

	//Code to make sure there is not a loop in the list
	if (node1->prev != nullptr) {
		node1->prev->next = node1;
	}
	if (node2->prev != nullptr) {
		node2->prev->next = node2;
	}
	if (node2->val < node1->val) {
		return node2;
	}
	return node1;
}

//Returns the node position of the smallest node in the linked list
LinkedListNode* findMin(LinkedListNode* start) {
	//Keeps track of what the minimum node is
	//Runs through the list and adjusts minimum as needed and then returns that node
	LinkedListNode* minNode = start;
	LinkedListNode* traverser = start;
	while (traverser != nullptr) {
		if (traverser->val < minNode->val) {
			minNode = traverser;
		}
		traverser = traverser->next;
	}
	return minNode;
}

//Original BubbleSort attempt, leaving this one to chronicle my work
//LinkedListNode* BubbleSort(LinkedListNode* head, LinkedListNode** tail) {
//	LinkedListNode* temp = nullptr;
//	LinkedListNode* current = head;
//	LinkedListNode* headNode = head;
//	LinkedListNode* swappedVal = nullptr;
//	bool swapped = true;
//	//int swaps = 0;
//
//	//LinkedListNode* minNode = findMin(head);
//
//	if (head == nullptr) {
//		return head;
//	}
//
//	while (swapped) {
//		current = headNode;
//		swapped = false;
//		while (current != nullptr && current->next != nullptr) {
//			if (current->val > current->next->val) {
//				swappedVal = SwapNodes(current, current->next);
//				//swaps++;
//				//cout << swaps << endl;
//
//				if (swappedVal->prev == nullptr) {
//					PrintLinked(head);
//					headNode = swappedVal;
//				}
//				swapped = true;
//			}
//			current = current->next;
//		}
//		temp = current;
//
//	}
//	*tail = temp;
//	return headNode;
//}

//Bubble sort algorithm that adjusts the head and tail passed into the function
//Sorts in alphabetical order
LinkedListNode* BubbleSort(LinkedListNode* head, LinkedListNode** tail) {
	//If the list consists of only a head, nothing to sort
	if (head->next == nullptr) {
		return head;
	}
	//If only two nodes, just need to compare
	if (head->next->next == nullptr && head->val < head->next->val) {
		return head;
	}
	//Same as above only if the second node is actually the smaller one
	else if (head->next->next == nullptr && head->val > head->next->val) {
		head = SwapNodes(head, head->next);
		return head;
	}

	LinkedListNode* listIterator = head;
	LinkedListNode* newListHead = head;
	bool swapped = true;

	//In case there is more than 2 elements goes through the list until there is one complete
	//cycle without a swap happening
	while (swapped) {
		swapped = false;
		while (listIterator && listIterator->next) {
			if (listIterator->val > listIterator->next->val) {
				LinkedListNode* swapNode = SwapNodes(listIterator, listIterator->next);
				swapped = true;
				if (swapNode->prev == nullptr) {
					newListHead = swapNode;
				}
			}
			if (listIterator->next == nullptr) {
				*tail = listIterator;
			}
			listIterator = listIterator->next;
		}
		listIterator = newListHead;
	}
	*tail = FindTail(newListHead);
	return newListHead;

}

//Selection sort performed on the given head and tail
//Sorts in alphabetical order
LinkedListNode* SelectionSort(LinkedListNode* head, LinkedListNode** tail) {
	LinkedListNode* sortedHead = head;
	LinkedListNode* sortedTail = sortedHead;
	//Always select the minimum node and move it to the tail position

	LinkedListNode* initialMin = findMin(sortedHead);
	//Making sure the position in the head is the first minimum
	if (initialMin != sortedHead) {

		sortedHead = SwapNodes(sortedHead, initialMin);
	}

	sortedTail = sortedHead->next;

	while (sortedTail->next != nullptr) {
		LinkedListNode* currentMin = findMin(sortedTail);
		if (currentMin->val < sortedTail->val) {
			//swaps++;
			sortedTail = SwapNodes(sortedTail, currentMin);
		}
		sortedTail = sortedTail->next;
	}
	*tail = sortedTail;
	return sortedHead;
}

//Takes the list given by the head passed in, and writes it to the file with given filename
void WriteToFile(LinkedListNode* head, string fileName) {
	ifstream inputStream(fileName);
	//Checking if the file already exists
	if (inputStream.is_open()) {
		cout << "Writing to file ..." << endl;
		cout << "Error! File '" << fileName << "' already exists.";
		inputStream.close();
	}
	else {
		cout << "Writing to file ..." << endl;
		inputStream.close();
		ofstream outputStream(fileName);
		LinkedListNode* iteratorNode = head;
		while (iteratorNode != nullptr) {
			string currWord = iteratorNode->val;
			outputStream << currWord << "\n";
			iteratorNode = iteratorNode->next;
		}
		cout << "                         ...Done!";
		outputStream.close();
	}
}

//Takes a reference to a head and tail, and then opens the dictionary given by the string passed in
void OpenDict(LinkedListNode** head, LinkedListNode** tail, string dictNum) {
	unsigned int i = 0;
	//This line saves the given dictionary into a vector
	vector<string> toFill = fillVector(FILE_NAME + dictNum + FILE_SUFFIX);
	*head = AddNode(toFill.at(i));
	*tail = *head;
	for (i = 1; i < toFill.size(); i++) {
		*tail = AddNode(toFill.at(i), *tail);
	}
	cout << "Dictionary " << dictNum << " is open." << endl;
}

//Takes the head of a linked list and deletes every node from the heap
void DeleteList(LinkedListNode* head, LinkedListNode* tail) {
	//Always goes through the list and deletes the previous node, and goes until the end
	while (head->next) {
		if (head->prev) {
			delete head->prev;
		}
		head = head->next;
	}
	delete head;
	head = nullptr;
	tail = nullptr;
}

//Take the head and optional tail of a list to find the midpoint between two nodes or the whole list
LinkedListNode* FindMidpoint(LinkedListNode* head, LinkedListNode* tail = nullptr) {
	LinkedListNode* slow = head;
	LinkedListNode* fast = head;
	//Utilizing the fast and slow method to find the midpoint
	//Example of function "overloading" tail is an optional parameter, as this is used in other functions
	while (fast != tail && fast->next != tail) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

//Performs binary search on the given list
//Returns null or the node location of the target string
LinkedListNode* BinarySearch(LinkedListNode* head, LinkedListNode* tail, string target) {
	LinkedListNode* searchHead = head;
	LinkedListNode* searchTail = tail;
	LinkedListNode* searchMid = FindMidpoint(head, tail);
	while (searchHead->val < searchTail->val && searchHead->next != searchTail->prev) {
		//cout << "start: " << searchHead->val << ", mid: " << searchMid->val << ", end: " << searchTail->val << endl;
		//First checking all the special cases, namely whether our target is the head, tail, or middle
		if (target == searchHead->val) {
			PrintNodeWithNextAndPrev(searchHead);
			return searchHead;
		}
		else if (target == searchMid->val) {
			PrintNodeWithNextAndPrev(searchMid);
			return searchMid;
		}
		else if (target == searchTail->val) {
			PrintNodeWithNextAndPrev(searchTail);
			return searchTail;
		}
		//Otherwise we adjust on whether the target is larger or smaller than the middle, and repear the process
		if (target < searchMid->val) {
			searchHead = searchHead->next;
			searchTail = searchMid->prev;
			searchMid = FindMidpoint(searchHead, searchTail);
		}
		else if (target > searchMid->val) {
			searchHead = searchMid->next;
			searchTail = searchTail->prev;
			searchMid = FindMidpoint(searchHead, searchTail);
		}
	}
	cout << "start: " << searchHead->val << ", mid: " << searchMid->val << ", end: " << searchTail->val << endl;
	cout << "Your word was '" << target << "'. We did not find your word." << endl;
	return nullptr;
}

//Inserts an existing node rightt after the node passed with the first parameter
LinkedListNode* InsertNode(LinkedListNode* nodeBeforeInsertion, LinkedListNode* nodeToInsert) {
	LinkedListNode* tempForward = nullptr;
	//Checking the special conditions wheer we are inserting a node at the end
	if (!nodeBeforeInsertion->next) {
		nodeToInsert->next = nullptr;
		nodeToInsert->prev = nodeBeforeInsertion;
		nodeBeforeInsertion->next = nodeToInsert;
		return nodeToInsert;
	}
	if (nodeBeforeInsertion->next) {
		tempForward = nodeBeforeInsertion->next;
	}

	nodeBeforeInsertion->next = nodeToInsert;
	nodeToInsert->prev = nodeBeforeInsertion;
	nodeToInsert->next = tempForward;
	tempForward->prev = nodeToInsert;
	tempForward = nullptr;
	return nodeToInsert;
}

//Helper functon to find the "tail" of the list atfer certain operations


//Original MergList function that was very inefficient due to using the FindInsertionPoint Function
LinkedListNode* MergeLists(LinkedListNode* head1, LinkedListNode* head2) {
	if (head1->val < head2->val) {

		LinkedListNode* KeeperList = head1;
		LinkedListNode* removeList = head2;

		while (removeList != nullptr) {
			LinkedListNode* insertionPt = FindInsertionPoint(KeeperList, removeList->val);
			LinkedListNode* tempNode = removeList->next;
			if (insertionPt) {
				if (insertionPt->prev == nullptr) {
					KeeperList = InsertNode(insertionPt, removeList);
				}
				else if (insertionPt->val == removeList->val) {
					if (removeList->next) {
						removeList = removeList->next;
						delete removeList->prev;
					}
					else {
						delete removeList;
					}
				}
				else {
					InsertNode(insertionPt, removeList);
				}
				removeList = tempNode;
			}
			else {
				removeList = removeList->next;
			}
		}
		//(*tail1) = FindTail(head1);
		KeeperList = nullptr;
		removeList = nullptr;
		return head1;
	}
	else if (head2->val < head1->val) {

		LinkedListNode* KeeperList = head2;
		LinkedListNode* removeList = head1;

		while (removeList != nullptr) {
			LinkedListNode* insertionPt = FindInsertionPoint(KeeperList, removeList->val);
			LinkedListNode* tempNode = removeList->next;
			if (insertionPt) {
				if (insertionPt->prev == nullptr) {
					KeeperList = InsertNode(insertionPt, removeList);
				}
				else if (insertionPt->val == removeList->val) {
					if (removeList->next) {
						removeList = removeList->next;
						delete removeList->prev;
					}
					else {
						delete removeList;
					}
				}
				else {
					InsertNode(insertionPt, removeList);
				}
				removeList = tempNode;
			}
			else {
				removeList = removeList->next;
			}
		}
		//(*tail2) = FindTail(head2);
		KeeperList = nullptr;
		removeList = nullptr;
		return head2;
	}
	else {

		LinkedListNode* KeeperList = head1;
		LinkedListNode* removeList = head2;

		//Checking whether the second list only has one element, and therefore deleting and exiting
		if (head2->next) {
			removeList = removeList->next;
			delete removeList->prev;
		}
		else {
			delete head2;
			//(*tail1) = FindTail(head1);
			return head1;
		}

		while (removeList != nullptr) {
			LinkedListNode* insertionPt = FindInsertionPoint(KeeperList, removeList->val);
			LinkedListNode* tempNode = removeList->next;
			if (insertionPt) {
				if (insertionPt->prev == nullptr) {
					KeeperList = InsertNode(insertionPt, removeList);
				}
				else if (insertionPt->val == removeList->val) {
					removeList = removeList->next;
					delete removeList->prev;
				}
				else {
					InsertNode(insertionPt, removeList);
				}
				removeList = tempNode;
			}
			else {
				removeList = removeList->next;
			}
		}
		//(*tail1) = FindTail(head1);
		KeeperList = nullptr;
		removeList = nullptr;
		return head1;
	}
}


//Function that takes heads of two linked lists, and returns one alphabetical linked list
//Lists need to be alphabetical to have a valuable result
LinkedListNode* MergeVersion2(LinkedListNode* head1, LinkedListNode* head2) {
	//first checking whether each of the lists is empty and returning the other
	if (!head1 && !head2) {
		return nullptr;
	}
	if (!head1) {
		return head2;
	}
	if (!head2) {
		return head1;
	}

	//We're using a dummy node here to recursively adjust the lists and move one step further along each time
	LinkedListNode* dummyNode = nullptr;
	if (head1->val < head2->val) {
		dummyNode = head1;
		dummyNode->next = MergeVersion2(head1->next, head2);
	}
	else {
		dummyNode = head2;
		dummyNode->next = MergeVersion2(head1, head2->next);
	}

	//Special condition to check and account for duplicate values
	if (dummyNode->next != nullptr && dummyNode->next->val == dummyNode->val) {
		LinkedListNode* dummyDuplicate = dummyNode->next;
		dummyNode->next = dummyDuplicate->next;

		if (dummyDuplicate->next != nullptr) {
			dummyDuplicate->next->prev = dummyNode;
		}

		dummyDuplicate = nullptr;
	}
	else {
		dummyNode->next->prev = dummyNode;
		dummyNode->prev = nullptr;
	}


	return dummyNode;

}

//Merge sort algorithm, takes the head and tail of a list and puts it into alphabetical order
//Returns the head of the newly sorted list
LinkedListNode* MergeSort(LinkedListNode* head, LinkedListNode** tail) {
	//Checking for any of the special conditions where we only have one or none elements
	if (head == nullptr || head->next == nullptr || head == (*tail)) {
		return head;
	}
	//Recursively dividing the list evey time and cutting the elements in half in order
	//To then reassemble and return the new list
	else {
		LinkedListNode* midpoint = FindMidpoint(head, *tail);
		LinkedListNode* temp = midpoint->next;
		midpoint->next = nullptr;
		LinkedListNode* leftHalf = MergeSort(head, &midpoint);
		LinkedListNode* rightHalf = MergeSort(temp, tail);
		LinkedListNode* ReturnList = MergeVersion2(leftHalf, rightHalf);
		(*tail) = FindTail(ReturnList);
		return ReturnList;
	}
}

string GetValue(LinkedListNode* node) {
	return node->val;
}

int main()
{
	int dictNum;
	cout << "Which Dictionary should be opened? Enter a number between \"1\" and " << MAX_DICTIONARY_NUM << ":";
	cin >> dictNum;
	LinkedListNode* head = nullptr;
	LinkedListNode* tail = nullptr;
	OpenDict(&head, &tail, std::to_string(dictNum));

	int menuChoice = -1;
	while (menuChoice != 0) {
		cout << "\n--------------------------------------------\n"
			<< "Options menu: \n"
			<< " (1) Print words\n"
			<< " (2) Find a word\n"
			<< " (3) Find word, insert if not found (assumes words are sorted alphabetically)\n"
			<< " (4) Find word, delete if found \n"
			<< " (5) Swap two words\n"
			<< " (6) Sort words (Bubble Sort or Selection Sort)\n"
			<< " (7) Find a word - Binary Search (assumes words are sorted alphabetically)\n"
			<< " (8) Merge two dictionaries (will sort first)\n"
			<< " (9) Sort words (Merge Sort)\n"
			<< "(10) Sort words (Bucket Sort)\n"
			<< "(11) Load a dictionary (closes current dictionary)\n"
			<< "(12) Write current dictionary to file\n"
			<< "Enter a number from 1 to 12, or 0 to exit: ";

		cin >> menuChoice;

		switch (menuChoice)
		{
		case 0: {
			cout << "Thank you! Bye!" << endl;
			break;
		}
		case 1: {
			PrintLinked(head);
			break;
		}
		case 2: {
			string toSearch;
			cout << "Enter a word to search for in the chosen Dictionary:";
			cin >> toSearch;
			LinkedListNode* searchResult = LinearSearch(head, toSearch);
			if (searchResult) {
				PrintNodeWithNextAndPrev(searchResult);
			}
			else {
				cout << "Your word was '" << toSearch << "'. We did not find your word." << endl;
			}
			break;
		}
		case 3: {
			string toSearch;
			cout << "Enter a word to search for in the chosen Dictionary:";
			cin >> toSearch;
			LinkedListNode* searchResult = LinearSearch(head, toSearch);
			if (searchResult) {
				PrintNodeWithNextAndPrev(searchResult);
			}
			else {
				cout << "Your word was '" << toSearch << "'. We did not find your word." << " Adding word to dictionary...";
				cout << "Inserted!" << endl;
				LinkedListNode* insertionPoint = InsertNewNode(head, toSearch);
				if (insertionPoint->next) {
					cout << "The next word would be '" << insertionPoint->next->val << "'" << endl;
				}
				else {
					cout << "There is no word following '" << insertionPoint->val << "'" << endl;
				}
				if (insertionPoint->prev) {
					cout << "The previous word would be '" << insertionPoint->prev->val << "'" << endl;
				}
				else {
					head = insertionPoint;
					cout << "There is no word before '" << insertionPoint->val << "'" << endl;
				}
				break;
			}
		}
		case 4: {
			string toSearch;
			cout << "Enter a word to delete from the chosen Dictionary:";
			cin >> toSearch;

			//LinkedListNode* searchResult = LinearSearch(head, toSearch);
			head = DeleteNode(head, toSearch);
			break;
		}
		case 5: {
			cout << "Enter a word to search for in the chosen Dictionary: ";
			string firstWord;
			cin >> firstWord;
			LinkedListNode* searchResult = nullptr;
			searchResult = LinearSearch(head, firstWord);
			if (!searchResult) {
				cout << "Your word was '" << firstWord << "'. We did not find your word." << endl;
				cout << "Can't swap - word not found!" << endl;
				break;
			}
			PrintNodeWithNextAndPrev(searchResult);

			cout << "Enter a word to search for in the chosen Dictionary: ";
			string secondWord;
			cin >> secondWord;
			LinkedListNode* searchResult2 = nullptr;
			searchResult2 = LinearSearch(head, secondWord);
			if (!searchResult2) {
				cout << "Your word was '" << secondWord << "'. We did not find your word." << endl;
				cout << "Can't swap - word not found!" << endl;
				break;
			}
			PrintNodeWithNextAndPrev(searchResult2);

			if (searchResult != searchResult2) {
				cout << "Words '" << searchResult->val << "' and '" << searchResult2->val << "' have been swapped!";
				if (searchResult->prev == nullptr || searchResult2->prev == nullptr) {
					head = SwapNodes(searchResult, searchResult2);
				}
				else {
					SwapNodes(searchResult, searchResult2);
				}
			}
			else {
				cout << "Hey! Those are the same word!";
			}
			break;
		}
		case 6: {
			cout << "sorting..." << endl;
			head = BubbleSort(head, &tail);
			cout << "          ...Done!" << endl;
			break;
		}
		case 7: {
			head = BubbleSort(head, &tail);
			string searchTarget;
			cout << "Enter a word to search for in the chosen Dictionary: ";
			cin >> searchTarget;
			BinarySearch(head, tail, searchTarget);
			break;
		}
		case 8: {
			int secondDictNum;

			cout << "Which dictionary should be opened? Enter a number between \"1\" and " << MAX_DICTIONARY_NUM << ":" << endl;
			cin >> secondDictNum;

			while (secondDictNum == dictNum) {
				cout << "That dictionary is already open! Pick another." << endl;
				cout << "Which dictionary should be opened? Enter a number between \"1\" and " << MAX_DICTIONARY_NUM << ":" << endl;
				cin >> secondDictNum;
			}

			LinkedListNode* listTwoHead;
			LinkedListNode* listTwoTail;

			OpenDict(&listTwoHead, &listTwoTail, std::to_string(secondDictNum));
			head = BubbleSort(head, &tail);
			listTwoHead = BubbleSort(listTwoHead, &listTwoTail);
			cout << "Sorting..." << endl;
			cout << "Merging..." << endl;
			head = MergeVersion2(head, listTwoHead);
			tail = FindTail(head);
			cout << "...Done!" << endl;
			break;
		}
		case 9: {
			cout << "sorting..." << endl;

			head = MergeSort(head, &tail);

			cout << "          ...Done!" << endl;
			break;
		}
		case 10: {
			cout << "Coming soon!" << endl;
			break;
		}
		case 11: {
			cout << "Which Dictionary should be opened? Enter a number between \"1\" and " << MAX_DICTIONARY_NUM << ": ";
			int dictNum;
			cin >> dictNum;
			DeleteList(head, tail);
			head = nullptr;
			tail = nullptr;
			OpenDict(&head, &tail, std::to_string(dictNum));
			break;
		}
		case 12: {
			string fileName;
			cout << "Enter name of file (.txt will be appended automatically):";
			cin >> fileName;
			WriteToFile(head, fileName + FILE_SUFFIX);
			break;
		}
		default:
			cout << "Error! Input must be a number between 1 and 12, or 0 to exit." << endl;
			break;
		}

	}
	return 0;
} // end main ()



/* function returns a vector of dictionary words - possible inputs are 1, 2, & 3 *
* representing three different word lists. Function will return word list #3 if *
* any integer besides 1 or 2 is passed in.                                      *
*/
/* Note: not all versions of C++ support direct definition of a vector, hence a *
 * temporary array is used here.                                                *
 */
vector<string> fillVector(string fileName) {
	vector<string> dict;
	ifstream inputFileStream(fileName);
	if (inputFileStream.good()) {
		while (!inputFileStream.eof()) {
			string currentWord;
			inputFileStream >> currentWord;
			dict.push_back(currentWord);
		}
	}
	else {
		cout << "Bad";
	}
	inputFileStream.close();
	return dict;
}


/*
User Documentation:

Functions included in the LinkedList:

Basic structure representing the LinkedList
LinkedListNode(string val, LinkedListNode* prev, LinkedListNode* next)

After creating a head, this function can be used to insert a new Node at the end of the list
LinkedListNode AddNode(string val, LinkedListNode* tail = nullptr)
Example (Creating a new list and adding a Node):
LinkedListNode* head = nullptr;
LinkedListNode* tail = nullptr;
head = AddNode("hello");

Example (Taking a list and adding a new node):
LinkedListNode* head = AddNode("hello");
LinkedListNode* tail = head;
AddNode("second node", tail);

LinearSearch takes in the head of an existing LinkedList, searches for the passed value and returns the position
or nullptr if the value is not found
LinkedListNode* LinearSearch(LinkedListNode* head, string toSearch)
Example (Assume head points to a valid LinkedList):
LinkedListNode* searchResult = LinearSearch(head, "word");
if(searchResult){
	cout << "Word found";
}
else{
	cout << "Word not found";
}


LinkedListNode* FindInsertionPoint(LinkedListNode* head, string word)

When required to insert a node in the correct alphabetical position this function can be used, returns the node where
the new node is located
LinkedListNode* InsertNewNode(LinkedListNode* head, string word)
Example (Given that head points to a valid LinkedList):
LinkedListNode* newNode = InsertNewNode(head, "new node");

This function will scan the list given by head, and delete the word if found
Returns the node that followed the deleted node
LinkedListNode* DeleteNode(LinkedListNode* head, string word)
Example (Given that head points to a valid LinkedList)
LinkedListNode* afterDelete = DeleteNode(head, "delete this");

String representation of the LinkedList, starts with the node passed in typically head
void PrintLinked(LinkedListNode* list)
Example (Given that head points to a valid LinkedList(A,B,C)):
PrintLinked(head);
Output:
A
B
C

Prints a string representation of a single node, and next and previous if applicable
void PrintNodeWithNextAndPrev(LinkedListNode* node)
Example (Given that head points to avalid LinkedList(A,B,C)):
PrintNodeWithNextAndPrev(head);
Output:
Your word was A
There is no word before A
The next word would be B

PrintNodeWithNextAndPrev(head->next);
Output:
Your word was B
The previous word would be A
The next word would be C

PrintNodeWithNextAndPrev(head->next->next);
Output:
Your word was C
The previous word would be B
There is no word following C

When necessary to swap two nodes, use this function
The two passed in nodes will be completely swapped (not just the values)
When swapping, if the head is to be swapped you need to reassign your head variable
LinkedListNode* SwapNodes(LinkedListNode* node1, LinkedListNode* node2)
Example (Given that head is valid LinkedList(A,B,C)):
head = SwapNodes(head,head->next->next)
The list will now be (C,B,A)


Helper function mainly used in some sorting, can be used by the user to find the smallest value
Returns the Node with the smalles value alphabetically
LinkedListNode* findMin(LinkedListNode* start)
Example (Given that head is a valid LinkedList(A,B,C))
LinkedListNode* smallestVal = findMin(head);
smallestVal will contain the Node pointing to A

Bubble sort algorithm that will put the passed list into alphabetical order
Automatically adjusts the position the tail, the return value will be the new head
LinkedListNode* BubbleSort(LinkedListNode* head, LinkedListNode** tail)
Example (Given that head is a valid LinkedList(C,A,B))
head = BubbleSort(head, &tail);
Head will now point to A, and tail to C

Bubble sort algorithm that will put the passed list into alphabetical order
Automatically adjusts the position the tail, the return value will be the new head
LinkedListNode* SelectionSort(LinkedListNode* head, LinkedListNode** tail)
Example (Given that head is a valid LinkedList(C,A,B))
head = SelectionSort(head, &tail);
Head will now point to A, and tail to C


Function to export the LinkedList onto a file, the file will automatically have the ".txt" extensions applied
Will only write to File if there is no existing file with the same name present
void WriteToFile(LinkedListNode* head, string fileName)
Example (Given that head is a valid LinkedList(C,A,B))
WriteToFile(head, dict)
Will create a file called dict.txt that contains the LinkedList words

Function used to open a dictionary from a ".txt" file, the file will need to be called dictionary[number].txt
If the file exists, will read each line into a seperate node of the LinkedList
Required a head and tail node to be passed in
void OpenDict(LinkedListNode** head, LinkedListNode** tail, string dictNum)
Example:
LinkedListNode* head = nullptr;
LinkedListNode* tail = nullptr;
OpenDict(head, tail, 10);
Will open dictionary10.txt and read it in, if it exists

When called upon, this function takes the head and tail of your LinkedList and deletes all the Nodes from the heap
Recommended to make head and tail nullptr when done with this operation
void DeleteList(LinkedListNode* head, LinkedListNode* tail)
Example (Given that head is a valid LinkedList(C,A,B))
DeleteList(head,tail);
head = nullptr;
tail = nullptr;

Function to find the midpoint of the LinkedList
Used as a helper function for other functions, but can be used to find the middle between head and tail if needed
Will always return the lower middle in an even numbered list
Tail is an optional parameter to get the middle of a subset of the list
When tail is not provided will automatically get the middle of the whole list
LinkedListNode* FindMidpoint(LinkedListNode* head, LinkedListNode* tail = nullptr)
Example (Given that head is a valid LinkedList(A,B,C))
LinkedListNode* midpt = FindMidpoint(head)
Output:
midpt will contain the Node B

midpt = FindMidpoint(head,head->next);
Output:
midpt will contain the node A, since it is the half of 2

BinarySearch function that will either return the Node of the target string, or nullptr if the value does not exist
Requires a sorted list to function correctly, make sure to call one of the sorting algorithms before
LinkedListNode* BinarySearch(LinkedListNode* head, LinkedListNode* tail, string target)
Example (Given that head is a valid LinkedList(C,A,B))
head = BubbleSort(head,&tail);
LinkedListNode* searchResult = BinarySearch(head,tail,"B");
Output:
searchResult will contain the Node with value B

Function used for precise insertion of nodes, need to pass in the node before and the node to insert
Will return a reference to the node passed in
Cannot insert node into the head position
LinkedListNode* InsertNode(LinkedListNode* nodeBeforeInsertion, LinkedListNode* nodeToInsert)
Example (Given that head is a valid LinkedList(A,B,C))


Function used to recover the tail, when a function may alter the tail
Should be used before any of the functions that interact with the tail, if the integrity of the tail may be in question
LinkedListNode* FindTail(LinkedListNode* head)
Example (Given that head is a valid LinkedList(A,B,C))
tail = FindTail(head);
tail should now contain C

Function that merges two LinkedLists and retains their alphabetical shape
The lists need to be sorted before merging them
It is recommended to call MergeSort before calling this function
Duplicate values are discarded
LinkedListNode* MergeVersion2(LinkedListNode* head1, LinkedListNode* head2)
Example (Given that head1 and head2 are valid LinkedList (A,B,C) (C,D,E)
head1 = MergeVersion2(head1,head2);
Output:
head1 = (A,B,C,D,E

Function that performs a merge sort to bring the data into alphabetical order
Returns the head to the new sorted list, and automatically adjusts the tail
LinkedListNode* MergeSort(LinkedListNode* head, LinkedListNode** tail)
Example (Given tha head is a valid LinkedList(B,A,C,)
head = MergeSort(head, &tail);
Output:
head = A
tail = C
LinkedList head = A,B,C

Function that returns the string value of a particular node
string GetValue(LinkedListNode* node)
Example (Given head is a valid LinkedList(A,B,C):
cout << GetValue(head) << endl;
cout << GetValue(head->next);
Output
A
B
*/







