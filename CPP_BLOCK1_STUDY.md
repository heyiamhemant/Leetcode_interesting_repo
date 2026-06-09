# C++ Deep — Block 1: Modern C++ Foundations

**Week 1 study deck. 25 questions, ~10 hr/week target.**

Calibrated for senior/staff R&D C++ interviews at Synopsys Canada, Cadence Canada, Arm Waterloo (perf modeling), Tenstorrent compiler/runtime, NVIDIA Toronto, AMD Markham.

## How to use

1. Cover the answer. Write your own answer in DSA_Dojo's `notes` field per question (id 336–360, topic *C++ Deep*).
2. Reveal answer. Score yourself 0–3 in `conf`:
   - **0** — wrong / blank
   - **1** — partial (got the gist, missed the why or the code)
   - **2** — correct but slow / needed prompting
   - **3** — fluent, could teach it
3. After 25 done, redo every `conf <= 1` question without looking.
4. Mark `reviewed=1` only when you've hit `conf=3` twice on different days.

**Time budget**: 25 questions × ~25 min avg = ~10 hours over 7 days. Schedule: 4 weekday evenings × 1 hr + Sat/Sun × 3 hr.

**Sources**: Scott Meyers, *Effective Modern C++* (Items 1–25); cppreference.com; Herb Sutter / Andrei Alexandrescu talks.

---

## Section A — Type Deduction (Q1–5)

<a id="q1"></a>
### Q1 · Medium · Templates / Type Deduction

**Question**: Given the template
```cpp
template <typename T> void f(T param);
template <typename T> void g(T& param);
template <typename T> void h(T&& param);
```
what is the deduced type of `T` and the parameter type for these calls?

```cpp
int x = 27;
const int cx = x;
const int& rx = x;
int arr[5];
const char name[] = "hello";

f(x);      // (1)
f(cx);     // (2)
f(rx);     // (3)
f(arr);    // (4)
g(arr);    // (5)
h(x);      // (6)
h(27);     // (7)
```

**Why it's asked**: Every C++ interview opens with deduction. Getting `arr` decay and forwarding-ref collapsing wrong is the most common signal of a candidate who has used C++ without understanding it.

**Answer**:

| Call | T | param type | Note |
|---|---|---|---|
| (1) `f(x)` | `int` | `int` | Top-level const/ref/volatile stripped from non-ref `T` |
| (2) `f(cx)` | `int` | `int` | `const` is top-level here — stripped |
| (3) `f(rx)` | `int` | `int` | Ref-ness stripped, then top-level const stripped |
| (4) `f(arr)` | `int*` | `int*` | Array decays to pointer for **by-value** template params |
| (5) `g(arr)` | `int[5]` | `int (&)[5]` | Ref params **preserve** array type — useful for `arraySize<N>` |
| (6) `h(x)` | `int&` | `int&` | `x` is lvalue → `T` deduces to `int&` → collapses to `int&` |
| (7) `h(27)` | `int` | `int&&` | `27` is rvalue → `T` deduces to `int` → param is `int&&` |

**Pitfall**: For `T&&` (a *forwarding reference*, not an rvalue reference) deduction depends entirely on value category of the argument. Lvalue → `T&`, rvalue → `T`. Reference collapsing then produces `T&` or `T&&`.

**Drill-down**: Write the `arraySize` template that returns the compile-time size of a C array.
```cpp
template <typename T, size_t N>
constexpr size_t arraySize(T (&)[N]) noexcept { return N; }
```

---

<a id="q2"></a>
### Q2 · Hard · auto / Forwarding Reference

**Question**: Explain what `auto&&` means and how it differs from `int&&`. Then evaluate:

```cpp
auto&& a = 42;
auto&& b = a;
const auto&& c = 42;
const auto&& d = a;   // compile?
```

**Why it's asked**: Forwarding references through `auto&&` are everywhere in modern C++ (range-for, generic lambdas). Confusing them with rvalue refs breaks `std::forward` chains in tests.

**Answer**:

- `auto&&` is a **forwarding reference** — it follows the same deduction rules as `T&&` in templates. The deduced type depends on the initializer's value category.
- `int&&` is a true **rvalue reference** — only binds to rvalues, never to lvalues.

For the snippets:

```cpp
auto&& a = 42;     // 42 is rvalue → auto = int   → a is int&&
auto&& b = a;      // a is lvalue → auto = int&  → collapse → b is int&
const auto&& c = 42;  // const + rvalue ref → c is const int&&
const auto&& d = a;   // ERROR — a is lvalue, can't bind to const rvalue ref
```

The `const` on `auto&&` *defeats* the forwarding reference. Once you add `const`, `auto&&` becomes a true rvalue reference (`const X&&`) and won't deduce from lvalues.

**Pitfall**: `for (auto&& x : container)` is the safe default precisely because `auto&&` binds to anything. But `for (const auto&& x : container)` is silently broken — it can't bind to lvalues, which most containers yield.

**Drill-down**: In a generic lambda, why is `[](auto&& x) { use(std::forward<decltype(x)>(x)); }` the correct forwarding pattern? Because `decltype(x)` recovers the original reference category (lvalue ref or rvalue ref) that `auto&&` deduced.

---

<a id="q3"></a>
### Q3 · Medium · decltype vs auto

