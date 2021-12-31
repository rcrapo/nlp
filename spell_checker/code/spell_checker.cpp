#include "spell_checker.h"
#include <fstream> //this is for reading text files
#include <iostream>
#include <string>
#include <math.h>
#include <ctime>
#include <cmath>

//string t_word = "";

Trie::Trie(){
    alpha_index = {{'a',0}, {'b',1}, {'c',2}, {'d',3}, {'e',4}, {'f',5}, 
                   {'g',6}, {'h',7}, {'i',8}, {'j',9}, {'k',10}, {'l',11}, 
                   {'m',12}, {'n',13}, {'o',14}, {'p',15}, {'q',16}, {'r',17},
                   {'s',18}, {'t',19}, {'u',20}, {'v',21}, {'w',22}, {'x',23}, {'y',24}, {'z',25}};  


 
    //word_set.resize(26);

   // word_sum = 0;
}

Trie::~Trie(){
    
}

shared_ptr<trie_node> Trie::makeTrie() {

  //manually create trie structure
  // with the words "gift", "gifts", "git", "give", "giving"

  //create a root "dummy" node with blak char value 
  shared_ptr<trie_node> root = InitNode(' ', false, false);

  shared_ptr<trie_node> NodeG = InitNode('g', false, false);
  shared_ptr<trie_node> NodeI = InitNode('i', false, false);
  shared_ptr<trie_node> NodeF = InitNode('f', false, false);
  shared_ptr<trie_node> NodeT = InitNode('t', true, false);
  shared_ptr<trie_node> NodeS = InitNode('s', true, true);

  shared_ptr<trie_node> NodeT2 = InitNode('t', true, false);

  shared_ptr<trie_node> NodeV = InitNode('v', false, false);
  shared_ptr<trie_node> NodeE = InitNode('e', true, true);

  shared_ptr<trie_node> NodeI2 = InitNode('i', false, false);
  shared_ptr<trie_node> NodeN = InitNode('n', false, false);
  shared_ptr<trie_node> NodeG2 = InitNode('g', true, true);

  //make the trie manually
  //gift, gifs

  root->next_let->at(6) = NodeG;
  NodeG->next_let->at(8) = NodeI;
  NodeI->next_let->at(5) = NodeF;
  NodeF->next_let->at(19) = NodeT;
  NodeT->next_let->at(18) = NodeS;

  //git
  NodeI->next_let->at(19) = NodeT2;

  //give
  NodeI->next_let->at(19) = NodeV;
  NodeV->next_let->at(4) = NodeE;

  //giving
  NodeV->next_let->at(8) = NodeI2;
  NodeI2->next_let->at(13) = NodeN;
  NodeN->next_let->at(6) = NodeG2;

  return root;
}

//the code for this function was mostly taken from stackoverflow

string Trie::convertFileToString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
}



//this function was created from a few pieces of code that I found on stack overflow
//and cplusplus.com

vector<string> Trie::split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    int string_length = s.length();

    for(int i = 0; i < string_length; i++){
        if(s[i] < 97 || s[i] > 122){
            if(s[i] == 32){
                continue;
            }
            else{
                res = {"nope"};
                cout << "Error: cannot convert string. String must contain only lower case letters" << endl;
                return res;
            }
        }
    }

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));

    //create a set and transfer the words from the vector to delete duplicates
    set<string> res_2 = {}; 

    for(int i = 0; i < res.size(); i++){
        res_2.insert(res[i]);
    }

    //transer the words in the set to a vector to have better control
    vector<string> res_3;

    for (set<string>::iterator it = res_2.begin(); it!=res_2.end(); ++it){
        res_3.push_back(*it);
    }

    return res_3;
}


shared_ptr<trie_node> Trie::InitNode(char letter, bool is_word, bool is_leaf){
    shared_ptr<trie_node> n_node(new trie_node);

    n_node->letter = letter;
    n_node->is_word = is_word;
    n_node->is_leaf = is_leaf;
    n_node->next_let = shared_ptr<vector<shared_ptr<trie_node>>>(new vector<shared_ptr<trie_node>>);
    n_node->next_let->resize(26); //make sure this is right

    return n_node;
}

