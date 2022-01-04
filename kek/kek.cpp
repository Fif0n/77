#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "string"

using namespace std;

class cipher {
public:
    ifstream fIn1;
    ifstream fIn2;
    ofstream fOut;

    int repentence = 0;

    cipher();
    ~cipher();
    string code(string key, string text);
    string decode(string key, string text);
    void count(string text);

};

cipher::cipher() {
    fIn1.open("c:\\dokad.txt");
    fIn2.open("c:\\szyfr.txt");
    fOut.open("c:\\Vigenere_wyniki.txt");
}

cipher::~cipher() {
    fIn1.close();
    fIn2.close();
    fOut.close();
}

string cipher::code(string key, string text) {
    string newText = "";
    int whiteChars = 0;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            newText += ' ';
            whiteChars++;
        }
        else if (text[i] == '.') {
            newText += '.';
            whiteChars++;
        }
        else if (text[i] == ',') {
            newText += ',';
            whiteChars++;
        }
        else {
            int x = i - whiteChars;
            int k = int(text[i] - 'A') + int(key[x % key.length()] - 'A');
            newText += char((k % 26) + 'A');
        }
    }

    repentence = ceil(float(text.length() - whiteChars) / key.length());
    return newText;
}

string cipher::decode(string key, string text) {
    string newText = "";
    int whiteChars = 0;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            newText += ' ';
            whiteChars++;
        }
        else if (text[i] == '.') {
            newText += '.';
            whiteChars++;
        }
        else if (text[i] == ',') {
            newText += ',';
            whiteChars++;
        }
        else {
            int x = i - whiteChars;
            int k = int(text[i] - 'A') - int(key[x % key.length()] - 'A');
            while(k < 0) {
                k += 26;
            }
            
            newText += char(k + 'A');
        }
    }

    
    return newText;
}

void cipher::count(string text) {
    int t[26];
    for (int i = 0; i < 26; i++) {
        t[i] = 0;
    }
    for (int i = 0; i < text.length(); i++) {
        t[text[i] - 'A' ]++;
    }
    for (int i = 0; i < 26; i++) {
        fOut<<char(i+'A')<<":"<<t[i]<<endl;
    }

    double k = 0;
    for (int i = 0; i < 26; i++) {
        int l = 0;
        l += (t[i] - 1) * t[i];
        k += l;
    }
    int sum = 0;
    for (int i = 0; i < 26; i++) {
        sum += t[i];
    }
   
    int n = (sum - 1) * sum;
    k = k / n;
    
    double d;
    double ko = k;
    ko = ko - 0.0385;
    d = 0.0285 / ko;
    
    d += 0.005;
    d = 0.01 * int(100 * d);
    fOut << "wyniki" << endl;
    fOut << d<<endl;
    fOut << round(d);
   
    
}

int main()
{
    cipher c1;
    string f1;

    getline(c1.fIn1, f1);
    c1.fOut << "77.1" << endl;
    c1.fOut << c1.code("LUBIMYCZYTAC", f1) << endl;
    c1.fOut << "liczba powtorzen: " << c1.repentence << endl;

    string f2, c2;
    c1.fOut << "77.2" << endl;
    getline(c1.fIn2, f2);
    getline(c1.fIn2, c2);
    c1.fOut << c1.decode(c2, f2)<<endl;
    c1.fOut << "77.3" << endl;
    c1.count(f2);

}

