#include "getstringpic3.h"
#include <QDebug>
GetStringPic3::GetStringPic3()
{
    T = 27;
    T1 = 2;
}
void GetStringPic3::iniStringPic(QString filename)
{

    QByteArray ba = filename.toLatin1();
    src = cvLoadImage(ba.data(),-1);
    if(src==NULL)
    {
         qDebug()<<"没有该图片";
    }else{
    IplImage *img_ty = NULL;
    CvSize dst_cvsize;
    dst_cvsize.height = 90;
    dst_cvsize.width = 300;
    img_ty = cvCreateImage(dst_cvsize, src->depth, src->nChannels);
    cvResize(src, img_ty, CV_INTER_LINEAR);         //二线性插值法会出现灰度
    src = cvCloneImage( img_ty );


        pImg8uSmooth=cvCreateImage(dst_cvsize,IPL_DEPTH_8U,1);

        pImg8u=cvCreateImage(dst_cvsize,IPL_DEPTH_8U,1);
        pImgCanny=cvCreateImage(dst_cvsize,IPL_DEPTH_8U,1);

        cvCvtColor(src,pImg8u,CV_RGB2GRAY);//灰度化

        cvSmooth(pImg8u,pImg8uSmooth,CV_GAUSSIAN,3,0,0);   //高斯滤波
        cvCanny(pImg8uSmooth,pImgCanny,100,200,3);         //二值化
        cvDilate(pImgCanny,pImgCanny,0,1);
        cvErode(pImgCanny,pImgCanny,0,1);
        cvNamedWindow("cvcanny",1);
        cvShowImage("cvcanny",pImgCanny);


        row_start=0;
        row_end=0;
        col_start=0;
        col_end=0;
        qDebug()<<"图片的高度值（即像素的行数）为："<<pImgCanny->height<<endl;
        qDebug()<<"图片的宽度值（即像素的列数）为："<<pImgCanny->width<<endl;


         find_UpAndDown_row(pImgCanny);   //找到图片中含有车牌有效信息的最上行和最下行
         find_LeftAndRight_col(pImgCanny);//找到图片中含有车牌有效信息的最左列和最右列
         find_ROI(pImg8u,pImg8uROI);      //找到图片中只含有目标区域的部分

        pImgResize=cvCreateImage(cvSize(nWidth,nHeight),IPL_DEPTH_8U,1);
        cvResize(pImg8uROI,pImgResize,CV_INTER_LINEAR); //线性插值
        cvNamedWindow("感兴趣图像的宽度与高度",1);
        cvShowImage("感兴趣图像的宽度与高度",pImgResize);

        cut_and_drawLine(pImgResize );    //对含有车牌有效信息的图片分割出字符，并画出分割线
        show_every_char(pImgResize);      //显示出所有分割出来的字符
        cvWaitKey(0);

        cvReleaseImage(&pImgResize);
        cvReleaseImage(&pImg8uROI);
        cvReleaseImage(&pImgCharOne);
        cvReleaseImage(&pImgCharTwo);
        cvReleaseImage(&pImgCharThree);
        cvReleaseImage(&pImgCharFour);
        cvReleaseImage(&pImgCharFive);
        cvReleaseImage(&pImgCharSix);
        cvReleaseImage(&pImgCharSeven);

        cvDestroyAllWindows();
    }
}
void GetStringPic3::find_UpAndDown_row(IplImage *src_son_row){
/////////////////////////////////////////////////////////判断每行是不是含有车牌信息的行是通过查看黑点白点变化的次数来确定的

//    qDebug()<<"T"<<T;
//    qDebug()<<"T1"<<T1;
    for(j=0;j<src_son_row->height;j++)
                                                       //遍历整幅图的行和列，寻找包含车牌信息的行数
    {
        int count=0;                                       //  count/2  记录每行白点（水平的白线看做一个点）的个数
        for(i=0;i<src_son_row->width;i++)
        {
            if(S(src_son_row,i,j)!=S(src_son_row,i+1,j))  //统计行跳数
                count++;
            if(count>T)                               //把含有车牌有效信息的行j存放到row[k]
            {
                row[k]=j;
                k++;                                  //记录含有有效车牌信息的行数
                break;
            }
        }
        //cout<<"count值为："<<count<<endl;
    }
    qDebug()<<"有效行k值为："<<k<<endl;
    for(i=0;i<k;i++)                                 //从上边开始，3行连续时认为是起始行
    {
        if((row[i]==row[i+1]-1)&&(row[i+1]==row[i+2]-1)){
            row_start=row[i];
           // cout<<"the start row123:"<<row_start<<endl;
            break;
        }
    }
    qDebug()<<"the start row:"<<row_start<<endl;
    cvLine(pImg8u,cvPoint(0,row_start),cvPoint(src->width,row_start),cvScalar(255,0,0),1,8,0);
    cvNamedWindow("划线_上",1);
    cvShowImage("划线_上",pImg8u);

    for(i=k-1;i>row_start;i--)     //从下边开始，3行连续时认为是起始行
    {
        if((row[i]==row[i-1]+1)&&(row[i-1]==row[i-2]+1)){
            row_end=row[i];
            break;
        }
    }
    qDebug()<<"the end row:"<<row_end<<endl;
    cvLine(pImg8u,cvPoint(0,row_end),cvPoint(src->width,row_end),cvScalar(255,0,0),1,8,0);
    cvNamedWindow("划线_上下",1);
    cvShowImage("划线_上下",pImg8u);
}
/******************************************************************************************\
      定义一个子函数find_LeftAndRight_col，找到图片中含有车牌有效信息的最左列和最右列
\******************************************************************************************/
void GetStringPic3::find_LeftAndRight_col(IplImage *src_son_col){
/////////////////////////////////////////////////判断每列是不是含有车牌有效信息是查看每列中含有白点像素的个数
    bool flag=false;
    for(i=10;i<src_son_col->width;i++)           //找到左列开始？？？i为什么是10？？？
    {
        int count=0;
        for(j=row_start;j<row_end;j++)
        {
            if(S(src_son_col,i,j)==255)
                count++;
            if(count>T1)
            {
                col_start=i;
                flag=true;
                break;
            }
        }
        if(flag) break;
    }
    cout<<"the start col:"<<col_start<<endl;
    cvLine(pImg8u,cvPoint(col_start,row_start),cvPoint(col_start,row_end),cvScalar(255,0,0),1,8,0);
    cvNamedWindow("划线_左",1);
    cvShowImage("划线_左",pImg8u);

    flag=false;
    for(i=src_son_col->width-10;i>col_start;i--)           //找到右列开始
    {
        int count=0;
        for(j=row_start;j<row_end;j++)
        {
            if(S(src_son_col,i,j)==255)
                count++;
            if(count>T1)
            {
                col_end=i;
                flag=true;
                break;
            }
        }
        if(flag) break;
    }
    cout<<"the end col:"<<col_end<<endl;
    cvLine(pImg8u,cvPoint(col_end,row_start),cvPoint(col_end,row_end),cvScalar(255,0,0),1,8,0);
    cvNamedWindow("划线_左右",1);
    cvShowImage("划线_左右",pImg8u);
}
/******************************************************************************************\
              定义一个子函数find_ROI，找到图片中只含有目标区域的部分
\******************************************************************************************/
void GetStringPic3::find_ROI(IplImage *before_ROI,IplImage *after_ROI){
    CvRect ROI_rect;                 //获得图片感兴趣区域
    ROI_rect.x=col_start;
    ROI_rect.y=row_start;
    ROI_rect.width=col_end-col_start;
    ROI_rect.height=row_end-row_start;
    cvSetImageROI(pImg8u,ROI_rect);
    pImg8uROI=cvCreateImage(cvSize(ROI_rect.width,ROI_rect.height),IPL_DEPTH_8U,1);
    cvCopy(pImg8u,pImg8uROI);
    cvResetImageROI(pImg8u);
    }
 /******************************************************************************************\
      定义一个子函数cut_and_drawLine，对含有车牌有效信息的图片分割出字符，并画出分割线
\******************************************************************************************/
 void GetStringPic3::cut_and_drawLine(IplImage *befour_cut_image ){

     for(i=0;i<7;i++)
    {
        switch(i){
            case 0:                                          //0是省份名占45个像素
            case 1:                                          //1是市名的字母占45个像素
                col[i*2]=i*nCharWidth+i*nSpace;
                //cout<<col[i*2]<<endl;
                col[i*2+1]=(i+1)*nCharWidth+i*nSpace;
                //cout<<col[i*2+1]<<endl;
                break;                                       //1与2之间有个点宽度是34个像素
            case 2:                                          //2---6是剩余的字母和数字各自占45个像素
            case 3:
            case 4:
            case 5:
            case 6:
                col[i*2]=i*nCharWidth+i*nSpace+22;
                cout<<col[i*2]<<endl;
                col[i*2+1]=(i+1)*nCharWidth+i*nSpace+22;
                cout<<col[i*2+1]<<endl;
                break;
        }

    }
    for(i=0;i<14;i++)        //画出每个字符的区域
    {
        cvLine(befour_cut_image,cvPoint(col[i],0),cvPoint(col[i],nHeight),cvScalar(255,0,0),1,8,0);
        //cout<<col[i*2]<<" "<<col[2*i+1]<<" ";
    }
    //cvNamedWindow("画出每个字符的区域",1);
    //cvShowImage("画出每个字符的区域",befour_cut_image);

 }
