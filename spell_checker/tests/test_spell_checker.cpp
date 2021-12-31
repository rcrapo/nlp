// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/spell_checker.h"

#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <ctime>
#include <cmath>

using namespace std;

class test_Trie : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
	}
    
	// this function runs before every TEST_F function
	void SetUp() override {
    }

	// this function runs after every TEST_F function
	void TearDown() override {
	}
};

//create a tree manually for testing purposes
shared_ptr<trie_node> makeTrie() {
  Trie spell_trie;

  //manually create trie structure
  // with the words "gif" "gift", "gifts", "git", "give", "giving"

  //create a root "dummy" node with blak char value 
  shared_ptr<trie_node> root = spell_trie.InitNode(' ', false, false);

  shared_ptr<trie_node> NodeG = spell_trie.InitNode('g', false, false);
  shared_ptr<trie_node> NodeI = spell_trie.InitNode('i', false, false);
  shared_ptr<trie_node> NodeF = spell_trie.InitNode('f', true, false);
  shared_ptr<trie_node> NodeT = spell_trie.InitNode('t', true, false);
  shared_ptr<trie_node> NodeS = spell_trie.InitNode('s', true, true);

  shared_ptr<trie_node> NodeT2 = spell_trie.InitNode('t', true, true);

  shared_ptr<trie_node> NodeV = spell_trie.InitNode('v', false, false);
  shared_ptr<trie_node> NodeE = spell_trie.InitNode('e', true, true);

  shared_ptr<trie_node> NodeI2 = spell_trie.InitNode('i', false, false);
  shared_ptr<trie_node> NodeN = spell_trie.InitNode('n', false, false);
  shared_ptr<trie_node> NodeG2 = spell_trie.InitNode('g', true, true);

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
  NodeI->next_let->at(21) = NodeV;
  NodeV->next_let->at(4) = NodeE;

  //giving
  NodeV->next_let->at(8) = NodeI2;
  NodeI2->next_let->at(13) = NodeN;
  NodeN->next_let->at(6) = NodeG2;

  return root;
}

TEST_F(test_Trie, convertTextTest){
    Trie spell_trie;

    string the_words = spell_trie.convertFileToString("/home/jovyan/data_structures/Final_Project_Trie/build/the_words.txt");

    string comparison_string = "these pretzels are the best i think i should eat some more";

    ASSERT_EQ(the_words, comparison_string);
/*
    int vector_size = comparison_vector.size(); 

    for(int i = 0; i < vector_size; i++){
        ASSERT_EQ(the_words[i], comparison_vector[i]);
    }    
*/
}



TEST_F(test_Trie, splitTest){
    Trie spell_trie;
    
    string sentence = "this is the first time";

    vector<string> words = spell_trie.split(sentence, " ");

    vector<string> comparison_vector{"this", "is", "the", "first", "time"};

    //checking to see if the "words" vector and the "comparison" vector have the same amount of words
    ASSERT_EQ(words.size(), comparison_vector.size());

    int vector_size = comparison_vector.size(); 

    //making sure that each respective value in both vectors are equivalent
    sort(comparison_vector.begin() , comparison_vector.end());

    sort(words.begin() , words.end());

    for(int i = 0; i < vector_size; i++){
        ASSERT_EQ(words[i], comparison_vector[i]);
    }

    //if an input string contains anything but lower case letters the function
    //will output a vector with only the word "nope"
    string bad_sentence = "i can't believe it's yogurt";

    vector<string> bad_output = spell_trie.split(bad_sentence, " ");

    ASSERT_EQ("nope", bad_output[0]);

}


TEST_F(test_Trie, InitNodeTest){
    Trie spell_trie;
    shared_ptr<trie_node> n_trie = spell_trie.InitNode('r', true, true);

    ASSERT_TRUE(n_trie);

    ASSERT_EQ(n_trie->letter, 'r');

    ASSERT_TRUE(n_trie->is_word);

    ASSERT_TRUE(n_trie->is_leaf);

    //neeed to resize this vector to represent the whole alphabet
    //this is how the cursor will find the path of real and non real words
    ASSERT_TRUE(n_trie->next_let->size() == 26);

}

