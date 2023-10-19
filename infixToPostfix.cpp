/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
'* Program name    : L4-3 (stackInfix2PostSTLLib)                      *
'*                                                                     *
'* Written by      : Matthew Carreon                                   *
'*                                                                     *
'* Purpose         : Convert from infix expression into a postfix expression*
*                    using STL Stack Libary                            *
'*                                                                     *
'* Inputs          : An infix expression will be inputed through a seperate*
*                    main program                                      *
'*                                                                     *
'* Outputs         : Display the infix and postfix expressions         *
'*                                                                     *
'* Calls           : Calls from the class infixToPostfix and stack STL *
*                    Calls to precedence(char symA, char symB),        *
*                    getInfix(string infix), showInfix(), showPostfix()*
*                    infixToPostfix(string infix)                      *
*                    External Calls from the class STL stack          *
'*                                                                     *
'* Structure       : BEGIN                                             *
'*                        initalize a infixToPostfix variable          *
*                         Call getinfix, showInFix and showPostfix     *
'*                   STOP                                              *
'*                        End of Program                               *
'*                                                                     *
'*---------------------------------------------------------------------*
'* Change Log:                                                         *
'*                         Revision                                    *
'*       Date    Changed  Rel Ver Mod Purpose                          *
'* 05/13/22      matthew  000.000.000 Create the basic file to be used *
'* 05/13/22      matthew  000.001.000 Copy old code from the previous L3-2*
'* 05/13/22      matthew  000.002.000 2a is converted using STL stack  *
'* 05/13/22      matthew  000.003.000 2b is converted using STL stack  *
'* 05/13/22      matthew  000.004.000 2c is converted using STL stack  *
'* 05/13/22      matthew  000.005.007 Fixed issues with stack not grabbing*
*                                     the proper symbols.              *
'* 05/13/22      matthew  000.006.002 Fixed issues with stack not grabbing*
*                                     the proper symbols.              *
*                                                                      *
'* 05/13/22      matthew  000.007.004 Fixed issues with stack pushing  *
*                                     duplicate symbols                *
'* 05/14/22      matthew  000.008.000 Documention + removed leftover code*
'* 05/14/22      matthew  000.008.002 Fixed an error when removing leftover*
*                                     code                             *
'* 05/14/22      matthew  000.008.005 Removed more leftover code from  *
*                                     other infixToPostfix.h           *
'*                                                                     *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "infixToPostfix.h"
#include <string>
#include <iostream>
#include <stack>

using namespace std;

//This is a method to check the precendence of two characters
//Code taken from previous L3-2 code
bool infixToPostfix::precedence(char symA, char symB)
{
    int precedence1, precedence2;

    if (symA == '*' || symA == '/') { //Multiplacation and division is 1st
        precedence1 = 2;
    }
    else if (symA == '+' || symA == '-') { //Addition and substraction is 2nd
        precedence1 = 1;
    }
    else if (symA == '(') { //Anything else is in 3rd
        precedence1 = 0;
    }

    if (symB == '*' || symB == '/') { //Multiplacation and division is 1st
        precedence2 = 2;
    }
    else if (symB == '+' || symB == '-') { //Addition and substraction is 2nd
        precedence2 = 1;
    }
    else { //Anything else is in 3rd
        precedence2 = 0;
    }
    return (precedence1 >= precedence2); //Compare the precedence (true or false)

}

void infixToPostfix::convertToPostFix()
{
    stack<char> myStackChar;//Initalize stack #1
    pfx = ""; //Initalize postfix #1
    int lengthOfInfix = ifx.length(); //Get the lenth of the infix expression for the for loop 
    for (int i = 0; i < lengthOfInfix; i++) { //#2
        if ((ifx[i] >= 'a' && ifx[i] <= 'z') || (ifx[i] >= 'A' && ifx[i] <= 'Z') || (ifx[i] >= '0' && ifx[i] <= '9')) { //Step 2a a) If sym is an operand, append sym to pfx.
            pfx += ifx[i]; //Add the symbol to postfix
        }
        
        else if (ifx[i] == '(') { //Step 2b If sym is (, push sym onto the stack.
            myStackChar.push(ifx[i]); //symbol is pushed onto Stack
        }

        else if (ifx[i] == ')') { //Step 2c If sym is ), pop and append all of the symbols from the stack until the most recent left parenthesis. Pop and discard the left parenthesis
            while (myStackChar.top() != '(') { //v2 REWORKED
                pfx += myStackChar.top(); //The top symbol from the stack to postfix 
                myStackChar.pop(); //Remove the top character from the stack
            }
            myStackChar.pop(); //This is used to help discard the left parenthesis
        }

        if (ifx[i] == '+' || ifx[i] == '-' || ifx[i] == '*' || ifx[i] == '/') { //Step 2d If sym is an operator:  
            //2d i Pop and append all of the operators from the stack two pfx that are above the most recent left parenthesis and have precedence greater than or equal two sym.
            while (!myStackChar.empty() && precedence(myStackChar.top(), ifx[i])) { //Added precendence
                pfx += myStackChar.top();//The top symbol from the stack to postfix 
                myStackChar.pop();//Remove the top character from the stack
            }

            //2d ii Push sym onto stack
            myStackChar.push(ifx[i]);
        }
    }

    //#3 After processing infx, some operators might be left in the stack.  Pop and append to pfx everything from the stack.
    while (!myStackChar.empty()) {
        pfx += myStackChar.top();
        myStackChar.pop();
    }

}

//Takes the 
void infixToPostfix::getInfix(string infix)
{
    ifx = infix;
    //convertToPostFix();
}

//Method to display Infix Expression
void infixToPostfix::showInfix()
{
    cout << "Infix Expression: " << ifx << endl;
}

//Method to display Postfix Expression
void infixToPostfix::showPostfix()
{
    cout << "Postfix Expression: " << pfx << endl;
}

//Default Contructor with string parameter
infixToPostfix::infixToPostfix(string infix) {
    ifx = infix;
    pfx = "";
    convertToPostFix();
}

//Default Contructor with no parameter
infixToPostfix::infixToPostfix()
{
    ifx = "";
    pfx = "";
    //convertToPostFix();
}