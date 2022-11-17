#pragma once

#include <concepts>
#include <stddef.h>
#include "type_tuples.hpp"
using type_tuples::TTuple;
namespace type_lists
{
    

    template <class TL>
    concept TypeSequence = requires
    {
        typename TL::Head;
        typename TL::Tail;
    };

    struct Nil
    {
    };

    template <class TL>
    concept Empty = std::derived_from<TL, Nil>;

    template <class TL>
    concept TypeList = Empty<TL> || TypeSequence<TL>;

    // Your fun, fun metaalgorithms :)
    template <class T, class TL>
    struct Cons
    {
        using Head = T;
        using Tail = TL;
    };

    template <class T>
    struct Repeat
    {
        using Head = T;
        using Tail = Repeat<T>;
    };

    template <typename... TL>
    struct Help_struct_for_to_tuple
    {
    };

    template <class T, class Tail>
    struct Help_struct_for_to_tuple<Cons<T, Tail>>
    {
        using Type = typename Help_struct_for_to_tuple<Tail, T>::Type;
    };

    template <class T, class Tail, class... U>
    struct Help_struct_for_to_tuple<Cons<T, Tail>, U...>
    {
        using Type = typename Help_struct_for_to_tuple<Tail, U..., T>::Type;
    };
    template <class TL>
    requires(TypeSequence<TL>) struct Help_struct_for_to_tuple<TL>
    {
        using Type = typename Help_struct_for_to_tuple<typename TL::Tail, typename TL::Head>::Type;
    };
    template <class TL, class... U>
    requires(TypeSequence<TL>) struct Help_struct_for_to_tuple<TL, U...>
    {
        using Type = typename Help_struct_for_to_tuple<typename TL::Tail, U..., typename TL::Head>::Type;
    };
    template <class... U>
    struct Help_struct_for_to_tuple<Nil, U...>
    {
        using Type = TTuple<U...>;
    };

    template <typename T>
    using ToTuple = typename Help_struct_for_to_tuple<T>::Type;

    template <class Tuple>
    struct Help_struct_for_from_tuple
    {
    };

    template <typename T, typename... Tail>
    struct Help_struct_for_from_tuple<TTuple<T, Tail...>>
    {
        using Type = Cons<T, typename Help_struct_for_from_tuple<TTuple<Tail...>>::Type>;
    };

    template <typename T>
    struct Help_struct_for_from_tuple<TTuple<T>>
    {
        using Type = Cons<T, Nil>;
    };

    template <class Tuple>
    using FromTuple = typename Help_struct_for_from_tuple<Tuple>::Type;

    template <size_t N, typename T>
    struct Help_struct_for_take
    {
        using Type = Cons<typename T::Head, typename Help_struct_for_take<N - 1, typename T::Tail>::Type>;
    };
    template <typename T>
    struct Help_struct_for_take<0, T>
    {
        using Type = Nil;
    };
    template <size_t N>
    struct Help_struct_for_take<N, Nil>
    {
        using Type = Nil;
    };

    template <>
    struct Help_struct_for_take<0, Nil>
    {
        using Type = Nil;
    };
    template <size_t N, typename T>
    using Take = typename Help_struct_for_take<N, T>::Type;

    template<int N, typename T>
    struct Drop_struct {
        using Type = typename Drop_struct<N - 1, typename T::Tail>::Type;
    };
    template<typename T>
    struct Drop_struct<0, T> {
        using Type = T;
    };

    template<int N>
    struct Drop_struct<N, Nil> {
        using Type = Nil;
    };
    template<>
    struct Drop_struct<0, Nil> {
        using Type = Nil;
    };

    template <int N, typename T>
    using Drop = typename Drop_struct<N, T>::Type;

    template <size_t N, typename T>
    struct Replicate_
    {
        using Type = Cons<T, typename Replicate_<N - 1, T>::Type>;
    };
    template <typename T>
    struct Replicate_<1, T>
    {
        using Type = Cons<T, Nil>;
    };

    template <size_t N, typename T>
    using Replicate = typename Replicate_<N, T>::Type;

    template <template <class> typename F, typename T>
    struct Iterate
    {
        using Head = T;
        using Tail = Iterate<F, F<T>>;
    };

    template <typename... TL>
    struct Cycle
    {
    };

    template <typename TL>
    struct Cycle<TL>
    {
        using Head = typename TL::Head;
        using Tail = Cycle<TL, typename TL::Tail>;
    };
    template <typename TL, typename T>
    struct Cycle<TL, T>
    {
        using Head = typename T::Head;
        using Tail = Cycle<TL, typename T::Tail>;
    };
    template <typename TL>
    struct Cycle<TL, Nil>
    {
        using Head = typename TL::Head;
        using Tail = Cycle<TL, typename TL::Tail>;
    };

