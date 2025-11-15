
#include<iostream>
#include<set>
#include<fstream>
#include<new>
#include<algorithm>
#include<ctype.h>
#include<vector>
#include<cstdio>
using namespace std;

string formatInput(const string& input);
int getMenuOption();
void readUniqueWords(const set<string>&);
void readSharedWords(const set<string>&, const set<string>&);
void readWordsInInput1(const set<string>&, const set<string>&);
void readExclusiveWords(const set<string>&, const set<string>&);

int main() {
	fstream file1, file2;
		set<string>uniqueWordsF1,
			uniqueWordsF2;
		try {
			file1.open("fahrenheit 451.txt");
			if (!file1.is_open()) {
				throw "Error: File 1 not found";
			}
			do {
				string input;
				file1 >> input;
				if(!input.empty())
					uniqueWordsF1.emplace(formatInput(input));

			} while (!file1.eof());
			file1.close();
		}	catch (string error) {
		cout << error << endl;
		exit(EXIT_FAILURE);
		}
		try {
			file2.open("tale of two cities.txt");
			if (!file2.is_open()) {
				throw "Error: File 2 not found";
			}
			do {
				string input;
				file2 >> input;
				if(!input.empty())
				uniqueWordsF2.emplace(formatInput(input));
			} while (!file2.eof());
			file2.close();
		}catch (string error) {
			cout << error << endl;
			exit(EXIT_FAILURE);
		}

		int userOption;
		do {
			userOption = getMenuOption();
			switch (userOption) {
			case 1:
				cout << "\n\nDisplaying unique words in file 1\n";
				readUniqueWords(uniqueWordsF1);
				break;
			case 2:
				cout << "\n\nDisplaying unique words in file 2\n";
				readUniqueWords(uniqueWordsF2);
				break;
			case 3:
				cout << "\n\nDisplaying words shared by both files\n";
				readSharedWords(uniqueWordsF1, uniqueWordsF2);
				break;
			case 4:
				cout << "\n\nDisplaying words exclusive to file 1\n";
				readWordsInInput1(uniqueWordsF1, uniqueWordsF2);
				break;
			case 5:
				cout << "\n\nDisplaying words exclusive to file 2\n";
				readWordsInInput1(uniqueWordsF2, uniqueWordsF1);
				break;
			case 6:
				cout << "\n\nDisplaying words that only appear in one file and not the other\n";
				readExclusiveWords(uniqueWordsF1, uniqueWordsF2);
				break;
			case 7:
				cout << "\n\nHave a good day!\n";
				break;
			default:
				cout << "\n\nError: This program will now close\n";
			}
		} while (userOption!=7);
		return 0;
}

string formatInput(const string&input){
	if (input.size() == 0) {
		return "\0";
	}
	else {
		string temp;
		//	int index=0;
		for (int i = 0; i < input.size(); i++) {
			if (isalpha(input.at(i)))
			{
				temp.push_back(toupper(input.at(i)));
				//			index++;
			}
			else {
				break;
			}
		}
		temp.push_back('\0');
		//	string returnStr(temp);
		//	delete[] temp;
		//	return returnStr;
		temp.resize(temp.length());
		return temp;
	}
}

int getMenuOption() {
	bool tryAgain;
	int userOption=0;
	do {
		try {
			tryAgain = false;
			cout << "Please select from the following\n"
				<< "1) Access unique Words in file 1\n"
				<< "2) Access unique Words in file 2\n"
				<< "3) Access shared words in both files\n"
				<< "4) Access words exclusive to file 1\n"
				<< "5) Access words exlusive to file 2\n"
				<< "6) Access words that only appear in one file and not the other\n"
				<<"7) Exit\n";
			cin >> userOption;
			if (userOption < 1 || userOption > 7) {
				throw "ERROR: Invalid entry";
			}
		}
		catch (string error) {
			cout << error << endl
				<< "Please select an option 1-6\n\n";
			tryAgain = true;
		}
	}while (tryAgain);
	return userOption;
}

void readUniqueWords(const set<string>& input) {
	cout << "This set's unique words\n\n";
	for (string word : input) {
		cout << word << endl;
	}
}

void readSharedWords(const set<string>& input1, const set<string>& input2) {
	vector<string>sharedWords(input1.size()+input2.size());
	auto it=set_intersection(input1.begin(), input1.end(), input2.begin(), input2.end(), sharedWords.begin());
	sharedWords.resize(it - sharedWords.begin());
	cout << "Now displaying words that appear in both sets\n\n";
	for (string word : sharedWords) {
		cout << word << endl;
	}
}

void readWordsInInput1(const set<string>& input1, const set<string>& input2) {
	vector<string>uniqueWords(input1.size()+input2.size());
	auto it=set_difference(input1.begin(), input1.end(), input2.begin(), input2.end(), uniqueWords.begin());
	uniqueWords.resize(it - uniqueWords.begin());
	cout << "Now displaying words unique to this file\n\n";
	for (string word : uniqueWords) {
		cout << word << endl;
	}
}

void readExclusiveWords(const set<string>& input1, const set<string>&input2) {
	vector<string>exclusiveWords(input1.size()+input2.size());
	auto it=set_symmetric_difference(input1.begin(), input1.end(), input2.begin(), input2.end(), exclusiveWords.begin());
	exclusiveWords.resize(it - exclusiveWords.begin());
	cout << "Now displaying the words mutually exclusive to each set\n";
	for (string word : exclusiveWords) {
		cout << word << endl;
	}
}