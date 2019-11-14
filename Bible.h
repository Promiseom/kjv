#include <iostream>
#include <string>
#include <Fstream>
#include <map>
#include <vector>
#include "string_ops.h"

using namespace std;

//Prints the whole chapter of the bible
//chapterVerses: Contains the chapter verses to print
//bookName: Is the name of the book the chapter is in
//chapterNumber: "This is the chapter number that is printed
void printBibleVerses(vector<string> chapterVerses, string bookName, int chapterNumber);

//Returns true if the item can be found in the container
//item: Is the item being sort for
//container: Is the container to search for item in
bool bookContains(string item, vector<string> container, bool ignoreCase, string &foundBook);

//Changes the context into the a bible book context
//In this context you can go through all the chapters in the book
//bible: Is the bible containing all the books
//bookName: Is the name of the book to open
void getBook(map<string, vector<vector<string>>> bible, string bookName);

