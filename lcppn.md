# leisquid-cpp-note

本文采用 **CC BY-NC-SA 4.0** 协议授权

## 日期：23.8.21

### 1. 关于变量名

**对象名一般用小写字母**。例如，我们往往写成 `index`，不写 `INDEX`（一般把 `index` 当作类型名，而 `INDEX` 则一般被看作常量值，通常用预处理器指示符 `#define` 定义）。

### 2. 类的初始化

C++ 支持两种形式的初始化。

第一种形式是使用赋值操作符的显式语法形式：

```c++
int ival = 1024;
string project = "Fantasia 2000";
```

第二种是隐式形式，但是不太常用。在隐式形式中，初始值被放在括号中：

```c++
int ival(1024);
string project("Fantasia 2001");
```

另外，每种内置数据类型都支持一种特殊的构造函数语法，可将对象初始化为 0。例如：

```c++
int ival = int();           // ival == 0
double dval = double();     // dval == 0.0
```

### 3. 指针的声明

通过在标识符前加一个解引用操作符 `*` 来定义指针。

在下面的例子中，`lp` 是一个指向 long 类型对象的指针，而 `lp2` 则是一个 long 型的数据对象，不是指针：

```c++
long *lp, lp2;
```

所以为了清楚起见，最好写成：`long *lp;` 而不是 `long* lp;`，不然可能会出现如下的误会：

```c++
// 呐：ps2 并不是一个字符串指针
string* ps, ps2;
```

### 4. 指针的地址值

指针的地址值为 0 时，它不指向任何对象，或持有一个同类型的数据对象的地址。例如：

```c++
int ival = 1024;

int *pi = 0;        // pi 不指向任何对象
int *pi2 = &ival;   // pi2 指向 ival 的地址

pi = pi2;           // pi 和 pi2 都指向了 ival
pi2 = 0;            // pi2 不指向任何对象了
```

**指针不能持有非地址值**，**也不能被初始化或赋值为其他类型对象的地址值**。

但是，如果我们要做的仅仅是持有地址值（可能是把一个地址同另一个地址作比较），那么指针的实际类型就不重要了。C++ 提供了一种特殊的指针类型来支持这种需求：空类型指针（`void *`），它可以被任何数据指针类型的地址值赋值（函数指针不能赋值给它）。

### 5. C++ 的字符串类

标准 C++ 提供了支持字符串操作的 string 类。要使用 string 类型，必须先包含相关的头文件：

```c++
#include <string>
```

怎样拷贝一个字符串呢？最简单的办法是使用赋值操作符。例如：

```c++
st2 = st3;  // 把 st3 拷贝到 st2 中
```

可以使用加操作符 `+` 或看起来有点怪异的复合赋值操作符 `+=` 将两个或多个字符串连接起来。例如，给出两个字符串：

```c++
string s1( "hello, " );
string s2( "world\n" );
```

可以按如下方式将两个字符串连接起来形成第三个字符串：

```c++
string s3 = s1 + s2;
```

如果希望直接将 s2 附加在 s1 后面，那么可使用 `+=` 操作符：

```c++
s1 += s2;   // s1 == "hello, world\n"
```

### 6. 从 C 风格的 `char *` 型到 C++ 风格的 `string` 型

string 类型能够自动将 C 风格的字符串转换成 string 对象。例如这可以将一个 C 风格的字符串赋给一个 string 对象：

```c++
string s1;
const char *pc = "a character array";
s1 = pc; // ok
```

但是反过来的话，要这么写：

```c++
const char *charArr = s1.c_str();
```

其中，为了防止字符数组被程序直接处理，`c_str()` 返回了一个指向常量数组的指针 `const char *`。

### 7. string 和 char

string 类型支持通过下标操作符访问单个字符。例如：

```c++
string str( "the.fake.leisquid" );
for ( int i = 0; i < size; ++ i ) {
    if ( str[ i ] == '.' ) {
        str[ i ] = '_';
    }
}
```

### 8. 常量

(1) 因为常量在定义后就不能被修改，所以它**必须被初始化**。

(2) 任何“试图将一个非 const 对象的指针指向一个常量对象”的动作都将引起编译错误。

(3) 对于一个指向 xxx 类型的 const 对象的指针（`const xxx *`），**能修改它的地址**，**不能修改它指向的对象**；但是指向 const 对象的指针可以被赋以一个非 const 对象的地址。

(4) 在实际的程序中，指向 const 的指针常被用作函数的形式参数。它作为一个约定来保证：被传递给函数的实际对象在函数中不会被修改。如：

```c++
// 在实际的程序中，指向常量的指针往往被用作函数参数
int strcmp( const char *str1, const char *str2 );
```

(5) 可以定义一个 const 指针（`xxx *const`）指向一个 const 或一个非 const 对象，其**地址值不能再修改**，但是**指向的对象可以修改**。

### 9. 引用类型

