#pragma once

class Uncopyable
{
public:
    Uncopyable() {}
    ~Uncopyable() {}

private:
    Uncopyable(const Uncopyable &);
    const Uncopyable & operator=(const Uncopyable &);
};

