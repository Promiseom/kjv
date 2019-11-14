#include <iostream>
#include <Fstream>
#include <vector>
#include <iomanip>
#include "string_ops.h"

using namespace std;

void printHelp()
{
	cout<<"A minimum of 3 arguments are required:"<<endl;
	cout<<"<arg1> <arg2> <arg3>"<<endl;
	cout<<"arg1       This is the word to be searched."<<endl;
	cout<<"arg2       This is the book to start searching from, the program will start searching when this book is first found."<<endl;
	cout<<"arg3       The search ends when this book is found, if not given runs to the end.\n"<<endl;
}

int main(int argv, char *args[])
{
	//program requires at least one argument, the text to search
	string searchWord;
	//book to look in, if this is the only book, else start looking in this book
	//and end in another book
	string bookStart = "";  
	string bookEnd = "";  //stop searching in this book
		
	if(argv > 1)
	{
		if(args[1] == "-help" || args[1] == "help" || args[1] == "-h")
		{
			printHelp();
		}

		searchWord = args[1];
		if(argv > 2)
		{
			bookStart = args[2];
			if(argv > 3)
			{
				bookEnd = args[3];
			}
		}else
		{
			cout<<"No book specified.\nClosing...!"<<endl;
			return 0;
		}
	}else
	{
		cout<<"A minimum of 3 arguments expected, 1 found.\nClosing...!"<<endl;
		return 0;
	}

	//title for the window
	const char* windowTitle = stringToConstCharString("title Searching '" + searchWord + "' From [" + bookStart + "] - [" + bookEnd + "]");
	system(windowTitle);

	string dataFilename = "Data\\data.txt";					   //filename containing the data that will be searched
	cout<<"attempting to open file to begin search..."<<endl;
	ifstream fileReader(dataFilename);
	if(fileReader.is_open())
	{
		cout<<"file opened! Begining search..."<<endl;
		string verse;
		int nMatches = 0;
		bool isSearchStart = false;
		string previousBook = "";
		while(!fileReader.eof())
		{
			getline(fileReader, verse);
			vector<string> bookContent = split(verse, "|");
			string currentBookName = bookContent[0];
			string currentChapterNumber = bookContent[1];
			string currentVerse = bookContent[2];
			string currentVerseContent = bookContent[3];

			if(!compare(currentBookName, bookStart, true))
			{
				if(isSearchStart) 
				{ 
					if(argv > 3)
					{
						if(compare(currentBookName, args[3], true))
						{
							//cout<<"end found"<<endl;
							break;
						}else
						{
							bookStart = currentBookName;  //search a new book
						}
					}else
					{
						//cout<<"stopping after one book"<<endl;
						break;
					}
				}else
				{
					continue;
				}
			}else
			{
				if(previousBook != "")
				{
					if(compare(previousBook, currentBookName, true))
					{
						//the same book
					}else
					{
						cout<<"============================================"<<endl;
						if(nMatches > 0)
						{
							string reply;
							cout<<endl<<"MORE?(Y/N): ";
							cin>>reply;
							cin.ignore();
							if(reply == "N" || reply == "n")
							{
								break;
							}
						}						
						cout<<endl<<"============================================"<<endl;
						cout<<"Search Result: "<<currentBookName<<endl;		
						cout<<"============================================"<<endl;
					}
				}else
				{					
					cout<<"============================================"<<endl;
					cout<<"Search Result: "<<currentBookName<<endl;		
					cout<<"============================================"<<endl;
				}
				isSearchStart = true;
				previousBook = currentBookName;
				//search the verse content
				if(find(searchWord, currentVerseContent, true))
				{
					//string message = ". " + "Match Found in " + toString(currentBookName) + " " + toString(currentChapterNumber) + ":" + toString(currentVerse) + "\n";
					cout<<setw(4)<<++nMatches<<". "<<currentBookName<<" "<<currentChapterNumber<<":"<<currentVerse<<" ____ "<<currentVerseContent<<endl;
				}
			}			
		}
		if(nMatches == 0) { cout<<"No match found..."<<endl; }
		cout<<"============================================"<<endl;
		fileReader.close();
		cout<<"file closed!"<<endl;
	}else
	{
		cout<<"failed to open the data file for reading..."<<endl;
		cout<<"aborting search!"<<endl;
	}
    
	if(bookStart != "") 
	{
		cout<<"Press enter to close...";
		cin.ignore();
	}
	return 0;
}