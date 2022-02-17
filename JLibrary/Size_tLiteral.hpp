// JLibrary
// Size_tLiteral.hpp
// Created on 2022-02-14 by Justyn Durnford
// Last modified on 2022-02-14 by Justyn Durnford
// 

#pragma once

#include <cstddef>

#ifdef _WIN64

    constexpr std::size_t operator "" _uz(unsigned long long n)
    {
        return n;
    }

#endif // #ifdef _WIN64