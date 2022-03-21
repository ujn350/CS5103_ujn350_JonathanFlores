//
// Created by ujn350 on 3/20/22.
//

#ifndef CS5103_UJN350_JONATHANFLORES_WORD_H
#define CS5103_UJN350_JONATHANFLORES_WORD_H
#include <string>
using namespace std;

class Word {
    private:
        string wordname;
        int instances;
    public:
        Word(string);
        void increment();
        string get_wordname();
        int get_instances();
};


#endif //CS5103_UJN350_JONATHANFLORES_WORD_H