通过引用可以间接操作对象，使用方式类似于指针，但是不需要指针的语法。引用类型由类型标识符和一个取地址操作符来定义，而且引用必须被初始化。如：

```c++
int ival = 114514;

int &refVal = ival;     // 彳亍：refVal 是一个指向 ival 的引用
int &refVal2;           // 不彳亍：引用必须被初始化为指向一个对象
```

一旦引用已经定义，它就不能再指向其他的对象（这是它为什么必须要被初始化的原因）。

不能像对指针那样用一个对象的地址初始化引用，但是可以定义一个指针引用，如：

```c++
int ival = 114514;

int &refVal = &ival;    // 不彳亍：refVal 是 int 类型，不是 int*

int *pi = &ival;

int *&ptrVal2 = pi;     // 彳亍：refPtr 是一个指向指针的引用
```

const 引用可以用不同类型的对象初始化，也可以是不可寻址的值，如文字常量。

如果用一个 const 对象的地址来初始化一个引用，那么不能用非 const 引用定义。如：

```c++
const int ival = 114514;
int *&pi_ref = &ival;   // 不彳亍：要求一个 const 引用
```

实际的 C++ 程序很少使用指向独立对象的引用类型。引用类型主要被用作函数的形式参数，例如：

```c++
// 返回访问状态 将值放入参数
bool get_next_value( int &next_value );

// 重载加法操作符
Matrix operator+( const Matrix&, const Matrix& );
```

### 10. bool 型

虽然 bool 型的对象也被看作是一种整数类型的对象，但是它不能被声明为 signed、unsigned、short 或 long。

当表达式需要一个算术值时，bool 对象和 bool 文字都被隐式地提升成 int。如：

```c++
bool found = true;
int count = 0;

count += found;     // 此时 found 的值被提升为 0 或者 1
```

如果有必要，算术值和指针值也能隐式地被转换成 bool 型的值。0 或空指针被转换成 false，所有其他的值都被转换成 true。

### 11. 数组

(1) 数组定义由类型名、标识符和维数组成。**维数值必须是常量或常量表达式**，即必须能在编译时刻计算出它的值，这意味着非 const 的变量不能被用来指定数组的维数。如：

```c++
const int buf_size = 512;
int staff_size = 27;

char input_buffer[buf_size];    // 彳亍
double salaries[staff_size];    // 不彳亍：staff_size 不是常量
```

(2) 被显式初始化的数组可以不指定维数值，但是如果指定了维数，那么初始化列表提供的元素的个数不能超过这个值。

(3) 字符数组可以用一个由逗号分开的字符文字列表初始化，文字列表用花括号括起来，或者用一个字符串文字初始化。但是这两种形式不是等价的，字符串常量包含一个额外的终止空字符。如：

```c++
const char ca1[] = {'t', 'i', 'a', 'n', 'y', 'i'};
// 下面这个变成了：'t', 'i', 'a', 'n', 'y', 'i', '\0'
const char ca2[] = "tianyi";
// 下面这个戳啦！
const char ca3[6] = "tianyi";   // 编译会出错的，因为 "tianyi" 是 7 个元素。
```

(4) 一个数组**不能被另外一个数组初始化**，也**不能被赋值给另外一个数组**，而且**不允许声明一个引用数组**（即由引用组成的数组）。如：

```c++
const int array_size = 3;
int ix, jx, kx;
// 彳亍：类型为 int*的指针的数组
int *iap [] = { &ix, &jx, &kx };
// 不彳亍：不允许引用数组
int &iar[] = { ix, jx, kx };
// 不彳亍：不能用另一个数组来初始化一个数组
int ia2[] = ia; // 错误
int main()
{
    int ia3[ array_size ]; // 彳亍
    // 不彳亍：不能把一个数组赋给另一个数组
    ia3 = ia;
    return 0;
}
```

(5) 任意结果为整数值的表达式都可以作为索引值。

### 12. 运算符

(1) 可以把解引用操作符应用在地址值上，如：

```c++
*(pia + 2) = 1;
```

(2) C++ 语言运算符优先级表

| 优先级 | 分类 | 运算符 | 结合性 |
| ---- | ---- | ---- | ---- |
| 1 | 逗号运算符 | `,` | 从左到右 |
| 2 | 赋值运算符 | `=`、`+=`、`-=`、`*=`、`/=`、`%=`、`>=`、`<<=`、`&=`、`^=`、`\|=` | 从右到左 |
| 3 | 逻辑或 | `\|\|` | 从左到右 |
| 4 | 逻辑与 | `&&` | 从左到右 |
| 5 | 按位或 | `\|` | 从左到右 |
| 6 | 按位异或 | `^` | 从左到右 |
| 7 | 按位与 | `&` | 从左到右 |
| 8 | 相等/不等 | `==`、`!=` | 从左到右 |
| 9 | 关系运算符 | `<`、`<=`、`>`、`>=` | 从左到右 |
| 10 | 位移运算符 | `<<`、`>>` | 从左到右 |
| 11 | 加法/减法 | `+`、`-` | 从左到右 |
| 12 | 乘法/除法/取余 | `*`（乘号）、`/`、`%` | 从左到右 |
| 13 | 单目运算符 | `!`、`*`（指针）、`&` 、`++`、`–`、`+`（正号）、`-`（负号） | 从右到左 |
| 14 | 后缀运算符 | `( )`、`[ ]`、`->` | 从左到右 |

