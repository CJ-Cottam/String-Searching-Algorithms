#include "Rabin_Karp.h"
#include "utils.h"
Rabin_Karp::Rabin_Karp()
{
	PatHash = 0;
	TextHash = 0;
	MultiplerMSB = 1;
	PromptAnswer = ' ';
	Text_length = 0;
	Pattern_length = 0;
	Text_length = 0;
	Choice = 0;
	mean = 0;
}

//The Rabin Karp algorithm
void Rabin_Karp::RabinKarp(string & text, string&pattern)
{
	int i, j; // Iterators for loops

	//Two long long variables to store the hashes for the pattern and Text
	PatHash,TextHash = 0;

	//Multipler for the most significant bit
	MultiplerMSB = 1;
	for (i = 0; i < Pattern_length - 1; i++)
	{
		MultiplerMSB = (MultiplerMSB * NoChars) % PrimeNum;
	}
	//Using the AdamsTerribleHash function from week 7 as it is more efficent
	TextHash = AdamsTerribleHash(text);
	PatHash = AdamsTerribleHash(pattern);

	//The compute hash function
	//TextHash = compute_hash(text);
	//PatHash = compute_hash(pattern);

	//Creating the hash for pattern and Text
	for (i = 0; i < Pattern_length; i++) {
		PatHash = (PrimeNum * PatHash + pattern[i]) % PrimeNum;
		TextHash = (PrimeNum * TextHash + text[i]) % PrimeNum;
	}

	for (i = 0; i <= Text_length - Pattern_length; i++)
	{
		if (PatHash == TextHash)
		{
			for (j = 0; j < Pattern_length; j++)
			{
				if (text[i + j] != pattern[j])
				{
					break;
				}
			}
			if (j == Pattern_length) //If pattern has been found, the position index is pushed onto the vector.
			{
				RK_Index.push_back(i + 1);
			}
		}
		TextHash = (PrimeNum * (TextHash - text[i] * MultiplerMSB) + text[i + Pattern_length]) % PrimeNum;
		if (TextHash < 0)
		{
			TextHash = (TextHash + PrimeNum);
		}
	}
}

//This function calls to the Rabin Karp Algorithm and gives user input for options to change algorithms or change the pattern or text
void Rabin_Karp::RK_Run(string &text, string&pattern)
{
	//Assign the length of the pattern and text to two variables called Pattern_length and Text_Length
	Pattern_length = pattern.length();
	Text_length = text.length();
	while (Choice == 0)
	{
		//Starting Time
		auto start_Time = std::chrono::steady_clock::now();
		RabinKarp(text, pattern);
		//Ending Time
		auto Finish_Time = std::chrono::steady_clock::now();
		//The Final Time calculated
		std::chrono::duration<double> FinalTime = Finish_Time - start_Time;
		//The final time is pushed onto the vector storing the multiple times
		RK_Times.push_back(FinalTime.count());
		//Display results
		Results(pattern);
		//To reduce memory and storage, we clear the values from the RK_Index vector
		RK_Index.clear();
		RK_Index.erase(RK_Index.begin(), RK_Index.end());
		RK_Index.shrink_to_fit();
		//Asks the user if they would like to return to the main menu
		cout << "Would you like to go back to the main menu? Y/N" << endl;
		cin >> PromptAnswer;
		//IF yes then the values in the RK_Times vector are cleared and erase rom the vector and ends the while loop
		if (PromptAnswer == 'y' || PromptAnswer == 'Y')
		{
			system("cls");
			Choice = 1;
			RK_Times.clear();
			RK_Times.erase(RK_Times.begin(), RK_Times.end());
			RK_Times.shrink_to_fit();
		}
		else //Else ask the user if they would like to change either the pattern or the file.
		{
			cout << "Change the Pattern or file? Y/N" << endl;
			cin >> PromptAnswer;
			if (PromptAnswer == 'y' || PromptAnswer == 'Y')
			{
				ChangeTargets(text,pattern);
			}
		}
	}
}

//Adam Sampsons 'Terrible Hash Function from Week 7
unsigned int Rabin_Karp::AdamsTerribleHash(string &text)
{
	int hash = 0;
	for (char c : text) {
		hash += int(c);
	}
	return hash;
}

//Computing Hash function
unsigned long long Rabin_Karp::compute_hash(string& text)
{
	const int m = 1e9+9;
	int hash = 0;
	long long p_pow = 1;
	for (char c : text) {
		hash = (hash + (c - 'a' + 1) * p_pow) % m;
		p_pow = (p_pow * PrimeNum) % m;
	}
	return hash;
}

Rabin_Karp::~Rabin_Karp()
{
	cout << "Rabin Karp Destructor Called" << endl;
}

//Results Function
void Rabin_Karp::Results(string& pattern)
{
	//If the index vector is empty then display a message saying the pattern was not found
	if (RK_Index.empty())
	{
		cout << "Pattern: " << pattern << " was not found" << endl;
	}
	else
	{	//Else display the values from the RK_Index and RK_Times vectors
		
		for (int item : RK_Index)
		{
			cout << "Found " << pattern << "' at index " << item << "\n" << endl;
		}
		

		cout << "Times" << endl;
		int counter = 1;
		for (double item : RK_Times)
		{
			cout << "Test " << counter++ << ": " << item << endl;
			mean += item;
		}
		//The Mean
		cout << "Mean: " << mean / RK_Times.size() << endl;
		cout << "The word " << pattern << " was found " << RK_Index.size() << " times" << endl;
	}
}

//Change target function
void Rabin_Karp::ChangeTargets(string& text, string& pattern)
{
	//Asks the user if they want to change either the text file or pattern
	cout << "Which target would you like to change?\n1-Text file\n2-Pattern" << endl;
	cin >> Choice;
	if (Choice == 1)
	{
		cout << "File Name " << endl;
		cin >> Filename;
		text;
		load_file(Filename, text); //load the function from utils.h to change the loaded file
		Text_length = text.length();
	}
	else if (Choice == 2)
	{
		cout << "What is the new pattern?" << endl;
		cin >> pattern;
		Pattern_length = pattern.length();
	}
	Choice = 0;
}
