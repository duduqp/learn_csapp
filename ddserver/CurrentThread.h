#pragma once
#include <iostream>
using namespace std;
namespace CurrentThread{
extern __thread int t_cached_tid;
void Cachetid();

inline int tid()
{

    std::cout << __func__<<std::endl;
    if (__builtin_expect(t_cached_tid == 0, 0)) {
        Cachetid();
    }
    std::cout << t_cached_tid << std::endl;
    return t_cached_tid;
}
}
