//
// Created by afentev on 4/23/21.
//

#ifndef LANGUAGE_GENERATION_H
#define LANGUAGE_GENERATION_H

#include "semantic_analyzer.h"

std::string run(std::map<std::string, std::vector<std::string>>, std::vector<std::string>,
         std::map<std::string, std::tuple<std::string, std::string, bool, std::string>>);

std::string doubleToString(long double s) {
    std::stringstream ss(stringstream::in | stringstream::out);
    ss << std::setprecision(16) << s;
    return ss.str();
}

std::string getType(std::string s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    if (!s.empty() && it == s.end()) {
        return "int";
    }

    char* p = nullptr;
    std::strtof(s.data(), &p);
    if (p == s.data() + s.size()) {
        return "double";
    }

    return "string";
    if (s.size() > 2) {
        if (s[1] == '"' && s[s.size() - 1] == '"') {
            return "string";
        }
    }
}

bool AreTypesCompatible (const std::string& t1, const std::string& t2, const std::string& op) {
    if (op == "//" || op == "%" || op == "|" || op == "||" || op == "&" || op == "&&" || op == "^" || op == "<<" ||
                        op == ">>" || op == "%=" || op == "|=" || op == "&=" || op == "^=") {
        if (!is_correct_hdivision(t1, t2)) {
            dest.reverse();
            for (auto c: dest) {
                lexems.push_back(c);
            }
            throw string("TypeError: unsupported operand type(s) for " + op + ": '" + t1 + "' and '" + t2 + "'");
        }
        return true;
    } else if (op == ">" || op == "<" || op == ">=" || op == "<=" ||
               op == "==" || op == "!=" || op == "+" || op == "+=") {
        if (!is_correct_addition(t1, t2)) {
            dest.reverse();
            for (auto c: dest) {
                lexems.push_back(c);
            }
            throw string("TypeError: unsupported operand type(s) for " + op + ": '" + t1 + "' and '" + t2 + "'");
        }
        return true;
    } else if (op == "~") {
        if (t1 != "int") {
            dest.reverse();
            for (auto c: dest) {
                lexems.push_back(c);
            }
            throw string("TypeError: bad operand type for unary ~: '" + t2 + "'");
        }
        return true;
    } else if (op == "-" || op == "-=") {
        if (!is_correct_division(t1, t2)) {
            dest.reverse();
            for (auto c: dest) {
                lexems.push_back(c);
            }
            throw string("TypeError: unsupported operand type(s) for " + op + ": '" + t1 + "' and '" + t2 + "'");
        }
        return true;
    } else if (op == "*" || op == "*=") {
        if (!is_correct_mult(t1, t2)) {
            dest.reverse();
            for (auto c: dest) {
                lexems.push_back(c);
            }
            throw string("TypeError: unsupported operand type(s) for " + op + ": '" + t1 + "' and '" + t2 + "'");
        }
        return true;
    } else if (op == "/" || op == "/=") {
        if (!is_correct_division(t1, t2)) {
            dest.reverse();
            for (auto c: dest) {
                lexems.push_back(c);
            }
            throw string("TypeError: unsupported operand type(s) for " + op + ": '" + t1 + "' and '" + t2 + "'");
        }
        return true;
    } else if (op == "**") {
        if (!is_correct_division(t1, t2)) {
            dest.reverse();
            for (auto c: dest) {
                lexems.push_back(c);
            }
            throw string("TypeError: unsupported operand type(s) for " + op + ": '" + t1 + "' and '" + t2 + "'");
        }
        return true;
    } else if (op == "=") {
        if (!is_correct_assignment(t1, t2)) {
            dest.reverse();
            for (auto c: dest) {
                lexems.push_back(c);
            }
            throw string("TypeError: assignment type missmatch: '" + t1 + "' expected, but '" + t2 + "' found");
        }
        return true;
    }
}