另外，赋值操作符的优先级低于不等于操作符。

### 13. 复数类型

(1) 使用前要导入头文件：

```c++
#include <complex>
```

(2) 复数的定义及使用：

```c++
// 纯虚数 0 + 7i
complex< double > purei( 0, 7 );
// 虚数部分默认为 0: 3 + 0i
complex< float > real_num( 3 );
// 实部和虚部均默认为 0: 0 + 0i
complex< long double > zero;
// 用另一个复数对象来初始化一个复数对象
complex< double > purei2( purei );
```

(3) 当然也可以声明复数对象的数组：

```c++
complex< double > conjugate[ 2 ] = {
    complex< double >( 2, 3 ),
    complex< double >( 2, -3 )
};
```

也可以声明指针或引用：

```c++
complex< double > *ptr = &conjugate[0];
complex< double > &ref = *ptr;
```
复数支持加、减、乘、除和相等比较，也支持对实部和虚部的访问。

(4) 可以从内置算术数据类型到复数类型转换，但是反过来不支持，只能单独提实部或虚部。

```c++
double re = complex_obj.real();
double im = complex_obj.imag();

// 等价于上面的成员语法
double re = real( complex_obj );
double im = imag( complex_obj );
```

(5) 复数类也支持四种复合赋值操作符：加赋值（`+=`）、减赋值（`-=`）、乘赋值（`*=`）以及除赋值（`/=`）。

(6) 使用 std::cout 打印复数值的结果通常如下：

```
( 3.14159, -2.171 )
// 表示 3.14159 - 2.171i
```

---

## 日期：23.8.22

### 14. `new` 和 `delete`

运行时刻的内存分配被称为**动态内存分配**。动态内存分配由 `new` 表达式应用在一个类型指示符上来完成。`new` 表达式返回**指向新分配的对象的指针**。如：

```c++
int *pi = new int;          // 无初始化
int *pi = new int( 1024 );  // 初始化为值 1024
int *pia = new int[ 10 ];   // 分配了一个动态数组
string *ps = new string;    // 分配了一个 string 类
```

用 `delete` 表达式来显式地把对象的内存返还给空闲存储区。如：

```c++
delete pi;      // 释放了 pi 指向的 int 对象，将其返还给空闲存储区
delete [] pia;  // 释放了 pia 指向的 10 个 int 对象的数组，并把相关的内存区返还给空闲存储区
```

### 15. 逗号操作符

逗号表达式是一系列由逗号分开的表达式。这些表达式从左向右计算。逗号表达式的结果是最右边表达式的值。

### 16. 位操作符

| 操作符 | 功能 | 用法 |
| ---- | ---- | ---- |
| `~` | 按位非 | `~expr` |
| `<<` | 左移 | `expr1 << expr2` |
| `>>` | 右移 | `expr1 >> expr2` |
| `&` | 按位与 | `expr1 & expr2` |
| `^` | 按位异或 | `expr1 ^ expr2` |
| `\|` | 按位或 | `expr1 \| expr2` |
| `&=` | 按位与赋值 | `expr1 &= expr2` |
| `^=` | 按位异或赋值 | `expr1 ^= expr2` |
|`\|=` | 按位或赋值 | `expr1 \|= expr2` |

**关于右移（`>>`）**：如果操作数是无符号数，则右移操作符（`>>`）从左边开始插入 0，否则要么插入符号位的拷贝，要么插入 0，这由具体实现定义。

### 17. `switch` 语句

(1) `case` 标签后面跟的是**一个整数类型的常量或者常量表达式**，而且**任意两个 `case` 标签不能有同样的值**。

(2) **必须显式地告诉编译器停止执行 `switch` 中的语句**。这可以通过在 `switch` 语句内的每个执行单元后指定一个 `break` 语句来完成。

(3) 声明语句也可以被放在 `switch` 语句的条件中，在整个 `switch` 语
句中是可见的，但在其外面并不可见。如：

```c++
switch( int ival = get_response() )
{ /* ...... */ }
```

(4) 如果一个定义没有被包围在一个语句块中，那么它在 `case` 标签之间是可见的，但是只有当定义它的 `case` 标签被执行时，它才能被初始化。因此需要一个语句块来保证名字是可见的，并且保证它只在这个语句块中才能被初始化，只有这个语句块才能够使用它。如：

```c++
case ok:
    {
        // ok: 声明语句被放在语句块中
        string file_name = get_file_name();
        // ...
        break;
    }
```

