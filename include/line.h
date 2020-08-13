#ifndef LINE_H
#define LINE_H

#include <math.h>

namespace geometry_2d {
    struct coordinate
    {
        float x;
        float y;
        bool valid() const
        {
            return !(isnan(x) || isnan(y));
        }
    };
    const coordinate NULL_POINT = { NAN, NAN };
    inline float max(float x, float y) { return x > y ? x : y; }
    inline float min(float x, float y) { return x > y ? y : x; }
    enum class distance_type
    {
        Euclidean,
        Manhattan,
    };
    inline float Distance(const coordinate& p1, const coordinate& p2, distance_type tp = distance_type::Euclidean)
    {
        float dist = 0;
        switch (tp)
        {
        case distance_type::Euclidean:
            dist = static_cast<float>(sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
            break;
        case distance_type::Manhattan:
            dist = static_cast<float>(abs(p1.x - p2.x) + abs(p1.y - p2.y));
            break;
        default:
            break;
        }
        return dist;
    }
    inline bool inRange(float x, float up, float down)
    {
        return x >= down && x <= up;
    }

    class line
    {
        // line in form: Ax + By + C = 0
        float _A;
        float _B;
        float _C;
    public:
        line() { }
        line(float a, float b, float c) :
            _A(a), _B(b), _C(c) {}
        line(const coordinate& p1, const coordinate& p2)
        {
            _A = p2.y - p1.y;
            _B = p1.x - p2.x;
            _C = p2.x * p1.y - p1.x * p2.y;
        }
        virtual ~line() {}
        float slope() const { return -_A / _B; }
        float b() const { return -_C / _B; }
        bool vertical() const { return _B == 0; }
        bool horizontal() const { return _A == 0; }
        float getY(float x) const noexcept
        {
            return -(_A * x + _C) / _B;
        }
        float getX(float y) const noexcept
        {
            return -(_B * y + _C) / _A;
        }
        // get distance between this line and a point
        float getDistanceWithPoint(const coordinate& p) const noexcept
        {
            return Distance(p, getFootPoint(p));
        }
        // get foot of a perpendicular
        coordinate getFootPoint(const coordinate& p) const noexcept
        {
            float x = (slope() * p.y + p.x - slope() * b()) / (slope() * slope() + 1);
            float y = getY(x);
            return { x, y };
        }
        coordinate getIntersection(const line& ln) const
        {
            // return NULL_POINT when two line are parallel
            if (_A == 0) {
                if (ln._A == 0) {
                    return NULL_POINT;
                }
                float y = b();
                return { ln.getX(y), y };
            }
            if (_B == 0) {
                if (ln._B == 0) {
                    return NULL_POINT;
                }
                float x = -_C / _A;
                return { x, ln.getY(x) };
            }
            if (abs(ln.slope() - slope()) < 1e-8) {
                return NULL_POINT;
            }
            float x = (ln.b() - b()) / (slope() - ln.slope());
            float y = getY(x);
            return { x, y };
        }
        bool getPointSign(const coordinate& p) const
        {
            return _A * p.x + _B * p.y + _C > 0;
        }
    };

    class LineSegment : public line
    {
        coordinate _endpoint1;
        coordinate _endpoint2;
    public:
        LineSegment() { }
        LineSegment(float x1, float y1, float x2, float y2) :
            _endpoint1({ x1, y1 }), _endpoint2({ x2, y2 }), line(_endpoint1, _endpoint2) {}
        LineSegment(const coordinate& p1, const coordinate& p2) :
            _endpoint1(p1), _endpoint2(p2), line(p1, p2) { }
        float length() const
        {
            return Distance(_endpoint1, _endpoint2);
        }
        bool hasPoint(const coordinate& p) const
        {
            if (abs(p.y - getY(p.x)) > 1e-7) {
                return false;
            }
            if (p.x > max(_endpoint1.x, _endpoint2.x) || p.x < min(_endpoint1.x, _endpoint2.x)
                || p.y < min(_endpoint1.y, _endpoint2.y) || p.y > max(_endpoint1.y, _endpoint2.y)) {
                return false;
            }
            return true;
        }
        coordinate leftEndPoint() const
        {
            return _endpoint1.x < _endpoint2.x ? _endpoint1 : _endpoint2;
        }
        coordinate rightEndPoint() const
        {
            return _endpoint1.x, _endpoint2.x ? _endpoint2 : _endpoint1;
        }
        bool intersect(const LineSegment& ln) const
        {
            auto p = getIntersection(ln);
            if (p.valid() && hasPoint(p)) {
                return true;
            }
            return false;
        }
    };
}
#endif
