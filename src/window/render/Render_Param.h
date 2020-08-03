//
// Created by lenovo on 2020/8/2.
//

#ifndef INC_3DS_PRINTER_RENDER_PARAM_H
#define INC_3DS_PRINTER_RENDER_PARAM_H
//入射光方向
#define L {-0.577, -0.577, -0.577}
//视线方向 {-1, 0, 0}
#define N 100
//环境光强
#define Iar 10
#define Iag 10
#define Iab 10
//入射光强
#define Ipr 250
#define Ipg 250
#define Ipb 250
//漫反射系数
#define Kdr 0.6
#define Kdg 0.6
#define Kdb 0.45
//镜面反射系数
#define Ks 0.5
//#define Ksr (1 - Kdr)
//#define Ksg (1 - Kdg)
//#define Ksb (1 - Kdb)
//漫反射率
#define Rdr 0.2
#define Rdg 0.2
#define Rdb 0.2

#endif //INC_3DS_PRINTER_RENDER_PARAM_H
