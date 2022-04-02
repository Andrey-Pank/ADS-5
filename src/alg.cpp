// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priory(char sym_oper) {
    if ('(' == sym_oper) {
        return 0;
    } else if (')' == sym_oper) {
        return 1;
    } else if ('+' == sym_oper || '-' == sym_oper) {
        return 2;
    } else if ('*' == sym_oper || '/' == sym_oper) {
        return 3;
    } else if (' ' == sym_oper) {
        return 4;
    } else {
        return 5;
    }
}

std::string infx2pstfx(std::string inf) {
  TStack <char, 100> stack;
    std::string out;
    int i = 0;
    for (; i < inf.length(); i++) {
        if (5 == priory(inf[i])) {
            out += inf[i];
            while (5 == priory(inf[i+1]) && (i+1) < inf.length()) {
                out += inf[i+1];
                i += 1;
            }
            out += ' ';
        } else {
            if (0 == priory(inf[i])) {
                stack.push(inf[i]);
            } else if (priory(inf[i]) > priory(stack.get())) {
                stack.push(inf[i]);
            } else if (stack.isEmpty()) {
                stack.push(inf[i]);
            } else if (1 == priory(inf[i])) {
                while (0 != priory(stack.get())) {
                    out += stack.get();
                    out += ' ';
                    stack.pop();
                }
                stack.pop();
            } else if (priory(inf[i]) <= priory(stack.get())) {
                while (!stack.isEmpty() && 1 < priory(stack.get())) {
                    out += stack.get();
                    out += ' ';
                    stack.pop();
                }
                stack.push(inf[i]);
            }
        }
    }
    while (!stack.isEmpty()) {
        out += stack.get();
        out += ' ';
        stack.pop();
    }
    out.pop_back();
    return out;
}

int eval(std::string pref) {
  TStack<int, 100> istack;
    std::string out;
    int res = 0;
    int i = 0;
    for (; i < pref.length(); i++) {
        std::string check = "";
        while (5 == priory(pref[i])) {
            check += pref[i];
            i += 1;
        }
        if (check != "") {
            istack.push(std::stoi(check));
        }
        if (2 == priory(pref[i]) || 3 == priory(pref[i])) {
            int a = istack.get();
            istack.pop();
            int b = istack.get();
            istack.pop();
            if ('-' == pref[i]) {
                res = b - a;
                istack.push(res);
            } else if ('+' == pref[i]) {
                res = a + b;
                istack.push(res);
            } else if ('*' == pref[i]) {
                res = a * b;
                istack.push(res);
            } else if ('/' == pref[i]) {
                res = b / a;
                istack.push(res);
            }
        }
    }
    res = istack.get();
    return res;
}
