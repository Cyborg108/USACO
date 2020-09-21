/*
ID: rupertl1
PROG: palsquare
LANG: C++11
*/
/*
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;


int main() {

	ofstream fout("palsquare.out");
	ifstream fin("palsquare.in");

	int b;
	fin >> b;
	int x[9];
	int y[17];
	bool flag = true;
	for (int n = 1; n <= 300; n++) {
		for (int i = 0; i < 9; i++) x[i] = 0;
		for (int i = 0; i < 17; i++) y[i] = 0;
		//convert to base b
		int temp;
		temp = n;
		for (int d = 8; d >= 0; d--) {
			long p = pow(b, d);
			while (temp >= p) {
				temp = temp - p;
				x[8 - d] = x[8 - d] + 1;
			}
		}
		string num;
		string nums;
		//convert x array into string.
		//Need to eliminate leading zeroes.
		//Then convert int number < 10 into string number < 10.
		//Finally convert int number >= 10 into string ABC...
		int q1 = 0;
		while (x[q1] == 0) {
			q1++;
		}
		if (q1 == 8) {
			if (x[8] < 10) num += to_string(x[8]);
			else num += string(1, (char)(55 + x[8]));
		}
		else {
			for (int i = q1; i <= 8; i++) {
				if (x[i] < 10) num += to_string(x[i]);
				else num += string(1, (char)(55 + x[i]));
			}
		}

		int s = n*n;
		int t = s;
		if (b == 2) {
			for (int d = 16; d >= 0; d--) {
				long p2 = pow(b, d);
				while (t >= p2) {
					t = t - p2;
					y[16 - d] = y[16 - d] + 1;
				}
			}
		}
		else if (b == 3) {
			for (int d = 10; d >= 0; d--) {
				int p2 = pow(b, d);
				while (t >= p2) {
					t = t - p2;
					y[16 - d] = y[16 - d] + 1;
				}
			}
		}
		else if (b == 4) {
			for (int d = 8; d >= 0; d--) {
				int p2 = pow(b, d);
				while (t >= p2) {
					t = t - p2;
					y[16 - d] = y[16 - d] + 1;
				}
			}
		}
		else {
			for (int d = 7; d >= 0; d--) {
				int p2 = pow(b, d);
				while (t >= p2) {
					t = t - p2;
					y[16 - d] = y[16 - d] + 1;
				}
			}
		}
		//check if y is a palindrome
		int q = 0;
		while (y[q] == 0) {
			q++;
		}
		flag = true;
		for (int i = 0; i <= 16-q; i++) {
			if (y[16-i] != y[q + i]) {
				flag = false;
				break;
			}
		}
		if (q == 16) {
			if (y[16] < 10) nums += to_string(y[16]);
			else nums += string(1, (char)(55 + y[16]));
		}
		else {
			for (int j = q; j <= 16; j++) {
				if (y[j] < 10) nums += to_string(y[j]);
				else nums += string(1, (char)(55 + y[j]));
			}
		}
		if (flag == true) {
			fout << num << " " << nums << endl;
		}
		
		
	}
}
*/

/*
ID: rupertl1
PROG: palsquare
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;


int main() {

	ofstream fout("palsquare.out");
	ifstream fin("palsquare.in");

	int b;
	fin >> b;
	int x[9];
	int y[17];
	bool flag = true;
	for (int n = 1; n <= 300; n++) {
		for (int i = 0; i < 9; i++) x[i] = 0;
		for (int i = 0; i < 17; i++) y[i] = 0;
		//convert to base b
		int temp;
		temp = n;
		unsigned long long p = (unsigned long long)b;
		p *= p*p*p*p*p*p*p;
		for (int d = 8; d >= 0; d--) {
			//long p = pow(b, d);
			while (temp >= p) {
				temp = temp - p;
				x[8 - d] = x[8 - d] + 1;
			}
			p = p / b;
		}
		string num;
		string nums;
		//convert x array into string.
		//Need to eliminate leading zeroes.
		//Then convert int number < 10 into string number < 10.
		//Finally convert int number >= 10 into string ABC...
		int q1 = 0;
		while (x[q1] == 0) {
			q1++;
		}
		if (q1 == 8) {
			if (x[8] < 10) num += to_string(x[8]);
			else num += string(1, (char)(55 + x[8]));
		}
		else {
			for (int i = q1; i <= 8; i++) {
				if (x[i] < 10) num += to_string(x[i]);
				else num += string(1, (char)(55 + x[i]));
			}
		}

		int s = n*n;
		int t = s;
		if (b == 2) {
			long p2 = 65536;
			for (int d = 16; d >= 0; d--) {
				//long p2 = pow(b, d);
				while (t >= p2) {
					t = t - p2;
					y[16 - d] = y[16 - d] + 1;
				}
				p2 = p2 / 2;
			}
		}
		else if (b == 3) {
			int p2 = 59049;
			for (int d = 10; d >= 0; d--) {
				//int p2 = pow(b, d);
				while (t >= p2) {
					t = t - p2;
					y[16 - d] = y[16 - d] + 1;
				}
				p2 = p2 / 3;
			}
		}
		else if (b == 4) {
			int p2 = 65536;
			for (int d = 8; d >= 0; d--) {
				//int p2 = pow(b, d);
				while (t >= p2) {
					t = t - p2;
					y[16 - d] = y[16 - d] + 1;
				}
				p2 = p2 / 4;
			}
		}
		else {
			unsigned long long p2 = (unsigned long long)b;
			p2 *= p2*p2*p2*p2*p2*p2;
			for (int d = 7; d >= 0; d--) {
				int p2 = pow(b, d);
				while (t >= p2) {
					t = t - p2;
					y[16 - d] = y[16 - d] + 1;
				}
				p2 = p2 / b;
			}
		}
		//check if y is a palindrome
		int q = 0;
		while (y[q] == 0) {
			q++;
		}
		flag = true;
		for (int i = 0; i <= 16 - q; i++) {
			if (y[16 - i] != y[q + i]) {
				flag = false;
				break;
			}
		}
		if (q == 16) {
			if (y[16] < 10) nums += to_string(y[16]);
			else nums += string(1, (char)(55 + y[16]));
		}
		else {
			for (int j = q; j <= 16; j++) {
				if (y[j] < 10) nums += to_string(y[j]);
				else nums += string(1, (char)(55 + y[j]));
			}
		}
		if (flag == true) {
			fout << num << " " << nums << endl;
		}


	}
}