#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
#include "asciiArts.cpp"
using namespace std;

typedef string Ing;

string format(string s) {
    string ans = "";

    for(int i = 0; i < s.size(); ++i) {

        if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
            ans += tolower(s[i]);
        }
        else if(s[i] == ' ') {
            ans += ' ';
        }
    }
    return ans;
}

class User {
public:
    vector<Ing> ingredients;

    User() {}
    
    void addIngredient() {

        printLouro();

        while(true) {
            cout << "\nDigite o" << RED << " Nome " << RESET << "do Ingrediente que deve ser adicionado: ";
        
            Ing ingredient;
            getline(cin >> ws, ingredient);
            ingredient = format(ingredient);

            for(int i = 0; i < ingredients.size(); ++i) {
                if(ingredients[i] == ingredient) {
                    cout << RED << "\nIngrediente ja esta na sua lista!\n" << RESET;
                    break;
                }
                else if(i == ingredients.size() - 1) {
                    ingredients.push_back(ingredient);
                    cout << GREEN << "\nIngrediente Adicionado!\n" << RESET;
                    break;
                }
            }

            if(ingredients.size() == 0) {
                ingredients.push_back(ingredient);
                cout << GREEN << "\nIngrediente Adicionado!\n" << RESET;   
            }

            printAddMenu();

            int op;
            cout << "Escolha a opção: ";
            cin >> op;
            while (!cin.good()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        
            switch(op) {

                case 1:
                    break;
                case 2:
                    system("clear");
                    return;

                default:
                    printAdvice();
                    getchar();
                    system("clear");
                    return;
            }
        }
    }

    void removeIngredient() {

        printCoffee();

        while(true) {
            Ing ingredient;

            cout << "\nEscreva o" << RED << " Nome " << RESET << "do Ingrediente que deve ser Removido: ";
            
            cin >> ingredient;
            ingredient = format(ingredient);

            if(ingredients.size() == 0)
                cout << RED << "\nEsse Ingrediente não esta na sua lista!\n" << RESET;

            else for(int i = 0; i < ingredients.size(); ++i) {

                if(ingredients[i] == ingredient) {
                    ingredients.erase(ingredients.begin() + i);
                    cout << GREEN << "\nIngrediente Removido!\n" << RESET;
                    break;
                }

                else if(i == ingredients.size() - 1) {
                    cout << RED << "\nEsse Ingrediente não esta na sua lista!\n" << RESET;
                }
            }

            printRemoveMenu();

            int op;
            cout << "Escolha a opção: ";
            cin >> op;
            while (!cin.good()) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            switch(op) {
                case 1:
                    break;
                case 2:
                    system("clear");
                    return;
                default:
                    printAdvice();
                    getchar();
                    system("clear");
                    return;
            }
        }
    }

    void printAllIngredients() {

        if(ingredients.size() == 0) {
            printNoIngredientsAdvice();
            sleep(3);
            system("clear");
            return;
        }

        printPasta();

        cout << ORANGE;

        cout << "\t\t\t\t\t_____________________________________\n";

        for(int  i = 0; i < ingredients.size(); ++i) {

            cout << "\t\t\t\t\t|       |                           |\n";

            cout << "\t\t\t\t\t|   " << i + 1 << "   |";
            int l = ingredients[i].size();

            for(int j = 0; 2*j < (27 - l); ++j) {
                cout << " ";
            }

            cout << ingredients[i];

            for(int j = 0; j < 27 - l - (27 - l)/2; ++j) {
                cout << " ";
            }

            cout << "|\n\t\t\t\t\t|_______|___________________________|\n";

        }

        cout << "\n\t\t\t\t\t    Esses são seus ingredientes!\n" << RESET;

        cout << "\n\t\t\t\t\tPressione ENTER para voltar para o menu";
        getchar();
        getchar();
        system("clear");

    }

    void cleanIngredientsList(){
        ingredients.clear();
    }
};