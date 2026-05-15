# 🏛️ Mastering Object-Oriented Programming in C++

<div align="center">

<img src="https://media.giphy.com/media/L8K62iTDkzGX6/giphy.gif" width="250"/>

# 🚀 Complete C++ OOP Journey

### *From Fundamentals to Advanced Object-Oriented Design*

<img src="https://img.shields.io/badge/C%2B%2B-17%20%7C%2020-blue?style=for-the-badge&logo=c%2B%2B"/>
<img src="https://img.shields.io/badge/OOP-Concepts-orange?style=for-the-badge"/>
<img src="https://img.shields.io/badge/DSA-Integrated-success?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Status-Active-green?style=for-the-badge"/>
<img src="https://img.shields.io/github/repo-size/your-username/your-repo?style=for-the-badge"/>
<img src="https://img.shields.io/github/stars/your-username/your-repo?style=for-the-badge"/>

<br>

<img src="https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=28&duration=3000&color=00C2FF&center=true&vCenter=true&width=900&lines=Object-Oriented+Programming+in+C%2B%2B;Abstraction+%7C+Encapsulation+%7C+Inheritance;Polymorphism+%7C+Templates+%7C+STL;From+Beginner+to+Advanced+Level;Clean+Code+%7C+Modern+C%2B%2B+Practices"/>

</div>

---

# 📖 About This Repository

This repository is a **complete roadmap to mastering Object-Oriented Programming in C++**.  
It contains:

- 📚 Structured topic-wise learning
- 🧠 Core OOP principles
- ⚡ Modern C++ concepts
- 🛠️ Real implementations
- 🎓 College practicals & assignments
- 🔥 Advanced memory management
- 🚀 Industry-level coding practices

Whether you're:
- 👨‍🎓 A student preparing for exams
- 💻 A beginner learning OOP
- 🧠 A DSA enthusiast
- 🚀 An aspiring software engineer

This repository is designed to help you build a **strong conceptual foundation** in C++ and OOP.

---

# 🎯 Core Objectives

✅ Understand Object-Oriented Programming deeply  
✅ Write clean and reusable code  
✅ Learn memory-safe programming  
✅ Master inheritance and polymorphism  
✅ Understand real-world class design  
✅ Explore modern C++ features  
✅ Build strong coding logic and implementation skills  

---

# 🧠 OOP Concepts Covered

<div align="center">

| Pillar | Description |
|---|---|
| 🧩 **Abstraction** | Hiding implementation details and exposing only functionality |
| 🔒 **Encapsulation** | Protecting data using access specifiers |
| 🧬 **Inheritance** | Reusing and extending existing classes |
| 🎭 **Polymorphism** | Same interface with multiple behaviors |
| 🧠 **Modularity** | Dividing code into manageable components |
| 🔁 **Dynamic Binding** | Runtime method resolution using virtual functions |
| 📦 **Composition** | Building complex systems using objects |

</div>

---


## ✨ Repository Architecture

```bash
OOPs/
│
├── 📁 College/
│   ├── UNIT-1
│   ├── UNIT-2
│   ├── UNIT-3
│   ├── UNIT-4
│   └── UNIT-5
│
├── 📁 OOPs-Pillars/
│   ├── Abstraction/
│   ├── Encapsulation/
│   ├── Inheritance/
│   ├── Modularity/
│   └── Polymorphism/
│
├── 📁 Personal-Implementations/
│   ├── Constructors
│   ├── Friend Functions
│   ├── Operator Overloading
│   ├── Virtual Functions
│   ├── Static Members
│   ├── Structures & Unions
│   ├── Inheritance Examples
│   └── Custom OOP Logic
│
└── 📁 Topic-Wise-Lessons/
    ├── 01_Introduction
    ├── 02_Classes_and_Objects
    ├── 03_Constructors
    ├── 04_Operator_Overloading
    ├── 05_Inheritance
    ├── 06_Polymorphism
    ├── 07_Friend_Functions_and_Classes
    ├── 08_Static_Members
    ├── 09_Inner_Class
    ├── 10_Exception_Handling
    ├── 11_Templates
    ├── 12_File_Handling
    ├── 13_Destructors
    ├── 14_Smart_Pointers
    ├── 15_Constants_and_Pointers
    ├── 16_Namespaces
    ├── 17_Preprocessor_Directives
    ├── 18_CPP11_Features
    ├── 19_Abstract_Classes
    ├── 20_Virtual_Inheritance
    ├── 21_Rule_of_Three
    ├── 22_Casting_Operators
    └── 23_Composition
```

---

## 🔥 Featured Topics

### 🏗️ Classes & Objects

```cpp
class Student {
private:
    string name;
    int rollNo;

public:
    Student(string n, int r) : name(n), rollNo(r) {}

    void display() const {
        cout << "Name: " << name << " | Roll: " << rollNo << endl;
    }
};
```

<div align="center">

| ✔️ Object Creation | ✔️ Access Specifiers | ✔️ Member Functions | ✔️ Object Lifecycle |
|---|---|---|---|

