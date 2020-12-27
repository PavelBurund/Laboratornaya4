#include <iostream>
#include "ShapeAccumulator.h"
#include "Shapes.h"

int main()
{
	std::list<Shape*> shapes;
	shapes.push_back(new Circle(3));
	shapes.push_back(new Rectangle(4, 5));
	shapes.push_back(new Square(5));
	shapes.push_back(new Triangle(3, 4, 5));
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