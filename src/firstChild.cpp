#include <iostream>
#include <cctype>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {    
    if(argc < 2) {
        cerr << "No word provided" << endl;
        return 1;
    }

    string word = argv[1];

    for(int i = 0; i < word.length(); i++) {
        word[i] = toupper(word[i]);
    }

    word += '\n';

    cout << word;

    return 0;
}