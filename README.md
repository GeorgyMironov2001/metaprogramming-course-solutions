Задача 0. Slice-n-dice
========================


## Задача

### Slice

In this task, you will have to write a more generic version of `std::span`: `Slice` that supports an additional template parameter stride -- the step size when moving to the next element. For example,
```c++
    std::array<int, 10> data;
    std::iota(data.begin(), data.end(), 0);
    slice<int, 5, 2> even_elements{data};
```
Here the contents of `even_elements` should be `0, 2, 4, 6, 8`. Also, your implementation should support the runtime value of both parameters, or any one of them, when substituting `std::dynamic_extent` and `dynamic_stride` respectively into the template.

### Slice interface

Requirements for the `Slice' template -- interface repetition [`std::span`](https://en.cppreference.com/w/cpp/container/span), кроме следующих исключений:
* `size_bytes`
* `as_bytes`
* `as_writable_bytes`
* `subspan`
These methods imply `stride == 1`, so we will ignore them for now. Also, ignore the "Helper templates" section for now. Finally, the constructors `std::span` -- is a rather delicate science, so it is suggested not to repeat them one-to-one with cppreference, but to write your own from scratch so that the tests pass.
Next, we need some additions related to the `stride` parameter:
* Methods `Skip`, to change the `stride`
* Methods `DropFirst`, discarding the first few elements
* Methods `DropLast`, dropping the last few elements
* A modification of the constructor from iterator and size that also accepts `stride`
Note that we do not require a `Subslice` method analogous to `subspan`. Trying to write such a method that accounts for all combinations of runtime and compile-time parameters leads to combinatorial explosion, so instead we provide the more elementary methods `First`, `Last`, `DropFirst`, `DropLast` and `Stride`. For each of these, create two overloads: one with a template parameter and one with a regular parameter.

Note that `const Slice<T>` and `Slice<const T>` are not the same thing! The former prohibits changing the current variable of type `Slice`, the latter prohibits changing the data pointed to by the current variable.

We also require that a `Slice` with static parameters implicitly casts to a similar slice with dynamic parameters (both at the same time, and only one separately). The cast of `Slice<T>` to `Slice<const T>` must also be implicit.

Also, a mandatory requirement -- the size of each `Slice` specialization must be the smallest possible size. That is, you cannot store data about `extent` and `stride` in runtime if they are known in compile time. Think how to achieve this without solving the whole problem 4 times again. Perhaps inheritance will help you? Don't be afraid to use all the power of C++ and even change the solution pattern completely. The main thing is to pass the tests.

Don't clog the global `namespace` with auxiliary templates, put them in a separate `namespace`.

