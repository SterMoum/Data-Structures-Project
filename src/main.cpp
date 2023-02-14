#include <iostream> //basic library for using std
#include <fstream> //fstream library for ifstream and ofstream statements
#include <string> //string library for managing std::string type
#include <ctime>  //ctime to use rand() function in order to get a random number
#include "HashTable.h" //HashTable class
#include "AVLTree.h"  //AVLTree class(no need to include "Tree.h" because AVLTree includes it itself because of their inheritance)
#include "Timer.h" //Timer Class


#define Q_size 100000 //defining Q size with maximum value 100000 cells


//Function to insert the words in the HashTable
    void word_insertion(HashTable&);

//Function to insert the words in the Binary Tree

    void word_insertion(Tree&);

//Function to insert the words in the AVL Tree

    void word_insertion(AVLTree&);

//Function to implement Search in HashTable

    void SearchingFunction(std::string*,HashTable&,int);

//Function to implement Search in Binary Tree

    void SearchingFunction(std::string*,Tree&,int);

//Function to implement Search in AvL Tree

    void SearchingFunction(std::string*,AVLTree&,int);

//Function to create the random Q Table

    void Q_insertion(std::string*,int&);

//It is just a function that returns true if the current letter belongs to the latin alphabet

    bool allowed_character(char);