**Question**: Given
```cpp
const int  ci = 0;
const int& cr = ci;
int x = 0;

auto     a1 = cr;    // type?
decltype(cr) a2 = cr; // type?
auto     a3 = x;     // type?
decltype(x) a4 = x;  // type?
decltype((x)) a5 = x; // type?
```
What are the types of a1..a5?

**Why it's asked**: Tests whether you understand that `auto` strips qualifiers like template-by-value deduction does, but `decltype` preserves the exact declared type — and **`decltype((expr))` of an lvalue expression gives `T&`**.

**Answer**:

| Var | Type | Reason |
|---|---|---|
| `a1` | `int` | `auto` strips ref and top-level const |
| `a2` | `const int&` | `decltype` preserves the exact declared type of name `cr` |
| `a3` | `int` | `auto` from `int` lvalue → `int` |
| `a4` | `int` | `decltype` of a *name* → its declared type |
| `a5` | `int&` | `decltype` of an *expression* (parens make it an expression) → `T&` if lvalue |

**Pitfall**: `decltype(auto)` (C++14) means "deduce like `decltype` would, applied to the initializer expression." Forgetting the parens-wrap rule causes the silent bug below.

```cpp
decltype(auto) f1() { int x = 0; return x; }    // returns int
decltype(auto) f2() { int x = 0; return (x); }  // returns int& -> DANGLING!
```

**Drill-down**: Why is `decltype(auto)` preferred over `auto` for proxy-returning generic forwarders? Because `auto` strips reference-ness and breaks forwarding through proxies like `vector<bool>::reference`.

---

<a id="q4"></a>
### Q4 · Easy · auto Pitfall: Proxy Types

**Question**: This code looks innocent. What's wrong?

```cpp
std::vector<bool> features = computeFeatures();
auto highPriority = features[5];
processFeature(highPriority);  // expects a bool
```

**Why it's asked**: Tests awareness of "invisible" proxy types (vector<bool>::reference, expression templates in Eigen/Boost, etc.).

**Answer**: `std::vector<bool>::operator[]` does **not** return `bool&` — it returns a temporary proxy object `std::vector<bool>::reference`. `auto` deduces `highPriority` as that **proxy**, not as `bool`. The temporary `vector<bool>` (if `features` was a temporary) dies at the end of the full-expression, leaving `highPriority` as a **dangling proxy**.

Fix — force the type:
```cpp
auto highPriority = static_cast<bool>(features[5]);
// or
bool highPriority = features[5];
```

**Pitfall**: This is the canonical "invisible proxy" trap. Same problem with Eigen's expression templates: `auto m = A * B + C;` may return an expression template that holds dangling references to `A`, `B`, `C`.

**Drill-down**: When is the "explicitly typed initializer idiom" (`auto x = static_cast<T>(expr);`) better than just `T x = expr;`? Mostly when `T` is verbose or when you want to make the intentional conversion visible in code review.

---

<a id="q5"></a>
### Q5 · Hard · decltype(auto) Return Type

**Question**: You're writing a generic indexing wrapper:
```cpp
template <typename Container, typename Index>
??? access(Container& c, Index i) {
    authenticateUser();
    return c[i];
}
```
What should the return type be, and why are `auto`, `auto&`, `decltype(auto)` all different here?

**Why it's asked**: Tests whether you can write transparent wrappers over `operator[]` that preserve mutability — directly relevant for EDA tooling that wraps STL containers.

**Answer**:

| Return type | Behavior | Problem |
|---|---|---|
| `auto` | Returns by value | Caller can't write `access(v, 3) = 42;` even when `c[i]` is mutable |
| `auto&` | Returns lvalue ref | Breaks if `c[i]` returns by value (e.g., proxy from `vector<bool>`) |
| `decltype(auto)` | Preserves exact type of `c[i]` including ref-ness | **Correct** — works for both lvalue-ref returns and by-value returns |

```cpp
template <typename Container, typename Index>
decltype(auto) access(Container& c, Index i) {
    authenticateUser();
    return c[i];
}
```

**Pitfall**: Don't write `return std::forward<...>(c[i]);` here unless you actually want forwarding semantics — for a simple wrapper, `decltype(auto) return c[i];` is enough and safer.

**Drill-down**: How would you write the same wrapper using **C++20 trailing return type deduction** to support both lvalue and rvalue container arguments? Use forwarding reference:
```cpp
template <typename Container, typename Index>
decltype(auto) access(Container&& c, Index i) {
    return std::forward<Container>(c)[i];
}
```

---

## Section B — Initialization & Modern Syntax (Q6–10)

<a id="q6"></a>
### Q6 · Hard · Brace vs Paren Initialization

**Question**: Predict and explain the output:

```cpp
std::vector<int> v1(10, 5);   // (a)
std::vector<int> v2{10, 5};   // (b)
int  a(3.7);                  // (c)
int  b{3.7};                  // (d)
class W { public: W(int){} W(std::initializer_list<int>){} };
W w1(10);                     // (e)
W w2{10};                     // (f)
W w3({10});                   // (g)
```

**Why it's asked**: Tests whether you've internalized the three brace-init rules: narrowing-forbidden, most-vexing-parse-immune, and the `initializer_list` overload-poisoning rule.

**Answer**:

