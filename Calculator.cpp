#include "Calculator.h"
#include <sstream>

Calculator::Calculator(string infixEx){
    /*
    convert infix to prefix ->> reverse infix expression,
                                apply postfix conversion the reversed infix expression,
                                reverse again
                                                */
    this->stack = new Stack();
    
    //reverse the infix expression with stack
    string reverse;
    string token;
    istringstream iss(infixEx);
    iss >> token;
    while(token.compare(";") != 0){
        StackItem *item = new StackItem(token);
        stack->push(item);
        iss >> token;
    }
    while(!stack->isEmpty()){
        reverse += stack->top()->toString() + " ";
        stack->pop();
    }
    reverse += ";";
    
    //changes reversed pars
    for(int i = 0; i < reverse.length(); i++){
        if(reverse[i] == '('){
            reverse[i] = ')';
        }
        else if(reverse[i] == ')'){
            reverse[i] = '(';
        }
    }
    //postfix conversion is applied
    string result;
    string token2;
    istringstream iss2(reverse);
    iss2 >> token2;
    while(token2.compare(";") != 0){
        StackItem *newItem = new StackItem(token2);
        if(!newItem->isOperator){
            result += newItem->toString() + " ";
            delete newItem;
        }
        else if(newItem->op == OPERATOR_LEFTPAR){
            stack->push(newItem);
        }
        else if (newItem->op == OPERATOR_RIGHTPAR){
            while((!stack->isEmpty()) && (stack->top()->op != OPERATOR_LEFTPAR)){
                StackItem *newItem2 = stack->top();
                result += newItem2->toString() + " ";
                stack->pop();
            }
            if(stack->top()->op == OPERATOR_LEFTPAR){
                stack->pop();
            }
        }
        else {
            //inorder to make (+ and -) , (/ and *) priorities eqaul, .op values divided by 2
            while((!stack->isEmpty()) && (newItem->op/2  <= stack->top()->op/2)){
                StackItem *newItem3 = stack->top();
                result += newItem3->toString() + " ";    
                stack->pop();
            }
            stack->push(newItem);
        }
        iss2 >> token2;
    }
    while(!stack->isEmpty()){
        result += stack->top()->toString() + " ";
        stack->pop();
    }
    result += ";";
    
    //reverse again
    string prefixEx;
    string token3;
    istringstream iss3(result);
    iss3 >> token3;
    while(token3.compare(";") != 0){
        StackItem *item = new StackItem(token3);
        stack->push(item);
        iss3 >> token3;
    }
    while(!stack->isEmpty()){
        prefixEx += stack->top()->toString() + " ";
        stack->pop();
    }
    prefixEx += ";";    

    this->prefixExpression = prefixEx;
}

string Calculator::getPrefix(){
    return this->prefixExpression;
}

int Calculator::calculate(){
    //reverses the prefix expression that is obtained
    string convertedEx = this->prefixExpression;
    string rev;
    string token4;
    istringstream iss4(convertedEx);
    iss4 >> token4;
    while(token4.compare(";") != 0){
        StackItem *item = new StackItem(token4);
        stack->push(item);
        iss4 >> token4;
    }
    while(!stack->isEmpty()){
        rev += stack->top()->toString() +" ";
        stack->pop();
    }
    rev += ";";
    
    //calculate the result
    string token5;
    istringstream iss5(rev);
    iss5 >> token5;
    while(token5.compare(";") != 0){
        StackItem *newItem = new StackItem(token5);
        if(!newItem->isOperator){
            stack->push(newItem);
        }
        else{
            StackItem *item1 = stack->pop();
            StackItem *item2 = stack->pop();

            switch (newItem->op)
            {
            case OPERATOR_MINUS: {
                StackItem *newItem1 = new StackItem(to_string(item1->n - item2->n));
                stack->push(newItem1);
                break;
                }
            case OPERATOR_PLUS: {
                StackItem *newItem2 = new StackItem(to_string(item1->n + item2->n));
                stack->push(newItem2);
                break;
                }
            case OPERATOR_DIVISION:{
                StackItem *newItem3 = new StackItem(to_string(item1->n / item2->n));
                stack->push(newItem3);
                break;
                }
            case OPERATOR_MULTIPLICATION:{
                StackItem *newItem4 = new StackItem(to_string(item1->n * item2->n));
                stack->push(newItem4);
                break;
                }
            }
            delete item1;
            delete item2;
        }
        iss5 >> token5;
    }
    int result = stack->top()->n;
    
    while(!stack->isEmpty()){
        stack->pop();
    }
    return result;
}

Calculator::~Calculator(){
    delete this->stack;
}