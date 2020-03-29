#pragma once
#include <memory>
//singleton wrapper
template<class T,class X=void,int N=0>
class Singleton{
public:
    static T * GetInstanceRaw()
    {
        static T * v=new T;
        return v;
    }

    static std::shared_ptr<T> GetInstanceSMT()
    {
        static std::shared_ptr<T> v(std::make_shared<T>());
        return v;
    }
};
