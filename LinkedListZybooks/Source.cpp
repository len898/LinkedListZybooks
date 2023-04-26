/********************************************************************************
 *		TITLE
 *		author(s):
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

 //const std::string FILE_ONE_ = std::string(FILE_ONE);

using namespace std;

/* function returns a vector of dictionary words - possible inputs are 1, 2, & 3 *
 * representing three different word lists. Function will return word list #3 if *
 * any integer besides 1 or 2 is passed in.                                      *
 */
 //vector<string> fillVector(int choice);
vector<string> fillVector(string fileName);


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

LinkedListNode* AddNode(string val, LinkedListNode* listEnd = nullptr) {
	if (!listEnd) {
		return new LinkedListNode(val, listEnd, nullptr);
	}
	else {
		LinkedListNode* current = new LinkedListNode(val, listEnd, nullptr);
		listEnd->next = current;
		return current;
	}
}

LinkedListNode* LinearSearch(LinkedListNode* head, string toSearch) {

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

LinkedListNode* FindInsertionPoint(LinkedListNode* head, string word) {
	LinkedListNode* iterator = head;
	if (head->val > word) {
		return head;
	}
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

LinkedListNode* InsertNewNode(LinkedListNode* head, string word) {
	LinkedListNode* nodeBeforeInsert = FindInsertionPoint(head, word);
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


LinkedListNode* DeleteNode(LinkedListNode* head, string word) {
	LinkedListNode* DeletionNode = LinearSearch(head, word);
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

void PrintLinked(LinkedListNode* list) {
	while (list != nullptr) {
		cout << list->val << endl;
		list = list->next;
	}
}

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

LinkedListNode* findMin(LinkedListNode* start) {
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

LinkedListNode* BubbleSort(LinkedListNode* head, LinkedListNode** tail) {
	if (head->next == nullptr) {
		return head;
	}
	if (head->next->next == nullptr && head->val < head->next->val) {
		return head;
	}
	else if (head->next->next == nullptr && head->val > head->next->val) {
		head = SwapNodes(head, head->next);
		return head;
	}

	LinkedListNode* listIterator = head;
	LinkedListNode* newListHead = head;
	bool swapped = true;

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
		//*tail = listIterator;
		listIterator = newListHead;
	}
	//cout << "Tail: " << (*tail)->val << endl;
	return newListHead;

}

LinkedListNode* SelectionSort(LinkedListNode* head, LinkedListNode** tail) {
	LinkedListNode* sortedHead = head;
	LinkedListNode* sortedTail = sortedHead;


	LinkedListNode* initialMin = findMin(sortedHead);
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

void WriteToFile(LinkedListNode* head, string fileName) {
	ifstream inputStream(fileName);
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

void OpenDict(LinkedListNode** head, LinkedListNode** tail, string dictNum) {
	unsigned int i = 0;
	vector<string> toFill = fillVector(FILE_NAME + dictNum + FILE_SUFFIX);
	*head = AddNode(toFill.at(i));
	*tail = *head;
	for (i = 1; i < toFill.size(); i++) {
		*tail = AddNode(toFill.at(i), *tail);
	}
	cout << "Dictionary " << dictNum << " is open." << endl;
}

void DeleteList(LinkedListNode* head, LinkedListNode* tail) {
	while (head->next) {
		if (head->prev) {
			delete head->prev;
		}
		head = head->next;
	}
	head = nullptr;
	tail = nullptr;
}

LinkedListNode* FindMidpoint(LinkedListNode* head, LinkedListNode* tail = nullptr) {
	LinkedListNode* slow = head;
	LinkedListNode* fast = head;

	while (fast != tail && fast->next != tail) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

LinkedListNode* BinarySearch(LinkedListNode* head, LinkedListNode* tail, string target) {
	LinkedListNode* searchHead = head;
	LinkedListNode* searchTail = tail;
	LinkedListNode* searchMid = FindMidpoint(head, tail);
	while (searchHead->val < searchTail->val && searchHead->next != searchTail->prev) {
		cout << "start: " << searchHead->val << ", mid: " << searchMid->val << ", end: " << searchTail->val << endl;
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

LinkedListNode* InsertNode(LinkedListNode* nodeBeforeInsertion, LinkedListNode* nodeToInsert) {
	LinkedListNode* tempForward = nullptr;
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

LinkedListNode* FindTail(LinkedListNode* head) {
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

LinkedListNode* MergeLists(LinkedListNode* head1, LinkedListNode* head2, LinkedListNode** tail1, LinkedListNode** tail2) {
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
		(*tail1) = FindTail(head1);

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
		(*tail2) = FindTail(head2);

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
			(*tail1) = FindTail(head1);
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
		(*tail1) = FindTail(head1);
		return head1;
	}
}



LinkedListNode* MergeSort(LinkedListNode* head, LinkedListNode** tail) {
	if (head == nullptr || head->next == nullptr || head == (*tail)) {
		return head;
	}
	else {
		LinkedListNode* midpoint = FindMidpoint(head, *tail);
		LinkedListNode* temp = midpoint->next;
		midpoint->next = nullptr;
		LinkedListNode* leftHalf = MergeSort(head, &midpoint);
		LinkedListNode* rightHalf = MergeSort(temp, tail);
		LinkedListNode* ReturnList = MergeLists(leftHalf, rightHalf, tail, tail);
		(*tail) = FindTail(ReturnList);
		return ReturnList;
	}
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
			head = MergeLists(head, listTwoHead, &tail, &listTwoTail);
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







