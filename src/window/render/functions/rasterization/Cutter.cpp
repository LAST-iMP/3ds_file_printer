//
// Created by lenovo on 2020/7/29.
//

#include "Cutter.h"

void Cutter::cut(RECT &rect, RENDER_DATA &data) {
    checkLocation(*data.faces, rect);
}

void Cutter::checkLocation(unordered_set<Face*>& faces, RECT &rect) {
    auto iter = faces.begin();
    while (iter != faces.end()) {
        auto box = (*iter)->boundingBox;
        auto min = Vertex::translate(box->yMin, box->zMin, rect);
        auto max = Vertex::translate(box->yMax, box->zMax, rect);
        if (max[0] < 0 || max[1] < 0 || min[0] >= rect.right || min[1] >= rect.bottom) iter = faces.erase(iter);
        else iter++;
    }
}
