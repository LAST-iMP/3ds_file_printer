//
// Created by lenovo on 2020/8/2.
//

#ifndef INC_3DS_PRINTER_RENDER_PARAM_H
#define INC_3DS_PRINTER_RENDER_PARAM_H
//入射光方向
#define L_DIR {-0.577, -0.577, -0.577}
//#define L_DIR {-1.0, 0, 0}
//阴影变换矩阵
#define ShadowMatrix_X {0.53452, -0.80178, -0.26726}
#define ShadowMatrix_Y {0.53452, 0.80178, -0.26726}
#define ShadowMatrix_Z {0.53452, 0, 0.53452}
//视线焦点
#define EYE_POINT {4000, 0, 0}
//视线方向 {-1, 0, 0}
#define NS 6
//环境光强
#define Iar 45
#define Iag 45
#define Iab 45
//入射光强
#define Ipr 255
#define Ipg 255
#define Ipb 255
//漫反射系数
#define Kdr 0.4f
#define Kdg 0.3f
#define Kdb 0.2f
//遮蔽漫反射系数
#define BKdr Kdr * 0.2
#define BKdg Kdg * 0.2
#define BKdb Kdb * 0.2
//镜面反射系数
#define Ks 0.3f
//全局光照最小权值
#define MinWeight 0.001
//反射光强系数
#define RefWeight 0.1f

#endif //INC_3DS_PRINTER_RENDER_PARAM_H
