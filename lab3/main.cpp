#include <iostream>
#include "TokenCounter.h"
#include <string>
#include <cassert>
using namespace std;

size_t test(const string &pattern, const string &str)
{
    return for_each(str.begin(), str.end(), TokenCounter(pattern)).GetTokenCount();
}

int main() {
    assert (test("tt", "tnnnttnnntnnntttnnttttnn") == 4);
    assert (test("a", "bbbbbbbbbbbbbbbbb") == 0);
    assert (test("a", "aaaa") == 4);
    assert (test("abca", "abcabca") == 1);
    assert (test("abca", "abcaabca") == 2);
    return 0;
}