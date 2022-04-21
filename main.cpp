#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include "word.h"

using namespace std;

void replace_word_in_text(string::iterator& head, string::iterator& tail, string &text, string &targetword, string &replaceword)
{
    string testword;
    if(distance(head, tail) == targetword.length())
    {
        for (int i = 0; i < targetword.length(); i++)
        {
            testword.push_back(*(head + i));
        }
        if (testword == targetword)
        {
            while (head != tail)
            {
                int head_tail_dist = distance(head, tail);
                head = text.erase(head);
                tail = (head + head_tail_dist) - 1;
            }
            for (int i = replaceword.length() - 1; i >= 0; i--)
            {
                head = text.insert(head, replaceword[i]);
            }
            head = head + replaceword.length();
            tail = head;
        }
    }
}

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
    string::iterator end = text.end();

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

void replace_text(string &text)
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

    while(head != text.end() && tail != text.end())
    {
        if(!IsSeparator(*tail))
        {
            tail++;
            if(tail == text.end())
            {
                replace_word_in_text(head, tail, text, targetword, replaceword);
            }
        }
        else
        {
            replace_word_in_text(head, tail, text, targetword, replaceword);
            tail++;
            head = tail;
        }
    }

    ofstream output("input_text.txt", ofstream::out);
    output << text;
    output.close();
    cout << "replacement process complete" << endl;
    cout << "--------------------------------------------------------------------" << endl << endl;
}

void print_line(string::iterator text_head, string::iterator text_tail)
{
    while(text_head != text_tail)
    {
        cout << *text_head;
        text_head++;
    }
    cout << endl;
}

bool grepline_linesearch(const string::iterator& line_head, const string::iterator& line_tail, string keyword)
{
    string::iterator text_head = line_head;
    string::iterator text_tail = line_head;
    string current_word;

    while(text_head != line_tail && text_tail != line_tail)
    {
        if(!IsSeparator(*text_tail))
        {
            current_word.push_back(*text_tail);
            text_tail++;
            if(text_tail == line_tail)
            {
                if(current_word == keyword)
                {
                    print_line(line_head, line_tail);
                    return true;
                }
            }
        }
        else
        {
            if(current_word == keyword)
            {
                print_line(line_head, line_tail);
                return true;
            }
            current_word.clear();
            text_tail++;
            text_head = text_tail;
        }
    }
    return true;
}

void grepline(string &text)
{
    string keyword;
    bool FinalLineParsed = 0;

    cout << "------------------------- GREPLINE -------------------------" << endl;
    cout << "Please enter the keyword: " << endl;
    cin >> keyword;
    cout << endl;

    string::iterator line_head = text.begin();
    string::iterator line_tail = text.begin();

    while(!FinalLineParsed)
    {
        line_tail = line_head;
        while(*line_tail != '\n' && line_tail != text.end())
        {
            line_tail++;
        }
        if(line_tail == text.end())
        {
            FinalLineParsed = 1;
        }
        grepline_linesearch(line_head, line_tail, keyword);
        line_head = line_tail;
        line_head++;
    }

    cout << "--------------------------------------------------------------------" << endl << endl;
}

int main(){
    cout << endl << "############################# STRINGS AND WORDS #############################" << endl << endl;
    cout << "reading text file contents..." << endl << endl;

    ifstream input("input_text.txt", ifstream::in);
    stringstream inputStream;
    inputStream << input.rdbuf();
    string text = inputStream.str();
    input.close();

    int selection;

    while(1)
    {
        cout << "What would you like to perform? Enter the integer associated with your selection." << endl;
        cout << "1: Display Word Frequency" << endl;
        cout << "2: Replace Words" << endl;
        cout << "3: Grep Line" << endl;
        cout << "9: Quit" << endl;
        cin >> selection;

        if(selection == 1)
        {
            display_word_frequency(text);
        }
        else if(selection == 2)
        {
            replace_text(text);
        }
        else if(selection == 3)
        {
            grepline(text);
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
