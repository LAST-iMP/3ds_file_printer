#include "Z_Buffer.h"

template<typename T>
static void swap(vector<T*>& edges, int a, int b) {
    auto temp = edges[a];
    edges[a] = edges[b];
    edges[b] = temp;
}

void Z_Buffer::doRasterize(RECT *rect, RENDER_DATA *data, BYTE *buffer, Vector3D * light) {
    this->rect = rect;
    this->light = light;

    distance = vector<vector<int>>(rect->right, vector<int>(rect->bottom, data->boundingBox->xMin - 10));
    for (Face* f : *data->faces) {
        r_Face(buffer, *f);
    }
}

void Z_Buffer::r_Face(BYTE *buffer, Face &f) {
    //获取三角面片的边
    auto edges = vector<HalfEdge*>(f.getEdges());
    //三角面片的点
    auto v1 = edges[0]->getOrigin();
    auto v2 = edges[1]->getOrigin();
    auto v3 = edges[2]->getOrigin();
    int zMin = f.boundingBox->zMin;
    int zMax = f.boundingBox->zMax;
    //将斜率为0的边或非最低点开始的边移动至3位
    if (!((int)v1->getZ() != zMin ^ (int)v2->getZ() != zMin)) swap(edges, 0, 2);
    else if (!((int)v2->getZ() != zMin ^ (int)v3->getZ() != zMin)) swap(edges, 1, 2);
    //按照边的左右顺序排序
    Edge_Node acLeft(edges[0]);
    Edge_Node acRight(edges[1]);
    if (acLeft.y + acLeft.dy > acRight.y + acRight.dy) {
        Edge_Node temp = acLeft;
        acLeft = acRight;
        acRight = temp;
    }

    for (int z = zMin; z <= zMax; z++) {
        //深度增量
        float tempX = acLeft.x;
        float dx = (acRight.x - acLeft.x) / (acRight.y - acLeft.y);
        //画布上的坐标
        auto location = Vertex::translate(acLeft.y, z, *rect);
        //数据数组坐标
        int index = (location[0] + location[1] * rect->right) * 3;
        //法向量及增量
        Vector3D n = Vector3D(acLeft.normal);
        Vector3D dn = Vector3D(acRight.normal);
        dn = (dn - n) / (acRight.y - acLeft.y);
        for (int i = acLeft.y; i <= acRight.y; ++i, location[0]++, index += 3) {
            //检查越界
            bool check = !(location[0] < 0 || location[1] < 0 || location[0] >= rect->right || location[1] >= rect->bottom);
            if (check && distance[location[0]][location[1]] < tempX) {
                distance[location[0]][location[1]] = tempX;
                auto localLight = colorFilter->localLight(n, *light);
                colorFilter->fillColor(buffer, index, localLight[0], localLight[1], localLight[2]);
            }
            tempX += dx;
            n += dn;
        }
        if (z == zMax || z == zMin);
        else if ((int)acLeft.zMax == z) acLeft = Edge_Node(edges[2]);
        else if ((int)acRight.zMax == z) acRight = Edge_Node(edges[2]);
        acLeft.next();
        acRight.next();
    }
}