TEST_F(test_Trie, appendTest){
    Trie spell_trie;
    shared_ptr<trie_node> root = spell_trie.InitNode(' ', false, false);

    bool append_result = spell_trie.append_word(root, "track");

    ASSERT_TRUE(append_result);

    //checking to see that the character and node was inserted in the right slot of the vector
    ASSERT_EQ('t', root->next_let->at(19)->letter);

    ASSERT_EQ('r', root->next_let->at(19)->next_let->at(17)->letter);

    ASSERT_EQ('a', root->next_let->at(19)->next_let->at(17)->next_let->at(0)->letter);

    ASSERT_EQ('c', root->next_let->at(19)->next_let->at(17)->next_let->at(0)->next_let->at(2)->letter);

    ASSERT_EQ('k', root->next_let->at(19)->next_let->at(17)->next_let->at(0)->next_let->at(2)->next_let->at(10)->letter);

    ASSERT_TRUE(root->next_let->at(19)->next_let->at(17)->next_let->at(0)->next_let->at(2)->next_let->at(10)->is_word);

    ASSERT_TRUE(root->next_let->at(19)->next_let->at(17)->next_let->at(0)->next_let->at(2)->next_let->at(10)->is_leaf);

    //the second time adding the same word should not be successful out of redundancy
    bool append_result_2 = spell_trie.append_word(root, "track");

    ASSERT_FALSE(append_result_2);

    bool append_result_3 = spell_trie.append_word(root, "tracks");

    ASSERT_TRUE(append_result_3);

    ASSERT_EQ('s', root->next_let->at(19)->next_let->at(17)->next_let->at(0)->next_let->at(2)->next_let->at(10)->next_let->at(18)->letter);

    ASSERT_TRUE(root->next_let->at(19)->next_let->at(17)->next_let->at(0)->next_let->at(2)->next_let->at(10)->next_let->at(18)->is_word);

    ASSERT_TRUE(root->next_let->at(19)->next_let->at(17)->next_let->at(0)->next_let->at(2)->next_let->at(10)->next_let->at(18)->is_leaf);

    //once a new word is appended to the end of the old word, the old word's end no longer has "is_leaf" status
    ASSERT_FALSE(root->next_let->at(19)->next_let->at(17)->next_let->at(0)->next_let->at(2)->next_let->at(10)->is_leaf);
}


TEST_F(test_Trie, buildTrieTest){
    Trie spell_trie;
    
    vector<string> word_list{"gif", "gift", "gifts", "give", "giving", "git"};

    shared_ptr<trie_node> root = spell_trie.build_trie(word_list);

    ASSERT_TRUE(root);

    //checking to see that the last letter of each word has the proper node in the right place
    //and that the node is marked true for "is_word"
    ASSERT_TRUE(root->next_let->at(6)->next_let->at(8)->next_let->at(5)->is_word);

    ASSERT_TRUE(root->next_let->at(6)->next_let->at(8)->next_let->at(5)->next_let->at(19)->is_word);

    ASSERT_TRUE(root->next_let->at(6)->next_let->at(8)->next_let->at(5)->next_let->at(19)->next_let->at(18)->is_word);

    ASSERT_TRUE(root->next_let->at(6)->next_let->at(8)->next_let->at(21)->next_let->at(4)->is_word);

    ASSERT_TRUE(root->next_let->at(6)->next_let->at(8)->next_let->at(21)->next_let->at(8)->next_let->at(13)->next_let->at(6)->is_word);

    ASSERT_TRUE(root->next_let->at(6)->next_let->at(8)->next_let->at(19)->is_word);


}



TEST_F(test_Trie, deleteTest){
    Trie spell_trie;
    
    vector<string> word_list{"gif", "gift", "gifts", "give", "giving", "git"};

    shared_ptr<trie_node> root = spell_trie.build_trie(word_list);

    bool delete_result = spell_trie.delete_word(root, "give");

    ASSERT_TRUE(delete_result);
    
    int count_result = spell_trie.count_words(root);

    ASSERT_EQ(count_result, 5);

    vector<string> prefix_results;

    string t_word;

    //making sure that only one word is left given a certain prefix
    spell_trie.prefix_search(root, "giv", prefix_results, t_word);

    ASSERT_EQ(prefix_results[0], "giving");

    //show that you can't delete  an already deleted word from the structure
    bool delete_result_2 = spell_trie.delete_word(root, "give");

    ASSERT_FALSE(delete_result_2);

    //can't delete a word that was never in the trie structure
    bool delete_result_3 = spell_trie.delete_word(root, "grand");

    ASSERT_FALSE(delete_result_3);

}



TEST_F(test_Trie, countTest){
    Trie spell_trie;

    shared_ptr<trie_node> trie_structure = makeTrie();

    int num_words = spell_trie.count_words(trie_structure);

    ASSERT_EQ(num_words, 6);

    bool delete_result = spell_trie.delete_word(trie_structure, "give");

    ASSERT_TRUE(delete_result);

    num_words = spell_trie.count_words(trie_structure);

    ASSERT_EQ(num_words, 5);

    spell_trie.reset(trie_structure);

    num_words = spell_trie.count_words(trie_structure);

    ASSERT_EQ(num_words, 0);

}

