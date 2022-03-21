//
// Created by ujn350 on 3/20/22.
//

#include "word.h"
Word::Word(string name)
{
    wordname = name;
    instances = 1;
}

void Word::increment()
{
    instances++;
}

string Word::get_wordname()
{
    return wordname;
}

int Word::get_instances()
{
    return instances;
}