int main(void)
{
    HashTable A; //Creating Hash table object(A)

    Tree B; //Creating BST Object(B)

    AVLTree C; //Creating AVL Tree object(C)

    std::string *Q;// Q table is to execute search on our data structures

    Q = new std::string[Q_size];

    int Q_counter = 0;//counter for current elements in Q table

//INSERTING...
    std::cout << "Hash Table Adding elements: ";

    word_insertion(A); //call word_insertion for HashTable

    std::cout << "Bin Tree Adding Elements: ";

    word_insertion(B); //call word_insertion for BST(Binary Search Tree)

    std::cout << "AVL Tree Adding Elements: ";

    word_insertion(C); //call word_insertion for AVL Tree

//CREATING THE Q SET
    Q_insertion(Q,Q_counter); //call Q_insertion for inserting random words to the Q table

    std::cout << "In our Data Structures " << Q_counter << " words will be searched..." << std::endl;

//SEARCHING...
    std::cout << "Hash table Search: ";

    SearchingFunction(Q,A,Q_counter); //call SearchingFunction for searching the Q words in the HashTable

    std::cout << "BinTree Search: ";

    SearchingFunction(Q,B,Q_counter); //call SearchingFunction for searching the Q words in the BST


    std::cout << "AVL Tree Search: ";

    SearchingFunction(Q,C,Q_counter); //call SearchingFunction for searching the Q words in the AVL Tree

//WRITING THE RESULTS OF SEARCHING IN FILES...
    A.WriteToFileHashTable(Q,Q_counter); //public method of class HashTable that writes the results of searching in file "HashTableResults.txt"

    B.WriteToFileTree(Q,Q_counter); //public method of class Tree that writes the results of searching in file "BinTreeResults.txt"

    C.WriteToFileAVL(Q,Q_counter); //public method of class AVLTree that writes the results of searching in file "AVLTreeResults.txt"


	return 0;
}
void word_insertion(HashTable &A)
{

    std::ifstream F; //ifstream statement to read words from file

    F.open("text file(Guttenberg).txt"); //THE FILENAME SHOULD BE THE SAME IN ALL DATA STRUCTURES DURING INSERTING IN ORDER TO IMPLEMENT SEARCHING

    if(F.is_open()) //returns NULL if the File cannot be oppenned
    {

        Timer HashTableTimer; //After declaring a Timer object(HashTableTimer) the constructor
                            //of class Timer is being called and the
                            //timing of inserting words in the HashTable begins to count

        std::string line; // in std::string line i am saving each line of the opened file

        std::string buffer; //temporary std::string that keeps the allowed letters

        char checker; //if there are any letters saved in buffer after getting out of the for loop
                      //(line 118-137) then checker has 1 as a value and a word should be added to
                      // the current edited structure(HashTable)

        while(std::getline(F,line)) //getline extracts the characters of the opened file and each of file`s line is being saved to std::string line
        {
            for(int i = 0; i < (int)line.length(); i++) //(int)line.length() returns the length of each line
            {
                if(allowed_character(line[i])) //if the current letter(line[i]) is an allowed character (see allowed_character(char letter) function in line 326-332)
                {
                    buffer.push_back(line[i]); //it is added to buffer (buffer.push_back(std::string line[i]) assing line[i] at the end of the current string)

                    checker = 1;
                }
                //if the current letter (line[i]) is not an allowed character it means that in buffer
                //there is a whole word saved and line[i] is a punctuation mark or a number or a space.
                //i check the previous one if is an allowed character for sure just to avoid different kind of problems(Maybe it is not necessary but no words are being missed)
                else if(i > 0 && allowed_character(line[i-1]))
                {

                    A.AddString(buffer); //buffer is being added to the Hash Table

                    buffer.clear(); //buffer is now empty

                    checker = 0;
                }


            }
            if(checker) //checking if the buffer is not cleared
            {
                A.AddString(buffer);

                buffer.clear();
            }
        }
        F.close(); //closing the opened file
    }
    else
    {
        std::cout << "Error opening File" << std::endl;
    }


}
void word_insertion(Tree &B)
{
    std::ifstream F; //ifstream statement to read from file

    F.open("text file(Guttenberg).txt"); //THE FILENAME SHOULD BE THE SAME IN ALL DATA STRUCTURES DURING INSERTING IN ORDER TO IMPLEMENT SEARCHING IN OUR PROGRAMM

    if(F.is_open()) //returns NULL if the File cannot be oppenned
    {
        Timer BinTreeTimer; //After declaring a Timer object(BinTreeTimer) the constructor
                            //of class Timer is being called and the
                            //timing of inserting words in BST begins to count

        std::string line; // in std::string line i am saving each line of the opened file

        std::string buffer; //temporary std::string that keeps the allowed letters

        char checker; //if there are any letters saved in buffer after getting out of the for loop
                      //(line 118-137) then checker has 1 as a value and a word should be added to
                      // the current edited structure(Binary Search Tree)

        while(std::getline(F,line)) //getline extracts the characters of the opened file and each of file`s line is being saved to std::string line
        {
            for (int i = 0; i < (int)line.length(); i++) //(int)line.length() returns the length of each line
            {
                if ((allowed_character(line[i]))) //if the current letter(line[i]) is an allowed character (see allowed_character(char letter) function in line 326-332)
                {
                    buffer.push_back(line[i]); //it is added to buffer (buffer.push_back(std::string line[i]) assing line[i] at the end of the current string)

                    checker = 1;
                }
                //if the current letter (line[i]) is not an allowed character it means that in buffer
                //there is a whole word saved and line[i] is a punctuation mark or a number or a space.
                //i check the previous one if is an allowed character for sure just to avoid different kind of problems(Maybe it is not necessary...)
                else if (i > 0 && allowed_character(line[i-1]))
                {
                    B.addLeaf(buffer); //buffer is being added to the Bin Tree

                    buffer.clear(); //buffer is now empty

                    checker = 0;
                }
            }
            if(checker) //checking if the buffer is not cleared
            {
                B.addLeaf(buffer);

                buffer.clear();
            }
        }
        F.close(); //closing the opened file
    }
    else
    {
        std::cout << "Error opening File" << std::endl;
    }
}
void word_insertion(AVLTree& C)
{
    std::ifstream F; //ifstream statement to read from file

    F.open("text file(Guttenberg).txt"); //THE FILENAME SHOULD BE THE SAME IN ALL DATA STRUCTURES DURING INSERTING IN ORDER TO IMPLEMENT SEARCHING IN OUR PROGRAMM

    if(F.is_open()) //returns NULL if the File cannot be oppenned
    {
        Timer AVLTreeTimer; //After declaring a Timer object(AVLTreeTimer) the constructor
                            //of class Timer is being called and the
                            //timing of inserting words in AVL Tree begins to count

        std::string line; // in std::string line i am saving each line of the opened file

        std::string buffer; //temporary std::string that keeps the allowed letters

        char checker; //if there are any letters saved in buffer after getting out of the for loop
                      //(line 118-137) then checker has 1 as a value and a word should be added to
                      // the current edited structure(AVL Tree)

        while(std::getline(F,line)) //getline extracts the characters of the opened file and each of file`s line is being saved to std::string line
        {
            for (int i = 0; i < (int)line.length(); i++) //(int)line.length() returns the length of each line
            {
                if ((allowed_character(line[i])))  //if the current letter(line[i]) is an allowed character (see allowed_character(char letter) function in line 326-332)
                {
                    buffer.push_back(line[i]); //it is added to buffer (buffer.push_back(std::string line[i]) assing line[i] at the end of the current string)

                    checker = 1;
                }
                //if the current letter (line[i]) is not an allowed character it means that in buffer
                //there is a whole word saved and line[i] is a punctuation mark or a number or a space.
                //i check the previous one if is an allowed character for sure just to avoid different kind of problems(Maybe it is not necessary...)
                else if (i > 0 && allowed_character(line[i-1]))
                {
                    C.addLeaf(buffer); //buffer is added to the AVL Tree

                    buffer.clear(); //buffer now is empty

                    checker = 0;
                }
            }
            if(checker) //checking if the buffer is not cleared
               {
                C.addLeaf(buffer);

                buffer.clear();
               }
        }
        F.close(); //closing the opened file
    }
    else
    {
        std::cout << "Error opening File" << std::endl;
    }

}
void SearchingFunction(std::string* Q,HashTable& A,int Q_counter)
{
    Timer SearchHashing; //After declaring SearchHashing as a Timer object the timing of the searching algorithm in HashTable begins to count

    for(int i = 0; i < Q_counter; i++)
        A.FindElement(Q[i]);
}