std::pair<std::string, std::string> makeOperation(const std::string& raw1, const std::string& raw2,
                                                  const std::string& t1, const std::string& t2,
                                                  const std::string& op) {
    AreTypesCompatible(t1, t2, op);
    if (op == "//") {
        return {"int", std::to_string(std::stoi(raw1) / std::stoi(raw2))};
    } else if (op == "%") {
        return {"int", std::to_string(std::stoi(raw1) % std::stoi(raw2))};
    } else if (op == "|") {
        return {"int", std::to_string(std::stoi(raw1) | std::stoi(raw2))};
    } else if (op == "||") {
        return {"int", std::to_string(std::stoi(raw1) || std::stoi(raw2))};
    } else if (op == "&") {
        return {"int", std::to_string(std::stoi(raw1) & std::stoi(raw2))};
    } else if (op == "&&") {
        return {"int", std::to_string(std::stoi(raw1) && std::stoi(raw2))};
    } else if (op == "^") {
        return {"int", std::to_string(std::stoi(raw1) ^ std::stoi(raw2))};
    } else if (op == "<<") {
        return {"int", std::to_string(std::stoi(raw1) << std::stoi(raw2))};
    } else if (op == ">>") {
        return {"int", std::to_string(std::stoi(raw1) >> std::stoi(raw2))};
    } else if (op == ">") {
        return {"int", std::to_string(std::stold(raw1) > std::stold(raw2))};
    } else if (op == "<") {
        return {"int", std::to_string(std::stold(raw1) < std::stold(raw2))};
    } else if (op == ">=") {
        return {"int", std::to_string(std::stold(raw1) >= std::stold(raw2))};
    } else if (op == "<=") {
        return {"int", std::to_string(std::stold(raw1) <= std::stold(raw2))};
    } else if (op == "==") {
        return {"int", std::to_string(std::stold(raw1) == std::stold(raw2))};
    } else if (op == "!=") {
        return {"int", std::to_string(std::stold(raw1) != std::stold(raw2))};
    } else if (op == "+") {
        if (t1 == "string" && t2 == "string") {
            return {"string", "\"" + raw1.substr(1, static_cast<int> (raw1.size()) - 2)
            + raw2.substr(1, static_cast<int> (raw2.size()) - 2) + "\""};
        } else if (t1 == "int" && t2 == "int") {
            return {"int", std::to_string(std::stoi(raw1) + std::stoi(raw2))};
        } else {
            return {"double", doubleToString(std::stold(raw1) + std::stold(raw2))};
        }
    } else if (op == "-") {
        if (t1 == "int" && t2 == "int") {
            return {"int", std::to_string(std::stoi(raw1) - std::stoi(raw2))};
        } else {
            return {"double", doubleToString(std::stold(raw1) - std::stold(raw2))};
        }
    } else if (op == "*") {
        if (t1 == "int" && t2 == "int") {
            return {"int", std::to_string(std::stoi(raw1) * std::stoi(raw2))};
        } else {
            return {"double", doubleToString(std::stold(raw1) * std::stold(raw2))};
        }
    } else if (op == "/") {
        return {"double", doubleToString(std::stold(raw1) / std::stold(raw2))};
    } else if (op == "**") {
        if (t1 == "int" && t2 == "int") {
            return {"int", std::to_string(static_cast<int> (std::pow(std::stoi(raw1),
                                                                     std::stoi(raw2))))};
        } else {
            return {"double", doubleToString(std::pow(std::stold(raw1), std::stold(raw2)))};
        }
    }
}

