#pragma once

#include <cstddef>
#include <string_view>
#include <array>
#include<algorithm>
#include <cstring>

/*
template<std::size_t N>
struct FixedString {
     char p[N];

    constexpr FixedString(const char* str, std::size_t length) {
        std::ranges::copy(str, str+length, p);
    }

    constexpr FixedString(char const(&pp)[N]) {
        std::ranges::copy(pp, p);
    }

    template<std::size_t s>
    constexpr FixedString(FixedString<s> other) {
        char q[N];
        for (int i = 0; i < s; ++i) {
            q[i] = other.p[i];
        }
        strcpy(p, q);
    }

    constexpr operator std::string_view() const {
        return p;
    }

    //constexpr friend auto operator<=>(const FixedString &f, const FixedString &s) = default;
};

template<FixedString a>
constexpr auto operator ""_cstr() {
    return a;
}*/


template<std::size_t max_length>
struct BufferString {
    char buffer_[std::min(256ul, max_length)];

    constexpr BufferString() noexcept = default;


    constexpr BufferString(const char (&str)[max_length]) {
        std::ranges::copy(str, &str[std::min(256ul, max_length)], buffer_);
        //        std::ranges::copy(str, str+max_length-1, buffer_);
    }

    constexpr explicit operator std::string_view() const {
        return buffer_;
    }


};

template<std::size_t N>
struct FixedString {


    constexpr FixedString(std::basic_string_view<char> view) {
        length = view.length();
        std::ranges::copy(view, b);
    }

    char b[std::min(N, 256ul)]{};
    std::size_t length = N;

    template<std::size_t M>
    constexpr FixedString(BufferString<M> fs) {
        length = M;
        std::ranges::copy(fs.buffer_, &fs.buffer_[M], b);
    }

    template<std::size_t M>
    constexpr FixedString(const char (&str)[M], std::size_t l):b{} {
        std::ranges::copy(str, &str[l], b);
    }

    constexpr operator std::string_view() const {
        return b;
    }

    //constexpr friend auto operator<=>(const FixedString &f, const FixedString &s) = default;
};

template<BufferString a>
constexpr auto operator ""_cstr() {
    return FixedString<256>(a);
}


