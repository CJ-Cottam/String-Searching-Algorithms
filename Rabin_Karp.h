#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <string>
//Prime Number & ASCII Characters
#define PrimeNum 31
#define NoChars 256
using std::string;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::sort;
using std::ifstream;
using std::ofstream;
class Rabin_Karp
{
public:
	void RabinKarp(string& text, string&pattern);
	void RK_Run(string& text, string& pattern);
	void Results(string& pattern);
	void ChangeTargets(string& text, string& pattern);
	Rabin_Karp();
	vector<int> RK_Index; // Vector collection type for storing multiple int locations
	vector<double> RK_Times; // Vector collection type for storing multiple int locations
	//Hash Functions
	unsigned int AdamsTerribleHash(string& text);
	unsigned long long compute_hash(string &text);
	~Rabin_Karp();
private:
	long long PatHash, TextHash;
	int MultiplerMSB;
	double mean;
	int Pattern_length, Text_length;
	char PromptAnswer;
	int Choice;
	string Filename;
};

