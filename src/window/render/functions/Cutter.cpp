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
        auto vertexes = (*iter)->getVertexes();
        auto l1 = vertexes[0]->getLocation();
        auto l2 = vertexes[1]->getLocation();
        auto l3 = vertexes[2]->getLocation();

        auto t1 = Vertex::translate(l1[1], l1[2], rect);
        auto t2 = Vertex::translate(l2[1], l2[2], rect);
        auto t3 = Vertex::translate(l3[1], l3[2], rect);

        if (t1[0] < 0 && t2[0] < 0 && t3[0] < 0) iter = faces.erase(iter);
        else if (t1[0] >= rect.right && t2[0] >= rect.right && t3[0] >= rect.right) iter = faces.erase(iter);
        else if (t1[1] < 0 && t2[1] < 0 && t3[1] < 0) iter = faces.erase(iter);
        else if (t1[1] >= rect.bottom && t2[1] >= rect.bottom && t3[1] >= rect.bottom) iter = faces.erase(iter);
        else iter++;
    }
}
