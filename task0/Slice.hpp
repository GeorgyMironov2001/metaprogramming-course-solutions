
#include <span>
#include <concepts>
#include <cstdlib>
#include <array>
#include <iterator>


inline constexpr std::ptrdiff_t dynamic_stride = -1;

namespace detail {
    template<size_t extent>
    class Extent_struct {
    public:
        constexpr Extent_struct(std::size_t) noexcept {}

        static constexpr size_t get_extent() noexcept {
            return extent;
        }
    };

    template<>
    class Extent_struct<std::dynamic_extent> {
    public:
        constexpr Extent_struct(std::size_t extent) noexcept
                : _extent(extent) {}

        constexpr std::size_t get_extent() const noexcept {
            return _extent;
        }

    private:
        std::size_t _extent;
    };

    template<std::ptrdiff_t stride>
    class Stride_struct {
    public:
        constexpr Stride_struct(std::ptrdiff_t) noexcept {}

        static constexpr std::ptrdiff_t get_stride() noexcept {
            return stride;
        }
    };

    template<>
    class Stride_struct<dynamic_stride> {
    public:
        constexpr Stride_struct(std::ptrdiff_t stride) noexcept
                : _stride(stride) {}

        constexpr std::ptrdiff_t get_stride() const noexcept {
            return _stride;
        }

    private:
        std::ptrdiff_t _stride;
    };
}
template<typename T>
struct my_iterator : std::iterator<std::random_access_iterator_tag, T, int> {
    T *pointer;
    int stride{1};
    int pos{0};

    my_iterator(T *pointer, int stride, int pos)
            : pointer(pointer), stride(stride), pos(pos) {}

    my_iterator() = default;

    my_iterator(const my_iterator &) = default;

    my_iterator &operator=(const my_iterator &) = default;

    ~my_iterator() = default;

    T &operator*() const {
        return *pointer;
    }

    my_iterator &operator++() {
        pointer += stride;
        pos++;
        return *this;
    }

    my_iterator operator++(int) {
        auto old = *this;
        ++(*this);
        pos++;
        return old;
    }

    T *operator->() const { return pointer; }

    my_iterator &operator--() {
        pointer -= stride;
        pos--;
        return *this;
    }

    my_iterator operator--(int) {
        auto old = *this;
        --(*this);
        pos--;
        return old;
    }

    T &operator[](int n) const {
        return pointer[n*stride];
    }

    my_iterator &operator+=(int n) {
        pointer += n * stride;
        pos += n;
        return *this;
    }
    my_iterator operator+(int n) const{
        return my_iterator<T>(pointer+n*stride, stride, pos+n);
    }

    my_iterator &operator-=(int n) {
        pointer -= n * stride;
        pos -= n;
        return *this;
    }
    my_iterator<T> operator-(int n) const{
        return my_iterator<T>(pointer-n*stride, stride, pos-n);
    }
    const T* base() const {
        return pointer;
    }
};

template<typename T>
void swap(my_iterator<T> &a, my_iterator<T> &b) {}

template<typename T, typename Q>
bool operator==(const my_iterator<T> &a, const my_iterator<Q> &b) { return a.pos == b.pos; }

template<typename T, typename Q>
bool operator!=(const my_iterator<T> &a, const my_iterator<Q> &b) { return a.pos != b.pos; }

template<typename T, typename Q>
bool operator<=>(const my_iterator<T> &a, const my_iterator<Q> &b) { return a.pos <=> b.pos; }

template<typename T, typename Q>
bool operator<(const my_iterator<T> &a, const my_iterator<Q> &b) { return a.pos < b.pos; }

template<typename T, typename Q>
bool operator>(const my_iterator<T> &a, const my_iterator<Q> &b) { return a.pos > b.pos; }

template<typename T, typename Q>
bool operator<=(const my_iterator<T> &a, const my_iterator<Q> &b) { return a.pos <= b.pos; }

template<typename T, typename Q>
bool operator>=(const my_iterator<T> &a, const my_iterator<Q> &b) { return a.pos >= b.pos; }

