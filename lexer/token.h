#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>
#ifndef TOKEN_H
#define TOKEN_H

using namespace std;

enum Names 
{
    UNDEF,//0
    ID,//1
    INTEGER, //2
    OP, //3
    SEP, //4
    SYSTEM_OUT_PRINTLN, // 5
    END_OF_FILE//6
};

class Token 
{
    public: 
        int name;
        int attribute;
        string lexeme;
    
        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }

        Token(int name, string l)
        {
            this->name = name;
            attribute = UNDEF;
            lexeme = l;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};

#endif // TOKEN_H