#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

string trim(string s) {
    while (!s.empty() && isspace(s.back())) s.pop_back();
    while (!s.empty() && isspace(s.front())) s.erase(s.begin());
    return s;
}

int tleCheck(const string& cmd) {
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd.c_str(), NULL);
        exit(0);
    }

    int status;
    auto start = chrono::steady_clock::now();
    while (true) {
        if (waitpid(pid, &status, WNOHANG)) return status;
        if (chrono::duration<double>(chrono::steady_clock::now() - start).count() > 5) {
            kill(pid, SIGKILL);
            return -1;
        }
        usleep(1000);
    }
}

int main() {
    system("g++ sol.cpp -std=gnu++23 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -O2 -o sol");

    ifstream f("tests.db");
    if (!f) {
        cerr << "No tests.db found!\n";
        return 1;
    }

    vector<pair<string, string>> tests;
    string line, in, out;

    while (getline(f, line)) {
        if (line == "###") {
            in.clear(); out.clear();

            while (getline(f, line) && line != "@@@") in += line + '\n';
            while (getline(f, line) && line != "###") out += line + '\n';

            tests.push_back({in,out});

            if (line == "###") f.seekg(-4, ios::cur);
        }
    }

    int tc = 1;
    for (auto& [tin, tout] : tests) {
        ofstream("int") << tin;
        int res = tleCheck("./sol < int > out1");
        cout << "Test " << tc++ << ": ";

        if (res == -1) {
            cout << YELLOW << "Time Limit Exceeded!" << RESET << endl;
            continue;
        }

        ifstream fo("out1");
        string user((istreambuf_iterator<char>(fo)), {});

        if (trim(user) == trim(tout)) {
            cout << GREEN << "Accepted" << RESET << endl;
        } else {
            cout << RED << "Wrong Answer" << RESET << endl;
            cout << YELLOW << "Expected: \n" << tout;
            cout << "Got: \n" << user << RESET << endl;
        }
    }
}