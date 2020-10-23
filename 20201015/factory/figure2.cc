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

	//只要类中出现了虚函数时，一般情况下都要将析构函数设置为虚函数
	virtual ~Figure() {}
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

	~Rectangle() {	cout << "~Rectangle()" << endl;}

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

	~Circle() {	cout << "~Cirlce()" << endl;	}

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

	~Triangle() {	cout << "~Triangle()" << endl;	}
private:
	double _a;
	double _b;
	double _c;
};

//工厂模式
//适用条件：
//   1. 如果对象的创建是比较简单的，不需要使用工厂模式
//   2. 共产模式适用于批量创建对象,对象的创建比较复杂的情况
//		


class Factory
{
public:
	virtual Figure * create() = 0;
};

class CircleFactory : public Factory
{
public:
	Figure * create() override
	{
		//
		//xml
		//数据是存储在配置文件中的
		//
		return new Circle(20);
	}
};


class TriangleFactory : public Factory
{
public:
	Figure * create() override
	{
		//
		//xml
		//数据是存储在配置文件中的
		//
		return new Triangle (3, 4, 5);
	}
};

class RectangleFactory : public Factory
{
	Figure * create()
	{
		//
		//xml
		//数据是存储在配置文件中的
		//
		return new Rectangle (10, 11);
	}
};
 
int main(void)
{
	unique_ptr<Factory> circleFactory(new CircleFactory());
	unique_ptr<Figure> circle(circleFactory->create());
	
	unique_ptr<Factory> triangleFactory(new TriangleFactory());
	unique_ptr<Figure> triangle(triangleFactory->create());


	unique_ptr<Factory> rectangleFactory(new RectangleFactory());
	unique_ptr<Figure> rectangle(rectangleFactory->create());

	display(circle.get());
	display(rectangle.get());
	display(triangle.get());

	return 0;
}
