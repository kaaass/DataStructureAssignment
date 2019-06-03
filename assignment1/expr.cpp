#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

#define cin fin
#define cout fout
#define LL long long

ifstream fin("expr.in");
ofstream fout("expr.out");

enum Type {
    OP = 0, OPRAND
};

struct Token {
    Type type;
    char charVal;
    LL intVal;
};

bool is_num(char ch) {
    return '0' <= ch && ch <= '9';
}

vector<Token> tokenizer(string expr) {
    vector<Token> tokens;
    string token;
    char ch;
    int ind = 0, len = (int) expr.size();

    while (ind < len) {
        ch = expr[ind];
        if (is_num(ch)) {
            token.push_back(ch);
        } else {
            if (token.size() > 0) {
                LL val;
                sscanf(token.c_str(), "%lld", &val);
                tokens.push_back((Token) {OPRAND, '\0', val});
                // cout << token << endl;
                token = "";
            }
            tokens.push_back((Token) {OP, ch, -1});
            // cout << ch << endl;
        }
        ind++;
    }
    return tokens;
}

int getPrip(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            break;
    }
    return -1;
}

vector<Token> parseRpn(vector<Token> tokens) {
    vector<Token> rpn;
    stack<Token> ops;
    bool flag;
    for (auto token: tokens) {
        if (token.type == OP) {
            // Operator
            switch (token.charVal) {
                case '(':
                    ops.push(token);
                    break;
                case ')':
                    while (!ops.empty()) {
                        Token top = ops.top();
                        ops.pop();
                        if (top.charVal == '(') {
                            break;
                        }
                        rpn.push_back(top);
                    }
                    break;
                case '+':
                case '-':
                case '*':
                case '/':
                    flag = false;
                    while (!ops.empty()) {
                        Token top = ops.top();
                        if (getPrip(token.charVal) > getPrip(top.charVal)) {
                            ops.push(token);
                            flag = true;
                            break;
                        } else {
                            rpn.push_back(top);
                            ops.pop();
                        }
                    }
                    if (!flag) {
                        ops.push(token);
                    }
                    break;
                case '=':
                    while (!ops.empty()) {
                        rpn.push_back(ops.top());
                        ops.pop();
                    }
                    break;
                default:
                    break;
            }
        } else {
            rpn.push_back(token);
        }
    }
//    for (auto t: rpn) {
//        cout << t.charVal << " :" << t.intVal << endl;
//    }
    return rpn;
}

LL evalRpn(vector<Token> rpn) {
    stack<LL> op;
    for (auto t: rpn) {
        if (t.type == OP) {
            LL a, b;
            b = op.top(); op.pop();
            a = op.top(); op.pop();
            switch (t.charVal) {
                case '+':
                    op.push(a+b);
                    break;
                case '-':
                    op.push(a-b);
                    break;
                case '*':
                    op.push(a*b);
                    break;
                case '/':
                    op.push(a/b);
                    break;
                default:
                    break;
            }
        } else {
            op.push(t.intVal);
        }
        // cout << t.charVal << " :" << t.intVal << endl;
    }
    return op.top();
}

int main() {
    string expr;
    vector<Token> tokens;
    vector<Token> rpn;
    LL ret;

    cin >> expr;
    tokens = tokenizer(expr);
    rpn = parseRpn(tokens);
    ret = evalRpn(rpn);
    cout << ret << endl;
    return 0;
}