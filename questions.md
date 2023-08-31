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

## 练习 18.9

已知下列类层次结构，以及数据成员集：

```c++
class Base1 {
public:
    // ...
protected:
    int ival;
    double dval;
    char cval;
    // ...
private:
    int *id;
    // ...
};
class Base2 {
public:
    // ...
protected:
    float fval;
    // ...
private:
    double dval;
    // ...
};
class Derived: public Base1 {
public:
    // ...
protected:
    string sval;
    double dval;
    // ...
};
class MI: public Derived, public Base2 {
    public:
    // ...
protected:
    int *ival;
    complex<double> cval;
    // ...
};
```

以及 `MI::foo()` 成员函数的骨架：

```c++
int ival;
double dval;
void MI::foo( double dval ) {
    int id;
    //...
}
```

(a) 请指出在 `MI` 中可见的成员有哪些，有来自多个基类中的可见成员吗？

(b) 请指出在 `MI::foo()` 中可见的成员有哪些？

---

## 练习 18.10

请用在练习 18.9 中定义的类层次结构，指出成员函数 `MI::bar()` 中的赋值哪些是错误的。

```c++
void MI::bar() {
    int sval;
    // 练习答案放在此处
}

```

(a): `dval = 3.14159;`

(b): `cval = 'a';`

(c): `id = 1;`

(d): `fval = 0;`

(e): `sval = *ival;`

---

## 练习 18.11

请用在练习 18.9 中定义的类层次结构，以及下面成员函数 `MI::foobar()` 的骨架：

```c++
int id;
void MI::foobar( float cval ) {
    int dval;
    // 练习答案放在此处
}

```

(a) 将 `Base1` 的 `dval` 成员加上 `Derived` 的 `dval` 成员，并将结果赋值给局部的 `dval` 实例。

(b) 将 `MI` 的 `cval` 的实数部分赋值给 `Base2` 的 `fval` 成员。

(c) 将 `Base1` 的 `cval` 成员赋值给 `Derived` 的 `sval` 成员的第一个字符。

---

## 练习 18.12

已知下列类层次结构，以及下列名为 `print()` 的成员函数：

```c++
class Base {
public:
    void print( string ) const;
    // ...
};
class Derived1: public Base {
public:
    void print( int ) const;
    // ...
};
class Derived2: public Base {
public:
    void print( double ) const;
    // ...
};
class MI: public Derived1, public Derived2 {
public:
    void print( complex<double> )const;
    // ...
};

```

1. 为什么下列语句会导致编译时刻错误？

```c++
MI mi;
string dancer( "Nijinsky" );
mi.print( dancer );
```

2. 怎样修改 `MI` 的定义以使它正确编译和执行？
