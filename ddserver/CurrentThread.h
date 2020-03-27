#pragma once
namespace CurrentThread{
extern __thread int t_cached_tid;
void Cachetid();

inline int tid()
{
    return t_cached_tid;
}
}