bool Trie::append_word(shared_ptr<trie_node> root, string new_word){

    int word_size = new_word.length();

    shared_ptr<trie_node> curr = root;

    for(int i = 0; i < word_size; i++){

        char curr_letter = new_word[i];

        //if the slot for the next character is null, then a new node must be created and placed in the 
        //vector, making the newly placed node the newest leaf node
        if(!curr->next_let->at(alpha_index[curr_letter])){
            shared_ptr<trie_node> new_char = InitNode(curr_letter, false, true);

            //before inserting a new node, the leaf status must be set to false
            curr->is_leaf = false;

            curr->next_let->at(alpha_index[curr_letter]) = new_char;

            //move the pointer along to the new node
            curr = new_char;
        }
        else{
            if(curr->next_let->at(alpha_index[curr_letter])->letter != curr_letter){
                curr->next_let->at(alpha_index[curr_letter])->letter = curr_letter;

            }
            //move the pointer along to the next node
            curr = curr->next_let->at(alpha_index[curr_letter]);
        }


        //if the word already exists in the trie and is marked as a word, then
        //the function returns false because the word was not added because of redundancy
        if(i == word_size-1){
            if(curr->is_word == true){
                return false;
            }
            else{
                curr->is_word = true;
            }


        }
    }
    
       return true;

}
    



shared_ptr<trie_node> Trie::build_trie(vector<string> word_set){
    
    shared_ptr<trie_node> root = InitNode(' ', false, true);

    int word_set_size = word_set.size();

    for(int i = 0; i < word_set_size; i++){
        append_word(root,word_set[i]);
    }
    
    return root;
}



int Trie::count_words(shared_ptr<trie_node> root){


    int word_sum = 0;

    //add to the local count of the words if is_word is true

    if(root->is_word){ 
        word_sum += 1;
    }

    //if the function reaches a leaf then it will stop this iteration of the function
    //and add the local sum to the overall sum that was created in the fist iteration
    if(root->is_leaf){
        return word_sum;
    }
    else{
        for(int i = 0; i <26; i++){
            if(root->next_let->at(i)){
                word_sum += count_words(root->next_let->at(i));

            }
        }
    }
    return word_sum;
}



void Trie::word_search(shared_ptr<trie_node> root, vector<string>& word_outputs, string& t_word){

    t_word += root->letter;

    if(root->is_word){
        word_outputs.push_back(t_word);
    }

    if(root->is_leaf){
        return;
    }

    for(int i = 0; i <26; i++){
        if(root->next_let->at(i)){
            word_search(root->next_let->at(i), word_outputs, t_word);
            t_word.pop_back();
        }
    }

    for(int j = 0; j <word_outputs.size(); j++){
        if(word_outputs[j][0] == ' '){
            word_outputs[j].erase(0,1);
        }

    }


}

/*
void Trie::prefix_search(shared_ptr<trie_node> root, string prefix, vector<string>& prefix_results){
   //THIS VERSION WILL ONLY ACCCEPT THE PREFIX IN IT'S ENTIRETY

    shared_ptr<trie_node> curr(root);

    //in case even the first character doesn't work as a viable prefix
    if(!curr->next_let->at(alpha_index[prefix[0]])){
        return;
    }


    for(int i = 0; i < prefix.length(); i++){
        if(curr->next_let->at(alpha_index[prefix[i]])){
            curr = curr->next_let->at(alpha_index[prefix[i]]);
        }
        // if at any point the entire prefix isn't found in the structure
        //the function throw an error and exit with no results.
        else{

            cout << "Error: prefix not found in trie structure" << endl;
            return;

        }
    }

    cout << curr->letter << endl;;

    word_search(curr, prefix_results);

    //need to modify the prifix to fit it to the recursive results from the 
    //word_search function
    prefix.pop_back();


    //cout << prefix << endl;

    for(int j = 0; j < prefix_results.size(); j++){
        //prefix_results[j] = prefix + prefix_results[j];
        cout << prefix_results[j] << endl;
    }


}
*/