### 18. `do while` 语句

`do while` 循环的条件语句不支持对象定义，即不能写成：

```c++
do {
    // ...
} while ( int foo = get_foo() )     // 戳啦！！
```

### 19. 类

#### (1) 以下是一个定义了字符串的类的示例：

```c++
#include <iostream>
class String;

istream& operator>>( istream&, String& );
ostream& operator<<( ostream&, const String& );

class String {
public:
    // 一组重载的构造函数，提供自动初始化功能
    // String str1;                 // String()
    // String str2( "literal" );    // String( const char* );
    // String str3( str2 );         // String( const String& );
    String();                   // 默认构造函数，不需要显式的初始值
    // 下面这些叫做拷贝构造函数
    String( const char* );
    String( const String& );

    // 析构函数：删除对象时执行
    ~String();

    // 一组重载的赋值操作符
    // str1 = str2
    // str3 = "a string literal"
    String& operator=( const String& );
    String& operator=( const char* );

    // 一组重载的等于操作符
    // str1 == str2;
    // str3 == a string literal ;
    bool operator==( const String& );
    bool operator==( const char* );

    // 重载的下标操作符
    // str1[ 0 ] = str2[ 0 ];
    char& operator[]( int );

    // 成员访问函数
    int size() { return _size; }
    char* c_str() { return _string; }

private:
    int _size;
    char *_string;
};
```

#### (2) 成员函数的调用

如：

```c++
String object( "Danny" );
String *ptr = new String( "Anna" );
String array[2];

vector<int> sizes( 3 );
// 针对对象的点成员访问符号：`.`
// object 的长度为 5
sizes[ 0 ] = object.size();
// 针对指针的箭头成员访问符号：`->`
// ptr 的长度为 4
sizes[ 1 ] = ptr->size();
// 再次使用点成员访问符号
// array[0] 的长度为 0
sizes[ 2 ] = array[0].size();
```

#### (3) 在类的定义外定义类的函数

前面 `size()` 和 `c_str()` 函数都是在 String 类中定义的，不过也可以在类的定义外定义。如：

```c++
// bool：返回类型；
// String::：表示 String 类成员；
// operator==：函数的名字：（重载）等于操作符
bool String::operator==(const String &rhs) {
    if (_size != rhs._size) {
        return false;
    }
    return strcmp(_string, rhs._string)? false: true;
}
```

#### (4) 内联

可以将函数声明称内联（`inline`）函数，以减小调用，提高性能。在类定义内部定义的成员函数默认是设置为 `inline` 的，但是要把类外定义的成员函数声明为内联函数，必须显式声明。

在类体外定义的内联成员函数，应该被包含在含有该类定义的头文件中。

#### (5) 析构函数

当不需要对象时，要用 `delete` 表达式释放该内存区。可以通过定义类的析构函数自动实现，把 `delete` 表达式放在构析函数中。如果类的析构函数存在，那么在每个类的生命期结束时它会被自动调用。

析构函数由类名前面加一个波浪号（`~`）来标识。

如：

```c++
inline String::~String() { delete [] _string; }
```

### 20. 栈

#### (1) 栈的基本操作

向栈中 **压入（push）** 一个新值，以及 **弹出（pop）** 或获取最后压入的值。

#### (2) 一个简单的栈的声明示例

```c++
#include <vector>

class iStack {
public:
    // capacity 是定义的栈的容量
    iStack( int capacity ): _stack( capacity ), _top( 0 ) {}

    bool pop( int &value );
    bool push( int value );

    bool full();
    bool empty();
    void display();

    int size();

private:
    int _top;               // 栈中的元素计数
    vector< int > _stack;
};
```

```c++
bool iStack::pop( int &top_value )
{
    if ( empty() )
        return false;

    top_value = _stack[ --_top ];

    return true;
}

bool iStack::push( int value )
{
    if ( full() )
        return false;

    _stack[ _top++ ] = value;

    return true;
}

void iStack::display()
{
    if ( !size() )
    {
        cout << "( 0 )\n";
        return;
    }
    cout << "( " << size() << " )( bot: ";
    for ( int ix = 0; ix < _top; ++ix )
        cout << _stack[ ix ] << " ";
    cout << " :top )\n";
}
```

## 日期：23.8.23

### 21. 函数

#### (1) 函数返回类型

可以是预定义类型（如 int 或 double）、复合类型（如 int& 或 double*）或者用户定义类型（如枚举、类或 void）。

内置数组类型不能作为返回类型，但是可以返回指向数组元素的指针。如：

```c++
int *fun();
```

类和容器也可以作为返回类型，但是效率会有点低。

另外，在标准 C++ 中，返回类型不能省略。

#### (2) 传参

C++ 传递参数的默认方法是将实参的值复制到参数的存储区，即 **按值传递** （pass-by value）。

