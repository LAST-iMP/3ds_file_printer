#include "Rasterize.h"

template<typename T>
void swap(vector<T*>&, int, int);
void fillColor(BYTE* buffer, int index, int r, int g, int b);

Rasterize::Rasterize(RECT *rect, RENDER_DATA* data) {
    this->rect = rect;
    this->data = data;
}

Rasterize::~Rasterize() {

}

void Rasterize::rasterize(BYTE *buffer, vector<float>& light) {
    vector<vector<int>> distance = vector<vector<int>>(rect->right, vector<int>(rect->bottom, data->boundingBox->xMin - 10));

    for (Face* f : *data->faces) {
        r_Face(buffer, *f, distance, data->boundingBox->xMin, data->boundingBox->xMax, light);
    }
}

void Rasterize::r_Face(BYTE *buffer, Face &f, vector<vector<int>> &distance, float xMin, float xMax, vector<float>& light) {
    //获取三角面片的边
    auto edges = vector<HalfEdge*>(f.getEdges());
    //三角面片的点
    auto v1 = edges[0]->getOrigin();
    auto v2 = edges[1]->getOrigin();
    auto v3 = edges[2]->getOrigin();
    int zMin = f.boundingBox->zMin;
    int zMax = f.boundingBox->zMax;
    //将斜率为0的边或非最低点开始的边移动至3位
    if (!(v1->getIntZ() != zMin ^ v2->getIntZ() != zMin)) swap(edges, 0, 2);
    else if (!(v2->getIntZ() != zMin ^ v3->getIntZ() != zMin)) swap(edges, 1, 2);
    //按照边的左右顺序排序
    ActiveEdge acLeft(edges[0]);
    ActiveEdge acRight(edges[1]);
    if (acLeft.y + acLeft.dy > acRight.y + acRight.dy) {
        ActiveEdge temp = acLeft;
        acLeft = acRight;
        acRight = temp;
    }

    for (int z = zMin; z <= zMax; z++) {
        //深度增量
        float tempX = acLeft.x;
        float dx = (acRight.x - acLeft.x) / (acRight.y - acLeft.y);
        //颜色增量
//        float colorDepth = 255 * (acLeft.x - xMin) / (xMax - xMin);
//        float dColor = 255 * dx / (xMax - xMin);
        //画布上的坐标
        auto location = Vertex::translate(acLeft.y, z, *rect);
        //数据数组坐标
        int index = (location[0] + location[1] * rect->right) * 3;
        //法向量及增量
        vector<float> n = vector<float>(acLeft.normal);
        vector<float> dn = vector<float>(acRight.normal);
        dn[0] = (dn[0] - n[0]) / (acRight.y - acLeft.y);
        dn[1] = (dn[1] - n[1]) / (acRight.y - acLeft.y);
        dn[2] = (dn[2] - n[2]) / (acRight.y - acLeft.y);
        for (int i = acLeft.y; i <= acRight.y; ++i, location[0]++, index += 3) {
            //检查越界
            bool check = !(location[0] < 0 || location[1] < 0 || location[0] >= rect->right || location[1] >= rect->bottom);
            if (check && distance[location[0]][location[1]] < tempX) {
                distance[location[0]][location[1]] = tempX;
                float NL = getNL(tempX, i, z, n);
//                cout<<NL<<endl;
                auto Id = diffuse(NL);
                auto Is = mirror(NL, tempX, i, z, n);
//                fillColor(buffer, index, colorDepth, colorDepth, 0);
                fillColor(buffer, index, Id[0] + Is[0] + Iar, Id[1] + Is[1] + Iag, Id[2] + Is[2] + Iab);
            }
            tempX += dx;
//            colorDepth += dColor;
            n[0] += dn[0];
            n[1] += dn[1];
            n[2] += dn[2];
        }
        if (z == zMax || z == zMin) ;
        else if ((int)acLeft.z_max == z) acLeft = ActiveEdge(edges[2]);
        else if ((int)acRight.z_max == z) acRight = ActiveEdge(edges[2]);
        acLeft.next();
        acRight.next();
    }
}
vector<float> Rasterize::getLightColor(float dw, float x, float y, float z, vector<float> &normal) {
    float NL = getNL(x, y, z, normal);
    vector<float> result = vector<float>(3);
//    result[0] = Iar + Ipr * NL * dw *;
//    result[0] = Iag + Ipg * NL * dw *;
//    result[0] = Iab + Ipb * NL * dw *;
    return vector<float>();
}

