//
// Created by afentev on 3/17/21.
//

#ifndef LANGUAGE_SEMANTIC_ANALYZER_H
#define LANGUAGE_SEMANTIC_ANALYZER_H

#include <bits/stdc++.h>
#include "syntax_analyzer.h"

using namespace std;

std::list<pair<int, string>> dest;

struct VarVal {
    string name, type, value, id;
    bool init = false;
};

bool is_correct_assignment(const string& t1, const string& t2) {
    if (t1 == "int" && t2 == "int") {
        return true;
    } else if (t1 == "int" && t2 == "double") {
        return true;
    } else if (t1 == "double" && t2 == "int") {
        return true;
    } else if (t2 == "double" && t2 == "double") {
        return true;
    } else if (t1 == "string" && t2 == "string") {
        return true;
    } else if (t1 == "vector" && t2 == "vector") {
        return true;
    }
    return false;
}

bool is_correct_addition(const string& t1, const string& t2) {
    if (t1 == "int" && t2 == "int") {
        return true;
    } else if (t1 == "int" && t2 == "double") {
        return true;
    } else if (t1 == "double" && t2 == "int") {
        return true;
    } else if (t2 == "double" && t2 == "double") {
        return true;
    } else if (t1 == "string" && t2 == "string") {
        return true;
    }
    return false;
}

bool is_correct_mult(const string& t1, const string& t2) {
    if (t1 == "int" && t2 == "int") {
        return true;
    } else if (t1 == "int" && t2 == "double") {
        return true;
    } else if (t1 == "double" && t2 == "int") {
        return true;
    } else if (t2 == "double" && t2 == "double") {
        return true;
    } else if (t1 == "int" && t2 == "string") {
        return true;
    } else if (t1 == "string" && t2 == "int") {
        return true;
    }
    return false;
}

bool is_correct_division(const string& t1, const string& t2) {
    if (t1 == "int" && t2 == "int") {
        return true;
    } else if (t1 == "int" && t2 == "double") {
        return true;
    } else if (t1 == "double" && t2 == "int") {
        return true;
    } else if (t2 == "double" && t2 == "double") {
        return true;
    }
    return false;
}

bool is_correct_hdivision(const string& t1, const string& t2) {
    if (t1 == "int" && t2 == "int") {
        return true;
    }
    return false;
}

class TID {
public:
    void init() {
        id = new int;
        *id = 0;
        this->parent = nullptr;
    }

    TID() {
        init();
    }

    TID* add_block() {
        TID* block = new TID;
        block->init();
        block->id = id;
        block->parent = this;
        children.push_back(block);
        return block;
    }

    std::string add(VarVal& obj) {
        obj.id = "&" + std::to_string(*id);
        *id += 1;
        variables[obj.name] = obj;
        return obj.id;
    }

    bool is_contain(const string& s) {
        if (this->parent == nullptr) {
            return is_contain_local(s);
        } else {
            if (is_contain_local(s)) {
                return true;
            } else {
                return this->parent->is_contain(s);
            }
        }
    }

    std::tuple<string, string, string> get_all(string s) {
        if (this->is_contain(s)) {
            if (this->variables.find(s) != this->variables.end()) {
                return {this->variables[s].type, this->variables[s].value, this->variables[s].id};
            } else {
                return this->parent->get_all(s);
            }
        } else {
            {
                std::string::const_iterator it = s.begin();
                while (it != s.end() && std::isdigit(*it)) ++it;
                if (!s.empty() && it == s.end()) {
                    return {"int", s, "-1"};
                }
            }
            {
                char* p = nullptr;
                std::strtof(s.data(), &p);
                if (p == s.data() + s.size())
                    return {"double", s, "-1"};
            }
            if (s.size() > 1) {
                if (s[0] == '"' && s[s.size() - 1] == '"') {
                    return {"string", s, "-1"};
                }
            }
            dest.reverse();
            for (const auto& c: dest) {
                lexems.push_back(c);
            }
            throw "NameError: name '" + s + "' is not defined";
        }

    }