按值传递的问题是不会改变实参的值。比如下面的函数就没有对实参造成变化：

```c++
void swap(int v1, int v2) {
    int temp = v2;
    v2 = v1;
    v1 = temp;
}
```

为解决这一问题，可以将参数声明为指针：

```c++
void pswap(int *v1, int *v2) {
    int temp = *v2;
    *v2 = *v1;
    *v1 = temp;
}
```

但是传递的参数是两个对象的地址而不是对象本身了：

```c++
pswap(&i, &j);
```

另外一种方法是把参数声明为引用，如：

```c++
void rswap(int &v1, int &v2) {
    int temp = v2;
    v2 = v1;
    v1 = temp;
}
```

调用的时候这么写：

```c++
rswap(i, j);
```

就没这么麻烦了，而且如果传入的参数是类对象，也可以避免复制。

但是如果希望被引用的参数不被随意修改，可以把参数声明为 const 类型：

```c++
int fun(const xxx& xx) { /* ...... */ }
```

#### (3) 数组参数

C++ 中，数组不会按值传递，传递的是第 0 个元素的指针。

而且数组的长度与参数声明无关，所以以下函数的声明都是有效的：

```c++
void scan(int*);
void scan(int[]);
void scan(int[10]);
```

不过要注意以下几点：

① 由于传入的是指针，所以对参数的改变会直接应用到实参。如果不想改变数组中的元素，可以将参数声明为 const。

② 数组长度不是参数类型的一部分，也就是函数不知道传递过来的数组的实际长度。有一个办法就是传递参数时需要额外提供数组的长度；另一种办法是声明为数组的引用，这样数组的长度就会成为参数和实参类型的一部分了，如：

```c++
void putValues( int (&arr)[10] );

int main() {
    int i, j[ 2 ];
    putValues( i ); // 不彳亍：实参不是 10 个 int 的数组
    putValues( j ); // 不彳亍：实参不是 10 个 int 的数组
    return 0;
}
```

但是，这限制了可以作为实参被传递给 `putValues()` 的数组的种类。

#### (4) 默认实参

函数可以用参数表中的初始化语法为一个或多个参数指定默认实参。例如搞一个模拟终端显示器，可以指定一个默认的高度、宽度和背景字符：

```c++
char *screenInit(int width = 80, int height = 25, char background = ' ');
```

此时调用时可以不提供实参，也可以只提供部分实参，效果如下：

```c++
char *cursor;

cursor = screenInit();              // 等价于 screenInit(80, 25, ' ')
cursor = screenInit(125);           // 等价于 screenInit(125, 25, ' ')
cursor = screenInit(125, 40);       // 等价于 screenInit(125, 40, '#')
cursor = screenInit(125, 40, '#');
```

但是以下用法就错误了：

```c++
cursor = screenInit('@');           // 等价于 screenInit('@', 25, ' ')
cursor = screenInit( , , '@');      // 并不等价于 screenInit(80, 25, '@')
```

一个参数只能在一个文件中被指定一次默认实参。默认实参不一定必须是常量表达式，可以使用任意表达式。

#### (5) 省略号

有时候我们无法列出传递给函数的所有实参的类型和数目。在这种情况下可以用省略号（`...`）指定函数参数表。

省略号挂起类型检查机制。它们的出现告知编译器，当函数被调用时，可以有 0 个或多个实参，而实参的类型未知。

省略号有下列两种形式：

```c++
void foo( parm_list, ... );
void foo( ... );
```

第一种形式为特定数目的函数参数提供了声明。在这种情况下，当函数被调用时，对于与显式声明的参数相对应的实参进行类型检查，而对于与省略号对应的实参则挂起类型检查。在第一种形式中，参数声明后面的逗号是可选的。

标准 C 库输出函数 `printf()` 就是一个必须使用省略号的例子。`printf()` 的第一个参数总是 C 风格字符串:

```c++
int printf( const char* ... );
```
这要求 `printf()` 的每次调用都必须传递第一个 const char* 型的实参。在 `printf()` 的调用中，字符串后面是否有其他实参由第一个被称作格式字符串的实参所决定。在格式字符串中，由 `%` 开头的元字符表示其他实参的存在。如下调用：

```c++
printf( "hello, world\n" );
```

有一个字符串实参。但是如下调用：

```c++
printf( "hello, %s\n", userName );
```

有两个实参，`%` 表明需要第二个实参，`s` 表明该实参的类型是一个字符串。

大多数带有省略号的函数都利用显式声明的参数中的一些信息来获取函数调用中提供的其他可选实参的类型和数目。同此，带有省略号的第一种形式的函数声明最常使用。

对于如下两个不等价的函数声明：

```c++
void f();       // 不接受任何函数
void f( ... );  // 可以接受 0 到多个实参
```

调用 `f( 0x00, 0x80, 0xff )` 只对上面第二个声明有效；而调用 `f()` 对上面任意一个声明都有效。

