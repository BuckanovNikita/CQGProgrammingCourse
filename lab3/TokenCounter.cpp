//
// Created by nikita on 06.10.2018.
//

#include "TokenCounter.h"

typedef std::pair<int,int> range;

size_t TokenCounter::GetTokenCount() const {

    vector<range> range_set = {};

    for(int i=pattern.length(); i<prefix_function.size(); i++)
        if(prefix_function[i] == pattern.length())
            range_set.emplace_back(std::make_pair(i,i-pattern.length()));

    sort(range_set.begin(), range_set.end());
    size_t result = 0;
    int max_r = 0;

    for(const range& t : range_set)
    {
        if(t.second >= max_r)
        {
            ++result;
            max_r = std::max(max_r, t.first);
        }
    }
    return result;
}

void TokenCounter::operator()(const char& it) {
    if (cur_pos == 0)
    {
        ++cur_pos;
        search_string = it;
        prefix_function.push_back(0);
        return;
    }
    search_string += it;
    size_t matched_prefix = cur_pos-1;
    size_t candidate = prefix_function[matched_prefix];
    while( candidate !=0 && search_string[cur_pos] != search_string[candidate] )
    {
        matched_prefix = prefix_function[matched_prefix] - 1;
        candidate = prefix_function[matched_prefix];
    }
    if(candidate == 0)
        prefix_function.push_back((size_t)(search_string[cur_pos] == search_string[0]));
    else
        prefix_function.push_back(candidate + 1);
    ++cur_pos;
}

TokenCounter::TokenCounter(const string &pattern, const char &sep): cur_pos(0), pattern(pattern), search_string(""), prefix_function({}) {
    for(char t : pattern)
        operator()(t);
    operator()(sep);
}

