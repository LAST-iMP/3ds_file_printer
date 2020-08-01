//
// Created by lenovo on 2020/7/29.
//

#include "Rasterize.h"

void swap(vector<HalfEdge*>&, int, int);
void fillColor(BYTE* buffer, int index, BYTE r, BYTE g, BYTE b);

void Rasterize::rasterize(BYTE *buffer, RECT &rect, RENDER_DATA &data) {
    vector<vector<int>> distance = vector<vector<int>>(rect.right, vector<int>(rect.bottom, data.xMin - 50));

    for (Face* f : *data.faces) {
        r_Face(buffer, rect, *f, distance, data.xMin, data.xMax);
    }
}

void Rasterize::r_Face(BYTE *buffer, RECT rect, Face &f, vector<vector<int>> &distance, int xMin, int xMax) {
    auto edges = vector<HalfEdge*>(f.getEdges());
    auto v1 = edges[0]->getOrigin();
    auto v2 = edges[1]->getOrigin();
    auto v3 = edges[2]->getOrigin();
    int zMin = min(min(v1->getIntZ(), v2->getIntZ()), v3->getIntZ());
    int zMax = max(max(v1->getIntZ(), v2->getIntZ()), v3->getIntZ());
    //将斜率为0的边或非最低点开始的边移动至3位
    if (!(v1->getIntZ() != zMin ^ v2->getIntZ() != zMin)) swap(edges, 0, 2);
    else if (!(v2->getIntZ() != zMin ^ v3->getIntZ() != zMin)) swap(edges, 1, 2);
    //按照左右排序
    ActiveEdge acLeft(edges[0]);
    ActiveEdge acRight(edges[1]);
    if (acLeft.y + acLeft.dy > acRight.y + acRight.dy) {
        ActiveEdge temp = acLeft;
        acLeft = acRight;
        acRight = temp;
    }

    bool drawEdge = DRAW_EDGE;
    for (int z = zMin; z <= zMax; z++) {
        float tempX = acLeft.x;
        float dx = (acRight.x - acLeft.x) / (acRight.y - acLeft.y);
        for (int i = acLeft.y; i <= acRight.y; ++i) {
            auto location = Vertex::translate(i, z, rect);
            bool check = !(location[0] < 0 || location[1] < 0 || location[0] >= rect.right || location[1] >= rect.bottom);
            if (check && distance[location[0]][location[1]] < tempX) {
                distance[location[0]][location[1]] = tempX;
                int index = (location[0] + location[1] * rect.right) * 3;
                int colorDepth = (i != (int)acLeft.y && i != (int)acRight.y || !drawEdge)? (int)(255 * (tempX - xMin) / (xMax - xMin)) : 0;
                fillColor(buffer, index, colorDepth, colorDepth, 0);
            }
            tempX += dx;
        }
        if (z == zMax || z == zMin) ;
        else if ((int)acLeft.z_max == z) acLeft = ActiveEdge(edges[2]);
        else if ((int)acRight.z_max == z) acRight = ActiveEdge(edges[2]);
        acLeft.next();
        acRight.next();
    }
}

void swap(vector<HalfEdge*>& edges, int a, int b) {
    auto temp = edges[a];
    edges[a] = edges[b];
    edges[b] = temp;
}

void fillColor(BYTE* buffer, int index, BYTE r, BYTE g, BYTE b) {
    buffer[index + 2] = r;
    buffer[index + 1] = g;
    buffer[index] = b;
}

/*void Rasterize::r_Line(HDC &hdc, RECT rect, vector<int> &v1, vector<int> &v2, vector<vector<int>> &distance) {
    if (v1[1] > v2[1]) return r_Line(hdc, rect, v2, v1, distance);
    bool isYInc, isPositive;
    int x, y, z, dx, dy, dz, error, limit, delta1, delta2;
    dx = v2[0] - v1[0];
    dy = v2[1] - v1[1];
    dz = v2[2] - v1[2];
    x = v1[0];
    y = v1[1];
    z = v1[2];
    long color = RGB(0,0,0);
    isYInc = abs(dy) >= abs(dz);
    isPositive = (isYInc)? dz >= 0 : dy >= 0;
    error = (isYInc)? -dy : -dz;
    delta1 = (isYInc)? abs(2*dz) : abs(2*dy);
    delta2 = (isYInc)? abs(2*dy) : abs(2*dz);
    limit = (isYInc)? dy : dz;
    for (int j = 0; j < limit; ++j) {
        auto location = Vertex::translate(y, z, rect);
        int dis = distance[location[0]][location[1]];
        int tempX = interpolation(0, (limit-1), v1[0], v2[0], j);
//        cout<<tempX<<endl;
        if (dis <= tempX) {
            distance[location[0]][location[1]] = tempX;
            SetPixel(hdc, location[0], location[1], color);
        }
        if (isYInc) y++;
        else z++;
        error += delta1;
        if (error >= 0) {
            if (isYInc) z += (isPositive)? 1 : -1;
            else y += (isPositive)? 1 : -1;
            error -= delta2;
        }
    }
}*/