#pragma once
#include "sfml/graphics.hpp"

using namespace sf;
using namespace std;

namespace physics {
    // checks if a point intersects with a polygon
    bool intersects(Vector2f point, const VertexArray& polygon);
    // checks if two polygons intersect
    bool intersects(const VertexArray& poly1, const VertexArray& poly2);

    // gets the transformed shape of a polygon using a given transform
    VertexArray getTransformed(const VertexArray& polygon, const Transform& transform);
}