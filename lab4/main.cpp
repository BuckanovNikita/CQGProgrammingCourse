#include <iostream>
#include "Stream.cpp"
#include "fstream"
#include <random>
using std::string;
using std::cout;
using std::endl;
using std::pair;

int main() {
    std::ifstream f;
    std::setlocale(LC_ALL, "Rus");
    f.open("last_names.txt");
    vector<string> last_names;
    vector<string> first_names;
    while(f)
    {
        string c;
        f>>c;
        last_names.push_back(c);
    }
    f.close();

    f.open("first_names.txt");
    while(f)
    {
        string c;
        f>>c;
        first_names.push_back(c);
    }

    Stream<size_t> r1 = GetRandomStream(std::default_random_engine(2344), std::uniform_int_distribution<size_t>(0, first_names.size()-1));
    Stream<size_t> r2 = GetRandomStream(std::default_random_engine (2366), std::uniform_int_distribution<size_t>(0, last_names.size()-1));

    cout<<"Seed test:"<<endl;
    for (const auto &q : Take(r1, 10))
        cout<<q<<" ";
    cout<<endl;

    for (const auto &q : Take(r1, 20))
        cout<<q<<" ";
    cout<<endl;
    cout<<endl;

    Stream<pair<size_t, size_t>> r_zip = Zip(r1, r2);
    Stream<pair<string, string>> names = Map(r_zip, [&last_names, &first_names](pair<size_t, size_t> p)
    { return make_pair(first_names[p.first], last_names[p.second]);});
    Stream<pair<string,string>> filtered_names = Filter(names, [](pair<string, string> p){ return p.first[0] != p.second[0];});
    int i = 0;
    for (const auto &q : Take(filtered_names, 20))
        cout<<++i<<" "<<q.first<<" "<<q.second<<endl;
    return 0;
}