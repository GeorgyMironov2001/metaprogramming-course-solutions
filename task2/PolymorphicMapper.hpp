#pragma once

#include <optional>
#include <iostream>



template<class From, auto target>
struct Mapping {
    using Key = From;
    static constexpr auto target_ = target;
};

template<class Base, class Target, class... Mappings>
struct PolymorphicMapper {
};

template<class Base, class Target>
struct PolymorphicMapper<Base, Target> {
    static std::optional<Target> map(Base &object) {
        return std::nullopt;
    }

    static void just_do_it() {

    }
};

template<class Base, class Target, class Map, class ...Mappings>
struct PolymorphicMapper<Base, Target, Map, Mappings...> {
    static std::optional<Target> map(Base &object) {

        static_assert(std::same_as<const Target, decltype(Map::target_)>);

        if (dynamic_cast<typename Map::Key *>(&object)) {
            PolymorphicMapper<Base, Target, Mappings...>::just_do_it();
            return (Target)Map::target_;
        } else {
            return PolymorphicMapper<Base, Target, Mappings...>::map(object);
        }
    }

    static void just_do_it() {
        static_assert(std::same_as<const Target, decltype(Map::target_)>);
        PolymorphicMapper<Base, Target, Mappings...>::just_do_it();
    }
};
