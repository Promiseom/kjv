#include "Bible.h" 

bool isBookOpen = false;  			//indicates if a book is open
bool isChapterOpen = false;  		//indicates if a chapter is open
bool isSingleVerseMode = false;  	// only one verse is displayed in single verse mode

string bookName = "";    	//the book that been opened
int chapterNumber = -1;		//the chapter that has been opened
int nChapters;     			//number of chapters in the opened book
int nVerse;         			// the verse in a chapter to open
map<string, vector<vector<string>>> myBible;
vector<vector<string>> myChapters;  //indicates the content of the open book

void help(vector<string> arguments)
{
	cout<<endl;
	cout<<"kjv command syntax and usage:"<<endl;
	cout<<"Note*: In this documentation, <> contains the command while [] holds the argument, these symbols should not be included in the commands!\n"<<endl;

	cout<<"Opening a book: "<<endl;
	cout<<"<-open | -o> [bookname]\n"<<endl;
	cout<<"Opening a chapter: "<<endl;
	cout<<"<-chapter | -c> [chapter_number]\n"<<endl;
	
	cout<<"To open a specific chapter in a book, combine the above commands as follows"<<endl;
	cout<<"<-open | -o> [bookname] <-chapter | -c> [chapter_number]\n"<<endl;

	cout<<"While a book and chapter has been opened previously, you can use the following commands:"<<endl;
	cout<<"<-next | -n>        Open the next chapter if any."<<endl;
	cout<<"<-prev | -p>        Open the previous chapter if any.\n"<<endl;
	cout<<"Other Arguments"<<endl;
	cout<<"<-verse | -v [verse number]      Optional parameter to specify the verse to open"<<endl;
	cout<<"                                 When used, only the specified verse is open"<<endl;
	cout<<"Usage:"<<endl;
	cout<<"-open genesis -c 2 -v 5          Open genesis chapter 2 verse 5"<<endl;
}

void open(vector<string> arguments, vector<string> bookNames)
{	
	string bookname = "";
	string chapter = "";
	
	//cout<<"Welcome to the open context"<<endl;
	//get the next argument associated with this context
	if(arguments.size() < 2)
	{
		//there's only one argument, next argument is '' which is an invalid argument
		cout<<"Invalid argument ' ' "<<endl;
	}else{
		bookname = arguments[1];	
	}
	
	//move to the next argument if any
	if(arguments.size() > 2)
	{
		//it's expected the next argument will be -chapter
        //anything other than that will be invalid
        if(arguments[2] == "chapter" || arguments[2] == "-chapter" || arguments[2] == "-c")
		{
			//proceed to the get the chapter number which is the next argument
			if(arguments.size() > 3)
			{
				chapterNumber = parseInt(arguments[3]);
				if(chapterNumber > 0)
				{					
					chapter = arguments[3];
				}else
				{
					chapterNumber = -1;
					cout<<"Invalid chapter "<<arguments[3]<<endl;
				}
			}else
			{
				cout<<"Invalid chapter ' '"<<endl;
			}

			// next get the particular verse if specified
			if(arguments.size() > 4)
			{
				if(arguments[4] == "-verse" || arguments[4] == "verse" || arguments[4] == "-v")
				{
					// check the verse argument
					if(arguments.size() > 5)
					{
						// get the verse number
						nVerse = parseInt(arguments[5]);
						if(nVerse > 0){
							isSingleVerseMode = true;
						}else{
							cout<<"Invalid verse '"<<nVerse<<"'"<<endl;
						}
					}
				}else{
					cout<<"Invalid argument "<<arguments[4]<<endl;
				}				
			}
		}else
		{
			cout<<"Invalid command "<<arguments[2]<<"-chapter needs an integer argument, 0 provided!"<<endl;			
		}
	}
	string foundBook; //the name of the book that has been found
	if(bookname != "" && bookContains(bookname, bookNames, true, foundBook))
	{
		myChapters = myBible.find(foundBook)->second;
		nChapters = myChapters.size();
		cout<<"Opening "<<bookname<<endl;
		isBookOpen = true;
		isChapterOpen = false; //chapter not open for new book
		bookName = foundBook;   //this book has now been opened

		//if chapter argument is valid
		if(chapter != "")
		{
			cout<<" chapter "<<chapterNumber<<endl;
			isChapterOpen = true;
			cout<<"Attempting to open chapter"<<endl;
			cout<<"Book has "<<nChapters<<" chapter(s)"<<endl;
			if(chapterNumber <= nChapters)
			{
				printBibleVerses(myChapters[chapterNumber - 1], bookName, chapterNumber);
			}else
			{
				cout<<"Invalid chapter, Chapter should be in range 1 - "<<nChapters<<endl;
			}
		}
	}else
	{
		cout<<"Could not find \""<<bookname<<"\""<<endl;
	}
	cout<<endl;
}

