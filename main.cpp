#include <iostream>
#include <math.h>
using namespace std;

class Vector3D
{
public:
    double X;
    double Y;
    double Z;
    Vector3D(const double &x = 0, const double &y = 0, const double &z = 0) : X(x), Y(y), Z(z) {};

    Vector3D operator+(const Vector3D &second) const
    {
        return {X + second.X, Y + second.Y, Z + second.Z};
    }

    Vector3D operator-(const Vector3D &second) const
    {
        return {X - second.X, Y - second.Y, Z - second.Z};
    }

    Vector3D operator*(const double &x) const
    {
        return {X * x, Y * x, Z * x};
    }

    bool operator!=(const Vector3D &second) const
    {
        if(X != second.X || Y != second.Y || Z != second.Z){
            return true;
        }
        return false;
    }

    double scalar_multiply(const Vector3D &second)
    {
        return X * second.X + Y * second.Y + Z * second.Z;
    }

    Vector3D perpendicular(const Vector3D &second)
    {
        return {
            Y * second.Z - Z * second.Y,
            Z * second.X - X * second.Z,
            X * second.Y - Y * second.X};
    }

    void print() const
    {
        cout << "(" << X << ", " << Y << ", " << Z << ")";
    }
};

class Segment3D
{
public:
    Vector3D start;
    Vector3D end;
    Segment3D(const Vector3D &one, const Vector3D &second) : start(one), end(second) {};
};

Vector3D *Intersect(const Segment3D &first, const Segment3D &second)
{
    Vector3D d1 = first.end - first.start;
    Vector3D d2 = second.end - second.start;
    Vector3D r = second.start - first.start;

    Vector3D perpd1d2 = d1.perpendicular(d2);
    double denumer = perpd1d2.scalar_multiply(perpd1d2);

    if (fabs(r.scalar_multiply(perpd1d2) > 1e-6))
    {
        return nullptr;
    }
    if (fabs(denumer) < 1e-6)
    {
        cout << "Отрезки коллинеарны или параллельны" << endl;
        return nullptr;
    }
    double t1 = (r.perpendicular(d2)).scalar_multiply(perpd1d2) / denumer;
    double t2 = (r.perpendicular(d1)).scalar_multiply(perpd1d2) / denumer;
    if (t1 < 0 || t1 > 1 || t2 < 0 || t2 > 1 || (first.start + d1 * t1) != (second.start + d2 * t2))
    {
        return nullptr;
    }
    return new Vector3D(first.start + d1 * t1);
}

int main()
{
    Vector3D s1, e1, s2, e2;
    cout << "Enter the beginning of the first segment (x y z): ";
    cin >> s1.X >> s1.Y >> s1.Z;
    cout << "Enter the ending of the first segment (x y z): ";
    cin >> e1.X >> e1.Y >> e1.Z;
    cout << "Enter the beginning of the second segment(x y z): ";
    cin >> s2.X >> s2.Y >> s2.Z;
    cout << "Enter the ending of the second segment (x y z): ";
    cin >> e2.X >> e2.Y >> e2.Z;

    Segment3D segment_one(s1, e1);
    Segment3D segment_two(s2, e2);
    Vector3D *intersection = Intersect(segment_one, segment_two);
    if (intersection)
    {
        cout << "Точка пересечения:";
        intersection->print();
        delete intersection;
    }
    else
    {
        cout << "У отрезков нет точки пересечения" << endl;
    }

    cout << endl;
}