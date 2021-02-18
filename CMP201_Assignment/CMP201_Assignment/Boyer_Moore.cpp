#include "Boyer_Moore.h"
#include"utils.h"

Boyer_Moore::Boyer_Moore()
{
	PromptAnswer = ' ';
	Text_length = 0;
	Pattern_length = 0;
	Text_length = 0;
	Choice = 0;
	counter = 0;
	mean = 0;
}
Boyer_Moore::~Boyer_Moore()
{
	cout << "Boyer Moore Destructor called" << endl;
}



void Boyer_Moore::run_BM(string& text, string& pattern)
{
	Pattern_length = pattern.length();
	Text_length = text.length();
	while (Choice == 0)
	{
		auto start_Time = std::chrono::steady_clock::now();
		BoyerMoore(text, pattern);
		auto Finish_Time = std::chrono::steady_clock::now();
		std::chrono::duration<double> FinalTime = Finish_Time - start_Time;
		BM_Times.push_back(FinalTime.count());
		Results(pattern);
		BM_Index.clear();
		BM_Index.erase(BM_Index.begin(), BM_Index.end());
		BM_Index.shrink_to_fit();

		cout << "Would you like to quit? Y/N" << endl;
		cin >> PromptAnswer;
		if (PromptAnswer == 'y' || PromptAnswer == 'Y')
		{
			Choice = 1;

			BM_Times.clear();
			BM_Times.erase(BM_Times.begin(), BM_Times.end());
			BM_Times.shrink_to_fit();
		}
		else
		{
			cout << "Change the Pattern or file? Y/N" << endl;
			cin >> PromptAnswer;
			if (PromptAnswer == 'y' || PromptAnswer == 'Y')
			{
				ChangeTargets(text, pattern);
			}
		}
		counter++;
	}
}

//The Boyer Moore algorithm
void Boyer_Moore::BoyerMoore(string& text, string& pattern)
{
	//The skip table being filled the value from the pattern length variable
	for (int i = 0; i < 256; i++)
	{
		skip[i] = Pattern_length;
	}
	for (int i = 0; i < Pattern_length; ++i)
	{
		skip[int(pattern[i])] = (Pattern_length - 1) - i;
	}


	for (int i = 0; i < Text_length - Pattern_length; ++i) {
		int j;
		// s variable used to check the single hash value
		int  s = skip[int((unsigned char)text[i + Pattern_length - 1])];

		if (s != 0)
		{
			i += s - 1;
			continue;
		}

		for (j = 0; j < Pattern_length; j++) {
			if (text[i + j] != pattern[j]) {
				break; // Doesn't match here.
			}
		}
		if (j == Pattern_length) {
			BM_Index.push_back(i + 1); // if match push the index to the vector
		}
	}
}
//Results function
void Boyer_Moore::Results(string& pattern)
{
	//If the index is empty then display a message saying not found
	if (BM_Index.empty())
	{
		cout << "Pattern: " << pattern << " was not found" << endl;
	}
	else
	{
		//Else display the values from the RK_Index and RK_Times vectors
		for (int item : BM_Index)
		{
			cout << "Found " << pattern << "' at index " << item << "\n" << endl;
		}
		
		cout << "Times" << endl;
		counter = 1;
		for (double item : BM_Times)
		{
			cout << "Test " << counter++ << ": " << item << endl;
			mean += item;
		}
		cout << "Mean: " << mean / BM_Times.size() << endl;
		cout << "The word " << pattern << " was found " << BM_Index.size() << " times" << endl;
	}
}
//Change target function
void Boyer_Moore::ChangeTargets(string& text, string& pattern)
{
	cout << "Which target would you like to change?\n1-Text file\n2-Pattern" << endl;
	cin >> Choice;
	if (Choice == 1)
	{
		cout << "File Name " << endl;
		cin >> Filename;
		text;
		load_file(Filename, text);  //load the function from utils.h to change the loaded file
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