### 22. 处理命令行选项

执行程序时可能会传递命令行选项。比如：

```sh
g++ -O2 ./source.cpp -o ./target
```

命令行选项就是 `main()` 的实参。为了实现选项的传递，可以通过 `main()` 函数的一种扩展原型特征来访问这些选项：

```c++
int main( int argc, char *argv[] ) { /* ...... */ }
```

其中 `argc` 包含命令行选项的个数，`argv` 包含 `argc` 个 C 风格字符串，代表了由空格分隔的命令
选项。

这里假设一个程序 `prog` 支持以下用法：

```
program_name [-d] [-h] [-v]
             [-o output_file] [-l limit_value]
             file_name
             [ file_name [file_name [ ... ]]]
```

其中，方括号中的内容是可选的，例如最小的命令行只给出要处理的文件：


```sh
prog chap1.doc
```

而其他可能的调用方式如下：

```sh
prog -l 1024 -o chap1-2.out chap1.doc chap2.doc
prog -d chap3.doc
prog -l 512 -d chap4.doc
```

那么可以按照以下步骤处理这些命令行选项：

1. 按顺序从 `argv` 中取出每个选项。可以用 for 循环来完成，并跳过程序名，从索引 1 开始迭代：

```c++
for ( int ix = 1; ix < argc; ++ix ) {
    char *pchar = argv[ ix ];
    // ...
}
```

2. 确定选项的类型。如果它以 `-` 开始，那么就能知道它是 `{h, d, v, l, o}` 之一，否则它或许是与 `-l` 相关的实际限制量，或者是与 `-o` 相关的输出文件名，或者是程序要处理的文件名。这里用 switch 语句确定是否存在一个 `-`：

```c++
switch ( pchar[ 0 ] ) {
    case '-': {
        // 识别 -h, -d, -v, -l, -o 的代码
    }
    default: {
        // 处理 -l 后的限制值
        // -o 后面的输出文件
        // 文件名 ...
    }
}
```

3. 填写代码，处理第 2 项中的两个 `case`。如果存在 `-`，那么简单地切换到下一个字符，确定用户指定的选项。

下面是实现代码的一般轮廓：

```c++
case '-': {
    switch( pchar[ 1 ] )
    {
    case 'd':
        // 处理调试
        break;
    case 'v':
        // 处理版本请求
        break;
    case 'h':
        // 处理帮助
        break;
    case 'o':
        // 准备处理输出文件
        break;
    case 'l':
        // 准备处理限制量
        break;
    default:
        // 可能是无法辨识的选项，报告并退出
    }
}
```

请看 CPPP 3rd 给出的完整的示例代码：

```c++
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>

const char *const program_name = "comline";
const char *const program_version = "version 0.01 (08/07/97)";

inline void usage( int exit_value = 0 )
{
    // 输出一个格式化的用法信息
    // 并用 exit_value 退出...
    cout << "usage:\n"
        << program_name << " "
        << "[-d] [-h] [-v] \n\t"
        << "[-o output_file] [-l limit] \n\t"
        << "file_name\n\t[file_name [file_name [ ... ]]]\n\n"
        << "where [] indicates optional option: \n\n\t"
        << "-h: help.\n\t\t"
        << "generates this message and exits\n\n\t"
        << "-v: version.\n\t\t"
        << "prints version information and exits\n\n\t"
        << "-d: debug.\n\t\tturns debugging on\n\n\t"
        << "-l limit\n\t\t"
        << "limit must be a non-negative integer\n\n\t"
        << "-o ofile\n\t\t"
        << "file within which to write out results\n\t\t"
        << "by default, results written to standard output \n\n"
        << "file_name\n\t\t"
        << "the name of the actual file to process\n\t\t"
        << "at least one file_name is required --\n\t\t"
        << "any number may be specified\n\n"
        << "examples:\n\t\t"
        << "$command chapter7.doc\n\t\t"
        << "$command -d -l 1024 -o test_7_8 "
        << "chapter7.doc chapter8.doc\n\n";
    exit( exit_value );
}
int main( int argc, char* argv[] )
{
    bool debug_on = false;
    bool ofile_on = false;
    bool limit_on = false;
    int limit = -1;
    string ofile;
    vector<string, allocator> file_names;
    cout << "illustration of handling command line arguments:\n"
        << "argc: " << argc << endl;
    for ( int ix = 1; ix < argc; ++ix )
    {
        cout << "argv[ " << ix << " ]: "
        << argv[ ix ] << endl;
        char *pchar = argv[ ix ];
        switch ( pchar[ 0 ] )
        {
        case '-':
            {
                cout << "case \'-\' found\n";
                switch( pchar[ 1 ] )
                {
                case 'd':
                    cout << "-d found: "
                        << "debugging turned on\n";
                    debug_on = true;
                    break;
                case 'v':
                    cout << "-v found: "
                        << "version info displayed\n";
                    cout << program_name
                        << " :: "
                        << program_version
                        << endl;
                    return 0;
                case 'h':
                    cout << "-h found: "
                        << "help information\n";

                    // 这里没必要用 break 了, usage() 可以退出
                    usage();
                case 'o':
                    cout << "-o found: output file\n";
                    ofile_on = true;
                    break;
                case 'l':
                    cout << "-l found: "
                        << "resource limit\n";
                    limit_on = true;
                    break;
                default:    // 或文件名
                    cout << program_name
                        << " : error : "
                        << "unrecognized option: - "
                        << pchar << "\n\n";
                    // 这里没必要用 break 了, usage() 可以退出
                    usage( -1 );
                }
                break;
            }
        default: // 或文件名
            cout << "default nonhyphen argument: "
                << pchar << endl;
            if ( ofile_on ) {
                ofile_on = false;
                ofile = pchar;
            }
            else if ( limit_on ) {
                limit_on = false;
                limit = atoi( pchar );
                if ( limit < 0 ) {
                    cout << program_name
                        << " : error : "
                        << "negative value for limit.\n\n";
                    usage( -2 );
                }
            }
            else
                file_names.push_back( string( pchar ));
            break;
        }
    }
    if ( file_names.empty() ) {
        cout << program_name
            << " : error : "
            << "no file specified for processing.\n\n";
        usage( -3 );
    }
    if ( limit != -1 )
        cout << "User-specifed limit: "
            << limit << endl;
    if ( ! ofile.empty() )
        cout << "User-specified output file: "
            << ofile << endl;
    cout << (file_names.size() == 1 ? "File " : "Files ")
        << "to be processed are the following:\n";
    for ( int inx = 0; inx < file_names.size(); ++inx )
        cout << "\t" << file_names[ inx ] << endl;
}
```

