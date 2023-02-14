#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>
#include <fstream>
struct Element
{
    int counter; //counter variable is used to save how many times the word is saved in the Hash Table(that`s the whole point of using the struct)

    std::string word; //Our Hash Table is going to save words from the latin alphabet
};

class HashTable
{
    public:
        HashTable(); //Base constructor

        ~HashTable(); //Destructor

        void AddString(std::string); //Method that adds elements to the hash table

        void FindElement(std::string); //Method for searching hash table elements

        void WriteToFileHashTable(std::string*,int); //Method that writes the results of searching

    private:
        static const int table_size = 200000; //i am going to use the static version of the Hash Table (I think that size is big enough)

        Element* HT[table_size]; //declaring it as a pointer because in each node both word and counter variables are going to be saved

       unsigned int HashFunction(std::string); //Function that returns the correct Element`s index

        void AvoidCollision(unsigned int&); //if an element should be entered in an index that is occupied then it`s index should be changed(I used linear probing to avoid collision)
};
std::ostream &operator << (std::ostream&,Element*); //operator << for F << HT[index] (see line 101 in HashTable.cpp)
#endif // HASHTABLE_H
