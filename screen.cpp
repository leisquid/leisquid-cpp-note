#include <iostream>
#include <string>
using namespace std;

const char RING = '\007';
const char BELL = '\007';

class Screen
{
    friend istream &operator>>(istream &, Screen &);
    friend ostream &operator<<(ostream &os, const Screen &s)
    {
        // ok: 指向 height, _width, 和 _screen
        os << "<" << s._height << "," << s._width << ">";
        os << s._screen;
        return os;
    }

public:
    Screen(int hi = 8, int wid = 40, char bkground = '#');

    inline int Screen::height() { return _height; }
    inline int Screen::width() { return _width; }

    inline void home()
    {
        this->_cursor = 0;
    }
    inline Screen &Screen::end()
    {
        _cursor = _width * _height - 1;
        return *this;
    }

    void move(int, int);
    inline char get() const
    {
        return this->_screen[_cursor];
    }

    inline char get(int, int);
    bool checkRange(int, int);

    int height()
    {
        return this->_height;
    }

    int width()
    {
        return this->_width;
    }

    void copy(const Screen &);
    void set(const string &s);
    void set(char ch);

    bool isEqual(char ch) const;

    // void forward();
    // void backward();
    // void up();
    // void down();

    inline Screen &forward();
    inline Screen &back();
    inline Screen &end();
    inline Screen &up();
    inline Screen &down();

    // clear() 的声明在类体内
    // 它指定了缺省实参 bkground = '#'
    Screen &clear(char bkground)
    {
        // 重置 cursor 以及清屏幕
        _cursor = 0;

        _screen.assign(     // 赋给字符串
            _screen.size(), // size() 个字符
            bkground        // 值都是 bkground
        );

        // 返回被调用的对象
        return *this;
    }

    Screen &display()
    {
        typedef string::size_type idx_type;

        for (idx_type ix = 0; ix < _height; ++ix)
        {
            // 针对每一行
            idx_type offset = _width * ix; // row position
            for (idx_type iy = 0; iy < _width; ++iy)
                // 针对每一列, 输出元素
                cout << _screen[offset + iy];
            cout << endl;
        }
        return *this;
    }

    // reSize() 的声明在类体内
    // 它指定了缺省实参 bkground = '#'
    Screen &Screen::reSize(int h, int w, char bkground)
    {
        // 把屏幕的大小设置到高度 h 和 宽度 w
        // 记住屏幕的内容
        string local(_screen);

        // 替换 _screen 所引用的字符串
        _screen.assign( // 赋给字符串
            h * w,      // h * w 个字符
            bkground    // 值都是 bkground
        );

        typedef string::size_type idx_type;
        idx_type local_pos = 0;

        // 把原来屏幕的内容拷贝到新的屏幕上
        for (idx_type ix = 0; ix < _height; ++ix)
        {
            // 每一行
            idx_type offset = w * ix; // 行位置

            for (idx_type iy = 0; iy < _width; ++iy)
                // 每一列, 赋以原来的值
                _screen[offset + iy] = local[local_pos++];
        }

        _height = h;
        _width = w;

        // _cursor 保持不变
        return *this;
    }

private:
    string _screen;
    mutable string::size_type _cursor;
    short _height, _width;

    inline int row();
    inline int remainingSpace();
};

Screen::Screen(int hi, int wid, char bk) : _height(hi),          // 用 hi 初始化 _height
                                           _width(wid),          // 用 wid 初始化 _width
                                           _cursor(0),           // 初始化 _cursor 为 0
                                           _screen(hi * wid, bk) // _Screen 的大小为 hi*wid
// 所有位置用 bk 的字符值初始化
{ // 所有的工作都由成员初始化列表完成
  // 14.5 节将讨论成员初始化列表
}

inline int Screen::row()
{ // 返回当前行
    return (_cursor + _width) / _width;
}

inline int Screen::remainingSpace()
{
    // 当前位置不再是剩余的
    int sz = _width * _height;
    return (sz - _cursor);
}

