#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

struct ListNode {
	ListNode*	  prev;
	ListNode*     next;
	ListNode*     rand;
	string   data;
};

// динамический двусвязный циклический список
class DoublyLinkedList
{
public:

	DoublyLinkedList();
	~DoublyLinkedList();

	//запись и чтение файла средствами C++

	void serialize(const string& fileName);
	void deserialize(const string& fileName);

	//запись и чтение файла средствами C

	void Serialize(const char* fileName);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
	void Deserialize(const char* fileName);  // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

	void add(const string& data);
	ListNode* findByIndex(int index);
	ListNode* findeByData(string& data);
	void del(ListNode* node);

	bool isListEmpty();

	ListNode* getFirstElement();
	ListNode* getLastElement();
	ListNode* getRandomElement();
	int getCountElements();
private:

	void addNode(ListNode* newNode);

	ListNode* head = NULL;
	ListNode* tail = NULL;

	int count = 0;
};

