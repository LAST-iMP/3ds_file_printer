
#include "MainFrame.h"

Render* MainFrame::render;

MainFrame::MainFrame(HINSTANCE hinstance, HINSTANCE hPreInstance, char *ipCmdLine, int nShowCmd) {
    this->hinstance = hinstance;
    this->hPreInstance = hPreInstance;
}

MainFrame::~MainFrame() {
    delete render;
}

void MainFrame::show(const string& filePath) {
    MainFrame::render = new Render(filePath);
    registerWindow();
    /*获取新窗口句柄 参数：
     * unsigned long 窗口拓展样式 WS_EX_开头常量
     * char * 窗口类名 需要和窗口类定义相同
     * char * 窗口标题名
     * unsigned long 窗口样式 WS_开头常量
     * int*4 代表左边，上边，宽度，高度
     * HWND 父窗口句柄，无则为null
     * HMENU菜单句柄，无则为null
     * HINSTANCE 实例句柄
     * void * 默认为null
     */
    hwnd = CreateWindowExA(WS_EX_LEFT, WINDOW_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, 400, 100, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hinstance, NULL);
    //设置窗口显示状态，SW_开头常量
    ShowWindow(hwnd, SW_SHOW);
    //立即发送WM_POINT消息让窗口处理函数执行
    UpdateWindow(hwnd);
    startListen(hwnd);
}

bool MainFrame::registerWindow() {
/* typedef struct tagWNDCLASSEXA {
            UINT        cbSize;           //WNDCLASSEXA 结构体的大小（sizeof（WNDCLASSEX））
            UINT        style;            //窗口类的样式
            WNDPROC     lpfnWndProc;      //窗口处理函数的指针
            int         cbClsExtra;       //为窗口类的额外信息做记录，初始化为0。
            int         cbWndExtra;       //记录窗口实例的额外信息，系统初始为0
            HINSTANCE   hInstance;        //本模块的实例句柄
            HICON       hIcon;            //窗口类的图标，为图标资源句柄
            HCURSOR     hCursor;          //窗口类的鼠标样式，为鼠标样式资源的句柄
            HBRUSH      hbrBackground;    //窗口类的背景刷，为背景刷句柄
            LPCSTR      lpszMenuName;     //指向菜单的指针
            LPCSTR      lpszClassName;    //指向类名称的指针
            HICON       hIconSm;          //小图标的句柄，在任务栏显示的图标
        } WNDCLASSEXA, *PWNDCLASSEXA, NEAR *NPWNDCLASSEXA, FAR *LPWNDCLASSEXA;
    */
    WNDCLASSEXA wndClass = {0};
    //分配给WNDCLASSEX的空间
    wndClass.cbSize = sizeof(WNDCLASSEXA);
    //窗口类所有窗口的样式
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    //消息处理函数
    wndClass.lpfnWndProc = wndProc;
    //该类生成的所有窗口共享附加空间
    wndClass.cbClsExtra = 0;
    //每实例化一个窗口的空间
    wndClass.cbWndExtra = 0;
    //模块实例句柄
    wndClass.hInstance = hinstance;
    //图标句柄
    wndClass.hIcon = LoadIconA(hinstance, IDI_APPLICATION);
    //鼠标句柄
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    //背景图刷句柄
    wndClass.hbrBackground = CreateSolidBrush(GRAY_BRUSH);
    //菜单指针
    wndClass.lpszMenuName = nullptr;
    //窗口类名指针
    wndClass.lpszClassName = WINDOW_NAME;
    //底部任务栏小图标句柄
    wndClass.hIconSm = nullptr;
    //注册窗口
    return RegisterClassExA(&wndClass) != 0;
}

int MainFrame::startListen(HWND hwnd) {
    /*   typedef struct tagMSG {
            HWND hwnd; 消息所属窗口句柄
            UINT message; 消息标识符 WM_开头常量
            WPARAM wParam; 消息的两个参数
            LPARAM lParam;
            DWORD time; 消息投递时间
            POINT pt; 投递过程中鼠标的位置
          } MSG,*PMSG,*NPMSG,*LPMSG;
     */
    MSG msg = {0};
    //MSG结构体地址，窗体句柄（null则获取所有消息），消息编号最大值，消息编号最小值
    while (true) {
        if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            //将虚拟消息转换为字符消息
            TranslateMessage(&msg);
            //将消息发送给处理函数
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK MainFrame::wndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
        case WM_PAINT:
            MainFrame::render->draw(hwnd);
            break;
        case WM_KEYDOWN:
            if (wparam == VK_ESCAPE)
                DestroyWindow(hwnd);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_LBUTTONDOWN:
            break;
        default:
            return DefWindowProc(hwnd, message, wparam, lparam);
    }
    return 0;
}

