//
// Created by nikita on 06.10.2018.
//
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>

using std::for_each;
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

#ifndef LAB3_TOKENCOUNTER_H
#define LAB3_TOKENCOUNTER_H


class TokenCounter {

    public:

        explicit TokenCounter(const string& pattern, const char &sep='$');

        void operator() (const char& it);

        size_t GetTokenCount() const;

    private:

        size_t cur_pos;

        string search_string;

        string pattern;

        vector<size_t> prefix_function;
};


#endif //LAB3_TOKENCOUNTER_H
