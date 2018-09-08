#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    struct Bracket new_bracket('0',0);
    int last_error = 0;
    int first_error = 0;
    bool flag_close = 0;

    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            new_bracket.type = next;
            new_bracket.position = position;
            opening_brackets_stack.push(new_bracket);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if(!opening_brackets_stack.empty())
            {
                new_bracket = opening_brackets_stack.top();
                if(new_bracket.Matchc(next))
                {
                    opening_brackets_stack.pop();
                }
                else if(flag_close == 0)
                {
                    new_bracket.type = next;
                    new_bracket.position = position;
                    opening_brackets_stack.push(new_bracket);
                    flag_close = 1;
                    last_error = position + 1;
                }
            }
            else{
                new_bracket.type = next;
                new_bracket.position = position;
                opening_brackets_stack.push(new_bracket);
                flag_close = 1;
                last_error = position + 1;
            }
        }
    }

    // Printing answer, write your code here
    if(opening_brackets_stack.empty())
    {
        std::cout<<"Success";
    }
    else if(last_error != 0)
    {
        std::cout<<last_error;
    }
    else{
        while(!opening_brackets_stack.empty())
        {
            first_error = opening_brackets_stack.top().position + 1;
            opening_brackets_stack.pop();
        }
        std::cout<<first_error;
    }

    return 0;
}
