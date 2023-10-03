#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

    string word = argv[1];
    stringstream ss(word);
    string temp;
    string res;

    while(ss >> temp){
        res += temp + " ";
    }

    if (!res.empty()) {
        res.pop_back();
    }
    res += '\n';
    cout << res;

    return 0;
}