void Trie::prefix_search(shared_ptr<trie_node> root, string prefix, vector<string>& prefix_results, string& t_word){
    
    //THIS VERSION WILL SEARCH FOR A TRUNCATED VERSION OF THE GIVEN PREFIX

    shared_ptr<trie_node> curr(root);

    //in case even the first character doesn't work as a viable prefix
    if(!curr->next_let->at(alpha_index[prefix[0]])){
        return;
    }

    int loop_counter = 0;

    for(int i = 0; i < prefix.length(); i++){
        if(curr->next_let->at(alpha_index[prefix[i]])){
            curr = curr->next_let->at(alpha_index[prefix[i]]);
            loop_counter++;
        }
        // if at any point the prefix isn't fully found in the trie structure
        // the function needs to stop looping and then continue from the characters/truncated prefix
        // and then look for the other words
        else{

            break;


        }
    }


    word_search(curr, prefix_results, t_word);

    //these values determine how much of the prefix needs to be deleted to successfully 
    //be appended to the remaining suffixes of each word
    int surviving_chars = prefix.length() - (prefix.length() - loop_counter) - 1;
    int num_deletions = prefix.length() - surviving_chars;


    for(int p = 0; p < num_deletions; p++){
        prefix.pop_back();
    }


    for(int j = 0; j < prefix_results.size(); j++){
        prefix_results[j] = prefix + prefix_results[j];
    }


}



bool Trie::delete_word(shared_ptr<trie_node> root, string word){
    
    int word_length = word.length();

    //create a pointer to update to each node until it gets to the end of the word
    shared_ptr<trie_node> curr = root;

    for(int i = 0; i < word_length; i++){
        if(curr->next_let->at(alpha_index[word[i]])){
            curr = curr->next_let->at(alpha_index[word[i]]);
        }
        //if at any point the pointer hits a null node, the word
        //is for sure not in the trie structure
        else{
            return false;
        }

    }

    //if the pointer successfully gets to 
    //the end of the word without hitting a null node,
    //but the word was previously deleted
    //then the return the function returns a false value
    if(curr->is_word == false){
        return false;
    }
    else{
        curr->is_word = false;

        return true;
    }
    
}

void Trie::word_suggestion(shared_ptr<trie_node> root, string input_word, vector<string>& suggestions, string& t_word){

    //Need to set a clear criteria for this function
    //and be able to explain this in the interview

    prefix_search(root, input_word, suggestions, t_word);

    int input_length = input_word.length();

    int low_range = input_length -1;

    int high_range = input_length +1;

    int num_suggestions = suggestions.size();

    for(int i = 0; i < num_suggestions; i++){
        if(suggestions[i].length() < low_range || suggestions[i].length() > high_range){
            suggestions.erase(suggestions.begin() + i); 
        }
    }



    

    for(int j = 0; j < num_suggestions; j++){

        if(input_word == suggestions[j]){
            cout << "Correct, no suggestions" << endl;
            suggestions.clear();
            return;
        }

    }

        cout << "\"" << input_word << "\"" << " not found\nWord Suggestions: " << endl;
        
        for(int j = 0; j < num_suggestions; j++){

            cout << suggestions[j] << endl;
        }

}




void Trie::reset(shared_ptr<trie_node> root){

    if(root->is_leaf){
        root->is_leaf = false;
        root->is_word = false;
        return;
    }
    else{
    for(int i = 0; i< 26; i++){
        if(root->next_let->at(i)){
            root->next_let->at(i)->is_word = false;
            reset(root->next_let->at(i));
        }
    }
    }
}

/*
vector<set<string>> Trie::build_lookup(vector<string> words){
    set<string> word_list;
}
*/