template<typename T>
my_iterator<T> operator+(const my_iterator<T> &a, int n) {
    return my_iterator<T>(a.pointer+n*a.stride, a.stride, a.pos+n);
}

template<typename T>
my_iterator<T> operator+(int n, const my_iterator<T> &a) {
    return my_iterator<T>(a.pointer+n*a.stride, a.stride, a.pos+n);
}

template<typename T>
my_iterator<T> operator-(const my_iterator<T> &a, int n) {
    return my_iterator<T>(a.pointer-n*a.stride, a.stride, a.pos-n);
}

template<typename T>
my_iterator<T> operator-(int n, const my_iterator<T> &a) {
    return my_iterator<T>(a.pointer-n*a.stride, a.stride, a.pos-n);
}


template<typename T>
int operator-(const my_iterator<T> &a, const my_iterator<T> &b) {
    return a.pos - b.pos;
}

template<typename T>
int operator+(const my_iterator<T> &a, const my_iterator<T> &b) {
    return a.pos + b.pos;
}

template<class T, std::size_t _Extent = std::dynamic_extent, std::ptrdiff_t _Stride = 1>
class Slice {
public:
    using element_type = T;
    using value_type = std::remove_cv_t<T>;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = element_type &;
    using const_reference = const element_type &;

    using iterator = my_iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;

    static constexpr size_t extent = _Extent;
    static constexpr std::ptrdiff_t stride = _Stride;

    constexpr Slice() : data_(nullptr), extent_(0), stride_(1) {}

    constexpr Slice(const Slice &s) noexcept = default;

    template<std::contiguous_iterator It>
    constexpr Slice(It first, std::size_t count, std::ptrdiff_t skip):
            data_(std::to_address(first)), extent_(count), stride_(skip) {}

    /*template<std::contiguous_iterator _It, typename OExtent, typename OStride>
    constexpr explicit Slice(_It _first, OExtent extent, std::ptrdiff_t stride)
            : data_(std::to_address(_first)), extent_(extent), stride_(stride) {
    }*/

    template<class OT, size_t Oextent, std::ptrdiff_t Ostride>
    constexpr Slice(const Slice<OT, Oextent, Ostride> &other) :
            data_(other.Data()), extent_(other.Size()), stride_(other.Stride()) {}

    /*template<typename R>
    constexpr Slice(R&& range):
    Slice(std::ranges::data(range), std::ranges::size(range), 1u){}*/

    template<typename OT, size_t ArrayExtent>
    Slice(const std::array<OT, ArrayExtent> &arr):
            Slice<T, ArrayExtent, 1>(static_cast<pointer>(arr.data()), ArrayExtent, 1) {}

    template<class U>
    Slice(U &container) requires requires{ container.data(); container.size(); }
            :data_(container.data()), extent_(container.size()), stride_(1) {}


    constexpr Slice &operator=(const Slice &) noexcept = default;

    constexpr Slice<T, std::dynamic_extent, dynamic_stride> Skip(std::ptrdiff_t skip) {
        int new_extent = (int) ((Size()+skip-1) / skip);
        return Slice<element_type, std::dynamic_extent, dynamic_stride>(Data(), new_extent, Stride() * skip);
    }

    template<std::ptrdiff_t skip>
    constexpr Slice<element_type, extent != -1 ? (extent+skip-1) / skip : extent, skip * stride> Skip() requires (stride != -1) {
        int new_extent = (Size()+skip-1) / skip;
        return Slice<element_type, extent != -1 ? (extent+skip-1) / skip : extent, skip * stride>(Data(), new_extent,
                                                                                         Stride() * skip);
    }

    template<std::ptrdiff_t skip>
    constexpr Slice<element_type, std::dynamic_extent, dynamic_stride> Skip() requires (stride == -1) {
        return Skip(skip);
    }

    template<typename OT, size_t OExtent, std::ptrdiff_t OStride>
    friend bool operator==(const Slice<T, _Extent, _Stride> &s1, const Slice<OT, OExtent, OStride> &s2) {
        if (s1.Size() != s2.Size()) return false;
        for (size_t i = 0; i < s1.Size(); ++i) {
            if (s1[i] != s2[i]) return false;
        }
        return true;
    }