</div>

---

### ⚡ Constructors & Destructors

<div align="center">

```
  Object Created ──▶ Constructor()  ──▶ [Object Lives] ──▶ ~Destructor()
        │                  │                  │                   │
    Allocate           Initialize          In Use             Cleanup &
     Memory             Members          by program            Deallocate
```

</div>

| Type | Purpose |
|------|---------|
| **Default Constructor** | Zero-arg initialization |
| **Parameterized Constructor** | Custom initialization |
| **Copy Constructor** | Clone an existing object |
| **Constructor Overloading** | Multiple init strategies |
| **Destructor** | Resource cleanup |
| **Deep vs Shallow Copy** | Memory-safe duplication |

---

### 🎭 Polymorphism

```cpp
class Shape {
public:
    virtual double area() const = 0;   // Pure virtual
    virtual ~Shape() = default;
};

class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    double area() const override { return 3.14159 * r * r; }
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    double area() const override { return w * h; }
};
```

<div align="center">

```
          Polymorphism
         /            \
   Compile-time     Runtime
    (Static)        (Dynamic)
        |               |
   Overloading    Virtual Functions
   Op Overload    Pure Virtual / ABC
```

</div>

Includes: Function Overloading · Operator Overloading · Function Overriding · Virtual Functions · Pure Virtual Functions · Runtime Polymorphism

---

### 🧬 Inheritance

```
         ┌──────────┐
         │  Animal  │          ← Base Class
         └────┬─────┘
         ┌────┴─────┐
    ┌────┴──┐   ┌───┴────┐
    │  Dog  │   │  Cat   │    ← Single Inheritance
    └───────┘   └────────┘
         ↓
    ┌──────────────────┐
    │  GuideDog        │      ← Multilevel Inheritance
    └──────────────────┘
```

| Type | Description |
|------|-------------|
| **Single** | One base → One derived |
| **Multiple** | Multiple bases → One derived |
| **Multilevel** | Chain of inheritance |
| **Hierarchical** | One base → Multiple derived |
| **Hybrid** | Combination of the above |
| **Virtual Base Class** | Solves the Diamond Problem |

---

### 🧠 Smart Pointers & Memory Management

```cpp
// ✅ Modern C++ — No manual memory management
auto ptr  = std::make_unique<int>(42);           // Exclusive ownership
auto sptr = std::make_shared<MyClass>(args...);  // Shared ownership
std::weak_ptr<MyClass> wptr = sptr;              // Non-owning observer

// ❌ Old C++ — Prone to leaks
MyClass* raw = new MyClass();  // Who deletes this?
delete raw;                    // Easy to forget
```

| Concept | Description |
|---------|-------------|
| **RAII** | Resource Acquisition Is Initialization |
| **`unique_ptr`** | Single owner, auto-deleted |
| **`shared_ptr`** | Ref-counted shared ownership |
| **`weak_ptr`** | Break circular references |
| **Memory Leaks** | Detection and prevention |

---

## 📚 Detailed Learning Modules

<div align="center">

| # | Module | Topics Included |
|---|--------|----------------|
| 01 | 📘 Introduction | Basics of OOP, Procedural vs OOP paradigm |
| 02 | 🏗️ Classes & Objects | Blueprint creation, member functions, lifecycle |
| 03 | ⚙️ Constructors | All constructor types, deep/shallow copy |
| 04 | 🔄 Operator Overloading | Custom operators, stream operators |
| 05 | 🧬 Inheritance | All 5 types + virtual base class |
| 06 | 🎭 Polymorphism | Compile-time & runtime polymorphism |
| 07 | 🤝 Friend Functions | Accessing private members externally |
| 08 | 📦 Static Members | Shared class-level data and methods |
| 09 | 🔲 Inner Class | Nested class design patterns |
| 10 | ⚠️ Exception Handling | try, catch, throw, custom exceptions |
| 11 | 🧠 Templates | Generic programming, function & class templates |
| 12 | 💾 File Handling | Reading & writing files with streams |
| 13 | 💥 Destructors | Object cleanup and RAII |
| 14 | 🚀 Smart Pointers | unique_ptr, shared_ptr, weak_ptr |
| 15 | 📌 Constants & Pointers | const correctness, pointer semantics |
| 16 | 🏛️ Namespaces | Scope resolution and organization |
| 17 | ⚙️ Preprocessor | Macros, guards, conditional compilation |
| 18 | ✨ C++11 Features | auto, lambdas, range-for, nullptr, move semantics |
| 19 | 🧱 Abstract Classes | Pure virtual, interfaces, ABCs |
| 20 | 🔀 Virtual Inheritance | Diamond problem, virtual base class |
| 21 | 📐 Rule of Three | Copy constructor, copy assignment, destructor |
| 22 | 🎯 Casting Operators | static_cast, dynamic_cast, reinterpret_cast |
| 23 | 🧩 Composition | HAS-A relationships, object aggregation |

</div>

---

## 🛠️ Technical Stack

<div align="center">

