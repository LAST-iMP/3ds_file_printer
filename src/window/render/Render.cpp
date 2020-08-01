
#include "Render.h"

Render::Render(const string &filePath) {
    CK_Main3DS* model = load(filePath);
    mesh = transform(model);
    delete model;
}

Render::~Render() {
    delete mesh;
}

CK_Main3DS* Render::load(const string& filePath) {
    fstream fp;
    fp.open(filePath.data(), ios::binary | ios::in);
    CK_Main3DS* result = nullptr;
    if (!!fp) result = startRead(fp);
    fp.close();
    return result;
}

CK_Main3DS* Render::startRead(fstream &fp) {
    char buffer[2];
    fp.read(buffer, 2);
    unsigned short id = (unsigned short)buffer[0] + ((unsigned short)(buffer[1])<<8u);

    if (id != MAIN3DS) return nullptr;
    else return new CK_Main3DS(id, fp);
}

Mesh* Render::transform(CK_Main3DS* m) {
    auto* edit = m->getFirstSubChunk(EDIT3DS);
    return new Mesh(dynamic_cast<CK_Edit3DS*>(edit));
}

void Render::draw(HWND hwnd) {
    //定义指向包含绘图信息的结构体变量
    PAINTSTRUCT PtStr;
    //获取窗口大小
    RECT rect;
    GetClientRect(hwnd, &rect);
    rect.bottom += ((rect.bottom & 0b11) == 0)? 0 : 4 - (rect.bottom & 0b11);
    rect.right += ((rect.right & 0b11) == 0)? 0 : 4 - (rect.right & 0b11);
    //开始绘制
    HDC hDC = BeginPaint(hwnd, &PtStr);
    //双缓冲绘制
    doubleBuffer(hDC, &rect);
    //释放资源
    EndPaint(hwnd, &PtStr);
}

void Render::doubleBuffer(HDC hdc,RECT *rect) {
    //画布长和宽
    int iWidth = rect->right;
    int iHeight = rect->bottom;
    int size = iWidth * iHeight * 3;
    //与hdc兼容的内存dc
    HDC g_hMemDC = CreateCompatibleDC(hdc);
    //位图信息头
    BYTE bmibuf[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
    memset(bmibuf, 0, sizeof(bmibuf));
    auto* pbmi = (BITMAPINFO*)bmibuf;
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biWidth = iWidth;
    pbmi->bmiHeader.biHeight = iHeight;
    pbmi->bmiHeader.biPlanes = 1;
    pbmi->bmiHeader.biBitCount = 24;
    pbmi->bmiHeader.biCompression = BI_RGB;
    //数据指针
    BYTE * g_pBits;
    //创建位图，放在g_hMemDC中，信息头为pbmi，使用RGB颜色，数据指针接收到g_pBits
    HBITMAP g_hBmp = CreateDIBSection(g_hMemDC, pbmi, DIB_RGB_COLORS, (void **)&g_pBits, nullptr, 0);
    //将位图选进内存dc中
    auto g_hOldBmp = (HBITMAP)SelectObject(g_hMemDC, g_hBmp);
    //绘制
    fillBuffer(g_pBits, *rect, size);
    BitBlt(hdc, 0, 0, iWidth, iHeight, g_hMemDC, 0, 0, SRCCOPY);
    //释放资源
    SelectObject(g_hMemDC, g_hOldBmp);
    DeleteObject(g_hBmp);
    ReleaseDC(nullptr, hdc);
    DeleteDC(g_hMemDC);
}

void Render::fillBuffer(BYTE* buffer, RECT& rect, int length) {
    memset(buffer, 255, length);

    RENDER_DATA data(this->mesh);
    Cutter::cut(rect, data);
    Blanker::blank(data);

    struct timeval start, end;
    mingw_gettimeofday(&start, nullptr);
    Rasterize::rasterize(buffer, rect, data);
    mingw_gettimeofday(&end, nullptr);
    cout<<"spend: "<<(end.tv_sec * 1000000 - start.tv_sec * 1000000 + end.tv_usec - start.tv_usec)<<"us, "<<(end.tv_sec * 1000000 - start.tv_sec * 1000000 + end.tv_usec - start.tv_usec)/1000<<"ms"<<endl<<endl;
}
