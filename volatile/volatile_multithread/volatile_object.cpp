#include <iostream>

using namespace std;

class test{
    public:
        test();
        test(string, int);
        void Foo() const volatile{
            cout << const_cast<std::string&>(name) << state_ << endl;
        };
        void Bar(){
            state_+=2;
            cout << state_ << endl;
        };
    private:
        string name;
        int state_;
};

test::test(){
    name = "";
    state_ = 0;
};

test::test(string m_name, int m_state){
    name = m_name;
    state_ = m_state;
}

int main(void){
    test regularTest("regular",1);
    const volatile test volatileTest("volatile",2);
    volatileTest.Foo();
    regularTest.Foo();
    const_cast<test&>(volatileTest).Bar();
}
