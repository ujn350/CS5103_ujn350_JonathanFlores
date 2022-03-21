#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "word.h"

using namespace std;

bool InHistory(string& currentWord, vector<Word>& word_history)
{
    if(word_history.empty())
    {
        return false;
    }
    for(int i = 0; i < word_history.size(); i++)
    {
        if(currentWord == word_history[i].get_wordname())
        {
            return true;
        }
    }
    return false;
}

void add_word_to_history(string::iterator& head, string::iterator& tail, vector<Word>& word_history)
{
    string currentWord;
    for(auto it = head; it != tail; it++)
    {
        currentWord.push_back(*it);
    }
    if(!currentWord.empty())
    {
        if(!InHistory(currentWord, word_history))
        {
            word_history.push_back(Word(currentWord));
        }
        else
        {
            for(int i = 0; i < word_history.size(); i++)
            {
                if(currentWord == word_history[i].get_wordname())
                {
                    word_history[i].increment();
                    break;
                }
            }
        }
    }
}

//Function that tests if current pointed to character is a separator character
bool IsSeparator(char testchar)
{
    vector<char> separators = {' ', '\t', '\n'};
    for(int i = 0; i < separators.size(); i++)
    {
        if(testchar == separators[i])
        {
            return true;
        }
    }
    return false;
}

void display_word_frequency(string &text)
{
    vector<Word> word_history;

    string::iterator head = text.begin();
    string::iterator tail = head;
    string::iterator const end = text.end();



    while(head != end && tail != end)
    {
        if(!IsSeparator(*tail))
        {
            tail++;
            if(tail == end)
            {
                add_word_to_history(head, tail, word_history);
            }
        }
        else
        {
            add_word_to_history(head, tail, word_history);
            tail++;
            head = tail;

        }
    }
    for(int i = 0; i < word_history.size(); i++)
    {
        cout << "-----------------------------------------------------------" << endl;
        cout << "word: " << "\"" << word_history[i].get_wordname() << "\"" << endl;
        cout << "freq: " << word_history[i].get_instances() << endl;
    }
    cout << "-----------------------------------------------------------" << endl << endl;

}

int main(){
    cout << endl << "############################# STRINGS AND WORDS #############################" << endl << endl;
    cout << "reading text file contents..." << endl;

    //grabs text from stream and creates string of full text
    ifstream input("input_text.txt", ifstream::in);
    stringstream inputStream;
    inputStream << input.rdbuf();
    string text = inputStream.str();

    display_word_frequency(text);

    return 0;
}
