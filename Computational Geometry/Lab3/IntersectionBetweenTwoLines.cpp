#include <iostream>
#include <algorithm>

using namespace std;

struct Point
{
	float x;
	float y;
	Point() {}
	Point(float xx, float yy)
	{
		this->x = xx;
		this->y = yy;
	}
};

Point rightMostPoint(const Point p1, const Point p2)
{
	return (p1.x > p2.x) ? p1 : p2;
}

Point leftMostPoint(const Point p1, const Point p2)
{
	return (p1.x < p2.x) ? p1 : p2;
}

Point lineLineIntersection(Point A, Point B, Point C, Point D)
{
	//	Ecuatia dreptei AB reprezentata ca a1x + b1y = c1
	float a1 = B.y - A.y;
	float b1 = A.x - B.x;
	float c1 = a1*(A.x) + b1*(A.y);

	// Ecuatia dreptei CD reprezentata ca a2x + b2y = c2
	float a2 = D.y - C.y;
	float b2 = C.x - D.x;
	float c2 = a2*(C.x) + b2*(C.y);

	float determinant = a1*b2 - a2*b1;

	float x = (b2*c1 - b1*c2) / determinant;
	float y = (a1*c2 - a2*c1) / determinant;
	return Point(x, y);

}
bool onSegment(Point p, Point q, Point r)
{
	// Primeste 3 puncte coliniare si verifica daca punctul q se afla pe segmentul determinat de punctele p si r
	//	! - Punctele trebuie sa fie coliniare

	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

// Test de orientare
// 0 --> coliniare
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// Verificam daca punctele se intersecteaza
int doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Toate orientarile de care avem nevoie pt a verifica intersectia
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);


	if (o1 != o2 && o3 != o4)
		return 1;	// Se intersecteaza

	if (!orientation(p1, p2, q1) && !orientation(p1, q2, q1))
		return 0;   // Sunt coliniare

					// p1, q1 si p2 sunt coliniare si p2 se afla pe segmentul p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return 1;

	// p1, q1 si q2  sunt coliniare si q2 se afla pe segmentul p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return 1;

	// p2, q2 si p1 sunt coliniare si p1se afla pe segmentul p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return 1;

	// p2, q2 si q1 sunt coliniare si q1se afla pe segmentul p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return 1;

	return -1; // Nu se intersecteaza
}

int main()
{
	Point p1(0, 0);
	Point q1(2, 2);
	Point p2(1, 3);
	Point q2(1, -3);
	int result = doIntersect(p1, q1, p2, q2);
	if (result == 1)
	{
		// Determinam punctele de intersectie
		Point result = lineLineIntersection(p1, q1, p2, q2);
		cout << " Segmentele se intersecteaza in punctul : " << result.x << " " << result.y << endl;

	}
	else if (result == 0)
	{
		Point l1, l2, r1, r2;
		l1 = leftMostPoint(p1, q1);
		r1 = rightMostPoint(p1, q1);
		l2 = leftMostPoint(p2, q2);
		r2 = rightMostPoint(p2, q2);

		cout << "Segmentele sunt coliniare.\n";
		if (onSegment(l1, l2, r1) && onSegment(l1, r2, r1))
		{
			//cout << "Intersectia este segmentul [l2,r2]";
			cout << "Intersectia este segmentul [(" << l2.x << "," << l2.y << ")(" << r2.x << "," << r2.y << ")]" << endl;
		}
		else if (onSegment(l2, l1, r2) && onSegment(l2, r1, r2))
		{
			//cout << "Intersectia este segmentul [l1,r1]";
			cout << "Intersectia este segmentul [(" << l1.x << "," << l1.y << ")(" << r1.x << "," << r1.y << ")]" << endl;
		}
		else if (onSegment(l1, l2, r1) && !onSegment(l1, r2, r1))
		{
			//cout << "Intersectia este segmentul [l2,r1]";
			cout << "Intersectia este segmentul [(" << l2.x << "," << l2.y << ")(" << r1.x << "," << r1.y << ")]" << endl;
		}
		else if (onSegment(l2, l1, r2) && !onSegment(l2, r1, l2))
		{
			//cout << "Intersectia este segmentul [l1,r2]";
			cout << "Intersectia este segmentul [(" << l1.x << "," << l1.y << ")(" << r2.x << "," << r2.y << ")]" << endl;
		}
		elsey
			cout << "Punctele nu se intersecteaza.\n";
	}
	else
	{
		cout << "Segmentele nu se intersecteaza.\n";
	}

	return 0;
}
