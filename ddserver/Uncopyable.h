#pragma once

class Uncopyable
{
protected:
    Uncopyable() {}
    ~Uncopyable() {}

private:
    Uncopyable(const Uncopyable &);
    const Uncopyable & operator=(const Uncopyable &);
};

