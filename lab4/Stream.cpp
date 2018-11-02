//
// Created by nikita on 16.10.2018.
//
#include <functional>
#include <vector>
#include <type_traits>
#include <random>
using std::vector;

template<class T>
struct Stream
{
    Stream(T current, std::function<Stream<T>()> next) : current(current), next(next) {}
    T current;
    std::function<Stream<T>()> next;
};

template<class T>
vector<T> Take(Stream<T> stream, size_t n)
{
    vector<T> result = vector<T>();
    result.reserve(n);
    for(int i=0; i<n; i++)
    {
        result.push_back(stream.current);
        stream = stream.next();
    }
    return result;
}

template<class T, class TFn>
Stream <std::decay_t<std::invoke_result_t <TFn, T>>> Map(Stream<T> stream, TFn f)
{
    return Stream <std::decay_t<std::invoke_result_t <TFn, T>>>(f(stream.current), [=](){return Map(stream.next(), f);});
};

template<class T1, class T2>
Stream<std::pair<T1, T2>> Zip(Stream<T1> s1, Stream<T2> s2)
{
    return Stream<std::pair<T1, T2>>(std::make_pair(s1.current, s2.current), [=]{return Zip(s1.next(), s2.next());});
}


template<class T, class TFn>
Stream<T> Filter(Stream<T> s, TFn pred)
{
    while( !pred(s.current) )
        s = s.next();
    return Stream<T>( s.current, [=]()
    {
        return Filter(s.next(), pred);
    });
}

template <class T>
Stream<T> GetRandomStream(std::default_random_engine generator, std::uniform_int_distribution<T> distribution)
{
    T val = distribution(generator);
    //std::default_random_engine g1 = generator;
    //std::uniform_int_distribution<T> d1 = distribution;
    return Stream<T>(val, [=](){return GetRandomStream(generator, distribution);});
}