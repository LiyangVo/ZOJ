#include <iostream>
#include <stdio.h>
using namespace std;

// DO NOT USE FLOAT !!!!

double max(double x, double y) {
  return x > y ? x : y;
}

double min(double x, double y) {
  return x > y ? y : x;
}

double abs(double x) {
  return x >= 0 ? x : -x;
}

struct Point {
  double x;
  double y;
};

double cross(Point &b, Point &a1, Point &a2) {
  return (b.x - a1.x) * (a2.y - a1.y) - (b.y - a1.y) * (a2.x - a1.x);
}

bool isIntersect(Point &a1, Point &a2, Point &b1, Point &b2) {
  // rect
  if (min(b1.x, b2.x) > max(a1.x, a2.x) || max(b1.x, b2.x) < min(a1.x, a2.x) ||
      min(b1.y, b2.y) > max(a1.y, a2.y) || max(b1.y, b2.y) < min(a1.y, a2.y)) {
    return false;
  }
  
  // kuali
  return cross(b1, a1, a2) * cross(b2, a1, a2) <= 0 && cross(a1, b1, b2) * cross(a2, b1, b2) <= 0;
}
  
int main() {
  int count = 0;
  int index = 0;
  Point list[1000];
  
  while(cin >> count && count) {
    // input
    for (int i = 0; i < count; i++) {
      cin >> list[i].x >> list[i].y;
    }

    bool isPolygon = count >= 3;
	for (int i = 0; i < count && isPolygon; i++) {
		for (int j = 0; j < i - 1 && isPolygon; j++) {
		  if ((i + 1 - j) != count && isIntersect(list[(i + 1) % count], list[i], list[j + 1], list[j])) {
		      isPolygon = false;
		  }
		}
    }

    // output
    if (++index > 1) {
      cout << endl;
    }

    cout << "Figure " << index << ": ";
    if (isPolygon) {
      double area = 0;
      for (int i = 0; i < count; i++) {
		int j = (i + 1) % count;
		area += list[i].x * list[j].y - list[i].y * list[j].x;
      }

      printf("%.2f\n", abs(area * 0.5));
    }
    else {
      cout << "Impossible" << endl;
    }
  }

  return 0;
}
