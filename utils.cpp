#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utils.h"

using std::cerr;
using std::cout;
using std::ifstream;
using std::string;
using std::vector;
using std::endl;
void die(const string& msg) {
	cerr << "Error: " << msg << endl;
#ifdef _DEBUG
	abort();
#else
	exit(1);
#endif
}

void load_file(const string& filename, string& str) {
	// To make this program less fussy about where exactly it's run
	// from relative to the file, try looking in parent directories too.
	std::string directory = "";
	for (int i = 0; i < 6; i++) {
		ifstream f(directory + filename, std::ios_base::binary);
		if (!f.good()) {
			directory = "../" + directory;
			continue;
		}

		// Seek to the end of the file to find its length.
		f.seekg(0, std::ios_base::end);
		const size_t length = f.tellg();

		// Seek back to the start of the file and read the data.
		vector<char> buf(length);
		f.seekg(0);
		f.read(buf.data(), length);
		str.assign(buf.begin(), buf.end());

		return;
	}

	die("Unable to find " + filename);
}

