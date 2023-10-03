#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cstring>
#include  <stdio.h>
using namespace std;

int main() {
    string MyWord;

    getline(cin, MyWord);

    int pipe1[2];
    int pipe2[2];


    if (pipe(pipe1) == -1 or pipe(pipe2) == -1) {
        cerr << "Pipe error" << endl;
        return 1;
    }

    pid_t pid1 = fork();

    if (pid1 == -1) {
        cerr << "Fork failed" << endl;
        return 1;
    }

    if (pid1 == 0) {
        cout << "hello,its 1st proccess child" << endl;
       
        close(pipe1[0]);
        if (dup2(pipe1[1], STDOUT_FILENO) == -1) {
            cerr << "Dup2 error" << endl;
            return 1;
        }

        if (execl("./firstChild","./firstChild",MyWord.c_str(),nullptr) == -1) {
            cerr << "Execl error" << strerror(errno)<< endl;
            return 1;
        }

    }

    close(pipe1[1]);

    pid_t pid2 = fork();

    if (dup2(pipe1[0], STDIN_FILENO) == -1) {
        cerr << "Dup2 error" << endl;
        return 1;
    }

    if (pid2 == 0) {
        close(pipe2[0]);
        getline(cin,MyWord);
        close(pipe1[0]);
        if (dup2(pipe2[1], STDOUT_FILENO) == -1) {
            cerr << "Dup2 error" << endl;
            return 1;
        }
        if (execl("./secondChild","./secondChild",MyWord.c_str(),nullptr) == -1) {
            cerr << "Execl error" << strerror(errno)<< endl;
            return 1;
        }
    }

    close(pipe1[0]);
    close(pipe2[1]);

    if (pid1 > 0 and pid2 > 0) {
        if (dup2(pipe2[0], STDIN_FILENO) == -1) {
            cerr << "Dup2 error" << endl;
            return 1;
        }
        getline(cin,MyWord);
        cout <<  MyWord << endl;
        
        cout << "its parent proccess" << endl;

        wait(nullptr);
        wait(nullptr);
    }

    return 0;
}