void chapter(vector<string> arguments)
{
	if(!isBookOpen)
	{
		cout<<"Error! Book has to open to open chapter!!!"<<endl;
	}else
	{
		if(arguments.size() > 1)
		{
			//make sure the next argument is a number
			chapterNumber = parseInt(arguments[1]);
			if(chapterNumber > 0)
			{
				if(chapterNumber <= nChapters)
				{
					cout<<"opening chapter "<<chapterNumber<<" from "<<bookName<<endl;				
					printBibleVerses(myChapters[chapterNumber - 1], bookName, chapterNumber);
					isChapterOpen = true;
				}else
				{
					chapterNumber = -1;
					cout<<"Invalid chapter, Chapter should be in range 1 - "<<nChapters<<endl;
				}

				// next get the particular verse if specified
				if(arguments.size() > 2)
				{
					if(arguments[2] == "-verse" || arguments[2] == "verse" || arguments[2] == "-v")
					{
						// check the verse argument
						if(arguments.size() > 3)
						{
							// get the verse number
							nVerse = parseInt(arguments[3]);
							if(nVerse > 0){
								isSingleVerseMode = true;
							}else{
								cout<<"Invalid verse '"<<nVerse<<"'"<<endl;
							}
						}
					}else{
						cout<<"Invalid argument "<<arguments[4]<<endl;
					}				
				}				
			}else
			{
				chapterNumber = -1;
				cout<<"Invalid chapter "<<arguments[1]<<endl;
			}
		}else
		{
			cout<<"1 argument expected 0 found\n"<<endl;
		}		
	}
}

//go to the next chapter in the open book
//this is only possible is there's a chapter open
bool nextChapter()
{
	if(isBookOpen)
	{
		if(isChapterOpen && chapterNumber != -1)
		{
			if(chapterNumber + 1 > nChapters)
			{
				cout<<"Last chapter already open"<<endl;
				return false;
			}
			cout<<"Opening next chapter "<<++chapterNumber<<" of "<<bookName<<endl;
			printBibleVerses(myChapters[chapterNumber - 1], bookName, chapterNumber);
			return true;
		}else
		{
			cout<<"Failed to open next chapter because no chapter has been open yet!"<<endl;
		}
	}else
	{
		cout<<"Invalid operation, no book is currently open!"<<endl;
	}
	return false;
}

bool previousChapter()
{
	if(isBookOpen)
	{
		if(isChapterOpen)
		{
			if(chapterNumber - 1 < 1)
			{
				cout<<"This is the first chapter of the bible"<<endl;
				return false;
			}
			cout<<"Opening previous chapter "<<--chapterNumber<<" of "<<bookName<<endl;
			printBibleVerses(myChapters[chapterNumber - 1], bookName, chapterNumber);
			return true;
		}else
		{
			cout<<"Failed to open previous chapter because no chapter has been open yet!"<<endl;
		}
	}else
	{
		cout<<"Invalid operation, no book is currently open!"<<endl;
	}
	return false;
}

void searchBible(vector<string> arguments)
{
	//construct arguments for the search program
	//[start] [search] [search word] [bookstart] <lastbook>
	string command = "start search";
	if(arguments.size() > 1)
	{
		command += (" \"" + arguments[1] + "\""); //search word
		if(arguments.size() > 2)
		{
			command += (" " + arguments[2]); //book start
			if(arguments.size() > 3)
			{
				command += (" " + arguments[3]); //book end
			}
		}
	}	
	cout<<"Input search command: "<<command<<endl;
	const char* strCommand = stringToConstCharString(command);
	cout<<"Search command: "<<strCommand<<endl;  //so we can see the search command
	system(strCommand);
}

void printBibleVerses(vector<string> chapterVerses, string bookName, int chapterNumber)
{
	cout<<endl;
	cout<<"================================"<<endl;
	cout<<bookName<<" Chapter "<<chapterNumber<<endl;
	cout<<"================================"<<endl;

	if(isSingleVerseMode)
	{	
		if(chapterVerses.size() >= nVerse)
		{
			cout<<nVerse<<".  "<<chapterVerses[nVerse - 1]<<endl;
		}else
		{
			cout<<"Invalid verse, verse must be in ange (1 - "<<chapterVerses.size()<<")"<<endl;
		}		
	}else{
		for(int a = 0; a < chapterVerses.size(); a++)
		{
			cout<<a + 1<<".  "<<chapterVerses[a]<<endl;
		}
	}
	isSingleVerseMode = false;
}

