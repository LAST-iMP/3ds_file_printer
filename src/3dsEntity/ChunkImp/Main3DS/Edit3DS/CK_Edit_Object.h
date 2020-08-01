//
// Created by lenovo on 2020/7/27.
//

#ifndef INC_3DS_PRINTER_CK_EDIT_OBJECT_H
#define INC_3DS_PRINTER_CK_EDIT_OBJECT_H

#include "EditObject/CK_Obj_TriMesh.h"

class CK_Edit_Object: public Chunk {
private:
    vector<char>* name;
public:
    CK_Edit_Object(unsigned short id, fstream & fp);
    ~CK_Edit_Object() override;
    void readSubChunks(fstream & fp);
    void readData(fstream & fp);
    vector<char>& getData();
    unsigned int getRealLength() override;
};
#endif //INC_3DS_PRINTER_CK_EDIT_OBJECT_H