| Code | Result | Why |
|---|---|---|
| (a) `v1(10, 5)` | Vector of **10 fives** | Calls `vector(size_type, value_type)` ctor |
| (b) `v2{10, 5}` | Vector of **{10, 5}** | `initializer_list<int>` ctor wins over the (size,value) ctor |
| (c) `int a(3.7)` | `a = 3` | Allows narrowing — silent truncation |
| (d) `int b{3.7}` | **Compile error** | Brace init forbids narrowing conversions |
| (e) `W w1(10)` | Calls `W(int)` | Parens never pick `initializer_list` |
| (f) `W w2{10}` | Calls `W(initializer_list)` | Brace prefers `initializer_list` ctor when one exists, even with implicit single-arg match |
| (g) `W w3({10})` | Calls `W(initializer_list)` | Explicit `initializer_list` argument |

**Pitfall**: Adding an `initializer_list` constructor to a class **silently changes** brace-init behavior of every existing call site. STL classes (`vector`, `map`) live with this; your own classes should think twice before adding both kinds of ctors.

**Drill-down**: When does brace init solve the *most vexing parse*? `W w(X());` is parsed as a function declaration `w` returning `W`, taking a function returning `X`. `W w{X()};` is unambiguously an object construction.

---

<a id="q7"></a>
### Q7 · Easy · nullptr vs NULL vs 0

**Question**: Why is `nullptr` strictly preferred? Show a case where `NULL` or `0` causes an overload ambiguity that `nullptr` fixes.

**Why it's asked**: Trivial-looking but often gets a wrong "it's just nicer syntax" answer. The real reason is overload resolution.

**Answer**: `NULL` is typically `#define NULL 0` or `((void*)0)` — an *integral type*, not a pointer. `0` is an integer. Both undergo integral-promotion overload resolution that picks the wrong overload:

```cpp
void f(int);
void f(void*);

f(NULL);    // ambiguous or calls f(int) — depends on macro definition
f(0);       // calls f(int)
f(nullptr); // calls f(void*) — nullptr has type std::nullptr_t, only converts to pointer
```

Also: `nullptr` works inside templates without breaking type deduction (a `0` argument deduces `T = int`, not `T*`).

**Pitfall**: `std::nullptr_t` is a real type. You can write `void f(std::nullptr_t);` as an overload.

**Drill-down**: Why does the standard not just deprecate `NULL`? Backward compatibility — billions of lines of legacy code. C++23 still keeps it.

---

<a id="q8"></a>
### Q8 · Easy · using vs typedef

**Question**: Beyond syntax, what does `using` give you that `typedef` cannot?

**Why it's asked**: Tests awareness of alias templates — used heavily in modern metaprogramming and tool architecture.

**Answer**: `using` supports **template aliases**, `typedef` does not.

```cpp
// typedef can't do this:
template <typename T>
typedef std::vector<T, MyAlloc<T>> MyVec;  // ERROR

// using does:
template <typename T>
using MyVec = std::vector<T, MyAlloc<T>>;

MyVec<int> v;  // == std::vector<int, MyAlloc<int>>
```

Pre-C++11 workaround was an empty struct holding the typedef inside, which required `typename MyVecHelper<T>::type` — clunky.

**Pitfall**: `using namespace X;` is the unrelated using-directive — don't confuse with `using` for type aliases.

**Drill-down**: When writing templated containers/wrappers (like a templated `Cache<K, V>` for an EDA tool), prefer `using` for all internal typedefs — keeps the code consistent and template-alias-ready.

---

<a id="q9"></a>
### Q9 · Medium · Scoped vs Unscoped Enums

**Question**: List the three concrete advantages of `enum class` over plain `enum`. Show one case where plain `enum` is genuinely better.

**Why it's asked**: Tests modern hygiene without being a trivia question.

**Answer**:

Advantages of `enum class`:
1. **Strongly scoped** — names don't leak into the enclosing namespace. `Color::Red` vs `Red`.
2. **No implicit conversion to int** — `int x = Color::Red;` is an error. Forces intent.
3. **Forward-declarable** with explicit underlying type — `enum class Color : uint8_t;` in a header, full definition elsewhere → reduces include dependencies.

Plain `enum` is better only when you genuinely want bit-field-style integer interop, e.g.:
```cpp
enum AccessFlags { Read = 1, Write = 2, Execute = 4 };
int flags = Read | Write;  // implicit conversions help here
```
With `enum class` you'd need `static_cast<int>(AccessFlags::Read)` everywhere.

**Pitfall**: You can give scoped enums a custom underlying type (`enum class E : uint16_t {}`) — useful for serialization and ABI control. Unscoped enums can also have explicit underlying types since C++11.

**Drill-down**: How do scoped enums interact with `switch`? You must qualify each case (`case Color::Red:`), but the compiler will warn if you forget a case — better safety than plain enums.

---

<a id="q10"></a>
### Q10 · Easy · = delete vs private undefined

**Question**: Pre-C++11, the standard "non-copyable" pattern was:
```cpp
class NonCopy {
private:
    NonCopy(const NonCopy&);
    NonCopy& operator=(const NonCopy&);
};
```
Why is `= delete` strictly better than this pattern, beyond aesthetics?

**Why it's asked**: Tests whether you can articulate the *visibility* and *function-overload* benefits of `= delete`.

**Answer**:

1. **Better error messages** — `= delete` produces "use of deleted function" at the call site. The private-undefined trick produces an `undefined reference` linker error from inside the implementation, often with no clue which call triggered it.

2. **Deletes work for any function, not just special members**. You can delete specific overloads:
```cpp
void f(int);
void f(double) = delete;   // ban implicit promotion from float/double
void f(char) = delete;     // ban implicit char promotion
```