可以参照以下命令的形式自行测试程序：

```sh
./a.out -d -l 1024 -o test_7_8 chapter7.doc chapter8.doc
```

另外，最好可以把处理命令行选项的细节封装起来，使它不会扰乱 `main()`。可以定义全局对象，不需要在函数之间传来传去；也可以把处理过程封装到一个类中。如：

```c++
#include <vector>
#include <string>

class CommandOpt {
public:
    CommandOpt() : _limit( -1 ), _debug_on( false ) {}
    int parse_options( int argc, char *argv[] );
    string out_file() { return _out_file; }
    bool debug_on() { return _debug_on; }
    int files() { return _file_names.size(); }

    // 访问 _file_names
    string& operator[]( int ix );
private:
    inline int usage( int exit_value = 0 );

    bool _debug_on;
    int _limit;
    string _out_file;
    vector<string, allocator> _file_names;

    static const char *const program_name;
    static const char *const program_version;
};

int main( int argc, char *argv[] ) {
    // ...
    CommandOpt com_opt;
    int option_status;
    option_status = com_opt.parse_options(argc, argv);
    // ...
}
```

## 日期：23.8.24

### 23. 指向函数的指针

#### (1) 怎么声明

如对于以下函数：

```c++
#include <string>

int lexicoCompare( const string &s1, const string &s2 ) {
    return s1.compare(s2);
}
```

写成这样就成了函数指针。注意解引用操作符应与函数名关联，所以要用到括号：

```c++
int (*pf)( const string &, const string & );
```

用法可以是下面这样：

```c++
int printf( const char*, ... );
int strlen( const char* );
int (*pfce)( const char*, ... );    // 可以指向 printf()
int (*pfc)( const char* );          // 可以指向 strlen()
```

#### (2) 初始化和赋值

当一个函数名没有被调用操作符修饰时，它会被解释成指向该类型函数的指针。如：

```
lexicoCompare
```

被解释为这种指针：

```c++
int (*)( const string &, const string & );
```

指向函数的指针可以这样被初始化：

```c++
int (*pfi)( const string &, const string & ) = lexicoCompare;
int (*pfi2)( const string &, const string & ) = &lexicoCompare;
```

也可按照以下方式被赋值：

```c++
pfi = lexicoCompare;
pfi2 = pfi;
```

#### (3) 调用

调用函数时，不需要解引用操作符。无论是用函数名直接调用函数，还是用指针间接调用函数，两者的写法是一样的。

对于如下声明：

```c++
int min( int*, int );
int (*pf)( int*, int ) = min;
```

当调用 `pf()` 时，可以写成 `pf( ia, iaSize );` 或显式地写成：`(*pf)( ia, iaSize );`。两者的效果是一致的，但是后者可以清楚楚该调用是通过函数指针执行的。

只有已经被初始化或赋值的指针（引用到一个函数）才可以被安全地用来调用一个函数。

#### (4) 函数指针的数组

可以声明一个函数指针的数组，如：

```c++
int (*testCases[10])();
```

将 `testCases` 声明为一个拥有 10 个元素的数组，每个元素都是一个指向函数的函数指针。该函数没有参数，返回类型为 int。