//Compares a string with other strings in a vector<string> container,
//returns true if the string item matches any of the strings in the container else return false
//if the string is found, its also return in the outResult variable passed into the function
bool bookContains(string item, vector<string> container, bool ignoreCase, string &outResult)
{
	for(int a = 0; a < container.size(); a++)
	{
		//both strings will be compared in lower case if case to be ignored
		if(ignoreCase && strToLower(item) == strToLower(container[a]))
		{
			outResult = container[a];
			return true;
		}else if(!ignoreCase && item == container[a])
		{
			outResult = container[a];
			return true;
		}
	}
	return false;
}

void getBook(map<string, vector<vector<string>>> bible, string bookName)
{
	vector<vector<string>> myChapters = bible.find(bookName)->second;
	cout<<"The book of "<<bookName<<" contains "<<myChapters.size()<<" chapters"<<endl;
	int selectedChapter;
	string userResponse;

	//make sure you get the right kind of input
	cout<<"Enter the chapter number(1 - "<<myChapters.size()<<"): ";
	cin>>selectedChapter;
	cin.ignore();

	while(selectedChapter > myChapters.size() || selectedChapter < 1)
	{
		cout<<"Invalid chapter"<<endl;
		//make sure you get the right kind of input
		cout<<"Enter the chapter number(1 - "<<myChapters.size()<<"): ";
		cin>>selectedChapter;
		cin.ignore();
	}
	do
	{			
		printBibleVerses(myChapters[selectedChapter - 1], bookName, selectedChapter);
		cout<<endl;
		if(++selectedChapter > myChapters.size())
		{
			break;
		}
		//make sure you get the right kind of input
		cout<<"Next chapter(y/n)? ";
		cin>>userResponse;
		cin.ignore();
	}while(userResponse != "n");
	cout<<"Closing book...!"<<endl;
	cout<<endl;
}

