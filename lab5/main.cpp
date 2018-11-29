#include <iostream>
#include <string>
using namespace std;

template <class T> class copy_ptr
{

public:
    copy_ptr() : m_ptr(nullptr) {}

    explicit copy_ptr(T* i_ptr) : m_ptr(i_ptr) {}

    template<class Y>
    copy_ptr(copy_ptr<Y>& other_ptr) : m_ptr(new T(*other_ptr)) {}

    template <class Y>
    copy_ptr<T>& operator=(const copy_ptr<Y>& other_ptr)
    {
        m_ptr = new T(*other_ptr);
        return *this;
    }


    /*copy_ptr<T>& operator=(const copy_ptr<typename remove_cv<T>::type>& other_ptr)
    {
        m_ptr = new T(*other_ptr);
        return *this;
    }

    copy_ptr<T>& operator=(const copy_ptr<const typename remove_cv<T>::type>& other_ptr)
    {
        m_ptr = new T(*other_ptr);
        return *this;
    }*/

    copy_ptr(copy_ptr<T>&& other_ptr) noexcept : m_ptr(other_ptr.get()) {}

    copy_ptr<T>& operator=(copy_ptr<T>&& other_ptr) noexcept
    {
        m_ptr = other_ptr.m_ptr;
        return *this;
    }

    ~copy_ptr()
    {
        delete m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }

    T& operator*() const
    {
        return *m_ptr;
    }

    T* get() const
    {
        return m_ptr;
    }

    void reset()
    {
        delete m_ptr;
        m_ptr = nullptr;
    }

    void reset(T* i_ptr)
    {
        if (m_ptr != i_ptr)
        {
            delete m_ptr;
            m_ptr = i_ptr;
        }
    }

    explicit operator bool() const
    {
        return m_ptr != nullptr;
    }

private:
    T* m_ptr;
};

template<typename T, typename... Args>
copy_ptr<T> make_copy(Args&&... args)
{
    return copy_ptr<T>(new T(forward<Args>(args)...));
}

int main() {
    copy_ptr<string>c(new string("string 1"));
    copy_ptr<string>b(c);
    (*b)[7] = '2';
    cout << *c << " " << *b << endl;

    string* test_str = new string ("string 3");
    copy_ptr<string>p1(test_str);
    copy_ptr<string>p2(test_str);
    copy_ptr<string>p3(move(p1));
    (*p2)[7] = '4';
    cout << *p2 << " " << *p3 << endl;

    copy_ptr<string> p4, p5;
    p5 = p4 = move(b);
    cout<<*p4<<" "<<*p5<<" "<<endl;
    cout<<endl;

    copy_ptr<string> p6 = make_copy<string>(5, 'c');
    copy_ptr<const string> p7 = p6;//make_copy<const string>(10,'a');
    //p7 = p6;
    cout<<*p6<<" "<<*p7<<endl;

    copy_ptr<string> p8 = make_copy<string>(5, 'c');
    copy_ptr<const string> p9 = make_copy<const string>(10,'a');
    p8 = p9;
    cout<<*p8<<" "<<*p9<<endl;

    return 0;
}