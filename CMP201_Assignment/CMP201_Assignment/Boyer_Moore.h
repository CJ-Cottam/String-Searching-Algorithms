#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <string>
//ASCII Character
#define NoChars 256
using std::string;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::sort;
using std::ofstream;
using std::ifstream;
class Boyer_Moore
{
public:
	void run_BM(string& text, string& pattern);// Pre running
	void BoyerMoore(string& text, string& pattern);//Algorithm
	void Results(string& pattern);//Results function
	void ChangeTargets(string& text, string& pattern); //Change targets
	Boyer_Moore(); //Constructor
	vector<int> BM_Index; // Vector collection type for storing multiple int locations
	vector<double> BM_Times; // Vector collection type for storing multiple int locations
	~Boyer_Moore(); // Destructor
private:
	int Pattern_length, Text_length;
	char PromptAnswer;
	double mean;
	int skip[256];
	int Choice;
	int counter;
	string Filename;
};

