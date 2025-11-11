#include <stdio.h>

// Structure for a point
struct Point {
    int x, y;
};

// Function to find orientation
int orientation(struct Point p, struct Point q, struct Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;   // collinear
    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

// Function to print convex hull using Jarvis March
void convexHull(struct Point points[], int n) {
    if (n < 3) {
        printf("Convex hull not possible (less than 3 points)\n");
        return;
    }

    int l = 0; // Find leftmost point
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    int hull[n];
    int p = l, q;
    int count = 0;

    // Traverse the hull
    do {
        hull[count++] = p;
        q = (p + 1) % n;

        for (int i = 0; i < n; i++)
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;

        p = q;
    } while (p != l);

    printf("Points in Convex Hull (Jarvis March):\n");
    for (int i = 0; i < count; i++)
        printf("(%d, %d)\n", points[hull[i]].x, points[hull[i]].y);
}

int main() {
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);

    struct Point points[n];
    printf("Enter the coordinates (x y):\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    convexHull(points, n);
    return 0;
}