3. **`= delete` functions can be at any access level** — convention is `public`, since "deleted" + "public" gives the cleanest error message.

4. **Works in template specializations** to ban specific instantiations:
```cpp
template <typename T> void process(T);
template <> void process<void*>(void*) = delete;
```

**Pitfall**: `= delete` deletes only that specific overload — it doesn't propagate to copies/conversions. To prevent all copying, delete both copy ctor and copy assignment.

**Drill-down**: What's `= default`? It explicitly asks the compiler to generate the default version of a special member function. Useful when you've added other special members and want to preserve the default ones, or to express intent.

---

## Section C — const / override / noexcept / constexpr (Q11–15)

<a id="q11"></a>
### Q11 · Medium · override and final

**Question**: This compiles but is silently wrong. Identify all the bugs:

```cpp
class Base {
public:
    virtual void mf1() const;
    virtual void mf2(int x);
    virtual void mf3() &;
    void mf4() const;  // not virtual
};

class Derived : public Base {
public:
    virtual void mf1();              // (a)
    virtual void mf2(unsigned int x); // (b)
    virtual void mf3() &&;           // (c)
    virtual void mf4() const;        // (d)
};
```
None of these override the base. How does `override` save you?

**Why it's asked**: Silent override-failure is one of the most common production bugs in OO C++ codebases. Senior interviewers always ask this.

**Answer**: None of (a)–(d) override:

| | Reason |
|---|---|
| (a) | Missing `const` qualifier — different cv-qualifications |
| (b) | Parameter type differs (`int` vs `unsigned int`) — no implicit override |
| (c) | Reference qualifier differs (`&` vs `&&`) |
| (d) | Base function isn't virtual to begin with |

Adding `override` would make each a compile error and force the fix:
```cpp
virtual void mf1() override;       // ERROR — base has const, fix it
virtual void mf1() const override; // OK
```

**Pitfall**: `override` is a *contextual* keyword — it's only special after a member function declaration. You can have a member variable named `override` (don't, but you can).

**Drill-down**: What does `final` do at the class vs method level? On a class — no one can derive from it. On a virtual method — no override can override it further. Both can help devirtualization in optimizers.

---

<a id="q12"></a>
### Q12 · Hard · const Member Functions & Thread Safety

**Question**: This `const` method is a data race waiting to happen. Why?

```cpp
class Polynomial {
    mutable std::vector<double> rootCache_;
    mutable bool cacheValid_ = false;
public:
    const std::vector<double>& roots() const {
        if (!cacheValid_) {
            rootCache_ = computeRoots();
            cacheValid_ = true;
        }
        return rootCache_;
    }
};
```
Two threads call `roots()` concurrently on the same `Polynomial`. The method is `const`. Is it safe?

**Why it's asked**: Tests whether you understand the standard library's *"const == thread-safe"* contract and the lazy-init thread-safety pattern. Directly relevant to your shared-memory caching layer experience — exactly this class of bug.

**Answer**: **Not safe.** The standard library assumes `const` member functions are safe to call concurrently from multiple threads on the same object. This one violates that — two threads can enter the `if`, both write to `rootCache_`, and tear it.

The `mutable` keyword bypasses `const` for the compiler but **doesn't bypass the thread-safety contract** you owe callers.

Fix — protect mutation:
```cpp
class Polynomial {
    mutable std::mutex m_;
    mutable std::vector<double> rootCache_;
    mutable bool cacheValid_ = false;
public:
    const std::vector<double>& roots() const {
        std::lock_guard<std::mutex> g(m_);
        if (!cacheValid_) {
            rootCache_ = computeRoots();
            cacheValid_ = true;
        }
        return rootCache_;
    }
};
```

For single-counter mutables, use `std::atomic<T>` instead of mutex — much faster for the read-fast-path.

**Pitfall**: Returning `const T&` from a `const` method while the internal cache may be mutated by a later `const` call from another thread → caller's reference dangles or sees torn data. Either return by value, or hold the mutex on the read path too.

**Drill-down**: How does this map to your Synopsys shared-memory cache work? Multiple processes, not threads — so `std::mutex` doesn't help. You need POSIX shared mutexes (`pthread_mutex_init` with `PTHREAD_PROCESS_SHARED`) or futex-based atomic counters in shared memory. Exactly the kind of follow-up Synopsys Canada will ask.

---

<a id="q13"></a>
### Q13 · Medium · noexcept

**Question**: Beyond documentation, when does `noexcept` actually matter to the compiler/library?

**Why it's asked**: Tests whether you know the **move-vs-copy selection** inside STL containers.

**Answer**: Three concrete cases where `noexcept` is observable:

1. **`std::vector::push_back` and friends**: when the vector needs to grow, it uses `std::move_if_noexcept` to decide between moving and copying existing elements. If the move constructor is **not** `noexcept`, the vector falls back to copy to preserve the strong exception guarantee. Marking your move ctor `noexcept` can speed up vector reallocations by 10–100x.

2. **`std::swap`** is `noexcept(noexcept(...))` for many types — declaring your `swap` `noexcept` enables noexcept-friendly composition.

3. **Stack unwinding optimizations** — the compiler can omit unwind tables for `noexcept` functions, saving binary size.

```cpp
class MyType {
public:
    MyType(MyType&&) noexcept;          // critical for vector<MyType> perf
    MyType& operator=(MyType&&) noexcept;
};
```

