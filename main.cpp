#include <iostream>
#include <string>
#include <vector>
#include <iterator>
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
    cout << "------------------------- WORD FREQUENCIES -------------------------" << endl;
    for(int i = 0; i < word_history.size(); i++)
    {
        cout << "\"" << word_history[i].get_wordname() << "\": " << word_history[i].get_instances() << endl;
    }
    cout << "--------------------------------------------------------------------" << endl << endl;

}

bool replace(string &text)
{
    string targetword;
    string replaceword;

    cout << "------------------------- WORD REPLACEMENT -------------------------" << endl;
    cout << "Please enter the target word to replace: " << endl;
    cin >> targetword;
    cout << "Enter what to replace target word with: " << endl;
    cin >> replaceword;

    string::iterator head = text.begin();
    string::iterator tail = head;
    string::iterator const end = text.end();

    string testword;

    while(head != end && tail != end)
    {
        if(!IsSeparator(*tail))
        {
            tail++;
        }
        else if(distance(head, tail - 1) == targetword.length())
        {
            testword.clear();
            for(int i = 0; i < targetword.length(); i++)
            {
                testword.push_back(*(head + i));
            }
            if(testword == targetword)
            {
                if(replaceword.length() == targetword.length())
                {

                }
                else if(replaceword.length() > targetword.length())
                {

                }
                else if(replaceword.length() < targetword.length())
                {

                }
            }
        }

    }
}

int main(){
    cout << endl << "############################# STRINGS AND WORDS #############################" << endl << endl;
    cout << "reading text file contents..." << endl << endl;

    ifstream input("input_text.txt", ifstream::in);
    stringstream inputStream;
    inputStream << input.rdbuf();
    string text = inputStream.str();

    int selection;

    while(1)
    {
        cout << "What would you like to perform? Enter the integer associated with your selection." << endl;
        cout << "1: Display Word Frequency" << endl;
        cout << "2: Replace Words" << endl;
        cout << "9: Quit" << endl;
        cin >> selection;

        if(selection == 1)
        {
            display_word_frequency(text);
        }
        else if(selection == 2)
        {
            replace(text);
        }
        else if(selection == 9)
        {
            break;
        }
        else
        {
            cout << "Not a valid selection." << endl;
        }
    }

    cout << "Good bye! :)" << endl;
    return 0;
}
