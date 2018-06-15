/*************************************************************************
> File Name: hashTable.cpp
> Author: Ran
> Mail:
> Created Time: 11/13/2016
************************************************************************/
#include <string.h>
#include <iostream>  
#include <vector>  
#include <list>  
#include <algorithm>  
#include <string>
#include <fstream>
#include <iterator>

using namespace std;

/****************************************************************
*   Data type name£ºWord
*   Description : The project data as a hash table
*****************************************************************/
void makeUpper(string &str);

class Word {
public:
	Word() { word = ""; definition = ""; }
	Word(const string & word, const string & definition) :word(word), definition(definition) {}
	const string & getWord() const
	{
		return word;
	}
	const string & getDefinition() const
	{
		return definition;
	}

	//overloaded == operator   
	bool operator==(const Word & rhs) const
	{
		return getWord() == rhs.getWord() && getDefinition() == rhs.getDefinition();
	}

	//overloaded != operator   
	bool operator!=(const Word & rhs) const
	{
		return !(*this == rhs);
	}

	friend ostream & operator<<(const ostream & os, const Word & e) {
		return cout << "Word: " << e.word << ",Definition: " << e.definition << endl;
	}

private:
	string word;
	string definition;
};

/****************************************************************
* Function name: hash (const HashedObj & key)
* Function description: According to the key value for a hash value, this function is based on a specific mathematical formula
* Parameter list: The key value of the data item
* Returns the result: Returns a value obtained by the hash function
*****************************************************************/
int hash(const string & key)
{
	int hashVal = 0;

	//Sum the formula using the hash function  
	for (int i = 0; i < key.length(); ++i)
		hashVal = 37 * hashVal + key[i];

	return hashVal;
}

/****************************************************************
* Function name: hash (const HashedObj & key)
* Function description: According to the key value for a hash value, this function is based on a specific mathematical formula
* Parameter list: key The key value of the data item
* Returns the result: Returns a value obtained by the hash function
*****************************************************************/
int hash(const Word & item)
{
	return ::hash(item.getWord());
}

/****************************************************************
* Hashtable class name: HashTable
* Description: Hashtable class for dictionary.
*****************************************************************/
template<typename HashedObj>
class HashTable {
public:
	explicit HashTable(int size = 101) :theLists(size), currentSize(0) {}
	~HashTable();

	/**************************The hash table needs to implemenmt*****************************************/
	void insert(const HashedObj & x);//Insert the item x 
	bool containes(const string & str) const;//It is judged whether or not the data item x is included
	Word deleteIt(const string & str);//Delete item x
	/*****************************************************************************************************/


	bool containes(const HashedObj & x) const;//It is judged whether or not the data item x is included
	bool search(const HashedObj & x) const;
	void makeEmpty();//Clear the hash table 
	bool isEmpty();
	bool remove(const HashedObj & x);//Delete item x
	void print();//Outputs the contents of the hash table
	HashedObj findElement(const HashedObj & x);//Look up data items by name  
	int getCurrentSize() { return currentSize; }
	int getSizeOfTheLists() { return theLists.size(); }
	void run(char** input);
private:
	vector<list<HashedObj> > theLists;//The structure of the hash table, theLists size default initialized to 101  
	int currentSize;//The number of elements currently in the hash table  
private:

	/*********************************The hash table needs to implemenmt********************************************/
	void rehash();//Re-hash
	/***************************************************************************************************************/

	int myhash(const HashedObj & x) const;//Hash function 
	int nextPrime(int n);//Find the nearest N to a prime number  
	bool isPrime(int n);
};

/****************************************************************
* Function name: findElement (const HashedObj & x) const
* Functional Description: Find the element x
* Parameter list: x is the element to find
* Returns the result: Returns the element if found, otherwise returns a default constructed element value
*****************************************************************/
template<typename HashedObj>
HashedObj HashTable<HashedObj>::findElement(const HashedObj & x)
{
	list<HashedObj> & whichList = theLists[myhash(x)];

	typename list<HashedObj>::iterator it = find(whichList.begin(), whichList.end(), x);
	if (it != whichList.end())
		return *it;
	else {
		HashedObj obj;//Returns an object with a member value of 0  
		return obj;
	}
}