std::map<std::string, int> priority {
    std::make_pair("(", -100),
    std::make_pair("=", 0),
    std::make_pair("+=", 0),
    std::make_pair("-=", 0),
    std::make_pair("*=", 0),
    std::make_pair("/=", 0),
    std::make_pair("%=", 0),
    std::make_pair("|=", 0),
    std::make_pair("&=", 0),
    std::make_pair("^=", 0),
    std::make_pair("||", 1),
    std::make_pair("&&", 2),
    std::make_pair("|", 3),
    std::make_pair("^", 4),
    std::make_pair("&", 5),
    std::make_pair("==", 6),
    std::make_pair("!=", 6),
    std::make_pair("<", 7),
    std::make_pair("<=", 7),
    std::make_pair(">", 7),
    std::make_pair(">=", 7),
    std::make_pair("<<", 8),
    std::make_pair(">>", 8),
    std::make_pair("+", 9),
    std::make_pair("-", 9),
    std::make_pair("*", 10),
    std::make_pair("/", 10),
    std::make_pair("%", 10),
    std::make_pair("//", 10),
    std::make_pair("**", 11),
    std::make_pair("++", 12),
    std::make_pair("--", 12),
    std::make_pair("!", 12),
    std::make_pair("~", 12),
    std::make_pair(".", 13),
    std::make_pair("return", -1)
};

std::map<std::string, int> functions {
    std::make_pair("print", 1),
    std::make_pair("read", 1),
    std::make_pair("return", 1)
};

std::map<std::string, std::vector<std::pair<std::string, std::string>>> functionsVars;