void SearchingFunction(std::string* Q,Tree& B,int Q_counter)
{
    Timer SearchBinTree; //After declaring SearchBinTree as a Timer object the timing of the searching algorithm in BST begins to count

    for(int i = 0; i < Q_counter; i++)
        B.FindNode(Q[i]);
}
void SearchingFunction(std::string* Q,AVLTree& C,int Q_counter)
{
    Timer SearcAVLTree; //After declaring SearchAVLTree as a Timer object the timing of the searching algorithm in AVL tree begins to count

    for(int i = 0; i < Q_counter; i++)
        C.FindNode(Q[i]);
}
void Q_insertion(std::string* Q,int& Q_counter)
{

    std::ifstream F;

    F.open("text file(Guttenberg).txt");

    if(F.is_open())
    {
        std::string line;

        std::string buffer;

        char flag; //variable that decides if the current word should ender the Q_SET or not

        char checker;

        while(std::getline(F,line))
        {
            srand(time(NULL)); //use of the computer`s internal clock to control the choice of the seed.Since timings is continually changing,the seed is forever changing

            for(int i = 0; i < (int)line.length(); i++)
            {

                 if (allowed_character(line[i]))
                  {

                    buffer.push_back(line[i]);

                    checker = 1;

                  }
                   else if (i > 0 && allowed_character(line[i-1]))
                  {
                    flag = rand() % 2; //rand()%2 gives 1 or 0 as output in flag

                    if(flag) //if flag is equal to 1 buffer is being saved to the Q table
                    {
                        Q[Q_counter++] = buffer;

                         if(Q_counter == Q_size)
                            return;
                    }

                    buffer.clear(); //buffer is now empty

                    checker = 0;

                   }

            }
            if(checker)
            {
                Q[Q_counter++] = buffer; //buffer is being inserted to the Q table

                if(Q_counter == Q_size)
                    return;

                buffer.clear();
            }
        }
        F.close();
    }
    else
        std::cout << "Error opening File";

}
bool allowed_character(char letter)
{
	if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z'))
        return true;
    else
        return false;
}



