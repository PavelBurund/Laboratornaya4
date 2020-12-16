#include <list>
#include <iostream>
#include <cmath>
#include <vector>
#include <typeinfo>

class Shape {
public:
	double virtual calcArea() = 0;
	double virtual calcPerimeter() = 0;
	std::string virtual info() = 0;
};
class Triangle : public Shape {
private:
	double side1 = 0, side2 = 0, side3 = 0;
public:
	Triangle(double side1, double side2, double side3) : side1(side1), side2(side2), side3(side3)
	{
		if (!(side1 + side2 > side3 || side2 + side3 > side1 || side1 + side3 > side2)) throw("Вы ввели несуществущий треугольник");
		if (side1 <= 0 || side2 <= 0 || side3 <= 0) throw("Некорректное значение сторон");
	}
	double virtual calcArea() override
	{
		int Perimetr, HalfP;
		Perimetr = side1 + side2 + side3;
		HalfP = Perimetr / 2;
		return sqrt(HalfP * (HalfP - side1) * (HalfP - side2) * (HalfP - side3));
	}
	double virtual calcPerimeter() override
	{
		return side1 + side2 + side3;
	}
	double getSide1() {
		return side1;
	}
	double getSide2() {
		return side2;
	}
	double getSide3() {
		return side3;
	}
	std::string virtual info() override
	{
		return typeid(Triangle).name();
	}
};
class Square : public Shape {
private:
	double side = 0;
public:
	Square(double side) : side(side)
	{
		if (side <= 0) throw("Некорректное значение стороны");
	}
	double virtual calcArea() override
	{
		return pow(side, 2);
	}
	double virtual calcPerimeter() override
	{
		return side * 4;
	}
	double getSide() { return side; }
	std::string virtual info() override
	{
		return typeid(Square).name();
	}
};
class Rectangle : public Shape {
private:
	double width = 0, height = 0;
public:
	Rectangle(int width, int height) : width(width), height(height)
	{
		if (width <= 0 || height <= 0) throw("Некорректное значение сторон");
	}
	double virtual calcArea() override
	{
		return width * height;
	}
	double virtual calcPerimeter() override
	{
		return width * 2 + height * 2;
	}
	double getWidth() {
		return width;
	}
	double getHeight() {
		return height;
	}
	std::string virtual info() override
	{
		return typeid(Rectangle).name();
	}
};
class Circle : public Shape {
private:
	double radius = 0;
public:
	Circle(double radius) : radius(radius)
	{
		if (radius <= 0) throw("Некорректное значение радиуса");
	}
	double virtual calcArea() override
	{
		return  3.14 * radius * radius;
	}
	double virtual calcPerimeter()
	{
		return 3.14 * 2 * radius;
	}
	double getRadius() { return radius; }
	std::string virtual info() override
	{
		return typeid(Circle).name();
	}
};

#define MINDOUBLE std::numeric_limits<double>().min()
#define MAXDOUBLE std::numeric_limits<double>().max()

class ShapeAccumulator
{
private:
	std::list<Shape*> list;
	double sumOfPerimeters = 0;
	double sumOfAreas = 0;
	double maxArea = MINDOUBLE;
	double minArea = MAXDOUBLE;
	double maxPerimeter = MINDOUBLE;
	double minPerimeter = MAXDOUBLE;
public:
	void AddShape(Shape* shape)
	{
		list.push_back(shape);
		sumOfPerimeters += shape->calcPerimeter();
		sumOfAreas += shape->calcArea();
		if (maxArea < shape->calcArea()) maxArea = shape->calcArea();
		if (minArea > shape->calcArea()) minArea = shape->calcArea();
		if (maxPerimeter < shape->calcPerimeter()) maxPerimeter = shape->calcPerimeter();
		if (minPerimeter > shape->calcPerimeter()) minPerimeter = shape->calcPerimeter();
	}

	template<typename T>
	void AddShapes(T&& cont) {
		try
		{
			for (auto it = std::begin(cont); it != std::end(cont); it++)
			{
				AddShape(*it);
			}
		}
		catch (std::exception exception)
		{
			cout << "Ошибка во входящих данных";
		}
	}

	float getMaxAreaShape()
	{
		return maxArea;
	}

	float getMinAreaShape()
	{
		return minArea;
	}

	float getMaxPerimeterShape()
	{
		return maxPerimeter;
	}

	float getMinPerimeterShape()
	{
		return minPerimeter;
	}

	float getTotalArea()
	{
		return sumOfAreas;
	}

	float getTotalPerimeter()
	{
		return sumOfPerimeters;
	}
};

int main()
{
	std::list<Shape*> shapes;
	shapes.push_back(new Circle(0));
	shapes.push_back(new Rectangle(0, 0));
	shapes.push_back(new Square(0));
	shapes.push_back(new Triangle(1, 1, 45));
	int sumOfArea = 0;
	Shape* maxAreaOfFigures = nullptr;
	Shape* maxPerimeterOfFigures = nullptr;
	Shape* minAreaOfFigures = nullptr;
	Shape* minPerimeterOfFigures = nullptr;
	for (auto iter = shapes.begin(); iter != shapes.end(); ++iter)
	{
		sumOfArea += (*iter)->calcArea();
		if (maxAreaOfFigures == nullptr || maxAreaOfFigures->calcArea() < (*iter)->calcArea()) maxAreaOfFigures = *iter;
		if (minAreaOfFigures == nullptr || minAreaOfFigures->calcArea() > (*iter)->calcArea()) minAreaOfFigures = *iter;
		if (maxPerimeterOfFigures == nullptr || maxPerimeterOfFigures->calcPerimeter() < (*iter)->calcPerimeter()) maxPerimeterOfFigures = *iter;
		if (minPerimeterOfFigures == nullptr || minPerimeterOfFigures->calcPerimeter() > (*iter)->calcPerimeter()) minPerimeterOfFigures = *iter;
	}
	std::vector<Shape*> shapes2;
	shapes2.push_back(new Circle(3));
	shapes2.push_back(new Rectangle(5, 6));
	shapes2.push_back(new Square(50));
	shapes2.push_back(new Triangle(3, 4, 5));
	ShapeAccumulator shac;
	shac.AddShapes(shapes);
	shac.AddShapes(shapes2);
	shac.AddShape(new Circle(6));
	std::cout << shac.getMaxAreaShape() << std::endl;
	std::cout << shac.getMaxPerimeterShape() << std::endl;
	std::cout << shac.getTotalPerimeter() << std::endl;
	std::cout << shac.getTotalArea() << std::endl;
	std::cout << shac.getMinAreaShape() << std::endl;
	std::cout << shac.getMinPerimeterShape() << std::endl;
	return 0;
}