void generation(vector<pair<int, string>> &lexems) {
    int delay = 0;
    std::stack<std::string> s;
    std::vector<std::string> vec;

    std::string type;
    bool decl = false;

    std::stack<std::tuple<int, int, int, int>> whileBegin;
    std::stack<std::vector<int>> breaks;
    std::stack<int> loopOnly;
    // first - vec size before while; second - vec size after condition; third - "{" balance; =
    // fourth - is it "IF" (0 - false, 1 - true, 2 - elseawait)

    int figBracesBalance = 0;
    bool whileCondition = false;
    int forCondition = 0;
    int forConditionIndex = 0;
    int forStepIndex = 0;
    bool ifCondition = false;
    bool elseAwait = false;

    auto tid = new TID;
    tid->init();
    tid = tid->add_block();

    int funcDescription = 0;
    std::string funcName;
    
    std::map<std::string, std::tuple<std::string, std::string, bool, std::string>> tidID;
    // key - id
    // value[0] - type
    // value[1] - value
    // value[2] - isInitialized
    // value[3] - name

    std::map<std::string, std::vector<std::string>> RPN;

    for (auto& x: lexems) {
        if (funcDescription == 3) {
            funcDescription--;
            continue;
        } else if (funcDescription == 2) {
            funcName = x.second;
            funcDescription--;
            continue;
        }
//        if (delay) {
//            delay--;
//            continue;
//        }

        if (elseAwait) {
            elseAwait = false;
            if (x.second == "else") {
                vec.emplace_back("0");
                vec.emplace_back("!!");

                std::string temp = vec[std::get<0>(whileBegin.top())];
                if (temp[0] == '@') {
                    temp = temp.substr(1, static_cast<int> (temp.size()) - 1);
                }
                vec[std::get<0>(whileBegin.top())] = "@" + std::to_string(std::stoi(temp) + 2);
                std::get<0>(whileBegin.top()) = static_cast<int>(vec.size()) - 2;
                std::get<3>(whileBegin.top()) = 2;
                elseAwait = false;
                continue;
            } else {
                whileBegin.pop();
            }
        }

        if (x.second == "{") {
            if (whileCondition) {
                vec.emplace_back("0");
                vec.emplace_back("!?");
                std::get<1>(whileBegin.top()) = static_cast<int>(vec.size()) - 2;
                whileCondition = false;
            }
            if (forCondition == 1) {
                forCondition--;
            } else {
                if (funcDescription) {
                    funcDescription = 0;
                } else {
                    tid = tid->add_block();
                }
            }
            figBracesBalance++;
            continue;
        } else if (x.second == "}") {
            tid = tid->parent;
            if (!whileBegin.empty() && std::get<3>(whileBegin.top()) == 1) {
                vec[std::get<0>(whileBegin.top())] = "@" + std::to_string(vec.size());
                elseAwait = true;
            } else if (!whileBegin.empty() && std::get<3>(whileBegin.top()) == 2) {
                vec[std::get<0>(whileBegin.top())] = "@" + std::to_string(vec.size());
                whileBegin.pop();
            } else if (!whileBegin.empty() && figBracesBalance - 1 == std::get<2>(whileBegin.top())) {
                vec.push_back("@" + std::to_string(std::get<0>(whileBegin.top())));
                vec.emplace_back("!!");
                vec[std::get<1>(whileBegin.top())] = "@" + std::to_string(vec.size());

                for (int ind: breaks.top()) {
                    vec[ind] = vec[std::get<1>(whileBegin.top())] = "@" + std::to_string(vec.size());
                }

                whileBegin.pop();
                loopOnly.pop();
                breaks.pop();
            }
            figBracesBalance--;

            if (figBracesBalance == 0) {
                RPN[funcName] = vec;
                vec.clear();
                while (!s.empty()) {
                    s.pop();
                }
            }
            continue;
        }

        if (x.second == "while") {
            whileBegin.emplace(vec.size(), 0, figBracesBalance, 0);
            loopOnly.emplace(vec.size());
            breaks.emplace();
            whileCondition = true;
        } else if (x.second == "for") {
            tid = tid->add_block();
            whileBegin.emplace(vec.size(), 0, figBracesBalance, 0);
            loopOnly.emplace(vec.size());
            breaks.emplace();
            forCondition = 4;
        } else if (x.second == "continue") {
            vec.push_back("@" + std::to_string(loopOnly.top()));
            vec.emplace_back("!!");
        } else if (x.second == "break") {
            vec.emplace_back("0");
            vec.emplace_back("!!");
            breaks.top().push_back(static_cast<int>(vec.size()) - 2);
        } else if (x.second == "if") {
            ifCondition = true;
        } else if (x.second == "fn") {
            funcDescription = 3;
            tid = tid->add_block();
//            delay = 5;
        } else if (decl) {
            decl = false;
            if (tid->is_contain_local(x.second)) {
                throw std::string("DeclarationError: Variable '" + x.second + "' was already declared.\n");
            } else {
                VarVal e = VarVal();
                e.name = x.second;
                e.type = type;
                e.init = false;

                std::string old = x.second;
                x.second = tid->add(e);

                if (funcDescription == 1) {
                    functionsVars[funcName].push_back({x.second, type});
                    tidID[x.second] = std::make_tuple(type, "", true, old);
                } else {
                    tidID[x.second] = std::make_tuple(type, "", false, old);
                }
            }
            s.push(x.second);
        } else if (x.second == "int" || x.second == "string" || x.second == "double") {
            decl = true;
            type = x.second;
        } else if (x.second == "=" || x.second == "+=" || x.second == "-=" || x.second == "*=" || x.second == "/=" ||
                                x.second == "%=" || x.second == "|=" || x.second == "&=" || x.second == "^=" ||
                                x.second == "**") {  // right-associative
            while (!s.empty() && (!priority.contains(s.top()) || priority.at(s.top()) > priority.at(x.second))) {
                vec.push_back(s.top());
                s.pop();
            }
            s.push(x.second);
        } else if (x.second == "||" || x.second == "&&" || x.second == "|" || x.second == "^" || x.second == "&" ||
                   x.second == "==" || x.second == "!=" || x.second == "<" || x.second == "<=" || x.second == ">" ||
                   x.second == ">=" || x.second == "<<" || x.second == ">>" || x.second == "+" || x.second == "-" ||
                   x.second == "*" || x.second == "/" || x.second == "%" || x.second == "//" || x.second == "++" ||
                   x.second == "--" || x.second == "!" || x.second == "~" || x.second == ".") {  // left-associative
            while (!s.empty() && (!priority.contains(s.top()) || priority.at(s.top()) >= priority.at(x.second))) {
                vec.push_back(s.top());
                s.pop();
            }
            s.push(x.second);
        } else if (x.second == "(" || x.second == "return") {
            s.push(x.second);
        } else if (x.second == ")") {
            if (funcDescription) {
                functions[funcName] = static_cast<int> (functionsVars[funcName].size());
            }
            if (forCondition == 2) {
                std::get<0>(whileBegin.top()) = loopOnly.top() = forStepIndex + 2;
            }

            while (!s.empty() && s.top() != "(") {
                vec.push_back(s.top());
                s.pop();
            }

            if (forCondition == 2) {
                vec.emplace_back("@" + std::to_string(forConditionIndex));
                vec.emplace_back("!!");
                vec[forStepIndex] = "@" + std::to_string(vec.size());
                forCondition--;
            }

            if (ifCondition) {
                vec.emplace_back("0");
                vec.emplace_back("!?");
                whileBegin.emplace(static_cast<int>(vec.size()) - 2, 0, 0, 1);
                ifCondition = false;
            }

            if (s.empty()) {
//                throw std::string("GenerationError: Unbalanced braces");
            } else {
                s.pop();
                if (!s.empty()) {
                    std::string isFunc = s.top();
                    if (functions.contains(isFunc)) {
                        s.pop();
                        vec.push_back(isFunc);
                    }
                }
            }
        } else if (x.second == ";") {
            while (!s.empty()) {
                if (forCondition && s.top() == "(") {
                    break;
                }
                vec.push_back(s.top());
                s.pop();
            }

            if (forCondition == 4) {
                forCondition--;
                forConditionIndex = static_cast<int>(vec.size());
            } else if (forCondition == 3) {
                vec.emplace_back("0");
                vec.emplace_back("!?");
                std::get<1>(whileBegin.top()) = static_cast<int>(vec.size()) - 2;
                forStepIndex = static_cast<int>(vec.size());
                vec.emplace_back("0");
                vec.emplace_back("!!");
                forCondition--;
            }
        } else {
            if (tid->is_contain(x.second)) {
                s.push(std::get<2> (tid->get_all(x.second)));
            } else {
                if (x.second == ",") {
                    while (!s.empty() && s.top() != "(") {
                        vec.push_back(s.top());
                        s.pop();
                    }
                } else {
                    s.push(x.second);
                }
//                vec.push_back(x.second);
            }
        }
    }

    vec = RPN["ternSearch"];

    for (const auto& x: vec) {
        std::cout << x << ' ';
    }
    std::cout << std::endl << std::endl;

    run(RPN, vec, tidID);

//    std::cout << std::get<1> (tidID["&0"]) << std::endl;
}

