#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#endif // SYNTAX_ANALYZER_H

#pragma once

#include <bits/stdc++.h>
#include "lexic_analyzer.h"
using namespace std;

bool ended = false;
string result;
int cur_num = 1;
int err_num = 0;
bool in_get = true;
vector<pair<int, string>> lexems;
int type;
string str;
int loop_depth = 0;
bool Isblock();
bool isfunc_call();
vector<int> nums_mem;

void get() {
    in_get = true;
    if (lexems.empty()) throw string("SyntaxError: unexpected EOF");
    type = lexems.back().first;
    str = lexems.back().second;
    lexems.pop_back();
    bool f = cur_num != nums.back();
    cur_num = nums.back();
    nums.pop_back();
    if (type == 7) {
        throw string("SyntaxError: unexpected symbol");
    }
    if (f) {
        result = "\t\t" + str + ' ';
        err_num = str.size() + 1;
    } else {
        if (result.empty()) {
            result += "\t\t";
        }
        result += str + ' ';
        err_num += str.size() + 1;
    }
    in_get = false;
}

int next_num(int d = 1) {
    if (lexems.size() < d) throw string("SyntaxError: unexpected EOF");
    return lexems[lexems.size() - d].first;
}

string next_str(int d = 1) {
    if (lexems.size() < d) throw string("SyntaxError: unexpected EOF");
    return lexems[lexems.size() - d].second;
}

bool next_type() {
    if (lexems.size() == 0) return 0;
    string str = lexems.back().second;
    return str == "string" || str == "int" || str == "double" || str == "vector";
}

bool isass_operation() { return str == "=" || str == "+=" || str == "-=" ||
        str == "*=" || str == "/=" || str == "%=" || str == "&=" || str == "^=" || str == "|="; }

string But_Found() {
    return ", but found \"" + str + "\"";
}

bool iscremant() { return str == "--" || str == "++"; }

bool isunary_operation() { return str == "+" || str == "-" || str == "!" || str == "~"; }

bool isbinary_operation() { return type == 2 && !isass_operation() &&
            !(str == "--" || str == "++" || str == "!" || str == "~"); }

bool isatom_type() { return str == "string" || str == "int" || str == "double"; }

bool Istype() {
    if (get(), isatom_type()) return 1;
    else if (str == "vector") {
        if (get(), str != "<") throw string("SyntaxError: vector type must be inside \"<>\"") + But_Found();
        if (!Istype()) throw string("SyntaxError: expected type specifier") + But_Found();
        if (get(), str != ">") throw string("SyntaxError: vector type must be inside \"<>\"") + But_Found();
        return 1;
    } else if (str == ")") {
        ended = true;
        return 1;
    } else return 0;
}

bool Isname() { return get(), type == 1; }

bool Isfunc_params() {
    ended = false;
    get();
    if (str != "(") return 0;
    if (str == ")") return 1;
    while (true) {
        if (!Istype()) throw string("SyntaxError: expected type specifier") + But_Found();
        if (ended) {
            return 1;
        }
        if (!Isname()) throw string("SyntaxError: expected variable name") + But_Found();
        if (get(), str != ",") break;
    }
    if (str != ")") throw string("SyntaxError: expected \")\" at the end function parameters definition") + But_Found();
    return 1;
}