int main(int argv, char* args[])
{
	system("Title The Holy Bible - King James Version");
	cout<<"THE HOLY BIBLE [VERSION 2.0.4]"<<endl;
	cout<<"(C)2018 AEMIS INC."<<endl;
	cout<<endl;

	//this is where everything in the bible is contained
	//every book is accessed using its name
	map<string, vector<vector<string>>> bible;
	//contains all the name of the books in the bible
	vector<string> bookNames; 
	string relDataFile = "Data\\data.txt";
	string exeFileName = args[0];
	int index = exeFileName.find_last_of("\\");
	string dataFile = subString(exeFileName, 0, index) + relDataFile;
	//cout<<exeFileName<<endl;
	//cout<<dataFile<<endl;
	//string dataFile ="Desktop\\The Holy Bible\\Data\\data.txt";

	//contains all the content of a chapter
	//all the chapters of a book are loaded here before inserting it into the bible
	vector<vector<string>> chapters;
	vector<string> chapterVerses;

	string lastBookName = "";
	string lastChapter = "";

	ifstream fileReader(dataFile);
	string line;
	int numberOfVerses = 0;

	if(fileReader.is_open())
	{
		cout<<"Loading bible..."<<endl;
		while(!fileReader.eof())
		{
			getline(fileReader, line);
			numberOfVerses++;

			//line contains everythin we need
			vector<string> bookContent = split(line, "|");
			string currentBookName = bookContent[0];
			string currentChapterNumber = bookContent[1];
			string currentVerse = bookContent[2];
			string currentVerseContent = bookContent[3];

			//cout<<currentBookName<<" "<<currentChapterNumber<<":"<<currentVerse<<" "<<currentVerseContent<<endl;

			if(lastBookName == "" || lastBookName != currentBookName)
			{
				if(lastBookName != "")
				{
					//add the last chapter of the last book before adding book
					if(chapterVerses.size() > 0)
					{
						//cout<<"Adding new chapter."<<endl;
						chapters.push_back(chapterVerses);
						bible.insert(pair<string, vector<vector<string>>>(lastBookName, chapters));

						cout<<lastBookName<<", ";
						bookNames.push_back(lastBookName);
						chapters.clear();
						chapterVerses.clear();
					}					
				}
				//a new book has been found
				lastBookName = currentBookName;
				lastChapter = currentChapterNumber;
				//cout<<"Adding new verse "<<chapterVerses.size() + 1<<": "<<currentVerseContent<<endl;
			    chapterVerses.push_back(currentVerseContent);
			}else
			{
				//continue with current book
				if(lastChapter == "" || lastChapter != currentChapterNumber)
				{
					//goto new chapter
					if(lastChapter != "")
					{
						//cout<<"Adding new chapter."<<endl;
						chapters.push_back(chapterVerses);
						chapterVerses.clear();
					}
					lastChapter = currentChapterNumber;
					//cout<<"Adding new verse "<<chapterVerses.size() + 1<<": "<<currentVerseContent<<endl;
					chapterVerses.push_back(currentVerseContent);
				}else
				{
					//continue with the current chapter
					//cout<<"Adding new verse "<<chapterVerses.size() + 1<<": "<<currentVerseContent<<endl;
					chapterVerses.push_back(currentVerseContent);
				}
			}
		}		

		//add the last chapter of the bible
		if(chapterVerses.size() > 0)
		{
			chapters.push_back(chapterVerses);
		}
		//add the last book of the bible
		if(chapters.size() > 0)
		{
			bible.insert(pair<string, vector<vector<string>>>(lastBookName, chapters));
			cout<<lastBookName<<endl;
			bookNames.push_back(lastBookName);
			chapters.clear();
			chapterVerses.clear();
		}
	}else
	{
		cout<<"Failed to load application data...\nClosing application...";
		cin.ignore();
		return 0;
	}
	cout<<"Done Loading bible... contains "<<numberOfVerses<<" verses"<<endl;
	fileReader.close();
	cout<<"The bible contains "<<bible.size()<<" books"<<endl;
	cout<<endl;
	
	//*****************************************************************************************
	myBible = bible;
	string command;
	while(true)
	{
		cout<<"\nkjv>> ";
		getline(cin, command);

		if(command.length() < 1) { continue;} //ignore empty command

		//arguments are not case sentitive
		command = strToLower(command);
		
		if(command == "exit" || command == "quit")
		{
			cout<<"Are you sure? ";
			string ans = "n";
			cin>>ans;
			cin.ignore();
			ans = strToLower(ans);
			if(ans == "y") { break; }
			continue; //go back to receive commands
		}
		
		//-----------------ACCEPT BOOK NAMES WITH WHITESPACES--------------------------------------------------------------------
		int n = getOccurrences(command, '"');
		bool isQuoteFound = false;
		for(char &i : command)
		{
			if(i == '"') 
			{
				isQuoteFound = !isQuoteFound;
				n--;
			}

			if(isQuoteFound && i == ' ' && n >= 1) //there must be a closing quote
			{
				i = '_'; //replace the white space with underscore
			}
		}

		vector<string> arguments = split(command, " ");

		for(int a = 0; a < arguments.size(); a++)
		{
			//because no '_' should be found in any argument in the command
			for(char &s : arguments[a])
			{
				if(s == '_' || s == '"') { s = ' '; }
			}
			//to replace whitespaces that might have been produced by the previous operation
			arguments[a] = trim(arguments[a]);  
		}

		//cout<<"Number of arguments "<<arguments.size()<<endl;		
		//-------------------------------------------------------------------------------------------------
		
		if(arguments[0] == "open" || arguments[0] == "-open" || arguments[0] == "-o")
		{
			open(arguments, bookNames);
		}else if(arguments[0] == "chapter" || arguments[0] == "-chapter" || arguments[0] == "-c")
		{
			chapter(arguments);
		}else if(arguments[0] == "help" || arguments[0] == "-help" || arguments[0] == "-h")
		{
			help(arguments);
		}else if(arguments[0] == "next" || arguments[0] == "-next" || arguments[0] == "-n")
		{
			nextChapter();
		}else if(arguments[0] == "prev" || arguments[0] == "-prev" || arguments[0] == "-p")
		{
			previousChapter();
		}else if(arguments[0] == "search" || arguments[0] == "-search" || arguments[0] == "-s")
		{
			//validate there're at least 3 arguments <search command> [search word] [begining]
			if(arguments.size() < 3)
			{
				cout<<"A minimum of 3 arguments: \"<search command> [search word] [begining] expected\" "<<arguments.size()<<" found"<<endl;
			}else
			{
				searchBible(arguments);
			}
				
		}else{
			cout<<"Invalid command "<<arguments[0]<<endl;
		}
	}
	
	cout<<"Closing bible...!"<<endl;
	cout<<endl;
	cout<<"Press enter to close...";
	cin.ignore();
	return 0;
}
