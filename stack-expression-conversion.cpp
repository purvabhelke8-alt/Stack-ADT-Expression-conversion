#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Node for Singly Linked List
struct Node
{
    char data;
    Node* next;

    Node(char value)
    {
        data = value;
        next = nullptr;
    }
};

// Stack ADT using Singly Linked List
class Stack
{
private:
    Node* top;

public:
    // Constructor
    Stack()
    {
        top = nullptr;
    }

    // Destructor
    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    // Check whether stack is empty
    bool isEmpty()
    {
        return top == nullptr;
    }

    // Push element into stack
    void push(char value)
    {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    // Pop element from stack
    char pop()
    {
        if (isEmpty())
        {
            return '\0';
        }

        Node* temp = top;
        char value = top->data;

        top = top->next;
        delete temp;

        return value;
    }

    // Return top element
    char peek()
    {
        if (isEmpty())
        {
            return '\0';
        }

        return top->data;
    }
};

// Check whether character is an operator
bool isOperator(char ch)
{
    return ch == '+' || ch == '-' ||
           ch == '*' || ch == '/' ||
           ch == '^';
}

// Return operator precedence
int precedence(char op)
{
    if (op == '^')
        return 3;

    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

// Check right associativity
bool isRightAssociative(char op)
{
    return op == '^';
}

// Convert infix expression to postfix
string infixToPostfix(const string& infix)
{
    Stack stack;
    string postfix;

    for (char ch : infix)
    {
        // Ignore spaces
        if (ch == ' ')
            continue;

        // Operand
        if (isalnum(static_cast<unsigned char>(ch)))
        {
            postfix += ch;
        }

        // Opening parenthesis
        else if (ch == '(')
        {
            stack.push(ch);
        }

        // Closing parenthesis
        else if (ch == ')')
        {
            while (!stack.isEmpty() && stack.peek() != '(')
            {
                postfix += stack.pop();
            }

            if (!stack.isEmpty() && stack.peek() == '(')
            {
                stack.pop();
            }
        }

        // Operator
        else if (isOperator(ch))
        {
            while (!stack.isEmpty() &&
                   stack.peek() != '(' &&
                   (precedence(stack.peek()) > precedence(ch) ||
                   (precedence(stack.peek()) == precedence(ch) &&
                    !isRightAssociative(ch))))
            {
                postfix += stack.pop();
            }

            stack.push(ch);
        }
    }

    // Pop remaining operators
    while (!stack.isEmpty())
    {
        if (stack.peek() != '(')
        {
            postfix += stack.pop();
        }
        else
        {
            stack.pop();
        }
    }

    return postfix;
}

// Convert infix expression to prefix
string infixToPrefix(string infix)
{
    // Remove spaces
    infix.erase(
        remove(infix.begin(), infix.end(), ' '),
        infix.end()
    );

    // Reverse expression
    reverse(infix.begin(), infix.end());

    // Swap parentheses
    for (char& ch : infix)
    {
        if (ch == '(')
            ch = ')';
        else if (ch == ')')
            ch = '(';
    }

    // Convert reversed expression to postfix
    string postfix = infixToPostfix(infix);

    // Reverse postfix to obtain prefix
    reverse(postfix.begin(), postfix.end());

    return postfix;
}

// Main function
int main()
{
    string infix;

    cout << "============================================\n";
    cout << "     STACK ADT - EXPRESSION CONVERTER\n";
    cout << "============================================\n";

    cout << "\nEnter an Infix Expression: ";
    getline(cin, infix);

    if (infix.empty())
    {
        cout << "\nError: Expression cannot be empty.\n";
        return 1;
    }

    // Generate postfix expression
    string postfix = infixToPostfix(infix);

    // Generate prefix expression
    string prefix = infixToPrefix(infix);

    cout << "\n--------------------------------------------\n";
    cout << "             CONVERSION RESULT\n";
    cout << "--------------------------------------------\n";

    cout << "Infix   : " << infix << endl;
    cout << "Postfix : " << postfix << endl;
    cout << "Prefix  : " << prefix << endl;

    cout << "--------------------------------------------\n";
    cout << "Program executed successfully!🎊🎊\n";
    cout << "============================================\n";

    return 0;
}