bool Isexpr(string end_c1 = ";", string end_c2 = "\0") {
    // 0 - start
    // 1 - name
    // 2 - .
    // 3 - function name
    // 4 - operation
    // 5 - variable
    // 6 - value
    // 7 - pref_inc
    int cur = 0;
    if (next_str() == ";" && (end_c1 == ";" || end_c2 == ";")) return get(), 1;
    if ((next_str() == "break" || next_str() == "continue") &&
            next_str(2) == ";" && end_c1 == ";" && end_c2 == "\0") {
        get(), get();
        if (loop_depth > 0) return 1;
        else {
            err_num -= str.size() + 6;  // 1 + "break".size()
            throw string("SyntaxError: using \'break\' outside loop is forbidden");
        }
    }
    while (get(), str != end_c1 && str != end_c2) {
        if (cur == 0) {
            if (isunary_operation()) cur = 4;
            else if (str == "(") Isexpr(")"), cur = 6;
            else if (iscremant()) cur = 7;
            else if (type == 1) cur = 1;
            else if (type > 3) cur = 6;
            else throw string("SyntaxError: expected expression") + But_Found();
        } else if (cur == 1) {
            if (iscremant()) cur = 6;
            else if (isass_operation()) cur = 0;
            else if (isbinary_operation()) cur = 4;
            else if (str == "[") Isexpr("]"), cur = 5;
            else if (str == ".") cur = 2;
            else if (str == "(") isfunc_call(), cur = 6;
            else throw string("SyntaxError: expected operation") + But_Found();
        } else if (cur == 2) {
            if (type == 1) cur = 3;
            else throw string("SyntaxError: expected method name") + But_Found();
        } else if (cur == 3) {
            if (str != "(") throw string("SyntaxError: expected function call parameters list") + But_Found();
            isfunc_call();
            cur = 6;
        } else if (cur == 4) {
            if (str == "(") Isexpr(")"), cur = 6;
            else if (iscremant()) cur = 7;
            else if (isunary_operation()) continue;
            else if (type == 1) cur = 6;
            else if (type > 3) cur = 6;
            else throw string("SyntaxError: expected second operand in expression") + But_Found();
        } else if (cur == 5) {
            if (iscremant()) cur = 6;
            else if (isass_operation()) cur = 0;
            else if (isbinary_operation()) cur = 4;
            else if (str == "[") Isexpr("]"), cur = 5;
            else if (str == ".") cur = 2;
            else throw string("SyntaxError: expected operation") + But_Found();
        } else if (cur == 6) {
            if (isbinary_operation()) cur = 4;
            else if (str == "[") Isexpr("]"), cur = 6;
            else if (str == ".") cur = 2;
            else throw string("SyntaxError: expected operation") + But_Found();
        } else if (cur == 7) {
            if (iscremant()) continue;
            else if (type == 1) cur = 6;
            else throw string("SyntaxError: expected variable name") + But_Found();
        }
    }
    if (!(cur == 1 || cur == 5 || cur == 6)) throw string("SyntaxError: incomplete expression");
    return 1;
}

bool isfunc_call() {
    if (next_str() == ")") return get(), 1;
    while (true) {
        Isexpr(",", ")");
        if (str == ")") break;
    }
    return 1;
}

bool Isdeclaration_operator() {
    Istype();
    while (get(), type == 1) {
        if (get(), str == "=") Isexpr(";", ",");
        else if (str == ",") continue;
        else if (str == ";") break;
        else throw string("SyntaxError: declaration error");
        if (str == ";") break;
    }
    if (str != ";") throw string("SyntaxError: declaration error");
    return 1;
}

bool Isfor_operator() {
    ++loop_depth;
    get();
    if (get(), str != "(") throw string("SyntaxError: expected \'for\' loop description inside \"()\"") + But_Found();
    if (next_type()) Isdeclaration_operator();
    else Isexpr();
    Isexpr();
    Isexpr(")");
    Isblock();
    --loop_depth;
    return 1;
}

bool Iswhile_operator() {
    ++loop_depth;
    get();
    if (get(), str != "(") throw string("SyntaxError: expected \'while\' loop description inside \"()\"") + But_Found();
    Isexpr(")");
    Isblock();
    --loop_depth;
    return 1;
}

bool Isif_operator() {
    get();
    if (get(), str != "(") throw string("SyntaxError: expected \'if\' condition inside \"()\"") + But_Found();
    Isexpr(")");
    Isblock();
    if (next_str() == "else") get(), Isblock();
    return 1;
}

bool Iscomp_operator() {
    if (next_type()) Isdeclaration_operator();
    else if (next_str() == "for") Isfor_operator();
    else if (next_str() == "while") Iswhile_operator();
    else if (next_str() == "if") Isif_operator();
    else Isexpr();
    return 1;
}

bool Isblock() {
    if (get(), str != "{") throw string("SyntaxError: expected block") + But_Found();
    while (next_str() != "}") {
        if (next_str() == "{") Isblock();
        else Iscomp_operator();
    }
    get();
    return 1;
}

bool Isfunc_block() {
    if (get(), str != "{") return 0;
    while (next_str() != "return") {
        if (next_str() == "{") Isblock();
        else Iscomp_operator();
    }
    get();
    Isexpr();
    if (get(), str != "}") throw string("SyntaxError: expected \"}\" at the end of function") + But_Found();
    return 1;
}

bool Check_Syntax(vector<pair<int, string>> &aa) {
    nums_mem = nums;
    lexems = aa;
    reverse(lexems.begin(), lexems.end());
    reverse(nums.begin(), nums.end());
    while (!lexems.empty()) {
        if (get(), str != "fn") throw string("SyntaxError: expexted function description") + But_Found();
        if (!Istype()) throw string("SyntaxError: expected type specifier") + But_Found();
        if (!Isname()) throw string("SyntaxError: expected function name") + But_Found();
        if (!Isfunc_params()) throw string("SyntaxError: expected function parameters definition inside \"()\"") + But_Found();
        if (!Isfunc_block()) throw string("SyntaxError: expected block") + But_Found();
    }
    return 1;
}
