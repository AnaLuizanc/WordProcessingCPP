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

vector<int> kmp(string text, string pattern){
    int indexText = 0;
    int indexPattern = 0;
    vector<int> table = createTable(pattern); 
    int counter = 0;

    vector<int> positions;

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
            positions.push_back(indexText-indexPattern);
            indexPattern = table[indexPattern-1];
            counter++;
        }
    }

    
    //cout << "\n\nPadrão encontrado " << counter << " vezes";
    
    return positions;
}

void wildcardSearch(string bookString, string search, int words){
    string bookStringToSearch;
    string searchToUpper;

    for(int i = 0; i < bookString.size(); i++)
        bookStringToSearch.push_back(toupper(bookString[i]));

    if(search[0] == '*'){
        string valueAfter;
        for(int i = 1; i < search.size(); i++)
            valueAfter.push_back(search[i]);
        for(int i = 0; i < valueAfter.size(); i++)
            searchToUpper.push_back(toupper(valueAfter[i]));

        vector<int> positionsAfter = kmp(bookStringToSearch, searchToUpper);

    
        for(int i = 0; i < positionsAfter.size(); i++){
        int j = 0;
        int spaceCounter = 0;
        while(spaceCounter != 2){
            if(bookString[positionsAfter[i] - j] == ' ')
                spaceCounter++;
            j++;
        }

        int initialChar = positionsAfter[i] - j + 1;
        cout << "' ";

        int spaceInSearch = 0;        
        for(int i = 0; i < search.size(); i++)
            if(search[i] == ' ')
                spaceInSearch++;

        spaceCounter = 0;
        for(int i = 0; spaceCounter != spaceInSearch + 2; i++){
            cout << bookString[initialChar + i];
            if(bookString[initialChar + i] == ' ')
                spaceCounter++;
        }
        int initialCounter = positionsAfter[i];

        cout << "' in position: " << positionsAfter[i];
        cout << endl;
    }
    }
    else if(search[search.size() - 1] == '*'){
        search.pop_back();
        vector<int> positions = kmp(bookString, search);
        for(int i=0; i<positions.size(); i++){
            int startString = positions[i] + search.length();
            string concat;
            while(bookString[startString] != ' '){
                concat += bookString[startString];
                startString++;
            }
            cout << "'" << search << concat << "' ";
            cout << "in position: " << positions[i] << endl;
        }
    }
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

    string search = "* water and";

    wildcardSearch(bookString, search); 
    return 0; 
}