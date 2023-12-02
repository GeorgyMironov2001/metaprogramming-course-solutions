Задача 1. Endless laziness
========================

## Problem

### Working with infinite lists of types

Consider the following concept.

```c++

template<class TL>
concept TypeSequence =
    requires {
        typename TL::Head;
        typename TL::Tail;
    };
```

It is claimed to describe *infinite sequences of types*. `TL::Tail` is also implicitly required to satisfy the `TypeSequence` concept, but it is probably not possible to model this in C++20.

But how can the type sequence be infinite if the memory in the compiler is finite?

The answer is the same as in functional languages: lazy computation. The compiler lazily instantiates class template members, including aliases like Tail, which means they can even refer to the current template, but with different arguments.

Example:
```c++
template<class T>
struct FunnyStarrySequence {
    using Head = T;
    using Tail = FunnyStarrySequence<T*>;
};
```
Instances of this pattern describe infinite lists of the form `(T, T*, T**, T***, T****, ...)`. The entire list is not stored in compiler memory, only the pattern of fetching the next elements is stored. How many times you fetch the next element -- that's how many will be computed.

But it is inconvenient to work with infinite type sequences alone, so let's consider the following code.

```c++
struct Nil {};

template<class TL>
concept Empty = std::derived_from<TL, Nil>;

template<class TL>
concept TypeList = Empty<TL> || TypeSequence<TL>;
```

We have introduced the concept of `Empty`, describing an empty list as an arbitrary successor of `Nil`, and `TypeList`, describing a *potentially infinite list* as either empty or a sequence. Note that the implicit requirement on `TL::Tail` needs to be changed: it must satisfy the more general concept of `TypeList`, not specifically `TypeSequence`. A more correct approach would be to define `TypeList` independently of TypeSequence and treat them as independent entities. However, the chosen approach allows the compiler to guess that any sequence is also a list, which can be useful in practice when overloading functions.

So, your task is to implement a set of interesting operations for working with infinite lists, in the process figuring out how to implement specific types of timelists in general.

### "New" Tiplists

From now on, we will call them type tuples to better distinguish them from potentially infinite sheets. In this problem, we will also need tuples in some places, but we will not write very abstruse algorithms on them. Recall that they are defined as
```c++
template<class... Ts>
struct TTuple {};
```
Note that all the different tuplets can be combined into one family using the `TypeTuple` concept. Familiarize yourself with its implementation in the template and think what other troubles you can do using such a technique.

### Part 1: operations

Следующие функции должны находится в неймспейсе `type_lists`.

 * `Cons<T, TL>` -- a list with `T` at the beginning, and then -- the elements of the list `TL`.
 * `FromTuple<TT>`/`ToTuple<TL>` -- functions for converting between **end** lists and pipes. Will help you when debugging.
 * `Repeat<T>` -- An infinite list of `T`.
 * `Take<N, TL>` -- the first `N` elements of the potentially infinite list `TL`.
 * `Drop<N, TL>` -- everything except the first `N` elements of the list `TL`.
 * `Replicate<N, T>` -- list of `N` elements equal to `T`.
 * `Map<F, TL>` -- list from the results of applying `F` to the elements of `TL`.
 * `Filter<P, TL>` -- list only those elements of `TL` that satisfy `P<_>::Value`. The relative order of the elements must not change.
 * `Iterate<F, T>` -- list in which each next element is the result of applying the metafunction `F` to the previous one, and the first one is `T`.
 * `Cycle<TL>` -- an infinite list in which the finite list `TL` is repeated time after time.
 * `Inits<TL>` -- list of all `TL` prefixes in ascending order of length.
 * `Tails<TL>` -- list of all `TL` suffixes in ascending order of the length of their complement to the whole list.
 * `Scanl<OP, T, TL>` -- A sequence in which the first element is `T` and each subsequent element is obtained by applying `OP<_, _>::Type` to the current and next element of `TL`.
 * `Foldl<OP, T, TL>` -- type, obtained as `OP<.... OP<OP<T, TL[0]>, TL[1]> ... >`. If the sequence is infinite, the value is undefined.
 * `Zip2<L, R>` -- list of pairs of i-th elements of lists `L` and `R`, respectively, in a row.
 * `Zip<TL...>` -- a list of typles one item of fixed number from each list.


 * `GroupBy<EQ, TL>` -- a list of **sequential** lists of `TL` elements that are "equal" **sequentially**, i.e. each next element must be equal to the current one (this allows, for example, to search for increasing subsequences). Equality is implied in the sense of `EQ<T, S>::Value == true`. For example, a groupbyte of letters in the word "Mississippi" by equality -- `["M", "i", "ss", "i", "ss", "i", "pp", "i"]`. If all elements of the *infinite* sequence `TL` are equal, the behavior is undefined (think about what's stopping us from defining it). Here `EQ` -- a metapredicate satisfying the axioms of equality.

### Part 2: numerical sequences

Put the contents of this section into the global nymspace.

Let's introduce a new class:
```c++
template<auto V>
struct ValueTag{ static constexpr auto Value = V; };
```
We can use it to store values inside types, which gives us the ability to work with infinite lists of values in compile-time. Compute the following types:

 * `Nats` -- the natural numbers `(0, 1, 2, 3, ...)`.
 * `Fib` -- Fibonacci numbers `(0, 1, 1, 2, ...)`.
 * `Primes` -- prime numbers `(2, 3, 5, 7, ...)`.