**Pitfall**: `noexcept` is a hard promise. Throwing from a `noexcept` function calls `std::terminate` directly — no destructor cleanup, no stack unwinding. Don't slap `noexcept` on everything; only on functions you can prove (or by definition cannot) throw.

**Drill-down**: What's `noexcept(noexcept(expr))`? Conditional noexcept — "this function is noexcept if `expr` is noexcept." Used in generic code that propagates noexcept-ness through composition.

---

<a id="q14"></a>
### Q14 · Hard · constexpr Functions vs Variables

**Question**: Walk through the difference between `const`, `constexpr`, and `consteval`. Then explain: what changed for `constexpr` functions from C++11 → C++14 → C++17 → C++20?

**Why it's asked**: Compile-time computation is heavily used in EDA tool code (lookup tables, tag dispatch). Tests whether you know what's actually allowed inside a `constexpr` body.

**Answer**:

| Keyword | Meaning |
|---|---|
| `const` | Value cannot change after init. Can be runtime-initialized. |
| `constexpr` (variable) | Must be initialized with a constant expression — known at compile time. Implies `const`. |
| `constexpr` (function) | *May* be evaluated at compile time when called with constant args; otherwise runs at runtime. |
| `consteval` (C++20) | **Must** be evaluated at compile time. Compile error if called with non-constant args. |
| `constinit` (C++20) | Variable must be initialized at compile time, but may be mutated later. Solves static-init-order fiasco. |

Evolution of `constexpr` function bodies:

- **C++11**: Single `return` statement only. No loops, no locals, no branching beyond ternary.
- **C++14**: Multi-statement bodies, local variables, `if`/`switch`/loops, mutation of locals.
- **C++17**: `constexpr if`, lambdas in constexpr context.
- **C++20**: `try`/`catch` (but throwing makes it non-constexpr), `dynamic_cast`, `typeid`, allocations via `new`/`delete` (with the result freed during constant evaluation).

```cpp
constexpr int factorial(int n) {       // C++14+
    int result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

constexpr int v = factorial(5);   // compile-time
int x = readInt();
int y = factorial(x);             // runtime
```

**Pitfall**: A `constexpr` function called with non-constant args runs at runtime. To force compile-time evaluation, assign result to a `constexpr` variable or use `consteval`.

**Drill-down**: Why use `constexpr` for things like a sin/cos lookup table in an EDA tool? Generated at compile time → zero runtime initialization cost, table goes in `.rodata`, sharable across processes, cache-friendly.

---

<a id="q15"></a>
### Q15 · Medium · cbegin/cend & const-correct Generics

**Question**: Why prefer `std::cbegin(c)` over `c.cbegin()` in template code?

**Why it's asked**: Tests awareness of non-member function overloads — the foundation of generic STL-like code.

**Answer**: `std::cbegin(c)` is a non-member function that works for:
1. Standard containers with a `cbegin()` member.
2. **C-style arrays** (`int arr[10]`) — no member functions at all.
3. User types that provide `begin()`/`end()` but not `cbegin()` (very common in third-party code) — `std::cbegin` synthesizes the const iterator from `std::begin(c)`.

```cpp
template <typename C, typename V>
auto findValue(const C& c, const V& target) {
    return std::find(std::cbegin(c), std::cend(c), target);  // works for arrays + non-STL types
}
```

**Pitfall**: Using `c.cbegin()` in templates excludes C arrays and many third-party containers — `std::cbegin` is strictly more general.

**Drill-down**: Same reasoning applies to `std::size(c)`, `std::data(c)`, `std::empty(c)` (C++17). Always prefer non-member free functions in generic code.

---

## Section D — Special Member Functions (Q16–18)

<a id="q16"></a>
### Q16 · Hard · Rule of 0 / 3 / 5

**Question**: A user declares a destructor for logging purposes:
```cpp
class Widget {
    std::vector<int> data_;
public:
    ~Widget() { LOG("destroyed"); }
};

Widget w1;
Widget w2 = std::move(w1);  // does this move or copy?
```
What happens, and why? Walk through the special-member-generation rules.

**Why it's asked**: The Rule of 5 / Rule of 0 governs every modern C++ class design. Getting this wrong silently kills move performance.

**Answer**: Declaring a destructor **suppresses move generation**. So `w2 = std::move(w1)` falls back to the **copy constructor** (which is still generated because copy generation is only deprecated, not removed, when dtor is user-declared).

The full rule table:

