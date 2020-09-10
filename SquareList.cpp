#include "SquareList.h"
#include <cmath>

using namespace std;

SquareList::SquareList()
{
	inners.resize(0);
}

SquareList::~SquareList()
{

	//iterate through inners and call clear
	std::list<InnerSquareList>::iterator iterator, end = inners.end();
	for (iterator = inners.begin(); iterator != end; ++iterator) 
	{
		iterator->clean();
	}

}

//Keep the length of each inner list satisfying the definition of a Square List
void SquareList::consolidate()
{

	//initialize iterator and variables,
	//find max and min allowed in each inner list
	std::list<InnerSquareList>::iterator iterator, end = inners.end();
	int prevInnerListSize = -1;
	int squareListSize = size();
	double min = sqrt(squareListSize) / 2.0;
	double max = 2.0 * sqrt(squareListSize);

	//iterate through the upper list (inners)
	for (iterator = inners.begin(); iterator != end; ++iterator) 
	{

		//If we come across empty inner list, delete it
		if (iterator->sizeOfThisInnerList() == 0)
		{

			std::list<InnerSquareList>::iterator newIterator;
			newIterator = iterator;
			inners.erase(newIterator);

			if (iterator != inners.begin()) 
			{
				--iterator;
			}

		}

		//If we come across two ajacent inner list that are short, merge
		else if (prevInnerListSize != -1 && iterator->sizeOfThisInnerList() <= min && prevInnerListSize <= min) 
		{

			InnerSquareList &cuurentInnerList = *iterator;
			--iterator;

			iterator->merge(cuurentInnerList);

		}

		//If we come across a list too long, split
		else if (iterator->sizeOfThisInnerList() > max) 
		{

			std::list<InnerSquareList>::iterator newIterator;
			newIterator = iterator;
			++newIterator;

			if (iterator == end) 
			{
				inners.push_back(iterator->split());
			}
			else 
			{
				inners.insert(newIterator, iterator->split());
				--iterator;
			}

		}

		//keep track of previous list size, for merge checking
		prevInnerListSize = iterator->sizeOfThisInnerList();
	}

}

//insert first
void SquareList::addFirst(int data)
{

	//if empty list, create inner list and push_front,
	//followed by adding data
	if (inners.size() == 0)
	{
		InnerSquareList newInnerList;
		inners.push_front(newInnerList);
		inners.front().addFirst(data);
	}
	//otherwise, call addFirst
	else if (inners.size() > 0)
	{
		inners.front().addFirst(data);
	}
	//run consolidate to ensure Square List meets requirments
	consolidate();

}

//insert last
void SquareList::addLast(int data)
{

	//if empty list, create inner list and push_back,
	//followed by adding data
	if (inners.size() == 0)
	{
		InnerSquareList newInnerList;
		inners.push_back(newInnerList);
		inners.back().addLast(data);
	}
	//otherwise, call addLast
	else if (inners.size() > 0)
	{
		inners.back().addLast(data);
	}
	//run consolidate to ensure Square List meets requirments
	consolidate();

}

//removes first element in square list
int SquareList::removeFirst()
{

	int removedData = 0;

	//check if list is empty
	if (inners.size() == 0)
	{
		cout << "Error: square list is empty." << endl;
		return -1;
	}
	//otherwise, remove first and return its value
	else 
	{
		removedData = inners.front().get(0);
		inners.front().remove(0);
		consolidate();
		return removedData;
	}

}

//insert a value to be at location "pos"
void SquareList::add(int pos, int data)
{

	int squareListSize = size();

	//check if position is out of bounds
	if (pos > (squareListSize) || pos < 0)
	{
		cout << "Error: " << pos << " is out of bounds." << endl;
	}
	//check if empty list and pos is other than 0
	else if (inners.size() == 0 && pos != 0) 
	{
		cout << "Error: empty list and position to be inserted is not 0." << endl;
	}
	//if empty list and desired pos is 0,
	//make new innerlist and push_front data
	else if (inners.size() == 0 && pos == 0)
	{
		InnerSquareList isl;
		inners.push_front(isl);
		inners.front().addFirst(data);
		consolidate();
	}
	else 
	{

		int prevNodes = 0;

		std::list<InnerSquareList>::iterator iterator = inners.begin();

		//if desired pos resides in the last inner list
		if ( (squareListSize - inners.back().sizeOfThisInnerList()) <= (pos) )
		{

			//add data accordingly
			prevNodes = (squareListSize - inners.back().sizeOfThisInnerList());
			int newPos = pos - prevNodes;
			inners.back().add(newPos, data);
			consolidate();

		}
		//if desired pos is anywhere else
		else 
		{

			//iterate to the desired pos
			while ((iterator->sizeOfThisInnerList() + prevNodes - 1) < pos) 
			{
				prevNodes = prevNodes + iterator->sizeOfThisInnerList();
				++iterator;
			}

			//insert data into pos
			int newPos = pos - prevNodes;
			iterator->add(newPos, data);
			consolidate();
			
		}

	}

}

//removes element from Square List at index pos
int SquareList::remove(int pos)
{

	int squareListSize = size();
	int valueToReturn = -1;

	//check is pos is out of bounds
	if (pos > (squareListSize - 1) || pos < 0)
	{
		cout << "Error: " << pos << " is out of bounds." << endl;
		return -1;
	}
	//check for empty list
	else if (inners.size() == 0)
	{
		cout << "Error: empty list." << endl;
		return -1;
	}
	else 
	{

		int prevNodes = 0;

		std::list<InnerSquareList>::iterator iterator = inners.begin();

		//if pos resides in last inner list, call remove accordingly
		if ( (squareListSize - inners.back().sizeOfThisInnerList()) <= (pos) )
		{

			prevNodes = (squareListSize - inners.back().sizeOfThisInnerList());
			int newPos = pos - prevNodes;
			valueToReturn = inners.back().remove(newPos);
			consolidate();
			return valueToReturn;

		}
		else 
		{

			//iterate until correst list is found that contains pos
			while ((iterator->sizeOfThisInnerList() + prevNodes - 1) < pos) 
			{
				prevNodes = prevNodes + iterator->sizeOfThisInnerList();
				++iterator;
			}

			//remove Node at pos accordingly
			int newPos = pos - prevNodes;
			valueToReturn = iterator->remove(newPos);
			consolidate();
			return valueToReturn;

		}

	}

}

