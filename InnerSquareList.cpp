#include "InnerSquareList.h"

using namespace std;

//returns header pointer
Node* InnerSquareList::getHeader()
{
	return m_header;
}

//returns tail pointer
Node* InnerSquareList::getTail()
{
	return m_tail;
}

//constructor with no given data (empty inner list)
InnerSquareList::InnerSquareList() : m_header(NULL), m_tail(NULL), m_length(0)
{

}

//initialize an inner list with given data
InnerSquareList::InnerSquareList(Node* header, Node* tail, size_t length) : m_header(header), m_tail(tail), m_length(length)
{

}

//deconstructor
InnerSquareList::~InnerSquareList()
{
	
}

//delete all dynamically allocated nodes
void InnerSquareList::clean()
{

	while(m_header != NULL)
	{
		remove(0);
	}

}

//data should be at position "pos" after insertion
void InnerSquareList::add(int pos, int data)
{
	
	//create new current node for traversing
	Node *newData = new Node();
	newData->value = data;
	newData->next = NULL;

	Node *current = new Node();
	current = m_header;

	//create a node that points to previous for reference
	Node *prevNode = new Node();
	prevNode = NULL;
	
	//loop until iterators are at desired location
	int position = 0;
	while (position != pos && current->next != NULL)
	{
		position = position + 1;
		prevNode = current;
		current = current->next;
	}
	
	//This instance would be adding at the begining of list
	if (current == m_header && position == pos)
	{
		addFirst(data);
		delete newData;
	}

	//This instance would be adding somewhere in middle of list
	else if (position == pos)
	{
		newData->next = current;
		prevNode->next = newData;
		m_length = m_length + 1;
	}

	//This instance would be adding at the end of the list
	else if (current->next == NULL && (position + 1) == pos)
	{
		addLast(data);
		delete newData;
	}

	//When the position argument is out of bounds
	else 
	{
		cout << "Error: " << pos << " is out of bounds." << endl;
	}
	
	//free iterators memory
	current = NULL;
	prevNode = NULL;
	delete current;
	delete prevNode;

}

//push_front of STL
void InnerSquareList::addFirst(int data)
{

	//create new node to be added
	Node *newData = new Node();
	newData->next = NULL;
	newData->value = data;

	//if empty list
	if (m_header == NULL)
	{
		m_tail = newData;
		m_header = newData;
		m_length = m_length + 1;
	}
	//if list is not empty
	else 
	{
		newData->next = m_header;
		m_header = newData;
		m_length = m_length + 1;
	}

}

//insert as the last element
void InnerSquareList::addLast(int data)
{

	//create node to be added
	Node *newData = new Node();
	newData->next = NULL;
	newData->value = data;

	//if empty list
	if (m_header == NULL)
	{
		m_header = newData;
		m_tail = newData;
		m_length = m_length + 1;
	}
	//if list is not empty
	else 
	{
		m_tail->next = newData;
		m_tail = newData;
		m_length = m_length + 1;
	}

}

//remove node, position starts from 0
int InnerSquareList::remove(int pos)
{

	//create iterators
	Node *current = new Node();
	current = m_header;

	Node *prevNode = new Node();
	prevNode = NULL;
	
	//loop until ilerators are in desired position
	int valueToReturn = 0;
	int position = 0;
	while (position != pos && current->next != NULL)
	{
		position = position + 1;
		prevNode = current;
		current = current->next;
	}
	
	//This instance would be if removing the first element
	if (current == m_header && position == pos)
	{
		//If the list has more than one element
		if (current->next != NULL)
		{
			m_header = current->next;
			valueToReturn = current->value;
			delete current;
			m_length = m_length - 1;
		}
		//If list only has one element
		else if (current->next == NULL)
		{
			m_header = NULL;
			m_tail = NULL;
			valueToReturn = current->value;
			delete current;
			m_length = m_length - 1;
		}
	}

	//This instance would be if removing the last element
	else if (current == m_tail && position == pos)
	{
		m_tail = prevNode;
		prevNode->next = NULL;
		valueToReturn = current->value;
		delete current;
		m_length = m_length - 1;
	}

	//This instance would be if removing somewhere else in the list
	else if (position == pos)
	{
		prevNode->next = current->next;
		current->next = NULL;
		valueToReturn = current->value;
		delete current;
		m_length = m_length - 1;
	}

	//When the position argument is out of bounds
	else 
	{
		cout << "Error: " << pos << " is out of bounds." << endl;
		current = NULL;
		delete current;
		return -1;
	}

	//free iterator memory
	prevNode = NULL;
	delete prevNode;
	return valueToReturn;

}