/****************************************************************
* Function name: void run(char** input)
* Functional Description: run
* Parameter list: char** input
*****************************************************************/
template<typename HashedObj>
void HashTable<HashedObj>::run(char** input)
{
		HashTable<Word> table;
		ifstream json;

		if (input[1] != NULL) {
			string path = input[1]; //get the full path
			int pos = path.find_last_of('/'); //find last '/'
			string s(path.substr(pos + 1)); //get the file name only
			if (s.compare("dictionary.json") == 0) { //only accept "dictionary.json" name
				json.open(input[1]);
				cout << "Dictionary loading." << endl;
				while (!json.eof())
				{
					char buffer[10000] = "";
					json.getline(buffer, 10000); //store {"word","definetion"};
					if (buffer[0] != '\0') { //avoid read empty char*
						char* temp = buffer;
						temp = temp + 2; // delete '{"' symbol
						char* word = strtok(temp, ":"); //strtok ":"
						word[strlen(word) - 1] = '\0'; // delete '"' symbol after word.
						char* definition = strtok(NULL, "}"); //strtok '}'
						definition = definition + 2; // delete ',"' sybol before definetion
						definition[strlen(definition) - 1] = '\0';// delete '"' symbol
						//cout << "Word: " << word << endl << "Explanation: " << definition << endl;
						Word wordClass(word, definition);
						table.insert(wordClass);
					}
				}
				json.close();
				double tableSize = table.getCurrentSize(); //make a number double;
				cout << "Dictionary loaded." << endl <<
					"Words count: " << table.getCurrentSize() << endl <<
					"table size: " << table.getSizeOfTheLists() << endl <<
					"The Current load factor: " << tableSize / table.getSizeOfTheLists() << endl;

				string enterWord;

				while (cout << "Word to define: " << endl && cin >> enterWord) //while(cin>>a) because EOF define -1
				{
					makeUpper(enterWord);
					table.containes(enterWord);
				}
			}
			else
			{
				cout << "Usage: " << input[0] << " " << s << endl //cout the user type
					<< "Please specify the file name \"dictionary.json\" for reading." << endl;
			}
		}
		else
		{
			cout << "Usage: " << input[0] << endl //nothing in the file;
				<< "Please specify the file name \"dictionary.json\" for reading." << endl;
		}
}

/****************************************************************
* Function name: print ()
* Function Description: Output the contents of the hash table
* Parameter list: None
* Back to Results: None
*****************************************************************/
template<typename HashedObj>
void HashTable<HashedObj>::print()
{
	cout << "The content in the output hash table: " << endl;
	for (unsigned i = 0; i < theLists.size(); ++i) {
		cout << i << ": " << endl;
		for (typename list<HashedObj>::iterator it = theLists[i].begin(); it != theLists[i].end(); ++it) {
			cout << *it;
		}
	}
}

/****************************************************************
* Function name: isEmpty ()
* Function description: Determine whether the hash table is empty
* Parameter list: None
* Back to Results: None
*****************************************************************/
template<typename HashedObj>
bool HashTable<HashedObj>::isEmpty()
{
	return currentSize == 0;
}

/****************************************************************
* Function name: makeEmpty ()
* Function: Clear the hash table
* Parameter list: None
* Back to Results: None
*****************************************************************/
template<typename HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
	for (int i = 0; i < theLists.size(); ++i)
		theLists[i].clear();

	currentSize = 0;//The current number of elements is set to zero 
}

/****************************************************************
* Function name: contain (const HashedObj & x) const
* Function Description: Determines whether the hash table contains elements with value x
* Parameter list: x data item
* Returns the result: true if x is included, false otherwise
*****************************************************************/
template<typename HashedObj>
bool HashTable<HashedObj>::containes(const HashedObj & x) const
{
	const list<HashedObj> & whichList = theLists[myhash(x)];
	return find(whichList.begin(), whichList.end(), x) != whichList.end();
}

/****************************************************************
* Function name: contain (const string & x) const
* Function Description: Determines whether the hash table contains elements with value x
* Parameter list: x data item
* Returns the result: true if x is included, false otherwise
*****************************************************************/
template<typename HashedObj>
bool HashTable<HashedObj>::containes(const string & str) const
{
	Word x(str, "");
	const list<HashedObj> & whichList = theLists[myhash(x)];
	typename list<HashedObj>::const_iterator it;
	for (it = whichList.begin(); it != whichList.end(); ++it)
	{
		if ((*it).getWord() == x.getWord())
		{
			cout << "Definition: " << (*it).getDefinition() << endl;
			return 1;
		}
	}
	cout << "Word not found." << endl;
	return 0;
}
/****************************************************************
* Function name: search (const HashedObj & x) const
* Function Description: Determines whether the hash table contains elements with value x
* Parameter list: x data item
* Returns the result: true if x is included, false otherwise
*****************************************************************/
template<typename HashedObj>
bool HashTable<HashedObj>::search(const HashedObj & x) const
{
	const list<HashedObj> & whichList = theLists[myhash(x)];
	typename list<HashedObj>::const_iterator it;
	for (it = whichList.begin(); it != whichList.end(); ++it)
	{
		if ((*it).getWord() == x.getWord())
		{
			cout << "Definition: " << (*it).getDefinition() << endl;
			return 1;
		}
	}
	cout << "Word not found." << endl;
	return 0;
}
/****************************************************************
* Function name: deleteIt (const string & x)
* Function Description: Determines whether the hash table contains elements with value x
* Parameter list: x data item
* Returns the result: return nullptr if word is not in the table
*****************************************************************/
template<typename HashedObj>
Word HashTable<HashedObj>::deleteIt(const string & str)
{
	Word x(str, "");
	list<HashedObj> & whichList = theLists[myhash(x)];

	typename list<HashedObj>::iterator it = find(whichList.begin(), whichList.end(), x);

	if (it == whichList.end())
		return NULL;

	whichList.erase(it);//Removes the element x  
	--currentSize;
	return x;
}
/****************************************************************
* Function name: remove (const HashedObj & x)
* Function Description: Determines whether the hash table contains elements with value x
* Parameter list: x data item
* Returns the result: true if x is included, false otherwise
*****************************************************************/
template<typename HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj & x)
{
	list<HashedObj> & whichList = theLists[myhash(x)];

	typename list<HashedObj>::iterator it = find(whichList.begin(), whichList.end(), x);

	if (it == whichList.end())
		return false;

	whichList.erase(it);//Removes the element x  
	--currentSize;
	return true;
}

