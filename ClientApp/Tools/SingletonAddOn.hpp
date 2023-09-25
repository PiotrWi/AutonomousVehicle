#pragma once

template <typename Type>
class SingletonAddOn
{
public:
    static Type& getInstance()
    {
        static Type obj;
        return obj;
    }
};