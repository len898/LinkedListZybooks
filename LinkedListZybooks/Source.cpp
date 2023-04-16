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

#define FILE_ONE "short_dict.txt"
#define FILE_TWO "short_dict2.txt"
#define FILE_THREE "short_dict3.txt"

#define NEW_DICT_FILE "Updated Dictionary.txt"
#define NEW_DICT_FILE_TWO "Updated Dictionary2.txt"
#define NEW_DICT_FILE_THREE "Updated Dictionary3.txt"

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
	while (iterator->next) {
		if (iterator->val < word && iterator->next->val > word) {
			return iterator;
		}
		iterator = iterator->next;
	}
	return iterator;
}

LinkedListNode* InsertNode(LinkedListNode* head, string word) {
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

LinkedListNode* SelectionSort(LinkedListNode* head) {
	LinkedListNode* sortedHead = head;
	LinkedListNode* sortedTail = sortedHead;
	int swaps = 0;
	int count = 0;

	LinkedListNode* initialMin = findMin(sortedHead);
	if (initialMin != sortedHead) {
		count++;
		sortedHead = SwapNodes(sortedHead, initialMin);
		swaps++;
		cout << "***total swaps = " << swaps << ", count = " << count << " ***" << endl;
		PrintLinked(sortedHead);
	}
	else {
		count++;
		cout << "***total swaps = " << swaps << ", count = " << count << " ***" << endl;
		PrintLinked(sortedHead);
	}
	sortedTail = sortedHead->next;

	while (sortedTail != nullptr) {
		count++;
		if (findMin(sortedTail)->val < sortedTail->val) {
			swaps++;
			sortedTail = SwapNodes(sortedTail, findMin(sortedTail));
		}
		cout << "***total swaps = " << swaps << ", count = " << count << " ***" << endl;
		PrintLinked(sortedHead);
		sortedTail = sortedTail->next;
	}
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
			outputStream << currWord;
			iteratorNode = iteratorNode->next;
		}
		cout << "                         ...Done!";
		outputStream.close();
	}
}



int main()
{
	int dictNum;
	cout << "Which Dictionary should be opened? Enter \"1\", \"2\", or \"3\":";
	cin >> dictNum;
	LinkedListNode* head = NULL;
	LinkedListNode* tail = NULL;
	if (dictNum == 1) {
		unsigned int i = 0;
		vector<string> toFill = fillVector(FILE_ONE);
		head = AddNode(toFill.at(i));
		tail = head;
		for (i = 1; i < toFill.size(); i++) {
			tail = AddNode(toFill.at(i), tail);
		}
	}
	else if (dictNum == 2) {
		unsigned int i = 0;
		vector<string> toFill = fillVector(FILE_TWO);
		head = AddNode(toFill.at(i));
		tail = head;
		for (i = 1; i < toFill.size(); i++) {
			tail = AddNode(toFill.at(i), tail);
		}
	}
	else if (dictNum == 3) {
		unsigned int i = 0;
		vector<string> toFill = fillVector(FILE_THREE);
		head = AddNode(toFill.at(i));
		tail = head;
		for (i = 1; i < toFill.size(); i++) {
			tail = AddNode(toFill.at(i), tail);
		}
	}
	int menuChoice = -1;
	while (menuChoice != 0) {
		cout << "\n--------------------------------------------\n"
			<< "Options menu: \n"
			<< "(1) Print words\n"
			<< "(2) Find a word\n"
			<< "(3) Find word, insert if found (assumes words are sorted alphabetically)\n"
			<< "(4) Find word, delete if found \n"
			<< "(5) Swap two words\n"
			<< "(6) Sort words (Bubble Sort or Selection Sort)\n"
			<< "(7) Find a word - Binary Search (assumes words are sorted alphabetically)\n"
			<< "(8) Merge two dictionaries (will sort first)\n"
			<< "(9) Write current dictionary to file\n"
			<< "Enter a number from 1 to 9, or 0 to exit: ";

		cin >> menuChoice;

		switch (menuChoice)
		{
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
				cout << "Your word was '" << searchResult->val << "'. ";
				if (searchResult->next) {
					cout << "The next word would be '" << searchResult->next->val << "'" << endl;
				}
				else {
					cout << "There is no word following '" << searchResult->val << "'" << endl;
				}
				if (searchResult->prev) {
					cout << "The previous word would be '" << searchResult->prev->val << "'" << endl;
				}
				else {
					cout << "There is no word before '" << searchResult->val << "'" << endl;
				}
				break;
			}
			else {
				cout << "Your word was '" << toSearch << "'. We did not find your word." << endl;
				break;
			}
		}
		case 3: {
			string toSearch;
			cout << "Enter a word to search for in the chosen Dictionary:";
			cin >> toSearch;
			LinkedListNode* searchResult = LinearSearch(head, toSearch);
			if (searchResult) {
				cout << "Your word was '" << searchResult->val << "'. ";
				if (searchResult->next) {
					cout << "The next word would be '" << searchResult->next->val << "'" << endl;
				}
				else {
					cout << "There is no word following '" << searchResult->val << "'" << endl;
				}
				if (searchResult->prev) {
					cout << "The previous word would be '" << searchResult->prev->val << "'" << endl;
				}
				else {
					cout << "There is no word before '" << searchResult->val << "'" << endl;
				}
				break;
			}
			else {
				cout << "Your word was '" << toSearch << "'. We did not find your word." << " Adding word to dictionary...";
				cout << "Inserted!" << endl;
				LinkedListNode* insertionPoint = InsertNode(head, toSearch);
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

			LinkedListNode* searchResult = LinearSearch(head, toSearch);
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
			head = SelectionSort(head);
			cout << "          ...Done!" << endl;
			break;
		}
		case 7: {
			cout << "Coming soon!" << endl;
			break;
		}
		case 8: {
			cout << "Coming soon!" << endl;
			break;
		}
		case 9: {
			if (dictNum == 1) {
				WriteToFile(head, NEW_DICT_FILE);
			}
			else if (dictNum == 2) {
				WriteToFile(head, NEW_DICT_FILE_TWO);
			}
			else {
				WriteToFile(head, NEW_DICT_FILE_THREE);
			}
			break;
		}
		default:
			break;
		}

	}


	cout << "Thank you! Bye!" << endl;

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
	if (!inputFileStream.bad()) {
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







