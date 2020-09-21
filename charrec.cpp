/*
ID: rupertl1
PROG: charrec
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>
#include <utility>
#include <string.h>
#include <iterator>
#include <vector>
#include <iomanip>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <stack>
#include <list>

using namespace std;

const int infinity = 2000000000;

enum Corruption {missing, none, duplicated};
const int NumChars = 27, Length = 20, NumCorruptions = 3;
const string characters = " abcdefghijklmnopqrstuvwxyz";
string **font;
string *input;
int n, *numCorruptions;
char *guess;
Corruption *type;
int ***differences;

int size(Corruption corruption) {
	int ret = Length;
	if (corruption == missing)
		ret--;
	else if (corruption == duplicated)
		ret++;
	return ret;
}
/*
	Finds best character ending at line finalLine
	Output recorded to guess[finalLine]
	Number of 0 vs. 1 corruptions to numCorruptions[finalLine]
	Type of corruption to type[finalLine]
	Parameters:
	finalLine: index of final line to consider in input
	corruption: type of corruption (missing / duplicated)
	corruptedLine: index of missing/duplicated line
*/
void find_best_char(int finalLine, Corruption corruption, int corruptedLine = -1) {
	// Check: valid number of lines to analyze
	if ((corruption == none && finalLine < Length - 1) || (corruption == duplicated && finalLine < Length))
		return;
	int prevFinalLine = finalLine - size(corruption);
	int prevCorruptions = 0;
	// Check: There was a result for the previous chunk of lines
	if (prevFinalLine >= 0) {
		if (guess[prevFinalLine] == '?')
			return;
		prevCorruptions = numCorruptions[prevFinalLine];
	}
	// For every character:
	for (int character = 0; character < NumChars; character++) {
		// our total number of 0 vs. 1 corruptions for the case
		int corruptions = 0;
		int maxCorruptions = 0;
		// line is the line number of the current character
		// inputLine is the actual index of the line from input
		for (int line = 0, inputLine = prevFinalLine + 1; line < Length; line++, inputLine++) {
			//take care of missing and duplicated line cases
			if (corruption == missing && line == corruptedLine) {
				inputLine--;
				continue;
			}
			if (corruption == duplicated && line == corruptedLine + 1 && inputLine - prevFinalLine - 1 == corruptedLine + 1)
				line--;
			// calculating the number of differences between inputLine
			// vs. the corresponding line from the character
			if (differences[inputLine][character][line] == -1) {
				differences[inputLine][character][line] = 0;
				for (int column = 0; column < Length; column++)
					if (input[inputLine][column] != font[character][line][column])
						differences[inputLine][character][line]++;
			}
			corruptions += differences[inputLine][character][line];
			if (corruption == duplicated && line == corruptedLine && differences[inputLine][character][line] > maxCorruptions)
				maxCorruptions = differences[inputLine][character][line];
		}
		corruptions -= maxCorruptions;
		int totalCorruptions = corruptions + prevCorruptions;
		if (totalCorruptions < numCorruptions[finalLine]) {
			numCorruptions[finalLine] = totalCorruptions;
			guess[finalLine] = characters[character];
			type[finalLine] = corruption;
		}
	}
}

// Recursive construction from final answer based on guess
string construct_string(int i) {
	if (i < Length - 2)
		return "";
	return construct_string(i - size(type[i])) + guess[i];
}

int main() {

	ifstream fin("charrec.in");
	ofstream fout("charrec.out");
	ifstream fontin("font.in");

	// font: array of known letters, stored as array of strings (lines)
	font = new string*[NumChars];
	fontin >> n;
	for (int i = 0; i < NumChars; i++) {
		font[i] = new string[Length];
		for (int j = 0; j < Length; j++)
			fontin >> font[i][j];
	}
	fontin.close();

	// input: array of strings (lines)
	fin >> n;
	input = new string[n];
	for (int i = 0; i < n; i++)
		fin >> input[i];
	fin.close();

	// number of 0 vs 1 corruptions
	numCorruptions = new int[n];
	// guess of which char 
	guess = new char[n];
	type = new Corruption[n];
	differences = new int**[n];

	// initialization
	for (int i = 0; i < n; i++) {
		numCorruptions[i] = infinity;
		guess[i] = '?';
		type[i] = none;
		differences[i] = new int*[NumChars];
		for (int j = 0; j < NumChars; j++) {
			differences[i][j] = new int[Length];
			for (int k = 0; k < Length; k++)
				differences[i][j][k] = -1;
		}
	}

	// line runs from the 19th line (minimum) to the last line
	for (int line = Length - 2; line < n; line++) {
		find_best_char(line, none);
		// relative index of the corrupted line
		for (int corruptedLine = 0; corruptedLine < Length; corruptedLine++) {
			find_best_char(line, missing, corruptedLine);
			find_best_char(line, duplicated, corruptedLine);
		}
	}

	// Now guess has the best character option ending at each finalLine.
	// We do not know immediately know the best "path" of corruptions
	// However we figure this out by backtracking
	// As we know that it has to end at the last line
	// So we just subtract the number of lines based on type

	fout << construct_string(n-1) << endl;
	fout.close();

	return 0;
}
