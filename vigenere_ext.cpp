#include <bits/stdc++.h>

using namespace std;

vector<char> stringToVecChar(string s) {
	vector<char> v;
	char ch;
	for (int i = 0; i < s.size(); ++i)
	{
		ch = s[i];
		v.push_back(ch);
	}
	return v;
}

void printVecChar(vector<char> v) {
	int kel_huruf = 5;
	for (int i = 0; i < v.size(); ++i)
	{
		printf("%c", v[i]);
		if ((i % kel_huruf) == (kel_huruf-1))
		{
			printf(" ");
		}
	}
}

void printVecCharInHex(vector<char> v) {
	char ch;
	for (int i = 0; i < v.size(); ++i)
	{
		ch = v[i];
		printf("%x ", ch & 0xff);
	}
	printf("\n");
}

string deleteSpace(string s) {
	s.erase(remove(s.begin(),s.end(),' '),s.end());
	return s;
}

vector<char> encrypt(string plaintext, string key) {
	//Delete Space

}

vector<char> decrypt(string plaintext, string key) {

}

vector<char> openFile(string filename);

int main(int argc, char const *argv[])
{
	return 0;
}