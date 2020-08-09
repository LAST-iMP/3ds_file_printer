#include "LT_Data.h"

pair<float, pair<vector<float>, Face *>> LT_Data::empty = make_pair(0, make_pair(vector<float>(), nullptr));

float getMatrixMulti(vector<float>& a, vector<float>& b) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

vector<float> getMatrixCross(vector<float>& a, vector<float>& b) {
    return {a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]};
}

LT_Data::LT_Data(Mesh *mesh, RECT& rect) {
    xLimit = mesh->boundingBox->xMax - mesh->boundingBox->xMin;
    yLimit = mesh->boundingBox->yMax - mesh->boundingBox->yMin;
    zLimit = mesh->boundingBox->zMax - mesh->boundingBox->zMin;
    this->rect = rect;
    box = new BoundingBox(
            mesh->boundingBox->xMin, mesh->boundingBox->xMax,
            mesh->boundingBox->yMin, mesh->boundingBox->yMax,
            mesh->boundingBox->zMin, mesh->boundingBox->zMax
            );
    subNodes = new list<LT_Data*>();
    faces = new list<Face*>();

    for (auto obj : *mesh->meshes){
        for (auto f : obj->getFaces()) this->insert(f);
    }
}

LT_Data::LT_Data(Face *face, float xSize, float ySize, float zSize, RECT& rect) {
    xLimit = xSize;
    yLimit = ySize;
    zLimit = zSize;
    this->rect = rect;
    box = new BoundingBox(
            face->boundingBox->xMin, face->boundingBox->xMax,
            face->boundingBox->yMin, face->boundingBox->yMax,
            face->boundingBox->zMin, face->boundingBox->zMax
    );
    subNodes = new list<LT_Data*>();
    faces = new list<Face*>();
    this->insert(face);
}

LT_Data::~LT_Data() {
    delete faces;
    for (auto sub : *subNodes) delete sub;
    delete subNodes;
    delete box;
}

bool LT_Data::operator<(LT_Data &data) {
    return data.subNodes->size() < this->subNodes->size();
}

bool LT_Data::insert(Face *face) {
    auto fBox = face->boundingBox;
    if (xLimit < max(fBox->xMax, box->xMax) - min(fBox->xMin, box->xMin)) return false;
    if (yLimit < max(fBox->yMax, box->yMax) - min(fBox->yMin, box->yMin)) return false;
    if (zLimit < max(fBox->zMax, box->zMax) - min(fBox->zMin, box->zMin)) return false;

    box->expand(fBox);
    for (auto sub : *subNodes) {
        if (sub->insert(face)){
            subNodes->sort();
            return true;
        }
    }

    if (xLimit/2 >= fBox->xMax - fBox->xMin && yLimit/2 >= fBox->yMax - fBox->yMin && zLimit/2 >= fBox->zMax - fBox->zMin)
        subNodes->push_back(new LT_Data(face, xLimit/2, yLimit/2, zLimit/2, rect));
    else
        faces->push_back(face);
    return true;
}

pair<float, pair<vector<float>, Face *>> LT_Data::getFirstCross(vector<float> &start, vector<float> &direction) {
    if (!checkBox(start, direction)) return empty;
    pair<float, pair<vector<float>, Face *>> result = empty;
    auto distance = FLT_MAX;
    for (auto sub : *subNodes) {
        auto temp = sub->getFirstCross(start, direction);
        if (temp.second.second == nullptr) continue;
        if (temp.first < distance) {
            distance = temp.first;
            result = temp;
        }
    }
    for (auto f : *faces) {
        if (getMatrixMulti(f->getNormalVector(), direction) > 0) continue;
        auto temp = getFaceCross(f, start, direction);
        if (temp.second.second == nullptr) continue;
        if (temp.first < distance) {
            distance = temp.first;
            result = temp;
        }
    }
    return result;
}

pair<float, pair<vector<float>, Face *>> LT_Data::getFaceCross(Face *face, vector<float> &start, vector<float> &direction) {
    auto vertexes = face->getVertexes();
    vector<float> E1 = {vertexes[1]->getX() - vertexes[0]->getX(), vertexes[1]->getY() - vertexes[0]->getY(), vertexes[1]->getZ() - vertexes[0]->getZ()};
    vector<float> E2 = {vertexes[2]->getX() - vertexes[0]->getX(), vertexes[2]->getY() - vertexes[0]->getY(), vertexes[2]->getZ() - vertexes[0]->getZ()};
    vector<float> P = getMatrixCross(direction, E2);
    float denominator = getMatrixMulti(P, E1);
    vector<float> T = {start[0] - vertexes[0]->getX(), start[1] - vertexes[0]->getY(), start[2] - vertexes[0]->getZ()};
    if (denominator < 0) {
        denominator = -denominator;
        T[0] = -T[0];
        T[1] = -T[1];
        T[2] = -T[2];
    }
    if (denominator < 0.001f) return empty;
    vector<float> Q = getMatrixCross(T, E1);
    float t = getMatrixMulti(Q, E2)/denominator;
    if (t < 0.0001) return empty;

    float u = getMatrixMulti(P, T)/denominator;
    float v = getMatrixMulti(Q, direction)/denominator;
    if (u < 0 || v < 0 || u + v > 1) return empty;
    vector<float> cross = {vertexes[0]->getX() + E1[0] * u + E2[0] * v, vertexes[0]->getY() + E1[1] * u + E2[1] * v, vertexes[0]->getZ() + E1[2] * u + E2[2] * v};
    return make_pair(t, make_pair(cross, face));
}

bool LT_Data::checkBox(vector<float> &start, vector<float> &direction) {
    if (direction[0] < 0 && start[0] < box->xMin || direction[0] > 0 && start[0] > box->xMax) return false;
    if (direction[1] < 0 && start[1] < box->yMin || direction[1] > 0 && start[1] > box->yMax) return false;
    if (direction[2] < 0 && start[2] < box->zMin || direction[2] > 0 && start[2] > box->zMax) return false;

    auto xRange = getRange(direction[0], start[0], box->xMin, box->xMax);
    auto yRange = getRange(direction[1], start[1], box->yMin, box->yMax);
    auto zRange = getRange(direction[2], start[2], box->zMin, box->zMax);
    return max(xRange.first, max(yRange.first, zRange.first)) < min(xRange.second, min(yRange.second, zRange.second));
}

pair<float, float> LT_Data::getRange(float dt, float start, float min, float max) {
    if (abs(dt) < 0.0000001 && min <= start && start <= max)
        return make_pair(0, FLT_MAX);
    else if (abs(dt) < 0.0000001)
        return make_pair(FLT_MAX, 0);
    else if (min <= start && start <= max)
        return make_pair(0, (dt > 0)? (max - start)/dt : (min - start)/dt);
    else if (dt > 0)
        return make_pair((min - start)/dt, (max - start)/dt);
    else
        return make_pair((max - start)/dt, (min - start)/dt);
}