    bool is_contain_local(const string& s) {
        return variables.find(s) != variables.end();
    }

    TID* parent;
    vector<TID*> children;
    map<string, VarVal> variables;
    int* id;
};

void Check_Semantic(vector<pair<int, string>> &aa) {
    reverse(nums_mem.begin(), nums_mem.end());
    result = "";
    err_num = 0;
    cur_num = 1;
    str = "";

    auto tid = new TID;
    tid->init();

    string func_name;

    int delay = 0;
    int await = 0;
    string type_;
    int vec_depth = 0;
    int retawait = 0;
    int funawait = 0;

    int index = 0;
    dest = std::list<pair<int, string>> (aa.begin(), aa.end());
    for (const auto& elem: aa) {
        dest.erase(dest.begin());
        str = elem.second;
        bool f = cur_num != nums_mem.back();
        cur_num = nums_mem.back();
        nums_mem.pop_back();

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

        if (elem.second == "//" || elem.second == "%" || elem.second == "|" || elem.second == "||" ||
            elem.second == "&" || elem.second == "&&" || elem.second == "^" || elem.second == "<<" ||
            elem.second == ">>" || elem.second == "%=" || elem.second == "|=" || elem.second == "&=" ||
            elem.second == "^=") {
            string t1 = std::get<0>(tid->get_all(aa[index - 1].second));
            string t2 = std::get<0>(tid->get_all(aa[index + 1].second));
            if (!is_correct_hdivision(t1, t2) && (aa[index + 2].second == ";" || aa[index + 2].second == ",")) {
                dest.reverse();
                for (auto c: dest) {
                    lexems.push_back(c);
                }
                throw string("TypeError: unsupported operand type(s) for " + elem.second + ": '" + t1 + "' and '" + t2 + "'");
            }
        } else if (elem.second == ">" || elem.second == "<" || elem.second == ">=" || elem.second == "<=" ||
                    elem.second == "==" || elem.second == "!=" || elem.second == "+" || elem.second == "+=") {
            string t1 = std::get<0>(tid->get_all(aa[index - 1].second));
            string t2 = std::get<0>(tid->get_all(aa[index + 1].second));
            if (!is_correct_addition(t1, t2) && (aa[index + 2].second == ";" || aa[index + 2].second == ",")) {
                dest.reverse();
                for (auto c: dest) {
                    lexems.push_back(c);
                }
                throw string("TypeError: unsupported operand type(s) for " + elem.second + ": '" + t1 + "' and '" + t2 + "'");
            }
        } else if (elem.second == "~") {
            string t2 = std::get<0>(tid->get_all(aa[index + 1].second));
            if (t2 != "int" && (aa[index + 2].second == ";" || aa[index + 2].second == ",")) {
                dest.reverse();
                for (auto c: dest) {
                    lexems.push_back(c);
                }
                throw string("TypeError: bad operand type for unary ~: '" + t2 + "'");
            }
        } else if (elem.second == "-" || elem.second == "+=") {
            string t1 = std::get<0>(tid->get_all(aa[index - 1].second));
            string t2 = std::get<0>(tid->get_all(aa[index + 1].second));
            if (!is_correct_division(t1, t2) && (aa[index + 2].second == ";" || aa[index + 2].second == ",")) {
                dest.reverse();
                for (auto c: dest) {
                    lexems.push_back(c);
                }
                throw string("TypeError: unsupported operand type(s) for " + elem.second + ": '" + t1 + "' and '" + t2 + "'");
            }
        } else if (elem.second == "*" || elem.second == "*=") {
            string t1 = std::get<0>(tid->get_all(aa[index - 1].second));
            string t2 = std::get<0>(tid->get_all(aa[index + 1].second));
            if (!is_correct_mult(t1, t2) && (aa[index + 2].second == ";" || aa[index + 2].second == ",")) {
                dest.reverse();
                for (auto c: dest) {
                    lexems.push_back(c);
                }
                throw string("TypeError: unsupported operand type(s) for " + elem.second + ": '" + t1 + "' and '" + t2 + "'");
            }
        } else if (elem.second == "/" || elem.second == "/=") {
            string t1 = std::get<0>(tid->get_all(aa[index - 1].second));
            string t2 = std::get<0>(tid->get_all(aa[index + 1].second));
            if (!is_correct_division(t1, t2) && (aa[index + 2].second == ";" || aa[index + 2].second == ",")) {
                dest.reverse();
                for (auto c: dest) {
                    lexems.push_back(c);
                }
                throw string("TypeError: unsupported operand type(s) for " + elem.second + ": '" + t1 + "' and '" + t2 + "'");
            }
        } else if (elem.second == "**") {
            string t1 = std::get<0>(tid->get_all(aa[index - 1].second));
            string t2 = std::get<0>(tid->get_all(aa[index + 1].second));
            if (!is_correct_division(t1, t2) && (aa[index + 2].second == ";" || aa[index + 2].second == ",")) {
                dest.reverse();
                for (auto c: dest) {
                    lexems.push_back(c);
                }
                throw string("TypeError: unsupported operand type(s) for " + elem.second + ": '" + t1 + "' and '" + t2 + "'");
            }
        } else if (elem.second == "=") {
            string t1 = std::get<0>(tid->get_all(aa[index - 1].second));
            string t2 = std::get<0>(tid->get_all(aa[index + 1].second));
            if (!is_correct_assignment(t1, t2) && (aa[index + 2].second == ";" || aa[index + 2].second == ",")) {
                dest.reverse();
                for (auto c: dest) {
                    lexems.push_back(c);
                }
                throw string("TypeError: assignment type missmatch: '" + t1 + "' expected, but '" + t2 + "' found");
            }
        }

        if (elem.second == "{") {
            auto t = tid->add_block();
            tid = t;
        } else if (elem.second == "}") {
            tid = tid->parent;
        }

        if (retawait) {
            retawait--;
            if (tid->is_contain(elem.second)) {
                string t = std::get<0>(tid->get_all(func_name));
                if(std::get<0>(tid->get_all(elem.second)) != t) {
                    dest.reverse();
                    for (auto c: dest) {
                        lexems.push_back(c);
                    }
                    throw string("TypeError: missmatch returning type: '" + t +
                    "' expected, but '" + tid->variables[elem.second].type + "' found");
                }
            }
        }

        if (elem.second == "return") {
            retawait = 1;
        }

        if (elem.second == "fn") {
            funawait = 2;
        }

        if (await) {
            await = 0;
            if (tid->is_contain_local(elem.second)) {
                dest.reverse();
                for (auto c: dest) {
                    lexems.push_back(c);
                }
                throw string("DeclarationError: Variable '" + elem.second + "' was already declared.\n");
            }
            VarVal e = VarVal();
            e.name = elem.second;
            e.type = type_;
            tid->add(e);

            if (funawait) {
                func_name = elem.second;
                funawait = 0;
            }
        }
        if (delay != 0) {
            delay--;

            if (delay == 0) {
                if (tid->is_contain_local(elem.second)) {
                    dest.reverse();
                    for (auto c: dest) {
                        lexems.push_back(c);
                    }
                    throw string("DeclarationError: Variable '" + elem.second + "' was already declared.\n");
                }
                VarVal e = VarVal();
                e.name = elem.second;
                e.type = "vector";
                tid->add(e);

                if (funawait) {
                    func_name = elem.second;
                    funawait = 0;
                }
            }
        } else {
            if (elem.second == "int") {
                await = 1;
                type_ = "int";
            } else if (elem.second == "double") {
                await = 1;
                type_ = "double";
            } else if (elem.second == "string") {
                await = 1;
                type_ = "string";
            }
        }
        if (elem.second == "vector") {
            vec_depth++;
            if (delay == 0) {
                delay = 4;
            } else {
                delay += 3;
            }
        }
        index++;
    }
}

#endif //LANGUAGE_SEMANTIC_ANALYZER_H
