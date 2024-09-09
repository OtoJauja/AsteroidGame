#include "Physics.h"

// checks if a point intersects with a polygon
bool physics::intersects(Vector2f point, const VertexArray& polygon)
{
    size_t n = polygon.getVertexCount() - 1;
    size_t intersecCount = 0;
    Vector2f rayEnd = Vector2f(numeric_limits<float>::max(), point.y);

    for (size_t i = 0; i < n; i++) {
        Vector2f p1 = polygon[i].position;
        Vector2f p2 = polygon[(i + 1) % n].position;

        // checks if the ray from the point intersects with an edge of the polygon
        if ((p1.y < point.y && p2.y >= point.y) || (p2.y < point.y && p1.y >= point.y)) {
            float t = (point.y - p1.y) / (p2.y - p1.y);
            float intersecX = p1.x + t * (p2.x - p1.x);

            // if the intersection point is on the left of the point, count it
            if (intersecX <= point.x && intersecX <= rayEnd.x)
            {
                intersecCount++;
            }
        }
    }
    // if the number of intersections is odd, the point is inside the polygon
    return intersecCount % 2 == 1;
}

// checks if two polygons intersect
bool physics::intersects(const VertexArray& poly1, const VertexArray& poly2) {
    size_t n1 = poly1.getVertexCount() - 1;
    size_t n2 = poly2.getVertexCount() - 1;

    for (size_t i = 0; i < n1; i++) {
        // calculates the normal vector of an edge of poly1
        Vector2f edge = poly1[i].position - poly1[(i + 1) % n1].position;
        Vector2f normal(-edge.y, edge.x);

        // normalizes the normal vector
        float length = sqrt(normal.x * normal.x + normal.y * normal.y);
        normal /= length;

        float min1 = numeric_limits<float>::max();
        float min2 = numeric_limits<float>::max();
        float max1 = numeric_limits<float>::min();
        float max2 = numeric_limits<float>::min();

        // projects the vertices of poly1 onto the normal and finds the min and max
        for (size_t j = 0; j < n1; j++) {
            float projection = poly1[j].position.x * normal.x + poly1[j].position.y * normal.y;
            min1 = min(min1, projection);
            max1 = max(max1, projection);
        }

        // projects the vertices of poly2 onto the normal and finds the min and max
        for (size_t j = 0; j < n2; j++) {
            float projection = poly2[j].position.x * normal.x + poly2[j].position.y * normal.y;
            min2 = min(min2, projection);
            max2 = max(max2, projection);
        }

        // if there is no overlap on the projected axis, polygons do not intersect
        if (max1 < min2 || max2 < min1)
        {
            return false;
        }
    }
    // if an overlap occurs on all axes, polygons intersect
    return true;
}

// gets the transformed shape of a polygon using a given transform
VertexArray physics::getTransformed(const VertexArray& polygon, const Transform& transform)
{
    VertexArray transformed = polygon;

    // applies transform to each vertex in the polygon
    for (size_t i = 0; i < transformed.getVertexCount(); i++) {
        transformed[i].position = transform.transformPoint(transformed[i].position);
    }

    return transformed;
}