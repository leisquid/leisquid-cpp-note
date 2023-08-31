# Questions Remaining Unsolved

## 练习 17.3

考虑 17.1 节末尾的练习 17.1 的图书馆类层次结构：

>
> ### 练习 17.1
>
> 一个图书馆支持下列类别的借阅资料，每个类别都有自己的借阅、登记策略。请把它们组织到一个继承层次中：
>
> ```
> book            audio book
> record          children's puppet
> video           sega video game
> rental book     sony playstation video game
> cdrom book      nintendo video game
> ```
>

的下列成员，请指出哪些实例可能是虚拟函数的候选者，哪些可能会在所有库资料之间是公共的，因此可以出现在基类中。注意：`LibMember` 表示“能够借阅图书馆资料的图书馆成员”的抽象。`Date` 是一个类，用来表示特定年份的一个日期。

```c++
class Library {
public:
    bool check_out( LibMember* );
    bool check_in ( LibMember* );
    bool is_late( const Date& today );
    double apply_fine();
    ostream& print( ostream&=cout );

    Date* due_date() const;
    Date* date_borrowed() const;

    string title() const;
    const LibMember* member() const;
};
```

---

## 练习 17.4

请指出 17.1 节的练习 17.2 中：

> ### 练习 17.2
>
> 请从下面含有一组类型的一般抽象中选择一个（或选择你自己的一个抽象）。把这些类型组织到一个继承层次中：
>
> > (1) 图形文件格式（如 `gif`、`tiff`、`jpeg`、`bmp`）；
> >
> > (2) 几何图形（如方、圆、球 圆锥）；
> >
> > (3) C++ 语言类型（如类、函数、成员函数）。

选择的类层次结构的基类和派生类成员，指出虚拟函数以及公有和被保护的成员。

---

## 练习 17.15

下面派生类的虚拟函数的重新声明哪些是错误的？


(a)

```c++
Base* Base::copy( Base* );
Base* Derived::copy( Derived* );
```

(b)

```c++
Base* Base::copy( Base* );
Derived* Derived::copy( Base* );
```

(c)

```c++
ostream& Base::print( int, ostream&=cout );
ostream& Derived::print( int, ostream& );
```

(d)

```c++
void Base::eval() const;
void Derived::eval();
```

---

## 练习 18.1

下列声明哪些是错误的？请说明原因。

(a)
```c++
class CADVehicle: public CAD, Vehicle { /* ... */ };
```

(b)
```c++
class DoublyLinkedList: public List, public List { /* ... */ };
```

(c)
```c++
class iostream: private istream, private ostream { /* ... */ };
```

---

## 练习 18.2

已知下列类层次结构，它们都定义了默认的构造函数：

```c++
class A { ... };
class B: public A { ... };
class C: public B { ... };
class X { ... };
class Y { ... };
class Z: public X, public Y { ... };
class MI: public C, public Z { ... };
```

定义的构造函数：`MI mi;` 的执行顺序是什么？

---

## 练习 18.3

已知下列类层次结构，它们都定义了默认的构造函数：

```c++
class X { ... };
class A { ... };
class B : public A { ... };
class C : private B { ... };
class D : public X, public C { ... };
D *pd = new D;
```

下列哪些转换是不允许的？

(a): `X *px = pd;`

(b): `A *pa = pd;`

(c): `B *pb = pd;`

(d): `C *pc = pd;`

---

## 练习 18.4

已知下列类层次结构，以及虚拟函数集：

```c++
class Base {
public:
    virtual ~Base();
    virtual ostream&print();
    virtual void log();
    virtual void debug();
    virtual void readOn();
    virtual void writeOn();
    // ...
};
class Derived1 : virtual public Base {
public:
    virtual ~Derived1();
    virtual void writeOn();
    // ...
};
class Derived2 : virtual public Base {
public:
    virtual ~Derived2();
    virtual void readOn();
    // ...
};
class MI : public Derived1, public Derived2 {
public:
    virtual ~MI();
    virtual ostream&print();
    virtual void debug();
    // ...
};

Base *pb = new MI;
```

下列语句调用哪一个函数实例？

(a): `pb->print();`

(b): `pb->debug();`

(c): `pb->readOn();`

(d): `pb->writeOn();`

(e): `pb->log();`

(f): `delete pb;`

---

## 练习 18.5

使用练习 18.4 定义的类层次结构，请指出当通过 (a) pd1 和 (b) d2 调用时，哪些虚拟函数是活动的：

(a): `Derived1 *pd1 = new MI;`

(b): `MI obj; Derived2 d2 = obj;`