    /*template<template<class> typename F, typename TL>
    struct Map_struct {
        using Type = Cons<F<typename TL::Head>, typename Map_struct<F, typename TL::Tail>::Type>;
    };
    template<template<class> typename F>
    struct Map_struct<F, Nil> {
        using Type = Nil;
    };
    template<template<class> typename F, typename TL>
    using Map_struct = typename Map_struct<F, TL>::Type;*/

    template <template <class> typename F, typename TL>
    struct Map_struct
    {
        using Head = F<typename TL::Head>;
        using Tail = Map_struct<F, typename TL::Tail>;
    };
    template <template <class> typename F, typename TL>
    requires(std::same_as<typename TL::Tail, Nil>) struct Map_struct<F, TL>
    {
        using Head = F<typename TL::Head>;
        using Tail = Nil;
    };
    template <template <class> typename F, typename TL>
    struct Map_Nil
    {
        using Type = Map_struct<F, TL>;
    };
    template <template <class> typename F, typename TL>
    requires(std::same_as<TL, Nil>) struct Map_Nil<F, TL>
    {
        using Type = Nil;
    };
    template <template <class> typename F, typename TL>
    using Map = typename Map_Nil<F, TL>::Type;
    template <bool, typename TL, template <class> typename P>
    struct struct_for_filter1
    {
    };

    template <bool b, template <class> typename P>
    struct struct_for_filter1<b, Nil, P>
    {
        using Type = Nil;
    };
    template <typename TL, template <class> typename P>
    struct struct_for_filter1<true, TL, P>
    {
        using Type = Cons<typename TL::Head, typename struct_for_filter1<P<typename TL::Tail::Head>::Value, typename TL::Tail, P>::Type>;
    };
    template <typename TL, template <class> typename P>
    struct struct_for_filter1<false, TL, P>
    {
        using Type = typename struct_for_filter1<P<typename TL::Tail::Head>::Value, typename TL::Tail, P>::Type;
    };

    template <typename T, template <class> typename P>
    struct struct_for_filter1<true, Cons<T, Nil>, P>
    {
        using Type = Cons<T, Nil>;
    };
    template <typename T, template <class> typename P>
    struct struct_for_filter1<false, Cons<T, Nil>, P>
    {
        using Type = Nil;
    };
    template <template <class> typename P, typename TL>
    struct struct_for_filter2
    {
        using Type = typename struct_for_filter1<P<typename TL::Head>::Value, TL, P>::Type;
    };
    template <template <class> typename P>
    struct struct_for_filter2<P, Nil>
    {
        using Type = Nil;
    };
    template <template <class> typename P, typename TL>
    using Filter = typename struct_for_filter2<P, TL>::Type;

    template <template <class, class> typename OP, typename T, typename TL>
    struct scan1
    {
        using Type = Cons<OP<T, typename TL::Head>, typename scan1<OP, OP<T, typename TL::Head>, typename TL::Tail>::Type>;
    };
    template <template <class, class> typename OP, typename T>
    struct scan1<OP, T, Nil>
    {
        using Type = Nil;
    };

    template <template <class, class> typename OP, typename T, typename TL>
    using Scanl = Cons<T, typename scan1<OP, T, TL>::Type>;

    template <template <class, class> typename OP, typename T, typename TL>
    struct fold1
    {
        using Type = typename fold1<OP, OP<T, typename TL::Head>, typename TL::Tail>::Type;
    };
    template <template <class, class> typename OP, typename T>
    struct fold1<OP, T, Nil>
    {
        using Type = T;
    };
    template <template <class, class> typename OP, typename T, typename TL>
    using Foldl = typename fold1<OP, T, TL>::Type;

    template <typename TL, size_t N, typename T>
    struct inits_struct
    {
        using Type = Cons<Take<N, TL>, typename inits_struct<TL, N + 1, typename T::Tail>::Type>;
    };
    template <typename TL, size_t N>
    struct inits_struct<TL, N, Nil>
    {
        using Type = Nil;
    };
    template <typename TL>
    using Inits = Cons<Nil, typename inits_struct<TL, 1, TL>::Type>;

    template <typename TL, size_t N, typename T>
    struct tails_struct
    {
        using Type = Cons<Drop<N, TL>, typename tails_struct<TL, N + 1, typename T::Tail>::Type>;
    };
    template <typename TL, size_t N>
    struct tails_struct<TL, N, Nil>
    {
        using Type = Nil;
    };
    template <typename TL>
    using Tails = Cons<TL, typename tails_struct<TL, 1, TL>::Type>;

    template <typename L, typename R>
    struct Zip2_struct
    {
        using Head = TTuple<typename L::Head, typename R::Head>;
        using Tail = Zip2_struct<typename L::Tail, typename R::Tail>;
    };
    template <typename L, typename R>
    requires(std::same_as<typename L::Tail, Nil> ||
             std::same_as<typename R::Tail, Nil>) struct Zip2_struct<L, R>
    {
        using Head = TTuple<typename L::Head, typename R::Head>;
        using Tail = Nil;
    };

