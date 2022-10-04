#pragma once

#include <concepts>

#include "type_tuples.hpp"
#include "value_types.hpp"

using value_types::ValueTag;
template<int N>
struct S {
    using Head = ValueTag<N>;
    using Tail = S<N + 1>;
};


template<int a, int b>
struct F {
    using Head = ValueTag<a + b>;
    using Tail = F<b, a + b>;
};

template<int P, int N>
struct Check_prime {
    static constexpr bool devided = (P % N == 0) || Check_prime<P, N - 1>::devided;
};
template<int P>
struct Check_prime<P, 2> {
    static constexpr bool devided = (P % 2 == 0);
};

template<int P>
struct Is_prime {
    static constexpr bool Value = !Check_prime<P, P - 1>::devided;
};
template<>
struct Is_prime<2> {
    static constexpr bool Value = true;
};

template<int N, bool>
struct Primes_struct {
};

template<int N>
struct Primes_struct<N, true> {
    using Head = ValueTag<N>;
    using Tail = Primes_struct<N + 1, Is_prime<N + 1>::Value>;
};
template<int N>
struct Primes_struct<N, false> {
    using Head = typename Primes_struct<N + 1, Is_prime<N + 1>::Value>::Head;
    using Tail = Primes_struct<Head::Value + 1, Is_prime<Head::Value + 1>::Value>;
};

using Nats = S<0>;
using Fib = F<-1, 1>;
using Primes = Primes_struct<2, true>;
