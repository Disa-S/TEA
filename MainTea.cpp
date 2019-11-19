#include <iosteam>
using namespace std;
// simple TEA implementation
void menu() { //menu 
    int choice = 0;
    cout <<
    "##########################\n"
        << "#Encrypt using TEA # \n"
        << "#Make a selection # \n"
        <<
        "########################"
    << endl;
        cout << endl
        << "\t\t 1. Encryption \n"
        << "\t\t 2. Decryption \n"
        << "\t\t 3. Quit \n"
        << endl << "\t\t\t make your selection";
        cout << endl;
        if (choice ==1) {
            encrypt();
        }
        else if(choice == 2) {
            decrypt();
        }
        else if (choice ==3) {
            
        }
        else { cout << "not a valid choice. \n\n"; menu();}
}

void encrypt(unsigned long k[], unsigned long text[]) { //encrypt by "distributing and mixing" each bit from inputs by blocks
    unsigned long y = text[0], z = text[1];
    unsigned long delta = 0x9e3779b9, sum = 0; int n;
    for (n =0; n < 32; n++) {
        sum+= delta;
        y += ((z<<4)+k[0]) ^ (z+sum) ^ ((z>>5)+k[1]);
        z += ((y<<4)+k[2]) ^ (y+sum) ^ ((y>>5)+k[3]);
    }
    text[0] = y, text[1] = z;
}

void decrypt(unsinged long k[], unsinged long text[]) { // same as encryption but - instead of +
    unsigned long y = text[0], z = text[1];
    unsigned long delta = 0x9e3779b9, sum = 0; int n;
    for (n =0; n < 32; n++) {
        sum -=delta;
         y -= ((z<<4)+k[0]) ^ (z+sum) ^ ((z>>5)+k[1]);
         z -= ((y<<4)+k[2]) ^ (y+sum) ^ ((y>>5)+k[3]);
        
    }
    text[0] = y, text[1] = z;
}

void main() {
    menu()
}