/******************************************************************************************\
              定义一个子函数show_every_char，显示出所有分割出来的字符
\******************************************************************************************/
void GetStringPic3:: show_every_char(IplImage *showChar){

    pImgCharOne=cvCreateImage(cvSize(nCharWidth,nHeight),IPL_DEPTH_8U,1);
    pImgCharTwo=cvCreateImage(cvSize(nCharWidth,nHeight),IPL_DEPTH_8U,1);
    pImgCharThree=cvCreateImage(cvSize(nCharWidth,nHeight),IPL_DEPTH_8U,1);
    pImgCharFour=cvCreateImage(cvSize(nCharWidth,nHeight),IPL_DEPTH_8U,1);
    pImgCharFive=cvCreateImage(cvSize(nCharWidth,nHeight),IPL_DEPTH_8U,1);
    pImgCharSix=cvCreateImage(cvSize(nCharWidth,nHeight),IPL_DEPTH_8U,1);
    pImgCharSeven=cvCreateImage(cvSize(nCharWidth,nHeight),IPL_DEPTH_8U,1);

    CvRect ROI_rect1;
    ROI_rect1.x=col[0];
    ROI_rect1.y=0;
    ROI_rect1.width=nCharWidth;
    ROI_rect1.height=nHeight;
    cvSetImageROI(showChar,ROI_rect1);
    cvCopy(showChar,pImgCharOne,NULL); //获取第1个字符
    cvResetImageROI(showChar);

    ROI_rect1.x=col[2];
    ROI_rect1.y=0;
    ROI_rect1.width=nCharWidth;
    ROI_rect1.height=nHeight;
    cvSetImageROI(showChar,ROI_rect1);
    cvCopy(showChar,pImgCharTwo,NULL); //获取第2个字符
    cvResetImageROI(showChar);

    ROI_rect1.x=col[4];
    ROI_rect1.y=0;
    ROI_rect1.width=nCharWidth;
    ROI_rect1.height=nHeight;
    cvSetImageROI(showChar,ROI_rect1);
    cvCopy(showChar,pImgCharThree,NULL); //获取第3个字符
    cvResetImageROI(showChar);

    ROI_rect1.x=col[6];
    ROI_rect1.y=0;
    ROI_rect1.width=nCharWidth;
    ROI_rect1.height=nHeight;
    cvSetImageROI(showChar,ROI_rect1);
    cvCopy(showChar,pImgCharFour,NULL); //获取第4个字符
    cvResetImageROI(showChar);

    ROI_rect1.x=col[8];
    ROI_rect1.y=0;
    ROI_rect1.width=nCharWidth;
    ROI_rect1.height=nHeight;
    cvSetImageROI(showChar,ROI_rect1);
    cvCopy(showChar,pImgCharFive,NULL); //获取第5个字符
    cvResetImageROI(showChar);

    ROI_rect1.x=col[10];
    ROI_rect1.y=0;
    ROI_rect1.width=nCharWidth;
    ROI_rect1.height=nHeight;
    cvSetImageROI(showChar,ROI_rect1);
    cvCopy(showChar,pImgCharSix,NULL); //获取第6个字符
    cvResetImageROI(showChar);

    ROI_rect1.x=col[12];
    ROI_rect1.y=0;
    ROI_rect1.width=nCharWidth;
    ROI_rect1.height=nHeight;
    cvSetImageROI(showChar,ROI_rect1);
    cvCopy(showChar,pImgCharSeven,NULL); //获取第7个字符
    cvResetImageROI(showChar);

    cvNamedWindow("分割后的车牌",1);
    cvShowImage("分割后的车牌",showChar);
    cvNamedWindow("one",CV_WINDOW_AUTOSIZE);
    cvShowImage("one",pImgCharOne);
    cvNamedWindow("two",1);
    cvShowImage("two",pImgCharTwo);
    cvNamedWindow("three",1);
    cvShowImage("three",pImgCharThree);
    cvNamedWindow("four",1);
    cvShowImage("four",pImgCharFour);
    cvNamedWindow("five",1);
    cvShowImage("five",pImgCharFive);
    cvNamedWindow("six",1);
    cvShowImage("six",pImgCharSix);
    cvNamedWindow("seven",1);
    cvShowImage("seven",pImgCharSeven);
    }
