#include <iostream>
#include "geometry_2d/shape/shape.h"
using namespace std;

int main()
{
	Circle circle(1, 1, 2);
	Triangle triangle(0, 0, 5, 4, 5, -3);
	Rectangle rectangle(2, 0, 6, -10);

	cout << boolalpha;
	cout << Intersect(&circle, &triangle) << endl
		<< Intersect(&circle, &rectangle) << endl
		<< Intersect(&rectangle, &triangle);
	return 0;
}