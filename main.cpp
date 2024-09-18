#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "functions.cpp"

using namespace std;

int main(){
    ifstream bookFile("./GoT.txt");

    string bookString;
    string bookStringToSearch;
    string linha;


    if(bookFile.is_open()){
        while(getline(bookFile, linha))
            bookString.append(linha);
    }

    for(int i = 0; i < bookString.size(); i++)
        bookStringToSearch.push_back(toupper(bookString[i]));
    
    //string search = "water and *";

    int opcao;
    do{
        //system("clear");
        cout << endl << "1. KMP" << endl;
        cout << "2. Wildscore" << endl;
        cout << "3. Cifra e quebra de cifra" << endl;
        cout << "0. FIM DO PROGRAMA." << endl;
        cout << "Digite opção desejada: ";
        cin >> opcao;

        switch(opcao){
            case 1:
            {
                system("clear");
                cin.ignore(); //limpa buffer
                string search;
                cout << "Digite string a ser procurada: ";
                getline(cin, search);
                string searchToUpper;

                for(int i = 0; i < search.size(); i++)
                    searchToUpper.push_back(toupper(search[i]));

                vector<int> positions = kmp(bookStringToSearch, searchToUpper);
                for(int i=0; i < positions.size(); i++)
                    cout << "Padrão encontrado em: " << positions[i] << endl;
                cout << "O padrão ocorreu " << positions.size() << " vezes." << endl;

                break;
            }
            case 2:
            {
                system("clear");
                cin.ignore(); //limpa buffer
                string search;
                cout << "Digite string a ser procurada: ";
                getline(cin, search);
                string searchToUpper;

                for(int i = 0; i < search.size(); i++)
                    searchToUpper.push_back(toupper(search[i]));

                cout << endl << "Deseja mostrar quantas palavras? ";
                int words;
                cin >> words;

                cout << endl << "STRING PROCURADA: " << searchToUpper << endl << endl;
                searchString(bookStringToSearch,searchToUpper, words);

                break;
            }
        }
    }while (opcao != 0);
    

/*
    string search = "water and *";
    
    
    cout << "Deseja mostrar quantas palavras? ";
                int words;
                cin >> words;

                cout << "STRING PROCURADA: " << search << endl;
                //searchString(bookStringToSearch,searchToUpper, words);

    vector<char> alphabetLetters = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    vector<char> alphabetSimbols = {'"','!','(',')','/','?',',','.',':',';'};

    string text = "Ci?ga,rettes After. Sex!";

    cout << endl << "STRING A SER CIFRADA: " << text << endl << endl;

    encrypt(alphabetLetters, alphabetSimbols, text);
*/
    return 0; 
}