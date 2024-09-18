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
    
    vector<char> alphabetLetters = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    vector<char> alphabetSimbols = {'"','!','(',')','/','?',',','.',':',';','#','@','&','\\','*','-','+','_','=','\''};

    vector<int> newAlphabet = newAlphabetGenerate(alphabetLetters);
    vector<int> newAlphabetSimbols = newAlphabetGenerate(alphabetSimbols);

    int opcao;
    do{
        cout << endl << "1. KMP" << endl;
        cout << "2. Wildscore" << endl;
        cout << "3. Cifra e quebra de cifra" << endl;
        cout << "0. FIM DO PROGRAMA." << endl;
        cout << "Digite opção desejada: ";
        cin >> opcao;

        switch(opcao){
            case 1:
            {
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
                wildscoreSearch(bookStringToSearch,searchToUpper, words);

                break;
            }
            case 3:
            {
                cin.ignore();
                
                int opcao2;
                string text;
                
                do{
                    cout << endl << "1. Entrar com o texto" << endl;
                    cout << "2. Ver texto de sugestão dos desenvolvedores" << endl;
                    cout << "3. Ver tradução do alfabeto" << 
                    endl;
                    cout << "0. Voltar para o menu principal" << endl << endl;
                    
                    cout << "Digite opção desejada: ";
                    cin >> opcao2;

                    if(opcao2 == 1){
                        
                        cin.ignore();
                        cout << "Digite texto: ";
                        getline(cin, text);

                        cout << endl << "STRING: " << text << endl << endl;

                        encryptAndDecrypt(alphabetLetters, alphabetSimbols, newAlphabet, newAlphabetSimbols, text);
                    }else if(opcao2 == 2){
                        
                        text = "* Why hello there! It's a beautiful day, isn't it? The birds are singing and the flowers are blooming. What a perfect day to be alive! :) *";

                        cout << endl << "STRING: " << text << endl << endl;

                        encryptAndDecrypt(alphabetLetters, alphabetSimbols, newAlphabet, newAlphabetSimbols, text);
                    }else if(opcao2 == 3){
                        
                        translatedAlphabets(alphabetLetters, alphabetSimbols, newAlphabet, newAlphabetSimbols);
                    }
                    else
                        cout << "Opção inválida!" << endl;
                }while(opcao2 != 0);                
            }
        }
    }while (opcao != 0);

    return 0; 
}