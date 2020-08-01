//
// Created by lenovo on 2020/7/29.
//

#include "Blanker.h"

void Blanker::blank(RENDER_DATA &data) {
    auto faces = data.faces;
    auto iter = faces->begin();
    while (iter != faces->end()) {
        if ((*iter)->getNormalVector()[0] < 0) iter = faces->erase(iter);
        else iter++;
    }
}
