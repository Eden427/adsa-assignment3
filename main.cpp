/*
 * @Author: Zichu Zhao 965927155@qq.com
 * @Date: 2025-10-14 14:55:49
 * @LastEditors: Zichu Zhao 965927155@qq.com
 * @LastEditTime: 2025-10-15 13:14:24
 * @FilePath: /Assignment-3/main.cpp
 * @Description: Hash table linear probing implementation for assignment.
 *               26 slots a-z, keys are lowercase words, hash = last char.
 *               With simple debug traces toggle by DEBUG macro.
 * 
 * 
 */

 # include <iostream>
 # include <string>
 # include <sstream>
 using namespace std;

 # define MAX_SLOTS 26 // just 26 slots for a-z
 
//  store words here
string words[MAX_SLOTS];

// 0 = never used
// 1 = deleted
// 2 = used
int status[MAX_SLOTS];

// get hash index by using last letter
int getHashIndex(string w){
    if(w.empty()) return 0; //just in case
    char last = w[w.length()-1];
    return last - 'a'; // covent 'a' to 0, 'b' to 1, ..., 'z' to 25
}

// find a word, if found return its pos, else -1
int findWord(string target){
    int start = getHashIndex(target);
    for(int i = 0; i < MAX_SLOTS; i++){
        int pos = (start + i) % MAX_SLOTS;
        if (status[pos] == 0){
            // if never used, stop searching
            return -1;
        }
        if(status[pos] == 2 && words[pos] == target){
            // found it
            // cout<<"[debug] found" << target << " at " << pos << endl;
            return pos;

        }
    }
    // not found
    return -1;
}

// add a new word
void addWord(string w){
    // skip if it already exists
    if(findWord(w) != -1) return;
    
    int start = getHashIndex(w);
    for (int i = 0; i< MAX_SLOTS; i++){
        int pos = (start + i) % MAX_SLOTS;

        //ok, found empty or deleted 
        if(status[pos] == 0 || status[pos] == 1){
            words[pos] = w;
            status[pos] = 2; // mark as used
            // cout<<"[debug] insert " << w << " at " << pos << endl;
            return;
        }
    }
    // table full(shouldn't happen cuz max 26 words)
}

// delete word (just tombstone it)
void deleteWord(string w){
    int pos = findWord(w);
    if (pos == -1){
        // cout<<"[debug] cannot find " << w << " to delete" << endl;
        return; // not found
    }
    status[pos] = 0; //tombstone
    words[pos] = "";
    // cout<<"[debug] deleted " << w << " at " << pos << endl;
}

int main(){
    // init status
    for (int i =0; i < MAX_SLOTS; i++){
        status[i] = 0;
        words[i] = "";
    }
    
    string line;
    getline(cin, line); //read a full line like "Aaaa Accc Abbb"
    if (line.empty()){
        cout<<endl;
        return 0; // nothing to do
    }

    stringstream ss(line);
    string token;

    while (ss >> token){
        char op = token[0]; // first letter
        string w = token.substr(1); // real word
        if (op == 'A'){
            addWord(w);   
        } else if (op == 'D'){
            deleteWord(w);
        }
        // cout <<"[debug] cmd done:" <<token <<endl;

    }
    // print remaining words
    bool first = true;
    for (int i = 0; i< MAX_SLOTS; i++){
        if (status[i] == 2){ // used
            if (!first) cout<<" ";
            cout<<words[i];
            first = false;
        }
    }
    cout<<endl;
    return 0;
}