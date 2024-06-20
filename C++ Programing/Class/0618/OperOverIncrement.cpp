#include <iostream>

using namespace std;

class Point {
private:
	double m_x, m_y;

public:
	Point(double x = 0.0, double y = 0.0) : m_x(x), m_y(y) { }

	Point& operator++() {
		m_x++;
		m_y++;
		return *this;
	}

	Point operator++(int) {
		return Point(m_x++, m_y++);
	}

	friend ostream& operator<<(ostream& o, const Point& p);
};

ostream& operator<<(ostream& o, const Point& p) {
	o << p.m_x << " " << p.m_y << " " << endl;
	return o;
}

int main() {
	Point p1(1.0, 2.0);


	return 0;
}

