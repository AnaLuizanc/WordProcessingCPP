#include <iostream>
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
        }
    }
}

int main(){

    kmp("abaaaba caba abcaabababc", "abc");

    return 0; 
}