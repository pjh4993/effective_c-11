#include <string>
std::string
operator+(std::string&& x, const std::string& y){
    return x += y;
}


std::string
operator+(const std::string& x, std::string&& y){
    return y.insert(0,x);
}

std::string
operator+(std::string&& x, std::string&& y){
    return x+=y;
}

int main(void){
    std::string s1 = "test1", s2 = "test2";
    std::string s3 = s1 + "test1" + "test2";
    std::string s4 = std::string("test3") + std::string("test2");
}
