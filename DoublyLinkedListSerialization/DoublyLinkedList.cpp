#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList()
{
	srand(time(0));
}

DoublyLinkedList::~DoublyLinkedList()
{
	while (this->tail != NULL)
	{
		this->head = this->head->next;
		delete this->head->prev;
		this->head->prev = NULL;
		if (this->head == this->tail)
		{
			delete this->head;
			this->tail = NULL;
			this->head = NULL;
		}
	}
}

void DoublyLinkedList::serialize(const string& fileName)
{
	try
	{
		if (!this->isListEmpty())
		{
			ofstream fin(fileName, ios::binary);

			ListNode* currentNode = this->head;
			for (size_t currentElement = 0; currentElement < this->count; currentElement++)
			{
				int datalength = currentNode->data.length() + 1;
				fin.write((char*)&datalength, sizeof(datalength));
				fin.write((char*)currentNode->data.c_str(), datalength);

				currentNode = currentNode->next;
			}
			fin.close();
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << "Failed to save list data to a file!" << std::endl;
	}
}

void DoublyLinkedList::deserialize(const string& fileName)
{
	try
	{
		ifstream fout;
		fout.exceptions(ifstream::badbit | ifstream::failbit);
		fout.open(fileName);

		while (!fout.eof())
		{
			string currentData = "";
			int datalength = 0;
			fout.read((char*)&datalength, sizeof(datalength));
			char* buffer = new char[datalength];
			fout.read(buffer, datalength);
			currentData = buffer;
			delete[]buffer;

			this->add(currentData);
		}
		fout.close();
	}
	catch (const ifstream::failure& ex)
	{
		if (ex.code().value() != 1) // другие исключения кроме отсутствия или недоступности файла
		{
			std::cout << "Failed to load list data from the file!" << std::endl;
		}
	}
}

void DoublyLinkedList::Serialize(const char* fileName)
{
	FILE* file;
	if ((file = fopen(fileName, "wb")) == NULL)
	{
		perror("Failed to save list data to a file!");
		return;
	}

	fwrite(&this->count, sizeof(int), 1, file);
	ListNode* currentNode = this->head;
	for (size_t currentElement = 0; currentElement < this->count; currentElement++)
	{
		int datalength = currentNode->data.length() + 1;
		fwrite(&datalength, sizeof(datalength), 1, file);
		fwrite(currentNode->data.c_str(), datalength, 1, file);

		currentNode = currentNode->next;
	}
	fclose(file);
}

void DoublyLinkedList::Deserialize(const char* fileName)
{
	FILE* file;
	if ((file = fopen(fileName, "rb")) == NULL)
	{
		perror("Failed to load list data from the file!");
		return;
	}

	int stringCount = 0;
	fread(&stringCount, sizeof(int), 1, file);
	for (size_t i = 0; i < stringCount; i++)
	{
		int datalength = 0;
		fread(&datalength, sizeof(datalength), 1, file);
		char* buffer = new char[datalength];
		fread(&buffer, datalength, 1, file);
		std::string currentData = "";
		currentData = buffer;
		delete[]buffer;
 
		this->add(currentData);
	}
	fclose(file);
}



void DoublyLinkedList::addNode(ListNode* newNode)
{
	if (this->head == NULL) // если добавляемый элемент первый
	{
		this->head = this->tail = newNode; //первый узел является началом и концом 
		newNode->next = newNode->prev = newNode; // указатели на следующий и предыдущий узлы первого узла указывают на него же
	}
	else
	{
		newNode->prev = this->tail;
		this->tail->next = newNode;
		newNode->next = this->head;
		this->tail = newNode;
		this->head->prev = this->tail;
	}

	newNode->rand = this->getRandomElement();

	this->count++;
}

void DoublyLinkedList::add(const string& data)
{
	ListNode* newNode = new ListNode();
	newNode->data = data;

	this->addNode(newNode);
}

ListNode* DoublyLinkedList::findByIndex(int index)
{
	if (this->head == NULL)
	{
		std::cout << "Failed to find list node by index in the list, the list is empty!" << std::endl;
		return NULL;
	}
	ListNode* currentNode;

	if (index == 0)
	{
		return this->head;
	}
	else
	{
		currentNode = this->head; // начать с начала списка
		int currentIndex = 1;
		while (currentIndex != index)
		{
			currentNode = currentNode->next; // пока следующий узел не является искомым
			currentIndex++;
		}
		return currentNode->next;
	}
}

ListNode* DoublyLinkedList::findeByData(string& data)
{
	if (this->head == NULL)
	{
		cout << "Failed to find list node by data, the list is empty!" << std::endl;
		return NULL;
	}
	if (this->head->data == data)
	{
		return this->head;
	}

	ListNode* currentNode = this->head;
	while (currentNode->data != data)
	{
		if (currentNode->next != NULL)
		{
			currentNode = currentNode->next;
		}
		else
		{
			cout << "Failed to find list node by data, data not found!" << std::endl;
			return NULL;
		}
	}
	return currentNode->next;
}

void DoublyLinkedList::del(ListNode* node)
{
	if (this->head == NULL)
	{
		cout << "Failed to delite list node, the list is empty!" << std::endl;
		return;
	}
	if ((node == this->head) && (this->head == this->tail))
	{
			count = 0;
			delete this->head;
			this->tail = NULL;
			this->head = NULL;
	}
	else
	{
		ListNode* currentNode = node->prev;

		currentNode->next = node->next;
		currentNode = node->next;
		currentNode->prev = node->prev;
		this->count--;
		if (node == this->head)
		{
			this->head = node->next;
		}
		else
		if (node == this->tail)
		{
			this->tail = node->prev;
		}
		currentNode = NULL;
		delete node;
	}
}

bool DoublyLinkedList::isListEmpty()
{
	return ((this->head == NULL) && (this->count == 0)) ? true : false;
}

ListNode* DoublyLinkedList::getFirstElement()
{
	return this->head;
}

ListNode* DoublyLinkedList::getLastElement()
{
	return this->tail;
}

ListNode* DoublyLinkedList::getRandomElement()
{
	int randomNumber = 0;
	if (count != 0)
	{
		randomNumber = rand() % this->count;
	}
	return this->findByIndex(randomNumber);
}

int DoublyLinkedList::getCountElements()
{
	return this->count;
}



