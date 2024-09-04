#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> createTable(string pattern){
    int len = pattern.length();
    vector<int> table(len,0);

    int idx = 0;
    int j  = 1;
    while(j < len){
        if(pattern[idx] == pattern[j]){
            idx++;
            table[j] = idx;
            j++;
        }
        else if(idx > 0)
            idx = table[idx-1];
        else
            j++;
    }

    return table;
}

void kmp(string text, string pattern){
    int indexText = 0;
    int indexPattern = 0;
    vector<int> table = createTable(pattern); 
    int counter = 0;

    while(indexText < text.length()){
        if(text[indexText] == pattern[indexPattern]){
            indexText++;
            indexPattern++;
        }
        else if(indexPattern >0)
            indexPattern = table[indexPattern-1];
        else
            indexText++;

        if(indexPattern == pattern.length()){
            cout << "Padrão encontrado em: " << indexText-indexPattern << endl;
            indexPattern = table[indexPattern-1];
            counter++;
        }
    }

    cout << "\n\nPadrão encontrado " << counter << " vezes";
}

int main(){
    ifstream bookFile("./GoT.txt");

    string bookString;
    string bookStringToSearch;
    string linha;


    if(bookFile.is_open()){
        while(getline(bookFile, linha)){
            bookString.append(linha);
        }
    }

    for(int i = 0; i < bookString.size(); i++)
        bookStringToSearch.push_back(toupper(bookString[i]));
    
    string search = "when she came of age. For centuries the Targaryens had married brother to sister";
    string searchToUpper;

    for(int i = 0; i < search.size(); i++)
        searchToUpper.push_back(toupper(search[i]));



    kmp(bookStringToSearch, searchToUpper);
    return 0; 
}