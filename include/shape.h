#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <vector>
#include <math.h>
#include <limits.h>
#include "line.h"

namespace geometry_2d {
    // forward declaration
    class visitor;
    class intersector;
    class Shape;
    class Triangle;
    class Circle;
    class Rectangle;

    bool Intersect(const Shape* s1, const Shape* s2);
    class Shape
    {
    public:
        virtual float getArea() const = 0;
        virtual void accept(visitor& v) const = 0;
        virtual intersector* getIntersector() const = 0;
        virtual void draw() const = 0;
        virtual  unsigned int getEdges() const = 0;
        virtual ~Shape() {}

    protected:
        virtual void _updateVertices() = 0;
        virtual void onDraw() const;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        std::vector<float> _vertices;
        std::vector<unsigned int> _indices;
        static const float SCALE_FACTOR;
    };
    class visitor
    {
    public:
        virtual void visit(const Circle&) = 0;
        virtual void visit(const Rectangle&) = 0;
        virtual void visit(const Triangle&) = 0;
    };
    class intersector : public visitor
    {
    public:
        intersector() : result(false) {}
        bool result;
    };


    // Circle
    class CircleIntersector : public intersector
    {
        const Circle& _circle;
    public:
        explicit CircleIntersector(const Circle& c) : _circle(c) {}
        void visit(const Circle& c) override;
        void visit(const Rectangle& r) override;
        void visit(const Triangle& t) override;
    };

    class Circle : public Shape
    {
        coordinate _center;
        float _radius;
        const static float PI;

    public:
        Circle(float x, float y, float r);
        float getArea() const override
        {
            return PI * _radius * _radius;
        }
        unsigned int getEdges() const override
        {
            return INT_MAX;
        }
        void draw() const override;
        intersector* getIntersector() const override
        {
            return new CircleIntersector(*this);
        }
        void accept(visitor& v) const override
        {
            v.visit(*this);
        }
        float radius() const { return _radius; }
        coordinate center() const { return _center; }

        bool intersectWithLine(const LineSegment& ls) const;
    protected:
        void _updateVertices() override;
    };


    // Rectangle
    class RectangleIntesector : public intersector
    {
        const Rectangle& _rect;
    public:
        explicit RectangleIntesector(const Rectangle& r) :
            _rect(r) {}
        void visit(const Circle& c) override;
        void visit(const Rectangle& r) override;
        void visit(const Triangle& t) override;
    };

    class Rectangle : public Shape
    {
        coordinate _leftUp;
        coordinate _rightDown;
    public:
        LineSegment up;
        LineSegment right;
        LineSegment bottom;
        LineSegment left;
        Rectangle(float x1, float y1, float x2, float y2) :
            _leftUp({ x1, y1 }), _rightDown({ x2, y2 }), up(x1, y1, x2, y1),
            right(x2, y1, x2, y2), bottom(x1, y2, x2, y2), left(x1, y1, x1, y2)
        {}
        float getArea() const override
        {
            return (_leftUp.x - _rightDown.x) * (_leftUp.y - _rightDown.y);
        }
        unsigned int getEdges() const override
        {
            return 4;
        }
        void draw() const override;
        intersector* getIntersector() const override
        {
            return new RectangleIntesector(*this);
        }
        void accept(visitor& v) const override
        {
            v.visit(*this);
        }
        coordinate leftUp() const { return _leftUp; }
        coordinate rightDown() const { return _rightDown; }
        float height() const { return _leftUp.y - _rightDown.y; }
        float width() const { return _rightDown.x - _leftUp.x; }
        // Determine if the point is inside the rectangle
        bool hasPoint(const coordinate& p) const
        {
            return (p.x <= _rightDown.x && p.x >= _leftUp.x)
                && (p.y >= _rightDown.y && p.y <= _leftUp.y);
        }
        bool intersectWithLine(const LineSegment& ln) const;
    protected:
        void _updateVertices() override;
    };


    // Triangle
    class TriangleIntesector : public intersector
    {
        const Triangle& _triangle;
    public:
        explicit TriangleIntesector(const Triangle& t) :
            _triangle(t) {}
        void visit(const Circle& c) override;
        void visit(const Rectangle& r) override;
        void visit(const Triangle& t) override;
    };

    class Triangle : public Shape
    {
        coordinate _point1;
        coordinate _point2;
        coordinate _point3;

    public:
        LineSegment edge1;
        LineSegment edge2;
        LineSegment edge3;
        Triangle(float x1, float y1, float x2, float y2, float x3, float y3);
        Triangle(const coordinate& p1, const coordinate& p2, const coordinate& p3);
        // using 0.5 * det(Mat(triangle)) to calculate area
        float getArea() const override
        {
            return 0.5f * (_point1.x * _point2.y + _point3.x * _point1.y + _point2.x * _point3.y
                - _point3.x * _point2.y - _point2.x * _point1.y - _point1.x * _point3.x);
        }
        unsigned int getEdges() const override
        {
            return 3;
        }
        void draw() const override;
        std::unique_ptr<Rectangle> getBoundRectangle() const;
        bool hasPoint(const coordinate& p) const;
        intersector* getIntersector() const override
        {
            return new TriangleIntesector(*this);
        }
        void accept(visitor& v) const override
        {
            v.visit(*this);
        }
        unsigned int getVAO() const { return VAO; }
        bool intersectWithLine(const LineSegment& ln) const;
        coordinate point1() const { return _point1; }
        coordinate point2() const { return _point2; }
        coordinate point3() const { return _point3; }
    protected:
        void _updateVertices() override;
    };
}

#endif
