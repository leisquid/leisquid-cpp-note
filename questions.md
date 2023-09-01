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
