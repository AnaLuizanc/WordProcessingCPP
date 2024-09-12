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
            //cout << "Padrão encontrado em: " << indexText-indexPattern << endl;
            positions.push_back(indexText-indexPattern);
            indexPattern = table[indexPattern-1];
        }
    }
    return positions;
}

void searchString(string bookString, string search, int words){
    if(search[0] == '*' && search[search.length()-1] == '*'){
        search = search.substr(1,search.length()-1);
        search.pop_back();

        vector<int> positions = kmp(bookString, search);
        for(int i=0; i<positions.size(); i++){
            int startStringBefore = positions[i];
            startStringBefore--;
            int wordsCounterBefore = words;

            while(wordsCounterBefore > 0){
                startStringBefore--;
                if(bookString[startStringBefore-1] == ' ')
                    wordsCounterBefore--;
            }
            
            string concatBefore;
            
            while(startStringBefore < positions[i]){
                concatBefore += bookString[startStringBefore];
                startStringBefore++;
            }
            
            int startStringAfter = positions[i] + search.length();
            int wordsCounterAfter = words;
            
            string concatAfter;

            while(wordsCounterAfter > 0){
                concatAfter += bookString[startStringAfter];
                startStringAfter++;
                if(bookString[startStringAfter] == ' ')
                    wordsCounterAfter--;
            }

            cout << concatBefore << search << concatAfter << endl;
        }

    }else if(search[0] == '*'){
        search = search.substr(1,search.length()-1);
        vector<int> positions = kmp(bookString, search);
        for(int i=0; i<positions.size(); i++){
            int startString = positions[i];
            startString--;
            int wordsCounter = words;
            while(wordsCounter > 0){
                startString--;
                if(bookString[startString-1] == ' ')
                    wordsCounter--;
            }
            
            string concat;
            while(startString < positions[i]){
                concat += bookString[startString];
                startString++;
            }
            
            cout << "'" << concat << search << "' ";
            cout << "in position: " << positions[i] << endl;
        }
    }else if(search[search.length()-1] == '*'){
        search.pop_back();
        
        vector<int> positions = kmp(bookString, search);
        for(int i=0; i<positions.size(); i++){
            int startString = positions[i] + search.length();
            string concat;
            int wordsCounter = words;
            while(wordsCounter > 0){
                concat += bookString[startString];
                startString++;
                if(bookString[startString] == ' ')
                    wordsCounter--;
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
    
    //string search = "water and *";
    //string searchToUpper;

    //for(int i = 0; i < search.size(); i++)
        //searchToUpper.push_back(toupper(search[i]));


    string search = "water and *";
    
    cout << "Deseja mostrar quantas palavras? ";
    int words;
    cin >> words;

    cout << "STRING PROCURADA: " << search << endl;
    searchString(bookString,search, words);
    
    return 0; 
}