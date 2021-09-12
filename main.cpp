/*
    Gabriel Alves Kuabara - nUSP 11275043
    Daniel Carvalho Dantas - nUSP 10685702 
    Pedro Afonso Perez Chagas - nUSP 7777970
    Antonio Italo Lima Lopes - nUSP 12542290
*/

/*
    Rascunho do Projeto: MidnightGororoba

    - Classe usuário
        - Ingredientes
        - Métodos:
            - Adicionar ingrediente
                - Perguntar nome e quantidade
                - Verificar se já existe na lista
            - Remover ingrediente
                - Perguntar nome e quantidade
                - Remover quantidades
            - Ver ingredientes
            - Limpar ingredientes
    - Classe Receita
        - Ingredientes essenciais
        - Ingredientes opcionais

    - Loop Principal
        - Adicionar Ingredientes
            - Informe o número de ingredientes
            - lista de ingredientes
        - Remover Ingredientes
        - Ver ingredientes atuais
        - Ver receitas possíveis com ingredientes atuais
            - Busca linear contando quantos ingredientes dão match
        - Fechar Programa
    - Banco de dados com receitas
    - Interfaces
        - Inicio:
            - Welcome to Midnight Gororoba
                - Pedir para pressionar uma tecla
            - Menu:
                - Inserir ingredientes
                - Remover ingredientes
                - Buscar receitas
                - "Já achei minha receita, obrigado MidnightGororoba!"
    - Artes ASCII
        - Welcome to Midnight Gororoba
        - Vergonha da Profission
        - Ratatouile?
        - *****Ratatonho*****
        - Imagens de receitas?
*/

/*
    Interface:
    
    - Start: Pepe lindo
        - Mudar mensagem de inicio
        - Colocar enter dentro de caixinha
        - Colocar mensagem

    - Menu:
        - Uma caixinha para cada opção (1 a 5)      
        - Escolha uma opção: 
        - SYSTEM.clear
        
        - Inserir Ingredientes:
            - Tabela Similar ao menu para repetir ou voltar ao menu
            - ASCII Art acompanhando (Ratatonho???)
            - Mensagem de efeito
            - Pedindo o ingrediente
            - Mensagem de confirmação
            - Requisitando outro ingrediente ou menu
            - Mensagem para ingrediente repetido ("sabe ler não?")
            

        - Retirar Ingredientes:
            - Tabela Similar ao menu para repetir ou voltar ao menu
            - ASCII Art acompanhando
            - Mensagem de efeito
            - Mensagem Pedindo ingrediente
            - Confirmação de remoção
            - Mensagem para ingrediente que não foi colocado ("sabe ler não?")
        
        - Listar Ingredientes:
            - Tem ingrediente:
                - Listar os ingredientes em tabela
                - Volta pra menu
            - Não tem ingredientes:
                - Se não houver ingredientes listados, vergonha da profission?
                - "Inflação tá alta, né meu filho?"
                - Volta pro menu
        
        - Buscar Receitas: 
            - Botar ASCII art do chefe incrível como tela de loading - 2/3s
            - Receitas Listadas em tabelas
            - Se não encontrar receitas, vergonha da profission e mandar ir no mercado.
            - Voltar para menu

        - Sair do programa: 
            - ASCII meme
            - vai ser peidão mesmo?
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
#include "recipe.cpp"
#include "user.cpp"
#include "asciiArts.cpp"
using namespace std;

vector<Recipe> recipes, possibleRecipes;

void startRecipes() {

    ifstream file("receitas.txt");

    string line;
    while(getline(file, line) && file.good()) {
        cout << line << endl;
        if (line.empty()) break;
        recipes.push_back(Recipe(line));
    }
}

bool compareRecipes(Recipe a, Recipe b) {
    return (a.nOptionals >= b.nOptionals);
}

bool isSubstring(string a, string b) {

    for(int i = 0; i + a.size() <= b.size(); ++i) {
        if(b.substr(i, a.size()) == a)
            return true;
    }

    return false;
}

void calculateMatches(User& user) {

    possibleRecipes.clear();

    for(int i = 0; i < recipes.size(); ++i) {

        Recipe& recipe = recipes[i];

        recipe.nNeeds = 0;
        recipe.nOptionals = 0;

        for(int j = 0; j < recipe.needs.size(); ++j) {
            for(int k = 0; k < user.ingredients.size(); ++k) {
                if(isSubstring(user.ingredients[k], recipe.needs[j]))
                    ++recipe.nNeeds;
            }
        }
    
        for(int j = 0; j < recipe.optionals.size(); ++j) {
            for(int k = 0; k < user.ingredients.size(); ++k) {
                if(isSubstring(user.ingredients[k], recipe.optionals[j]))
                    ++recipe.nOptionals;
            }
        }

        if(recipe.nNeeds == recipe.needs.size()) {
            possibleRecipes.push_back(recipe);
        }
    }

    sort(possibleRecipes.begin(), possibleRecipes.end(), compareRecipes);
}

void printPossibleRecipes() {
    if(possibleRecipes.size() == 0) {
        printShame();
        sleep(3);
        system("clear");
        return;
    }

    printChef();
    cout << "\n\t\t\t\t\t\t   Procurando receitas...\n";
    sleep(2);
    system("clear");

    printCroissant();

    cout << BOLDCYAN;

    cout << "\t\t\t\t\t_____________________________________________\n";
    cout << "\t\t\t\t\t|       |                                   |\n";
    cout << "\t\t\t\t\t|   " << 0 << "   |";  
    cout << "   Voltar para o Menu Principal    ";
    cout << "|\n\t\t\t\t\t|_______|___________________________________|\n";
    
    for(int  i = 0; i < possibleRecipes.size(); ++i) {

        cout << "\t\t\t\t\t|       |                                   |\n";

        cout << "\t\t\t\t\t|   " << i + 1 << "   |";
        int l = possibleRecipes[i].name.size();

        for(int j = 0; 2*(j + 1) <= (35 - l); ++j) {
            cout << " ";
        }

        cout << possibleRecipes[i].name;

        for(int j = 0; j < 35 - l - ((35 - l)/2); ++j) {
            cout << " ";
        }

        cout << "|\n\t\t\t\t\t|_______|___________________________________|\n";

    }   
    cout << RESET;

    while (true) {
        cout << "\nSelecione uma das Receitas: ";
        int select;
        cin >> select;
        while (!cin.good()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (select == 0) {
            system("clear");
            break;   
        }
        else if (select > 0 && select <= possibleRecipes.size()){ // ]0, size]
            possibleRecipes[select - 1].printRecipe();
        }
        else{
            printAdvice();
            cout << "\n\t\t\t\t\t\t\t    Voltando para o menu...\n";
            sleep(3);
            system("clear");
            break;
        }
    }

}

void menu () {
    User user = User();

    int option;
    while(true) {
        printMenu();
        cout << "Escolha uma opção: ";
        cin >> option;
        while (!cin.good()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        system("clear");

        switch (option) {
            case 1:
                user.addIngredient();
                break;
            case 2:
                user.removeIngredient();
                break;
            case 3:
                user.printAllIngredients();
                break;
            case 4:
                calculateMatches(user);
                printPossibleRecipes();
                break;
            case 5:
                printPepe();
                getchar();
                return;
            default:
                printAdvice();
                break;
        }
    }
}

void printInitialScreen() {
    system("clear");
    printWelcome();
    getchar();
    system("clear");
}

int main() {
    startRecipes();
    printInitialScreen();    
    menu();
    return 0;
}
