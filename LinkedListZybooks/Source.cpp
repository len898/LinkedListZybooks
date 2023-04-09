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

using namespace std;

/* function returns a vector of dictionary words - possible inputs are 1, 2, & 3 *
 * representing three different word lists. Function will return word list #3 if *
 * any integer besides 1 or 2 is passed in.                                      *
 */
vector<string> fillVector(int choice);

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
	LinkedListNode* newNode = new LinkedListNode(word, nodeBeforeInsert, nodeBeforeInsert->next);
	nodeBeforeInsert->next->prev = newNode;
	nodeBeforeInsert->next = newNode;
	return newNode;
}

void PrintLinked(LinkedListNode* list) {
	while (list != nullptr) {
		cout << list->val << endl;
		list = list->next;
	}
}


int main()
{
	int dictNum;
	cout << "Which Dictionary should be opened? Enter \"1\", \"2\", or \"3\":";
	cin >> dictNum;
	unsigned int i = 0;
	vector<string> toFill = fillVector(dictNum);
	LinkedListNode* head = AddNode(toFill.at(i));
	LinkedListNode* tail = head;
	for (i = 1; i < toFill.size(); i++) {
		tail = AddNode(toFill.at(i), tail);
	}

	string toSearch;
	cout << "Enter a word to search for in the chosen Dictionary:";
	cin >> toSearch;

	LinkedListNode* searchResult = LinearSearch(head, toSearch);

	if (searchResult) {
		cout << "Your word was '" << searchResult->val << "'. The next word would be '" << searchResult->next->val << "'. The previous word would be '" << searchResult->prev->val << "'.";
	}
	else {
		cout << "Your word was '" << toSearch << "'. We did not find your word." << " Adding word to dictionary...";
		cout << "Inserted!" << endl;
		LinkedListNode* insertionPoint = InsertNode(head, toSearch);
		if (insertionPoint->next) {
			cout << "The next word would be '" << insertionPoint->next->val << "'." << endl;
		}
		else {
			cout << "There is no word after '" << insertionPoint->val << "'." << endl;
		}
		if (insertionPoint->prev) {
			cout << "The previous word would be '" << insertionPoint->prev->val << "'.";
		}
		else {
			cout << "There is no word before '" << insertionPoint->val << "'." << endl;
		}
	}

	PrintLinked(head);

	return 0;
} // end main ()



/* function returns a vector of dictionary words - possible inputs are 1, 2, & 3 *
* representing three different word lists. Function will return word list #3 if *
* any integer besides 1 or 2 is passed in.                                      *
*/
/* Note: not all versions of C++ support direct definition of a vector, hence a *
 * temporary array is used here.                                                *
 */
vector<string> fillVector(int choice) {
	vector<string> dict;

	string temp1[] = { "airy", "aisle", "aisles", "ajar", "akimbo", "akin", "juveniles",
					"juxtapose", "knowledges", "known", "president", "tries", "trifle",
					"tugs", "wrongdoers", "wroth", "wyvern", "xenophon", "xylol", "yodle",
					"yurt", "zeugma", "ziggurat", "zootomy" };
	unsigned int size1 = 24;
	string temp2[] = { "aback", "abased", "acknowledgers", "administers", "affair",
					"aforementioned", "aggrieving", "agitating", "agree", "airlines", "ajar",
					"basin", "bawdy", "cheap", "cheated", "examiner", "excel",
					"lewdness", "liberal", "mathematician", "ordered", "president", "sandwich",
					"swagger", "swarm", "vomit", "yell", "zero", "zodiac", "zoo" };
	unsigned int size2 = 30;
	string temp3[] = { "ajar", "anachronism", "bleed", "bystander", "chariot", "clay",
					"contrive", "critiques", "databases", "derivative", "dog", "earthenware",
					"basin", "bawdy", "cheap", "cheated", "examiner", "excel",
					"echo", "fatiguing", "floppy", "goldsmith", "halt", "implies",
					"jam", "klutz", "lively", "malt", "meteor", "nonsense", "orphans",
					"paint", "playful", "railroad", "revolt", "shark", "spook", "syntax",
					"tablet", "thing", "ugly", "vigilant", "whirr", "yell", "zap", "zoo" };
	unsigned int size3 = 46;
	switch (choice) {
	case 1:
		for (unsigned int i = 0; i < size1; i++) {
			dict.push_back(temp1[i]);
		}
		break;
	case 2:
		for (unsigned int i = 0; i < size2; i++) {
			dict.push_back(temp2[i]);
		}
		break;
	default:
		for (unsigned int i = 0; i < size3; i++) {
			dict.push_back(temp3[i]);
		}
	}//end switch


	return dict;
} //end fillVector()





