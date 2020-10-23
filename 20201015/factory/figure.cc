#include <math.h>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

// 
//继承 + 虚函数 --> 实现多态
//
//面向对象的
//
//对扩展开放，对修改关闭
class Figure
{
public:
	virtual void display() const =0;
	virtual double area() =0;
};

void display(Figure * fig) 
{
	fig->display();
	cout << "的面积是:";
	cout << fig->area() << endl;
}

class Rectangle
: public Figure
{
public:
	Rectangle(double length, double width)
	: _length(length)
	, _width(width)
	{}

	void display() const
	{	cout << "矩形";	}

	double area() 
	{	return _length * _width;	}

private:
	double _length;
	double _width;
};

class Circle
: public Figure
{
public:
	Circle(double radius)
	: _radius(radius)
	{}

	void display() const
	{	cout << "圆";	}

	double area() 
	{	return PI * _radius * _radius;	}

private:
	double _radius;
	static const double PI;
};
const double Circle::PI = 3.14159;

class Triangle
: public Figure
{
public:
	Triangle(double a, double b, double c)
	: _a(a), _b(b), _c(c)
	{}
	
	void display() const
	{	cout << "三角形";	}

	double area() 
	{
		double p = (_a + _b + _c) / 2;
		return sqrt(p * (p - _a) * (p - _b) * (p - _c));//海伦公式
	}
private:
	double _a;
	double _b;
	double _c;
};

//简单工厂模型(静态工厂方法)
//缺点: 1. 不符合单一职责原则
//      2. 不符合开闭原则

class Factory
{
public:
	static Figure * createCircle()
	{
		//
		//xml
		//数据是存储在配置文件中的
		//
		return new Circle(20);
	}

	static Figure * createTriangle()
	{
		//
		//xml
		//数据是存储在配置文件中的
		//
		return new Triangle (3, 4, 5);
	}

	static Figure * createRectangle()
	{
		//
		//xml
		//数据是存储在配置文件中的
		//
		return new Rectangle (10, 11);
	}

	static Figure * createDiamond();
};
 
int main(void)
{
	unique_ptr<Figure> circle(Factory::createCircle());
	unique_ptr<Figure> triangle(Factory::createTriangle());
	unique_ptr<Figure> rectangle(Factory::createRectangle());

	display(circle.get());
	display(rectangle.get());
	display(triangle.get());

	return 0;
}