TEST_F(test_Trie, wordSearchTest){
    Trie spell_trie;

    shared_ptr<trie_node> trie_structure = makeTrie();

    vector<string> trie_outputs;

    string t_word = "";

    spell_trie.word_search(trie_structure, trie_outputs, t_word);

    //chcking to see if the function found all six words in the trie
    int word_count = trie_outputs.size();

    ASSERT_EQ(word_count, 6);

    vector<string> sorted_trie_words;

    sort(trie_outputs.begin() , trie_outputs.end());

    for(auto x : trie_outputs){
        sorted_trie_words.push_back(x);
    }

    //making sure that the fetched words in the trie respectively match the words in the 
    //word list vector
    vector<string> word_list{"gif", "gift", "gifts", "git", "give", "giving"};

    for(int i = 0; i < word_count; i++){
        ASSERT_EQ(sorted_trie_words[i], word_list[i]);
    }
}

TEST_F(test_Trie, prefixTest){
    Trie spell_trie;
 
    shared_ptr<trie_node> trie_structure = makeTrie();

    vector<string> prefix_outputs;

    string t_word = "";
    
    //checking to see if the function got all words with the given prefix
    spell_trie.prefix_search(trie_structure, "gif", prefix_outputs, t_word);

    ASSERT_EQ(prefix_outputs.size(), 3);

    ASSERT_EQ(prefix_outputs[0], "gif");

    ASSERT_EQ(prefix_outputs[1], "gift");

    ASSERT_EQ(prefix_outputs[2], "gifts");

    vector<string> prefix_outputs2;

    string t_word2 = "";

    spell_trie.prefix_search(trie_structure, "bro", prefix_outputs2, t_word2);

    //checking to see that wholly invalid prefixes return no results
    ASSERT_EQ(prefix_outputs2.size(), 0);

    vector<string> prefix_outputs3;

    string t_word3 = "";

    spell_trie.prefix_search(trie_structure, "gro", prefix_outputs3, t_word3);

    //checking to see that even subsections of a prefix can be used to find words in the trie
    //in this case the smallest valid linguistic unit is "g" 
    ASSERT_EQ(prefix_outputs3.size(), 6);

    ASSERT_EQ(prefix_outputs3[0], "gif");

    ASSERT_EQ(prefix_outputs3[1], "gift");

    ASSERT_EQ(prefix_outputs3[2], "gifts");

    ASSERT_EQ(prefix_outputs3[3], "git");

    ASSERT_EQ(prefix_outputs3[4], "give");

    ASSERT_EQ(prefix_outputs3[5], "giving");

}

TEST_F(test_Trie, suggestionTest){
    Trie spell_trie;
    
    //shared_ptr<trie_node> trie_structure = makeTrie();

    vector<string> word_list{"great", "grand", "gram", "graham" "good", "break", "broke", "brook", "booking"};

    shared_ptr<trie_node> trie_structure = spell_trie.build_trie(word_list);

    vector<string> suggestions;

    string t_word = "";

    spell_trie.word_suggestion(trie_structure, "bruk", suggestions, t_word);

    vector<string> sorted_suggestions;

    sort(suggestions.begin() , suggestions.end());

    for(auto x : suggestions){
        sorted_suggestions.push_back(x);
    }

    //the output vector will be all words that share the largest viable portion/prefix of the given word
    //and return a word that is with one charcter in length of the given word
    ASSERT_EQ(suggestions.size(), 3);

    ASSERT_EQ(suggestions[0], "break");

    ASSERT_EQ(suggestions[1], "broke");

    ASSERT_EQ(suggestions[2], "brook");


    vector<string> no_suggestions;

    string t_word2 = "";

    spell_trie.word_suggestion(trie_structure, "brook", no_suggestions, t_word2);

    //if the word already exists in the trie structure there is no need to offer suggestions,
    //thus the output variable contains no words
    ASSERT_EQ(no_suggestions.size(), 0);

}



TEST_F(test_Trie, resetTest){
    Trie spell_trie;
    
    shared_ptr<trie_node> root = makeTrie();

    ASSERT_TRUE(root);

    spell_trie.reset(root);

    ASSERT_TRUE(root);

    ASSERT_FALSE(root->next_let->at(6)->next_let->at(8)->next_let->at(5)->is_word);

    ASSERT_FALSE(root->next_let->at(6)->next_let->at(8)->next_let->at(5)->next_let->at(19)->is_word);

    ASSERT_FALSE(root->next_let->at(6)->next_let->at(8)->next_let->at(5)->next_let->at(19)->next_let->at(18)->is_word);

    ASSERT_FALSE(root->next_let->at(6)->next_let->at(8)->next_let->at(21)->next_let->at(4)->is_word);

    ASSERT_FALSE(root->next_let->at(6)->next_let->at(8)->next_let->at(21)->next_let->at(8)->next_let->at(13)->next_let->at(6)->is_word);

    ASSERT_FALSE(root->next_let->at(6)->next_let->at(8)->next_let->at(19)->is_word);
}


