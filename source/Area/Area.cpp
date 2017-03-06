#include <iostream>
#include <stdio.h>
using namespace std;

float max(float x, float y) {
  return x > y ? x : y;
}

float min(float x, float y) {
  return x > y ? y : x;
}

float abs(float x) {
  return x > 0 ? x : -x;
}

struct Point {
  float x;
  float y;
};

bool isStraddle(Point &a1, Point &a2, Point &b1, Point &b2) {
  float minAx = min(a1.x, a2.x);
  float maxAx = max(a1.x, a2.x);
  float minBx = min(b1.x, b2.x);
  float maxBx = max(b1.x, b2.x);

  float minAy = min(a1.y, a2.y);
  float maxAy = max(a1.y, a2.y);
  float minBy = min(b1.y, b2.y);
  float maxBy = max(b1.y, b2.y);

  return ((minBx >= minAx && minBx <= maxAx) || (maxBx >= minAx && maxBx <= maxAx)) &&
    ((minBy >= minAy && minBy <= maxAy) || (maxBy >= minAy && maxBy <= maxAy));
}

bool isIntersect(Point &a1, Point &a2, Point &b1, Point &b2) {
  float x1 = (b1.x - a1.x) * (a2.y - a1.y) - (b1.y - a1.y) * (a2.x - a1.x);
  if (x1 == 0) {
    return false;
  }

  float x2 = (b2.x - a1.x) * (a2.y - a1.y) - (b2.y - a1.y) * (a2.x - a1.x);
  if (x2 == 0 || x1 * x2 > 0) {
    return false;
  }

  float x3 = (a1.x - b1.x) * (b2.y - b1.y) - (a1.y - b1.y) * (b2.x - b1.x);
  if (x3 == 0) {
    return false;
  }

  float x4 = (a2.x - b1.x) * (b2.y - b1.y) - (a2.y - b1.y) * (b2.x - b1.x);
  if (x4 == 0 || x3 * x4 > 0) {
    return false;
  }
  
  return true;
}
  
int main() {
  int count;
  Point list[1000];
  int index;
  
  while(cin >> count && count) {
    // input
    for (int i = 0; i < count; i++) {
      cin >> list[i].x >> list[i].y;
    }

    bool isPolygon = count >= 3;
      for (int i = 0; i < count && isPolygon; i++) {
	Point a1 = list[(i + 1) % count];
	Point a2 = list[i];
	
	for (int j = 0; j < i && isPolygon; j ++) {
	  Point b1 = list[j + 1];
	  Point b2 = list[j];

	  if (i == (j + 1) || (i + 1 - j) == count) {
	    if ((a1.x - a2.x) * (b1.y - b2.y) - (a1.y - a2.y) * (b1.x - b2.x) == 0) {
	      isPolygon = false;
	      break;
	    }
	  }
	  else {
	    if (isStraddle(a1, a2, b1, b2) && isIntersect(a1, a2, b1, b2)) {
	      isPolygon = false;
	      break;
	    }
	  }
	}
      }

    // output
    if (++index > 1) {
      cout << endl;
    }

    cout << "Figure " << index << ": ";
    if (isPolygon) {
      float area = 0;
      int j = 0;
      
      for (int i = 0; i < count; i++) {
	j = (i + 1) % count;
	area += list[i].x * list[j].y - list[i].y * list[j].x;
      }

      printf("%.2lf\n", abs(area * 0.5));
    }
    else {
      cout << "Impossible" << endl;
    }
  }


  return 0;
}
