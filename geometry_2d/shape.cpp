#include "shape.h"
const float Circle::PI = 3.1415926;
bool Intersect(const Shape* s1, const Shape* s2)
{
	std::shared_ptr<intersector> sp(s2->getIntersector());
	s1->accept(*sp);
	return (*sp).result;
}

void CircleIntersector::visit(const Circle& c)
{
	result = (_circle.radius() + c.radius()) < Distance(_circle.center(), c.center());
}

void CircleIntersector::visit(const Rectangle& r)
{
	coordinate center = _circle.center();
	if (r.hasPoint(center)) {
		result = true;
	}
	else {
		bool isecUp = _circle.intersectWithLine(r.up);
		bool isecRight = _circle.intersectWithLine(r.right);
		bool isecDown = _circle.intersectWithLine(r.bottom);
		bool isecLeft = _circle.intersectWithLine(r.left);
		result = isecUp || isecRight || isecDown || isecLeft;
	}
}

void CircleIntersector::visit(const Triangle& t)
{
	coordinate center = _circle.center();
	if (t.hasPoint(center)) {
		result = true;
	}
	bool isec1 = _circle.intersectWithLine(t.edge1);
	bool isec2 = _circle.intersectWithLine(t.edge2);
	bool isec3 = _circle.intersectWithLine(t.edge3);
	result = isec1 || isec2 || isec3;
}

bool Circle::intersectWithLine(const LineSegment& ls) const
{
	if (ls.getDistanceWithPoint(_center) < _radius
		&& ls.hasPoint(ls.getFootPoint(_center)))
	{
		return true;
	}
	else if (Distance(ls.leftEndPoint(), _center) < _radius
		|| Distance(ls.rightEndPoint(), _center) < _radius)
	{
		return true;
	}
	return false;
}

void RectangleIntesector::visit(const Circle& c)
{
	auto isecor = c.getIntersector();
	isecor->visit(_rect);
}

void RectangleIntesector::visit(const Rectangle& r)
{
	bool sepVert = r.leftUp().y < _rect.rightDown().y
		|| r.rightDown().y > _rect.leftUp().y;
	bool sepHori = r.leftUp().x > _rect.rightDown().x
		|| r.rightDown().x < _rect.leftUp().x;
	result = !(sepVert || sepHori);
}

void RectangleIntesector::visit(const Triangle& t)
{
	std::shared_ptr<Rectangle> bound(t.getBoundRectangle());

	intersector* isecor = bound.get()->getIntersector();
	isecor->visit(_rect);
	if (isecor->result) {
		result = true;
	}
	else {
		if (_rect.intersectWithLine(t.edge1) || _rect.intersectWithLine(t.edge2)
			|| _rect.intersectWithLine(t.edge3)) {
			result = true;
		}
		result = false;
	}
}

bool Rectangle::intersectWithLine(const LineSegment& ln) const
{
	if (ln.horizontal()) {
		return inRange(ln.b(), _leftUp.y, _rightDown.y);
	}
	if (ln.vertical()) {
		return inRange(ln.getX(0), _rightDown.x, _leftUp.x);
	}
	float leftY = ln.getY(_leftUp.x);
	float rightY = ln.getY(_rightDown.x);
	float maxY = max(leftY, rightY), minY = min(leftY, rightY);
	if (inRange(_leftUp.y, maxY, minY) || inRange(_rightDown.y, maxY, minY)) {
		return true;
	}
	return false;
}

void TriangleIntesector::visit(const Circle& c)
{
	intersector* ins = c.getIntersector();
	ins->visit(_triangle);
	result = ins->result;
}

void TriangleIntesector::visit(const Rectangle& r)
{
	intersector* ins = r.getIntersector();
	ins->visit(_triangle);
	result = ins->result;
}

void TriangleIntesector::visit(const Triangle& t)
{
	if (t.hasPoint(_triangle.point1()) || t.hasPoint(_triangle.point2())
		|| t.hasPoint(_triangle.point3()))
	{
		result = true;
	}
	else if (t.intersectWithLine(_triangle.edge1) || t.intersectWithLine(_triangle.edge2)
		|| t.intersectWithLine(_triangle.edge3))
	{
		result = true;
	}
	else {
		result = false;
	}
}

Rectangle* Triangle::getBoundRectangle() const
{
	float left = min(min(_point1.x, _point2.x), _point3.x),
		right = max(max(_point1.x, _point2.x), _point3.x),
		up = max(max(_point1.y, _point2.y), _point3.y),
		down = min(min(_point1.y, _point2.y), _point3.y);
	return new Rectangle(left, up, right, down);
}

bool Triangle::hasPoint(const coordinate& p) const
{
	float total = getArea();
	float area1 = Triangle(_point1, _point2, p).getArea();
	float area2 = Triangle(_point1, _point3, p).getArea();
	float area3 = Triangle(_point2, _point3, p).getArea();

	return (area1 + area2 + area3) <= total;
}

bool Triangle::intersectWithLine(const LineSegment& ln) const
{
	if (ln.intersect(edge1) || ln.intersect(edge2) || ln.intersect(edge3)) {
		return true;
	}
	return false;
}
