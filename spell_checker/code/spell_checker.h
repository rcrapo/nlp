#ifndef SPELL_CHECKER_H__
#define SPELL_CHECKER_H__

#include <string>
#include <memory>
#include <queue>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>


using namespace std;


struct trie_node {

char letter;
bool is_word;
bool is_leaf;
shared_ptr<vector<shared_ptr<trie_node>>> next_let; //when a new letter shows up, I can insert the letter and trie node. When searching to see if a word is in the trie, the present letters in the map will show the way to navigation.

};




class Trie{
public:
  Trie();


  ~Trie();

  /*
  This function genrates a trie structure with hard coded values
  */
  shared_ptr<trie_node> makeTrie();



  //this function reads in a file and outputs a string
  //*this function was pulled from stack overflow
  string convertFileToString(const string& path);

  /*
  This function takes in a string and splits it on a delimiter of my choice. 
  For the purposes of the project the delimiter will be a single space. 
  The function then inserts the wordsinto a set in order to get rid of any deuplicates values.
  Finally the function inserst teh words back into a vector to be returned as a function output.
  */
  vector<string> split(string s, string delimiter);


  /*
  This function allocates memory for a trie_node (defined above) and then assigns the respective attributes
  according to the input values passed in as parameters
  */
  shared_ptr<trie_node> InitNode(char letter, bool is_word, bool is_leaf);

  /*
  This function adds a new word to the trie structure. 
  If the addition is unsuccessful (because of redundancy), the function returns false.
  If the structure is already in place, the added characters will fill the deleted nodes
  */
  bool append_word(shared_ptr<trie_node> root, string new_word);

  /*
  This function will take in a vector os strings and then recursively build out a trie structure with the appropriate 
  markings/values for theach attribute of each trie node.

  */
  shared_ptr<trie_node> build_trie(vector<string> word_set);


  /*
  This function will count the number of words in a trie structure. 
  This is mostly to test other functions and build a starting point for the more complex functions
  */
  int count_words(shared_ptr<trie_node> root);


  /*
  This function takes in a root node, navigates the entire tree and then
  fills an output variable vector with all of the words that were found
  */
  void word_search(shared_ptr<trie_node> root, vector<string>& word_outputs, string& t_word);


  /*
  This function will return all the words in the trie that contain the inputted prefix. 
  If there are no words in the trie that match with the given prefix, 
  the the "prefix_results" vector will be empty.
  If any part of the prefix is valid, that valid subsection will beused to search for relevant words in
  the trie.
  */
  void prefix_search(shared_ptr<trie_node> root, string prefix, vector<string>& prefix_results, string& t_word);


  /*
  This function will delete the entered word from the trie structure. 
  A false returned value measn that the word was already deleted or 
  that the word never existed in the structure
  */
  bool delete_word(shared_ptr<trie_node> root, string word);


  /*
  This function will take in an input word and output a vector and corresponding preint satement depending on what it finds.
  if the input word is mispelled or does not exist in the trie (this is dependant on the corpus that was used to create the trie in the first place)
  the function will fill the suggestions variable with similar words - by similar words the criteris is as follows
  -> the similar words share at least in part the same prefix as the inputted word and the length of the words are within one
  character's length of the inputted word.

  If the inputted word already exists in the trie, the suggestions vector is not filled with words and 
  and printout will let the user know that there are no suggestions.
  */
  void word_suggestion(shared_ptr<trie_node> root, string input_word, vector<string>& suggestions, string& t_word);

  /*
  This reset all values in the trie structure without removing the nodes. 
  This will make room for adding new values without having to recreate 
  the trie structure from scratch
  */
  void reset(shared_ptr<trie_node> root);

    
private:

  //a global map that will help the cursor to find the right slots for each charcter in each word
  map<char, int> alpha_index;

};

#endif // EMPTY_H__