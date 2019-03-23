#ifndef GETSTRINGPIC3_H
#define GETSTRINGPIC3_H
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <iostream>
using namespace std;

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QString>
using namespace cv;
//#define T 27
//#define T1 2
#define S(image,x,y) ((uchar*)(image->imageData + image->widthStep*(y)))[(x)]
class GetStringPic3
{
public:
        int T;  //判断一行是不是车牌有效信息的阈值
        int T1; //判断一列是不是车牌有效信息的阈值
        GetStringPic3();
        IplImage *src;
        IplImage *pImg8u=NULL;             //灰度图
        IplImage *pImg8uSmooth=NULL;       //高斯滤波后的图
        IplImage *pImgCanny=NULL;          //二值化的图
        IplImage *pImg8uROI=NULL;         //感兴趣的图片
        IplImage *pImgResize=NULL;        //归一化的灰度图

        IplImage *pImgCharOne=NULL;
        IplImage *pImgCharTwo=NULL;
        IplImage *pImgCharThree=NULL;
        IplImage *pImgCharFour=NULL;
        IplImage *pImgCharFive=NULL;
        IplImage *pImgCharSix=NULL;
        IplImage *pImgCharSeven=NULL;


        int i,j;
        int row_start,row_end;             //用来记录车牌开始，结束行
        int col_start,col_end;             //用来记录车牌开始，结束列
        int row[120];                      //row[]存放含有有效车牌信息的第j行，把所有有效行放一个数组里面，统一管理，有利于判断。
        int col[340];                      //存放每个字符双边界（列）的位置
        int k=0;                           //含有有效车牌信息的行数
        int nCharWidth=45;                 //每个字符的列，也就是宽度
        int nSpace=12;                     //字符之间的间隙
        int nWidth=409;                    //(409,90)分别为感兴趣图像的宽度与高度
        int nHeight=90;

        void find_UpAndDown_row(IplImage *src_son_row);
                                          //定义一个子函数，找到图片中含有车牌有效信息的最上行和最下行
        void find_LeftAndRight_col(IplImage *src_son_col);
                                          //定义一个子函数，找到图片中含有车牌有效信息的最左列和最右列
        void find_ROI(IplImage *before_ROI,IplImage *after_ROI);
                                         //定义一个子函数find_ROI，找到图片中只含有目标区域的部分
        void cut_and_drawLine(IplImage *befour_cut_image );
                                         //定义一个子函数cut_and_drawLine，对含有车牌有效信息的图片分割出字符，并画出分割线
        void show_every_char(IplImage *showChar);

        void iniStringPic(QString filename);
};

#endif // GETSTRINGPIC3_H