| User declares | Compiler generates |
|---|---|
| Nothing | default ctor, dtor, copy ctor, copy=, move ctor, move= |
| Any constructor | dtor, copy ctor, copy=, move ctor, move= (no default ctor) |
| Destructor | copy ctor, copy= (**no moves**) |
| Copy ctor or copy= | the other copy, dtor (**no moves**) |
| Move ctor or move= | dtor (**no copies**, no other move — they're deleted) |

**Rule of 5**: If you declare any of `{destructor, copy ctor, copy=, move ctor, move=}`, you probably need to declare or `= default` all five.

**Rule of 0**: Best practice — design classes that don't need any custom special members. Use RAII members (`unique_ptr`, `vector`, etc.) and let the compiler generate all five correctly.

Fix the Widget:
```cpp
class Widget {
    std::vector<int> data_;
public:
    ~Widget() { LOG("destroyed"); }
    Widget() = default;
    Widget(const Widget&) = default;
    Widget& operator=(const Widget&) = default;
    Widget(Widget&&) = default;
    Widget& operator=(Widget&&) = default;
};
```

**Pitfall**: Adding a destructor "just for logging" can secretly turn every move into a copy in your codebase. Profilers often miss this because the copy is invoked from the move site.

**Drill-down**: How does this interact with `std::vector<Widget>::push_back`? If Widget's move is suppressed, every reallocation copies all elements instead of moving — O(N) potentially-expensive copies per growth.

---

<a id="q17"></a>
### Q17 · Medium · = default for Special Members

**Question**: What's the difference between an implicitly-generated default constructor and one written as `Widget() = default;`? Both seem equivalent.

**Why it's asked**: Tests whether you know about the "non-trivial" distinction that matters for ABI and constexpr.

**Answer**: Functionally identical for behavior, but:

1. **`= default` preserves "trivial" classification** even when paired with a user-declared dtor or other ctors. Implicit generation may not happen at all once another ctor is declared, so `= default` is the only way to keep the default ctor available.

2. **`= default` can be `constexpr`**:
   ```cpp
   constexpr Widget() = default;  // requires all members to be constexpr-default-constructible
   ```

3. **Visibility documentation** — `= default` in a header makes the intent explicit to readers and code review tools.

4. **`= default` outside the class body** (in `.cpp`) can be useful when the dtor needs to see a complete type from the header (e.g., Pimpl idiom — see Q24).

**Pitfall**: A user-declared default ctor (with empty body `Widget() {}`) is **not** trivial, even if it does nothing. `Widget() = default;` is trivial. This matters for `std::is_trivially_constructible_v`, which some library code uses for memcpy optimizations.

**Drill-down**: When would you write `Widget() = delete;`? To prevent default construction — useful for types that must always be initialized with specific data (e.g., a `Connection` class that requires a URL).

---

<a id="q18"></a>
### Q18 · Hard · Special Members with Smart Pointer Members

**Question**: Given:
```cpp
class Holder {
    std::unique_ptr<Impl> p_;
public:
    // intentionally empty
};
```
Is `Holder` movable? Copyable? Default-constructible?

**Why it's asked**: Combines special-member-generation rules with `unique_ptr`'s `= delete`d copy. Common interview confusion source.

**Answer**:

- **Default-constructible**: Yes — `p_` is default-initialized to `nullptr`.
- **Movable**: Yes — implicit move ctor/assign generated; they move `p_`.
- **Copyable**: **No** — copy ctor/assign are *implicitly deleted* because `unique_ptr` is not copyable. Attempting `Holder h2 = h1;` is a compile error.

The compiler doesn't refuse to declare the class — it deletes the copy operations that can't compile. Same mechanism for `std::mutex`, `std::thread`, `std::atomic` members.

**Pitfall**: If you then write a custom destructor (e.g., for logging), the implicit moves get suppressed — and now `Holder` becomes **not movable, not copyable**. You'd have to explicitly `= default` the moves to recover.

**Drill-down**: How does this compose with `std::vector<Holder>`? You can construct a `vector<Holder>`, but you cannot copy it. You can move it. `push_back` works only if Holder is movable (or copyable, which it isn't). Use `emplace_back(...)` to construct in place.

---

## Section E — Smart Pointers (Q19–25)

<a id="q19"></a>
### Q19 · Medium · unique_ptr Custom Deleter Cost

**Question**: Compare the sizeof of these three unique_ptrs:
```cpp
std::unique_ptr<File>                           p1;            // (a)
std::unique_ptr<File, decltype(&fclose)>        p2(nullptr, fclose);  // (b)
std::unique_ptr<File, decltype([](File* f){ fclose(f); })> p3;  // (c)
```
Which are 8 bytes, which are 16, and why?

**Why it's asked**: Tests understanding of empty-base optimization and stateful-deleter cost — directly relevant to writing zero-overhead RAII wrappers.

**Answer** (on 64-bit):

| Ptr | Size | Reason |
|---|---|---|
| (a) | **8 bytes** | Default deleter is empty; EBO eliminates it |
| (b) | **16 bytes** | Function pointer deleter — must store the function pointer |
| (c) | **8 bytes** | Stateless lambda is empty; EBO applies |

The default `std::default_delete<T>` is an empty struct → empty-base optimization collapses it to zero overhead. A function pointer (`&fclose`) is *stateful* (8 bytes) — adds size. A stateless lambda is empty, so EBO applies.

```cpp
// Equivalent and same size as (c):
struct FCloseDeleter { void operator()(File* f) const { fclose(f); } };
std::unique_ptr<File, FCloseDeleter> p4;  // 8 bytes
```

**Pitfall**: Capturing lambdas are not empty → use the same as function pointer (sizeof grows). Prefer stateless functor or stateless lambda for deleters.

**Drill-down**: `shared_ptr<T>` always allocates a control block for the deleter regardless of stateless-ness — so deleter size has different cost implications for `shared_ptr`.

---

<a id="q20"></a>
### Q20 · Hard · shared_ptr Control Block

**Question**: What's inside `shared_ptr<T>`'s control block, and what does `sizeof(shared_ptr<T>)` give you?

**Why it's asked**: Tests low-level understanding of `shared_ptr` cost — critical for perf-modeling and tool architecture interviews.

**Answer**:

`sizeof(shared_ptr<T>)` = **16 bytes** on 64-bit (two pointers):
1. Pointer to the managed object.
2. Pointer to the control block.

The control block (allocated separately on the heap, unless `make_shared`) contains:
- **Strong reference count** (atomic, typically `long`)
- **Weak reference count** (atomic, typically `long`)
- **Deleter** (type-erased)
- **Allocator** (type-erased)
- Often a virtual table pointer (the control block is polymorphic to dispatch deleter/allocator).

Total control block: typically **~24–48 bytes** depending on stdlib.

Atomic operations on the ref count are **expensive** (cache-line bouncing, full memory barriers on some architectures). Copying a `shared_ptr` is *not* free — it's an atomic increment. Across threads sharing a pointer to the same object, the cache line containing the ref count becomes a contention hotspot (false sharing if other unrelated atomics are nearby).

**Pitfall**: Passing `shared_ptr` by value in hot paths kills perf. Pass by `const shared_ptr<T>&` when you don't need shared ownership in the callee, or pass the raw `T*` (or reference) if the callee only borrows.

**Drill-down**: Why are weak refs separate from strong refs? Because the control block must outlive the object — `weak_ptr` keeps the control block alive (for `expired()` checks) even after the object is destroyed. The object dies when strong=0; the control block dies when both strong=0 and weak=0.

---

<a id="q21"></a>
### Q21 · Medium · weak_ptr & Cyclic References

**Question**: This code leaks. Find the cycle and fix it.

```cpp
struct Node {
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;
};

auto a = std::make_shared<Node>();
auto b = std::make_shared<Node>();
a->next = b;
b->prev = a;
// when a and b go out of scope, neither is freed
```

**Why it's asked**: Cycle-detection in shared_ptr graphs is the most common shared_ptr bug. Tests whether you can spot and fix it.

**Answer**: Both `a` and `b` have strong ref count = 2 when entering scope (their own + the cross-pointer). When local `a` and `b` go out of scope, both drop to 1, never 0. Classic memory leak.

Fix — break the cycle with `weak_ptr` for the "back-pointer":
```cpp
struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node>   prev;   // back-edge is weak
};
```

To use `prev`, call `.lock()` to get a `shared_ptr` (returns empty if the pointee is gone):
```cpp
if (auto p = node.prev.lock()) {
    use(*p);
}
```

**Pitfall**: Convention for trees/graphs: parent→child uses `shared_ptr`, child→parent uses `weak_ptr`. Same for observer patterns: subject holds `weak_ptr` to observers.

**Drill-down**: Is there a runtime way to detect shared_ptr cycles? Not in the std library. You'd need to instrument with a custom allocator or use a debugger plugin. Best defense is design-time discipline.

---

<a id="q22"></a>
### Q22 · Medium · make_shared vs new + shared_ptr

**Question**: List the three concrete reasons to prefer `std::make_shared<T>(args...)` over `std::shared_ptr<T>(new T(args...))`.

**Why it's asked**: Tests whether you know the allocation, exception-safety, and source-clarity angles.

**Answer**:

1. **Single allocation**. `make_shared` allocates one block containing both the object and the control block. `new T` + `shared_ptr` ctor performs two allocations and two frees. ~2x faster for small objects, and better cache locality (object and control block adjacent).

2. **Exception safety** in argument-evaluation orderings:
   ```cpp
   processWidget(std::shared_ptr<Widget>(new Widget), computePriority());
   ```
   If `computePriority` throws *between* `new Widget` and the `shared_ptr` ctor, the Widget leaks. C++17 tightened evaluation order to mostly prevent this, but `make_shared` makes it impossible:
   ```cpp
   processWidget(std::make_shared<Widget>(), computePriority());  // safe
   ```

3. **No `new` in user code** — fewer raw `new`s = fewer chances to forget a delete or pair with the wrong smart pointer.

**Pitfall**: `make_shared` has two gotchas — see Q23.

**Drill-down**: `std::make_unique<T>` (C++14) — same allocation/exception-safety argument applies but `make_unique` does NOT do the single-allocation trick (there's no control block for `unique_ptr` to fuse with). It's still preferred for the exception-safety + readability reasons.

---

<a id="q23"></a>
### Q23 · Hard · make_shared Anti-Patterns

**Question**: When should you NOT use `make_shared`?

**Why it's asked**: Most candidates know "prefer make_shared" but few can articulate when it's actively wrong.

**Answer**: Three cases where you should use `new T` + `shared_ptr` ctor instead:

1. **You need a custom deleter**. `make_shared` doesn't accept one — only the default deleter:
   ```cpp
   auto sp = std::shared_ptr<File>(fopen(...), [](File* f){ fclose(f); });
   ```

2. **Custom allocator needed** — use `std::allocate_shared(alloc, args...)` instead, which is the allocator-aware sibling of `make_shared`.

3. **Large object + long-lived `weak_ptr` observers**. With `make_shared`, the object and control block share one allocation. The allocation lives until both strong **and** weak refs hit zero. So a 1 MB object with one weak_ptr observer keeps **the entire 1 MB block alive** until the weak_ptr also dies — not just the ~32 bytes of control block. With `new T` + `shared_ptr`, the object's 1 MB is freed when strong→0, and only the small control block stays around for the weak_ptr.

```cpp
// Bad for large objects with weak observers:
auto sp = std::make_shared<BigObject>();  // 1 MB stays alive while any weak_ptr exists

// Better:
std::shared_ptr<BigObject> sp(new BigObject);  // 1 MB freed when strong→0
```

**Pitfall**: This issue is invisible until you profile memory in long-running services. EDA tool flows that hold weak observers across multi-hour runs are a real-world case.

**Drill-down**: Same reasoning applies to `std::enable_shared_from_this` — it's compatible with both `new` and `make_shared`, no preference change.

---

<a id="q24"></a>
### Q24 · Hard · Pimpl with unique_ptr

**Question**: This Pimpl pattern compiles in the .cpp but **fails to compile** in a caller's translation unit. Why?

```cpp
// widget.h
class Widget {
    struct Impl;
    std::unique_ptr<Impl> p_;
public:
    Widget();
    // dtor implicit
};

// widget.cpp
struct Widget::Impl { /* ... */ };
Widget::Widget() : p_(std::make_unique<Impl>()) {}

// caller.cpp
#include "widget.h"
void f() {
    Widget w;   // ERROR: invalid application of sizeof to incomplete type 'Widget::Impl'
}
```

**Why it's asked**: This is the canonical Pimpl-idiom trap. Asked at every C++ shop.

**Answer**: The destructor of `Widget` is **implicitly defined** at the point where the class is first needed to be destructible — in `caller.cpp`. To destroy `unique_ptr<Impl>`, the compiler needs the complete definition of `Impl`. But `caller.cpp` only includes the header, which forward-declares `Impl`. Compiler error.

Fix — declare the destructor in the header, define it in the .cpp **after** `Impl` is complete:
```cpp
// widget.h
class Widget {
    struct Impl;
    std::unique_ptr<Impl> p_;
public:
    Widget();
    ~Widget();                       // declared only
    Widget(Widget&&) noexcept;       // also need these
    Widget& operator=(Widget&&) noexcept;
};

// widget.cpp
struct Widget::Impl { /* ... */ };
Widget::Widget() : p_(std::make_unique<Impl>()) {}
Widget::~Widget() = default;                   // defined here, where Impl is complete
Widget::Widget(Widget&&) noexcept = default;
Widget& Widget::operator=(Widget&&) noexcept = default;
```

**Pitfall**: Move ops also need to destroy the old `Impl` → same incomplete-type problem. Must be defined out-of-line too.

**Drill-down**: Why does the same problem not appear with `shared_ptr<Impl>`? Because `shared_ptr` stores its deleter type-erased in the control block — the deleter is created at the point of construction (where `Impl` is complete) and used from there. `unique_ptr`'s default deleter is a compile-time template parameter — it has to call `delete Impl` from wherever the destruction happens, requiring `Impl` to be complete at every destruction site.

---

<a id="q25"></a>
### Q25 · Medium · unique_ptr<T[]>

**Question**: When is `std::unique_ptr<T[]>` useful, and why is it usually discouraged in modern C++?

**Why it's asked**: Tests whether you know better alternatives exist.

**Answer**: `std::unique_ptr<T[]>` manages a dynamically-allocated array with `delete[]`. Specialization details:
- `operator[]` provided (not `operator*` or `operator->`).
- Doesn't support derived-to-base conversion.
- Doesn't support custom-deleter type matching with non-default deleters easily.

Legitimate use cases (narrow):
- Interfacing with C APIs that return raw arrays you must `delete[]`.
- Implementing low-level containers from scratch.
- When you really need a `T*` with no size carried alongside (size known externally).

Why discouraged:
- **`std::vector<T>`** does everything `unique_ptr<T[]>` does and also: knows its size, supports growth, has iterators, integrates with `<algorithm>`.
- **`std::array<T, N>`** for compile-time sizes — zero overhead, value semantics.
- **`std::span<T>`** (C++20) — non-owning view, replaces "pointer + size" parameter pairs.

```cpp
// Rarely justified:
std::unique_ptr<int[]> arr(new int[100]);

// Almost always better:
std::vector<int> arr(100);
```

**Pitfall**: `std::make_unique<T[]>(n)` does **value-initialize** every element. For large primitive arrays this is wasteful — `std::vector` with reserve+push or a custom default-init allocator is better.

**Drill-down**: When would `std::span<T>` replace `unique_ptr<T[]>` *and* `vector<T>` in an API? When the function doesn't take ownership — `span` is the universal "I want to read/write a contiguous range without caring who owns it" parameter type.

---

## End-of-Week Self-Assessment

After completing all 25 questions, rate yourself:

| Score | Meaning | Action |
|---|---|---|
| 60+ conf points (avg 2.4+) | Fluent on foundations | Proceed to Block 2 (Move & Forwarding) next week |
| 50–60 (avg 2.0–2.4) | Solid but slow | One more pass on `conf <= 1` questions, then proceed |
| 40–50 (avg 1.6–2.0) | Patchy | Spend Week 2 redoing all questions with full answer writing in notes field |
| <40 | Foundations weak | Read Effective Modern C++ Items 1–25 cover-to-cover before resuming |

**Top 5 questions to re-drill before any interview** (highest interview frequency):
- Q1 (template type deduction)
- Q6 (brace vs paren init)
- Q11 (override silent-fail)
- Q12 (const member thread safety) — your Synopsys shared-memory hook
- Q23 (make_shared anti-pattern with large objects + weak_ptr)

**Block 2 preview (next week)**: Move semantics deep dive — `std::move`, `std::forward`, perfect forwarding, reference collapsing, the rule of move-vs-copy elision. Most-asked block for perf-modeling roles.
