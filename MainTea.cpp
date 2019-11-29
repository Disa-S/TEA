#include <iostream>
#include <fstream> //check readio
#include <string> //string
#include <iterator> // ostream_iterator
#include <sstream>

using std::ifstream;
using std::string;
std::ofstream ofile;
// simple TEA implementation

void writetofile(unsigned long text[], unsigned long key[]) {
	string out = "encrypted.txt";
	std::ofstream outfile(out);
	outfile << text
		<< "\n"
		<< key
		<< std::endl;

	std::cout << "\n Writing to file ";
	std::cout << out;
	outfile.close();
}

void encrypt(unsigned long k[], unsigned long text[]) { //encrypt by "distributing and mixing" each bit from inputs by blocks
	unsigned long y = text[0], z = text[1];
	unsigned long delta = 0x9e3779b9, sum = 0; int n;
	//for (int kj =0; kj< text.length();
	for (n = 0; n < 32; n++) {
		sum += delta;
		y += ((z << 4) + k[0]) ^ (z + sum) ^ ((z >> 5) + k[1]);
		z += ((y << 4) + k[2]) ^ (y + sum) ^ ((y >> 5) + k[3]);
	}
	text[0] = y, text[1] = z;

	writetofile(text, k);

	//return 0;
}


void decrypt(unsigned long k[], unsigned long text[]) { // same as encryption but - instead of +
	unsigned long y = text[0], z = text[1];
	unsigned long delta = 0x9e3779b9, sum = 0; int n;
	for (n = 0; n < 302; n++) {
		sum -= delta;
		y -= ((z << 4) + k[0]) ^ (z + sum) ^ ((z >> 5) + k[1]);
		z -= ((y << 4) + k[2]) ^ (y + sum) ^ ((y >> 5) + k[3]);
	}
	text[0] = y, text[1] = z;
	writetofile(text, k);

}

long GetFileSize(string filename) {
	struct stat stat_buf;
	int rc = stat(filename.c_str(), &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}

unsigned long readio(string usertext) { //read file to buffer as a whole
	unsigned long ul = 0;
	std::ifstream ifs(usertext);
	std::stringstream buffer;
	buffer << ifs.rdbuf();
	string str = buffer.str();

	try {ul = stoul(str, nullptr, 0);	}
	catch (std::out_of_range) {
		const char* array = str.c_str();
		for (int i = 0; i < 8; ++i) {
			ul = ul | ((unsigned long)array[i] << (8 * i)); }
		ul = (unsigned long) array;
	}
	ifs.close();
	return ul;
}
unsigned long generator() { //generate random long for TEA
	unsigned char MyBytes[4];
	unsigned long MyNumber = 0;
	unsigned char* ptr = (unsigned char*)&MyNumber;
	MyBytes[0] = rand() % 256; //0-255
	MyBytes[1] = rand() % 256; //256 - 65535
	MyBytes[2] = rand() % 256; //65535 -
	MyBytes[3] = rand() % 256; //16777216
	memcpy(ptr + 0, &MyBytes[0], 1);
	memcpy(ptr + 1, &MyBytes[1], 1);
	memcpy(ptr + 2, &MyBytes[2], 1);
	memcpy(ptr + 3, &MyBytes[3], 1);

	return(MyNumber);
}

void menu() { //menu 
	int choice;
	unsigned long userlong;

	string usertext;
	std::cout <<
		"##########################\n"
		<< "#Encrypt using TEA # \n"
		<< "#Make a selection # \n"
		<<
		"##########################"
		<< std::endl;
	std::cout << std::endl
		<< "\t\t 1. Encryption \n"
		<< "\t\t 2. Decryption \n"
		<< "\t\t 3. Quit \n"
		<< std::endl << "\t\t\t Make your selection";
	std::cout << std::endl;

	std::cin >> choice;

	if (choice == 1) {
		std::cout <<
		"\t File to encrypt."
		<< std::endl;
		std::cin >> usertext;

		unsigned long buffer =  readio(usertext);
		unsigned long userlong = generator();
		std::cout << buffer;
		encrypt(&userlong, &buffer); //pass the pointer
	}

	else if (choice == 2) {
		std::cout <<
			"\t File to decrypt."
			<< std::endl;
		std::cin >> usertext;

		unsigned long buffer = readio(usertext);
		std::cout <<
			"\t Decrypting Key."
			<< std::endl;
		std::cin >> userlong;
		decrypt(&userlong, &buffer); //pass the pointer
	}
	else if (choice == 3) {

	}
	else { std::cout << "Not a valid choice. \n\n"; }

}

int main() {	menu();
	return 0;
}
