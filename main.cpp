#include <iostream>
#include "semantic_analyzer.h"
#include "generation.h"

int main(int argc, char *argv[]) {
    try {
        auto res = Make_Lexems();
//        Check_Syntax(res);
//        Check_Semantic(res);
//        res.emplace_back(0, "}");
        generation(res);
    } catch (string& s) {
        string filename = argv[0];

        cerr << "\tFile \"<" << filename << ">\" panicked at line " << to_string(cur_num) << ":" << endl;
        cerr << result;

        if (in_get) {
            cerr << str << ' ';
            err_num++;
        } else {
            err_num -= str.size() + 1;
        }
        auto q = nums;
        if (q.empty()) {
            q = nums_mem;
        }
        if (!lexems.empty()) {
            while (cur_num == q.back()) {
                cur_num = q.back();
                q.pop_back();
                cerr << lexems.back().second << ' ';
                lexems.pop_back();
            }
        }
        cerr << endl << "\t\t";
        for (int i = 0; i < err_num; ++i) {
            cerr << " ";
        }
        cerr << "^" << endl << s << endl;
    }
    return 0;
}