float Rasterize::getNL(float x, float y, float z, vector<float> &normal) {
    float dx = data->boundingBox->xMax - x;
    float dy = data->boundingBox->yMax - y;
    float dz = data->boundingBox->zMax - z;
    float length = sqrt(dx*dx + dy*dy + dz*dz);
    return getMatrixMulti(dx/length, dy/length, dz/length, normal[0], normal[1], normal[2]);
}

float Rasterize::getMatrixMulti(float x1, float y1, float z1, float x2, float y2, float z2) {
    return x1*x2 + y1*y2 + z1*z2;
}


vector<float> Rasterize::diffuse(float LN) {
    vector<float> Id(3);
    Id[0] = LN * Kdr * Ipr;
    Id[1] = LN * Kdg * Ipg;
    Id[2] = LN * Kdb * Ipb;
    return Id;
}

vector<float> Rasterize::mirror(float NL, float x, float y, float z, vector<float> &normal) {
    float dx = data->boundingBox->xMax - x;
    float dy = data->boundingBox->yMax - y;
    float dz = data->boundingBox->zMax - z;
    float length = sqrt(dx*dx + dy*dy + dz*dz);
    float Rx = 2 * normal[0] * NL - dx / length;
//    float Ry = 2 * normal[1] * NL - dy / length;
//    float Rz = 2 * normal[2] * NL - dz / length;
    float RVN = pow(-Rx, N);
    vector<float> Is(3);
    Is[0] = Ipr * Ks * RVN;
    Is[1] = Ipg * Ks * RVN;
    Is[2] = Ipb * Ks * RVN;
    return Is;
}


template<typename T>
void swap(vector<T*>& edges, int a, int b) {
    auto temp = edges[a];
    edges[a] = edges[b];
    edges[b] = temp;
}

void fillColor(BYTE* buffer, int index, int r, int g, int b) {
//    cout<<(unsigned int)r<<" "<<(unsigned int)g<<" "<<(unsigned int)b<<endl;
    buffer[index + 2] = (r >= 0)? (unsigned char)r : 0;
    buffer[index + 1] = (g >= 0)? (unsigned char)g : 0;
    buffer[index] = (b >= 0)? (unsigned char)b : 0;
}

ACT_EDGE::ACT_EDGE(HalfEdge *e) {
    Vertex* vL = (e->getTarget()->z < e->getOrigin()->z)? e->getTarget() : e->getOrigin();
    Vertex* vH = (e->getTarget()->z < e->getOrigin()->z)? e->getOrigin() : e->getTarget();
    x = vL->x;
    y = vL->y;
    int dz = ((int)vH->z - (int)vL->z);
    dx = (vH->x - vL->x) / dz;
    dy = (vH->y - vL->y) / dz;
    z_max = vH->z;

    auto targetNormal = vH->getAveNormal();
    normal = vector<float>(*vL->getAveNormal());
    dN = vector<float>(3);
    dN[0] = ((*targetNormal)[0] - normal[0]) / dz;
    dN[1] = ((*targetNormal)[1] - normal[1]) / dz;
    dN[2] = ((*targetNormal)[2] - normal[2]) / dz;
}

void ACT_EDGE::next() {
    y += dy;
    x += dx;
    normal[0] += dN[0];
    normal[1] += dN[1];
    normal[2] += dN[2];
}
