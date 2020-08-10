#include "LT_Data.h"

//距离，法向量，交点坐标，面引用
pair<pair<float, Vector3D>, pair<Vector3D, Face *>> LT_Data::empty = make_pair(make_pair(0, Vector3D()), make_pair(Vector3D(), nullptr));

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

pair<pair<float, Vector3D>, pair<Vector3D, Face *>> LT_Data::getFirstCross(
        pair<Vector3D, __decay_and_strip<Face *>::__type> start, Vector3D &direction) {
    if (!checkBox(start.first, direction)) return empty;
    pair<pair<float, Vector3D>, pair<Vector3D, Face *>> result = empty;
    auto distance = FLT_MAX;
    for (auto sub : *subNodes) {
        auto temp = sub->getFirstCross(start, direction);
        if (temp.second.second == nullptr) continue;
        if (temp.first.first < distance) {
            distance = temp.first.first;
            result = temp;
        }
    }
    for (auto f : *faces) {
        if (f->getNormalVector() * direction > 0) continue;
        auto temp = getFaceCross(f, start, direction);
        if (temp.second.second == nullptr) continue;
        if (temp.first.first < distance) {
            distance = temp.first.first;
            result = temp;
        }
    }
    return result;
}

pair<pair<float, Vector3D>, pair<Vector3D, Face *>> LT_Data::getFaceCross(Face *face, pair<Vector3D, Face *> &start, Vector3D &direction) {
    auto vertexes = face->getVertexes();
    Vector3D E1 = {vertexes[1]->getX() - vertexes[0]->getX(), vertexes[1]->getY() - vertexes[0]->getY(), vertexes[1]->getZ() - vertexes[0]->getZ()};
    Vector3D E2 = {vertexes[2]->getX() - vertexes[0]->getX(), vertexes[2]->getY() - vertexes[0]->getY(), vertexes[2]->getZ() - vertexes[0]->getZ()};
    Vector3D P = direction.cross(E2);
    float denominator = P * E1;
    auto startPoint = start.first;
    Vector3D T = {startPoint.getX() - vertexes[0]->getX(), startPoint.getY() - vertexes[0]->getY(), startPoint.getZ() - vertexes[0]->getZ()};
    if (denominator < 0.00001f) {
        denominator = -denominator;
        T = -T;
    }
    if (denominator < 0.00001f) return empty;
    Vector3D Q = T.cross(E1);
    float t = Q * E2 / denominator;
    if (t < 0.0001f && !(face == start.second && abs(t) < 0.01)) return empty;

    float u = P * T / denominator;
    float v = Q * direction / denominator;
    if (u < 0 || v < 0 || u + v > 1) return empty;
    Vector3D cross = {vertexes[0]->getX() + E1.getX() * u + E2.getX() * v, vertexes[0]->getY() + E1.getY() * u + E2.getY() * v, vertexes[0]->getZ() + E1.getZ() * u + E2.getZ() * v};
    Vector3D normal = *vertexes[0]->getAveNormal() + (*vertexes[1]->getAveNormal() - *vertexes[0]->getAveNormal()) * u + (*vertexes[2]->getAveNormal() - *vertexes[0]->getAveNormal()) * v;
    normal.toUnit();
    return make_pair(make_pair(t, normal), make_pair(cross, face));
}

bool LT_Data::checkBox(Vector3D &start, Vector3D &direction) {
    if (direction.getX() < 0 && start.getX() < box->xMin || direction.getX() > 0 && start.getX() > box->xMax) return false;
    if (direction.getY() < 0 && start.getY() < box->yMin || direction.getY() > 0 && start.getY() > box->yMax) return false;
    if (direction.getZ() < 0 && start.getZ() < box->zMin || direction.getZ() > 0 && start.getZ() > box->zMax) return false;

    auto xRange = getRange(direction.getX(), start.getX(), box->xMin, box->xMax);
    auto yRange = getRange(direction.getY(), start.getY(), box->yMin, box->yMax);
    auto zRange = getRange(direction.getZ(), start.getZ(), box->zMin, box->zMax);
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
