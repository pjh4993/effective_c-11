#include <memory>

class Point{
    public:
        constexpr Point(double xVal=0, double yVal=0) noexcept
            : x(xVal), y(yVal){}
        constexpr double xValue() const noexcept {return x;}
        constexpr double yValue() const noexcept {return y;}
        constexpr void setX(double newX) noexcept {x = newX;}
        constexpr void setY(double newY) noexcept {y = newY;}
    private:
        double x, y;
};

class ncPoint{
    public:
        ncPoint(){};
        ncPoint(double xVal){x = xVal;}
        double xValue() const noexcept {return x;}
        void setX(double newX) noexcept {x = newX;}
    private:
        double x;
};


constexpr
Point midpoint(const Point& p1, const Point& p2) noexcept{
    return { (p1.xValue() + p2.xValue())/2, 
        (p1.yValue() + p2.yValue())/2};
}


/*
template <class T> constexpr
std::shared_ptr<T> factory(){
    return std::shared_ptr<T>(new T);
}
*/

template <class T, class A1>
std::shared_ptr<T>
factory(A1&& a1){
    return std::shared_ptr<T>(new T(std::forward<A1>(a1)));
}

int main(void){
    Point pt {2,3};
    std::shared_ptr<Point> p1 = factory<Point>(10), p2 = factory<Point>(11);
    p1->setX(6.8);
    p1->setY(10.99);
    std::shared_ptr<Point> p3 = factory<Point>(midpoint(*p1, *p2));
    std::shared_ptr<ncPoint> ncptr1 = factory<ncPoint>(ncPoint(2.0));

}
