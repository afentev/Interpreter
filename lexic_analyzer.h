#ifndef LEXIC_ANALYZER_H
#define LEXIC_ANALYZER_H

#endif // LEXIC_ANALYZER_H

#pragma once

#include <bits/stdc++.h>
using namespace std;

int cur_str_num = 1;
vector<int> nums(0);

vector<string> strings;

ifstream fin;
// 0 - reserved
// 1 - variable
// 2 - operation
// 3 - punctuation
// 4 - string const
// 5 - int const
// 6 - double const
// 7 - rubbish

void Push_Lexem(vector<pair<int, string>> &res, int &cur_num, string &cur_str, unordered_set<string> &reserved) {
    if (cur_num == 0) {
        return;
    }
    if (cur_num == 6) {
        res.push_back({7, cur_str});
        nums.push_back(cur_str_num);
    } else if (cur_num == 5) {
        res.push_back({4, cur_str});
        nums.push_back(cur_str_num);
    } else if (cur_num == 4) {
        if (reserved.find(cur_str) == reserved.end())
            res.push_back({1, cur_str});
        else
            res.push_back({0, cur_str});
        nums.push_back(cur_str_num);
    } else if (cur_num == 1) {
        res.push_back({5, cur_str});
        nums.push_back(cur_str_num);
    } else {
        res.push_back({6, cur_str});
        nums.push_back(cur_str_num);
    }
    cur_num = 0;
    cur_str = "";
}

vector<pair<int, string>> Make_Lexems() {
    string tmp;
    unordered_set<string> st_reserved(256), st_ops(265), st_punct(256);
    fin.open("/Users/user/CLionProjects/Language/stuff/reserved_words");
    while (fin >> tmp) st_reserved.insert(tmp);
    fin.close();
    fin.open("/Users/user/CLionProjects/Language/stuff/operations");
    while (fin >> tmp) st_ops.insert(tmp);
    fin.close();
    fin.open("/Users/user/CLionProjects/Language/stuff/punctuation");
    while (fin >> tmp) st_punct.insert(tmp);
    fin.close();
    fin.open("/Users/user/CLionProjects/Language/stuff/source_code");
    char cc, next;
    fin.get(cc);
    int cur_num = 0;
    string cur_str;
    vector<pair<int, string>> res;
    while (fin.get(next)) {
        string ss = "", s1(1, cc), s2(1, next);
        ss.push_back(cc);
        ss.push_back(next);
        if (cur_num == 1 && cc == '.') {
            if (!isdigit(next)) cur_num = 6;
            else cur_num = 2;
            cur_str.push_back(cc);
        } else if (cur_num == 5) {
            if (cc == '"') {
//                cur_str += "\"";
                Push_Lexem(res, cur_num, cur_str, st_reserved);
            }
            else cur_str.push_back(cc);
        } else if (ss == "/*")  {
            while (!(cc == '*' && next == '/')) if (cc == '\n') ++cur_str_num, fin >> next, cc = next;
            fin >> next;
        } else if (cc == '#') {
            Push_Lexem(res, cur_num, cur_str, st_reserved);
            while (next != '\n') fin.get(next);
            ++cur_str_num;
            fin.get(next);
        } else if (cc == ' ' || cc == '\n') {
            if (cc == '\n') {
                ++cur_str_num;
                strings.push_back(tmp);
                tmp = "";
            }
            Push_Lexem(res, cur_num, cur_str, st_reserved);
        } else if (st_punct.find(s1) != st_punct.end()) {
            Push_Lexem(res, cur_num, cur_str, st_reserved);
            res.push_back({3, s1});
            nums.push_back(cur_str_num);
        } else if (st_ops.find(ss) != st_ops.end()) {
            Push_Lexem(res, cur_num, cur_str, st_reserved);
            res.push_back({2, ss});
            nums.push_back(cur_str_num);
            fin.get(next);
        } else if (st_ops.find(s1) != st_ops.end()) {
            Push_Lexem(res, cur_num, cur_str, st_reserved);
            res.push_back({2, s1});
            nums.push_back(cur_str_num);
        } else if (cur_num == 6) {
            cur_str.push_back(cc);
        } else if (cur_num == 1) {
            if (cc == 'e') {
                if (!isdigit(next)) cur_num = 6;
                else cur_num = 3;
            } else if (!isdigit(cc)) {
                cur_num = 6;
            }
            cur_str.push_back(cc);
        } else if (cur_num == 2) {
            if (cc == 'e') {
                if (!isdigit(next)) cur_num = 6;
                else cur_num = 3;
            } else if (!isdigit(cc)) {
                cur_num = 6;
            }
            cur_str.push_back(cc);
        } else if (cur_num == 3) {
            if (!isdigit(cc)) cur_num = 6;
            cur_str.push_back(cc);
        } else if (cur_num == 4) {
            if (!(isalnum(cc) || cc == '_')) cur_num = 6;
            cur_str.push_back(cc);
        } else {
            if (cc == '"') {
                cur_num = 5;
                cc = next;
//                cur_str += "\"";
                continue;
            }
            if (isdigit(cc)) cur_num = 1;
            else if (isalpha(cc)) cur_num = 4;
            else cur_num = 6;
            cur_str.push_back(cc);
        }
        cc = next;
    }
    Push_Lexem(res, cur_num, cur_str, st_reserved);
    return res;
}
