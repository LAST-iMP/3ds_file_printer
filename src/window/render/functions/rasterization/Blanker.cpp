//
// Created by lenovo on 2020/7/29.
//

#include "Blanker.h"

void Blanker::blank(RENDER_DATA &data) {
    checkDirection(data.faces);
}

void Blanker::checkDirection(unordered_set<Face*> * faces) {
    auto iter = faces->begin();
    while (iter != faces->end()) {
        if ((*iter)->getNormalVector().getX() < 0) iter = faces->erase(iter);
        else iter++;
    }
}

