cmake_minimum_required(VERSION 3.16)
project(3ds_printer)

set(CMAKE_CXX_STANDARD 11)

add_executable(3ds_printer
        src/3dsEntity/Chunk.cpp
        src/3dsEntity/ChunkImp/CK_Main3DS.cpp src/3dsEntity/ChunkImp/CK_Unknown.cpp
        src/3dsEntity/ChunkImp/Main3DS/CK_Edit3DS.cpp
        src/3dsEntity/ChunkImp/Main3DS/Edit3DS/CK_Edit_Object.cpp
        src/3dsEntity/ChunkImp/Main3DS/Edit3DS/EditObject/CK_Obj_TriMesh.cpp
        src/3dsEntity/ChunkImp/Main3DS/Edit3DS/EditObject/TriMesh/CK_Tri_Face1.cpp
        src/3dsEntity/ChunkImp/Main3DS/Edit3DS/EditObject/TriMesh/CK_Tri_Local.cpp
        src/3dsEntity/ChunkImp/Main3DS/Edit3DS/EditObject/TriMesh/CK_Tri_Vertex.cpp
        src/MeshEntity/Mesh_Obj.cpp src/MeshEntity/components/Face.cpp src/MeshEntity/components/HalfEdge.cpp src/MeshEntity/components/Vertex.cpp
        src/window/render/Render.cpp src/window/render/Render.h src/main.cpp src/window/MainFrame.cpp src/window/MainFrame.h src/window/WindowInfo.h src/window/render/functions/Rasterize.cpp src/window/render/functions/Rasterize.h src/window/render/functions/Cutter.cpp src/window/render/functions/Cutter.h src/window/render/functions/Blanker.cpp src/window/render/functions/Blanker.h src/window/render/Render_DATA.h src/MeshEntity/Mesh.cpp src/MeshEntity/Mesh.h src/MeshEntity/components/BoundingBox.cpp src/MeshEntity/components/BoundingBox.h src/window/render/Render_Param.h)