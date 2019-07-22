#include <iostream>

using namespace std;

int main(void){
#ifndef VOL
    const int local = 10;
    int *ptr = (int*)&local;
    cout << "Initial value of local var : " << local << endl;
    *ptr = 100;
    cout << "Modified value of local var : " << local << endl;
#endif
#ifdef VOL
    const volatile int local = 10;
    int *ptr = (int*)&local;
    cout << "DVOLInitial value of local var : " << local << endl;
    *ptr = 100;
    cout << "Modified value of local var : " << local << endl;
#endif
}