/****************************************************************
* Function name: insert (const HashedObj & x)
* Function description: Insert the element x in the hash table, and do nothing if the inserted entry already exists.
* Otherwise, place it at the front of the table
* Parameter list: x data item
* Returns the result: true if the insertion succeeded, false otherwise
*****************************************************************/
template<typename HashedObj>
void HashTable<HashedObj>::insert(const HashedObj & x)
{
	list<HashedObj> & whichList = theLists[myhash(x)];

	if (find(whichList.begin(), whichList.end(), x) != whichList.end())
		remove(x);

	whichList.push_back(x);

	//rehash  
	if (++currentSize > theLists.size())
		rehash();//Expand the size of the table 

}


/****************************************************************
* Function name: ~ HashTable ()
* Function description: destructor
* Parameter list: None
* Back to Results: None
*****************************************************************/
template<typename HashedObj>
HashTable<HashedObj>::~HashTable()
{

}

/****************************************************************
* Function name: nextPrime (int n)
* Function Description: Obtains a prime number nearest to n
* Parameter list: n indicates the value
* Returns the result: Returns a prime number
*****************************************************************/
template<typename HashedObj>
int HashTable<HashedObj>::nextPrime(int n)
{
	int nextPrime = n;
	bool found = false;

	//loop continuously until isPrime returns true for a number above n
	while (!found)
	{
		nextPrime++;
		if (isPrime(nextPrime))
			found = true;
	}
	return nextPrime;
}
/****************************************************************
* Function name: isPrime (int n)
* Function Description: Obtains a prime number nearest to n
* Parameter list: n indicates the value
* Returns the result: Returns a prime number
*****************************************************************/
template<typename HashedObj>
bool HashTable<HashedObj>::isPrime(int n)
{
	//loop from 2 to n/2 to check for factors
	for (int i = 2; i <= n / 2; i++)
	{
		if (n % i == 0)     //found a factor that isn't 1 or n, therefore not prime
			return false;
	}

	return true;
}
/****************************************************************
* Function name: rehash ()
* Functional Description: Expand the size of the hash table
* Parameter list: None
* Back to Results: None
*****************************************************************/
template<typename HashedObj>
void HashTable<HashedObj>::rehash()
{
	vector<list<HashedObj> > oldLists = theLists;

	//Create a new hash table that is twice the size of the original  
	theLists.resize(nextPrime(2 * theLists.size()));

	for (int i = 0; i < theLists.size(); ++i)
		theLists[i].clear();

	//Copy the hash table  
	for (int i = 0; i < oldLists.size(); ++i) {
		typename  list<HashedObj>::iterator it = oldLists[i].begin();
		while (it != oldLists[i].end()) 
		{
			insert(*it++);
			currentSize--;
		}
	}
}
/****************************************************************
* Function name: myhash (const HashedObj & key)
* Function description: According to the key value for a hash value
* Parameter list: key The key value of the data item
* Return Result: Returns a hash value
*****************************************************************/
template<typename HashedObj>
int HashTable<HashedObj>::myhash(const HashedObj & key) const
{
	int hashVal = ::hash(key);

	hashVal %= theLists.size();

	if (hashVal < 0)
		hashVal += theLists.size();

	return hashVal;
}
/****************************************************************
* Function name: makeUpper(string &str)
* Function description: make all letter be upper case
*****************************************************************/
void makeUpper(string &str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] += ('A' - 'a');
		}
	}
}

int main(int argc, char* argv[])
{
	HashTable<Word> h;
	h.run(argv);
	
	return 0;
}