像数组 `testCases` 这样的声明非常难读，因为很难分析出函数类型与声明的哪部分相关。在这种情况下，可以使用 `typedef` 名字可以使声明更为易读：


```c++
typedef int (*PFV)(); // 定义函数类型指针的 typedef
PFV testCases[10];
```

这种声明与前面的等价。

由 `testCases` 的一个元素引用的函数调用如下：

```c++
const int size = 10;
PFV testCases[size];
int testResults[size];

void runtests() {
    for ( int i = 0; i < size; ++i )
        // 调用一个数组元素
        testResults[ i ] = testCases[ i ]();
}
```

函数指针的数组可以用一个初始化列表来初始化，该表中每个初始值都代表了一个与数组元素类型相同的函数。如：

```c++
int lexicoCompare( const string &, const string & );
int sizeCompare( const string &, const string & );

typedef int ( *PFI2S )( const string &, const string & );
PFI2S compareFuncs[2] =
{
    lexicoCompare,
    sizeCompare
};
```

也可以声明指向 `compareFuncs` 的指针。这种指针的类型是：指向函数指针数组的指针。声明如下：

```c++
PFI2S (*pfCompare)[2] = &compareFuncs;
```

声明可以分解为：

```
(*p fCompare)
```

解引用操作符 `*` 把 `pfCompare` 声明为指针，后面的 `[2]` 表示 `pfCompare` 是指向两个元素数组的指针：

```
(*pfCompare)[2]
```

`typedef PFI2S` 表示数组元素的类型：它是指向函数的指针，返回 int，有两个 `const string&` 型的参数。数组元素的类型与表达式 `&lexicoCompare` 的类型相同，也与 `compareFuncs` 的第一个元素的类型相同。此外它还可以通过下列语句之一获得：

```c++
compareFuncs[ 0 ];
(*pfCompare)[ 0 ];

```

要通过 `pfCompare` 调用 `lexicoCompare` ，可以用下列语句之一：

```c++
// 两个等价的调用
pfCompare[ 0 ]( string1, string2 );         // 编写
((*pfCompare)[ 0 ])( string1, string2 );    // 显式
```

#### (5) 用法举例

```c++
#include <iostream>
#include <string>

// 这些通常应该在头文件中
int lexicoCompare( const string &, const string & );
int sizeCompare( const string &, const string & );
typedef int (*PFI)( const string &, const string & );
void sort( string *, string *, PFI=lexicoCompare );

string as[10] = { "a", "light", "drizzle", "was", "falling",
        "when", "they", "left", "the", "museum" };

int main() {
    // 调用 sort(), 使用缺省实参作比较操作
    sort( as, as + sizeof(as)/sizeof(as[0]) - 1 );

    // 显示排序之后的数组的结果
    for ( int i = 0; i < sizeof(as)/sizeof(as[0]); ++i )
        cout << as[ i ].c_str() << "\n\t";
}
```

### 24. 关于头文件的设计

(1) 头文件不能过大，否则编译时间会太长。所以有些 C++ 实现提供了预编译头文件支持。

(2) 头文件不应该含有“非内联函数或对象”的定义。例如，下面的代码表示的正是这样的定义，因此不应该出现在头文件中。这些定义如果被包含在同一程序的两个或多个文件中，就会产生重复定义的编译错误：

```c++
extern int ival = 10;   // 显式初始化使得它实际上是个定义
double fica_rate;       // 缺少 extern 而被视为 C++ 中实际的定义
extern void dummy() {}  // 花括号代表该函数的定义
```

但是，符号常量（const）定义以及内联函数可以被定义多次。

### 25. 寄存器自动对象

在函数中频繁被使用的自动变量可以用 `register` 声明。如果可以，编译器会把该对象装载到机器的寄存器中，否则对象仍位于内存中。

关键字 `register` 对编译器来说只是一个建议。有些编译器可能忽略该建议，而是使用寄存器分配算法找出最合适的候选放到机器可用的寄存器中。

### 26. 静态局部对象

是在整个程序运行期间一直存在的局部对象。一般把局部对象声明为 `static`。它的值在函数调用之间保持有效，但是其名字的可视性仍限制在其局部域内。

静态局部对象在程序执行到该对象的声明处时才会被首次初始化，但是只用初始化一次，在局部域内发生调用时这个值也始终有效。

未经初始化的静态局部对象会被程序自动初始化为 0。相反，自动对象的值会是任意的，除非它被显式初始化。

## 日期：23.8.25

### 今日问题

> 下面是 C++ 类 classType 的成员函数 assign()：
>
> ```c++
> classType& classType::assign( const classType &source )
> {
>     if ( this != &source )
>     {
>         this->~classType();
>         new (this) classType( source );
>     }
>     return *this;
> }
> ```
>
> 你对这种编码风格有什么看法？你认为这是一种安全的操作吗？为什么？
