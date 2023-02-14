#include "HashTable.h"

HashTable::HashTable()
{
    for(int i = 0; i  < table_size; i++)
    {
        HT[i] = new Element; //allocating each pointer (HT[i]) as an Element type

        HT[i]->word = ""; //initializing each pointer to word with ""

        HT[i]->counter = 0; //initializing each pointer to counter to 0
    }

}
HashTable::~HashTable()
{
    for(int i = 0; i < table_size; i++)
    {
        if(HT[i]->word != "")
            delete HT[i];
    }
    //deleting each pointer that is NOT null!
}
unsigned int HashTable::HashFunction(std::string key)
{
    unsigned int index = 0;

    int seed = 131; //using a seed parameter to prevent hash collisions for different data

    for(int i = 0; i < (int)key.length(); i++)
    {
        index = (index * seed) + key[i];
    }
    //Hash Function: Each ASCII number of string s is being added with the current index * seed (Quite simple function i can say)
    return index % table_size;
}
void HashTable::AddString(std::string key)
{
    unsigned int index = HashFunction(key); //call HashFunction to get the index

    if(HT[index]->word == "") //That means that HT[index] is empty
    {
        //occupying index...//
        HT[index]->word = key;
        HT[index]->counter = 1;
    }
    else //That means that HT[index] is already occupied so there are 2 possible cases:
    {
        if (HT[index]->word == key) //if string key is equal to the HT[index]->word then we just increase the counter by 1
         {
            HT[index]->counter += 1;
         }
        else //in the else statement it means that we came up with a collision
        {
            AvoidCollision(index); //call AvoidCollision(index) to update the value of index(see line 74-81)

            //occupying the correct space

            HT[index]->word = key;

            HT[index]->counter = 1;
        }
    }

}
void HashTable::FindElement(std::string key)
{
    unsigned int index = HashFunction(key); //call HashFunction to get the index of string key

    while (HT[index]->word != key)
    {
        index++;  //update the index until HT[index]->word is equal to key!(linear probing)

        if(index == table_size)
            index = 0;
    }

}
void HashTable::AvoidCollision(unsigned int& index) //i am using call by reference here
{
    while(HT[index]->word != "")
    {
        index++; //just a linear probing

        if(index == table_size)
            index = 0;
    }
    index %= table_size; //update index

}
void HashTable::WriteToFileHashTable(std::string* Q,int Q_counter)
{
    std::ofstream F; //ofstream statement to print words in file

    F.open("HashTableResults.txt");

    if(F.is_open())
    {
        for(int i = 0; i < Q_counter; i++)
        {
            unsigned int index = HashFunction(Q[i]);

            while (HT[index]->word != Q[i])
            {
                index++;

                if(index == table_size)
                    index = 0;
            }
            if(HT[index]->word == Q[i] && HT[index]->counter > 0)
                F << HT[index] << std::endl; //print the word and counter in file "HashTableResults.txt"

        }
        F.close(); //closing the opened file

    }
    else
        std::cerr << "Error opening file" << std::endl;

}
//implementation of << operator!!!
std::ostream &operator << (std::ostream& File_out,Element* Table)
{
    File_out << Table->word << "[" << Table->counter << "]";

    return File_out;

}

