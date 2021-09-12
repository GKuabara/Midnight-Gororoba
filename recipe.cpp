#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
#include <math.h>
#include "asciiArts.cpp"
using namespace std;

#define Delimiter ';'
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

int myStoi (string s) {
    int number = 0;
    for (int i = 0; i < s.size(); ++i)
        number += (s[i] - 48) * pow(10, (s.size() - i - 1));
    return number;
}

class Recipe {
public:
    int nNeeds;
    int nOptionals;
    string name;
    vector<string> needs;
    vector<string> optionals;
    vector<string> instructions;

    Recipe ();
    Recipe(string line) {
        stringstream lineStream(line);
        string token;
        int n;

        // gets name
        getline(lineStream, name, Delimiter);

        // gets number of key ingredients
        getline(lineStream, token, Delimiter);
        n = myStoi(token);

        // gets key ingredients
        while (n--) {
            getline(lineStream, token, Delimiter);
            needs.push_back(token);
        }

        // gets number of optional ingredients
        getline(lineStream, token, Delimiter);
        n = myStoi(token);

        // gets optional ingredients
        while (n--) {
            getline(lineStream, token, Delimiter);
            optionals.push_back(token);
        }

        // gets number of instructions
        getline(lineStream, token, Delimiter);
        n = myStoi(token);

        // gets instructions
        while (n--) {
            getline(lineStream, token, Delimiter);
            instructions.push_back(token);
        }
    }

        void printRecipe () {
            cout << endl << RED << name << RESET << endl;
            
            cout << BOLDRED;
            cout << "$ Ingredientes Necessários: ";
            for (int i = 0; i < needs.size(); ++i)
                cout << needs[i] << ", ";
            cout << RESET << endl;
            
            if (optionals.size() != 0) {
                cout << YELLOW;
                cout << "# Ingredientes Opcionais: ";
                for (int i = 0; i < optionals.size(); ++i)
                    cout << optionals[i] << ", ";
                cout << RESET << endl;
            }
            
            cout << ORANGE << "+ Instruções:\n";
            for (int i = 0; i < instructions.size(); ++i)
                cout << "\t" << i + 1 << " - " << instructions[i] << endl;
            cout << RESET << endl;
        }
};