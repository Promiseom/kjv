#include <iostream>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

//prints all the content of a vector
void print(vector<string> container)
{
	for(int a = 0; a < container.size(); a++)
	{
		cout<<container[a]<<", ";
	}
	cout<<endl;
}

//returns the number of times a certain character occurs in a string
int getOccurrences(string str, char c)
{
	int count = 0;
	for(char a : str)
	{
		if(a == c){ count++; }
	}
	return count;
}

//converts a string to an integer
//converts a string representing a non-negative integer to an integer
int parseInt(string num)
{
	map<char, int> numbers;
	//insert the values
	numbers.insert(pair<char, int>('0', 0));
	numbers.insert(pair<char, int>('1', 1));
	numbers.insert(pair<char, int>('2', 2));
	numbers.insert(pair<char, int>('3', 3));
	numbers.insert(pair<char, int>('4', 4));
	numbers.insert(pair<char, int>('5', 5));
	numbers.insert(pair<char, int>('6', 6));
	numbers.insert(pair<char, int>('7', 7));
	numbers.insert(pair<char, int>('8', 8));
	numbers.insert(pair<char, int>('9', 9));

	int finalNumber = 0;
	int nDigits = num.length();
	for(int a = 0; a < nDigits; a++)
	{
		//make sure this is an int digit
		if(numbers.find(num[a])->first < 48 ||  numbers.find(num[a])->first > 57)
		{
			return -1;  //-1 means the number was not converted, because the number is not valid
		}
		finalNumber += pow(10, (nDigits - 1 - a)) * numbers.find(num[a])->second;
	}
	return finalNumber;
}

//Get the substring of a string from start index to end index inclusive
string subString(string str, int startIndex, int end)
{
	//check index bounds
	if(startIndex > end || startIndex >= str.length() || end == str.length() || end < 0)
	{
		return "";
	}

	string subString = "";
	for(int a = startIndex; a <= end; a++)
	{
		subString += str[a];
	}
	return subString;
}

//Remove all trailing whitespaces
string trim(string str)
{
	string finalString = "";
	bool isFirstReal = false;
	for(int a = 0; a < str.length(); a++)
	{
		if(str[a] == ' ' && !isFirstReal)
		{
			continue;
		}
		finalString += str[a];
		isFirstReal = true;
	}
	//remove all whitespaces from the back
	for(int a = finalString.length() - 1; a >= 0; a--)
	{
		if(finalString[a] != ' ')
		{
			finalString = subString(finalString, 0, a);
			break;
		}
	}
	return finalString;
}

//splits a string into an array of strings
//the string splitted using the splitChars
//this fuction has implemented for specific use in this program, 
//this function will need modification to be used in another project
vector<string> split(string str, string splitCharacters)
{
	vector<string> words;
	for(int i = 0; i < splitCharacters.length(); i++)
	{
		//checks all occurrences of this character
		int index;
		while((index = str.find_first_of(splitCharacters[i])) < str.length())
		{
			string foundWord = subString(str, 0, index - 1);
			words.push_back(trim(foundWord));
			if(index + 1 < str.length())
			{
				str = subString(str, index + 1, str.length() - 1);
			}else
			{
				str = "";
			}
			//the argument e
		}
	}
	if(str.length() > 0)
	{
		words.push_back(trim(str));
	}
	return words;
}

//Converts all the characters to lower case
string strToLower(string str)
{
	string lowerString = str;
	for(auto& s : lowerString)
	{
		s = tolower(s);
	}
	return lowerString;
}

//compares the equality of 2 strings,
//ignores the case if the ignoreCase argument is true
bool compare(string str1, string str2, bool ignoreCase)
{
	return (ignoreCase)? strToLower(str1) == strToLower(str2) : str1 == str2;
}

string removeSymbols(string str)
{
	string finalString = "";
	map<int, string> unwantedSymbols;
	unwantedSymbols.insert(pair<int, string>(44, ","));
	unwantedSymbols.insert(pair<int, string>(34, "\""));
	unwantedSymbols.insert(pair<int, string>(58, ":"));
	unwantedSymbols.insert(pair<int, string>(41, ")"));
	unwantedSymbols.insert(pair<int, string>(40, "("));
	unwantedSymbols.insert(pair<int, string>(95, "_"));
	unwantedSymbols.insert(pair<int, string>(93, "]"));
	unwantedSymbols.insert(pair<int, string>(91, "["));
	unwantedSymbols.insert(pair<int, string>(126, "~"));
	unwantedSymbols.insert(pair<int, string>(45, "-"));
	unwantedSymbols.insert(pair<int, string>(46, "."));

	for(char a : str)
	{ 
		if(unwantedSymbols.find(a)->first > 11) { continue; }
		finalString += a;
	}
	return finalString;
}

//returns true if a substring can be found within a string
//a match is found if the 
bool find(string subString, string str, bool ignoreCase)
{
	vector<string> subStrings = split(subString, " ");
	vector<string> strStrings = split(str, " ");

	int nMatches = 0;
	for(string a : subStrings)
	{
		for(string b : strStrings)
		{
			//string c = removeSymbols(b);
			//cout<<"comparing: "<<a<<"("<<a.length()<<") and "<<c<<"("<<c.length()<<")";
			if(compare(a, removeSymbols(b), ignoreCase))
			{
				//cout<<"     match found";
				nMatches++;
				break;  //go to another search word
			}
			//cout<<endl;
		}
	}
	if(subStrings.size() >= 2) { return nMatches >= 2; }
	return nMatches > 0;
}

//converts a string to a 'const char*'
const char * stringToConstCharString(string convString)
{
	int strLength = convString.length();
	char * strOutput = new char[strLength];
	for(int a = 0; a < strLength; a++)
	{
		strOutput[a] = convString[a];
	}
	return strOutput;
}