#include "Shapes.h"

class ShapeAccumulator
{
private:
	std::list<Shape*> list;
public:
	void AddShape(Shape* shape)
	{
		list.push_back(shape);
	}

	template<typename T>
	void AddShapes(T&& cont) {
		for (auto it = std::begin(cont); it != std::end(cont); it++)
		{
			AddShape(*it);
		}
	}

	Shape* getMaxAreaShape()
	{
		auto maxPerimeterShape = list.begin();
		if (maxPerimeterShape == list.end()) return nullptr;

		for (auto it = list.begin(); it != list.end(); it++)
		{
			if ((*it)->calcArea() > (*maxPerimeterShape).calcArea())
				maxPerimeterShape = it;
		}
		return *maxPerimeterShape;
	}

	Shape* getMinAreaShape()
	{
		auto minAreaShape = list.begin();
		if (minAreaShape == list.end()) return nullptr;

		for (auto it = list.begin(); it != list.end(); it++)
		{
			if ((*it)->calcArea() < (*minAreaShape).calcArea())
				minAreaShape = it;
		}
		return *minAreaShape;
	}

	Shape* getMaxPerimeterShape()
	{
		auto maxPerimeterShape = list.begin();
		if (maxPerimeterShape == list.end()) return nullptr;

		for (auto it = list.begin(); it != list.end(); it++)
		{
			if ((*it)->calcPerimeter() > (*maxPerimeterShape).calcPerimeter())
				maxPerimeterShape = it;
		}
		return *maxPerimeterShape;
	}

	Shape* getMinPerimeterShape()
	{
		auto minPerimeterShape = list.begin();
		if (minPerimeterShape == list.end()) return nullptr;

		for (auto it = list.begin(); it != list.end(); it++)
		{
			if ((*it)->calcPerimeter() < (*minPerimeterShape).calcPerimeter()) 
				minPerimeterShape = it;
		}
		return *minPerimeterShape;
	}

	float getTotalArea()
	{
		double sumOfAreas = 0;
		for (auto it = list.begin(); it != list.end(); it++)
		{
			sumOfAreas += (*it)->calcPerimeter();
		}

		return sumOfAreas;
	}

	float getTotalPerimeter()
	{
		double sumOfPerimeters = 0;
		for (auto it = list.begin(); it != list.end(); it++)
		{
			sumOfPerimeters += (*it)->calcPerimeter();
		}

		return sumOfPerimeters;
	}
};