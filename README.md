Задача 3. Очень умный неуказатель
========================


## Задача

Реализуйте шаблонный класс Spy, оборачивающий произвольный объект и логирующий обращения к нему.

Оборачиваемый объект необходимо хранить *по значению*. 2 года назад справедливо заметили, что называть такие сущности указателями неправильно, поэтому мы будем называть их умными неуказателями.

Если `s` &mdash; значение типа `Spy<T>`,  выражение `s->member` должно приводить к обращению к нестатическому члену `member` оборачиваемого объекта.

### Логеры

Метод `setLogger` устанавливает логер. После вычисления каждого выражения, содержащего обращения к оборачиваемому объекту через `operator ->`, должен вызываться логер, если он установлен. В качестве аргумента логер принимает количество обращений к объекту при вычислении выражения.

Обращения через `operator *` не логируются.

Если оборачиваемый тип `T` не копируемый, то `Spy<T>` должен поддерживать move-only логеры.

Если в одном выражении происходит обращение к оборачиваемому объекту и изменяется логер, поведение не определено.

Использовать `std::function` и `std::any` в этом задании запрещено.

### Сохранение концептов

Будем говорить, что умный неуказатель `W` сохраняет концепт `C`, если для любого типа `T`

1) `T` удовлетворяет `C` &rArr; `W<T>` удовлетворяет `C`,
2) `T` моделирует `C` &rArr; `W<T>` моделирует `C`.

Ваш `Spy` должен сохранять основные объектные концепты: `std::movable`, `std::copyable`, `std::semiregular`, `std::regular`. Для этого можно накладывать дополнительные ограничения на шаблонный аргумент метода `setLogger`.

Операторы сравнения должны сравнивать оборачиваемые объекты, игнорируя логер. При копировании (перемещении) должны копироваться (перемещаться) и логер, и оборачиваемый объект.

Если в одном выражении происходит обращение к оборачиваемому объекту и перемещение неуказателя, поведение не определено. Копирование создаёт новый объект, обращения к которому должны учитываться _отдельно_.

### Бонус: аллокаторы и small buffer optimization (+2 у.е.)

Поддержите пользовательские аллокаторы и small buffer optimization для логеров. Обратите внимание, что мы пишем на C++20, и вместо placement new следует использовать метод `std::allocator_traits<Alloc>::construct`, который в свою очередь вызовет `std::construct_at`, а вместо прямого вызова деструктора следует использовать метод `std::allocator_traits<Alloc>::destroy`, который в свою очередь вызовет `std::destroy_at`. Более того, так как мы не знаем тип логгера в момент создания `Spy`, нам придётся использовать аллокатор на тип `std::byte`. Однако функции `construct` и `destroy` принимают шаблонным параметром тип, который необходимо сконструировать, поэтому один и тот же аллокатор может аллоцировать память для и конструировать любые логгеры.

Ознакомьтесь с именованым набором требований [AllocatorAwareContainer](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer). Прочитайте занимательную [статью](https://www.foonathan.net/2015/10/allocatorawarecontainer-propagation-pitfalls/) про смешные трейты `propagate_on_container_copy_assignment` и `propagate_on_container_move_assignment`. Не забудьте реалоцировать память в случае мув-присваивания `Spy` с ложным `propagate_on_container_move_assignment` и разными аллокаторами.

### Бонус 2: обобщённая таблица виртуальных вызовов (без баллов, без тестов, для безумцев)

Если вам совсем нечем заняться, придумайте (или украдите) дизайн и реализуйте обобщённый механизм таблиц виртуальных вызовов. В результате класс `Spy` должен уметь "убирать" стёртую функцию мува по запросу пользователя через политику "move-only" и весить на несколько байт меньше. Также должна быть возможность сделать политику вынесения таблицы виртуальных вызовов в статическое хранилище (в таком случае виртуальные вызовы будут работать за 2 индерекции, но сам `Spy` будет весить ещё меньше).

## Пример

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

## Вопросы для размышлений

1. С какими проблемами мы бы столкнулись, если бы захотели добавить константную версию оператора `->`?

2. Как бы вы модифицировали класс `Spy`, чтобы поддержать обращения к оборачиваемому объекту из нескольких потоков?

3. Можем ли мы аккуратно обработать всё случаи пометок `noexcept` стёртых методов логгера?

4. Хотелось бы, чтобы при перемещении внутри выражения счётчик сохранялся, как будто обращения происходят к одному и тому же объекту:

   `(a->doSmth(), (b = std::move(a))->doSmth()); // 2`

   Подумайте, как это можно реализовать без динамического выделения памяти? Почему такое решение будет работать? Если захочется, реализуйте.

## Формальности

**Дедлайн:** 04:00 14.11.2020.

**Баллы:** 3 (+2) уе.

Код пушьте в ветку `task3` и делайте pull request в `master`.

Используйте всю мощь стандартной библиотеки, кроме `std::function` и `std::any`.

Отвечать на вопросы для размышлений необязательно.

## Тесты

Тесты этого задания собираются с address и UB санитайзерами. Будьте осторожны, делая бонусный уровень!
