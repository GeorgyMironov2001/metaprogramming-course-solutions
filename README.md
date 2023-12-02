Задача 3. A very clever non-pointer
========================


## Problem

Implement a Spy template class that wraps an arbitrary object and logs calls to it.

The wrapped entity needs to be stored *by value*. It was rightly pointed out 2 years ago that it is wrong to call such entities pointers, so we will call them smart non-pointers.

If `s` &mdash; a value of type `Spy<T>`, the expression `s->member` shall result in a call to the non-static member `member` of the wrapped object.

### Loggers

The `setLogger` method sets the logger. After evaluating each expression containing references to the wrapped object via `operator ->`, the logger should be called if it is set. The logger takes as an argument the number of accesses to the object when evaluating the expression.

Addresses via `operator *` are not logged.

If the wrapped type `T` is not copyable, then `Spy<T>` must support move-only loggers.

If the wrapped object is accessed and the logger is changed in the same expression, the behavior is undefined.

Using `std::function` and `std::any` in this task is prohibited.

### Saving concepts

We will say that a smart non-pointer `W` preserves a concept `C` if for any type `T`

1) `T` satisfies `C` &rArr; `W<T>` satisfies `C`,
2) `T` models `C` &rArr; `W<T>` models `C`.

Your `Spy` must preserve the basic object concepts: `std::movable`, `std::copyable`, `std::semiregular`, `std::regular`. To do this, you can impose additional constraints on the template argument of the `setLogger` method.

Comparison operators must compare wrapped objects, ignoring the logger. When copying (moving), both the logger and the wrapped object must be copied (moved).

If a wrapped object is accessed and a non-pointer is moved in the same expression, the behavior is undefined. Copying creates a new object, which must be accessed _separately_.


## Example

```c++
struct Holder {
    int x = 0;
    bool isPositive() const {
        return x > 0;
    }
};

Spy s{Holder{}};
static_assert(std::semiregular<decltype(s)>);

s.setLogger([](auto n) { std::cout << n << std::endl; });

s->isPositive() && s->x--; // prints 1
s->x++ + s->x++; // prints 2
s->isPositive() && s->x--; // prints 2

s.setLogger([dummy = std::unique_ptr<int>()](auto n) {}); // compilation error

// -----------------------------------

struct MoveOnly {
    MoveOnly() = default;

    MoveOnly(MoveOnly&&) = default;
    MoveOnly& operator =(MoveOnly&&) = default;

    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator =(const MoveOnly&) = delete;

    ~MoveOnly() noexcept = default;
};

Spy t{MoveOnly{}};

s.setLogger([dummy = std::unique_ptr<int>()](auto n) {}); // ok

static_assert(std::movable<decltype(t)>);
static_assert(!std::copyable<decltype(t)>);
```

