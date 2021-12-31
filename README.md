# Spell checker using Trie Structures

This project uses the trie structure as a means of identifying words found in a given corpus.

This program can help a user know if a certain word exists in a given text file. If it doesn't, it will provide a list of words with a similar spelling.
With enough data (a big enough text file) this program can be used as a true spell checker** as any words not found in a exhaustive list are seen as non-existent.

The user can upload a text file of their choosing and then change the file path input for the `convertFileToString` function found in the main.cpp file. This will determine the corpus that all input words will be measured against.
Alternatively, the user can simply modify the given text file found in the build folder (labelled "the_words.txt)

After the right file path is set to the correct text file, the user enter an input word for the second parameter of the `word_suggestion` function.

After these measures are taken, the user can then navigate with the terminal to the build folder. From there, the code can be compiled using Ctrl + Shift + b

To run the program enter `./main` and see the printed results from the input word and the chosen text.

All tests can be run as well by entering `./run_tests` in the same folder



**for this project only lower case words can be accepted