    constexpr size_type Size() const {
        return extent_.get_extent();
    }

    constexpr pointer Data() const {
        return data_;
    }

    constexpr std::ptrdiff_t Stride() const {
        return stride_.get_stride();
    }

    constexpr iterator begin() {
        return iterator(data_, Stride(), 0);
    }

    constexpr iterator end() {
        return iterator(data_ + this->Size() * Stride(), Stride(), Size());
    }

    constexpr reverse_iterator rbegin() {
        return reverse_iterator(this->end() * Stride(), Stride(), Size());
    }

    constexpr reverse_iterator rend() {
        return reverse_iterator(this->begin(), Stride(), 0);
    }


    constexpr T &operator[](const size_t &index) const {
        return *(data_ + index * stride_.get_stride());
    }

    constexpr Slice<element_type, std::dynamic_extent, stride> First(std::size_t count) const {
        return Slice<element_type, std::dynamic_extent, stride>(Data(), count, Stride());
    }

    template<size_t count>
    constexpr Slice<element_type, count, stride> First() const {
        return Slice<element_type, count, stride>(Data(), count, Stride());
    }

    constexpr Slice<element_type, std::dynamic_extent, stride> Last(std::size_t count) const {
        return Slice<element_type, std::dynamic_extent, stride>(Data() + Size() - count, count, Stride());
    }

    template<size_t count>
    constexpr Slice<element_type, count, stride> Last() const {
        return Slice<element_type, count, stride>(Data() + Size() - count, count, Stride());
    }

    constexpr Slice<element_type, std::dynamic_extent, stride> DropLast(size_t drop_count) {
        return Slice<element_type, std::dynamic_extent, stride>(Data(), Size() - drop_count, Stride());
    }

    template<size_t drop_count>
    constexpr Slice<element_type, extent - drop_count, stride> DropLast() requires (extent != std::dynamic_extent) {
        return Slice<element_type, extent - drop_count, stride>(Data(), Size() - drop_count, Stride());
    }

    template<size_t drop_count>
    constexpr Slice<element_type, std::dynamic_extent, stride> DropLast() requires (extent == std::dynamic_extent) {
        return DropLast(drop_count);
    }

    constexpr Slice<element_type, std::dynamic_extent, stride> DropFirst(size_t drop_count) {
        return Slice<element_type, std::dynamic_extent, stride>(Data() + Stride() * drop_count, Size() - drop_count,
                                                                Stride());
    }

    template<size_t drop_count>
    constexpr Slice<element_type, extent - drop_count, stride> DropFirst() requires (extent != std::dynamic_extent) {
        return Slice<element_type, extent - drop_count, stride>(Data() + Stride() * drop_count, Size() - drop_count,
                                                                Stride());
    }

    template<size_t drop_count>
    constexpr Slice<element_type, std::dynamic_extent, stride> DropFirst() requires (extent == std::dynamic_extent) {
        return DropFirst(drop_count);
    }

private:
    [[no_unique_address]] detail::Extent_struct<_Extent> extent_;
    [[no_unique_address]] detail::Stride_struct<_Stride> stride_;
    T *data_;
};

/*template<typename Type, size_t ArrayExtent>
Slice(Type(&)[ArrayExtent]) -> Slice<Type, ArrayExtent, 1>;*/

template<typename Type, size_t ArrayExtent>
Slice(std::array<Type, ArrayExtent> &) -> Slice<Type, ArrayExtent, 1>;

/*template<typename Type, size_t ArrayExtent>
Slice(const std::array<Type, ArrayExtent> &)
-> Slice<const Type, ArrayExtent, 1>;*/

template<typename Range>
Slice(Range &)
-> Slice<std::remove_reference_t<std::ranges::range_reference_t<Range &>>>;

template<std::contiguous_iterator Iter, typename Extent, typename Stride>
Slice(Iter, Extent, Stride)
-> Slice<std::remove_reference_t<std::iter_reference_t<Iter>>, std::dynamic_extent, dynamic_stride>;