| Technology | Usage |
|---|---|
| 💻 **C++11/14/17/20** | Core Programming Language |
| ⚙️ **GCC / G++** | Compilation |
| 🧠 **Visual Studio Code** | Development Environment |
| 🐙 **Git & GitHub** | Version Control |
| 📚 **STL** | Data Structures & Algorithms |

</div>

---

## 🚀 Learning Milestones

- [x] Mastered Classes & Objects
- [x] Implemented Constructor Overloading
- [x] Learned Memory Management
- [x] Understood Virtual Functions
- [x] Implemented Operator Overloading
- [x] Worked with Smart Pointers
- [x] Explored Rule of Three
- [x] Learned Templates & Generic Programming
- [x] Exception Handling
- [x] File Handling in C++

---

## 🎯 Why This Repository Stands Out

<div align="center">

✨ **Beginner Friendly** &nbsp;|&nbsp; ✨ **Clean Folder Structure** &nbsp;|&nbsp; ✨ **Topic-wise Organization**

✨ **Real Code Implementations** &nbsp;|&nbsp; ✨ **Modern C++ Concepts** &nbsp;|&nbsp; ✨ **Practical Learning Approach**

✨ **Interview Preparation Friendly** &nbsp;|&nbsp; ✨ **College + Industry Oriented**

</div>

---

## 🧪 Personal Implementations

This section contains experimental work and deeper exploration:

- 🔥 **Experimental implementations** — non-trivial edge cases
- 🧠 **Concept testing** — validating mental models with code
- ⚡ **Edge cases** — corner-case analysis
- 🚀 **Advanced logic** — complex OOP internals

Examples include:

> Copy Constructors · Friend Classes · Virtual Base Classes · Complex Operator Overloading · Typecasting · Union & Structures · Scope Resolution · Static Members

---

## 📸 Repository Preview

<div align="center">

**📂 Structured Learning Architecture**

<img src="https://user-images.githubusercontent.com/74038190/212897597-4f7b5d7f-6cf0-4bb4-a4f4-0e2f7bcb4c54.gif" width="700"/>

</div>

---

## 💡 Modern C++ Features Included

```cpp
// Type inference
auto value = 10;

// Range-based for loop
vector<int> nums = {1, 2, 3, 4};
for (auto x : nums) cout << x << " ";

// Lambda expressions
auto square = [](int x) { return x * x; };

// Smart pointers
auto ptr = make_unique<MyClass>();

// nullptr (not NULL)
int* p = nullptr;
```

| Feature | Description |
|---------|-------------|
| **`auto`** | Compiler-inferred types |
| **Range-based loops** | Clean iteration syntax |
| **Smart pointers** | Safe heap allocation |
| **`nullptr`** | Type-safe null pointer |
| **Lambda expressions** | Inline anonymous functions |
| **Move semantics** | Efficient resource transfer |
| **Type inference** | Less boilerplate, same safety |

---

## 📈 Future Enhancements

- [ ] GUI Projects using C++
- [ ] STL Mastery Section
- [ ] Design Patterns (GoF)
- [ ] Multithreading & Concurrency
- [ ] Competitive Programming Utilities
- [ ] Advanced Memory Optimization
- [ ] Game Development Basics

---

## 🤝 Contributions

Contributions are welcome! If you'd like to:

- Improve code quality
- Add more examples
- Optimize implementations
- Enhance documentation

Feel free to **fork** the repository and open a **pull request**.

---

## 🌟 Support

If you found this repository helpful:

- ⭐ **Star** the repository
- 🍴 **Fork** it and build on top
- 📢 **Share** with your peers

---
## 👨‍💻 Author

<div align="center">

### Sahastrajeet Hardaha

🚀 *Passionate Developer · DSA Enthusiast · OOP Explorer*

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=18&duration=3000&pause=1000&color=00C2FF&center=true&vCenter=true&width=500&lines=Building+one+class+at+a+time+🏗️;Writing+code+people+can+read+📖;OOP+is+not+just+syntax+—+it's+thinking+🧠" alt="author tagline"/>

[![GitHub](https://img.shields.io/badge/GitHub-Sahastrajeet--Hardaha-181717?style=for-the-badge&logo=github)](https://github.com/your-username)

</div>

---

## 📜 Philosophy

<div align="center">

> *"Programs must be written for people to read,*
> *and only incidentally for machines to execute."*
>
> — **Harold Abelson**

</div>

---

## 🏁 Final Note

This repository represents a continuous journey toward mastering:

| 🧠 Problem Solving | 🏗️ Software Design | ⚡ Modern C++ | 🚀 Scalable Practices |
|---|---|---|---|

Every file contributes toward building a stronger foundation in **software engineering** and **object-oriented thinking**.

<div align="center">

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=20&duration=2500&pause=800&color=2ECC71&center=true&vCenter=true&width=600&lines=%F0%9F%92%BB+Happy+Coding!;%E2%AD%90+Keep+Learning+%E2%80%A2+Keep+Building;%F0%9F%9A%80+Keep+Growing!" alt="footer"/>

</div>