//get element from Square List at index pos
int SquareList::get(int pos)
{

	int squareListSize = size();

	//check if pos is out of bounds
	if (pos > (squareListSize - 1) || pos < 0)
	{
		cout << "Error: " << pos << " is out of bounds." << endl;
		return -1;
	}
	//check if empty list
	else if (inners.size() == 0)
	{
		cout << "Error: empty list." << endl;
		return -1;
	}
	else 
	{

		int prevNodes = 0;

		//if pos resides in last inner list, call get accordingly
		if ( (squareListSize - inners.back().sizeOfThisInnerList()) <= (pos) )
		{

			prevNodes = (squareListSize - inners.back().sizeOfThisInnerList());
			int newPos = pos - prevNodes;
			return inners.back().get(newPos);

		}
		else 
		{

			std::list<InnerSquareList>::iterator iterator = inners.begin();
			
			//iterate until correst list is found that contains pos
			while ((iterator->sizeOfThisInnerList() + prevNodes - 1) < pos) 
			{
				prevNodes = prevNodes + iterator->sizeOfThisInnerList();
				++iterator;
			}

			////get data from Node at pos accordingly
			int newPos = pos - prevNodes;
			return iterator->get(newPos);

		}

	}

}

//set element at index pos the data 'data'
void SquareList::set(int pos, int data)
{
	
	int squareListSize = size();

	//check if pos is out of bounds
	if (pos > (squareListSize - 1) || pos < 0)
	{
		cout << "Error: " << pos << " is out of bounds." << endl;
	}
	//check for empty list
	else if (inners.size() == 0)
	{
		cout << "Error: empty list." << endl;
	}
	else 
	{

		int prevNodes = 0;

		std::list<InnerSquareList>::iterator iterator = inners.begin();

		//if pos resides in last inner list, call get accordingly
		if ( (squareListSize - inners.back().sizeOfThisInnerList()) <= (pos) )
		{

			prevNodes = (squareListSize - inners.back().sizeOfThisInnerList());
			int newPos = pos - prevNodes;
			inners.back().set(newPos, data);

		}
		else 
		{

			//iterate until correst list is found that contains pos
			while ((iterator->sizeOfThisInnerList() + prevNodes - 1) < pos) 
			{
				prevNodes = prevNodes + iterator->sizeOfThisInnerList();
				++iterator;
			}

			//call set accordingly
			int newPos = pos - prevNodes;
			iterator->set(newPos, data);

		}

	}
	
}

//total number of nodes in all inner lists
int SquareList::size()
{
	
	unsigned int totalSize = 0;

	//if inners is empty, return 0
	if (inners.size() == 0)
	{
		return 0;
	}

	//loop though top level list and track size
	std::list<InnerSquareList>::const_iterator iterator, end = inners.end();
	for (iterator = inners.begin(); iterator != end; ++iterator) 
	{
		totalSize = totalSize + iterator->sizeOfThisInnerList();
	}

	//return total size calculated
	return totalSize;

}

//Position of first occurence of a value
int SquareList::indexOf(int data)
{
	
	int indexToReturn = 0;

	//loop through upper level list
	int loopNum = 0;
	std::list<InnerSquareList>::iterator iterator, end = inners.end();
	for (iterator = inners.begin(); iterator != end; ++iterator) 
	{
		
		//if data is not in current inner list and iterator not at end,
		//iterate to next and track current position
		int currentIndex = iterator->InnerSquareList::indexOf(data);
		if (currentIndex == -1 && iterator != end)
		{
			
			if (loopNum == 0) 
			{
				indexToReturn = (indexToReturn + iterator->sizeOfThisInnerList()) - 1;
				loopNum = loopNum + 1;
			}
			else 
			{
				indexToReturn = (indexToReturn + iterator->sizeOfThisInnerList());
				loopNum = loopNum + 1;
			}

		}
		//if index of data was found
		else if (currentIndex != -1)
		{

			//if index if in first inner list, return index
			if (loopNum == 0) 
			{
				indexToReturn = currentIndex;
				return indexToReturn;
			}
			//if index was anywhere else, retrun index with corrected factor
			else if (loopNum > 0) 
			{
				indexToReturn = (indexToReturn + currentIndex) + 1;
				return indexToReturn;
			}

		}
		//otherwise, data not found, returns -1
		else if (currentIndex == -1 && iterator == end)
		{
			return -1;
		}

	}
	//otherwise, data not found, returns -1
	return -1;

}

//Printing out information of Square List for debugging
void SquareList::dump()
{

	int numOfInnerList = inners.size();
	int numLoops = 0;

	cout << "*********************************************************" << endl;
	cout << "SquareList dump:" << endl;
	cout << "Total size = " << size() << ", ";
	cout << "# of list = " << numOfInnerList << endl;
	
	//iterate though top list and call dump for each inner list
	std::list<InnerSquareList>::iterator iterator = inners.begin();
	while (numLoops < numOfInnerList) 
	{

		cout << "=========================================================" << endl;
		iterator->dump();
		++iterator;
		numLoops = numLoops + 1;

	}
	cout << "*********************************************************" << endl;

}