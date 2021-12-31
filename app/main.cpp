#include <iostream>
#include "../code/spell_checker.h"

using namespace std;



int main() {

Trie spell_trie;

//setting up the corpus by building out a trie structure

string the_words = spell_trie.convertFileToString("/home/jovyan/data_structures/Final_Project_Trie/build/the_words.txt");

vector<string> words =  spell_trie.split(the_words, " ");

shared_ptr<trie_node> root = spell_trie.build_trie(words);

//creating the output variables that will be used for the word checker

string t_word = "";

vector<string> suggestions;

//this function will print out word suggestions if the input word is not found
//in the corpus. If the word is found, no suggestions will be given 

spell_trie.word_suggestion(root, "pretzels", suggestions, t_word);


    return 0;
}