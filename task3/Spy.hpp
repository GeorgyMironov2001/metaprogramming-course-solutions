#pragma once

#include <concepts>
#include <memory>
#include <iostream>
#include <functional>
// Allocator is only used in bonus SBO tests,
// ignore if you don't need bonus points.

struct Base_Logger {
    virtual ~Base_Logger() = default;

    virtual void Add_Counter(int n) = 0;
};

template<class Logger>
struct Derived_Logger : Base_Logger {
    Logger logger_;

    void Add_Counter(int n) override {
        logger_(n);
    }

    explicit Derived_Logger(Logger &&logger) : logger_(std::forward<Logger>(logger)) {}
};

template<class T /*, class Allocator = std::allocator<std::byte>*/ >
class Spy;

template<typename T>
struct Helper {
    explicit Helper(Spy<T> &s) : value_(&s.value_), logger_ptr_(s.logger_ptr_), counter_(s.counter_) {}

    explicit Helper(Spy<T> &&s) : value_(&s.value_), logger_ptr_(std::move(s.logger_ptr_)), counter_(s.counter_) {}

    T *operator->() {
        return value_;
    }

    ~Helper() {
        if (*counter_ != 0 && logger_ptr_ != nullptr) {
            //std::cout << *counter_ << "\n";
            logger_ptr_->Add_Counter(*counter_);
        }
        *counter_ = 0;
    }

    std::shared_ptr<int> counter_{new int{0}};
    T *value_;
    // Allocator allocator_;
    Base_Logger *logger_ptr_{nullptr};
};

template<class T /*, class Allocator = std::allocator<std::byte>*/ >
class Spy {
public:

    Spy() = default;

    Spy(const T &value/* , const Allocator& alloc = Allocator()*/ ) : value_(value) {}

    Spy(T &&value) : value_(std::move(value)) {}

    T &operator*() {
        return value_;
    }

    const T &operator*() const {
        return value_;
    }


    auto operator->() {
        *counter_ += 1;
        //return this->shared_from_this();
        std::function f = [this](T *s) { this->f(); };
        return (Helper<T>(*this));
    }

    void f() {
        if (*counter_ != 0 && logger_ptr_ != nullptr) {
            //std::cout << *counter_ << "\n";
            logger_ptr_->Add_Counter(*counter_);
        }
        *counter_ = 0;
    }

    Spy(const Spy<T> &other)requires(std::copyable<T>): value_(other.value_), counter_(new int(0)),
                                                        logger_ptr_(other.logger_ptr_) {}

    Spy(Spy<T> &&other) noexcept requires(std::movable<T>): value_(std::move(other.value_)), counter_(new int(0)),
                                                            logger_ptr_(std::move(other.logger_ptr_)) {

    }

    Spy &operator=(const Spy<T> &other) {
        value_ = other.value_;
        counter_ = std::make_shared<int>(0);
        logger_ptr_ = other.logger_ptr_;

        return *this;
    }

    Spy &operator=(Spy<T> &&other) noexcept {
        value_ = std::move(other.value_);
        counter_ = std::make_shared<int>(0);
        logger_ptr_ = other.logger_ptr_;

        return *this;
    }
    /*
     * if needed (see task readme):
     *   default constructor
     *   copy and move construction
     *   copy and move assignment
     *   equality operators
     *   destructor
    */

    // Resets logger
    void setLogger();

    template<class Logger>
    /*requires  see task readme */
    void setLogger(Logger &&logger) requires ((!std::copyable<T> || std::copyable<std::remove_reference_t<Logger>> ) &&
                                              (!std::movable<T> || std::movable<std::remove_reference_t<Logger>>)) {
        logger_ptr_ = new Derived_Logger<Logger>(std::forward<Logger>(logger));
    }

    ~Spy() = default;

public:
    std::shared_ptr<int> counter_{new int{0}};
    T value_;
    // Allocator allocator_;
    Base_Logger *logger_ptr_{nullptr};
};

template<class T, class U>
bool operator==(const Spy<T> &l, const Spy<U> &r) requires (std::same_as<T, U> && std::equality_comparable<T>) {
    return l.value_ == r.value_;
}