std::string run(std::map<std::string, std::vector<std::string>> RPN, std::vector<std::string> vec,
std::map<std::string, std::tuple<std::string, std::string, bool, std::string>> tidID) {
    std::stack<std::string> handler;
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == "=") {
            std::string el1 = handler.top(); handler.pop();
            std::string el2 = handler.top(); handler.pop();

            std::string t, t2;
            if (el1[0] == '&') {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t = std::get<0> (res);
            } else {
                t = getType(el1);

            }
            if (el2[0] == '&') {
                auto res = tidID[el2];
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            if (AreTypesCompatible(t2, t, vec[i])) {
                if (t == "double" && t2 == "int") {
                    el1 = std::to_string(static_cast<int> (std::stold(el1)));
                } else if (t == "int" && t2 == "double") {
                    el1 += ".0";
                }
                std::get<1> (tidID[el2]) = el1;
                std::get<2> (tidID[el2]) = true;
            }
        } else if (vec[i] == "+=") {
            std::string el1 = handler.top(); handler.pop();
            std::string el2 = handler.top(); handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t1 = std::get<0> (res);
                el1 = std::get<1> (tidID[el1]);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t2 = std::get<0> (res);
            } else {
                throw std::string("InternalMemoryError: Use of uninitialized variable \"" + el1.substr(
                        1,static_cast<int> (el1.size()) - 1)) + "\" (bad access)";
            }
            auto res = makeOperation(std::get<1> (tidID[el2]), el1, t2, t1, "+");
            tidID[el2] = {res.first, res.second, true, std::get<3> (tidID[el2])};
        } else if (vec[i] == "-=") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t1 = std::get<0> (res);
                el1 = std::get<1> (tidID[el1]);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t2 = std::get<0> (res);
            } else {
                throw std::string("InternalMemoryError: Use of uninitialized variable \"" + el1.substr(
                        1,static_cast<int> (el1.size()) - 1)) + "\" (bad access)";
            }
            auto res = makeOperation(std::get<1> (tidID[el2]), el1, t2, t1, "-");
            tidID[el2] = {res.first, res.second, true, std::get<3> (tidID[el2])};
        } else if (vec[i] == "*=") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t1 = std::get<0> (res);
                el1 = std::get<1> (tidID[el1]);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t2 = std::get<0> (res);
            } else {
                throw std::string("InternalMemoryError: Use of uninitialized variable \"" + el1.substr(
                        1,static_cast<int> (el1.size()) - 1)) + "\" (bad access)";
            }
            auto res = makeOperation(std::get<1> (tidID[el2]), el1, t2, t1, "*");
            tidID[el2] = {res.first, res.second, true, std::get<3> (tidID[el2])};
        } else if (vec[i] == "/=") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t1 = std::get<0> (res);
                el1 = std::get<1> (tidID[el1]);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t2 = std::get<0> (res);
            } else {
                throw std::string("InternalMemoryError: Use of uninitialized variable \"" + el1.substr(
                        1,static_cast<int> (el1.size()) - 1)) + "\" (bad access)";
            }
            auto res = makeOperation(std::get<1> (tidID[el2]), el1, t2, t1, "/");
            tidID[el2] = {res.first, res.second, true, std::get<3> (tidID[el2])};
        } else if (vec[i] == "%=") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t1 = std::get<0> (res);
                el1 = std::get<1> (tidID[el1]);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t2 = std::get<0> (res);
            } else {
                throw std::string("InternalMemoryError: Use of uninitialized variable \"" + el1.substr(
                        1,static_cast<int> (el1.size()) - 1)) + "\" (bad access)";
            }
            auto res = makeOperation(std::get<1> (tidID[el2]), el1, t2, t1, "%");
            tidID[el2] = {res.first, res.second, true, std::get<3> (tidID[el2])};
        } else if (vec[i] == "|=") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t1 = std::get<0> (res);
                el1 = std::get<1> (tidID[el1]);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t2 = std::get<0> (res);
            } else {
                throw std::string("InternalMemoryError: Use of uninitialized variable \"" + el1.substr(
                        1,static_cast<int> (el1.size()) - 1)) + "\" (bad access)";
            }
            auto res = makeOperation(std::get<1> (tidID[el2]), el1, t2, t1, "|");
            tidID[el2] = {res.first, res.second, true, std::get<3> (tidID[el2])};
        } else if (vec[i] == "&=") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t1 = std::get<0> (res);
                el1 = std::get<1> (tidID[el1]);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t2 = std::get<0> (res);
            } else {
                throw std::string("InternalMemoryError: Use of uninitialized variable \"" + el1.substr(
                        1,static_cast<int> (el1.size()) - 1)) + "\" (bad access)";
            }
            auto res = makeOperation(std::get<1> (tidID[el2]), el1, t2, t1, "&");
            tidID[el2] = {res.first, res.second, true, std::get<3> (tidID[el2])};
        } else if (vec[i] == "^=") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t1 = std::get<0> (res);
                el1 = std::get<1> (tidID[el1]);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                t2 = std::get<0> (res);
            } else {
                throw std::string("InternalMemoryError: Use of uninitialized variable \"" + el1.substr(
                        1,static_cast<int> (el1.size()) - 1)) + "\" (bad access)";
            }
            auto res = makeOperation(std::get<1> (tidID[el2]), el1, t2, t1, "^");
            tidID[el2] = {res.first, res.second, true, std::get<3> (tidID[el2])};
        } else if (vec[i] == "||") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "||").second);
        } else if (vec[i] == "&&") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "&&").second);
        } else if (vec[i] == "|") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "|").second);
        } else if (vec[i] == "^") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "^").second);
        } else if (vec[i] == "&") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "&").second);
        } else if (vec[i] == "==") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "==").second);
        } else if (vec[i] == "!=") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "!=").second);
        } else if (vec[i] == "<") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "<").second);
        } else if (vec[i] == "<=") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "<=").second);
        } else if (vec[i] == ">") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, ">").second);
        } else if (vec[i] == ">=") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, ">=").second);
        } else if (vec[i] == "<<") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "<<").second);
        } else if (vec[i] == ">>") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, ">>").second);
        } else if (vec[i] == "+") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "+").second);
        } else if (vec[i] == "-") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "-").second);
        } else if (vec[i] == "*") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "*").second);
        } else if (vec[i] == "/") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "/").second);
        } else if (vec[i] == "%") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "%").second);
        } else if (vec[i] == "//") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "//").second);
        } else if (vec[i] == "**") {
            std::string el1 = handler.top();
            handler.pop();
            std::string el2 = handler.top();
            handler.pop();
            std::string t2, t1;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el1 = std::get<1> (res);
                t1 = std::get<0> (res);
            } else {
                t1 = getType(el1);
            }
            if (tidID.contains(el2)) {
                auto res = tidID[el2];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                el2 = std::get<1> (res);
                t2 = std::get<0> (res);
            } else {
                t2 = getType(el2);
            }
            handler.push(makeOperation(el2, el1, t2, t1, "**").second);
        } else if (vec[i] == "++") {
            std::string el1 = handler.top();
            handler.pop();
            std::string val, t;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                val = std::get<1> (res);
                t = std::get<0> (res);
            } else {
                throw std::string("InternalMemoryError: Use of uninitialized variable \"" + el1.substr(
                        1,static_cast<int> (el1.size()) - 1)) + "\" (bad access)";
            }
            auto res = makeOperation(val, "1", t, "int", "+");
            tidID[el1] = {res.first, res.second, true, el1};
            handler.push(res.second);
        } else if (vec[i] == "--") {
            std::string el1 = handler.top();
            handler.pop();
            std::string val, t;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2> (res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3> (res) + "\"");
                }
                val = std::get<1> (res);
                t = std::get<0> (res);
            } else {
                throw std::string("InternalMemoryError: Use of uninitialized variable \"" + el1.substr(
                        1,static_cast<int> (el1.size()) - 1)) + "\" (bad access)";
            }
            auto res = makeOperation(val, "1", t, "int", "-");
            tidID[el1] = {res.first, res.second, true, el1};
            handler.push(res.second);
        } else if (vec[i] == "!!") {
            std::string address = vec[i - 1];
            address = address.substr(1, static_cast<int> (address.size()) - 1);
            i = std::stoi(address) - 1;
        } else if (vec[i] == "!?") {
            if (handler.top() == "1") {
                continue;
            }
            std::string address = vec[i - 1];
            address = address.substr(1, static_cast<int> (address.size()) - 1);
            i = std::stoi(address) - 1;
        } else if (vec[i][0] == '?' || vec[i][0] == '!' || vec[i][0] == '@') {
            continue;
        } else if (vec[i] == "print") {
            std::string el1 = handler.top();
            handler.pop();
            std::string val;
            if (tidID.contains(el1)) {
                auto res = tidID[el1];
                if (!(std::get<2>(res))) {
                    throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3>(res) + "\"");
                }
                if (std::get<0> (res) == "string") {
                    std::string tmp = std::get<1>(res);
                    val = tmp.substr(1, static_cast<int> (tmp.size()) - 2);
                } else {
                    val = std::get<1>(res);
                }
            } else {
                val = el1;
            }
            while (val.find("\\n") != std::string::npos) {
                val.replace(val.find("\\n"), 2, "\n");
            }
            std::cout << val;
        } else if (vec[i] == "read") {
            std::string el1 = handler.top();
            handler.pop();
            std::string val;
            if (tidID.contains(el1)) {
                std::string st;
                std::cin >> st;
                auto r1 = tidID[el1];
                std::string typeFound = getType(st);
                std::string typeRequired = std::get<0>(r1);
                if (typeFound == "string" && typeRequired != "string" ||
                    typeFound != "string" && typeRequired == "string" ||
                    typeFound == "double" && typeRequired == "int") {
                    throw std::string(
                            "InputError: type \"" + std::get<0>(r1) +
                            "\" expected, but \"" + getType(st) + "\" found");
                }
                tidID[el1] = {std::get<0>(r1), st, true, std::get<3>(r1)};
            } else {
                val = el1;
            }
            std::cout << val;
        } else if (functions.contains(vec[i])) {
            if (vec[i] == "return") {
                std::string el2 = handler.top();
                if (tidID.contains(el2)) {
                    auto res = tidID[el2];
                    if (!(std::get<2>(res))) {
                        throw std::string("MemoryError: Use of uninitialized variable \"" + std::get<3>(res) + "\"");
                    }
                    el2 = std::get<1>(res);
                }
                return el2;
            }
            std::vector<std::string> args;
            for (int index = 0; index < functions[vec[i]]; ++index) {
                args.push_back(handler.top());
                handler.pop();
            }
            std::reverse(args.begin(), args.end());

            for (int index = 0; index < args.size(); ++index) {
                std::string el2 = args[index];
                if (tidID.contains(el2)) {
                    auto res = tidID[el2];
                    el2 = std::get<1>(res);
                }
                std::string typeFound = getType(el2);
                std::string typeRequired = functionsVars[vec[i]][index].second;
                if (typeFound == "string" && typeRequired != "string" ||
                    typeFound != "string" && typeRequired == "string" ||
                    typeFound == "double" && typeRequired == "int") {
                    throw std::string(
                            "ArgumentPassError: type \"" + typeRequired +
                            "\" expected, but \"" + typeFound + "\" found");
                }
                tidID[functionsVars[vec[i]][index].first] = {functionsVars[vec[i]][index].second, el2,
                                                             true,
                                                             functionsVars[vec[i]][index].first};
            }
            handler.push(run(RPN, RPN[vec[i]], tidID));

            // return values back (recursion problem)
            for (int index = 0; index < args.size(); ++index) {
                std::string el2 = args[index];
                if (tidID.contains(el2)) {
                    auto res = tidID[el2];
                    el2 = std::get<1>(res);
                }
                tidID[functionsVars[vec[i]][index].first] = {functionsVars[vec[i]][index].second, el2,
                                                             true,
                                                             functionsVars[vec[i]][index].first};
            }
        } else {
            handler.push(vec[i]);
        }
    }
    return "";
}

#endif //LANGUAGE_GENERATION_H


// b  0  =  b  5  <  @19  !?  @14  !!  b  ++  @3  !!  b  1  +=  @10  !!  return  0
// 0  1  2  3  4  5  6    7   8    9   10 11  12  13 14 15  16  17   18  19     20

// i  1  =  i  1  ==  13  !?  i  1  +=  @16  !!  i  2  +=  return  0
// 0  1  2  3  4  5   6   7   8  9  10  11   12 13 14  15  16      17