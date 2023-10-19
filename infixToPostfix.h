#pragma once
#include <string>
#include <iostream>
#include <stack>

using namespace std;

class infixToPostfix {
public:
    //Methods
    void convertToPostFix();
    void getInfix(string infix);
    void showInfix();
    void showPostfix();
    bool precedence(char A, char B);

    //Default constructor
    infixToPostfix(string infix);
    infixToPostfix();

private:
    string ifx; // infix notation
    string pfx; // postfix notation
};

