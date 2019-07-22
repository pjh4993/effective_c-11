#include <iostream>


using namespace std;

class Widget{
    public:
        int i;
        Widget(){
            cout << this << endl;
        };
        Widget(int m_i);
        static Widget makeWidget();
        void test();
};


Widget Widget::makeWidget(){
    return new Widget();
}

void Widget::test(){
    cout << this << endl;
}

Widget::Widget(int m_i){
    i = m_i;
}

int main(void){
    int i;
    //Widget&& var1 = Widget::makeWidget();
    Widget&& var1 = Widget::makeWidget();
    cin >> i; 
    var1.i = i;
    cout << var1.i << endl;
    var1.test();
    //Widget var2 = const_cast<Widget&&>(var1);
}