//return the element at position pos
int InnerSquareList::get(int pos) const
{
	
	//initialize variables and create iterater
	int valueToReturn = 0;
	int position = 0;
	Node *current = new Node();
	current = m_header;

	//loop until iterator is in desired position
	while (position != pos && m_header != NULL && current->next != NULL)
	{
		current = current->next;
		position = position + 1;
	}
	//once at desired positon, retrieve node info
	if (position == pos && m_header != NULL) 
	{
		valueToReturn = current->value;
		current = NULL;
		delete current;
		return valueToReturn;
	}
	//if the desired position is out of bounds, output error
	else 
	{
		cout << "Error: " << pos << " is not within bounds." << endl;
		current = NULL;
		delete current;
		return 0;
	}

}

//change the value at position pos to data
void InnerSquareList::set(int pos, int data)
{

	//create iterator
	Node *current = new Node();
	current = m_header;

	//if position is out of bounds, output error
	if (pos + 1 > m_length || pos < 0)
	{
		cout << "Error: " << pos << " is out of bounds.";
	}
	//otherwise, iterate to position and modify data
	else 
	{
		for (int i = 0; i < pos; i++)
		{
			current = current->next;
		}
		current->value = data;
	}

	//free iterator memory
	current = NULL;
	delete current;

}

//total number of nodes in the inner list
// conducts this in constant time. 
size_t InnerSquareList::sizeOfThisInnerList() const
{
	return m_length;
}

//find the index of given data, return -1 if not found
int InnerSquareList::indexOf(int data) const
{

	//loop through list, if Nodes data equals
	//desired data, then return its position
	for (int i = 0; i < m_length; i++)
	{
		if (get(i) == data)
		{
			return i;
		}
	}
	return -1;

}

//merge another inner list to rear of current inner list
//the second inner list should be empty after merge
// conducts this in constant time. 
void InnerSquareList::merge(InnerSquareList &isl)
{

	if (m_header == isl.getHeader())
	{
		cout << "Error: merging to self." << endl;
	}
	else if (m_header == NULL) 
	{
		cout << "Error: first list is empty." << endl;
	}
	else if (isl.m_header == NULL) 
	{
		cout << "Error: second list is empty." << endl;
	}
	//move tails and headers to correct new nodes
	else 
	{
		m_tail->next = isl.m_header;
		m_tail = isl.m_tail;
		m_length = m_length + isl.m_length;

		isl.m_length = 0;
		isl.m_header = NULL;
		isl.m_tail = NULL;
	}

}

//split an inner list at mid point, return the second half
//the first half should be the same, or one element less than the second half
InnerSquareList InnerSquareList::split()
{
	
	InnerSquareList newInnerList;

	Node *current = new Node();
	current = m_header;

	//check if list is empty
	if (m_header == NULL || m_length <= 1)
	{
		cout << "Empty List." << endl;
		return newInnerList;
	}
	else 
	{

		//index in the middle of list, want to split here
		size_t splitIndex = (m_length / 2) - 1;
		size_t currentPosition = 0;

		//loops til iterator is at correct position
		while (currentPosition < splitIndex && current->next != NULL)
		{
			current = current->next;
			currentPosition = currentPosition + 1;
		}

		//assign new correct headers and tails
		newInnerList.m_header = current->next;
		newInnerList.m_tail = m_tail;
		newInnerList.m_length = m_length - (splitIndex + 1);

		m_tail = current;
		current->next = NULL;
		m_length = m_length - newInnerList.m_length;

	}

	//free iterator memory
	current = NULL;
	delete current;

	return newInnerList;

}

//print of all node values and the last node in O(n)
//check the sample output for format
void InnerSquareList::dump()
{

	cout << "InnerList Dump:" << endl;
	cout << "size = " << m_length << endl;

	//check if list is empty
	if (m_header == NULL)
	{
		cout << "Empty List." << endl;;
	}
	//otherwise print all the nodes data in order
	else 
	{
		for (unsigned int i = 0; i < m_length; i++)
		{
			cout << "[" << get(i) << "] ";
		}
		cout << endl;
		cout << "tail.data = " << getTail()->value << endl;
	}

}