    template <typename L, typename R>
    struct base
    {
        using Type = Zip2_struct<L, R>;
    };

    template <typename L, typename R>
    requires(std::same_as<L, Nil> ||
             std::same_as<R, Nil>) struct base<L, R>
    {
        using Type = Nil;
    };
    template <typename L, typename R>
    using Zip2 = typename base<L, R>::Type;

    template <typename TL>
    struct get_head_cons
    {
    };
    template <typename T, typename TL>
    requires(!std::same_as<T, Nil>) struct get_head_cons<Cons<T, TL>>
    {
        using Type = Cons<typename T::Head, typename get_head_cons<TL>::Type>;
        static constexpr bool no_Nil = get_head_cons<TL>::no_Nil;
    };
    template <typename T, typename TL>
    requires(std::same_as<T, Nil>) struct get_head_cons<Cons<T, TL>>
    {
        using Type = Nil;
        static constexpr bool no_Nil = false;
    };
    template <typename T>
    requires(!std::same_as<T, Nil>) struct get_head_cons<Cons<T, Nil>>
    {
        using Type = Cons<typename T::Head, Nil>;
        static constexpr bool no_Nil = true;
    };
    template <typename T>
    requires(std::same_as<T, Nil>) struct get_head_cons<Cons<T, Nil>>
    {
        using Type = Nil;
        static constexpr bool no_Nil = false;
    };

    template <typename ConsTL>
    struct get_tail_cons
    {
    };

    template <typename T, typename TL>
    requires(!std::same_as<typename T::Tail, Nil>) struct get_tail_cons<Cons<T, TL>>
    {
        using Type = Cons<typename T::Tail, typename get_tail_cons<TL>::Type>;
        static constexpr bool Cons_tail_no_Nil = get_tail_cons<TL>::Cons_tail_no_Nil;
    };

    template <typename T, typename TL>
    requires(std::same_as<typename T::Tail, Nil>) struct get_tail_cons<Cons<T, TL>>
    {
        using Type = Nil;
        static constexpr bool Cons_tail_no_Nil = false;
    };
    template <typename T>
    requires(!std::same_as<typename T::Tail, Nil>) struct get_tail_cons<Cons<T, Nil>>
    {
        using Type = Cons<typename T::Tail, Nil>;
        static constexpr bool Cons_tail_no_Nil = true;
    };
    template <typename T>
    requires(std::same_as<typename T::Tail, Nil>) struct get_tail_cons<T>
    {
        using Type = Nil;
        static constexpr bool Cons_tail_no_Nil = false;
    };

    template <typename ConsTL>
    struct zip_struct
    {
        using Head = ToTuple<typename get_head_cons<ConsTL>::Type>;
        using Tail = zip_struct<typename get_tail_cons<ConsTL>::Type>;
    };
    template <typename ConsTL>
    requires(!get_tail_cons<ConsTL>::Cons_tail_no_Nil) struct zip_struct<ConsTL>
    {
        using Head = ToTuple<typename get_head_cons<ConsTL>::Type>;
        using Tail = Nil;
    };

    template <typename... TL>
    struct base_zip
    {
        using Type = zip_struct<FromTuple<TTuple<TL...>>>;
    };
    template <typename... TL>
    requires(!get_head_cons<FromTuple<TTuple<TL...>>>::no_Nil) struct base_zip<TL...>
    {
        using Type = Nil;
    };
    template <typename... TL>
    using Zip = typename base_zip<TL...>::Type;
    
    template<bool b, template<class, class> typename EQ, typename T, typename TL>
    struct Equal_Head {
        using Block = Nil;
        using Remain_tail = TL;
    };
    template<template<class, class> typename EQ, typename T, typename TL>
    struct Equal_Head<true, EQ, T, TL> {
        using helper = Equal_Head<EQ<T, typename TL::Tail::Head>::Value, EQ, T, typename TL::Tail>;
        using Block = Cons<typename TL::Head, typename helper::Block>;
        using Remain_tail = typename helper::Remain_tail;
    };

    template<template<class, class> typename EQ, typename T, typename TL>
    struct Equal_Head<true, EQ, T, Cons<TL, Nil>> {

        using Block = Cons<TL, Nil>;
        using Remain_tail = Nil;
    };
    template<template<class, class> typename EQ, typename TL>
    struct GroupBy {
        using now_block = Equal_Head<true, EQ, typename TL::Head, TL>;
        using Head = typename now_block::Block;
        using Tail = GroupBy<EQ, typename now_block::Remain_tail>;
    };

    template<template<class, class> typename EQ, typename T>
    struct GroupBy<EQ, Cons<T, Nil>> {
        using Head = Cons<T, Nil>;
        using Tail = Nil;
    };
    
}; // namespace type_lists

