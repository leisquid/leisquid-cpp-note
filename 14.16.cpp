#include <iostream>
using namespace std;

class Tianyi {
    public:
    Tianyi(): a(1), b(2) {
        cout << "调用了构造函数" << endl;
    }
    Tianyi(const Tianyi &tianyi) {
        this->a = tianyi.a;
        cout << "调用了拷贝构造函数" << endl;
    }
    ~Tianyi() {
        cout << "调用了析构函数" << endl;
    }
    private:
    int a;
    int b;
};

Tianyi global;

Tianyi foo_bar(Tianyi arg) {
    cout << "调用了 foo_bar()" << endl;
    cout << "Tianyi local = arg;" << endl;
    Tianyi local = arg;
    cout << "Tianyi *heap = new Tianyi(global);" << endl;
    Tianyi *heap = new Tianyi(global);
    cout << "*heap = local;" << endl;
    *heap = local;
    cout << "Tianyi pa[4] = {local, *heap};" << endl;
    Tianyi pa[4] = {local, *heap};
    cout << "return *heap;" << endl;
    return *heap;
}

int main() {
    foo_bar(global);

    return 0;
}
