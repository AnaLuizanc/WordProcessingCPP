using namespace std;

// Cria tabela do maior sufixo que também é prefixo.

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

// Executa KMP.

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
            positions.push_back(indexText-indexPattern);
            indexPattern = table[indexPattern-1];
        }
    }
    return positions;
}

/**Procura string com *
 * a procura pode ser feita das seguintes maneiras:
 *    * searchString -> return : palavras + searchString
 *    searchString * -> return : searchString + palavras
 *    * searchString * -> return : palavras + searchString + palavras
 * */ 

void wildscoreSearch(string bookString, string search, int words){
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

// Verifica se o número gerado em newAlphabetGenerate já existe.

int contains(vector<int> alphabet, int value){
    for(int i=0; i<alphabet.size(); i++){
        if(alphabet[i] == value)
            return i;
    }
    return -1;
}

// Gera um novo alfabeto para cifra.

vector<int> newAlphabetGenerate(vector<char> alphabet){
    vector<int> newAlphabet;
    srand(time(NULL));
    for(int i=0; i<alphabet.size(); i++){
        int number = rand()%alphabet.size();
        if(contains(newAlphabet, number) == -1){
            newAlphabet.push_back(number);
        }else
            --i;
    }

    return newAlphabet;
}

int searchToEncrypt(vector<char> alphabet, char elemento){
    for(int i=0; i<alphabet.size(); i++){
        if(alphabet[i] == elemento)
            return i;
    }
    return -1;
}

// Faz a cifra e a quebra de cifra do texto.

void encryptAndDecrypt(vector<char> alphabet, vector<char> alphabetSimbols, vector<int> newAlphabet, vector<int> newAlphabetSimbols, string text){
    string encrypted;

    for(int i=0; i<text.length(); i++){
        if(text[i] == ' '){
            encrypted.push_back(' ');
            continue;
        }

        if(searchToEncrypt(alphabetSimbols, text[i]) != -1){
            int position = searchToEncrypt(alphabetSimbols, text[i]);
            encrypted.push_back(alphabetSimbols[newAlphabetSimbols[position]]);
            continue;
        }
        
        int position = searchToEncrypt(alphabet, text[i]);
        encrypted.push_back(alphabet[newAlphabet[position]]);
    }
    cout << "Texto cifrado: " << encrypted << endl;

    string decrypted;
    for(int i=0; i<encrypted.length(); i++){
        if(encrypted[i] == ' '){
            decrypted.push_back(' ');
            continue;
        }
        
        if(searchToEncrypt(alphabetSimbols, encrypted[i]) != -1){
            int position = searchToEncrypt(alphabetSimbols, encrypted[i]);
            int pos2 = contains(newAlphabetSimbols, position);
            decrypted.push_back(alphabetSimbols[pos2]);
            continue;
        }

        int position = searchToEncrypt(alphabet, encrypted[i]);
        int pos2 = contains(newAlphabet, position);
        decrypted.push_back(alphabet[pos2]);
    }

    cout << endl << "Texto decifrado: " << decrypted << endl;
}

// Mostra a tradução do novo alfabeto gerado.

void translatedAlphabets(vector<char> alphabet, vector<char> alphabetSimbols, vector<int> newAlphabet, vector<int> newAlphabetSimbols){
    cout << endl << "Tradução de letras: " << endl;
    for (int i = 0; i < alphabet.size(); i++)
        cout << alphabet[i] << "  ----->  " << alphabet[newAlphabet[i]] << endl;
    
    cout << "Tradução de símbolos: " << endl;
    for(int i=0; i < alphabetSimbols.size(); i++)
        cout << alphabetSimbols[i] << "  ----->  " << alphabetSimbols[newAlphabetSimbols[i]] << endl;

}