bool Screen::checkRange(int row, int col)
{
    if (row < 1 || row > _height || col < 1 || col > _width)
    {
        cerr << "Screen coordinates ( "
             << row << ", " << col
             << " ) out of bounds.\n";
        return false;
    }
    return true;
}

inline void Screen::move(int r, int c)
{
    // 将 _cursor 称到绝对位置
    if (checkRange(r, c))
    {                               // 位置合法吗?
        int row = (r - 1) * _width; // 行位置
        _cursor = row + c - 1;
    }
}

void Screen::copy(const Screen &sobj)
{
    // 如果这个 Screen 对象与 sobj 是同一个对象
    // 则无需拷贝
    // 我们将在 13.4 节介绍 this 指针
    if (this != &sobj)
    {
        _height = sobj._height;
        _width = sobj._width;
        _cursor = 0;

        // 创建一个新字符串
        // 它的内容与 sobj._screen 相同
        _screen = sobj._screen;
    }
}

char Screen::get(int r, int c)
{
    move(r, c);   // _cursor 位置
    return get(); // 另一个 get() 成员函数
}

void Screen::set(const string &s)
{
    // 在当前 _cursor 位置写字符串
    int space = remainingSpace();
    int len = s.size();
    if (space < len)
    {
        cerr << "Screen: warning: truncation: "
             << "space: " << space
             << "string length: " << len << endl;
        len = space;
    }

    _screen.replace(_cursor, len, s);
    _cursor += len - 1;
}
void Screen::set(char ch)
{
    if (ch == '\0')
        cerr << "Screen: warning: "
             << "null character (ignored).\n";
    else
        _screen[_cursor] = ch;
}

bool Screen::isEqual(char ch) const
{
    return ch == _screen[_cursor];
}

// void Screen::forward()
// {
//     if (_cursor > 0)
//     {
//         _cursor--;
//     }
//     else
//     {
//         end();
//     }
// }

// void Screen::backward()
// {
//     if (_cursor < _height * _width - 1)
//     {
//         _cursor++;
//     }
//     else
//     {
//         home();
//     }
// }

// void Screen::up()
// {
//     if (_cursor >= _width)
//     {
//         _cursor -= _width;
//     }
//     else
//     {
//         cout << RING;
//     }
// }

// void Screen::down()
// {
//     if (_cursor + _width < _width * _height)
//     {
//         _cursor += _width;
//     }
//     else
//     {
//         cout << RING;
//     }
// }

inline Screen &Screen::forward()
{ // 向前移动_cursor 一个屏幕元素
    ++_cursor;
    // 检查是否到达右下角, 若是则折回
    if (_cursor == _screen.size())
        home();
    return *this;
}
inline Screen &Screen::back()
{ // 向后移动 _cursor 一个屏幕元素
    // 检查是否到达左上角 若是则折回
    if (_cursor == 0)
        end();
    else
        --_cursor;
    return *this;
}

inline Screen &Screen::end()
{
    _cursor = _width * _height - 1;
    return *this;
}

inline Screen &Screen::up()
{ // 移动 _cursor 向上一行
    // 不折回, 而是发出铃声
    if (row() == 1) // 到顶了?
        cout << BELL << endl;
    else
        _cursor -= _width;
    return *this;
}
inline Screen &Screen::down()
{
    if (row() == _height) // 到底了?
        cout << BELL << endl;
    else
        _cursor += _width;
    return *this;
}

int main()
{
    Screen sobj(3, 3); // 13.3.4 节定义的构造函数
    string init("abcdefghi");
    cout << "Screen Object ( "
         << sobj.height() << ", "
         << sobj.width() << " )\n\n";

    // 设置屏幕的内容
    string::size_type initpos = 0;
    for (int ix = 1; ix <= sobj.width(); ++ix)
        for (int iy = 1; iy <= sobj.height(); ++iy)
        {
            sobj.move(ix, iy);
            sobj.set(init[initpos++]);
        }

    // 打印屏幕的内容
    for (int ix = 1; ix <= sobj.width(); ++ix)
    {
        for (int iy = 1; iy <= sobj.height(); ++iy)
            cout << sobj.get(ix, iy);
        cout << "\n";
    }

    return 0;
}
